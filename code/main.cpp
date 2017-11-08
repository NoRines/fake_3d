#include <SDL2/SDL.h>
#include "Display.h"
#include "Graphics/FrameBuffers/RenderContext.h"

constexpr int DISPLAY_WIDTH = 640;
constexpr int DISPLAY_HEIGHT = 480;

constexpr int MAP_SIZE = 10;

// Test kod
static const uint8_t map[MAP_SIZE * MAP_SIZE] = 
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	  1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	  1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	  1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	  1, 0, 0, 0, 0, 0, 0, 1, 0, 1,
	  1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	  1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	  1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	  1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	  1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

void drawMap_2d(RenderContext& renderContext);

int main(int argc, char** argv)
{
	// Set the display values
	Display::setWidth(DISPLAY_WIDTH);
	Display::setHeight(DISPLAY_HEIGHT);
	Display::get();

	// Create a bitmap that can be copied to the screen
	RenderContext screenBitmap(Display::getWidth(), Display::getHeight());
	screenBitmap.clear(0xFF0000FF);

	// lite test saker
	double angle = 0.0;

	bool running = true;

	while(running)
	{
		angle += 0.001;
		SDL_Event e;
		while(SDL_PollEvent(&e))
		{
			if(e.type == SDL_QUIT)
			{
				running = false;
			}
		}
		screenBitmap.clear(0xFF0000FF);
		screenBitmap.drawLine(0xFF00FF00,
			200, 200,
			200 + cos(angle) * 100,
			200 + sin(angle) * 100);
		drawMap_2d(screenBitmap);
		Display::get().update(screenBitmap);
	}

	return 0;
}

void drawMap_2d(RenderContext& renderContext)
{
	constexpr int cellW = DISPLAY_WIDTH / MAP_SIZE;
	constexpr int cellH = DISPLAY_HEIGHT / MAP_SIZE;

	for(int y = 0; y < MAP_SIZE; y++)
	{
		for(int x = 0; x < MAP_SIZE; x++)
		{
			if(map[x + y*MAP_SIZE])
			{
				for(int i = 0; i < cellW; i++)
				{
					renderContext.drawVerticalLine
					(
						0xFFFF0000,
						(x*cellW) + i,
						(y*cellH),
						((y+1)*cellH)
					);
				}
			}
		}
	}
}
