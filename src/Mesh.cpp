#include <iostream>

#include "Mesh.hpp"

Mesh::Mesh(std::vector<float>& vertices_, std::vector<unsigned int>& indices_, glm::vec4 objColor_)
{
	this->indices = indices_;
	this->vertices = vertices_;
	this->buffer = std::make_unique<GeometryBuffer>(&vertices[0], vertices.size() * sizeof(float), &indices[0],
	                                                indices.size() * sizeof(float), indices.size());
	this->objColor = objColor_;
	buffer->setAttributes(0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	buffer->setAttributes(1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
}

Mesh::Mesh(const Mesh& mesh)
{
	this->indices = mesh.indices;
	this->vertices = mesh.vertices;
	this->objColor = mesh.objColor;
	this->buffer = std::make_unique<GeometryBuffer>(*(mesh.buffer));
}

void Mesh::render(Shader& shader, glm::mat4 mat_model)
{
	// TODO move rotation parameter into scene to also rotate light source
	// Set mesh color
	shader.setUniform("u_objectCol", this->objColor);
	shader.setUniform("u_model", mat_model);
	//draw vertices of mesh
	buffer->draw();
}
