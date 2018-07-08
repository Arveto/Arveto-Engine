
#include <iostream>
#include "Window/window.h"
#include "Shader/shader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glm/glm.hpp>


int main() {

		//Creating window and shader

	bool quit = false;

	Window window("Arveto Engine -- Testing");

	window.init();
	window.printInfos();


	Shader shader1("src/shaders/shader.vert", "src/shaders/shader.frag");



	/************************************************************************************************/

			// set up vertex data (and buffer(s)) and configure vertex attributes

		//Cube vertives
		float vertices[] = {
	        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	    };

		unsigned int VBO, VAO;
	    glGenVertexArrays(1, &VAO);
	    glGenBuffers(1, &VBO);

	    glBindVertexArray(VAO);

	    glBindBuffer(GL_ARRAY_BUFFER, VBO);
	    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	    // position attribute
	    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	    glEnableVertexAttribArray(0);
	    // texture coord attribute
	    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	    glEnableVertexAttribArray(1);


	/************************************************************************************************/

		// Creating and binding transformations matrices to our shader

	shader1.use();

	glm::mat4 modelMatrix = glm::mat4(1.0f);;
    glm::mat4 viewMatrix = glm::mat4(1.0f);;
	glm::mat4 projectionMatrix = glm::mat4(1.0f);;

	modelMatrix = glm::rotate(modelMatrix, glm::radians(40.0f), glm::vec3(1.0f, 0.5f, 0.0f));	//Model coords
	viewMatrix  = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -2.0f));		//Space coords
	projectionMatrix = glm::perspective(glm::radians(45.0f), (float)window.getWidth() / (float)window.getHeight(), 0.1f, 100.0f);

	shader1.setModelMatrix(modelMatrix);
	shader1.setViewMatrix(viewMatrix);
	shader1.setProjectionMatrix(projectionMatrix);

	glEnable(GL_DEPTH_TEST);


	/************************************************************************************************/


	//Game loop
	while ( !window.shouldClose() ) {
		window.refresh();

			// Render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Clean depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// render the triangle
		shader1.use();

		glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

		shader1.disable();

		window.pollEvents();

	}

}
