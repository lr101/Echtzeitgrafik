#include "Shader.h"

Shader::Shader(const char* p_vertex, const char* p_fragment)
{
	glewInit();
	this->s_vertex_ = glCreateShader(GL_VERTEX_SHADER);
	this->s_fragment_ = glCreateShader(GL_FRAGMENT_SHADER);
	compile(&this->s_vertex_, load(getPath(p_vertex).c_str()).c_str());
	compile(&this->s_fragment_, load(getPath(p_fragment).c_str()).c_str());
	link();
	// Bind prog to the opengl context
	glUseProgram(this->s_prog_);
	// Remove compiled shader objects
	glDeleteShader(this->s_vertex_);
	glDeleteShader(this->s_fragment_);
}

Shader::Shader(const Shader& shader)
{
	this->s_fragment_ = shader.s_fragment_;
	this->s_prog_ = shader.s_prog_;
	this->s_vertex_ = shader.s_vertex_;
}

GLint Shader::getUniform(const char* name) const
{
	const GLint location = glGetUniformLocation(this->s_prog_, name);
	glUseProgram(this->s_prog_);
	return location;
}

void Shader::setUniform(const char* name, const GLint val)
{
	glUniform1i(getUniform(name), val);
}

void Shader::setUniform(const char* name, const GLfloat val)
{
	glUniform1f(getUniform(name), val);
}

void Shader::setUniform(const char* name, const glm::vec3 val)
{
	glUniform3f(getUniform(name), val.x, val.y, val.z);
}

void Shader::setUniform(const char* name, const glm::vec4 val)
{
	glUniform4f(getUniform(name), val.x, val.y, val.z, val.w);
}

void Shader::setUniform(const char* name, glm::mat4 val)
{
	glUniformMatrix4fv(getUniform(name), 1, GL_FALSE, value_ptr(val));
}

std::string Shader::load(const char* src)
{
	try
	{
		// open files
		std::ifstream shader_file;
		shader_file.open(src);
		std::stringstream shaderStream;
		// read file's buffer contents into streams
		shaderStream << shader_file.rdbuf();
		shader_file.close();
		// convert stream into string
		return shaderStream.str();
	}
	catch (std::ifstream::failure& e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
	}
	return "";
}

void Shader::compile(GLuint* s, const char* s_src)
{
	glShaderSource(*s, 1, &s_src, nullptr);
	glCompileShader(*s);
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(*s, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(*s, 512, nullptr, infoLog);
		std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}


void Shader::link()
{
	this->s_prog_ = glCreateProgram();
	glAttachShader(this->s_prog_, this->s_vertex_);
	glAttachShader(this->s_prog_, this->s_fragment_);
	glLinkProgram(this->s_prog_);
	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(this->s_prog_, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->s_prog_, 512, nullptr, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
}

std::string Shader::getPath(const char* file_name) const
{
	try
	{
		return std::string(std::filesystem::current_path().generic_string()).append("/../res/").append(file_name);
	}
	catch (std::exception& e)
	{
		std::cout << "ERROR::SHADER::PATH COULD NOT BE BUILD: " << e.what() << std::endl;
	}
	return "";
}
