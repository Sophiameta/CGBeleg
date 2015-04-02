// Include standard headers
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "shader.hpp"
#include "texture.hpp"

// Camera Movement
#include "camtranslation.hpp"

// Objects
#include "Obj.hpp"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#define CAMERA_WIDTH 800
#define CAMERA_HEIGHT 600

GLFWwindow* mainWindow = 0;
bool fullScreen = false;

CamTranslation *camTranslate;

// upper body
Obj * root, * child;
float og_x, og_z; 
// head
Obj * child1, * child2;
// left arm
Obj * child3, * child4, * child5, * child6, * child7, * child8; 
float ag1_x, ag1_z, eg1_x, eg1_z, hg1_x, hg1_z; 
// right arm
Obj * child9, * child10, * child11, * child12, * child13, * child14;
float ag2_x, ag2_z, eg2_x, eg2_z, hg2_x, hg2_z; 
// lower body
Obj * root2, * child15;
float ug_x, ug_z; 
// left leg
Obj * child16, * child17, * child18, * child19, * child20, * child21;
float bg1_x, bg1_z, kg1_x, kg1_z, fg1_x, fg1_z; 
// right leg
Obj * child22, * child23, * child24, * child25, * child26, * child27;
float bg2_x, bg2_z, kg2_x, kg2_z, fg2_x, fg2_z;  

float *orient1 = &ug_x;
float *orient2 = &ug_z;
float min1 = 0; 
float max1 = 0;
float min2 = 0;
float max2 = 0;


void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (key) {
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
		break;

		// control camera
		case GLFW_KEY_KP_ADD:
			camTranslate->keySignal(CamTranslation::FORWARD, action);
		break;
		case GLFW_KEY_KP_SUBTRACT:
			camTranslate->keySignal(CamTranslation::BACKWARD, action);
		break;
		case GLFW_KEY_KP_4:
			camTranslate->keySignal(CamTranslation::LEFT, action);
		break;
		case GLFW_KEY_KP_6:
			camTranslate->keySignal(CamTranslation::RIGHT, action);
		break;
		case GLFW_KEY_KP_8:
			camTranslate->keySignal(CamTranslation::UP, action);
		break;
		case GLFW_KEY_KP_2:
			camTranslate->keySignal(CamTranslation::DOWN, action);
		break;
		
		// control body
		case GLFW_KEY_UP:
			if (*orient1 < max1){
				*orient1 += 5;
				child1->model = glm::rotate(child1->model, 5.0f, vec3(1, 0, 0));
			}
		break;
		case GLFW_KEY_DOWN:
			if (*orient1 > min1){
				*orient1 -= 5;
				child1->model = glm::rotate(child1->model, -5.0f, vec3(1, 0, 0));
			}
		break;
		case GLFW_KEY_LEFT:
			if (*orient2 > min2){
				*orient2 -= 5;
				child1->model = glm::rotate(child1->model, -5.0f, vec3(0, 0, 1));
			}
		break;
		case GLFW_KEY_RIGHT:
			if (*orient2 < max2){
				*orient2 += 5;
				child1->model = glm::rotate(child1->model, 5.0f, vec3(0, 0, 1));
			}
		break;

		// upper body
		case GLFW_KEY_5:
			child1 = child; orient1 = &og_x; orient2 = &og_z; min1 = -45; max1 = 45; min2 = -80; max2 = 80;
		break;
		// head
		case GLFW_KEY_4:
			child1 = child2; orient1 = &bg1_x; orient2 = &bg1_z; min1 = -60; max1 = 25; min2 = -30; max2 = 30;
		break;
		// left arm
		case GLFW_KEY_3:
			child1 = child4; orient1 = &ag1_x; orient2 = &ag1_z; min1 = 0; max1 = 90; min2 = -75; max2 = 90;
		break;
		case GLFW_KEY_2:
			child1 = child6; orient1 = &eg1_x; orient2 = &eg1_z; min1 = 0; max1 = 0; min2 = -90; max2 = 0;
		break;
			case GLFW_KEY_1:
			child1 = child8; orient1 = &hg1_x; orient2 = &hg1_z; min1 = -70; max1 = 5; min2 = -25; max2 = 30; 
		break;
		// right arm
		case GLFW_KEY_7:
			child1 = child10; orient1 = &ag2_x; orient2 = &ag2_z; min1 = 0; max1 = 90; min2 = -75; max2 = 90;
		break;
		case GLFW_KEY_8:
			child1 = child12; orient1 = &eg2_x; orient2 = &eg2_z; min1 = 0; max1 = 0; min2 = -90; max2 = 0;
		break;
		case GLFW_KEY_9:
			child1 = child14; orient1 = &hg2_x; orient2 = &hg2_z; min1 = -70; max1 = 5; min2 = -25; max2 = 30;
		break;

		// lower body
		case GLFW_KEY_6:
			child1 = child15; orient1 = &ug_x; orient2 = &ug_z; min1 = 0; max1 = 0; min2 = -20; max2 = 20;
		break;
		// left leg
		case GLFW_KEY_T: 
			child1 = child17; orient1 = &bg1_x; orient2 = &bg1_z; min1 = -80; max1 = 80; min2 = -80; max2 = 80;
		break;
		case GLFW_KEY_F: 
			child1 = child19; orient1 = &kg1_x; orient2 = &kg1_z; min1 = -90; max1 = 0; min2 = 0; max2 = 0;
		break;
		case GLFW_KEY_C:
			child1 = child21; orient1 = &fg1_x; orient2 = &fg1_z; min1 = -70; max1 = 20; min2 = -30; max2 = 30;
		break;
		// right leg
		case GLFW_KEY_Z: 
			child1 = child23; orient1 = &bg2_x; orient2 = &bg2_z; min1 = -80; max1 = 80; min2 = -80; max2 = 80;
		break;
		case GLFW_KEY_H: 
			child1 = child25; orient1 = &kg2_x; orient2 = &kg2_z; min1 = -90; max1 = 0; min2 = 0; max2 = 0;
		break;
		case GLFW_KEY_N:
			child1 = child27; orient1 = &fg2_x; orient2 = &fg2_z; min1 = -70; max1 = 20; min2 = -30; max2 = 30;
		break;
		default: break;
	}
}

void initGL() {
	// init glfw
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		exit(EXIT_FAILURE);
	}
	mainWindow = glfwCreateWindow(CAMERA_WIDTH, CAMERA_HEIGHT, "CGWR", NULL ,  NULL); // (width, height, title, windowed, shared window)

	// create window
	if (!mainWindow) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(mainWindow);

	//init glew
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		exit(EXIT_FAILURE);
	}

	// set callback functions
	glfwSetErrorCallback(error_callback);
	glfwSetKeyCallback(mainWindow, key_callback);
	
}

int main(void)
{	
	initGL();
	glClearColor(0.1f, 0.1f, 0.1f, 0.1f);

	// zBuffer
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// shader program
	GLuint programID = LoadShaders("StandardShading.vertexshader", "StandardShading.fragmentshader");
	glUseProgram(programID);
	
	// projection and camera
	glm::mat4 Projection = glm::perspective(75.0f, 4.0f / 3.0f, 0.01f, 100.0f);
	glm::vec3 camPos = glm::vec3(-5,0,-0.5);
	glm::vec3 camUp =  glm::vec3(0,0,1);
	glm::vec3 camDirection = glm::vec3(1,0,0);

	// movability and fps display

	camTranslate = new CamTranslation();
	

	// Ligth position
	glm::vec3 lightPos = glm::vec3(1,2,3); // ACTUALLY NOT USED)
	glm::vec3 sunPos = glm::vec3(-100,100,20);

	// timer
	double lastTime = glfwGetTime();
	double curTime;
	double tickMultiplier;
	bool giveTime = false;

	// Creating Objects

	// upper body
	root = new Obj("koerperteile/hueftgelenk.obj", "wood.bmp");
	root->model = glm::translate(root->model, glm::vec3(0.0f, 0.0f, 0.0f));

	child = new Obj("koerperteile/oberkoerper.obj", "wood.bmp");
	child->model = glm::translate(child->model, glm::vec3(0.0f, 0.0f, -0.1f));
	child->model = glm::rotate(child->model, 90.0f, glm::vec3(0, 0, 1)); 

	// head
	child1 = new Obj("koerperteile/hals.obj", "wood.bmp");
	child1->model = glm::translate(child1->model, glm::vec3(0.0f, 0.0f, 0.9f));	

	child2 = new Obj("koerperteile/kopf.obj", "wood.bmp");
	child2->model = glm::translate(child2->model, glm::vec3(0.0f, 0.0f, 0.0f));
	
	// left arm
	child3 = new Obj("koerperteile/schultergelenk.obj", "wood.bmp");
	child3->model = glm::translate(child3->model, glm::vec3(0.3f, 0.0f, 0.75f));


	child4 = new Obj("koerperteile/oberarm.obj", "wood.bmp");
	child4->model = glm::translate(child4->model, glm::vec3(0.0f, 0.0f, 0.0f));
	child4->model = glm::rotate(child4->model, 180.0f, glm::vec3(0, 1, 0));

	child5 = new Obj("koerperteile/ellenbogengelenk.obj", "wood.bmp");
	child5->model = glm::translate(child5->model, glm::vec3(-0.85f, 0.15f, 0.0f));

	child6 = new Obj("koerperteile/unterarm.obj", "wood.bmp");
	child6->model = glm::translate(child6->model, glm::vec3(0.05f, 0.0f, 0.0f));

	child7 = new Obj("koerperteile/handgelenk.obj", "wood.bmp");
	child7->model = glm::translate(child7->model, glm::vec3(-0.75f, 0.0f, 0.0f));

	child8 = new Obj("koerperteile/hand.obj", "wood.bmp");
	child8->model = glm::translate(child8->model, glm::vec3(0.0f, 0.0f, 0.0f));

	// right arm
	child9 = new Obj("koerperteile/schultergelenk.obj", "wood.bmp");
	child9->model = glm::translate(child9->model, glm::vec3(-0.3f, 0.0f, 0.75f));

	child10 = new Obj("koerperteile/oberarm.obj", "wood.bmp");
	child10->model = glm::translate(child10->model, glm::vec3(0.0f, 0.0f, 0.0f));

	child11 = new Obj("koerperteile/ellenbogengelenk.obj", "wood.bmp");
	child11->model = glm::translate(child11->model, glm::vec3(-0.85f, 0.15f, 0.0f));

	child12 = new Obj("koerperteile/unterarm.obj", "wood.bmp");
	child12->model = glm::translate(child12->model, glm::vec3(0.05f, 0.0f, 0.0f));

	child13 = new Obj("koerperteile/handgelenk.obj", "wood.bmp");
	child13->model = glm::translate(child13->model, glm::vec3(-0.75f, 0.0f, 0.0f));

	child14 = new Obj("koerperteile/hand.obj", "wood.bmp");
	child14->model = glm::translate(child14->model, glm::vec3(0.0f, 0.0f, 0.0f));

	// linking upper body
	root->appendChild(child);
	child->appendChild(child1);
	child1->appendChild(child2);
	child->appendChild(child3);
	child3->appendChild(child4);
	child4->appendChild(child5);
	child5->appendChild(child6);
	child6->appendChild(child7);
	child7->appendChild(child8);
	child->appendChild(child9);
	child9->appendChild(child10);
	child10->appendChild(child11);
	child11->appendChild(child12);
	child12->appendChild(child13);
	child13->appendChild(child14);

	// lower body
	root2 = new Obj("koerperteile/hueftgelenk.obj", "wood.bmp");
	root2->model = glm::translate(root2->model, glm::vec3(0.0f, 0.0f, 0.0f));

	child15 = new Obj("koerperteile/unterkoerper.obj", "wood.bmp");
	child15->model = glm::translate(child15->model, glm::vec3(0.0f, 0.0f, -0.5f));
	child15->model = glm::rotate(child15->model, 90.0f, glm::vec3(0, 0, 1));

	// left leg
	child16 = new Obj("koerperteile/oberschenkelgelenk.obj", "wood.bmp");
	child16->model = glm::translate(child16->model, glm::vec3(0.15f, 0.0f, -0.1f));

	child17 = new Obj("koerperteile/oberschenkel.obj", "wood.bmp");
	child17->model = glm::translate(child17->model, glm::vec3(0.0f, 0.0f, 0.05f));

	child18 = new Obj("koerperteile/kniegelenk.obj", "wood.bmp");
	child18->model = glm::translate(child18->model, glm::vec3(0.05f, -0.05f, -1.0f));
	
	child19 = new Obj("koerperteile/unterschenkel.obj", "wood.bmp");
	child19->model = glm::translate(child19->model, glm::vec3(0.0f, 0.0f, 0.0f));

	child20 = new Obj("koerperteile/fussgelenk.obj", "wood.bmp");
	child20->model = glm::translate(child20->model, glm::vec3(0.0f, 0.1f, -1.15f));

	child21 = new Obj("koerperteile/fuss.obj", "wood.bmp");
	child21->model = glm::translate(child21->model, glm::vec3(0.0f, 0.0f, 0.0f));
	child21->model = glm::rotate(child21->model, 160.0f, glm::vec3(0, 0, 1));

	// right leg
	child22 = new Obj("koerperteile/oberschenkelgelenk.obj", "wood.bmp");
	child22->model = glm::translate(child22->model, glm::vec3(-0.15f, 0.0f, -0.1f));

	child23 = new Obj("koerperteile/oberschenkel.obj", "wood.bmp");
	child23->model = glm::translate(child23->model, glm::vec3(0.0f, 0.0f, 0.05f));
	child23->model = glm::rotate(child23->model, 5.0f, glm::vec3(0, 1, 0));

	child24 = new Obj("koerperteile/kniegelenk.obj", "wood.bmp");
	child24->model = glm::translate(child24->model, glm::vec3(0.05f, -0.05f, -1.0f));
	
	child25 = new Obj("koerperteile/unterschenkel.obj", "wood.bmp");
	child25->model = glm::translate(child25->model, glm::vec3(0.0f, 0.0f, 0.0f));

	child26 = new Obj("koerperteile/fussgelenk.obj", "wood.bmp");
	child26->model = glm::translate(child26->model, glm::vec3(0.0f, 0.1f, -1.15f));

	child27 = new Obj("koerperteile/fuss.obj", "wood.bmp");
	child27->model = glm::translate(child27->model, glm::vec3(0.0f, 0.0f, 0.0f));
	child27->model = glm::rotate(child27->model, 190.0f, glm::vec3(0, 0, 1));
	
	root2->appendChild(child15);
	child15->appendChild(child16);
	child16->appendChild(child17);
	child17->appendChild(child18);
	child18->appendChild(child19);
	child19->appendChild(child20);
	child20->appendChild(child21);
	child15->appendChild(child22);
	child22->appendChild(child23);
	child23->appendChild(child24);
	child24->appendChild(child25);
	child25->appendChild(child26);
	child26->appendChild(child27);

	while (!glfwWindowShouldClose(mainWindow)) {

		// clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

		// take time
		curTime = glfwGetTime();
		tickMultiplier = curTime - lastTime;
		lastTime = curTime;

		// add tickMultiplier to time-relevant events
		camTranslate->setSpeed(tickMultiplier);

		// Camera matrix
		camTranslate->move(camPos, camDirection, camUp);
		
		glm::mat4 View = glm::lookAt(camPos, (camPos + camDirection), camUp);	
		glUniform3f(glGetUniformLocation(programID, "LightPosition_worldspace"), lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(glGetUniformLocation(programID, "Light2Position_worldspace"), sunPos.x, sunPos.y, sunPos.z);
		glUniform3f(glGetUniformLocation(programID, "CameraPosition_worldspace"), camPos.x, camPos.y, camPos.z);
		
		// Draw Objects
		root->drawObject(Projection, View, glm::mat4(1), programID);
		root2->drawObject(Projection, View, glm::mat4(1), programID);
		
		// Swap buffers
		glfwSwapBuffers(mainWindow);

		// Poll for and process events 
        glfwPollEvents();
	}

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
	_CrtDumpMemoryLeaks();
	return 0;
}

