#include <SDL2/SDL.h>
#include <stdlib.h>
#include "Display.h"

int main(int argc, char** argv)
{
	Display::setWidth(640);
	Display::setHeight(480);
	Display::get();

	bool running = true;

	while(running)
	{
		SDL_Event e;
		while(SDL_PollEvent(&e))
		{
			if(e.type == SDL_QUIT)
			{
				running = false;
			}
		}
		Display::get().update();
	}

	return 0;
}
