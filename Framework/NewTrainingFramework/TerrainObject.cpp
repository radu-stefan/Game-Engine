#include "stdafx.h"
#include "TerrainObject.h"
#include "SceneManager.h"

TerrainObject::TerrainObject()
{
}


TerrainObject::~TerrainObject()
{
}

void TerrainObject::Draw(ESContext * esContext)
{
	
	glUseProgram(shader->progId);

	SendCommonData();

	if (shader->uvBlendAttribute != -1) {
		glEnableVertexAttribArray(shader->uvBlendAttribute);
		glVertexAttribPointer(shader->uvBlendAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(5 * sizeof(Vector3) + sizeof(Vector2)));
	}

	if (shader->heightUniform != -1) 
		glUniform3f(shader->heightUniform, (const GLfloat) height.x, (const GLfloat)height.y, (const GLfloat)height.z);
	if (shader->uv_offsetUniform != -1)
		glUniform2f(shader->uv_offsetUniform, (const GLfloat)uv_offset.x, (const GLfloat)uv_offset.y);


	if (wired)
		glDrawElements(GL_LINES, model->mLinesIndices.size(), GL_UNSIGNED_SHORT, 0);
	else
		glDrawElements(GL_TRIANGLES, model->mIndices.size(), GL_UNSIGNED_SHORT, 0);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void TerrainObject::Update(ESContext * esContext, float deltaTime)
{
	Camera c = *SceneManager::getInstance()->GetActiveCamera();

	//position.x = c.position.x;
	//position.z = c.position.z;

	pos1 = Vector2(c.position.x, c.position.z);

	while ( pos1.x - pos0.x >= dim_celula ) {
		//miscare la dreapta
		position.x += dim_celula;
		pos0.x += dim_celula;
		uv_offset.x += 1 / (float)nr_celule;
	}
	while (fabs(pos1.x - pos0.x) >= dim_celula ) {
		position.x -= dim_celula;
		pos0.x -= dim_celula;
		uv_offset.x -= 1 / (float)nr_celule;
		//miscare la stanga
	}
	while (pos1.y - pos0.y >= dim_celula) {
		position.z += dim_celula;
		pos0.y += dim_celula;
		uv_offset.y -= 1 / (float)nr_celule;
		// miscare sus
	}
	while (fabs(pos1.y - pos0.y) >= dim_celula) {
		position.z -= dim_celula;
		pos0.y -= dim_celula;
		uv_offset.y += 1 / (float)nr_celule;
		//miscare jos
	}

}

void TerrainObject::Generate()
{
	Vertex vertex;
	model = new Model();
	uv_offset = Vector2(0, 0);
	Camera c = *SceneManager::getInstance()->GetActiveCamera();

	int z, x, i, j;
	for (z = c.position.z + dim_celula*nr_celule / 2, i = 0; i <= nr_celule; i++, z -= dim_celula) {
		for (x = c.position.x - dim_celula*nr_celule / 2, j = 0; j <= nr_celule; j++, x+= dim_celula ) {
			vertex.uv = Vector2(j,i);
			vertex.uv_blend = Vector2(((float)j/ (float)nr_celule), ((float)i/ (float)nr_celule));
			vertex.pos = Vector3(x, offsetY, z);
			model->mVertex.push_back(Vertex(vertex));
		}
	}

	for (i = 0; i < model->mVertex.size() - nr_celule-1; i++) {
		
		if ( (i+1) % (nr_celule + 1) == 0 ) {
			continue;
		}
		model->mIndices.push_back(i);
		model->mIndices.push_back(i + 1);
		model->mIndices.push_back(i + nr_celule + 1);

		model->mIndices.push_back(i + 1);
		model->mIndices.push_back(i + nr_celule + 2);
		model->mIndices.push_back(i + nr_celule + 1);

		model->mLinesIndices.push_back(i);
		model->mLinesIndices.push_back(i+1);
		model->mLinesIndices.push_back(i+1);
		model->mLinesIndices.push_back(i+nr_celule+1);
		model->mLinesIndices.push_back(i+nr_celule+1);
		model->mLinesIndices.push_back(i);

		model->mLinesIndices.push_back(i + 1);
		model->mLinesIndices.push_back(i + nr_celule + 2);
		model->mLinesIndices.push_back(i + nr_celule + 2);
		model->mLinesIndices.push_back(i + nr_celule + 1);
		model->mLinesIndices.push_back(i + nr_celule + 1);
		model->mLinesIndices.push_back(i + 1);
	}

	model->nrIndici = model->mIndices.size();
	model->nrIndiciWired = model->mLinesIndices.size();

	glGenBuffers(1, &model->vboId);
	glBindBuffer(GL_ARRAY_BUFFER, model->vboId);
	glBufferData(GL_ARRAY_BUFFER, model->mVertex.size() * sizeof(Vertex), model->mVertex.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &model->iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model->nrIndici * sizeof(unsigned short), model->mIndices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glGenBuffers(1, &model->wiredIboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->wiredIboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model->nrIndiciWired * sizeof(unsigned short), model->mLinesIndices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	generated = true;
}
