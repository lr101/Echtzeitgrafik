#pragma once

#define GLEW_STATIC
#include <GL/glew.h> // has to be included first!
#include <glm/ext.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>

class Shader
{
	GLuint s_vertex_;
	GLuint s_fragment_;
	GLuint s_prog_;

	std::string load(const char* src);
	void compile(GLuint* s, const char* s_src);
	void link();
	GLint getUniform(const char* name) const;
	std::string getPath(const char* file_name) const;

public:
	Shader(const char* p_vertex, const char* p_fragment);
	Shader(const Shader& shader);
	~Shader() = default;

	void setUniform(const char* name, GLint val);
	void setUniform(const char* name, GLfloat val);
	void setUniform(const char* name, glm::vec3 val);
	void setUniform(const char* name, glm::vec4 val);
	void setUniform(const char* name, glm::mat4 val);
};
