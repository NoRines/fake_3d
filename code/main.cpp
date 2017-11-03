#include <SDL2/SDL.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_EVERYTHING); // Sätter upp SDL

	SDL_Window* window = SDL_CreateWindow // Skapar ett fönster
	(
		"SDL window",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640, 480, 0
	);

	SDL_Renderer* renderer = SDL_CreateRenderer // Skapar en renderare
	(
		window, -1, 0
	);

	SDL_Texture* texture = SDL_CreateTexture // Skapar en textur
	(
		renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		640, 480
	);

	unsigned char screenBuffer[640*480*4]; // En buffer för alla pixlar
	int screenBufferPitch = 640*4;

	// Slumpa färger till alla pixlar
	for(int i = 0; i < 640*480*4; i++)
	{
		screenBuffer[i] = (unsigned char)(rand() % 256);
	}

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
		// Sätt texturen från en lista med pixel data
		SDL_UpdateTexture(
			texture, 0,
			screenBuffer, screenBufferPitch);
		// Kopiera texturen till renderaren
		SDL_RenderCopy(renderer, texture, 0, 0);
		// Presentera det som är renderaren
		SDL_RenderPresent(renderer);
	}

	// Tar bort allt
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}
