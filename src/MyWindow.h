#pragma once

#define GLEW_STATIC
#include <GL/glew.h> // has to be included first!
#include <GLFW/glfw3.h>
#include <assimp/Importer.hpp>
#include <glm/ext.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "Shader.h"

class MyWindow
{
	GLFWwindow* mWindow;
	bool projection_type;
	glm::mat4 mat_projection;
	Shader* shader;

public:
	MyWindow(int width, int height, const char* name);
	MyWindow(const MyWindow& window);
	~MyWindow();

	void onKey(int key, int scancode, int actions, int mods);
	void onResize(int width, int height);
	GLFWwindow* getWindow();
	void setShader(Shader* shader);

private:
	static void onKey(GLFWwindow* window, int key, int scancode, int actions, int mods) {
		MyWindow* obj = (MyWindow*)glfwGetWindowUserPointer(window);
		obj->onKey(key, scancode, actions, mods);
	};

	static void onResize(GLFWwindow* window, int width, int height) {
		MyWindow* obj = (MyWindow*)glfwGetWindowUserPointer(window);
		obj->onResize(width, height);
	}
};

