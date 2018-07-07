
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

	std::cout << "Model:\n";
	printf("[%f] [%f] [%f] [%f]\n", modelMatrix[0][0], modelMatrix[0][1], modelMatrix[0][2], modelMatrix[0][3]);
	printf("[%f] [%f] [%f] [%f]\n", modelMatrix[1][0], modelMatrix[1][1], modelMatrix[1][2], modelMatrix[1][3]);
	printf("[%f] [%f] [%f] [%f]\n", modelMatrix[2][0], modelMatrix[2][1], modelMatrix[2][2], modelMatrix[2][3]);
	printf("[%f] [%f] [%f] [%f]\n", modelMatrix[3][0], modelMatrix[3][1], modelMatrix[3][2], modelMatrix[3][3]);

	std::cout << std::endl;

	std::cout << "view:\n";
	printf("[%f] [%f] [%f] [%f]\n", viewMatrix[0][0], viewMatrix[0][1], viewMatrix[0][2], viewMatrix[0][3]);
	printf("[%f] [%f] [%f] [%f]\n", viewMatrix[1][0], viewMatrix[1][1], viewMatrix[1][2], viewMatrix[1][3]);
	printf("[%f] [%f] [%f] [%f]\n", viewMatrix[2][0], viewMatrix[2][1], viewMatrix[2][2], viewMatrix[2][3]);
	printf("[%f] [%f] [%f] [%f]\n", viewMatrix[3][0], viewMatrix[3][1], viewMatrix[3][2], viewMatrix[3][3]);

	std::cout << std::endl;

	std::cout << "projection:\n";
	printf("[%f] [%f] [%f] [%f]\n", projectionMatrix[0][0], projectionMatrix[0][1], projectionMatrix[0][2], projectionMatrix[0][3]);
	printf("[%f] [%f] [%f] [%f]\n", projectionMatrix[1][0], projectionMatrix[1][1], projectionMatrix[1][2], projectionMatrix[1][3]);
	printf("[%f] [%f] [%f] [%f]\n", projectionMatrix[2][0], projectionMatrix[2][1], projectionMatrix[2][2], projectionMatrix[2][3]);
	printf("[%f] [%f] [%f] [%f]\n", projectionMatrix[3][0], projectionMatrix[3][1], projectionMatrix[3][2], projectionMatrix[3][3]);


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
