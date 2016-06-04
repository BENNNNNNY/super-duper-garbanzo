#ifndef GAME_H
#define GAME_H
#include "Cell.h"

class Game {
private:
	Cell Board[100][100];
	int BoardXSize;
	int BoardYSize;
	int NumBombs;
public:
	Game(int, int);

	int CheckGameFinish();
	int ClearCell(int, int);
	void GenerateBoard(int, int);
	void PrintBoard();
	void Start();
};

#endif
