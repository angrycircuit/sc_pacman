#include "pacman.h"

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern SDL_Texture* background;
extern SDL_Texture* charactersTexture;
extern SDL_Rect pacmanClips[PACMAN_ANIMATION_FRAMES];
extern SDL_Rect dots[TOTALDOTS];
extern SDL_Rect energizer[TOTALENERGIZE];
extern struct Tile tile[TOTALTILE];
extern map[31][28];

int init(struct ObjectMoveInfo* objectMoveInfo)
{
	// initialize video & audio
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Init(SDL_INIT_AUDIO);
	SDL_Init(IMG_INIT_PNG);
	// initialize display container
	gWindow = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	// initialize render color to white
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	// initialize characters' moving information
	// -----------------------------------------
									  //coordinates
	initMoveInfo(&objectMoveInfo[PACMAN], 270, 460, PACMAN_RENDER_WIDTH, PACMAN_RENDER_HEIGHT);
	initMoveInfo(&objectMoveInfo[BLINKY], 275, 280, GHOST_RENDER_WIDTH, GHOST_RENDER_HEIGHT);	
	// load pictures to containers
	loadMedia();
	
	return 0;
}

void loadMedia()
{
	// load image to background container
	SDL_Surface* loadedSurface = IMG_Load("Source Files/map.jpg");
	background = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	// load texture
	charactersTexture = loadFromFile(gRenderer, "Source Files/characters.jpg");
	// set spritesheet
	setSprite();
	// set logic layer
	setTile();
	// set dots
	setDots();
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

// set objects' initial position, and their hitboxes' size
void initMoveInfo(struct ObjectMoveInfo* object, int posx, int posy, int width, int height)
{
	object->posx = posx;
	object->posy = posy;
	object->velx = 0;
	object->vely = 0;
	object->degree = 0;
	object->hitBox.x = object->posx;
	object->hitBox.y = object->posy;
	object->hitBox.w = 40;
	object->hitBox.h = 40;
	object->eatDots.x = object->posx + 20 - DOT_WIDTH / 2;
	object->eatDots.y = object->posy + 20 - DOT_HEIGHT / 2;
	object->eatDots.w = DOT_WIDTH;
	object->eatDots.h = DOT_HEIGHT;
	coordinateToIndex(object);
}

// set hitbox for each wall type tile
void setTile()
{
	int i, j;
	int counter = 0;
	for (i = 0; i < 31; i++)
	{
		for (j = 0; j < 28; j++)
		{
			tile[counter].type = map[i][j];
			if (tile[counter].type == 1)
			{
				tile[counter].hitBox.x = j * 20 + 10;
				tile[counter].hitBox.y = i * 20 + 10;
				tile[counter].hitBox.w = 20;
				tile[counter].hitBox.h = 10;
			}
			else if (tile[counter].type == 2)
			{
				tile[counter].hitBox.x = j * 20 + 20;
				tile[counter].hitBox.y = i * 20 + 10;
				tile[counter].hitBox.w = 10;
				tile[counter].hitBox.h = 20;
			}
			else if (tile[counter].type == 3)
			{
				tile[counter].hitBox.x = j * 20 + 10;
				tile[counter].hitBox.y = i * 20 + 20;
				tile[counter].hitBox.w = 20;
				tile[counter].hitBox.h = 10;
			}
			else if (tile[counter].type == 4)
			{
				tile[counter].hitBox.x = j * 20 + 10;
				tile[counter].hitBox.y = i * 20 + 10;
				tile[counter].hitBox.w = 10;
				tile[counter].hitBox.h = 20;
			}
			else if (tile[counter].type == 5)
			{
				tile[counter].hitBox.x = j * 20 + 10;
				tile[counter].hitBox.y = i * 20 + 20;
				tile[counter].hitBox.w = 10;
				tile[counter].hitBox.h = 10;
			}
			else if (tile[counter].type == 6)
			{
				tile[counter].hitBox.x = j * 20 + 10;
				tile[counter].hitBox.y = i * 20 + 10;
				tile[counter].hitBox.w = 10;
				tile[counter].hitBox.h = 10;
			}
			else if (tile[counter].type == 7)
			{
				tile[counter].hitBox.x = j * 20 + 20;
				tile[counter].hitBox.y = i * 20 + 10;
				tile[counter].hitBox.w = 10;
				tile[counter].hitBox.h = 10;
			}
			else if (tile[counter].type == 8)
			{
				tile[counter].hitBox.x = j * 20 + 20;
				tile[counter].hitBox.y = i * 20 + 20;
				tile[counter].hitBox.w = 10;
				tile[counter].hitBox.h = 10;
			}
				
			counter++;
		}
	}
}

// set hitbox for each dot
void setDots()
{
	int i, j;
	int dotsCounter = 0, energizerCounter = 0;
	for (i = 0; i < 31; i++)
	{
		for (j = 0; j < 28; j++)
		{
			if (map[i][j] == 0)
			{
				dots[dotsCounter].x = j * 20 + 20 - DOT_WIDTH / 2;
				dots[dotsCounter].y = i * 20 + 20 - DOT_HEIGHT / 2;
				dots[dotsCounter].w = DOT_WIDTH;
				dots[dotsCounter].h = DOT_HEIGHT;
				dotsCounter++;
			}
			else if (map[i][j] == 10)
			{
				energizer[energizerCounter].x = j * 20 + 20 - ENERGIZER_WIDTH / 2;
				energizer[energizerCounter].y = i * 20 + 20 - ENERGIZER_HEIGHT / 2;
				energizer[energizerCounter].w = ENERGIZER_WIDTH;
				energizer[energizerCounter].h = ENERGIZER_HEIGHT;
				energizerCounter++;
			}
		}
	}
		
}