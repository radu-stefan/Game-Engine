#pragma once
#include "SceneObject.h"

class TerrainObject :
	public SceneObject
{
public:
	TerrainObject();
	~TerrainObject();

	int nr_celule;
	float dim_celula;
	float offsetY;
	bool generated = false;
	Vector3 height;
	Vector2 pos0, pos1;
	Vector2 uv_offset;

	virtual void Draw(ESContext *esContext);
	virtual void Update(ESContext *esContext, float deltaTime);

	void Generate();
};

