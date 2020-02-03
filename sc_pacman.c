/***************************************/
/* SC Pacman Game                      */
/*                                     */
/* This is a fun project for IPC144NRR */
/* with input from various member of   */
/* of the class.                       */
/*                                     */
/* Programming is fun!                 */
/*                                     */
/***************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
	printf("SC Pac-Man! START PROGRAM--------------------\n\n");
	//Declare counter variables for loop
	int i, j;
	int pacman_x = 0, pacman_y = 0;
	char input = '0';
	char input_buffer = '0';
	//Create Map of size 15 - need to change this to a constant somehow without using global vars.
	char map[15][15];
	//Populate Map of size 15
	for (i = 0; i < 15; i++) {
		for (j = 0; j < 15; j++) {
			map[i][j] = '-';
		}
	}
	//Set player starting position
	map[pacman_y][pacman_x] = 'P';
	//Set player goal position
	map[0][14] = 'G';
	//Set variable to start game
	int gameon = 0;
	while (gameon == 0) {
		//Show Map
		for (i = 0; i < 15; i++) {
			for (j = 0; j < 15; j++) {
				printf("%c ", map[i][j]);
			}
			printf("\n");
		}
		//Enter Input
		input = '0';
		printf("Enter input, w = up, s = down, a = left, d = right: ");
		while (input == '0') {
			// The input_buffer is used because after entering a character there is a hidden '\n' that follows it,
			// The input_buffer is used because after entering a character there is a hidden '\n' that follows it, 
			// which causes errors. 
			// This is a temporary way of handling the \n to get our desired functionality
			scanf("%c%c", &input, &input_buffer);
			if (input != 'w' && input != 's' && input != 'a' && input != 'd') {
				printf("Wrong input please try again, w = up, s = down, a = left, d = right: ");
				input = '0';
			}	
		}
		printf("Input accepted!\n");
		//what happens for each input
		if (input == 'w') {
			//move player space up, change old space
			//if can't move, do nothing
			//checking to see if current y pos - 1 is out of bounds against size of map
			if (pacman_y - 1 >= 0) {
				pacman_y -= 1;
				//Check to see if player has won
				if (map[pacman_y][pacman_x] == 'G') {
					//set gameon var to exit while loop and end game
					gameon = 1;
				}
				//Move player & replace old space
				map[pacman_y][pacman_x] = map[pacman_y + 1][pacman_x];
				map[pacman_y + 1][pacman_x] = '-';
			}
			else {
				printf("Can't move further up!\n");
			}
		}
		if (input == 's') {
			//move player space down, change old space
			//if can't move, do nothing
			//checking to see if current y pos + 1 is out of bounds against size of map
			if (pacman_y + 1 < 15) {
				pacman_y += 1;
				//Check to see if player has won
				if (map[pacman_y][pacman_y] == 'G') {
					//set gameon var to exit while loop and end game
					gameon = 1;
				}
				//Move player & replace old space
				map[pacman_y][pacman_x] = map[pacman_y - 1][pacman_x];
				map[pacman_y - 1][pacman_x] = '-';
			}
			else {
				printf("Can't move further down!\n");
			}
		}
		if (input == 'a') {
			//move player space left, change old space
			//if can't move, do nothing
			//checking to see if current x pos - 1 is out of bounds against size of map
			if (pacman_x - 1 >= 0) {
				pacman_x -= 1;
				//Check to see if player has won
				if (map[pacman_y][pacman_x] == 'G') {
					//set gameon var to exit while loop and end game
					gameon = 1;
				}
				//Move player & replace old space
				map[pacman_y][pacman_x] = map[pacman_y][pacman_x + 1];
				map[pacman_y][pacman_x + 1] = '-';
			}
			else {
				printf("Can't move further left!\n");
			}
		}
		if (input == 'd') {
			//move player space right, change old space
			//if can't move, do nothing
			//checking to see if current x pos + 1 is out of bounds against size of map
			if (pacman_x + 1 < 15) {
				pacman_x += 1;
				//Check to see if player has won
				if (map[pacman_y][pacman_x] == 'G') {
					//set gameon var to exit while loop and end game
					gameon = 1;
				}
				//Move player & replace old space
				map[pacman_y][pacman_x] = map[pacman_y][pacman_x - 1];
				map[pacman_y][pacman_x - 1] = '-';
			}
			else {
				printf("Can't move further right!\n");
			}
		}
	}
	//Show winning map with winning message
	printf("\n----!!!!Congratulations You WIN!!!!----\n\n");
	for (i = 0; i < 15; i++) {
		for (j = 0; j < 15; j++) {
			printf("%c ", map[i][j]);
		}
		printf("\n");
	}
	printf("\n----!!!!Congratulations You WIN!!!!----\n");
	return 0;
}
