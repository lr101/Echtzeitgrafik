#include "PointLight.h"

PointLight::PointLight(glm::vec3 lightPos, glm::vec3 lightCol) {
	this->lightPos = lightPos;
	this->lightCol = lightCol;
}

PointLight::~PointLight() {

}

void PointLight::setUniforms(Shader& shader) {
	shader.setUniform("u_lightPos", this->lightPos);
	shader.setUniform("u_lightCol", this->lightCol);
}