#pragma once

#define GLM_FORCE_CTOR_INIT
#include <glm/glm.hpp>
#include <iostream>

#include "Shader.h"

class Camera
{
	glm::vec3 camera_position_;
	glm::mat4 view_;

public:
	Camera(glm::vec3 camera_position, glm::vec3 look_at);
	Camera(const Camera& camera);
	~Camera() = default;

	void set_uniforms(Shader& shader) const;
	glm::mat4 get_view() const;
	void set_view(const glm::mat4 view);
};
