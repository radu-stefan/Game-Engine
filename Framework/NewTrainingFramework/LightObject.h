#pragma once
#include "Shader.h"
#include "Texture.h"
#include <map>
#include "../Utilities/utilities.h"

class LightObject
{
public:
	LightObject();
	~LightObject();

	float specCoef;

	Vector3 diffuseColor;
	Vector3 specularColor;

	Vector3 direction;
	Vector3 position;
	Vector3 rotation;

	std::string name;

	enum type {
		directional,
		spot,
		point
	} type;

	void Update(ESContext *esContext, float deltaTime);
};

