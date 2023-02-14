#include "GeometryBuffer.h"

GeometryBuffer::GeometryBuffer(GLfloat vertices[], GLuint v_size, GLuint indices[], GLuint i_size, GLuint vertexAmount) {
	this->vertexAmount = vertexAmount;
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ebo);
	bindVAO();
	bindVBO();
	bindEBO();
	setVertices(vertices, v_size);
	setIndices(indices, i_size);
	setAttributes(0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	unbindVBO();
	unbindVAO();
	unbindEBO();
}

GeometryBuffer::~GeometryBuffer() {
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ebo);
}

void GeometryBuffer::setVertices(GLfloat vertices[], GLuint size) {
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void GeometryBuffer::setIndices(GLuint indices[], GLuint size) {
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void GeometryBuffer::setAttributes(GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid* offset) {
	glVertexAttribPointer(index, size, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(index);
}

void GeometryBuffer::draw() {
	bindVAO();
	glDrawElements(GL_TRIANGLES, this->vertexAmount, GL_UNSIGNED_INT, nullptr);
	unbindVAO();
}

void GeometryBuffer::bindVAO() {
	glBindVertexArray(m_vao);
}

void GeometryBuffer::bindVBO() {
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
}

void GeometryBuffer::bindEBO() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
}

void GeometryBuffer::unbindVAO() {
	glBindVertexArray(0);
}

void GeometryBuffer::unbindVBO() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GeometryBuffer::unbindEBO() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}