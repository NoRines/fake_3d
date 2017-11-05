#include <SDL2/SDL.h>
#include "Display.h"
#include "Graphics/FrameBuffers/Bitmap.h"

#include <utility>

int main(int argc, char** argv)
{
	constexpr int DISPLAY_WIDTH = 640;
	constexpr int DISPLAY_HEIGHT = 480;

	Display::setWidth(DISPLAY_WIDTH);
	Display::setHeight(DISPLAY_HEIGHT);
	Display::get();

	Bitmap screenBitmap(Display::getWidth(), Display::getHeight());
	screenBitmap.clear(0xFF0000FF);

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
		Display::get().update(screenBitmap);
	}

	return 0;
}
