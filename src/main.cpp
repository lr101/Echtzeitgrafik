

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
#include "Scene.hpp";
#include <iostream>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
Scene* loadScene();
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
    glm::mat4 mat_model = glm::mat4(1.0f);
    mat_projection = glm::mat4(1.0f);

    mat_model = glm::scale(mat_model, glm::vec3(1.5f, 1.5f, 1.5f));
    mat_projection = glm::perspective(glm::radians(45.0f), WIDTH / HEIGHT, 0.1f, 1000.0f);

    shader.setUniform("u_model", mat_model);
    shader.setUniform("u_projection", mat_projection);


    Scene* scene = loadScene();

    // For calculating fps
    GLdouble lastTime = glfwGetTime();
    GLuint nbFrames = 0;

    GLfloat rotAmount = glm::radians(0.f);
    const GLfloat rotPerFrame = .01f;

    scene->setUniforms(shader);
    
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
        glm::mat4 tmp_mat_model = glm::translate(mat_model, glm::vec3(2.f, 0.f, -2.f));
        tmp_mat_model = glm::rotate(tmp_mat_model, rotAmount, glm::vec3(0.1f, 0.1f, 0.1f));
        shader.setUniform("u_model", tmp_mat_model);

        //render the vertices in GeometryBuffer
        scene->render(shader);

        // Swap the screen buffers
        glfwSwapBuffers(window);

        // Rotate the cubes
        rotAmount = glm::radians(rotPerFrame + glm::degrees(rotAmount));

        // Calc fps
        GLdouble currentTime = glfwGetTime();
        nbFrames++;
        if (currentTime - lastTime >= 1.0) {
            std::cout << "fps = " << double(nbFrames) << std::endl;
            nbFrames = 0;
            lastTime += 1.0;
        }
       
    }

    delete scene;

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

Scene* loadScene() {
    // Create an instance of the Importer class
    Assimp::Importer importer;
    std::string path = std::filesystem::current_path().generic_string();
    std::string scene_file = std::string(path).append("/../res/test_scenedae.sec");
    const aiScene* scene = importer.ReadFile(scene_file,
        aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices |
        aiProcess_SortByPType | aiProcess_PreTransformVertices);
    // If the import failed, report it
    if (!scene) {
        std::cerr << "Importing of 3D scene failed: " << importer.GetErrorString() << std::endl;
    }
    return new Scene(scene);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
