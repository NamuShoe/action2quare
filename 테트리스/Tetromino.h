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
	Block block[4];

public:
	Tetromino(int num);
	int getX() { return x; };
	int getY() { return y; };
	Block* getBlock() { return block; };

	void print();

	bool isBlock(Board& board);

	void goLeft() { y -= 1; };
	void goRight() { y += 1; };
	void goUp() { x -= 1; };
	void goDown() { x += 1; };
	void rotate();

	void wallKick(Board& board);
};