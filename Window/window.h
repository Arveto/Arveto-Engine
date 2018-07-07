
#pragma once

#include <string>
#include <glad/glad.h>
#include <SDL2/SDL.h>

class Window{
	private:
		std::string title = "Arveto Engine";
		bool fullscreen = false;

		int width = 1000;
		int height = 600;

		SDL_Window *window;
		SDL_GLContext maincontext;

		SDL_Event event;
		bool closed = false;

		unsigned int refreshRate = 60; //(in Hz)

	public:
		Window();
		Window(std::string title);
		Window(int w, int h);
		Window(std::string title, int w, int h);

		void printInfos();

		void init();
		void refresh();

		void pollEvents();
		bool shouldClose();

		void setRefreshRate(unsigned int newRate);
};
