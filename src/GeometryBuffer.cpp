#include "GeometryBuffer.h"

GeometryBuffer::GeometryBuffer(GLfloat vertices[], GLuint v_size, GLuint indices[], GLuint i_size, GLuint vertexAmount) {
	this->useIndices = true;
	this->vertexAmount = vertexAmount;
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ebo);
	setVertices(vertices, v_size);
	setIndices(indices, i_size, vertexAmount);
}

GeometryBuffer::GeometryBuffer(GLfloat vertices[], GLuint v_size, GLuint vertexAmount) {
	this->useIndices = false;
	this->vertexAmount = vertexAmount;
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	setVertices(vertices, v_size);
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
	bindEBO();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
	unbindEBO();
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
		bindEBO();
		glDrawElements(GL_TRIANGLES, this->vertexAmount, GL_UNSIGNED_INT, nullptr);
		unbindEBO();
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

void GeometryBuffer::unbindEBO() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}