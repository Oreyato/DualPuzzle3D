#pragma once
#include <SDL.h>

#include "Consts.h"


const int WINDOW_WIDTH = Consts::Screen::WIDTH;
const int WINDOW_HEIGHT = Consts::Screen::HEIGHT;

class Window
{
public:
	Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	bool initialize();
	void close();

	SDL_Window* getSDLWindow() const { return SDLWindow; }
	int getWidth() const { return width; }
	int getHeight() const { return height; }

private:
	SDL_Window* SDLWindow;
	int width;
	int height;
};

