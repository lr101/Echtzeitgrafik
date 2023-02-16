
#define GLEW_STATIC
#include <GL/glew.h> // has to be included first!
#include <GLFW/glfw3.h>
#include <assimp/Importer.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include <iostream>
#include "GeometryBuffer.h"
#include "Shader.h"

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// Window dimensions
const GLfloat WIDTH = 800.f, HEIGHT = 600.f;

const char* vertexShader = "../res/shader.vert";
const char* fragmentShader = "../res/shader.frag";


glm::vec3 viewPos(3.f, 0.f, 10.f);
glm::vec3 lightOffset(0.f, 1.f, 0.f);
glm::mat4 mat_projection;
bool projection_type = true;

// The MAIN function, from here we start the application and run the game loop
int main()
{
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Cubes", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    glewInit();

    // Define the viewport dimensions
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	// Enable Depth Testing
	glEnable(GL_DEPTH_TEST);

    Shader shader(vertexShader, fragmentShader);

    // Create model, view and projection matrices for the shader
    glm::mat4 mat_model = glm::mat4(1.0f);
    glm::mat4 mat_view = glm::mat4(1.0f);
    mat_projection = glm::mat4(1.0f);

    //mat_model = glm::rotate(mat_model, glm::radians(40.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    mat_model = glm::scale(mat_model, glm::vec3(1.5f, 1.5f, 1.5f));

    mat_view = glm::translate(mat_view, -1.f * viewPos);

    mat_projection = glm::perspective(glm::radians(45.0f), WIDTH / HEIGHT, 0.1f, 1000.0f);

    shader.setUniform("u_model", mat_model);
    shader.setUniform("u_view", mat_view);
    shader.setUniform("u_projection", mat_projection);
    shader.setUniform("u_lightPos", viewPos + lightOffset);
    shader.setUniform("u_viewPos", viewPos);
    shader.setUniform("u_objectColor", glm::vec3(1.f, .5f, .32f));
    shader.setUniform("u_lightColor", glm::vec3(1.f, 1.f, 1.f));

    GLfloat verticesEBO[] = {
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, 0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, 0.5f,
    };

    GLuint indicesEBO[] = {
        0, 1, 2,
        1, 2, 3,
        0, 2, 6,
        0, 4, 6,
        4, 6, 7,
        4, 5, 7,
        3, 5, 7,
        1, 3, 5,
        0, 1, 5,
        0, 4, 5,
        2, 3, 7,
        2, 6, 7
    };

    //TODO calc normal automatically

    // vertices cube without ebo
    GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,

        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,

        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
    };

    GeometryBuffer buffer(vertices, sizeof(vertices), sizeof(vertices) / 3);
    // With EBO
    //GeometryBuffer buffer(verticesEBO, sizeof(verticesEBO), indicesEBO, sizeof(indicesEBO), sizeof(indicesEBO));

	buffer.setAttributes(0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	buffer.setAttributes(1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    // For calculating fps
    GLdouble lastTime = glfwGetTime();
    GLuint nbFrames = 0;

    GLfloat rotAmount = glm::radians(0.f);
    const GLfloat rotPerFrame = .1f;
    while (!glfwWindowShouldClose(window))
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();
        // Render
        // Clear the colorbuffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set projection
        shader.setUniform("u_projection", mat_projection);

        // Rotate model matrix

        for (int i = 0; i < 5; i++) {
            glm::mat4 tmp_mat_model = glm::translate(mat_model, glm::vec3(i * 2.f, 0.f, i * -2.f));
            tmp_mat_model = glm::rotate(tmp_mat_model, rotAmount, glm::vec3(1.0f, i * 0.5f, 0.1f));
            shader.setUniform("u_model", tmp_mat_model);

            // Draw our first triangle
			buffer.draw();
		}

		// Swap the screen buffers
		glfwSwapBuffers(window);

		// Rotate the cubes
        rotAmount = glm::radians(.1f + glm::degrees(rotAmount));

        // Calc fps
        GLdouble currentTime = glfwGetTime();
        nbFrames++;
        if (currentTime - lastTime >= 1.0) {
            std::cout << "fps = " << double(nbFrames) << std::endl;
            nbFrames = 0;
            lastTime += 1.0;
        }
    }
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        GLfloat aspect = WIDTH / HEIGHT;
        if (projection_type) {
            mat_projection = glm::ortho(-1.f * aspect, aspect, -1.f, 1.f, 0.1f, 1000.f);
		} else {
			mat_projection = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 1000.0f);
		}
		projection_type = !projection_type;
	}
}

// Is called whenever the window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
