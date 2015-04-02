#include "camtranslation.hpp"
#include <iostream>
CamTranslation::CamTranslation() {
	this->vectorLength = 1.0f;
}
void CamTranslation::keySignal(int direction, int glfw_keyAction) {
	switch(direction) {
		case UP:
			if(glfw_keyAction == PRESS) {
				relDirectionVector.z++;
			} else if(glfw_keyAction == RELEASE) {
				relDirectionVector.z--;
			}
		break;
		case DOWN:
			if(glfw_keyAction == PRESS) {
				relDirectionVector.z--;
			} else if(glfw_keyAction == RELEASE) {
				relDirectionVector.z++;
			}
		break;
		case RIGHT:
			if(glfw_keyAction == PRESS) {
				relDirectionVector.y++;
			} else if(glfw_keyAction == RELEASE) {
				relDirectionVector.y--;
			}
		break;
		case LEFT:
			if(glfw_keyAction == PRESS) {
				relDirectionVector.y--;
			} else if(glfw_keyAction == RELEASE) {
				relDirectionVector.y++;
			}
		break;
		case FORWARD:
			if(glfw_keyAction == PRESS) {
				relDirectionVector.x++;
			} else if(glfw_keyAction == RELEASE) {
				relDirectionVector.x--;
			}
		break;
		case BACKWARD:
			if(glfw_keyAction == PRESS) {
				relDirectionVector.x--;
			} else if(glfw_keyAction == RELEASE) {
				relDirectionVector.x++;
			}
		break;
	}
}

void CamTranslation::move(glm::vec3 &camPos, glm::vec3 &camDirection, glm::vec3 &camUp) {
	glm::vec3 trans = glm::vec3(0.0f, 0.0f, 0.0f);

	if(relDirectionVector.x != 0) {
		trans += vectorLength * relDirectionVector.x * glm::normalize(camDirection); // length * direction (1 or -1) * translation;
	}

	if(relDirectionVector.y != 0) {
		trans += vectorLength * -1 * relDirectionVector.y * glm::normalize(glm::cross(camUp, camDirection));
	}

	if(relDirectionVector.z != 0) {
		trans += vectorLength * relDirectionVector.z * glm::normalize(camUp);
	}
	camPos += trans;

}