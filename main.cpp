
#include <iostream>
#include "Window/window.h"
#include "Shader/shader.h"
#include <GLFW/glfw3.h>


int main() {

	bool quit = false;

	Window window("Arveto Engine -- Testing");

	window.init();
	window.printInfos();


	Shader shader1("src/shaders/shader.vert", "src/shaders/shader.frag");



	/************************************************************************************************/

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// positions		 // colors
		 0.5f, -0.5f, -0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top
	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


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
		glDrawArrays(GL_TRIANGLES, 0, 3);

		shader1.desactive();

		window.pollEvents();

	}

}
