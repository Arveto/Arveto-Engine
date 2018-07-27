
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Window/window.h"
#include "Shader/shader.h"
#include "Camera/camera.h"
#include "Model/model.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>


int main() {

		//Creating window and shader
	Window window("Arveto Engine -- Testing");

	window.init();
	window.printInfos();


	Shader shader1("modelShader", "modelShader");


	/************************************************************************************************/

			//Load model

		Model model1("nanosuit/nanosuit.obj");


	/************************************************************************************************/

		// Creating and binding transformations matrices to our shader
		// View matrix is managed by the camera (see below)

		shader1.use();

		glm::mat4 modelMatrix = glm::mat4(1.0f);;
		glm::mat4 projectionMatrix = glm::mat4(1.0f);;

		modelMatrix = glm::rotate(modelMatrix, glm::radians(0.0f), glm::vec3(0.5f, 0.5f, 0.0f));	//Model coords

		projectionMatrix = glm::perspective(glm::radians(60.0f), (float)window.getWidth() / (float)window.getHeight(), 0.1f, 100.0f);

		shader1.setModelMatrix(modelMatrix);
		shader1.setProjectionMatrix(projectionMatrix);

		glEnable(GL_DEPTH_TEST);

	/************************************************************************************************/

		// Camera creation
	Window &windowRef = window;
	Camera camera(glm::vec3(0.0f, 0.0f,  3.0f), windowRef);

	window.bindCamera(&camera);

	//Cam init
	shader1.setViewMatrix(camera.setView());

	/************************************************************************************************/


		//Game loop

	while ( !window.shouldClose() ) {

		// Input management
	window.refresh();
	window.pollEvents();

	shader1.setViewMatrix(camera.setView());


		// Render
	// Cleanings
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Model render
	model1.render(shader1);

	}

}
