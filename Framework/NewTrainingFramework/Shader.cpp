#include "stdafx.h"
#include "Shader.h"


int Shader::Load()
{
	char* c = new char[sr->pathVS.length() + 1];
	strcpy(c, sr->pathVS.c_str());
	vertexShader = esLoadShader(GL_VERTEX_SHADER, c);
	delete[] c;


	if (vertexShader == 0)
		return -1;

	c = new char[sr->pathFS.length() + 1];
	strcpy(c, sr->pathFS.c_str());
	fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, c);
	delete[] c;

	if (fragmentShader == 0)
	{
		glDeleteShader(vertexShader);
		return -2;
	}

	progId = esLoadProgram(vertexShader, fragmentShader);

	//finding location of uniforms / attributes
	positionAttribute = glGetAttribLocation(progId, "a_posL");
	colorAttribute = glGetAttribLocation(progId, "a_color");
	normAttribute = glGetAttribLocation(progId, "a_norm");
	binormAttribute = glGetAttribLocation(progId, "a_binorm");
	tgtAttribute = glGetAttribLocation(progId, "a_tgt");
	uvAttribute = glGetAttribLocation(progId, "a_uv");
	uvBlendAttribute = glGetAttribLocation(progId, "a_uv_blend");
	
	heightUniform = glGetUniformLocation(progId, "u_height");
	MVPuniform = glGetUniformLocation(progId, "MVP");
	uv_offsetUniform = glGetUniformLocation(progId, "u_uv_offset");
	cameraUniform = glGetUniformLocation(progId, "u_camera");
	rUniform = glGetUniformLocation(progId, "u_r");
	RUniform = glGetUniformLocation(progId, "u_R");
	modelUniform = glGetUniformLocation(progId, "u_model");
	fogUniform = glGetUniformLocation(progId, "u_fog");
	timeUniform = glGetUniformLocation(progId, "u_Time");
	dispMaxUniform = glGetUniformLocation(progId, "u_dispMax");

	textureUniform[0] = glGetUniformLocation(progId, "u_texture0");
	textureUniform[1] = glGetUniformLocation(progId, "u_texture1");
	textureUniform[2] = glGetUniformLocation(progId, "u_texture2");
	textureUniform[3] = glGetUniformLocation(progId, "u_texture3");
	textureUniform[4] = glGetUniformLocation(progId, "u_texture4");

	shininessUniform = glGetUniformLocation(progId, "u_shininess");

	dirDiffLight = glGetUniformLocation(progId, "u_dirLight.diffuse");
	dirDirection = glGetUniformLocation(progId, "u_dirLight.direction");
	dirSpecLight = glGetUniformLocation(progId, "u_dirLight.specular");
	dirSpecLight = glGetUniformLocation(progId, "u_dirLight.specular");
	dirSpecCoef = glGetUniformLocation(progId, "u_dirLight.specCoef");


	pointPosLight[0] = glGetUniformLocation(progId, "u_pointLight[0].position");
	pointDiffLight[0] = glGetUniformLocation(progId, "u_pointLight[0].diffuse");
	pointSpecLight[0] = glGetUniformLocation(progId, "u_pointLight[0].specular");
	pointSpecCoef[0] = glGetUniformLocation(progId, "u_pointLight[0].specCoef");

	pointPosLight[1] = glGetUniformLocation(progId, "u_pointLight[1].position");
	pointDiffLight[1] = glGetUniformLocation(progId, "u_pointLight[1].diffuse");
	pointSpecLight[1] = glGetUniformLocation(progId, "u_pointLight[1].specular");
	pointSpecCoef[1] = glGetUniformLocation(progId, "u_pointLight[1].specCoef");

	pointPosLight[2] = glGetUniformLocation(progId, "u_pointLight[2].position");
	pointDiffLight[2] = glGetUniformLocation(progId, "u_pointLight[2].diffuse");
	pointSpecLight[2] = glGetUniformLocation(progId, "u_pointLight[2].specular");
	pointSpecCoef[2] = glGetUniformLocation(progId, "u_pointLight[2].specCoef");

	pointPosLight[3] = glGetUniformLocation(progId, "u_pointLight[3].position");
	pointDiffLight[3] = glGetUniformLocation(progId, "u_pointLight[3].diffuse");
	pointSpecLight[3] = glGetUniformLocation(progId, "u_pointLight[3].specular");
	pointSpecCoef[3] = glGetUniformLocation(progId, "u_pointLight[3].specCoef");

	pointPosLight[4] = glGetUniformLocation(progId, "u_pointLight[4].position");
	pointDiffLight[4] = glGetUniformLocation(progId, "u_pointLight[4].diffuse");
	pointSpecLight[4] = glGetUniformLocation(progId, "u_pointLight[4].specular");
	pointSpecCoef[4] = glGetUniformLocation(progId, "u_pointLight[4].specCoef");

	ambLight = glGetUniformLocation(progId, "u_ambient");

	return 0;
}

Shader::Shader()
{
}


Shader::~Shader()
{
}

void Shader::freeResources()
{
	glDeleteProgram(progId);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}
