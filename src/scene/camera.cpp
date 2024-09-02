#include "pch.h"
#include "camera.h"

namespace Physx2D {
	Camera::Camera(vec2 position, float fov) {
		this->position = position;
		this->fov = fov;
	}

	void Camera::handleInputs(GLFWwindow* window, float delta_time) {
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			position.y += speed.y * delta_time;

		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			position.y -= speed.y * delta_time;

		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			position.x -= speed.x * delta_time;

		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			position.x += speed.x * delta_time;

		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
			position = vec2();
			fov = 1.f;
		}

		if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS && fov < 5.f )
			fov += delta_time * sensitivity;

		if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS&& fov > 0.2f)
			fov -= delta_time * sensitivity;
	}
}
