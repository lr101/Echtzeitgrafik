

#define GLEW_STATIC

#include <GL/glew.h> // has to be included first!
#include <GLFW/glfw3.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ft2build.h>
#include <filesystem>
#include "helper/RootDir.h"
#include FT_FREETYPE_H

#include "GeometryBuffer.h"
#include "Shader.h"
#include "Scene.hpp"
#include "MyWindow.h"
#include <iostream>


// Window dimensions
int WIDTH = 800.f, HEIGHT = 600.f;

const char* vertexShader = "shader.vert";
const char* fragmentShader = "shader.frag";

int main() {
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
	MyWindow mWindow(WIDTH, HEIGHT, "Window");

	// build and compile shaders
	Shader shader("shader.vert", "shader.frag");

	// Create model, view and projection matrices for the shader
	glm::mat4 mat_model = glm::mat4(1.0f);

	mat_model = glm::scale(mat_model, glm::vec3(1.5f, 1.5f, 1.5f));

	shader.setUniform("u_model", mat_model);

	mWindow.setShader(&shader);

	glewExperimental = GL_TRUE;
	glewInit();
	glEnable(GL_DEPTH_TEST);
	Scene scene = Scene("test_scenedae.sec");

	// For calculating fps
	GLdouble lastTime = glfwGetTime();
	GLuint nbFrames = 0;

	scene.setUniforms(shader);

	while (!glfwWindowShouldClose(mWindow.getWindow())) {
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		// Render
		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//render the vertices in GeometryBuffer
		scene.render(shader);

		// Swap the screen buffers
		glfwSwapBuffers(mWindow.getWindow());


		// Calc fps
		GLdouble currentTime = glfwGetTime();
		nbFrames++;
		if (currentTime - lastTime >= 1.0) {
			std::cout << "fps = " << double(nbFrames) << std::endl;
			nbFrames = 0;
			lastTime += 1.0;
		}

	}

	return 0;
}


