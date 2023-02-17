#include <iostream>

#include "Mesh.hpp"

Mesh2::Mesh2(std::vector<float>& vertices_, std::vector<unsigned int>& indices_)
{
    this->indices = indices_;
	this->vertices = vertices_;
	this->buffer = new GeometryBuffer(&vertices[0], vertices.size() * sizeof(float), &indices[0], indices.size() * sizeof(float), indices.size());
	buffer->setAttributes(0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	buffer->setAttributes(1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
}

Mesh2::~Mesh2() {
	delete buffer;
}

void Mesh2::render(Shader& shader)
{
	buffer->draw();
}