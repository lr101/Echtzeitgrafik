#pragma once

#include <vector>

#include "Shader.h"
#include "GeometryBuffer.h"

class Mesh
{
public:
	Mesh(std::vector<float>& vertices, std::vector<unsigned int>& indices, glm::vec4 obj_color);
	Mesh(const Mesh& mesh);
	~Mesh() = default;

	void render(Shader& shader, const glm::mat4 mat_model) const;


private:
	std::vector<float> vertices_;
	std::vector<unsigned int> indices_;
	glm::vec4 obj_color_;
	std::unique_ptr<GeometryBuffer> buffer_;
};
