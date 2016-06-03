#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <ncurses.h>

// TODO:
// Algorithm to empty blank spaces does nothing
// Allow to restart the game (make sure exiting doesnt allow restarting)
// Optimise clear board 

int board[12][12] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

int revealed[10][10];

void printBoard() {
	char ch;
	for(int i = 0; i < 10; i++) {
		for(int j = 0; j < 10; j++) {
			if(revealed[i][j] == 1) {
				switch(board[i + 1][j + 1]) {
					case -1:
						ch = 120;	// "x"
						break;
					case 0:
						ch = 32;	// Space
						break;
					default:
						ch = 48 + board[i + 1][j + 1];	// The number of the square
				}
			} else if(revealed[i][j] == 2) {
				ch = 120;	// "x"
			} else {
				ch = 43;	 // "+"
			}
			move(j, 2 * i);
			//getch();
			printw("%c ", ch);
		}
	}
	mvprintw(1, 22, "Arrow keys to move");
	mvprintw(3, 22, "Space to clear");
	mvprintw(5, 22, "x to mark");
	mvprintw(7, 22, "ESC to exit");
}

void generateBoard() {
	srand(2);//time(NULL));
	int xpos, ypos;
	int points[10];
	
	for(int i = 0; i < 10; i++) {
		xpos = rand() % 10 + 1;
		ypos = rand() % 10 + 1;
		do {
			xpos = rand() % 10 + 1;
			ypos = rand() % 10 + 1;
		} while(board[xpos][ypos] != 0);

		board[xpos][ypos] = -1;
		
		if(board[xpos - 1][ypos - 1] != -1) board[xpos - 1][ypos - 1]++;
		if(board[xpos - 1][ypos] != -1) board[xpos - 1][ypos]++;
		if(board[xpos - 1][ypos + 1] != -1) board[xpos - 1][ypos + 1]++;

		if(board[xpos][ypos - 1] != -1) board[xpos][ypos - 1]++;
		if(board[xpos][ypos + 1] != -1) board[xpos][ypos + 1]++;

		if(board[xpos + 1][ypos - 1] != -1) board[xpos + 1][ypos - 1]++;
		if(board[xpos + 1][ypos] != -1) board[xpos + 1][ypos]++;
		if(board[xpos + 1][ypos + 1] != -1) board[xpos + 1][ypos + 1]++;
	}
}

int clearBoard(int xpos, int ypos) {
	
	return 0;
}

/*
int clearBoard(int xpos, int ypos) {
	int tempx, tempy;
	int lastMove = 2;	// 1 - x. 2 - y
	int lastxMove = 0;	// 1 - Right. -1 - Left.
	int lastyMove = -1;	// 1 - Down. -1 - Up.

	if(revealed[xpos][ypos] != 2) {
		revealed[xpos][ypos] = 1;
		if(board[xpos + 1][ypos + 1] == -1) return 1;
		if(board[xpos + 1][ypos + 1] == 0) {
			for(int i = 0; i < 25; i++) {	//Currently !infinite loop
				if(ypos != 0) revealed[xpos][ypos - 1] = 1;
				if(xpos != 0 && ypos != 0) revealed[xpos - 1][ypos - 1] = 1;
				if(xpos != 9 && ypos != 0) revealed[xpos + 1][ypos - 1] = 1;

				if(xpos != 9) revealed[xpos + 1][ypos] = 1;
				if(xpos != 0) revealed[xpos - 1][ypos] = 1;

				if(ypos != 9) revealed[xpos][ypos + 1] = 1;
				if(xpos != 0 && ypos != 9) revealed[xpos - 1][ypos + 1] = 1;
				if(xpos != 9 && ypos != 9) revealed[xpos + 1][ypos + 1] = 1;

				if(xpos == 9) lastxMove = -1;	//Edges
				if(xpos == 0) lastxMove = 1;
				if(ypos == 9) lastyMove = -1;
				if(ypos == 0) lastyMove = 1;

				if(ypos == 9 && (xpos == 0 || xpos == 9)) lastyMove = -1;	//Corners
				if(ypos == 0 && (xpos == 0 || xpos == 9)) lastyMove = 1;

				if(lastMove == 1) {
					if(board[xpos + 1 + lastxMove][ypos + 1] == 0) {
						if(lastyMove = 1) {
							lastyMove = -1;
						} else {
							lastyMove = 1;
						}
					}
				}
				if(lastMove == 2) {
					if(board[xpos + 1][ypos + 1 + lastyMove] == 0) {
						if(lastxMove == 1) {
							lastxMove = -1;
						} else if(lastxMove == -1) {
							lastxMove = 1;
						}
					}
				}

				tempx = xpos;
				tempy = ypos;
				if (ypos != 0 && board[xpos + 1	 ][ypos + 1 - 1] == 0 && lastyMove == -1) { //&& lastMove != 2) {
					mvprintw(11 + i, 0, "y- ");
					ypos--;
					lastMove = 2;
					lastyMove = -1;
				} else if(xpos != 9 && board[xpos + 1 + 1][ypos + 1    ] == 0 && lastxMove == 1) { //&& lastMove != 3) {
					mvprintw(11 + i, 0, "x+ ");
					xpos++;
					lastMove = 1;
					lastxMove = 1;
				} else if(ypos != 9 && board[xpos + 1	 ][ypos + 1 + 1] == 0 && lastyMove == 1) { //&& lastMove != 1) {
					mvprintw(11 + i, 0, "y+ ");
					ypos++;
					lastMove = 2;
					lastyMove = 1;
				} else if(xpos != 0 && board[xpos + 1 - 1][ypos + 1    ] == 0 && lastxMove == -1) { //1&& lastMove != 4) {
					mvprintw(11 + i, 0, "x- ");
					xpos--;
					lastMove = 1;
					lastxMove = -1;
				}


				if(xpos == tempx && ypos == tempy) {
					if(board[xpos + 1 + 1][ypos + 1] == 0) {
						lastxMove = 1;
					} else if(board[xpos + 1 - 1][ypos + 1] == 0) {
						lastxMove = 2;
					} else {
						break;
					}
				}
			}
			refresh();
		}
	}
	return 0;
}
*/

int main(int argc,char **argv) {
	int xpos = 0;
	int ypos = 0;
	int userInput;
	int gameEnd = 0;	// 0 - in progress. 1 - Gameover. 2 - Completed.

	for(int i = 0; i < 10; i++) {
		for(int j = 0; j < 10; j++ ){
			revealed[i][j] = 0;
		}
	}

	generateBoard();

	initscr();
	//raw();
	noecho();
	keypad(stdscr, TRUE);

	printBoard();
	move(0, 0);
	while(userInput != 27 && !gameEnd) {	// ESC
		userInput = getch();
		switch(userInput) {
			case 258:	// Down
				if(ypos != 9) ypos++;
				break;
			case 259:	// Up
				if(ypos != 0) ypos--;
				break;
			case 260:	// Left
				if(xpos != 0) xpos -= 2;
				break;
			case 261:	// Right
				if(xpos != 18) xpos += 2;
				break;
			case 32:	// Space
				gameEnd = clearBoard(xpos / 2, ypos);
				//ypos--;
				break;
			case 120:	// "x"
				if(revealed[xpos / 2][ypos] == 0) {
					revealed[xpos / 2][ypos] = 2;
				} else {
					revealed[xpos / 2][ypos] = 0;
				}
				break;
		}
		getch();
		clear();
		printBoard();
		//ypos--;
		move(ypos, xpos);
		//getch();
		refresh();
	}

	switch(gameEnd) {
		case 0:
			mvprintw(11, 0, "Goodbye");
			break;
		case 1:
			mvprintw(11, 0, "Game Over\nR to restart");
			break;
		case 2:
			mvprintw(11, 0, "Completed\nR to restart");
			break;
	}
	getch();
	endwin();
	return 0;
}


/*
		if(board[xpos + 1][ypos + 1 - 1] == 0 && ypos != 0) revealed[xpos][ypos - 1] = 1;
		if(board[xpos + 1 - 1][ypos + 1 - 1] == 0 && xpos != 0 && ypos != 0) revealed[xpos - 1][ypos - 1] = 1;
		if(board[xpos + 1 + 1][ypos + 1 - 1] == 0 && xpos != 9 && ypos != 0) revealed[xpos + 1][ypos - 1] = 1;

		if(board[xpos + 1 + 1][ypos + 1] == 0 && xpos != 9) revealed[xpos + 1][ypos] = 1;
		if(board[xpos + 1 - 1][ypos + 1] == 0 && xpos != 0) revealed[xpos - 1][ypos] = 1;

		if(board[xpos + 1][ypos + 1 + 1] == 0 && ypos != 9) revealed[xpos][ypos + 1] = 1;
		if(board[xpos + 1 - 1][ypos + 1 + 1] == 0 && xpos != 0 && ypos != 9) revealed[xpos - 1][ypos + 1] = 1;
		if(board[xpos + 1 + 1][ypos + 1 + 1] == 0 && xpos != 9 && ypos != 9) revealed[xpos + 1][ypos + 1] = 1;
*/


