#include "Obj.hpp"
#include "objloader.hpp"
#include "texture.hpp"
#include <iostream>

Obj::Obj(const char *modelPath, const char *colorTexturePath) {
	
	this->model = glm::mat4(1);

	// mesh
	std::vector<glm::vec3> tempVertices;
	std::vector<glm::vec2> tempUVs;
	std::vector<glm::vec3> tempNormals;

	if (loadOBJ(modelPath, tempVertices, tempUVs, tempNormals)) {
		glGenVertexArrays(1, &vertexarray);
		glBindVertexArray(vertexarray);

		vertexcount = tempVertices.size();
		// create and bind vertex buffer
		glGenBuffers(1, &vertexbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, tempVertices.size() * sizeof(glm::vec3), &tempVertices[0], GL_STATIC_DRAW);

		// bind attributes to vertex array
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		// create and bind UV buffer
		glGenBuffers(1, &uvbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glBufferData(GL_ARRAY_BUFFER, tempUVs.size() * sizeof(glm::vec2), &tempUVs[0], GL_STATIC_DRAW);

		// bind attributes to vertex array
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

		// create and bind normal buffer
		glGenBuffers(1, &normalbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
		glBufferData(GL_ARRAY_BUFFER, tempNormals.size() * sizeof(glm::vec3), &tempNormals[0], GL_STATIC_DRAW);

		// bind attributes to vertex array
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glBindVertexArray(0);
	}


	// textures
	colorTexture = loadBMP_custom(colorTexturePath);

}

Obj::~Obj() {
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &normalbuffer);
	glDeleteVertexArrays(1, &vertexarray);

	glDeleteTextures(1, &colorTexture);
}

void Obj::appendChild(Obj *child) {
	this->children.push_back(child);

}


void Obj::removeChild(Obj *child) {
	for (int i = 0; i < children.size(); i++) {
		if (children[i] == child) {
			children.erase(children.begin() + i);
		}
	}
}


void Obj::drawObject(glm::mat4 projection, glm::mat4 view, glm::mat4 model, GLuint shader) {
	
	// actually used model
	glm::mat4 renderModel = model * this->model;

		// textures
	glEnable( GL_TEXTURE_2D );
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, colorTexture);
	glUniform1i(glGetUniformLocation(shader, "colorTextureSampler"), 0);

	// enable shading with textures
	glUniform1i(glGetUniformLocation(shader, "textureShading"),1 );

	// mesh + view
	glm::mat4 MVP = projection * view * renderModel;

	
	glBindVertexArray(vertexarray);
	glUniformMatrix4fv(glGetUniformLocation(shader, "MVP"), 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shader, "V"), 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shader, "M"), 1, GL_FALSE, &renderModel[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, vertexcount);

	glBindVertexArray(0);
	glDisable(GL_TEXTURE_2D);
	glUniform1i(glGetUniformLocation(shader, "textureShading"),0 ); // disable shading with textures

	// drawing child objects, this should be changed to an privarte function so openGL inits like glEnable(GL_TEXTURE_2D) so they arn't called multiple times for no reason
	for (int i = 0; i < children.size(); i++) {
		children[i]->drawObject(projection, view, renderModel, shader); // model * this->model is important, recursive
	}

}