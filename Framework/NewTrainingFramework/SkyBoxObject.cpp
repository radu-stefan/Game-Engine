#include "stdafx.h"
#include "SkyBoxObject.h"
#include "SceneManager.h"


SkyBoxObject::SkyBoxObject()
{
}

SkyBoxObject::~SkyBoxObject()
{
}

void SkyBoxObject::Draw(ESContext * esContext)
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

void SkyBoxObject::Update(ESContext * esContext, float deltaTime)
{
	position.x = SceneManager::getInstance()->GetActiveCamera()->position.x;
	position.z = SceneManager::getInstance()->GetActiveCamera()->position.z;
}
