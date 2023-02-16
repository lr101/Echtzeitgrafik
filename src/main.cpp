

#define GLEW_STATIC
#include <GL/glew.h> // has to be included first!
#include <GLFW/glfw3.h>
#include <assimp/Importer.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ft2build.h>
#include <filesystem>
#include "helper/RootDir.h"
#include FT_FREETYPE_H

#include <Shader_learn.h>
#include <camera_learn.h>
#include <Model_learn.h>
#include "GeometryBuffer.h"
#include "Shader.h"
#include "Scene.hpp";
#include <iostream>

unsigned int loadTexture(const char* path);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
Scene* loadScene();

// Window dimensions
const GLfloat WIDTH = 800.f, HEIGHT = 600.f;

const char* vertexShader = "shader.vert";
const char* fragmentShader = "shader.frag";

bool blinn = false;
bool blinnKeyPressed = false;

glm::vec3 viewPos(3.f, 0.f, 10.f);
glm::mat4 mat_projection;
bool projection_type = true;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = (float)WIDTH / 2.0;
float lastY = (float)HEIGHT / 2.0;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glewInit();
    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);

    // build and compile shaders
    Shader shader("shader.vert", "shader.frag");

    // Create model, view and projection matrices for the shader
    glm::mat4 mat_model = glm::mat4(1.0f);
    glm::mat4 mat_view = glm::mat4(1.0f);
    mat_projection = glm::mat4(1.0f);

    mat_model = glm::scale(mat_model, glm::vec3(1.5f, 1.5f, 1.5f));
    mat_view = glm::translate(mat_view, -1.f * viewPos);
    mat_projection = glm::perspective(glm::radians(45.0f), WIDTH / HEIGHT, 0.1f, 1000.0f);

    shader.setUniform("u_model", mat_model);
    shader.setUniform("u_view", mat_view);
    shader.setUniform("u_projection", mat_projection);
    shader.setUniform("u_viewPos", viewPos);
    shader.setUniform("u_objectCol", glm::vec3(1.f, .5f, .32f));

    Scene* scene = loadScene();
    
    
    while (!glfwWindowShouldClose(window))
    {

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw objects
        //shader.use();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        shader.setUniform("projection", projection);
        shader.setUniform("view", view);
        // set light uniforms
        shader.setUniform("viewPos", camera.Position);
        shader.setUniform("lightPos", lightPos);
        shader.setUniform("blinn", blinn);
      
        //
        scene->setUniforms(shader);
        scene->render(shader);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    delete scene;

    glfwTerminate();
    return 0;
}

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const* path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT); // for this tutorial: use GL_CLAMP_TO_EDGE to prevent semi-transparent borders. Due to interpolation it takes texels from next repeat 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
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
