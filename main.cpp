
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Window/window.h"
#include "Shader/shader.h"
#include "Camera/camera.h"
#include "Model/model.h"
#include "Scene/scene.h"


#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

int main() {

		//Creating window, shader and camera
	Window window("Arveto Engine -- Testing");

	window.init();
	window.printInfos();


	Shader shader1("modelShader", "modelShader");
	Camera camera1(glm::vec3(0.0f, 0.0f,  3.0f));


	/************************************************************************************************/

			//Load model

	Model model1("gamejam_trump/scene.gltf");
	Model model2("houses_pokrovskoe_streshnevo/scene.gltf");


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
	scene.bindModel(&model1);
	scene.bindModel(&model2);

	window.bindScene(&scene);

	model1.position = glm::vec3(0.0f, 0.0f, 0.0f);
	model1.rotationAngle = -90.0f;
	model1.rotationVec = glm::vec3(1.0f, 0.0f, 0.0f);
	model1.scale = glm::vec3(1.5f, 1.5f, 1.5f);

	model2.position = glm::vec3(28.0f, 15.7f, -13.0f);
	model2.rotationAngle = 180.0f;
	model2.rotationVec = glm::vec3(1.0f, 0.0f, 0.0f);
	/************************************************************************************************/

		//Game loop

	while ( !window.shouldClose() ) {

		// Input management
		window.refresh();
		window.pollEvents();
		scene.render();

	}

}
