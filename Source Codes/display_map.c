/* this is for displaying the playing map */

#include "pacman.h"

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern SDL_Texture* background;
extern SDL_Texture* charactersTexture;
extern SDL_Rect pacmanClips[PACMAN_ANIMATION_FRAMES];
extern SDL_Rect blinkyClips;	// will be an array if animation applied
extern map[31][28];
extern SDL_Rect dots[TOTALDOTS];
extern SDL_Rect energizer[TOTALENERGIZE];

// refresh the display every loop
void update(struct ObjectMoveInfo* objectMoveInfo, int couter) {
	// pacman's movement in each frame
	// the default refresh rate in SDL is based on the monitor the player have

	move(&objectMoveInfo[PACMAN], objectMoveInfo[PACMAN].hitBox, PACMAN_RENDER_WIDTH, PACMAN_RENDER_HEIGHT);

	// clear screen with white color
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);

	// render background, the map
	SDL_RenderCopy(gRenderer, background, NULL, NULL);

	// set pac's reder size
	// no matter what size of the pac image, it will be zoomed and rendered as 40 x 40, as long as the ratio is right
	SDL_Rect pacRenderQuad = { objectMoveInfo[PACMAN].posx + 2, objectMoveInfo[PACMAN].posy + 2, PACMAN_RENDER_WIDTH, PACMAN_RENDER_HEIGHT };

	// set ghosts' render size
	SDL_Rect blinkyRenderQuad = { objectMoveInfo[BLINKY].posx, objectMoveInfo[BLINKY].posy, GHOST_RENDER_WIDTH, GHOST_RENDER_HEIGHT };

	// set clip containers
	SDL_Rect* currentClip[CHARACTER_NUMBER];
	currentClip[PACMAN] = &pacmanClips[couter / 6];
	currentClip[BLINKY] = &blinkyClips;

	// render characters
	// render pac
	SDL_RenderCopyEx(gRenderer, charactersTexture, currentClip[PACMAN], &pacRenderQuad, objectMoveInfo[PACMAN].degree, NULL, SDL_FLIP_NONE);
	// render red ghost
	SDL_RenderCopyEx(gRenderer, charactersTexture, currentClip[BLINKY], &blinkyRenderQuad, 0.0, NULL, SDL_FLIP_NONE);

	renderDots();

	// update everything on screen once each loop
	SDL_RenderPresent(gRenderer);


}

void renderDots()
{
	SDL_Rect dotsQuad = { 0, 260, 20, 20 };

	int i, j;
	int dotsCounter = 0, energizerCounter = 0;

	for (i = 0; i < 31; i++)
	{
		for (j = 0; j < 28; j++)
		{
			if (map[i][j] == 0)
			{
				// render dots
				SDL_RenderCopy(gRenderer, charactersTexture, &dotsQuad, &dots[dotsCounter]);
				dotsCounter++;
			}				
			else if (map[i][j] == 10)
			{
				// render energizes
				SDL_RenderCopy(gRenderer, charactersTexture, &dotsQuad, &energizer[energizerCounter]);
				energizerCounter++;
			}
		}
	}
}

