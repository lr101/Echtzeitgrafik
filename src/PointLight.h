#pragma once

#include "Shader.h"

class PointLight {
	glm::vec3 lightPos;
	glm::vec3 lightCol;

public:
	PointLight(glm::vec3 lightPos, glm::vec3 lightCol);
	~PointLight();

	void setUniforms(Shader& shader);
};