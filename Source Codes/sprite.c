/* this is for displaying the pacman and monster sprite */
#include "pacman.h"

SDL_Rect pacmanClips[PACMAN_ANIMATION_FRAMES];
SDL_Rect blinkyClips;	// will be an array if animation applied

void setSprite()
{
	// set display area in the texture for ghosts
	// ==========================================
	
	// will rewrite into an array
	blinkyClips.x = 0;
	blinkyClips.y = 130;
	blinkyClips.w = GHOST_TEXTURE_WIDTH;
	blinkyClips.h = GHOST_TEXTURE_HEIGHT;

	// set display area in the texture for pac
	// =======================================
	for (int i = 0; i < PACMAN_ANIMATION_FRAMES; i++)
	{
		pacmanClips[i].y = 0;
		pacmanClips[i].w = PACMAN_TEXTURE_WIDTH;
		pacmanClips[i].h = PACMAN_TEXTURE_HEIGHT;
	}

	pacmanClips[0].x = 0;	
	pacmanClips[1].x = 140;
	pacmanClips[2].x = 140;
	pacmanClips[3].x = 140;
	pacmanClips[4].x = 140;
	pacmanClips[5].x = 140;
}