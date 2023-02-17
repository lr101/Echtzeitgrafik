#include "Camera.h"

Camera::Camera(glm::vec3 cameraPostition_) {
	std::cout << "camera position: " << cameraPostition_[0] << ", " << cameraPostition_[1] << ", " << cameraPostition_[2] << std::endl;
	this->cameraPostition = cameraPostition_;
}

Camera::~Camera() {

}

void Camera::setUniforms(Shader& shader) {
	//set position and view
	glm::mat4 mat_view = glm::mat4(1.0f);
	mat_view = glm::translate(mat_view, -1.f * cameraPostition);
	shader.setUniform("u_view", mat_view);
	shader.setUniform("u_viewPos", cameraPostition);
}