#include "stdafx.h"
#include "rapidxml-1.13/rapidxml.hpp"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "SkyBoxObject.h"
#include "TerrainObject.h"
#include "FireObject.h"

using namespace rapidxml;

SceneManager* SceneManager::smInstance = nullptr;


SceneManager::SceneManager()
{
}


void SceneManager::Init()
{
	xml_document<> doc;
	std::ifstream file("sceneManager.xml");
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);

	xml_node<> *sceneManager = doc.first_node();
	xml_node<> *node = sceneManager->first_node("cameras");
	for (xml_node<> *camera = node->first_node("camera"); camera; camera = camera->next_sibling("camera"))
	{
		Camera *cam = new Camera();

		node = camera->first_node("position");
		cam->position.x = atof((node->first_node("x"))->value());
		cam->position.y = atof((node->first_node("y"))->value());
		cam->position.z = atof((node->first_node("z"))->value());

		node = camera->first_node("target");
		cam->target.x = atof((node->first_node("x"))->value());
		cam->target.y = atof((node->first_node("y"))->value());
		cam->target.z = atof((node->first_node("z"))->value());

		node = camera->first_node("up");
		cam->up.x = atof((node->first_node("x"))->value());
		cam->up.y = atof((node->first_node("y"))->value());
		cam->up.z = atof((node->first_node("z"))->value());

		cam->moveSpeed = atof(camera->first_node("translationSpeed")->value());
		cam->rotateSpeed = atof(camera->first_node("rotationSpeed")->value());
		cam->fov = atof(camera->first_node("fov")->value());
		cam->nearPlane = atof(camera->first_node("near")->value());
		cam->farPlane = atof(camera->first_node("far")->value());

		cameras.insert(std::pair<int, Camera*>(atoi(camera->first_attribute()->value()), cam));
	}
	
	activeCamera = atoi(sceneManager->first_node("activeCamera")->value());

	node = sceneManager->first_node("lights");
	ambientalColor.x = atof(node->first_node("ambientalColor")->first_node("r")->value());
	ambientalColor.y = atof(node->first_node("ambientalColor")->first_node("g")->value());
	ambientalColor.z = atof(node->first_node("ambientalColor")->first_node("b")->value());

	for (xml_node<> *object = node->first_node("light"); object; object = object->next_sibling("light"))
	{
		LightObject *light = new LightObject;

		if (std::string(object->first_node("type")->value()) == "directional") {
			light->type = light->directional;
		} else if (std::string(object->first_node("type")->value()) == "point") {
			light->type = light->point;
		}
		else if (std::string(object->first_node("type")->value()) == "spot") {
			light->type = light->spot;
		}

		if (object->first_node("direction")) {
			node = object->first_node("direction");
			light->direction.x = atof((node->first_node("x"))->value());
			light->direction.y = atof((node->first_node("y"))->value());
			light->direction.z = atof((node->first_node("z"))->value());
		}

		if (object->first_node("position")) {
			node = object->first_node("position");
			light->position.x = atof((node->first_node("x"))->value());
			light->position.y = atof((node->first_node("y"))->value());
			light->position.z = atof((node->first_node("z"))->value());
		}
		if (object->first_node("diffuseColor")) {
			node = object->first_node("diffuseColor");
			light->diffuseColor.x = atof((node->first_node("r"))->value());
			light->diffuseColor.y = atof((node->first_node("g"))->value());
			light->diffuseColor.z = atof((node->first_node("b"))->value());
		}
		if (object->first_node("specularColor")) {
			node = object->first_node("specularColor");
			light->specularColor.x = atof((node->first_node("r"))->value());
			light->specularColor.y = atof((node->first_node("g"))->value());
			light->specularColor.z = atof((node->first_node("b"))->value());
		}
		if (object->first_node("specCoef")) {
			light->specCoef = atof(object->first_node("specCoef")->value());
		}

		SceneManager::light.push_back(light);
	}
	node = sceneManager->first_node("objects");
	for (xml_node<> *object = node->first_node("object"); object; object = object->next_sibling("object"))
	{
		SceneObject *obj;
		if (std::string(object->first_node("type")->value()) == "normal") {

			obj = new SceneObject();
			obj->type = obj->normal;

			obj->selfRotateSpeed = atof(object->first_node("selfRotateSpeed")->value());
		}
		else if (std::string(object->first_node("type")->value()) == "skybox") {

			SkyBoxObject *sky = new SkyBoxObject();

			sky->type = sky->skybox;

			obj = (SceneObject*)sky;
		}
		else if (std::string(object->first_node("type")->value()) == "surface") {
			//continue;
			TerrainObject *terrain = new TerrainObject();

			terrain->type = terrain->surface;

			terrain->nr_celule = atof((object->first_node("nr_celule"))->value());
			terrain->dim_celula = atof((object->first_node("dim_celula"))->value());
			terrain->offsetY = atof((object->first_node("offsetY"))->value());
			terrain->height.x = atof((object->first_node("height")->first_node("r"))->value());
			terrain->height.y = atof((object->first_node("height")->first_node("g"))->value());
			terrain->height.z = atof((object->first_node("height")->first_node("b"))->value());

			terrain->position.x = SceneManager::getInstance()->GetActiveCamera()->position.x;
			terrain->position.z = SceneManager::getInstance()->GetActiveCamera()->position.z;
			terrain->position.y = terrain->offsetY;

			terrain->pos0.x = terrain->position.x;
			terrain->pos0.y = terrain->position.z;

			terrain->Generate();
			
			obj = (SceneObject*)terrain;
		}
		else if (std::string(object->first_node("type")->value()) == "fire") {

			FireObject *fire = new FireObject();

			fire->type = fire->fire;

			fire->dispMax = atof((object->first_node("dispMax"))->value());
			fire->time = 0;

			obj = (SceneObject*)fire;
		}

		if(std::string(object->first_node("model")->value()) != "generated" )
			obj->model = ResourceManager::getInstance()->loadModel(atoi(object->first_node("model")->value()));
		obj->shader = ResourceManager::getInstance()->loadShader(atoi(object->first_node("shader")->value()));
		for (node = object->first_node("textures")->first_node("texture"); node; node = node->next_sibling()) {
			int id = atoi(node->first_attribute()->value());
			obj->textures.push_back(ResourceManager::getInstance()->loadTexture(id));
		}

		if (object->first_node("wired"))
			obj->wired = true;
		else
			obj->wired = false;

		if (std::string(object->first_node("depthTest")->value()) == "true")
			obj->depthTest = true;
		else
			obj->depthTest = false;

		if (std::string(object->first_node("blend")->value()) == "true")
			obj->blend = true;
		else
			obj->blend = false;

		obj->name = std::string(object->first_node("name")->value());

		if (object->first_node("position")) {
			node = object->first_node("position");
			obj->position.x = atof((node->first_node("x"))->value());
			obj->position.y = atof((node->first_node("y"))->value());
			obj->position.z = atof((node->first_node("z"))->value());
		}
		if (object->first_node("rotation")) {
			node = object->first_node("rotation");
			obj->rotation.x = atof((node->first_node("x"))->value());
			obj->rotation.y = atof((node->first_node("y"))->value());
			obj->rotation.z = atof((node->first_node("z"))->value());
		}
		if (object->first_node("scale")) {
			node = object->first_node("scale");
			obj->scale.x = atof((node->first_node("x"))->value());
			obj->scale.y = atof((node->first_node("y"))->value());
			obj->scale.z = atof((node->first_node("z"))->value());
		}

		if (object->first_node("shininess")) {
			obj->shininess = atof(object->first_node("shininess")->value());
		}

		objects.insert(std::pair<int, SceneObject*>(atoi(object->first_attribute()->value()), obj));
	}

	node = sceneManager->first_node("fog");
	fog_color.x = atof(node->first_node("r")->value());
	fog_color.y = atof(node->first_node("g")->value());
	fog_color.z = atof(node->first_node("b")->value());
	fog_start = atof(node->first_node("start")->value());
	fog_end = atof(node->first_node("end")->value());

	node = sceneManager->first_node("backgroundColor");
	backgroundColor.x = atof((node->first_node("r"))->value());
	backgroundColor.y = atof((node->first_node("g"))->value());
	backgroundColor.z = atof((node->first_node("b"))->value());
	
	node = sceneManager->first_node("debugSettings")->first_node("objectAxes")->first_node("OXColor");
	debugSettings.objAxes_OXColor.x = atof(node->first_node("r")->value());
	debugSettings.objAxes_OXColor.y = atof(node->first_node("g")->value());
	debugSettings.objAxes_OXColor.z = atof(node->first_node("b")->value());
	node = sceneManager->first_node("debugSettings")->first_node("objectAxes")->first_node("OYColor");
	debugSettings.objAxes_OYColor.x = atof(node->first_node("r")->value());
	debugSettings.objAxes_OYColor.y = atof(node->first_node("g")->value());
	debugSettings.objAxes_OYColor.z = atof(node->first_node("b")->value());
	node = sceneManager->first_node("debugSettings")->first_node("objectAxes")->first_node("OZColor");
	debugSettings.objAxes_OZColor.x = atof(node->first_node("r")->value());
	debugSettings.objAxes_OZColor.y = atof(node->first_node("g")->value());
	debugSettings.objAxes_OZColor.z = atof(node->first_node("b")->value());

	node = sceneManager->first_node("debugSettings")->first_node("camAxes")->first_node("OXColor");
	debugSettings.camAxes_OXColor.x = atof(node->first_node("r")->value());
	debugSettings.camAxes_OXColor.y = atof(node->first_node("g")->value());
	debugSettings.camAxes_OXColor.z = atof(node->first_node("b")->value());
	node = sceneManager->first_node("debugSettings")->first_node("camAxes")->first_node("OYColor");
	debugSettings.camAxes_OYColor.x = atof(node->first_node("r")->value());
	debugSettings.camAxes_OYColor.y = atof(node->first_node("g")->value());
	debugSettings.camAxes_OYColor.z = atof(node->first_node("b")->value());
	node = sceneManager->first_node("debugSettings")->first_node("camAxes")->first_node("OZColor");
	debugSettings.camAxes_OZColor.x = atof(node->first_node("r")->value());
	debugSettings.camAxes_OZColor.y = atof(node->first_node("g")->value());
	debugSettings.camAxes_OZColor.z = atof(node->first_node("b")->value());

	glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 0.0f);
}

SceneManager * SceneManager::getInstance()
{
	if (!smInstance) {
		smInstance = new SceneManager();
	}
	return smInstance;
}

void SceneManager::freeResources()
{
	for (std::map<int, Camera*>::iterator it = cameras.begin(); it != cameras.end(); it++)
		delete it->second;
	for (std::map<int, SceneObject*>::iterator it = objects.begin(); it != objects.end(); it++) {
		if (it->second->model) {
			glDeleteBuffers(1, &it->second->model->vboId);
			glDeleteBuffers(1, &it->second->model->iboId);
			glDeleteBuffers(1, &it->second->model->wiredIboId);
		}
		for( int i = 0 ; i < it->second->textures.size() ; i++ )
			glDeleteBuffers(1, &it->second->textures[i]->texId);
		delete it->second;
	}
	for (std::vector<LightObject*>::iterator it = light.begin(); it != light.end(); it++) {
		delete *it;
	}
	delete smInstance;
}

SceneManager::~SceneManager()
{
}

void SceneManager::Draw(ESContext * esContext)
{
	for (std::map<int, SceneObject*>::iterator it = objects.begin(); it != objects.end(); it++) {
		it->second->Draw(esContext);
	}
}

void SceneManager::Update(ESContext * esContext, float deltaTime)
{
	Camera::deltaTime = deltaTime;
	for (std::map<int, Camera*>::iterator it = cameras.begin(); it != cameras.end(); it++) {
		it->second->updateWV();
	}
	POINT pct;
	GetCursorPos(&pct);//coord pe ecran
	ScreenToClient(esContext->hWnd, &pct);
	//sau 0x80 pt 32b
	if ((GetKeyState(VK_LBUTTON) & 0x100) != 0) {
		if (esContext->width / 2 > pct.x) {
			//printf("left\n");
		}
		if (esContext->width / 2 <= pct.x) {
			//printf("right\n");
		}
	}

	for (std::map<int, SceneObject*>::iterator it = objects.begin(); it != objects.end(); it++) {
		it->second->Update(esContext, deltaTime);
	}
}

Camera * SceneManager::GetActiveCamera()
{
	return cameras.at(activeCamera);
}
