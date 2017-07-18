#include "stdafx.h"
#include "FireObject.h"


FireObject::FireObject()
{
}


FireObject::~FireObject()
{
}
void FireObject::Draw(ESContext * esContext)
{
	glUseProgram(shader->progId);

	SendCommonData();

	if (shader->dispMaxUniform != -1)
		glUniform1f(shader->dispMaxUniform, (const GLfloat)dispMax);
	if (shader->timeUniform != -1)
		glUniform1f(shader->timeUniform, (const GLfloat)time);

	if (wired)
		glDrawElements(GL_LINES, model->mLinesIndices.size(), GL_UNSIGNED_SHORT, 0);
	else
		glDrawElements(GL_TRIANGLES, model->mIndices.size(), GL_UNSIGNED_SHORT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void FireObject::Update(ESContext * esContext, float deltaTime)
{
	time += deltaTime;
	float x;
	if (time >= 1)
		time = modf(time, &x);
}