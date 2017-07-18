#pragma once
#include "stdafx.h"
#include "SceneObject.h"
#include "SceneManager.h"

SceneObject::SceneObject()
{
}


SceneObject::~SceneObject()
{
}

void SceneObject::Draw(ESContext * esContext)
{

	glUseProgram(shader->progId);

	SendCommonData();

	if (wired)
		glDrawElements(GL_LINES, model->mLinesIndices.size(), GL_UNSIGNED_SHORT, 0);
	else
		glDrawElements(GL_TRIANGLES, model->mIndices.size(), GL_UNSIGNED_SHORT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}


void SceneObject::SendCommonData()
{

	if (depthTest)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
	if( blend )
		glEnable(GL_BLEND);
	else
		glDisable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Matrix rotM, scaleM, transM, mod, MVP, rotX,rotY,rotZ;

	rotM.SetIdentity();
	transM.SetIdentity();
	scaleM.SetIdentity();
	mod.SetIdentity();


	rotM = rotX.SetRotationX(rotation.x) * rotY.SetRotationY(rotation.y) * rotZ.SetRotationZ(rotation.z);
	transM.SetTranslation(position.x, position.y, position.z);
	scaleM.SetScale(scale.x, scale.y, scale.z);

	mod = mod * scaleM * rotM * transM;
	Matrix view = SceneManager::getInstance()->GetActiveCamera()->viewMatrix;
	Matrix proj = SceneManager::getInstance()->GetActiveCamera()->projectionMatrix;

	MVP = mod * view * proj;

	glBindBuffer(GL_ARRAY_BUFFER, model->vboId);
	if (wired) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->wiredIboId);
	}
	else {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->iboId);
	}

	for (int i = 0; i < textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		switch (textures[i]->tr->type)
		{
		case TextureResource::_2d:
			glBindTexture(GL_TEXTURE_2D, textures[i]->texId);
			break;
		case TextureResource::cube:
			glBindTexture(GL_TEXTURE_CUBE_MAP, textures[i]->texId);
			break;
		}
		if (shader->textureUniform[i] != -1)
			glUniform1i(shader->textureUniform[i], i);
	}

	if (shader->positionAttribute != -1) {
		glEnableVertexAttribArray(shader->positionAttribute);
		glVertexAttribPointer(shader->positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	if (shader->colorAttribute != -1) {
		glEnableVertexAttribArray(shader->colorAttribute);
		glVertexAttribPointer(shader->colorAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(sizeof(Vector3)));
	}

	if (shader->normAttribute != -1) {
		glEnableVertexAttribArray(shader->normAttribute);
		glVertexAttribPointer(shader->normAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(2 * sizeof(Vector3)));
	}

	if (shader->binormAttribute != -1) {
		glEnableVertexAttribArray(shader->binormAttribute);
		glVertexAttribPointer(shader->binormAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(3 * sizeof(Vector3)));
	}

	if (shader->tgtAttribute != -1) {
		glEnableVertexAttribArray(shader->tgtAttribute);
		glVertexAttribPointer(shader->tgtAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(4 * sizeof(Vector3)));
	}

	if (shader->uvAttribute != -1) {
		glEnableVertexAttribArray(shader->uvAttribute);
		glVertexAttribPointer(shader->uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(5 * sizeof(Vector3)));
	}

	if (shader->MVPuniform != -1)
		glUniformMatrix4fv(shader->MVPuniform, 1, GL_FALSE, (const GLfloat *)MVP.m);

	//fog variables
	if (shader->modelUniform != -1)
		glUniformMatrix4fv(shader->modelUniform, 1, GL_FALSE, (const GLfloat *)mod.m);
	if (shader->fogUniform != -1)
		glUniform3f( shader->fogUniform,(const GLfloat)SceneManager::getInstance()->fog_color.x,
										(const GLfloat)SceneManager::getInstance()->fog_color.y, 
										(const GLfloat)SceneManager::getInstance()->fog_color.z);
	if (shader->rUniform != -1)
		glUniform1f(shader->rUniform, (const GLfloat)SceneManager::getInstance()->fog_start);
	if (shader->RUniform != -1)
		glUniform1f(shader->RUniform, (const GLfloat)SceneManager::getInstance()->fog_end);
	if (shader->cameraUniform != -1)
		glUniform3f(shader->cameraUniform,  (const GLfloat)SceneManager::getInstance()->GetActiveCamera()->position.x,
											(const GLfloat)SceneManager::getInstance()->GetActiveCamera()->position.y,
											(const GLfloat)SceneManager::getInstance()->GetActiveCamera()->position.z);

	if (shader->shininessUniform != -1)
		glUniform1f(shader->shininessUniform, (const GLfloat)shininess);

	if (shader->ambLight != -1)
		glUniform3f(shader->ambLight,   (const GLfloat)SceneManager::getInstance()->ambientalColor.x,
										(const GLfloat)SceneManager::getInstance()->ambientalColor.y,
										(const GLfloat)SceneManager::getInstance()->ambientalColor.z);

	for (int i = 0; i < SceneManager::getInstance()->light.size() ; i++) {
		if (shader->dirDiffLight != -1)
			glUniform3f(shader->dirDiffLight, 
					(const GLfloat)SceneManager::getInstance()->light[i]->diffuseColor.x,
					(const GLfloat)SceneManager::getInstance()->light[i]->diffuseColor.y,
					(const GLfloat)SceneManager::getInstance()->light[i]->diffuseColor.z);
		if (shader->dirSpecLight != -1)
			glUniform3f(shader->dirSpecLight,
					(const GLfloat)SceneManager::getInstance()->light[i]->specularColor.x,
					(const GLfloat)SceneManager::getInstance()->light[i]->specularColor.y,
					(const GLfloat)SceneManager::getInstance()->light[i]->specularColor.z);
		if (shader->dirSpecLight != -1)
			glUniform1f(shader->dirSpecCoef, (const GLfloat)SceneManager::getInstance()->light[i]->specCoef);

		switch (SceneManager::getInstance()->light[i]->type) {
		case LightObject::directional:
			if (shader->dirDirection != -1)
				glUniform3f(shader->dirDirection,  
						(const GLfloat)SceneManager::getInstance()->light[i]->direction.x,
						(const GLfloat)SceneManager::getInstance()->light[i]->direction.y,
						(const GLfloat)SceneManager::getInstance()->light[i]->direction.z);

			break;
		case LightObject::spot:
			break;
		}
	}

}


void SceneObject::Update(ESContext * esContext, float deltaTime)
{
}


