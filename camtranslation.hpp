#ifndef CAMERATRANSLATION_HPP
#define CAMERATRANSLATION_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class CamTranslation {
private:
	float vectorLength;
	glm::vec3 relDirectionVector;

	
public:
	// static variables

	//directions
	static const int UP = 1;
	static const int RIGHT = 2;
	static const int DOWN = 3;
	static const int LEFT = 4;
	static const int FORWARD = 5;
	static const int BACKWARD = 6;

	//actions
	static const int RELEASE = 0;
	static const int PRESS = 1;
	static const int REPEAT = 2;

	//functions
	CamTranslation();

	inline void setSpeed(float speed) {vectorLength = speed;};
	void keySignal(int direction, int glfw_keyAction);
	void move(glm::vec3 &camPos, glm::vec3 &camDirection, glm::vec3 &camUp);
};

#endif