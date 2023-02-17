#include "Shader.h"

Shader::Shader(const char* vertexFileName, const char* fragmentFileName) {
	glewInit();
	this->s_vertex = glCreateShader(GL_VERTEX_SHADER);
	this->s_fragment = glCreateShader(GL_FRAGMENT_SHADER);
	compile(&this->s_vertex, load(getPath(vertexFileName).c_str()).c_str());
	compile(&this->s_fragment, load(getPath(fragmentFileName).c_str()).c_str());
	link();
	// Bind prog to the opengl context
	glUseProgram(this->s_prog);
	// Remove compiled shader objects
	glDeleteShader(this->s_vertex);
	glDeleteShader(this->s_fragment);
}

Shader::Shader(const Shader& shader) {
	this->s_fragment = shader.s_fragment;
	this->s_prog = shader.s_prog;
	this->s_vertex = shader.s_vertex;
}

Shader::~Shader() {

}

GLint Shader::getUniform(const char* name) {
	GLint location = glGetUniformLocation(this->s_prog, name);
	glUseProgram(this->s_prog);
	return location;
}

void Shader::setUniform(const char* name, GLint val)
{
	glUniform1i(getUniform(name), val);
}

void Shader::setUniform(const char* name, GLfloat val)
{
	glUniform1f(getUniform(name), val);
}

void Shader::setUniform(const char* name, glm::vec3 val)
{
	glUniform3f(getUniform(name), val.x, val.y, val.z);
}

void Shader::setUniform(const char* name, glm::vec4 val)
{
	glUniform4f(getUniform(name), val.x, val.y, val.z, val.w);
}

void Shader::setUniform(const char* name, glm::mat4 val)
{
	glUniformMatrix4fv(getUniform(name), 1, GL_FALSE, glm::value_ptr(val));
}

std::string Shader::load(const char* src) {
	try {
		// open files
		std::ifstream shaderFile;
		shaderFile.open(src);
		std::stringstream shaderStream;
		// read file's buffer contents into streams
		shaderStream << shaderFile.rdbuf();
		shaderFile.close();
		// convert stream into string
		return shaderStream.str();
	}
	catch (std::ifstream::failure& e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
	}
	return "";
}

void Shader::compile(GLuint* s, const char* s_src) {
	glShaderSource(*s, 1, &s_src, NULL);
	glCompileShader(*s);
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(*s, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(*s, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}


void Shader::link() {
	this->s_prog = glCreateProgram();
	glAttachShader(this->s_prog, this->s_vertex);
	glAttachShader(this->s_prog, this->s_fragment);
	glLinkProgram(this->s_prog);
	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(this->s_prog, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->s_prog, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
}

std::string Shader::getPath(const char* fileName) {
	try {
		return std::string(std::filesystem::current_path().generic_string()).append("/../res/").append(fileName);
	}
	catch (std::exception& e) {
		std::cout << "ERROR::SHADER::PATH COULD NOT BE BUILD: " << e.what() << std::endl;
	}
	return "";
}

