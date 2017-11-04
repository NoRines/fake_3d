#include "Display.h"
#include <SDL2/SDL.h>
#include <iostream>

int Display::width = 0;
int Display::height = 0;

Display::Display(int width, int height, const char* title)
{
	// Starta sdl
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow
	(
		title,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width, height, 0
	);

	renderer = SDL_CreateRenderer
	(
		window, -1, 0
	);

	texture = SDL_CreateTexture
	(
		renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		width, height
	);

	// Skapa en buffer som vi kan skriva till
	screenBuffer = new unsigned char[width*height*4];
	bufferPitch = width * 4;
}

Display::~Display()
{
	// Rensa allt
	delete[] screenBuffer;
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Display::update()
{
	SDL_UpdateTexture
	(
		texture, 0,
		screenBuffer,
		bufferPitch
	);
	SDL_RenderCopy(renderer, texture, 0, 0);
	SDL_RenderPresent(renderer);
}

Display& Display::get()
{
	static Display instance(width, height, "SDL window");
	return instance;
}

void Display::setWidth(int width)
{
	if(!Display::width)
	{
		Display::width = width;
	}
}

void Display::setHeight(int height)
{
	if(!Display::height)
	{
		Display::height = height;
	}
}


