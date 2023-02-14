#include "GeometryBuffer.h"

GeometryBuffer::GeometryBuffer() {
        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);
        glGenBuffers(1, &m_ebo);
    }

GeometryBuffer::~GeometryBuffer() {
        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(1, &m_vbo);
        glDeleteBuffers(1, &m_ebo);
    }

void GeometryBuffer::bind() {
        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    }

void GeometryBuffer::unbind() {
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

void GeometryBuffer::setVertices(GLfloat vertices[]) {
        bind();
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        unbind();
    }

    void GeometryBuffer::setIndices(GLuint indices[]) {
        bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        unbind();
    }

    void GeometryBuffer::setAttribute(GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid* offset) {
        bind();
        glVertexAttribPointer(index, size, type, GL_FALSE, stride, offset);
        glEnableVertexAttribArray(index);
        unbind();
    }