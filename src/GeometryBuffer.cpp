#include "GeometryBuffer.h"

GeometryBuffer::GeometryBuffer(GLfloat vertices[], const GLuint v_size, GLuint indices[], const GLuint i_size, const GLuint vertex_amount)
{
	this->use_indices_ = true;
	this->vertex_amount_ = vertex_amount;
	glGenVertexArrays(1, &m_vao_);
	glGenBuffers(1, &m_vbo_);
	glGenBuffers(1, &m_ebo_);
	bind_vao();
	bind_ebo();
	unbind_vao();
	set_vertices(vertices, v_size);
	set_indices(indices, i_size);
}

GeometryBuffer::GeometryBuffer(GLfloat vertices[], const GLuint v_size, const GLuint vertex_amount)
{
	this->use_indices_ = false;
	this->vertex_amount_ = vertex_amount;
	glGenVertexArrays(1, &m_vao_);
	glGenBuffers(1, &m_vbo_);
	bind_vao();
	bind_ebo();
	unbind_vao();
	set_vertices(vertices, v_size);
}

GeometryBuffer::GeometryBuffer(const GeometryBuffer& buffer)
{
	this->m_ebo_ = buffer.m_ebo_;
	this->m_vao_ = buffer.m_vao_;
	this->m_vbo_ = buffer.m_vbo_;
	this->vertex_amount_ = buffer.vertex_amount_;
	this->use_indices_ = buffer.use_indices_;
}

GeometryBuffer::~GeometryBuffer()
{
	glDeleteVertexArrays(1, &m_vao_);
	glDeleteBuffers(1, &m_vbo_);
	glDeleteBuffers(1, &m_ebo_);
}

void GeometryBuffer::set_vertices(GLfloat* vertices, const GLuint size) const
{
	this->bind_vao();
	this->bind_vbo();
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	this->unbind_vao();
	this->unbind_vbo();
}

void GeometryBuffer::set_indices(GLuint* indices, const GLuint size) const
{
	this->bind_vao();
	this->bind_vbo();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
	this->unbind_vao();
	this->unbind_vbo();
}

void GeometryBuffer::set_attributes(const GLuint index, const GLint size, const GLenum type, const GLsizei stride, const GLvoid* offset) const
{
	this->bind_vao();
	this->bind_vbo();
	glVertexAttribPointer(index, size, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(index);
	this->unbind_vbo();
	this->unbind_vao();
}

void GeometryBuffer::draw() const
{
	this->bind_vao();
	if (this->use_indices_)
	{
		glDrawElements(GL_TRIANGLES, this->vertex_amount_, GL_UNSIGNED_INT, nullptr);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, this->vertex_amount_);
	}
	this->unbind_vao();
}

void GeometryBuffer::bind_vao() const
{
	glBindVertexArray(m_vao_);
}

void GeometryBuffer::bind_vbo() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_);
}

void GeometryBuffer::bind_ebo() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo_);
}

void GeometryBuffer::unbind_vao() const
{
	glBindVertexArray(0);
}

void GeometryBuffer::unbind_vbo() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
