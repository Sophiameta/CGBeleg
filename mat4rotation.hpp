#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Mat4Rotation {
private:
	bool rotating;
	glm::vec3 axis;
	float angle;



public:
	// --- variables ---

	// directions
	static const int UP = 1;
	static const int RIGHT = 2;
	static const int DOWN = 3;
	static const int LEFT = 4;

	// actions
	static const int RELEASE = 0;
	static const int PRESS = 1;
	static const int REPEAT = 2;

	// --- functions ---

	Mat4Rotation();
	void setSpeed(float angle);							// set angle
	void keySignal(int direction, int glfw_keyAction);	// Key input 
	glm::mat4 rotate(glm::mat4 model);						// actuall rotation operation


};