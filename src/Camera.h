#pragma once
#include "Shader.h"

class Camera
{
	glm::vec3 cameraPostition;
	glm::vec3 lookAt;

public:
	Camera(glm::vec3 cameraPostition_, glm::vec3 lookAt_);
	Camera(const Camera& camera);
	~Camera();

	void setUniforms(Shader& shader);
};
