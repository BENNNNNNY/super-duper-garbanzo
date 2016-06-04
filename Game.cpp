#include <iostream>
#include <time.h>
#include <ncurses.h>
#include "Game.h"

// Constructor. The input is the size of the board.
Game::Game(int x, int y) {
	Cell temp;
	BoardXSize = x;
	BoardYSize = y;
	// Dynamically sets the number of bombs based on board size.
	NumBombs = (BoardXSize * BoardYSize) / 10;
	// Loops through every cell on the board...
	for(int i = 0; i < BoardXSize + 1; i++) {
		for(int j = 0; j < BoardYSize + 1; j++) {
			// ...and creates a cell in each position.
			temp.SetXPos(i);
			temp.SetYPos(j);
			Board[i][j] = temp;
		}
	}
}

// Checks if the game has been finished.
int Game::CheckGameFinish() {
	int count = 0;
	// Loops through every cell on the board...
	for(int i = 0; i < BoardXSize; i++) {
		for(int j = 0; j < BoardYSize; j++) {
			// ...and counts the ones that have been revealed.
			count += Board[i][j].IsRevealed();
		}
	}
	// The total number of cells minus the number cells with bombs in
	// them is equal to the number of cells without bombs in them.
	// This means that when the number of revealed cells is equal to
	// this, there are no more bombs to be uncovered.
	if(count == BoardXSize * BoardYSize - NumBombs) return 1;
	return 0;
}

// Clears the cells based on an initial cell passed to the
// function.
int Game::ClearCell(int xpos, int ypos) {
	// Should only clear if the cell is not a bomb and isn't
	// revealed. The latter more so to save computational time.
	if(!Board[xpos][ypos].IsBomb() && !Board[xpos][ypos].IsRevealed()) {
		// Clears the choosen cell.
		Board[xpos][ypos].Clear();
		// If the cell has no terrist neighbours, all of the neighbours can be
		// cleared
		if(!Board[xpos][ypos].GetNumNeighbours()) {
			// Only clears cells on the field (if the choosen cell was an edge, it
			// could go into non existent cells.
			if(ypos != 0) ClearCell(xpos, ypos - 1);
			if(ypos != BoardYSize) ClearCell(xpos, ypos + 1);
			if(xpos != 0 && ypos != 1) ClearCell(xpos - 1, ypos - 1);
			if(xpos != 0) ClearCell(xpos - 1, ypos);
			if(xpos != 0 && ypos != BoardYSize) ClearCell(xpos - 1, ypos + 1);
			if(xpos != BoardXSize && ypos != 1) ClearCell(xpos + 1, ypos - 1);
			if(xpos != BoardXSize) ClearCell(xpos + 1, ypos);
			if(xpos != BoardXSize && ypos != BoardYSize) ClearCell(xpos + 1, ypos + 1);
		}
	}

	// If the user has selected a bomb that hasn't been flagged they go
	// boom.
	if(Board[xpos][ypos].IsBomb() && !Board[xpos][ypos].IsFlagged()) return 1;
	return 0;
}

// Uses ncurses to print the board to the screen.
void Game::PrintBoard() {
	int firstX = 0;
	int firstY = 0;
	char out;
	
	// Clears the screen. Probably not required since the same cells
	// are being replaced, but good practice.
	clear();
	
	// Goes through each cell in the array...
	for(int i = 0; i < BoardXSize; i++) {
		for(int j = 0; j < BoardYSize; j++) {
			// ...moves to the coresponding spot on the screen...
			move(j, i * 2);

			// ...and if the cell is flagged, it will display as such, if the cell is
			// revealed it will display the number of neighbours with bombs (or a space
			// if no neighbours) and lastly if the cell is not revealed/flagged, it
			// will display 
			if(Board[i][j].IsRevealed() && !Board[i][j].IsFlagged()) {
				out = Board[i][j].GetNumNeighbours() + 48;
				if(out == 48) out = 32;	// Space
			} else if(Board[i][j].IsFlagged()) {
				out = 120;	// x key.
			} else {
				out = 43;	// + key.
			}
			printw("%c", out);
		}
	}
	refresh();
}

// Only called once, used to generate the locations of the
// bombs and to set up the neighbour numbering system.
void Game::GenerateBoard(int initialX, int initialY) {
	//Gets the current time and uses it as a seed.
	srand(time(NULL));
	int xpos, ypos;
	
	// initialX & initialY are the first points that are selected by
	// the user. To avoid having the first cell they choose 
	// potentially be a bomb, it is set to a bomb...
	Board[initialX][initialY].SetBomb();

	// Loops once for each bomb.
	for(int i = 0; i < NumBombs; i++) {
		// Initial attempts at finding a free cell.
		xpos = rand() % BoardXSize;
		ypos = rand() % BoardYSize;

		// Loops until a free cell is found.
		do {
			xpos = rand() % BoardXSize;
			ypos = rand() % BoardYSize;
		} while(Board[xpos][ypos].IsBomb());

		// Once a free cell is found, the cell is set to be a bomb.
		Board[xpos][ypos].SetBomb();
		
		// Once a cell is set to be a bomb, the neighbours have their
		// bomb count increased by 1.
		Board[xpos][ypos - 1].IncNumNeighbours();
		Board[xpos][ypos + 1].IncNumNeighbours();
		Board[xpos - 1][ypos - 1].IncNumNeighbours();
		Board[xpos - 1][ypos].IncNumNeighbours();
		Board[xpos - 1][ypos + 1].IncNumNeighbours();
		Board[xpos + 1][ypos - 1].IncNumNeighbours();
		Board[xpos + 1][ypos].IncNumNeighbours();
		Board[xpos + 1][ypos + 1].IncNumNeighbours();
	}
	// ...and then toggled to not be a bomb.
	Board[initialX][initialY].SetBomb();
}

// Starts the game.
void Game::Start() {
	int gameEnd = 0;
	int xpos = 0;
	int ypos = 0;
	int userInput;
	int firstMove = 1;

	// Starts ncurses mode.
	initscr();
	// Stops user input from being echoed back.
	noecho();
	// Allows use of arrow keys and numberpad.
	keypad(stdscr, TRUE);

	// Generates an artificial board so that the user can make an
	// selection without potentially selecting a mine.
	for(int i = 0; i < BoardXSize; i++) {
		for(int j = 0; j < BoardYSize; j++) {
			move(j, 2 * i);
			printw("+");
		}
	}
	//Required everytime the screen is updated.
	refresh();

	// Moves the blinky thing on the screen to this location.
	move(0, 0);

	// Game loop, only runs while the game is running.
	while(!gameEnd) {
		// getch() gets the keystroke of the user.
		userInput = getch();
		switch(userInput) {
			case 27:	// ESC key.
				gameEnd = 3;
				break;
			case 258:	// Down key.
				if(ypos != BoardYSize - 1) ypos++;
				break;
			case 259:	// Up key.
				if(ypos != 0) ypos--;
				break;
			case 260:	// Left key.
				if(xpos != 0) xpos -= 2;
				break;
			case 261:	// Right key.
				if(xpos != 2 * (BoardXSize - 1)) xpos += 2;
				break;
			case 120:	// x key.
				// Toggles the flag of the selected cell.
				Board[xpos / 2][ypos].ToggleFlag();
				PrintBoard();
				break;
			case 32:	// Space key.
				// Generates the board after the first move.
				if(firstMove) {
					firstMove = 0;
					GenerateBoard(xpos / 2, ypos);
				}
				// Clears the cells and checks if the player has slected a bomb.
				if(ClearCell(xpos / 2, ypos)) gameEnd = 1;
				// Prints the board for the player.
				PrintBoard();
				// Checks if the game has finished.
				if(CheckGameFinish()) gameEnd = 2;
				break;

		}
		move(ypos, xpos);
	}

	// Ends ncurses mode.
	endwin();
	
	// Outputs a goodbye message depending on how the game finished.
	std::string goodbyeMessage;
	switch(gameEnd) {
		case 1:
			goodbyeMessage = "Game over!";
			break;
		case 2:
			goodbyeMessage = "Game completed!";
			break;
		case 3:
			goodbyeMessage = "Goodbye!";
			break;
	}
	std::cout << goodbyeMessage << std::endl;
}




