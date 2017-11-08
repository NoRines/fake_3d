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
	float playerX = 200.0f;
	float playerY = 200.0f;

	bool up = false;
	bool left = false;
	bool right = false;

	constexpr int target_fps = 18;
	constexpr int target_frame_time = 1000/target_fps;

	int old_tick = SDL_GetTicks();

	bool running = true;

	while(running)
	{
		int current_tick = SDL_GetTicks();
		int frameTime = current_tick - old_tick;
		old_tick = current_tick;

		if(frameTime < target_frame_time)
		{
			SDL_Delay(target_frame_time - frameTime);
		}

		SDL_Event e;
		while(SDL_PollEvent(&e))
		{
			if(e.type == SDL_QUIT)
			{
				running = false;
			}
			if(e.type == SDL_KEYDOWN)
			{
				if(e.key.keysym.sym == SDLK_UP)
				{
					up = true;
				}
				if(e.key.keysym.sym == SDLK_LEFT)
				{
					left = true;
				}
				if(e.key.keysym.sym == SDLK_RIGHT)
				{
					right = true;
				}
			}
			if(e.type == SDL_KEYUP)
			{
				if(e.key.keysym.sym == SDLK_UP)
				{
					up = false;
				}
				if(e.key.keysym.sym == SDLK_LEFT)
				{
					left = false;
				}
				if(e.key.keysym.sym == SDLK_RIGHT)
				{
					right = false;
				}
			}
		}
		screenBitmap.clear(0xFF0000FF);
		screenBitmap.drawLine(0xFF00FF00,
			200, 200,
			200 + cos(angle + 1.57f) * 20,
			200 + sin(angle + 1.57f) * 20);
		screenBitmap.drawLine(0xFF00FF00,
			200, 200,
			200 + cos(angle - 1.57f) * 20,
			200 + sin(angle - 1.57f) * 20);
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
