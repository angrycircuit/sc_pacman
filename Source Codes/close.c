// this is for releasing resourses and closing
#include "pacman.h"

// release the texture
void free(SDL_Texture* texture)
{
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
	}
}

// terminate the program
void close(SDL_Texture* background, SDL_Texture* charactersTexture, SDL_Renderer* gRenderer, SDL_Window* gWindow)
{
	// release textures
	free(background);
	free(charactersTexture);

	// destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	// quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}