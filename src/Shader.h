#pragma once

#define GLEW_STATIC
#include <GL/glew.h> // has to be included first!
#include <GLFW/glfw3.h>
#include <assimp/Importer.hpp>
#include <glm/ext.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <iostream>
#include <fstream>

#include "helper/RootDir.h"

class Shader {
	GLuint s_vertex;
	GLuint s_fragment;
	GLuint s_prog;

	std::string load(const char* src);
	void compile(GLuint *s, const char *s_src);
	void link();
	GLint getUniform(const char* name);

public:
	Shader(const char *p_vertex, const char *p_fragment);
	~Shader();

	void setUniform(const char* name, GLint val);
	void setUniform(const char* name, GLfloat val);
	void setUniform(const char* name, glm::vec3 val);
	void setUniform(const char* name, glm::vec4 val);
	void setUniform(const char* name, glm::mat4 val);

};
