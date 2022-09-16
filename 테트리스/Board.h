#pragma once
#include "Block.h"

#define WIDTH	12
#define HEIGHT	21

class Tetromino;

class Board
{
private:
	int width = WIDTH;
	int height = HEIGHT;
	Block blocks[HEIGHT][WIDTH];

public:
	Board();
	void print();
	Block getBlock(int x, int y) { return blocks[x][y]; };
	void setTetromino(Tetromino tet);
	bool isLine();
	void removeLine();
	void sortLine(int n);
};