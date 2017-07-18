#pragma once
#include "SceneObject.h"
class SkyBoxObject :
	public SceneObject
{
public:
	SkyBoxObject();
	~SkyBoxObject();

	void Draw(ESContext *esContext);
	void Update(ESContext *esContext, float deltaTime);
};

