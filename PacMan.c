/*
	TODO:
	Title Screen Module
	Sound Module
	Level Generate Module
	Start Game Module
	Pacman Module 
	Ghost Module

	I've just listed above what I can remember from class. Feel free to add to these modules if you can think of anything. I'll add more to this soon.
*/
#include <stdio.h>

// to use STD_OUTPUT_HANDLE 
// in gotoxy() & hidethecursor() function,
// it has to be included
#include <Windows.h>

// screen size
#define HEIGHT 20
#define WIDTH 50

// the number of beans
#define BEANNUM 48

// initialize global variables
/* 
	use 2d array to display, 
	every element stand for each display unit on the screen
	each unit value specify what to display
	1 - pacman, 2 - beans, ect.
*/

int screen[HEIGHT][WIDTH] = { 0 };

// pac's coordinate, y = vertical, x = horizontal
int pac_x, pac_y;

/*
   beans' coordinate
   x = vertical, y = horizontal
   cuz each bean has its own coordinate
   bean_x[0~47] & bean_y[0~47] stand for coordinate for each bean
   for example, bean_x[0] & bean_y[0] represent the first bean's coordinate
*/
int bean_x[BEANNUM], bean_y[BEANNUM];

// to store the number of bean eaten
int score;		

// refresh the screen, got from online tutorial
void gotoxy(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

// hide the cursor, got from online tutorial
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

// title page, use int type because a return value needed
int title()
{
	gotoxy(0, 0);
	HideCursor();

	// output the title
	for (int m = 0; m < HEIGHT / 2 - 5; m++)
		printf("\n");
	for (int n = 0; n < WIDTH / 2 - 6; n++)
		printf(" ");
	printf("************\n");
	for (int n = 0; n < WIDTH / 2 - 6; n++)
		printf(" ");
	printf("* PAC  MAN *\n");
	for (int n = 0; n < WIDTH / 2 - 6; n++)
		printf(" ");
	printf("************\n\n\n\n\n\n");
	for (int n = 0; n < WIDTH / 2 - 11; n++)
		printf(" ");

	// make the text blink
	static int blink = 0;
	if (blink < 500)
		blink++;
	if (blink <= 400)
		printf("Press Any Key to Start");
	else
		printf("                      ");
	if (blink == 500)
		// return to 0, in order to keep blinking
		blink = 0;

	// if any key pressed, return 1, then title page over, jump to the game
	if (_kbhit())
		return 1;

	return 0;
}

// initialization, this func only run once
void startup()
{
	// hide the cursor, once is enough
	HideCursor();

	// initialize the pacman's start location (say in the middle of the bottom)
	pac_x = WIDTH / 2;
	pac_y = HEIGHT - 1;

	/* 
		pacman's coordinate
		set the unit value of pacman's start location to 1
		to make show() display correctly
	*/
	screen[pac_y][pac_x] = 1;

	// initialize multiple (say 48) beans
	// i = index number [0~47] of each array
	int i = 0;

	/*
	    the verticle coordinates are between 9-12
		the horizontal coordinates are between 20-32
		the output should be a rectangle
	*/
	for (int m = 9; m < 13; m++)
		for (int n = 0; n < 12; n++)
		{
			bean_y[i] = m;
			i++;
		}
	
	// the index should set to 0, in order to initialize horizontal coordinates
	i = 0;
	for (int n = 0; n < 4; n++)
		for (int m = 20; m < 32; m++)
		{
			bean_x[i] = m;
			i++;
		}
	
	// set all 48 start locations' display units = 2 
	for (int m = 0; m < 48; m++)
		screen[bean_y[m]][bean_x[m]] = 2;
		
	// initialize the score
	score = 0;
}

// display
void show()
{
	// refresh the screen everytime
	gotoxy(0, 0);

	// iterate every point on the screen 
	// to decide what should display
	// based on each unit's value
	for (int m = 1; m <= HEIGHT; m++)
	{
		for (int n = 1; n <= WIDTH; n++)
		{
			//display the border with *
			if ((m == HEIGHT) | (n == WIDTH))
				printf("*");

			// display "C" as pacman, if the current unit's value = 1
			else if (screen[m][n] == 1)
				printf("C");

			// display "o" as beans
			else if (screen[m][n] == 2)
				printf("o");

			// reserved place for displaying ghosts
			//
			// else if (screen[m][n] == 3, 4, 5, 6, ect)
			// printf("symbols of ghosts")	
			
			// fill other points with empty space
			else
				printf(" ");

			
		}
		// switch to new line after iterate each line
		printf("\n");
	}
	// display current score
	printf("\nScore: %d", score);
}

void updateWithInput()
{
	// use input to store user's input
	char input;

	// if any key has been pressed
	if (_kbhit())
	{
		// use getch() to avoid press enter when input instead of what we've already leaned
		input = _getch();
	
		if (input == 'a')

			// pacman cannot move if reach the wall
			if (pac_x != 0)
			{
				// make the previous position invisible
				// otherwise it will leave trait
				screen[pac_y][pac_x] = 0;

				// change pac's coordinate based on input
				pac_x--;

				// the new coordinate must be set to 1 again!!! 
				// because the original initialization in startup only run once
				screen[pac_y][pac_x] = 1;
			}
		if (input == 'd')
			if (pac_x != WIDTH - 1)
			{
				screen[pac_y][pac_x] = 0;
				pac_x++;
				screen[pac_y][pac_x] = 1;
			}
		if (input == 'w')
			if (pac_y != 0)
			{
				screen[pac_y][pac_x] = 0;
				pac_y--;
				screen[pac_y][pac_x] = 1;
			}
		if (input == 's')
			if (pac_y != HEIGHT - 1)
			{
				screen[pac_y][pac_x] = 0;
				pac_y++;
				screen[pac_y][pac_x] = 1;
			}
	}
}

void updateWithOutInput()
{
	// pacman eat beans
	// use loop to check all the beans
	for (int m = 0; m <= BEANNUM; m++)
	{
		// if beans' coordinate = pacman's coordinate
		// which means they meet at the unit
		if ((bean_y[m] == pac_y) && (bean_x[m] == pac_x))
		{
			// set the coordinate out of screen to remove the dead bean
			bean_y[m] = -1;
			bean_x[m] = -1;
			// pacman get a point!
			score++;
		}
	}
			
	// reserved place for speed control of ghosts
	//
	//static int speed = 0;
	//if (speed < 15)
	//	speed++;
	//if (speed == 15)
	//{
	//	// return to 0
	//	speed = 0;
	//}
}

int main()
{
	/*
		as game begins, a title page shows up,
		and the game goes into a infinite loop
		to wait user to manipulate
	*/
	while (1)
	{
		// the title() returns 0 if nothing happen
		title();
		// as any key pressed, it return 1
		if (title())
			// if title returns 1, the loop ends
			break;
	}

	// initialization phase, run only once!
	startup();

	// an infinite game phase
	while (1)
	{
		show();
		updateWithOutInput();
		updateWithInput();
	}
	return 0;
}