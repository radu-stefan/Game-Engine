#pragma once
#include "SceneObject.h"
class FireObject :
	public SceneObject
{
public:

	float time;
	float dispMax;

	FireObject();
	~FireObject();
	void Draw(ESContext * esContext);
	void Update(ESContext * esContext, float deltaTime);
};

