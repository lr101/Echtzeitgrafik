#pragma once

#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glm/glm.hpp>
#include "Mesh.hpp"
#include "Shader.h"
#include "PointLight.h"
#include "Camera.h"
#include <filesystem>
#include "helper/RootDir.h"
#include <iostream>

class Scene
{
public:

	Scene(std::string fileName);

	void render(Shader& shader);

	void setUniforms(Shader& shader);

	~Scene();

private:

	void processMeshes(const aiScene* scene);

	void processLights(const aiScene* scene);

	void processCamera(const aiScene* scene);

	const aiScene* loadScene(std::string fileName);

	std::vector<Mesh*> meshes;

	std::unique_ptr<Camera> camera;

	std::unique_ptr<PointLight> light;
};
