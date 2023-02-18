#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>

#include "Shader.h"

class MyWindow
{
	GLFWwindow* m_window_;
	bool projection_type_;
	glm::mat4 mat_projection_;
	Shader* shader_;

public:
	MyWindow(int width, int height, const char* name);
	MyWindow(const MyWindow& window);
	~MyWindow();

	void onKey(int key, int scancode, int actions, int mods);
	void onResize(int width, int height);
	GLFWwindow* getWindow() const;
	void setShader(Shader* shader);

private:
	static void onKey(GLFWwindow* window, int key, int scancode, int actions, int mods)
	{
		auto obj = static_cast<MyWindow*>(glfwGetWindowUserPointer(window));
		obj->onKey(key, scancode, actions, mods);
	};

	static void onResize(GLFWwindow* window, int width, int height)
	{
		auto obj = static_cast<MyWindow*>(glfwGetWindowUserPointer(window));
		obj->onResize(width, height);
	}
};
