

#define GLEW_STATIC
#include <GL/glew.h> // has to be included first!
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ft2build.h>
#include <filesystem>
#include "helper/RootDir.h"
#include FT_FREETYPE_H

#include "GeometryBuffer.h"
#include "Shader.h"
#include "Scene.hpp";
#include <iostream>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// Window dimensions
const GLfloat WIDTH = 1920.f, HEIGHT = 1080.f;

const char* vertexShader = "shader.vert";
const char* fragmentShader = "shader.frag";

glm::mat4 mat_projection;
bool projection_type = true;



int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 8);
    glEnable(GL_MULTISAMPLE);

    
    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    glewInit();
    glEnable(GL_DEPTH_TEST);
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    // build and compile shaders
    Shader shader("shader.vert", "shader.frag");

    // Create model, view and projection matrices for the shader

    mat_projection = glm::mat4(1.0f);
    mat_projection = glm::perspective(glm::radians(45.0f), WIDTH / HEIGHT, 0.1f, 1000.0f);
    shader.setUniform("u_projection", mat_projection);


    Scene scene = Scene("test_scenedae.sec");

    // For calculating fps
    GLdouble lastTime = glfwGetTime();
    GLuint nbFrames = 0;

    

    scene.setUniforms(shader);
    
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

       

        //render the vertices in GeometryBuffer
        scene.render(shader);

        // Swap the screen buffers
        glfwSwapBuffers(window);
        

        // Calc fps
        GLdouble currentTime = glfwGetTime();
        nbFrames++;
        if (currentTime - lastTime >= 1.0) {
            std::cout << "fps = " << double(nbFrames) << std::endl;
            nbFrames = 0;
            lastTime += 1.0;
        }
       
    }



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
            mat_projection = glm::ortho(-1.f * aspect, aspect, -1.f, 1.f, 0.1f, 100.f);
        }
        else {
            mat_projection = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 1000.0f);
        }
        projection_type = !projection_type;
    }
}



void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
