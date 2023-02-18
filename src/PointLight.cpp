#include "PointLight.h"

PointLight::PointLight(glm::vec3 lightPos, glm::vec3 lightCol)
{
	std::cout << "light position: " << lightPos[0] << ", " << lightPos[1] << ", " << lightPos[2] << std::endl;
	std::cout << "light color: " << lightCol[0] << ", " << lightCol[1] << ", " << lightCol[2] << std::endl;
	this->lightPos = lightPos;
	this->lightCol = lightCol;
}

PointLight::PointLight(const PointLight& light)
{
	this->lightPos = light.lightPos;
	this->lightCol = light.lightCol;
}

PointLight::~PointLight()
{
}

void PointLight::setUniforms(Shader& shader)
{
	shader.setUniform("u_lightPos", this->lightPos);
	shader.setUniform("u_lightCol", this->lightCol);
}

void PointLight::apply_mat(Shader& shader, glm::mat4 mat_model)
{
	glm::vec4 tmp_light_pos = mat_model * glm::vec4(this->lightPos, 1.0f);
	shader.setUniform("u_lightPos", glm::vec3(tmp_light_pos));
}

