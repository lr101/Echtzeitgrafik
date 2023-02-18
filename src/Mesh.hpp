#pragma once

#include <vector>

#include "Shader.h"
#include "GeometryBuffer.h"

class Mesh
{
public:

	Mesh(std::vector<float>& vertices_, std::vector<unsigned int>& indices_, const GLfloat rotPerFrame_, glm::vec3 rotationMatrix_, glm::vec4 objColor_);
	Mesh(const Mesh& mesh);
	void render(Shader& shader);

	~Mesh() = default;

private:
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	GLfloat rotAmount = glm::radians(0.f);
	GLfloat rotPerFrame;
	glm::mat4 mat_model = glm::mat4(1.0f);
	std::unique_ptr<GeometryBuffer> buffer;
	glm::vec3 rotationMatrix;
	glm::vec4 objColor;
};