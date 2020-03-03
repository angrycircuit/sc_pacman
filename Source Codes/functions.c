#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string.h>	
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
void handleEvent(struct ObjectMoveInfo* object, SDL_Event* e)
{
    // if a key is pressed down
    if ((*e).type == SDL_KEYDOWN && (*e).key.repeat == 0)
    {
        // change speed in each axis
        switch ((*e).key.keysym.sym)
        {
        case SDLK_UP: object->vely = -VELOCITY; object->velx = 0; break;
        case SDLK_DOWN: object->vely = VELOCITY; object->velx = 0; break;
        case SDLK_LEFT: object->velx = -VELOCITY; object->vely = 0; break;
        case SDLK_RIGHT: object->velx = VELOCITY; object->vely = 0; break;
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