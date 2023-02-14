#include "Shader.h"

Shader::Shader(const char *p_vertex, const char *p_fragment) {
	this->s_vertex = glCreateShader(GL_VERTEX_SHADER);
	this->s_fragment = glCreateShader(GL_FRAGMENT_SHADER);
	compile(&this->s_vertex, load(p_vertex).c_str());
	compile(&this->s_fragment, load(p_fragment).c_str());
	link();
	// Bind prog to the opengl context
	glUseProgram(this->s_prog);
	// Remove compiled shader objects
	glDeleteShader(this->s_vertex);
	glDeleteShader(this->s_fragment);
}

Shader::~Shader() {

}

std::string Shader::load(const char* src) {
	std::string line, text;
	std::ifstream in(src);
	while (std::getline(in, line)) {
		text += line + "\n";
	}
	return text;
}

void Shader::compile(GLuint *s, const char *s_src) {
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
	glAttachObjectARB(this->s_prog, this->s_vertex);
	glAttachObjectARB(this->s_prog, this->s_fragment);
	glLinkProgram(this->s_prog);
	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(this->s_prog, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->s_prog, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
}
