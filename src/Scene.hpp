#pragma once

#include <vector>

#include <assimp/scene.h>
#include <glm/glm.hpp>
#include "Mesh.hpp"
#include "Shader.h"
#include "PointLight.h"

class Scene
{
public:

	Scene(const aiScene* scene);

	void render(Shader& shader);

	void setUniforms(Shader& shader);

	const glm::vec3& getCameraPos();

	//TODO destructor

private:

	void processMeshes(const aiScene* scene);
	
	void processLights(const aiScene* scene);

	std::vector<Mesh2*> meshes;

	glm::vec3 cameraPosition;

	std::unique_ptr<PointLight> light;
};
