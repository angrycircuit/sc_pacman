#include "pacman.h"

extern struct ObjectMoveInfo objectMoveInfo[CHARACTER_NUMBER];
extern SDL_Rect dots[TOTALDOTS];
extern SDL_Rect energizer[TOTALENERGIZE];

// sequences after eating dots
void updateWithoutInput()
{
	int i;
	for (i = 0; i < TOTALDOTS; i++)
		if (checkCollision(objectMoveInfo[PACMAN].eatDots, dots[i]))
			dots[i].w = 0;
	for (i = 0; i < TOTALENERGIZE; i++)
		if (checkCollision(objectMoveInfo[PACMAN].eatDots, energizer[i]))
			energizer[i].w = 0;
		
}