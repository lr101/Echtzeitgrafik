#include "MyWindow.h"

MyWindow::MyWindow(int width, int height, const char* name) {
	this->mat_projection = glm::perspective(glm::radians(45.0f), (float) width / (float) height, 0.1f, 1000.0f);
	this->mWindow = glfwCreateWindow(width, height, name, NULL, NULL);
	this->projection_type = true;

	glfwSetWindowUserPointer(this->mWindow, this);
	glfwSetKeyCallback(this->mWindow, onKey);
	glfwSetFramebufferSizeCallback(mWindow, onResize);
	glfwMakeContextCurrent(this->mWindow);
	glViewport(0, 0, width, height);
}

MyWindow::~MyWindow() {
	glfwDestroyWindow(this->mWindow);
}

void MyWindow::onKey(int key, int scancode, int actions, int mods) {
	if (key == GLFW_KEY_ESCAPE && actions == GLFW_PRESS) {
		glfwSetWindowShouldClose(this->mWindow, GL_TRUE);
	}

	if (key == GLFW_KEY_SPACE && actions == GLFW_PRESS) {
		int width, height;
		glfwGetFramebufferSize(this->mWindow, &width, &height);
		float aspect = (float) width / (float) height;
		if (this->projection_type) {
			this->mat_projection = glm::ortho(-1.f * aspect, aspect, -1.f, 1.f, 0.1f, 100.f);
		}
		else {
			this->mat_projection = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 1000.0f);
		}
		this->projection_type = !this->projection_type;
		this->shader->setUniform("u_projection", mat_projection);
	}
}

void MyWindow::onResize(int width, int height) {
	glViewport(0, 0, width, height);
}

GLFWwindow* MyWindow::getWindow() {
	return this->mWindow;
}

void MyWindow::setShader(Shader* shader) {
	this->shader = shader;
	this->shader->setUniform("u_projection", mat_projection);
}
