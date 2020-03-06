#define _CRT_SECURE_NO_WARNGINGS

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
struct ObjectMoveInfo objectMoveInfo[CHARACTER_NUMBER];

// containers
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

// textures
SDL_Texture* background;
SDL_Texture* charactersTexture;

// the cutting parts from spritesheet
SDL_Rect pacmanClips[PACMAN_ANIMATION_FRAMES];
SDL_Rect blinkyClips;	// will be an array if animation applied

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

		// pacman's movement in each frame
		// the default refresh rate in SDL is 60Hz, beautiful!
		move(&objectMoveInfo[PACMAN], objectMoveInfo[PACMAN].hitBox, PACMAN_RENDER_WIDTH, PACMAN_RENDER_HEIGHT);

		// clear screen with white color
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		// render background, the map
		SDL_RenderCopy(gRenderer, background, NULL, NULL);

		// set pac's reder size
		// no matter what size of the pac image, it will be zoomed and rendered as 40 x 40, as long as the ratio is right
		SDL_Rect pacRenderQuad = { objectMoveInfo[PACMAN].posx, objectMoveInfo[PACMAN].posy, PACMAN_RENDER_WIDTH, PACMAN_RENDER_HEIGHT };

		// set ghosts' render size
		SDL_Rect blinkyRenderQuad = {objectMoveInfo[BLINKY].posx, objectMoveInfo[BLINKY].posy, GHOST_RENDER_WIDTH, GHOST_RENDER_HEIGHT };

		// set clip containers
		SDL_Rect* currentClip[CHARACTER_NUMBER];
		currentClip[PACMAN] = &pacmanClips[frame / 6];
		currentClip[BLINKY] = &blinkyClips;

		// render current cutting part of characters
		// render pac
		SDL_RenderCopyEx(gRenderer, charactersTexture, currentClip[PACMAN], &pacRenderQuad, objectMoveInfo[PACMAN].degree, NULL, SDL_FLIP_NONE);
		// render red baby
		SDL_RenderCopyEx(gRenderer, charactersTexture, currentClip[BLINKY], &blinkyRenderQuad, 0.0, NULL, SDL_FLIP_NONE);

		// update everything on screen once each loop
		SDL_RenderPresent(gRenderer);

		// every 4 frames animation change once
		++frame;
		if (frame / 6 >= PACMAN_ANIMATION_FRAMES)
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

	// initialize characters' moving information
	// -----------------------------------------
									  //coordinates
	initMoveInfo(&objectMoveInfo[PACMAN], 20, 20, PACMAN_RENDER_WIDTH, PACMAN_RENDER_HEIGHT);
	initMoveInfo(&objectMoveInfo[BLINKY], 275, 280, GHOST_RENDER_WIDTH, GHOST_RENDER_HEIGHT);

	return 0;
}

void loadMedia()
{	
	// release resources 
	free(background);
	free(charactersTexture);

	// load image to background container
	SDL_Surface* loadedSurface = IMG_Load("Source Files/map.jpg");
	background = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

	// load texture
	charactersTexture = loadFromFile(gRenderer, "Source Files/characters.jpg");

	// set display area in the texture for ghosts
	// ------------------------------------------
	// will be encapsulated within a function

	// will rewrite to an array
	blinkyClips.x = 0;
	blinkyClips.y = 130;
	blinkyClips.w = GHOST_TEXTURE_WIDTH;
	blinkyClips.h = GHOST_TEXTURE_HEIGHT;

	// set display area in the texture for pac
	pacmanClips[0].x = 0;
	pacmanClips[0].y = 0;
	pacmanClips[0].w = PACMAN_TEXTURE_WIDTH;
	pacmanClips[0].h = PACMAN_TEXTURE_HEIGHT;

	pacmanClips[1].x = 140;
	pacmanClips[1].y = 0;
	pacmanClips[1].w = PACMAN_TEXTURE_WIDTH;
	pacmanClips[1].h = PACMAN_TEXTURE_HEIGHT;

	pacmanClips[2].x = 140;
	pacmanClips[2].y = 0;
	pacmanClips[2].w = PACMAN_TEXTURE_WIDTH;
	pacmanClips[2].h = PACMAN_TEXTURE_HEIGHT;

	pacmanClips[3].x = 140;
	pacmanClips[3].y = 0;
	pacmanClips[3].w = PACMAN_TEXTURE_WIDTH;
	pacmanClips[3].h = PACMAN_TEXTURE_HEIGHT;

	pacmanClips[4].x = 140;
	pacmanClips[4].y = 0;
	pacmanClips[4].w = PACMAN_TEXTURE_WIDTH;
	pacmanClips[4].h = PACMAN_TEXTURE_HEIGHT;

	pacmanClips[5].x = 140;
	pacmanClips[5].y = 0;
	pacmanClips[5].w = PACMAN_TEXTURE_WIDTH;
	pacmanClips[5].h = PACMAN_TEXTURE_HEIGHT;

}

void close()
{
	// free loaded resources
	free(background);
	free(charactersTexture);

	// destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	// quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}







