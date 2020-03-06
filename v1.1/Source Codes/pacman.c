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

	struct Obstacles CantPass[100] = {0};

	//right wall maze
	CantPass[0].posy = 275;
	CantPass[0].posx = 150;
	CantPass[1].posy = 170;
	CantPass[1].posx = 150;
	CantPass[2].posy = 300;
	CantPass[2].posx = 150;
	CantPass[3].posy = 380;
	CantPass[3].posx = 150;
	CantPass[4].posy = 450;
	CantPass[4].posx = 60;
	CantPass[5].posy = 485;
	CantPass[5].posx = 60;

	//upper wall
	CantPass[6].posx = 300;
	CantPass[6].posy = 100;
	CantPass[7].posx = 320;
	CantPass[7].posy = 100;

	//left wall maze
	CantPass[8].posx = 480;
	CantPass[8].posy = 285;
	CantPass[9].posx = 480;
	CantPass[9].posy = 180;
	CantPass[10].posx = 490;
	CantPass[10].posy = 300;
	CantPass[11].posx = 490;
	CantPass[11].posy = 380;
	CantPass[12].posx = 540;
	CantPass[12].posy = 450;
	CantPass[13].posx = 540;
	CantPass[13].posy = 485;

	//vertical walls
	CantPass[14].posy = 75;
	CantPass[14].temp = 85;
	CantPass[14].posx = 70;
	CantPass[15].posy = 140;
	CantPass[15].temp = 230;
	CantPass[15].posx = 180;
	CantPass[16].posy = 75;
	CantPass[16].temp = 85;
	CantPass[16].posx = 170;
	CantPass[17].posy = 75;
	CantPass[17].temp = 85;
	CantPass[17].posx = 150;
	CantPass[18].posy = 75;
	CantPass[18].temp = 85;
	CantPass[18].posx = 280;
	CantPass[19].posy = 290;
	CantPass[19].temp = 345;
	CantPass[19].posx = 170;
	CantPass[20].posy = 395;
	CantPass[20].temp = 430;
	CantPass[20].posx = 120;
	CantPass[21].posy = 190;
	CantPass[21].temp = 230;
	CantPass[21].posx = 140;
	CantPass[22].posy = 290;
	CantPass[22].temp = 340;
	CantPass[22].posx = 140;
	CantPass[23].posy = 450;
	CantPass[23].temp = 480;
	CantPass[23].posx = 180;
	CantPass[24].posy = 140;
	CantPass[24].temp = 230;
	CantPass[24].posx = 200;
	CantPass[25].posy = 75;
	CantPass[25].temp = 85;
	CantPass[25].posx = 550;
	CantPass[26].posy = 75;
	CantPass[26].temp = 85;
	CantPass[26].posx = 470;
	CantPass[27].posy = 75;
	CantPass[27].temp = 85;
	CantPass[27].posx = 450;
	CantPass[28].posy = 75;
	CantPass[28].temp = 85;
	CantPass[28].posx = 350;
	CantPass[29].posy = 140;
	CantPass[29].temp = 230;
	CantPass[29].posx = 450;
	CantPass[30].posy = 140;
	CantPass[30].temp = 230;
	CantPass[30].posx = 410;
	CantPass[31].posy = 290;
	CantPass[31].temp = 345;
	CantPass[31].posx = 470;
	CantPass[32].posy = 180;
	CantPass[32].temp = 245;
	CantPass[32].posx = 470;
	CantPass[33].posy = 290;
	CantPass[33].temp = 345;
	CantPass[33].posx = 440;
	CantPass[34].posy = 450;
	CantPass[34].temp = 465;
	CantPass[34].posx = 435;
	CantPass[35].posy = 390;
	CantPass[35].temp = 425;
	CantPass[35].posx = 465;
	CantPass[36].posy = 140;
	CantPass[36].temp = 190;
	CantPass[36].posx = 290;
	CantPass[37].posy = 360;
	CantPass[37].temp = 390;
	CantPass[37].posx = 300;
	CantPass[38].posy = 460;
	CantPass[38].temp = 490;
	CantPass[38].posx = 300;
	CantPass[39].posy = 240;
	CantPass[39].temp = 290;
	CantPass[39].posx = 230;
	CantPass[40].posy = 240;
	CantPass[40].temp = 290;
	CantPass[40].posx = 380;

	//horizontal walls
	CantPass[41].posx = 75;
	CantPass[41].temp = 95;
	CantPass[41].posy = 75;
	CantPass[42].posx = 180;
	CantPass[42].temp = 220;
	CantPass[42].posy = 75;
	CantPass[43].posx = 470;
	CantPass[43].temp = 510;
	CantPass[43].posy = 75;
	CantPass[44].posx = 360;
	CantPass[44].temp = 410;
	CantPass[44].posy = 75;
	CantPass[45].posx = 90;
	CantPass[45].temp = 95;
	CantPass[45].posy = 145;
	CantPass[46].posx = 470;
	CantPass[46].temp = 485;
	CantPass[46].posy = 145;
	CantPass[47].posx = 240;
	CantPass[47].temp = 345;
	CantPass[47].posy = 145;
	CantPass[48].posx = 180;
	CantPass[48].temp = 220;
	CantPass[48].posy = 200;
	CantPass[49].posx = 360;
	CantPass[49].temp = 400;
	CantPass[49].posy = 200;
	CantPass[50].posx = 230;
	CantPass[50].temp = 350;
	CantPass[50].posy = 240;
	CantPass[51].posx = 230;
	CantPass[51].temp = 350;
	CantPass[51].posy = 330;
	CantPass[52].posx = 230;
	CantPass[52].temp = 350;
	CantPass[52].posy = 350;
	CantPass[53].posx = 230;
	CantPass[53].temp = 350;
	CantPass[53].posy = 450;
	CantPass[54].posx = 180;
	CantPass[54].temp = 220;
	CantPass[54].posy = 400;
	CantPass[55].posx = 80;
	CantPass[55].temp = 100;
	CantPass[55].posy = 400;
	CantPass[56].posx = 350;
	CantPass[56].temp = 390;
	CantPass[56].posy = 400;
	CantPass[57].posx = 470;
	CantPass[57].temp = 500;
	CantPass[57].posy = 400;
	CantPass[58].posx = 370;
	CantPass[58].temp = 500;
	CantPass[58].posy = 495;
	CantPass[59].posx = 80;
	CantPass[59].temp = 220;
	CantPass[59].posy = 495;


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

		move(&pacmanMoveInfo, pacmanMoveInfo.hitBox, PACMAN_WIDTH, PACMAN_HEIGHT, CantPass);

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





