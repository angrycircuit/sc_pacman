#define _CRT_SECURE_NO_WARNINGS

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string.h>	
#include <stdlib.h>
#include <Windows.h>
#include <MMSystem.h>
#include <conio.h>
#include "declaration.h"

// release the resource
void free(SDL_Texture* texture)
{
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
	}
}

// set objects' initial position, and their hitboxes' size
void initMoveInfo(struct ObjectMoveInfo* object, int posx, int posy, int width, int height)
{
    object->posx = posx;
    object->posy = posy;
    object->velx = 0;
    object->vely = 0;
    object->degree = 0;
    object->hitBox.x = 0;
    object->hitBox.y = 0;
    object->hitBox.w = width;
    object->hitBox.h = height;
}

// load from spritesheet, erase black, and return the content
SDL_Texture* loadFromFile(SDL_Renderer* renderer, char* address[])
{
    // initialize container
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(address);

    // erase black
    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0x00, 0x00, 0x00));

    // store erased spritesheet
    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

    // release resource
    SDL_FreeSurface(loadedSurface);

    // return the processed image
    return newTexture;
}

// change the speed in each axis when a specific key pressed
void handleEvent(struct ObjectMoveInfo* object, SDL_Event* event)
{
    // if a key is pressed down
    if ((*event).type == SDL_KEYDOWN && (*event).key.repeat == 0)
    {
        // change speed in each axis
        switch ((*event).key.keysym.sym)
        {
        case SDLK_UP: object->vely = -VELOCITY; object->velx = 0; object->degree = 0; break;
        case SDLK_DOWN: object->vely = VELOCITY; object->velx = 0; object->degree = 180; break;
        case SDLK_LEFT: object->velx = -VELOCITY; object->vely = 0; object->degree = -90; break;
        case SDLK_RIGHT: object->velx = VELOCITY; object->vely = 0; object->degree = 90; break;
        }
    }
}

// change the object's position stored in ObjectMoveInfo, in order to make it move
// use pointer structure because the member's value has to be changed
// use "->" instead of ".", refering to the member's value
void move(struct ObjectMoveInfo* object, SDL_Rect targetHitBox, int objWidth, int objHeight)
{
    // move the object left or right
    // plus a negative value means minus
    object->posx += object->velx;
    object->hitBox.x = object->posx;

    // if the object went too far to the left or right
    if ((object->posx < MAP_LEFT_INNER) || ((object->posx + objWidth) > MAP_RIGHT_INNER)/* || checkCollision(object->hitBox, targetHitBox)*/)
    {
        // move back
        object->posx -= object->velx;
        object->hitBox.x = object->posx;
    }
    
    // move up or down
    object->posy += object->vely;
    object->hitBox.y = object->posy;

    // if the object went too far up or down
    if ((object->posy < MAP_UP_INNER) || (object->posy + objHeight > MAP_DOWN_INNER)/* || checkCollision(object->hitBox, targetHitBox)*/)
    {
        // move back
        object->posy -= object->vely;
        object->hitBox.y= object->posy;
    }
}

// check if two objects meet
int checkCollision(SDL_Rect a, SDL_Rect b)
{
    // the sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    // calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    // calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    // if any of the sides from A are outside of B
    if (bottomA <= topB)
        return 0;

    if (topA >= bottomB)
        return 0;

    if (rightA <= leftB)
        return 0;

    if (leftA >= rightB)
        return 0;

    // if none of the sides from A are outside B
    return 1;
}

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