
#include <iostream>
#include "window.h"
#include "../Logger/logger.h"



	//Constructors
Window::Window() {}

Window::Window(std::string title) : title(title) {}

Window::Window(int w, int h) : width(w), height(h) {}

Window::Window(std::string title, int w, int h)
			: title(title), width(w), height(h) {}



	//Initialize screen
void Window::init(){

			// SDL : initialize
		/****************************/

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		log("WINDOW::Init		Couldn't initialize SDL");

	atexit (SDL_Quit);
	SDL_GL_LoadLibrary(NULL);	//No extensions

	// Get OpenGL context
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);


			// SDL : create the window
		/*********************************/
	if (fullscreen) {
		window = SDL_CreateWindow(
			title.c_str(),
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL
		);
	} else {
		window = SDL_CreateWindow(
			title.c_str(),
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			width, height, SDL_WINDOW_OPENGL
		);
	}

	if (window == NULL)
		log("WINDOW::Init		Couldn't set video mode");

	maincontext = SDL_GL_CreateContext(window);
	if (maincontext == NULL)
		log("WINDOW::Init		Failed to create OpenGL context");


			//GLAD : Load OpenGL functions
		/*************************************/

	gladLoadGLLoader(SDL_GL_GetProcAddress);
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	// Use v-sync, not an engine for pussys here
	SDL_GL_SetSwapInterval(1);
	// Disable depth test and face culling.
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	int w,h;
	SDL_GetWindowSize(window, &w, &h);
	glViewport(0, 0, w, h);
	glClearColor(0.0f, 0.5f, 1.0f, 0.0f);
}


void Window::printInfos() const{
	std::cout << "OpenGL loaded" << std::endl;
	std::cout << "Vendor:   " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "Version:  " << glGetString(GL_VERSION) << std::endl;
}



int Window::getWidth() const{
	return width;
}



int Window::getHeight() const{
	return height;
}



void Window::refresh(){
    SDL_GL_SwapWindow(window);
	SDL_Delay(1000/refreshRate);
}



void Window::pollEvents(){
	SDL_PollEvent(&event);

	if (event.type == SDL_QUIT)
		closed = true;
}



bool Window::shouldClose(){
	return closed;
}



void Window::setRefreshRate(unsigned int newRate){
	refreshRate = newRate;
}
