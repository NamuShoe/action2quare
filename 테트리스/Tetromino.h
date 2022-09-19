#pragma once
#include "Block.h"

#define BLOCK_SIZE 4

class Board;

class Tetromino
{
private:
	int x = 0;
	int y = 4;
	int blockType;
	int size;
	bool change = true;
	bool fix = false;
	Block block[4];

public:
	Tetromino(int num);
	int getX() { return x; };
	void setX(int x) { this->x = x; };
	int getY() { return y; };
	void setY(int y) { this->y = y; };
	Block* getBlock() { return block; };
	bool isChange() { return change; };
	bool isFixed() { return fix; };

	void print();

	bool isBlock(Board& board);

	void goLeft(Board& board);
	void goRight(Board& board);
	void goDown(Board& board);
	void rotate(Board& board);

	void wallKick(Board& board);
};