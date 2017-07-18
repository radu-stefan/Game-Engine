#pragma once
#include "../Utilities/utilities.h"

class Shaders 
{
public:
	GLuint program, vertexShader, fragmentShader;
	char fileVS[260];
	char fileFS[260];
	GLint positionAttribute;
	GLint colorAttribute;
	GLint uvAttribute;
	GLint normAttribute;
	GLint binormAttribute;
	GLint tgtAttribute;

	GLint rotationUniform;
	GLint MVPuniform;
	GLint textureUniform;


	int Init(char * fileVertexShader, char * fileFragmentShader);
	~Shaders();
};