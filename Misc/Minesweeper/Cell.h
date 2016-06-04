#ifndef CELL_H
#define CELL_H
#include <iostream>
#include <tuple>

// See Cell.cpp for detailed comments.
class Cell {
private:
	int Bomb;
	int XPos, YPos;
	int NumNeighbours;
	int Revealed;
	int Flagged;
public:
	Cell();

	void SetXPos(int);
	void SetYPos(int);
	void SetBomb();
	int IsBomb();
	void IncNumNeighbours();
	int GetNumNeighbours();
	void Clear();
	int IsRevealed();
	void ToggleFlag();
	int IsFlagged();
};

#endif