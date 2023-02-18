#pragma once

#define GLEW_STATIC
#include <GL/glew.h> // has to be included first!

class GeometryBuffer
{
	GLuint m_vao_;
	GLuint m_vbo_;
	GLuint m_ebo_;
	GLuint vertex_amount_;
	GLboolean use_indices_;

	void set_vertices(GLfloat* vertices, const GLuint size) const;
	void set_indices(GLuint* indices, const GLuint size) const;
	void bind_vao() const;
	void bind_vbo() const;
	void bind_ebo() const;
	void unbind_vao() const;
	void unbind_vbo() const;

public:
	GeometryBuffer(GLfloat vertices[], const GLuint v_size, GLuint indices[], const GLuint i_size, const GLuint vertex_amount);
	GeometryBuffer(GLfloat vertices[], const GLuint v_size, const GLuint vertex_amount);
	GeometryBuffer(const GeometryBuffer& buffer);
	~GeometryBuffer();

	void draw() const;
	void set_attributes(const GLuint index, const GLint size, const GLenum type, const GLsizei stride, const GLvoid* offset) const;
};
