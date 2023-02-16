#pragma once

#include <vector>

#include "Shader.h"
#include "GeometryBuffer.h"

class Mesh2 
{
public:

    Mesh2(std::vector<float>& vertices_, std::vector<unsigned int>& indices_);

    void render(Shader& shader);

    ~Mesh2();

private:
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    
    GeometryBuffer* buffer;
};