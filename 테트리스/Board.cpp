﻿#include "Board.h"
#include "Tetromino.h"
#include <iostream>

using namespace std;

Board::Board()
{
	for (int i = 0; i < width; i++)
	{
		blocks[height - 1][i] = { height - 1, i, Color::White };
	}

	for (int i = 0; i < height - 1; i++)
	{
		blocks[i][0] = { i, 0, Color::White };
		blocks[i][width - 1] = { i, width - 1, Color::White };
	}
}

void Board::print()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			blocks[i][j].print(i, j);
		}
		cout << BLACK"          ";
	}
}

void Board::setTetromino(Tetromino tet)
{
	Block* block;
	block = tet.getBlock();

	for (int i = 0; i < BLOCK_SIZE; i++)
	{
		blocks[tet.getX() + block[i].getX()][tet.getY() + block[i].getY()] = { tet.getX() + block[i].getX(), tet.getY() + block[i].getY() , block[i].getColor() };
	}
}

void Board::removeLine()
{
	bool isLine;
	for (int i = HEIGHT - 2; i >= 0; i--)
	{
		isLine = true;
		for (int j = 1; j < WIDTH - 1; j++)
		{
			if (blocks[i][j].getColor() == 0)
			{
				isLine = false;
				break;
			}
		}
		if (isLine)
		{
			pressLine(i);
			i++;
		}
	}
}

void Board::pressLine(int n)
{
	Color temp;

	for (int j = 1; j < WIDTH - 1; j++)
		blocks[n][j].setColor(Color::Black);

	for (int i = n; i > 0; i--)
	{
		for (int j = 1; j < WIDTH - 1; j++)
		{
			if (blocks[i][j].getColor() != blocks[i - 1][j].getColor())
			{
				temp = blocks[i][j].getColor();
				blocks[i][j].setColor(blocks[i - 1][j].getColor());
				blocks[i - 1][j].setColor(temp);
			}
		}
	}
}
