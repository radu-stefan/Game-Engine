#pragma once

#include <string>
#include "../Utilities//utilities.h"
struct ModelResource {
	std::string path;
};

struct ShaderResource {
	std::string pathVS;
	std::string pathFS;
};

struct TextureResource {

	enum type
	{
		_2d,
		cube
	} type;
	std::string path;

	GLint min_filter;
	GLint mag_filter;

	GLint wrap_s;
	GLint wrap_t;
};