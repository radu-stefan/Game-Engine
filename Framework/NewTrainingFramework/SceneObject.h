#pragma once
#include "stdafx.h"
#include "Model.h"
#include "Shader.h"
#include "Texture.h"
#include <map>
#include "../Utilities/utilities.h"

class SceneObject
{
public:
	SceneObject();
	~SceneObject();

	Vector3 position;
	Vector3 rotation;
	Vector3 scale;
	Model *model;
	Shader *shader;
	std::vector<Texture*> textures;
	bool depthTest;
	bool blend;
	bool wired;
	std::string name;

	float selfRotateSpeed;
	float shininess;
	int followingCamera;
	int lights;

	enum type {
		normal,
		surface,
		skybox,
		fire
	} type;

	virtual void Draw(ESContext *esContext);
	virtual void Update(ESContext *esContext, float deltaTime);
	void SendCommonData();
};

