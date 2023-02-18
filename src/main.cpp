#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <filesystem>
#include <iostream>

#include "Shader.h"
#include "Scene.hpp"
#include "MyWindow.h"


// Window dimensions
int WIDTH = 800.f, HEIGHT = 600.f;

const char* vertex_shader = "shader.vert";
const char* fragment_shader = "shader.frag";

int main()
{
	std::cout << "Keybindings:\n"
		<< "[Space]\ttoggle projection between orthographic and perspective\n"
		<< "[c]\ttoggle face culling\n"
		<< "[Escape]\tclose the window\n"
		<< "[W or S]\trotate the camera up or down\n"
		<< "[A or D]\tdecrease or increase rotation speed\n" << std::endl;

	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 8);
	glEnable(GL_MULTISAMPLE);

	// initialize window
	MyWindow m_window(WIDTH, HEIGHT, "Window");

	// build and compile shader
	Shader shader("shader.vert", "shader.frag");
	m_window.setShader(&shader);

	glewExperimental = GL_TRUE;
	glewInit();
	glEnable(GL_DEPTH_TEST);
	Scene scene("test_scenedae.sec", 10.f, glm::vec3(0.f, 1.f, 0.f));
	m_window.setScene(&scene);

	// For calculating fps
	GLdouble last_time = glfwGetTime();
	GLuint nb_frames = 0;

	scene.set_uniforms(shader);

	while (!glfwWindowShouldClose(m_window.getWindow()))
	{
		// Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		// Render
		// Clear the color buffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//render the vertices in GeometryBuffer
		scene.render(shader);

		// Swap the screen buffers
		glfwSwapBuffers(m_window.getWindow());


		// Calc fps
		const GLdouble current_time = glfwGetTime();
		nb_frames++;
		if (current_time - last_time >= 1.0)
		{
			std::cout << "fps = " << static_cast<double>(nb_frames) << std::endl;
			nb_frames = 0;
			last_time += 1.0;
		}
	}

	return 0;
}
