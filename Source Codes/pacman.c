#define _CRT_SECURE_NO_WARNINGS

#include "pacman.h"

// function declaration
int init();
void loadMedia();
void close();

// global definitions below

// each object's position, speed, and its hitbox's position and speed
struct ObjectMoveInfo objectMoveInfo[CHARACTER_NUMBER];


// SDL regulates the parameters of main must be like this
int main(int argc, char* args[])
{
	init();
	loadMedia();
	int quit = 0;

	//Event handler
	SDL_Event e;

	// current frame
	int frame = 0;

	//Set the wall
	/*SDL_Rect wall;
	wall.x = 300;
	wall.y = 40;
	wall.w = 40;
	wall.h = 400;*/
	
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

		update(&objectMoveInfo, frame);

	}

	//Free resources and close SDL
	close();

	return 0;
}







