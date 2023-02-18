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
	Scene(std::string fileName, const GLfloat rot_per_frame, glm::vec3 rot_mat);

	Scene(const Scene& scene);

	void render(Shader& shader);

	void setUniforms(Shader& shader);

	~Scene();

private:
	void processMeshes(const aiScene* scene);

	void processLights(const aiScene* scene);

	void processCamera(const aiScene* scene);

	const aiScene* loadScene(std::string fileName);

	std::vector<std::unique_ptr<Mesh>> meshes;

	std::unique_ptr<Camera> camera_;

	std::unique_ptr<PointLight> light;

	GLfloat rot_amount_ = glm::radians(0.f);
	GLfloat rot_per_frame_;
	glm::vec3 rot_mat_;
	glm::mat4 mat_model_ = glm::mat4(1.f);
};
