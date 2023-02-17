#pragma once
#include "Shader.h"

class Camera {
	glm::vec3 cameraPostition;
	glm::vec3 lookAt;
	float orthographicWidth;

public:
	Camera(glm::vec3 cameraPostition_, glm::vec3 lookAt_, float orthographicWidth_);
	~Camera();

	void setUniforms(Shader& shader);
};