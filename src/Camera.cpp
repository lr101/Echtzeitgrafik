#include "Camera.h"

Camera::Camera(glm::vec3 cameraPostition_, glm::vec3 lookAt_) {
	std::cout << "camera position: " << cameraPostition_[0] << ", " << cameraPostition_[1] << ", " << cameraPostition_[2] << std::endl;
	std::cout << "camera looking at: " << lookAt_[0] << ", " << lookAt_[1] << ", " << lookAt_[2] << std::endl;
	this->cameraPostition = cameraPostition_;
	this->lookAt = lookAt_;
}

Camera::~Camera() {

}

void Camera::setUniforms(Shader& shader) {
	glm::mat4 mat_view = glm::mat4(1.0f);
	mat_view = glm::translate(mat_view, -1.f * cameraPostition);
	shader.setUniform("u_view", mat_view);
	shader.setUniform("u_viewPos", cameraPostition);
}