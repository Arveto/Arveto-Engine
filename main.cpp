
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


	/************************************************************************************************/

		// Creating and binding transformations matrices to our shader
		// View matrix is managed by the camera (see below)

		shader1.use();

		glm::mat4 modelMatrix = glm::mat4(1.0f);;
		glm::mat4 projectionMatrix = glm::mat4(1.0f);;

		modelMatrix = glm::rotate(modelMatrix, glm::radians(-90.0f), glm::vec3(0.5f, 0.5f, 0.0f));	//Model coords

		projectionMatrix = glm::perspective(glm::radians(60.0f), (float)window.getWidth() / (float)window.getHeight(), 0.1f, 100.0f);

		shader1.setModelMatrix(modelMatrix);
		shader1.setProjectionMatrix(projectionMatrix);
		shader1.setViewMatrix(camera1.setView());

		glEnable(GL_DEPTH_TEST);

	/************************************************************************************************/

		//Scene creation

		Scene scene(&shader1, &camera1);
		scene.bindModel(&model1);

		window.bindScene(&scene);
	/************************************************************************************************/


		//Game loop

	while ( !window.shouldClose() ) {

		// Input management
		window.refresh();
		window.pollEvents();
		scene.render();

	}

}
