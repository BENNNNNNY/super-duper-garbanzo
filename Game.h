#ifndef GAME_H
#define GAME_H
#include "Cell.h"

class Game {
private:
	// On finishing the program, I realise I don't need to have a
	// border around the game unlike previous versions. Could be
	// removed (should be removed) to make it 100x100 but lazy
	Cell Board[102][102];
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
