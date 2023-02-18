#include "GeometryBuffer.h"

GeometryBuffer::GeometryBuffer(GLfloat vertices[], GLuint v_size, GLuint indices[], GLuint i_size, GLuint vertexAmount) {
	this->useIndices = true;
	this->vertexAmount = vertexAmount;
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ebo);
	bindVAO();
	bindEBO();
	unbindVAO();
	setVertices(vertices, v_size);
	setIndices(indices, i_size, vertexAmount);
}

GeometryBuffer::GeometryBuffer(GLfloat vertices[], GLuint v_size, GLuint vertexAmount) {
	this->useIndices = false;
	this->vertexAmount = vertexAmount;
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	bindVAO();
	bindEBO();
	unbindVAO();
	setVertices(vertices, v_size);
}

GeometryBuffer::GeometryBuffer(const GeometryBuffer& buffer) {
	this->m_ebo = buffer.m_ebo;
	this->m_vao = buffer.m_vao;
	this->m_vbo = buffer.m_vbo;
	this->vertexAmount = buffer.vertexAmount;
	this->useIndices = buffer.useIndices;
}

GeometryBuffer::~GeometryBuffer() {
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ebo);
}

void GeometryBuffer::setVertices(GLfloat* vertices, GLuint size) {
	bindVAO();
	bindVBO();
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	unbindVAO();
	unbindVBO();
}

void GeometryBuffer::setIndices(GLuint* indices, GLuint size, GLuint vertexAmount) {
	bindVAO();
	bindVBO();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
	unbindVAO();
	unbindVBO();
}

void GeometryBuffer::setAttributes(GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid* offset) {
	bindVAO();
	bindVBO();
	glVertexAttribPointer(index, size, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(index);
	unbindVBO();
	unbindVAO();
}

void GeometryBuffer::draw() {
	bindVAO();
	if (this->useIndices) {
		glDrawElements(GL_TRIANGLES, this->vertexAmount, GL_UNSIGNED_INT, nullptr);
	}
	else {
		glDrawArrays(GL_TRIANGLES, 0, this->vertexAmount);
	}
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
