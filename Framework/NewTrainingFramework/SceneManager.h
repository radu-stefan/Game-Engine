#pragma once

#include "stdafx.h"
#include "SceneObject.h"
#include "Camera.h"
#include <map>
#include <vector>
#include "LightObject.h"
#include "../Utilities/utilities.h"


class SceneManager
{
private:
	SceneManager();
	static SceneManager* smInstance;
public:
	static SceneManager* getInstance();
	void freeResources();
	~SceneManager();

	void Init();
	void Draw (ESContext *esContext);
	void Update(ESContext *esContext, float deltaTime);
	Camera* GetActiveCamera();

	std::map<int,SceneObject*> objects;
	std::map<int, Camera*> cameras;
	std::vector<LightObject*> light;
	int activeCamera;

	Vector3 fog_color;
	Vector3 backgroundColor;
	Vector3 ambientalColor;

	float fog_start;
	float fog_end;

	struct {
		Vector3 objAxes_OXColor;
		Vector3 objAxes_OYColor;
		Vector3 objAxes_OZColor;

		Vector3 camAxes_OXColor;
		Vector3 camAxes_OYColor;
		Vector3 camAxes_OZColor;
	} debugSettings;
};

