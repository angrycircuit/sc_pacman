#include <SDL.h>
#include <SDL_image.h>

#define VELOCITY 1
//Screen dimension constants
#define SCREEN_WIDTH 580
#define SCREEN_HEIGHT 600
#define PACMAN_WIDTH 40
#define PACMAN_HEIGHT 40
#define MAP_LEFT_INNER 20
#define MAP_RIGHT_INNER 560
#define MAP_UP_INNER 20
#define MAP_DOWN_INNER 540
//#define MAP_DOWN_INNER 280
//#define MAP_RIGHT_INNER 300


#define PACMAN_ANIMATION_FRAMES 4

struct Obstacles { 
	int posx; 
	int posy; 
	int temp;
};

struct ObjectMoveInfo
{
	int posx;
	int posy;
	int velx;
	int vely;
	SDL_Rect hitBox;
};

extern void free(SDL_Texture*);
extern void handleEvent(struct ObjectMoveInfo* object, SDL_Event* e);
extern void move(struct ObjectMoveInfo* object, SDL_Rect targetHitBox, int objWidth, int objHeight);
extern int checkCollision(SDL_Rect a, SDL_Rect b);
extern SDL_Texture* loadFromFile(SDL_Renderer* renderer, char* address[]);