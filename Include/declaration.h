#include <SDL.h>
#include <SDL_image.h>

// the pacman's moving distance in each frame
#define VELOCITY 10

// screen dimension constants
#define SCREEN_WIDTH 580
#define SCREEN_HEIGHT 680

// the size of rendering
#define PACMAN_WIDTH 40
#define PACMAN_HEIGHT 40

// the inner boundaries of the map
#define MAP_LEFT_INNER 20
#define MAP_RIGHT_INNER 560
#define MAP_UP_INNER 20
#define MAP_DOWN_INNER 620

// the speed of animation change
#define PACMAN_ANIMATION_FRAMES 6

struct ObjectMoveInfo
{
	// position on x & y axis
	int posx;	
	int posy;
	// speed on each axis
	int velx;
	int vely;
	// the size of hitbox
	SDL_Rect hitBox;
};

// import functions declared in "functions.c"
// so it can be used in "pacman.c" instantly
extern void free(SDL_Texture*);
extern void handleEvent(struct ObjectMoveInfo* object, SDL_Event* e);
extern void move(struct ObjectMoveInfo* object, SDL_Rect targetHitBox, int objWidth, int objHeight);
extern int checkCollision(SDL_Rect a, SDL_Rect b);
extern SDL_Texture* loadFromFile(SDL_Renderer* renderer, char* address[]);