#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>

#include "Shader.h"
#include "Scene.hpp"

class MyWindow
{
	GLFWwindow* m_window_;
	bool projection_type_toggle_;
	bool cull_face_toggle_;
	glm::mat4 mat_projection_;
	Shader* shader_;
	Scene* scene_;

public:
	MyWindow(int width, int height, const char* name);
	MyWindow(const MyWindow& window);
	~MyWindow();

	void onKey(int key, int scancode, int actions, int mods);
	void onResize(int width, int height);
	GLFWwindow* getWindow() const;
	void setShader(Shader* shader);
	void setScene(Scene* scene);

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
