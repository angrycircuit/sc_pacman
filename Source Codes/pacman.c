#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string.h>	
#include "declaration.h"

// function declaration
int init();
void loadMedia();
void close();

// global definition
struct ObjectMoveInfo pacmanMoveInfo = { 20, 20, 0, 0, {0, 0, PACMAN_WIDTH, PACMAN_HEIGHT} };

// containers
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

// textures
SDL_Texture* background;
SDL_Texture* pacmanTexture;

SDL_Rect pacmanClips[PACMAN_ANIMATION_FRAMES];


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
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
				quit = 1;
			handleEvent(&pacmanMoveInfo, &e);
		}

		move(&pacmanMoveInfo, pacmanMoveInfo.hitBox, PACMAN_WIDTH, PACMAN_HEIGHT);

		//Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		/*SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderDrawRect(gRenderer, &wall);*/

		// render background
		SDL_RenderCopy(gRenderer, background, NULL, NULL);

		// set pacman render port
		SDL_Rect pacRenderQuad = { pacmanMoveInfo.posx, pacmanMoveInfo.posy, 40, 40 };

		// render current clip
		SDL_Rect* currentClip = &pacmanClips[frame / 4];
		SDL_RenderCopy(gRenderer, pacmanTexture, currentClip, &pacRenderQuad);

		//Update screen
		SDL_RenderPresent(gRenderer);

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

	// initialize render color
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

	// initialize png
	SDL_Init(IMG_INIT_PNG);

	return 0;
}

void loadMedia()
{	
	// resources release
	free(background);
	free(pacmanTexture);

	// load background
	SDL_Surface* loadedSurface = IMG_Load("Source Files/map.jpg");
	background = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

	// load pacman texture
	pacmanTexture = loadFromFile(gRenderer, "Source Files/pacmanSpriteSheet.jpg");

	// set sprite clips
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





