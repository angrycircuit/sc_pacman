#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string.h>	
#include "declaration.h"

// function declaration
int init();
void loadMedia();
void close();

// global definitions below

// each object's position, speed, and its hitbox's position and speed
struct ObjectMoveInfo pacmanMoveInfo = { 20, 20, 0, 0, {0, 0, PACMAN_WIDTH, PACMAN_HEIGHT} };

// containers
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

// textures
SDL_Texture* background;
SDL_Texture* pacmanTexture;

// the cutting parts from spritesheet
SDL_Rect pacmanClips[PACMAN_ANIMATION_FRAMES];

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
			handleEvent(&pacmanMoveInfo, &e);
		}

		// movement in each frame
		// the default refresh rate in SDL is 60Hz, beautiful!
		move(&pacmanMoveInfo, pacmanMoveInfo.hitBox, PACMAN_WIDTH, PACMAN_HEIGHT);

		// clear screen with white color
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		// render background, the map
		SDL_RenderCopy(gRenderer, background, NULL, NULL);

		// set pac's reder size
		// no matter what size of the pac image, it will be zoomed and rendered as 40 x 40, as long as the ratio is right
		SDL_Rect pacRenderQuad = { pacmanMoveInfo.posx, pacmanMoveInfo.posy, 40, 40 };

		// render current cutting part of pac
		SDL_Rect* currentClip = &pacmanClips[frame / 4];
		SDL_RenderCopy(gRenderer, pacmanTexture, currentClip, &pacRenderQuad);

		// update everything on screen once each loop
		SDL_RenderPresent(gRenderer);

		// every 4 frames animation change once
		++frame;
		if (frame / 4 >= PACMAN_ANIMATION_FRAMES)
			frame = 0;
	}



	//Free resources and close SDL
	close();

	return 0;
}

int init()
{
	// initialize video & audio
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Init(SDL_INIT_AUDIO);

	// initialize display container
	gWindow = SDL_CreateWindow( "Pacman", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	// initialize render color to white
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

	// initialize png if .png image is used
	SDL_Init(IMG_INIT_PNG);

	return 0;
}

void loadMedia()
{	
	// release resources 
	free(background);
	free(pacmanTexture);

	// load image to background container
	SDL_Surface* loadedSurface = IMG_Load("Source Files/map.jpg");
	background = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

	// load pac texture
	pacmanTexture = loadFromFile(gRenderer, "Source Files/pacmanSpriteSheet.jpg");

	// set spritesheet clips
	pacmanClips[0].x = 0;
	pacmanClips[0].y = 0;
	pacmanClips[0].w = PACMAN_WIDTH;
	pacmanClips[0].h = PACMAN_HEIGHT;

	pacmanClips[1].x = 160;
	pacmanClips[1].y = 0;
	pacmanClips[1].w = PACMAN_WIDTH;
	pacmanClips[1].h = PACMAN_HEIGHT;

	pacmanClips[2].x = 0;
	pacmanClips[2].y = 0;
	pacmanClips[2].w = PACMAN_WIDTH;
	pacmanClips[2].h = PACMAN_HEIGHT;

	pacmanClips[3].x = 0;
	pacmanClips[3].y = 0;
	pacmanClips[3].w = PACMAN_WIDTH;
	pacmanClips[3].h = PACMAN_HEIGHT;

}

void close()
{
	// free loaded resource
	free(background);
	free(pacmanTexture);

	// destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	// quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}





