#include "mat4rotation.hpp"


Mat4Rotation::Mat4Rotation() {
	this->axis = glm::vec3(0.0f,0.0f,0.0f);
	this->angle = 1.0f;
	this->rotating = false;
}

void Mat4Rotation::setSpeed(float angle) {
	this->angle = angle;
}

void Mat4Rotation::keySignal(int direction, int glfw_keyAction) {
	switch (direction) {
		case UP: {
			if(glfw_keyAction == PRESS) {
				this->axis += glm::vec3(1.0f, 0.0f, 0.0f);
			} else if (glfw_keyAction == RELEASE) {
				this->axis += glm::vec3(-1.0f, 0.0f, 0.0f);
			}
		} break;
		case RIGHT: {
			if(glfw_keyAction == PRESS) {
				this->axis += glm::vec3(0.0f, -1.0f, 0.0f);
			} else if (glfw_keyAction == RELEASE) {
				this->axis += glm::vec3(0.0f, 1.0f, 0.0f);
			}
		} break;
		case DOWN: {
			if(glfw_keyAction == PRESS) {
				this->axis += glm::vec3(-1.0f, 0.0f, 0.0f);
			} else if (glfw_keyAction == RELEASE) {
				this->axis += glm::vec3(1.0f, 0.0f, 0.0f);
			}
		} break;
		case LEFT: {
			if(glfw_keyAction == PRESS) {
				this->axis += glm::vec3(0.0f, 1.0f, 0.0f);
			} else if (glfw_keyAction == RELEASE) {
				this->axis += glm::vec3(0.0f, -1.0f, 0.0f);
			}
		} break;
	}

	if(this->axis == glm::vec3(0.0f,0.0f,0.0f)) {
		this->rotating = false;
	} else {
		this->rotating = true;
	}
	
}

glm::mat4 Mat4Rotation::rotate(glm::mat4 model) {
	if(rotating) {
		return glm::rotate(model, this->angle, this->axis);
	} else {
		return model;
	}

}