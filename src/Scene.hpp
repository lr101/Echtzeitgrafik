#pragma once

#include <vector>

#include <GL/glew.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glm/glm.hpp>
#include <glfw/glfw3.h>
#include "Mesh.hpp"
#include "Shader.h"
#include "PointLight.h"
#include "Camera.h"
#include <filesystem>
#include "helper/RootDir.h"
#include <iostream>

class Scene
{
	void process_meshes(const aiScene* scene);
	void process_lights(const aiScene* scene);
	void process_camera(const aiScene* scene);
	const aiScene* load_scene(std::string file_name) const;

	std::vector<std::unique_ptr<Mesh>> meshes_;
	std::unique_ptr<Camera> camera_;
	std::unique_ptr<PointLight> light_;
	GLfloat rot_amount_ = glm::radians(0.f);
	GLfloat rot_per_second_;
	glm::vec3 rot_mat_;
	glm::mat4 mat_model_ = glm::mat4(1.f);
	double old_time_;

public:
	Scene(std::string file_name, const GLfloat rot_per_second, glm::vec3 rot_mat);
	Scene(const Scene& scene);
	~Scene();

	void render(Shader& shader);
	void set_uniforms(Shader& shader) const;

};
