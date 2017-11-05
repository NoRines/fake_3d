#ifndef DISPLAY_H
#define DISPLAY_H

#include "Graphics/FrameBuffers/Bitmap.h"

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

class Display
{
private:
	Display(int width, int height, const char* title);
	~Display();

public:
	void update(const Bitmap& bitmap);

	Display() = delete;
	Display(const Display& display) = delete;
	Display(Display&& display) = delete;
	Display& operator=(const Display& display) = delete;
	Display& operator=(Display&& display) = delete;

	static Display& get();
	static void setWidth(int width);
	static void setHeight(int height);
	static int getWidth();
	static int getHeight();

private:
	static int width;
	static int height;

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
};

#endif
