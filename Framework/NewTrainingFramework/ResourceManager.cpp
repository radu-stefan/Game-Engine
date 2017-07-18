#pragma once
#include "stdafx.h"
#include "rapidxml-1.13/rapidxml.hpp"
#include "ResourceManager.h"


using namespace rapidxml;

ResourceManager* ResourceManager::rmInstance = nullptr;

ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{

}

void ResourceManager::Init()
{

	xml_document<> doc;
	std::ifstream file("resourceManager.xml");
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);

	xml_node<> *resourceManager = doc.first_node();

	xml_node<> *models = resourceManager->first_node("models");
	for (xml_node<> *model = models->first_node("model"); model; model = model->next_sibling())
	{
		ModelResource *m = new ModelResource();

		m->path = std::string(model->first_node("path")->value());

		models_res.insert(std::pair<int, ModelResource*>(atoi(model->first_attribute()->value()), m));
	}

	xml_node<> *textures = resourceManager->first_node("textures");
	for (xml_node<> *texture = textures->first_node("texture"); texture; texture = texture->next_sibling())
	{
		TextureResource *t = new TextureResource();

		if (std::string(texture->first_attribute("type")->value()) == "2d") {
			t->type = t->_2d;
		} else if (std::string(texture->first_attribute("type")->value()) == "cube") {
			t->type = t->cube;
		}

		t->path = std::string(texture->first_node("path")->value());

		if (std::string(texture->first_node("min_filter")->value()) == "LINEAR") {
			t->min_filter = GL_LINEAR;
		} else if (std::string(texture->first_node("min_filter")->value()) == "NEAREST") {
			t->min_filter = GL_NEAREST;
		}

		if (std::string(texture->first_node("mag_filter")->value()) == "LINEAR") {
			t->mag_filter = GL_LINEAR;
		} else if (std::string(texture->first_node("mag_filter")->value()) == "NEAREST") {
			t->mag_filter = GL_NEAREST;
		}

		if (std::string(texture->first_node("wrap_s")->value()) == "CLAMP_TO_EDGE") {
			t->wrap_s = GL_CLAMP_TO_EDGE;
		} else if (std::string(texture->first_node("wrap_s")->value()) == "REPEAT") {
			t->wrap_s = GL_REPEAT;
		} else if (std::string(texture->first_node("wrap_s")->value()) == "MIRRORED_REPEAT") {
			t->wrap_s = GL_MIRRORED_REPEAT;
		}

		if (std::string(texture->first_node("wrap_t")->value()) == "CLAMP_TO_EDGE") {
			t->wrap_t = GL_CLAMP_TO_EDGE;
		} else if (std::string(texture->first_node("wrap_t")->value()) == "REPEAT") {
			t->wrap_t = GL_REPEAT;
		} else if (std::string(texture->first_node("wrap_t")->value()) == "MIRRORED_REPEAT") {
			t->wrap_t = GL_MIRRORED_REPEAT;
		}

		textures_res.insert(std::pair<int, TextureResource*>(atoi(texture->first_attribute("id")->value()), t));
	}

	xml_node<> *shaders = resourceManager->first_node("shaders");
	for (xml_node<> *shader = shaders->first_node("shader"); shader; shader = shader->next_sibling())
	{
		ShaderResource *s = new ShaderResource();

		s->pathVS = std::string(shader->first_node("vs")->value());
		s->pathFS = std::string(shader->first_node("fs")->value());

		shaders_res.insert(std::pair<int, ShaderResource*>(atoi(shader->first_attribute()->value()), s));
	}
}

ResourceManager * ResourceManager::getInstance()
{
	if (!rmInstance) {
		rmInstance = new ResourceManager();
	}
	return rmInstance;
}

void ResourceManager::freeResources()
{

	for (std::map<int, ModelResource*>::iterator it = models_res.begin(); it != models_res.end(); it++) {
		delete it->second;
	}

	for (std::map<int, ShaderResource*>::iterator it = shaders_res.begin(); it != shaders_res.end(); it++) {
		delete it->second;
	}
	for (std::map<int, TextureResource*>::iterator it = textures_res.begin(); it != textures_res.end(); it++) {
		delete it->second;
	}

	for (std::map<int, Model*>::iterator it = models.begin(); it != models.end(); it++) {
		delete it->second;
	}
	for (std::map<int, Shader*>::iterator it = shaders.begin(); it != shaders.end(); it++) {
		delete it->second;
	}
	for (std::map<int, Texture*>::iterator it = textures.begin(); it != textures.end(); it++) {
		delete it->second;
	}

	delete rmInstance;
}

Model * ResourceManager::loadModel(int id)
{
	std::map<int, Model*>::iterator it1;

	it1 = models.find(id);
	if (it1 != models.end()) {
		return it1->second;
	}
	std::map<int, ModelResource*>::iterator it2;

	it2 = models_res.find(id);

	if (it2 != models_res.end()) {

		Model *m = new Model();
		m->mr = it2->second;
		m->Load();
		models.insert(std::pair<int, Model*>(id, m));
		return m;
	}

	return nullptr;
}

Texture * ResourceManager::loadTexture(int id)
{
	std::map<int, Texture*>::iterator it1;

	it1 = textures.find(id);
	if (it1 != textures.end()) {
		return it1->second;
	}
	std::map<int, TextureResource*>::iterator it2;

	it2 = textures_res.find(id);

	if (it2 != textures_res.end()) {

		Texture *t = new Texture();
		t->tr = it2->second;
		t->Load();
		textures.insert(std::pair<int, Texture*>(id, t));
		return t;
	}

	return nullptr;
}

Shader * ResourceManager::loadShader(int id)
{
	std::map<int, Shader*>::iterator it1;

	it1 = shaders.find(id);
	if (it1 != shaders.end()) {
		return it1->second;
	}
	std::map<int, ShaderResource*>::iterator it2;

	it2 = shaders_res.find(id);

	if (it2 != shaders_res.end()) {

		Shader *s = new Shader();
		s->sr = it2->second;
		s->Load();
		shaders.insert(std::pair<int, Shader*>(id, s));
		return s;
	}
	return nullptr;
}
