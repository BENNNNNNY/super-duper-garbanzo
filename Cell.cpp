#include <iostream>
#include <tuple>
#include <cmath>
#include "Cell.h"

// These variables need to start as 0 before the game can begin
// otherwise unwanted effects may occur.
Cell::Cell() {
	Bomb = 0;
	NumNeighbours = 0;
	Revealed = 0;
	Flagged = 0;
}

// Sets the value of XPos. XPos represents where the cell is in
// the array. This is only called in the Game constructor when
// creating the original array.
void Cell::SetXPos(int xpos) {
	XPos = xpos;
}

// See above. Same as before expect for the y co-ord.
void Cell::SetYPos(int ypos) {
	YPos = ypos;
}

// Originally didn't toggle, but to make sure that the first
// point the player chooses isn't bomb it can be toggled. This
// is only toggled off once at the end of the 
// Game::GenerateBoard function. It's normal use is in the same
// function when creating bombs.
void Cell::SetBomb() {
	if(Bomb) {
		Bomb = 0;
	} else {
		Bomb = 1;
	}
}

// Checks if the cell has a bomb in it. Returns 1 if it is a
// bomb and 0 otherwise.
int Cell::IsBomb() {
	return Bomb;
}

// Increments a number by one. NumNeighbours is the number of
// cells in the 8 surrounding cells that have a bomb in it.
// This is only used in the Game::GenerateBoard function.
void Cell::IncNumNeighbours() {
	NumNeighbours++;
}

// This returns the NumNeighbours variable. It is used when
// printing out the board to show how many bombs are nearby
// on revealed cells and to automatically clear the
// surrounding 8 cells if it is 0.
int Cell::GetNumNeighbours() {
	return NumNeighbours;
}

// A cell is revealed when it is cleared, i.e. when the player
// believes there is not a mine there. The Revealed variable
// is 1 when the player has revealed it and 0 otherwise.
void Cell::Clear() {
	Revealed = 1;
}

// Returns whether the cell has been revealed by the player or
// not.
int Cell::IsRevealed() {
	return Revealed;
}

// Toggles whether the user has flagged the cell or not. Cells
// that the user has flagged cannot 'exploded' if selected,
// accidentally or otherwise.
void Cell::ToggleFlag() {
	if(Flagged) {
		Flagged = 0;
	} else {
		Flagged = 1;
	}
}

// Returns whether this particular cell has been flagged
int Cell::IsFlagged() {
	return Flagged;
}
