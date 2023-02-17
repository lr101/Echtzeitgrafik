#pragma once
#include "Shader.h"

class Camera {
	glm::vec3 cameraPostition;

public:
	Camera(glm::vec3 cameraPostition);
	~Camera();

	void setUniforms(Shader& shader);
};