#include "pacman.h"
#include <SDL.h>

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

    // if not meet
    if (bottomA <= topB)
        return 0;

    if (topA >= bottomB)
        return 0;

    if (rightA <= leftB)
        return 0;

    if (leftA >= rightB)
        return 0;

    // if collision detected
    return 1;
}

int touchHorizontalWall(const struct ObjectMoveInfo object, const struct Tile* tile, int map[31][28])
{
    for (int i = 0; i < TOTALTILE; i++)
        if (tile[i].type >= 1 && tile[i].type <= 3 || tile[i].type >= 5 && tile[i].type <= 8)
            if (checkCollision(object.hitBox, tile[i].hitBox))
                return 1;
    return 0;
}

int touchVerticalWall(const struct ObjectMoveInfo object, const struct Tile* tile, int map[31][28])
{
    for (int i = 0; i < TOTALTILE; i++)
        if (tile[i].type == 2 || tile[i].type >= 4 && tile[i].type <= 8)
            if (checkCollision(object.hitBox, tile[i].hitBox))
                return 1;
    return 0;
}