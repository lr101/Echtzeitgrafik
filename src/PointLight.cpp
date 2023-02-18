#include "PointLight.h"

PointLight::PointLight(glm::vec3 light_pos, glm::vec3 light_col)
{
	std::cout << "light position: " << light_pos[0] << ", " << light_pos[1] << ", " << light_pos[2] << std::endl;
	std::cout << "light color: " << light_col[0] << ", " << light_col[1] << ", " << light_col[2] << std::endl;
	this->light_pos_ = light_pos;
	this->light_col_ = light_col;
}

PointLight::PointLight(const PointLight& light)
{
	this->light_pos_ = light.light_pos_;
	this->light_col_ = light.light_col_;
}

void PointLight::set_uniforms(Shader& shader) const
{
	shader.setUniform("u_lightPos", this->light_pos_);
	shader.setUniform("u_lightCol", this->light_col_);
}

void PointLight::apply_mat(Shader& shader, const glm::mat4 mat_model) const
{
	const glm::vec4 tmp_light_pos = mat_model * glm::vec4(this->light_pos_, 1.0f);
	shader.setUniform("u_lightPos", glm::vec3(tmp_light_pos));
}

