#include <iostream>
#include "Cell.h"
#include "Game.h"

int main(int argc,char **argv) {
	int sizex;
	int sizey;
	std::cout << "Arrow keys to move\nSpace to clear\n'x' key to flag\nESC key to quit at any time\n10 minimum, 100 maximum\nEnter first dimension: ";
	std::cin >> sizex;
	std::cout << "Enter second dimension: ";
	std::cin >> sizey;
	Game test(sizex, sizey);
	test.Start();
	return 0;
}
