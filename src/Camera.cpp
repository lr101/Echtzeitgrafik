#include "Camera.h"

Camera::Camera(glm::vec3 cameraPostition_, glm::vec3 lookAt_)
{
	std::cout << "camera position: " << cameraPostition_[0] << ", " << cameraPostition_[1] << ", " << cameraPostition_[
		2] << std::endl;
	std::cout << "look at: " << lookAt_[0] << ", " << lookAt_[1] << ", " << lookAt_[2] << std::endl;
	this->cameraPostition = cameraPostition_;
	this->lookAt = lookAt_;
}

Camera::Camera(const Camera& camera)
{
	this->cameraPostition = camera.cameraPostition;
	this->lookAt = camera.lookAt;
}

Camera::~Camera()
{
}

void Camera::setUniforms(Shader& shader)
{
	//set position and view
	glm::vec3 cameraDirection = normalize(this->cameraPostition - this->lookAt);
	std::cout << "Camera direction: " << cameraDirection.x << ", " << cameraDirection.x << ", " << cameraDirection.x <<
		std::endl;
	auto up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraRight = normalize(cross(up, cameraDirection));
	glm::vec3 cameraUp = cross(cameraDirection, cameraRight);
	glm::mat4 view;
	view = glm::lookAt(this->cameraPostition, this->lookAt, cameraUp);
	shader.setUniform("u_view", view);
	shader.setUniform("u_viewPos", cameraPostition);
}
