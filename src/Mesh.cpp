#include <iostream>

#include "Mesh.hpp"

Mesh::Mesh(std::vector<float>& vertices, std::vector<unsigned int>& indices, glm::vec4 obj_color)
{
	this->indices_ = indices;
	this->vertices_ = vertices;
	this->buffer_ = std::make_unique<GeometryBuffer>(&vertices[0], vertices.size() * sizeof(float), &indices[0],
	                                                indices.size() * sizeof(float), indices.size());
	this->obj_color_ = obj_color;
	buffer_->set_attributes(0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	buffer_->set_attributes(1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
}

Mesh::Mesh(const Mesh& mesh)
{
	this->indices_ = mesh.indices_;
	this->vertices_ = mesh.vertices_;
	this->obj_color_ = mesh.obj_color_;
	this->buffer_ = std::make_unique<GeometryBuffer>(*(mesh.buffer_));
}

void Mesh::render(Shader& shader, const glm::mat4 mat_model) const
{
	// Set mesh color
	shader.setUniform("u_objectCol", this->obj_color_);
	shader.setUniform("u_model", mat_model);
	//draw vertices_ of mesh
	buffer_->draw();
}
