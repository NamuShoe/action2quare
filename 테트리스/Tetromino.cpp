#include "Tetromino.h"
#include "Board.h"
#include <iostream>
#include <algorithm>

using namespace std;

int blockTypes[7][4][4] =
{
	{//Z RED 2 3
				{1, 1, 0, 0},
				{0, 1, 1, 0},
				{0, 0, 0, 0},
				{0, 0, 0, 0}
	},
	{//L ORANGE 3 3
				{0, 0, 2, 0},
				{2, 2, 2, 0},
				{0, 0, 0, 0},
				{0, 0, 0, 0}
	},
	{//O YELLOW 2 2
				{3, 3, 0, 0},
				{3, 3, 0, 0},
				{0, 0, 0, 0},
				{0, 0, 0, 0}
	},
	{//S GREEN 2 3
				{0, 4, 4, 0},
				{4, 4, 0, 0},
				{0, 0, 0, 0},
				{0, 0, 0, 0}
	},
	{//I SKY_BLUE 2 4
				{0, 0, 0, 0},
				{5, 5, 5, 5},
				{0, 0, 0, 0},
				{0, 0, 0, 0}
	},
	{//J BLUE 3 3
				{6, 0, 0, 0 },
				{6, 6, 6, 0 },
				{0, 0, 0, 0 },
				{0, 0, 0, 0 }
	},
	{//T PURPLE 3 3
				{0, 7, 0, 0},
				{7, 7, 7, 0},
				{0, 0, 0, 0},
				{0, 0, 0, 0}
	}
};

pair<int, int> wallKickTest[24] =
{
	{1, 0},
	{2, 0},
	{0, 1},
	{1, 1},
	{2, 1},
	{0, -1},
	{1, -1},
	{2, -1},
	{0, 2},
	{0, -2},
	{1, 2},
	{1, -2},
	{2, 2},
	{2, -2},
	{-1 ,0},
	{-1 ,1},
	{-1 ,-1},
	{-1 ,2},
	{-1 ,-2},
	{-2 ,0},
	{-2 ,1},
	{-2 ,-1},
	{-2 ,2},
	{-2 ,-2}
};

Tetromino::Tetromino(int num)
{
	int cnt = 0;
	blockType = num;

	if (blockType != 4)
		size = 3;
	else
	{
		size = 4;
		x--;
	}

	for (int i = 0; i < BLOCK_SIZE; i++)
	{
		for (int j = 0; j < BLOCK_SIZE; j++)
		{
			if (blockTypes[num][i][j] != 0)
			{
				block[cnt] = { i, j, (Color)blockTypes[num][i][j] };
				cnt++;
			}
		}
	};
}

void Tetromino::print()
{
	for (int i = 0; i < BLOCK_SIZE; i++)
	{
		block[i].print(block[i].getX() + x, block[i].getY() + y);
	}
	change = false;
}

void Tetromino::guidePrint(Board& board, Tetromino tetro)
{
	*this = tetro;
	
	while(!isBlock(board))
		guideDown(board);
	x -= 1;

	for (int i = 0; i < BLOCK_SIZE; i++)
	{
		block[i].guidePrint(block[i].getX() + x, block[i].getY() + y);
	}
}

bool Tetromino::isBlock(Board& board)
{
	for (int i = 0; i < BLOCK_SIZE; i++)
	{
		if (board.getBlock(x + block[i].getX(), y + block[i].getY()).getColor() != 0)
		{
			return true;
		}
	}
	return false;
}

void Tetromino::goLeft(Board& board)
{
	y -= 1;
	if (isBlock(board))
	{
		y += 1;
		change = false;
	}
	else
		change = true;
}

void Tetromino::goRight(Board& board)
{
	y += 1;
	if (isBlock(board))
	{
		y -= 1;
		change = false;
	}
	else
		change = true;
}

void Tetromino::goDown(Board& board)
{
	x += 1;
	if (isBlock(board))
	{
		x -= 1;
		fix = true;
		change = false;
	}
	else
		change = true;
}

void Tetromino::rotate(Board& board)
{
	for (int i = 0; i < BLOCK_SIZE; i++)
	{
		//시계방향으로 회전할 경우
		//회전 후 행의 값은, 기존 열의 값
		//회전 후 열의 값은, 기존 행의 최댓값에서 기존 행의 값을 뺀 값
		block[i] = { block[i].getY(), size - 1 - block[i].getX(), block[i].getColor() };
	}

	if (isBlock(board))
		wallKick(board);

	change = true;
}

void Tetromino::wallKick(Board& board)
{
	int tempX = x;
	int tempY = y;

	for (int i = 0; i < 24; i++)
	{
		x += wallKickTest[i].first;
		y += wallKickTest[i].second;
		if (!isBlock(board))
			break;
		else
		{
			x = tempX;
			y = tempY;
		}
	}
}
