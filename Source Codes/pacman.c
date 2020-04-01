#define _CRT_SECURE_NO_WARNINGS

#include "pacman.h"

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern SDL_Texture* background;
extern SDL_Texture* charactersTexture;
extern struct ObjectMoveInfo objectMoveInfo[CHARACTER_NUMBER];

// SDL regulates the parameters of main must be like this
int main(int argc, char* args[])
{
	init(&objectMoveInfo);

	SDL_Event e;		//Event handler
	int couter = 0;		// loop couter
	int quit = 0;		// termination flag
	

	// main loop
	while (!quit)
	{
		// handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			// user requests quit
			if (e.type == SDL_QUIT)
				quit = 1;

			// key listener
			handleEvent(&objectMoveInfo, &e);
		}

		// every 4 loops animation change once
		++couter;
		if (couter / 6 >= PACMAN_ANIMATION_FRAMES)
			couter = 0;

		// behaviors of eating / catching
		updateWithoutInput();

		// refresh the display every loop
		update(&objectMoveInfo, couter);
	}

	//Free resources and close SDL
	close(&background, &charactersTexture, &gRenderer, &gWindow);

	return 0;
}







