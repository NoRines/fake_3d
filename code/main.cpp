#include <SDL2/SDL.h>
#include "Display.h"
#include "Graphics/FrameBuffers/RenderContext.h"

#include <iostream>

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

void drawMap_2d(
	RenderContext& renderContext,
	float playerX, float playerY,
	float dirX, float dirY);
float castRayInMap(float playerX, float playerY, float dirX, float dirY);

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
	float dirX = 1.0f;
	float dirY = 0.0f;
	float playerX = 3.0f;
	float playerY = 3.0f;

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

		if(left)
		{
			float newDirX = cos(-0.05f)*dirX - sin(-0.05f)*dirY;
			float newDirY = sin(-0.05f)*dirX + cos(-0.05f)*dirY;
			dirX = newDirX;
			dirY = newDirY;
		}
		if(right)
		{
			float newDirX = cos(0.05f)*dirX - sin(0.05f)*dirY;
			float newDirY = sin(0.05f)*dirX + cos(0.05f)*dirY;
			dirX = newDirX;
			dirY = newDirY;
		}
		if(up)
		{
			playerX += 0.06f * dirX;
			playerY += 0.06f * dirY;
		}
		screenBitmap.clear(0xFF0000FF);
		drawMap_2d
		(
			screenBitmap,
			playerX, playerY,
			dirX, dirY
		);
		Display::get().update(screenBitmap);
	}

	return 0;
}

float castRayInMap(float playerX, float playerY, float dirX, float dirY)
{
	if(dirX < 0.001f && dirX > -0.001f)
	{
		dirX += 0.001f;
	}
	if(dirY < 0.001f && dirY > -0.001f)
	{
		dirY += 0.001f;
	}

	const float xUnitDist = sqrt(1 + ((dirY*dirY) / (dirX*dirX)));
	const float yUnitDist = sqrt(1 + ((dirX*dirX) / (dirY*dirY)));

	float xDist = 0.0f;
	float yDist = 0.0f;

	int mapX = (int)playerX;
	int mapY = (int)playerY;

	int stepX = 0;
	int stepY = 0;

	if(dirX > 0)
	{
		stepX = 1;
		xDist = ((float)(mapX + 1) - playerX) * xUnitDist;
	}
	else
	{
		stepX = -1;
		xDist = (playerX - (float)(mapX)) * xUnitDist;
	}

	if(dirY > 0)
	{
		stepY = 1;
		yDist = ((float)(mapY + 1) - playerY) * yUnitDist;
	}
	else
	{
		stepY = -1;
		yDist = (playerY - (float)(mapY)) * yUnitDist;
	}

	bool hitWall = false;
	int side = 1;
	while(!hitWall)
	{
		if(xDist < yDist)
		{
			xDist += xUnitDist;
			mapX += stepX;
			side = 0;
		}
		else
		{
			yDist += yUnitDist;
			mapY += stepY;
			side = 1;
		}
		if(map[mapX + MAP_SIZE*mapY] != 0)
		{
			hitWall = true;
		}
	}

	return (side == 0) ? (xDist-xUnitDist) : (yDist-yUnitDist);
}

void drawMap_2d(
	RenderContext& renderContext,
	float playerX, float playerY,
	float dirX, float dirY)
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
	#define screen_coords_x(X) \
		((X / MAP_SIZE) * DISPLAY_WIDTH)
	#define screen_coords_y(Y) \
		((Y / MAP_SIZE) * DISPLAY_HEIGHT)

	float distToWall = castRayInMap(playerX, playerY, dirX, dirY);

	renderContext.drawLine(0xFF00FF00,
		screen_coords_x(playerX), screen_coords_y(playerY),
		screen_coords_x(playerX) + screen_coords_x(dirX * distToWall),
		screen_coords_y(playerY) + screen_coords_y(dirY * distToWall));

	renderContext.drawLine(0xFF00FF00,
		screen_coords_x(playerX), screen_coords_y(playerY),
		screen_coords_x(playerX) - dirY * 10,
		screen_coords_y(playerY) + dirX * 10);
	renderContext.drawLine(0xFF00FF00,
		screen_coords_x(playerX), screen_coords_y(playerY),
		screen_coords_x(playerX) + dirY * 10,
		screen_coords_y(playerY) - dirX * 10);
}
