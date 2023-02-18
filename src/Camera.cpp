#include "Camera.h"

Camera::Camera(glm::vec3 camera_position, glm::vec3 look_at)
{
	std::cout << "camera position: " << camera_position[0] << ", " << camera_position[1] << ", " << camera_position[
		2] << std::endl;
	std::cout << "look at: " << look_at[0] << ", " << look_at[1] << ", " << look_at[2] << std::endl;
	this->camera_position_ = camera_position;

	const glm::vec3 look_at_(look_at[0], look_at[1], look_at[2]);
	const glm::vec3 camera_direction = normalize(this->camera_position_ - look_at_);
	std::cout << "Camera direction: " << camera_direction.x << ", " << camera_direction.x << ", " << camera_direction.x <<
		std::endl;
	const auto up = glm::vec3(0.0f, 1.0f, 0.0f);
	const glm::vec3 camera_right = normalize(cross(up, camera_direction));
	const glm::vec3 camera_up = cross(camera_direction, camera_right);
	this->view_ = glm::lookAt(this->camera_position_, look_at_, camera_up);
}

Camera::Camera(const Camera& camera)
{
	this->camera_position_ = camera.camera_position_;
	this->view_ = camera.view_;
}


void Camera::set_uniforms(Shader& shader) const
{
	//set position and view
	shader.setUniform("u_view", this->view_);
	shader.setUniform("u_viewPos", camera_position_);
}

glm::mat4 Camera::get_view() const
{
	return this->view_;
}

void Camera::set_view(const glm::mat4 view)
{
	this->view_ = view;
}


