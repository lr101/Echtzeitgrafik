#pragma once

#include <vector>

#include "Shader.h"
#include "GeometryBuffer.h"

class Mesh2 
{
public:

    Mesh2(std::vector<float>& vertices_, std::vector<unsigned int>& indices_, const GLfloat rotPerFrame_, glm::vec3 rotationMatrix_);

    void render(Shader& shader);

    ~Mesh2();

private:
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    GLfloat rotAmount = glm::radians(0.f);
    GLfloat rotPerFrame;
    glm::mat4 mat_model = glm::mat4(1.0f);
    GeometryBuffer* buffer;
    glm::vec3 rotationMatrix;
};