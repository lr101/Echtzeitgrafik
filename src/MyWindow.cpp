#include "MyWindow.h"

MyWindow::MyWindow(const int width, const int height, const char* name)
{
	this->mat_projection_ = glm::perspective(glm::radians(45.0f), static_cast<float>(width) / static_cast<float>(height),
	                                        0.1f, 1000.0f);
	this->m_window_ = glfwCreateWindow(width, height, name, nullptr, nullptr);
	this->projection_type_toggle_ = true;
	this->shader_ = nullptr;
	this->cull_face_toggle_ = true;

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
	this->projection_type_toggle_ = window.projection_type_toggle_;
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
		if (this->projection_type_toggle_)
		{
			this->mat_projection_ = glm::ortho(-1.f * aspect, aspect, -1.f, 1.f, 0.1f, 100.f);
		}
		else
		{
			this->mat_projection_ = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 1000.0f);
		}
		this->projection_type_toggle_ = !this->projection_type_toggle_;
		this->shader_->setUniform("u_projection", mat_projection_);
	}

	if (key == GLFW_KEY_C && actions == GLFW_PRESS)
	{
		if (this->cull_face_toggle_)
		{
			glDisable(GL_CULL_FACE);
		}
		else
		{
			glEnable(GL_CULL_FACE);
		}
		this->cull_face_toggle_ = !this->cull_face_toggle_;
	}

	if ((key == GLFW_KEY_W || key == GLFW_KEY_S) && (actions == GLFW_PRESS || actions == GLFW_REPEAT))
	{
		glm::mat4 view = this->scene_->get_view();

		if (key == GLFW_KEY_W)
			view = glm::rotate(view, glm::radians(5.f), glm::vec3(0.f, 0.f, -1.f));
		if (key == GLFW_KEY_S)
			view = glm::rotate(view, glm::radians(5.f), glm::vec3(0.f, 0.f, 1.f));

		this->shader_->setUniform("u_view", view);
		this->scene_->set_view(view);
	}

	if ((key == GLFW_KEY_A || key == GLFW_KEY_D) && (actions == GLFW_PRESS || actions == GLFW_REPEAT))
	{
		GLfloat rot_amount_per_second = this->scene_->get_rot_amount_per_second();
		if (key == GLFW_KEY_A)
			rot_amount_per_second -= 10.f;
		if (key == GLFW_KEY_D)
			rot_amount_per_second += 10.f;
		this->scene_->set_rot_amount_per_second(rot_amount_per_second);
	}
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

void MyWindow::setScene(Scene* scene)
{
	this->scene_ = scene;
}

