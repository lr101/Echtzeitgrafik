#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h> // has to be included first!
#include <GLFW/glfw3.h>
#include <assimp/Importer.hpp>
#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

typedef GLuint(*GL_CREATEPROGRAM) (void);
const char* functionName = "glCreateProgram";

void handleEvents(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main() {
	std::cout << "TEST" << std::endl;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 0);
	glfwWindowHint(GLFW_RED_BITS, 8);
	glfwWindowHint(GLFW_GREEN_BITS, 8);
	glfwWindowHint(GLFW_BLUE_BITS, 8);
	glfwWindowHint(GLFW_ALPHA_BITS, 8);
	glfwWindowHint(GLFW_STENCIL_BITS, 8);
	glfwWindowHint(GLFW_DEPTH_BITS, 24);
	glfwWindowHint(GLFW_RESIZABLE, true);
	GLFWwindow* window = glfwCreateWindow(800, 600, "Echtzeitgrafik", nullptr, nullptr);
	if (!window) {
		std::cerr << "Creation of window failed" << std::endl;
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		std::cerr << "Initialization of glew failed" << glewGetErrorString(error) << std::endl;
		glfwTerminate();
		return 1;
	}
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	glViewport(0, 0, 800, 600);
	
	
	while (!glfwWindowShouldClose(window)) {
		handleEvents(window);
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.5f, 0.1f, 0.2f, 1.0f);
		glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-0.9f, 0.3f, 0);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-0.9f, -0.9f, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.9f, 0.0f);
		glEnd();
		glFlush();
		/*glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0f, 0.1f, 0.2f, 1.0f);
		// TODO: OpenGL stuff here
		
		glfwSwapBuffers(window);*/
		//glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}