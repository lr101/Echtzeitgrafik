#include <iostream>

#include "Mesh.hpp"

Mesh2::Mesh2(std::vector<float>& vertices_, std::vector<unsigned int>& indices_, const GLfloat rotPerFrame_, glm::vec3 rotationMatrix_)
{
    this->indices = indices_;
	this->vertices = vertices_;
	this->rotPerFrame = rotPerFrame_;
	this->rotationMatrix = rotationMatrix_;
	this->buffer = new GeometryBuffer(&vertices[0], vertices.size() * sizeof(float), &indices[0], indices.size() * sizeof(float), indices.size());
	buffer->setAttributes(0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	buffer->setAttributes(1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
}

Mesh2::~Mesh2() {
	delete buffer;
}

void Mesh2::render(Shader& shader)
{
	// Rotate model matrix
	glm::mat4 tmp_mat_model = glm::rotate(this->mat_model, this->rotAmount, this->rotationMatrix);
	shader.setUniform("u_model", tmp_mat_model);
	rotAmount = glm::radians(this->rotPerFrame + glm::degrees(rotAmount));
	//draw vertices of mesh
	buffer->draw();
}