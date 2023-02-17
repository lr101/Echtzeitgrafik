#pragma once

#include <vector>

#include <assimp/scene.h>
#include <glm/glm.hpp>
#include "Mesh.hpp"
#include "Shader.h"
#include "PointLight.h"
#include "Camera.h"

class Scene
{
public:

	Scene(const aiScene* scene);

	void render(Shader& shader);

	void setUniforms(Shader& shader);

	~Scene();

private:

	void processMeshes(const aiScene* scene);
	
	void processLights(const aiScene* scene);

	void processCamera(const aiScene* scene);

	std::vector<Mesh2*> meshes;

	std::unique_ptr<Camera> camera;

	std::unique_ptr<PointLight> light;
};
