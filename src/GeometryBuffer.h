#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h> // has to be included first!
#include <GLFW/glfw3.h>
#include <assimp/Importer.hpp>
#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

class GeometryBuffer {
public:
    GeometryBuffer();

    ~GeometryBuffer();

    void bind();

    void unbind();

    void setVertices(GLfloat vertices[]);

    void setIndices(GLuint indices[]);

    void setAttribute(GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid* offset);

private:
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ebo;
};