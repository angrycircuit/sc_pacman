#define _CRT_SECURE_NO_WARNINGS

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string.h>	
#include <stdlib.h>
#include <Windows.h>
#include <MMSystem.h>
#include <conio.h>
#include "pacman.h"
#include <math.h>

// import global vars
extern struct ObjectMoveInfo objectMoveInfo[CHARACTER_NUMBER];
extern map[31][28];
extern struct Tile tile[TOTALTILE];
extern struct MakeATurn makeaturn;

// key listener
void handleEvent(struct ObjectMoveInfo* object, SDL_Event* event)
{
    // if a key is pressed down
    if ((*event).type == SDL_KEYDOWN && (*event).key.repeat == 0)
    {
        switch ((*event).key.keysym.sym)
        {
        case SDLK_UP:
			// moving helper flag and info
			if (canMakeATurn(UP, object))
			{
				makeaturn.direction = UP;
				makeaturn.targetPosx = (object->inx + 1) * 20;
				makeaturn.targetPosy = object->iny * 20;
			}
			// moving helper flag and info
			if (canMoveToNextTile(UP, object) && (object->inx * 20 != object->posx))
			{
				makeaturn.direction = UP;
				makeaturn.targetPosx = object->inx * 20;
				makeaturn.targetPosy = object->iny * 20;
			}
			// default behavior, moving helper not involved
			if (makeaturn.direction == 0 || object->vely > 0)
				setDirection(UP, object);			
		break;

        case SDLK_DOWN: 			
			if (canMakeATurn(DOWN, object))
			{
				makeaturn.direction = DOWN;
				makeaturn.targetPosx = (object->inx + 1) * 20;
				makeaturn.targetPosy = object->iny * 20;
			}
			if (canMoveToNextTile(DOWN, object) && (object->inx * 20 != object->posx))
			{
				makeaturn.direction = DOWN;
				makeaturn.targetPosx = object->inx * 20;
				makeaturn.targetPosy = object->iny * 20;
			}
			if (makeaturn.direction == 0 || object->vely < 0)
				setDirection(DOWN, object);
		break;

        case SDLK_LEFT: 			
			if (canMakeATurn(LEFT, object))
			{
				makeaturn.direction = LEFT;
				makeaturn.targetPosx = object->inx * 20;
				makeaturn.targetPosy = (object->iny + 1) * 20;
			}
			if (canMoveToNextTile(LEFT, object) && (object->iny * 20 != object->posy))
			{
				makeaturn.direction = LEFT;
				makeaturn.targetPosx = object->inx * 20;
				makeaturn.targetPosy = object->iny * 20;
			}
			// int h = touchHorizontalWall(*object, tile, map);
			if (makeaturn.direction == 0 || (object->velx == 0 && object->vely == 0) || object->velx > 0)
				setDirection(LEFT, object);
		break;

        case SDLK_RIGHT: 			
			if (canMakeATurn(RIGHT, object))
			{
				makeaturn.direction = RIGHT;
				makeaturn.targetPosx = object->inx * 20;
				makeaturn.targetPosy = (object->iny + 1) * 20;
			}
			if (canMoveToNextTile(RIGHT, object) && (object->iny * 20 != object->posy))
			{
				makeaturn.direction = RIGHT;
				makeaturn.targetPosx = object->inx * 20;
				makeaturn.targetPosy = object->iny * 20;
			}
			if (makeaturn.direction == 0 || object->velx < 0)
				setDirection(RIGHT, object);
		break;
        }
    }
}

// move from right/top to left/bottom, can make a turn at current tile, and the distance to the turing point < 25
int canMoveToNextTile(const int keyDirection, struct ObjectMoveInfo* object)
{
	if (keyDirection == UP && (map[object->iny - 1][object->inx] == 0 || map[object->iny - 1][object->inx] >= 9) && object->velx <= 0 && object->posx - object->inx * 20 < 25)
		return 1;
	if (keyDirection == DOWN && (map[object->iny + 1][object->inx] == 0 || map[object->iny + 1][object->inx] >= 9 )&& object->velx <= 0 && object->posx - object->inx * 20 < 25)
		return 1;
	if (keyDirection == RIGHT && (map[object->iny][object->inx + 1] == 0 || map[object->iny][object->inx + 1] >= 9) && object->vely <= 0 && object->posy - object->iny * 20 < 25)
		return 1;
	if (keyDirection == LEFT && (map[object->iny][object->inx - 1] == 0 || map[object->iny][object->inx - 1] >= 9) && object->vely <= 0 && object->posy - object->iny * 20 < 25)
		return 1;
	return 0;
}

// move from left to right or from up to down, can make a turn at next turn, and the distance to the turning point < 25
int canMakeATurn(const int keyDirection, struct ObjectMoveInfo* object)
{
	if (keyDirection == UP && (map[object->iny - 1][object->inx + 1] == 0 || map[object->iny - 1][object->inx + 1] >= 9) && object->velx >= 0 && ((object->inx + 1) * 20 - object->posx < 25))
		return 1;
	if (keyDirection == DOWN && (map[object->iny + 1][object->inx + 1] == 0 || map[object->iny + 1][object->inx + 1] >= 9) && object->velx >= 0 && ((object->inx + 1) * 20 - object->posx < 25))
		return 1;
	if (keyDirection == RIGHT && (map[object->iny + 1][object->inx + 1] == 0 || map[object->iny + 1][object->inx + 1] >= 9) && object->vely >= 0 && ((object->iny + 1) * 20 - object->posy < 25))
		return 1;
	if (keyDirection == LEFT && (map[object->iny + 1][object->inx - 1] == 0 || map[object->iny + 1][object->inx - 1] >= 9) && object->vely >= 0 && ((object->iny + 1) * 20 - object->posy < 25))
		return 1;
	return 0;
}

// default behaior when key pressing detected
// change to the moving direction
// change degree in order to rotate the texture
void setDirection(const int direction, struct ObjectMoveInfo* object)
{
	switch (direction)
	{
	case UP: object->vely = -VELOCITY; object->velx = 0; object->degree = 0; break;
	case DOWN: object->vely = VELOCITY; object->velx = 0; object->degree = 180; break;
	case LEFT: object->velx = -VELOCITY; object->vely = 0; object->degree = -90; break;
	case RIGHT: object->velx= VELOCITY; object->vely = 0; object->degree = 90; break;
	}
}

// change object's current position every loop
// proceed to one type of moving pattern based on the flag
void move(struct ObjectMoveInfo* object, SDL_Rect targetHitBox, int objWidth, int objHeight)
{
	// moving helper
	// will help player make a turn to avoid stucking
	if (makeaturn.direction != 0)
		if (object->posx == makeaturn.targetPosx && object->posy == makeaturn.targetPosy)
		{
			setDirection(makeaturn.direction, object);
			makeaturn.direction = 0;
		}
	// default pattern
	regularMove(object, targetHitBox, objWidth, objHeight);
	
}

// change the object's position stored in ObjectMoveInfo to make it move
void regularMove(struct ObjectMoveInfo* object, SDL_Rect targetHitBox, int objWidth, int objHeight)
{
    // move the object left or right
    // plus a negative value means minus

	// new positions
    object->posx += object->velx;
	// new tile
	coordinateToIndex(object);
	// hitBoxes moves
    object->hitBox.x = object->posx;
	object->eatDots.x = object->posx + 20 - DOT_WIDTH / 2;

	if (object->posx < 0 - PACMAN_RENDER_WIDTH)
		object->posx = 580;
	if (object->posx > 580)
		object->posx = 0 - PACMAN_RENDER_WIDTH;

    // if there is a wall type tile
    if (touchVerticalWall(*object, tile, map))
    {
        // reset flag
		makeaturn.direction = 0;
		// this value has been changed before
		// will cancel the addition
        object->posx -= object->velx;
		coordinateToIndex(object);
        object->hitBox.x = object->posx;
		object->eatDots.x = object->posx + 20 - DOT_WIDTH / 2;
    }
    
    // move up or down
    object->posy += object->vely;
	coordinateToIndex(object);
    object->hitBox.y = object->posy;
	object->eatDots.y = object->posy + 20 - DOT_HEIGHT / 2;

    if (touchHorizontalWall(*object, tile, map))
    {
        // stop
		makeaturn.direction = 0;
        object->posy -= object->vely;
		coordinateToIndex(object);
        object->hitBox.y= object->posy;
		object->eatDots.y = object->posy + 20 - DOT_HEIGHT / 2;
    }
}

// Liam's work
// ===========

//Function for playing audio, accepts the file name as an arguement
void Audio(LPCWSTR filename)
{
	PlaySound((filename), NULL, SND_SYNC);

	system("pause");
}


// Function for playback of ASCII animation frames
void Animation(const char* filename)
{
#define CHUNK 1024 // Buffer size
	char buf[CHUNK];
	FILE* file;
	size_t nread;
	file = fopen(filename, "r");
	if (file)
	{
		while ((nread = fread(buf, 1, sizeof buf, file)) > 0)
			fwrite(buf, 1, nread, stdout);
		if (ferror(file))
		{
			printf("%s not found.", filename);
		}
		fclose(file);
	}
	Sleep(10);
	system("cls");
}

//Function for triggering the introduction sequence
void Introduction(void)
{
#define CHUNK 1024
	char buf[CHUNK];
	FILE* file;
	size_t nread;

	PlaySound(TEXT("PAC DEATH.wav"), NULL, SND_SYNC);

	// Show the ASCII pacman from file
	file = fopen("pm.txt", "r");
	if (file)
	{
		while ((nread = fread(buf, 1, sizeof buf, file)) > 0)
			fwrite(buf, 1, nread, stdout);
		if (ferror(file))
		{
			printf("pm.txt not found.");
		}
		fclose(file);
	}
	PlaySound(TEXT("IPC PACMAN THEME MASTER.wav"), NULL, SND_SYNC);
	system("cls");

	PlaySound(TEXT("BOOP 2.wav"), NULL, SND_SYNC);

	// Show the credits info from file
	file = fopen("credits.txt", "r");
	if (file)
	{
		while ((nread = fread(buf, 1, sizeof buf, file)) > 0)
			fwrite(buf, 1, nread, stdout);
		if (ferror(file))
		{
			printf("credits.txt not found.");
		}
		fclose(file);
	}
	Sleep(5000);
	system("cls");

	// Show the PacMan Animation from frames
	int i;
	for (i = 0; i < 4; i++)
	{
		Animation("pacani1.txt");
		Animation("pacani2.txt");
		Animation("pacani3.txt");
		Animation("pacani4.txt");
		Animation("pacani5.txt");
		Animation("pacani6.txt");
		Animation("pacani7.txt");
		Animation("pacani8.txt");
		Animation("pacani9.txt");
		Animation("pacani10.txt");
		Animation("pacani11.txt");
		Animation("pacani12.txt");
	}
}

// Soundtest Mode, logic for selecting which sound to play
void SoundTest(void)
{
	int option = 0;
	while (option == 0)
	{
		system("cls");
		printf("Welcome to the Sound Test Mode\nSelect a sound to play.\n");
		printf("MUSIC\n1 - IPC Pac Man Theme\n");
		printf("\n");
		printf("SFX\n");
		printf("2 - Boop 1\n3 - Boop 2\n4 - Boop 3\n5 - Pac Man: dies\n");
		printf("99 - Quit Sound Test\n");
		printf("Please make your selection: ");
		scanf("%d", &option);
		system("cls");
		if (option == 1)
		{
			printf("IPC Pac Man Theme");
			PlaySound(TEXT("IPC PACMAN THEME MASTER.wav"), NULL, SND_SYNC);
		}
		if (option == 2)
		{
			printf("Boop 1");
			PlaySound(TEXT("BOOP 1.wav"), NULL, SND_SYNC);
		}
		if (option == 3)
		{
			printf("Boop 2");
			PlaySound(TEXT("BOOP 2.wav"), NULL, SND_SYNC);
		}
		if (option == 4)
		{
			printf("Boop 3");
			PlaySound(TEXT("BOOP 3.wav"), NULL, SND_SYNC);
		}
		if (option == 5)
		{
			printf("Pac Man: Dies");
			PlaySound(TEXT("PAC DEATH.wav"), NULL, SND_SYNC);
		}
		if (option == 99)
		{
			return;
		}
		option = 0;
	}
}