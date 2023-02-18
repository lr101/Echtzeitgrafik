#pragma once

#define GLEW_STATIC
#include <glm/ext.hpp>
#include <iostream>

#include "Shader.h"

class PointLight
{
	glm::vec3 light_pos_;
	glm::vec3 light_col_;

public:
	PointLight(glm::vec3 light_pos, glm::vec3 light_col);
	PointLight(const PointLight& light);
	~PointLight() = default;

	void set_uniforms(Shader& shader) const;
	void apply_mat(Shader& shader, const glm::mat4 mat_model) const;
};
