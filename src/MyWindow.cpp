#include "MyWindow.h"

MyWindow::MyWindow(const int width, const int height, const char* name)
{
	this->mat_projection_ = glm::perspective(glm::radians(45.0f), static_cast<float>(width) / static_cast<float>(height),
	                                        0.1f, 1000.0f);
	this->m_window_ = glfwCreateWindow(width, height, name, nullptr, nullptr);
	this->projection_type_ = true;
	this->shader_ = nullptr;

	glfwSetWindowUserPointer(this->m_window_, this);
	glfwSetKeyCallback(this->m_window_, onKey);
	glfwSetFramebufferSizeCallback(m_window_, onResize);
	glfwMakeContextCurrent(this->m_window_);
	glViewport(0, 0, width, height);
	glEnable(GL_CULL_FACE);
}

MyWindow::MyWindow(const MyWindow& window)
{
	this->mat_projection_ = window.mat_projection_;
	this->m_window_ = window.m_window_;
	this->projection_type_ = window.projection_type_;
	this->shader_ = window.shader_;
}

MyWindow::~MyWindow()
{
	glfwDestroyWindow(this->m_window_);
	glfwTerminate();
}

void MyWindow::onKey(int key, int scancode, int actions, int mods)
{
	if (key == GLFW_KEY_ESCAPE && actions == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(this->m_window_, GL_TRUE);
	}

	if (key == GLFW_KEY_SPACE && actions == GLFW_PRESS)
	{
		int width, height;
		glfwGetFramebufferSize(this->m_window_, &width, &height);
		const float aspect = static_cast<float>(width) / static_cast<float>(height);
		if (this->projection_type_)
		{
			this->mat_projection_ = glm::ortho(-1.f * aspect, aspect, -1.f, 1.f, 0.1f, 100.f);
		}
		else
		{
			this->mat_projection_ = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 1000.0f);
		}
		this->projection_type_ = !this->projection_type_;
		this->shader_->setUniform("u_projection", mat_projection_);
	}

	//TODO keys for toggling face culling and camera movement
}

void MyWindow::onResize(int width, int height)
{
	glViewport(0, 0, width, height);
}

GLFWwindow* MyWindow::getWindow() const
{
	return this->m_window_;
}

void MyWindow::setShader(Shader* shader)
{
	this->shader_ = shader;
	this->shader_->setUniform("u_projection", mat_projection_);
}
