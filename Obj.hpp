#ifndef OBJ_HPP
#define OBJ_HPP
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class Obj {
private:

	int vertexcount;
	GLuint vertexarray;
	GLuint vertexbuffer;
	GLuint normalbuffer;
	GLuint uvbuffer;

	GLuint colorTexture;

	std::vector<Obj*> children;


public:
	Obj(const char *modelPath, const char *colorTexturePath);
	~Obj();

	void appendChild(Obj *child);
	void removeChild(Obj *child);

	void drawObject(glm::mat4 projection, glm::mat4 view, glm::mat4 model,  GLuint shader);

	glm::mat4 model; // public model matrix for convenience

};
#endif // OBJ_HPP