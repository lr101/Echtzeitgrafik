#include "Camera.h"

Camera::Camera(glm::vec3 cameraPostition) {
	std::cout << "camera position: " << cameraPostition[0] << ", " << cameraPostition[1] << ", " << cameraPostition[2] << std::endl;
	this->cameraPostition = glm::vec3(3.f, 0.f, 10.f);
}

Camera::~Camera() {

}

void Camera::setUniforms(Shader& shader) {
	glm::mat4 mat_view = glm::mat4(1.0f);
	mat_view = glm::translate(mat_view, -1.f * cameraPostition);
	shader.setUniform("u_view", mat_view);
	shader.setUniform("u_viewPos", cameraPostition);
}