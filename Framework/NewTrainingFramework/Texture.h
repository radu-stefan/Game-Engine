#pragma once

#include "Resource.h"

class Texture
{
public:
	TextureResource* tr;
	GLuint texId;

	int Load();
	Texture();
	~Texture();
};

