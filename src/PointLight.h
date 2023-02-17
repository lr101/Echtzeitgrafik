#pragma once

#define GLEW_STATIC
#include <GL/glew.h> // has to be included first!
#include <GLFW/glfw3.h>
#include <assimp/Importer.hpp>
#include <glm/ext.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "Shader.h"

class PointLight {
	glm::vec3 lightPos;
	glm::vec3 lightCol;

public:
	PointLight(glm::vec3 lightPos, glm::vec3 lightCol);
	PointLight(const PointLight& light);
	~PointLight();

	void setUniforms(Shader& shader);
};