
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Window/window.h"
#include "Shader/shader.h"
#include "Camera/camera.h"
#include "Model/model.h"
#include "Model/shape.h"
#include "Scene/scene.h"


#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

int main() {

		//Creating window, shader and camera
	Window window("Arveto Engine -- Testing");

	window.init();
	window.printInfos();


	Shader shader1("modelShader", "lightShader");
	Camera camera1(glm::vec3(0.0f, 0.0f,  0.0f));
	camera1.movSpeed = 1.0;


	/************************************************************************************************/

			//Load model

	Model model1("Zero Suit Samus/DolSzerosuitR1.obj");
	Shape shape1(SQUARE);


	/************************************************************************************************/

		// Creating and binding transformations matrices to our shader
		// View matrix is managed by the camera (see below)

	shader1.use();
	glm::mat4 projectionMatrix = glm::mat4(1.0f);
	projectionMatrix = glm::perspective(glm::radians(60.0f), (float)window.getWidth() / (float)window.getHeight(), 0.1f, 1000.0f);

	shader1.setProjectionMatrix(projectionMatrix);
	shader1.setViewMatrix(camera1.setView());

	glEnable(GL_DEPTH_TEST);

	/************************************************************************************************/

		//Scene creation

	Scene scene(&shader1, &camera1);
	scene.bindElement(&model1);
	scene.bindElement(&shape1);

	window.bindScene(&scene);

	model1.position = glm::vec3(3.0f, -1.0f, 0.0f);
	model1.scale = glm::vec3(0.8f, 0.8f, 0.8f);

	/************************************************************************************************/

		//Game loop

	while ( !window.shouldClose() ) {

		// Input management
		window.refresh();
		window.pollEvents();
		scene.render();

	}

}
