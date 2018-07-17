
#pragma once

#include <string>
#include <glad/glad.h>
#include <SDL2/SDL.h>

#include "../Camera/camera.h"

class Window{
	private:
		std::string title = "Arveto Engine";
		bool fullscreen = false;

		int width = 1000;
		int height = 600;

		SDL_Window *window;
		SDL_GLContext maincontext;

		bool closed = false;
		unsigned int refreshRate = 60; //(in Hz)

		Camera * camera = NULL;	//Binded Camera object for input management

	public:
		Window();
		Window(std::string title);
		Window(int w, int h);
		Window(std::string title, int w, int h);

		void printInfos() const;
		int getWidth() const;
		int getHeight() const;

		void init();
		void refresh();

		SDL_Event event;
		void pollEvents();
		bool shouldClose();

		unsigned int getRefreshRate();
		void setRefreshRate(unsigned int newRate);

		void bindCamera(Camera * camera);
};
