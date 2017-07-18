#pragma once

#include "Resource.h"

class Shader
{
public:
	ShaderResource* sr;
	GLuint progId, vertexShader, fragmentShader;

	//common uniforms
	GLint positionAttribute;
	GLint colorAttribute;
	GLint uvAttribute;
	GLint normAttribute;
	GLint binormAttribute;
	GLint tgtAttribute;
	GLint rotationUniform;
	GLint MVPuniform;
	GLint textureUniform[5];
	//terrain uniforms
	GLint uvBlendAttribute;
	GLint heightUniform;
	GLint uv_offsetUniform;
	//fog uniforms
	GLint cameraUniform;
	GLint rUniform;
	GLint RUniform;
	GLint modelUniform;
	GLint fogUniform;
	//fire uniforms
	GLint timeUniform;
	GLint dispMaxUniform;

	GLint dirDiffLight;
	GLint dirSpecLight;
	GLint dirDirection;
	GLint dirSpecCoef;

	GLint ambLight;
	GLint shininessUniform;

	GLint pointPosLight[5];
	GLint pointDiffLight[5];
	GLint pointSpecLight[5];
	GLint pointSpecCoef[5];

	int Load();
	Shader();
	~Shader();
	void freeResources();
};

