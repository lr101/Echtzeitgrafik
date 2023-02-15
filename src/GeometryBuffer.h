#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

#define GLEW_STATIC
#include <GL/glew.h> // has to be included first!
#include <GLFW/glfw3.h>
#include <assimp/Importer.hpp>
#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

class GeometryBuffer {
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ebo;
	GLuint vertexAmount;
	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;

	void setVertices(GLfloat *vertices, GLuint size);
	void setIndices(GLuint *indices, GLuint size, GLuint vertexAmount);
	void setAttributes(GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid* offset);
	void bindVAO();
	void bindVBO();
	void bindEBO();
	void unbindVAO();
	void unbindVBO();
	void unbindEBO();

public:
	GeometryBuffer(GLfloat vertices[], GLuint v_size, GLuint indices[], GLuint i_size, GLuint vertexAmount);
	~GeometryBuffer();

	void draw();
};