#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string.h>	
#include "declaration.h"

void free(SDL_Texture* texture)
{
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
	}
}

// load from spritesheet and erase black
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

    return newTexture;
}

void handleEvent(struct ObjectMoveInfo* object, SDL_Event* e)
{
    if ((*e).type == SDL_KEYDOWN && (*e).key.repeat == 0)
    {
        //Adjust the velocity
        switch ((*e).key.keysym.sym)
        {
        case SDLK_UP: object->vely = -VELOCITY; object->velx = 0; break;
        case SDLK_DOWN: object->vely = VELOCITY; object->velx = 0; break;
        case SDLK_LEFT: object->velx = -VELOCITY; object->vely = 0; break;
        case SDLK_RIGHT: object->velx = VELOCITY; object->vely = 0; break;
        }
    }
    //If a key was released
    //else if ((*e).type == SDL_KEYUP && (*e).key.repeat == 0)
    //{
    //    //Adjust the velocity
    //    switch ((*e).key.keysym.sym)
    //    {
    //    case SDLK_UP: object->vely += VELOCITY; break;
    //    case SDLK_DOWN: object->vely -= VELOCITY; break;
    //    case SDLK_LEFT: object->velx += VELOCITY; break;
    //    case SDLK_RIGHT: object->velx -= VELOCITY; break;
    //    }
    //}
}

void move(struct ObjectMoveInfo* object, SDL_Rect targetHitBox, int objWidth, int objHeight)
{
    //Move the dot left or right
    object->posx += object->velx;
    object->hitBox.x = object->posx;

    //If the dot went too far to the left or right
    if ((object->posx < MAP_LEFT_INNER) || ((object->posx + objWidth) > MAP_RIGHT_INNER)/* || checkCollision(object->hitBox, a)*/)
    {
        //Move back
        object->posx -= object->velx;
        object->hitBox.x = object->posx;
    }
        //Move the dot up or down
        object->posy += object->vely;
        object->hitBox.y = object->posy;

    //If the dot went too far up or down
    if ((object->posy < MAP_UP_INNER) || (object->posy + objHeight > MAP_DOWN_INNER)/* || checkCollision(object->hitBox, a)*/)
    {
        //Move back
        object->posy -= object->vely;
        object->hitBox.y= object->posy;
    }
}

int checkCollision(SDL_Rect a, SDL_Rect b)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if (bottomA <= topB)
        return 0;

    if (topA >= bottomB)
        return 0;

    if (rightA <= leftB)
        return 0;

    if (leftA >= rightB)
        return 0;

    //If none of the sides from A are outside B
    return 1;
}