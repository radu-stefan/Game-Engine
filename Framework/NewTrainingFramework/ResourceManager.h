#pragma once
#include <map>
#include "Model.h"
#include "Texture.h"
#include "Shader.h"
#include "Resource.h"

class ResourceManager
{
private:
	ResourceManager();
	static ResourceManager* rmInstance;
public:
	~ResourceManager();
	void Init();
	static ResourceManager* getInstance();
	void freeResources();

	std::map<int, Model*> models;
	std::map<int, Texture*> textures;
	std::map<int, Shader*> shaders;

	std::map<int, ModelResource*> models_res;
	std::map<int, ShaderResource*> shaders_res;
	std::map<int, TextureResource*> textures_res;

	Model* loadModel(int id);
	Texture* loadTexture(int id);
	Shader* loadShader(int id);

};

