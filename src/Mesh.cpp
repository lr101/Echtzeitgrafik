#include <iostream>

#include "Mesh.hpp"

Mesh::Mesh(std::vector<float>& vertices_, std::vector<unsigned int>& indices_, const GLfloat rotPerFrame_, glm::vec3 rotationMatrix_)
{
	this->indices = indices_;
	this->vertices = vertices_;
	this->rotPerFrame = rotPerFrame_;
	this->rotationMatrix = rotationMatrix_;
	this->buffer = std::make_unique<GeometryBuffer>(&vertices[0], vertices.size() * sizeof(float), &indices[0], indices.size() * sizeof(float), indices.size());
	buffer->setAttributes(0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	buffer->setAttributes(1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
}

Mesh::Mesh(const Mesh& mesh) {
	this->indices = mesh.indices;
	this->vertices = mesh.vertices;
	this->rotPerFrame = mesh.rotPerFrame;
	this->rotationMatrix = mesh.rotationMatrix;
	this->buffer = std::make_unique<GeometryBuffer>(*(mesh.buffer));
}

Mesh::~Mesh() {}

void Mesh::render(Shader& shader)
{
	// Rotate model matrix
	glm::mat4 tmp_mat_model = glm::rotate(this->mat_model, this->rotAmount, this->rotationMatrix);
	shader.setUniform("u_model", tmp_mat_model);
	rotAmount = glm::radians(this->rotPerFrame + glm::degrees(rotAmount));
	//draw vertices of mesh
	buffer->draw();
}