
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

		float vertices[] = {
	        // positions          // colors
	         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
	         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
	        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,
	        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f
	    };
	    unsigned int indices[] = {
	        0, 1, 3, // first triangle
	        1, 2, 3  // second triangle
	    };
	    unsigned int VBO, VAO, EBO;
	    glGenVertexArrays(1, &VAO);
	    glGenBuffers(1, &VBO);
	    glGenBuffers(1, &EBO);

	    glBindVertexArray(VAO);

	    glBindBuffer(GL_ARRAY_BUFFER, VBO);
	    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	    // position attribute
	    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	    glEnableVertexAttribArray(0);
	    // color attribute
	    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	    glEnableVertexAttribArray(1);


	/************************************************************************************************/

		// Creating and binding transformations matrices to our shader

	shader1.use();

	glm::mat4 modelMatrix = glm::mat4(1.0f);;
    glm::mat4 viewMatrix = glm::mat4(1.0f);;
	glm::mat4 projectionMatrix = glm::mat4(1.0f);;

	modelMatrix = glm::rotate(modelMatrix, glm::radians(-10.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	viewMatrix  = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -3.0f));
	projectionMatrix = glm::perspective(glm::radians(45.0f), (float)window.getWidth() / (float)window.getHeight(), 0.1f, 100.0f);

	shader1.setModelMatrix(modelMatrix);
	shader1.setViewMatrix(viewMatrix);
	shader1.setProjectionMatrix(projectionMatrix);


	/************************************************************************************************/


	//Game loop
	while ( !window.shouldClose() ) {
		window.refresh();

			// Render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// render the triangle
		shader1.use();

		glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		shader1.disable();

		window.pollEvents();

	}

}
