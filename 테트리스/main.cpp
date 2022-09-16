#include "Tetromino.h"
#include "Board.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define LEFT	'a'
#define RIGHT	'd'
#define ROTATE	' '
#define DOWN	's'

#define MILLI_SECOND 1000

using namespace std;

int main()
{
	cout << "\x1b[?12h" << "\x1b[?25l";
	cout << BLACK;
	system("mode con cols=24 lines=22 | title Tetris");

	double speed = 1;
	ULONGLONG startTick = GetTickCount64();
	Board board;
	char control = NULL;
	bool isMove = true;

	cout << "speed: ";
	cin >> speed;

	system("cls");
	Tetromino* tet = nullptr;

	while (true)
	{
		//Logic
		if (tet == nullptr)
		{
			tet = new Tetromino(4);
			if (tet->isBlock(board))
				break;
			tet->goUp();
		}

		switch (control)
		{
		case LEFT:
			tet->goLeft();
			isMove = true;
			break;
		case RIGHT:
			tet->goRight();
			isMove = true;
			break;
		case ROTATE:
			tet->rotate();
			isMove = true;
			break;
		case DOWN:
			tet->goDown();
			startTick = GetTickCount64();
			isMove = true;
			break;
		}

		if (GetTickCount64() - startTick > 1.0 / speed * MILLI_SECOND)
		{
			startTick = GetTickCount64();
			control = DOWN;
			tet->goDown();
			isMove = true;
		}

		if (tet->isBlock(board))
		{
			if (control != DOWN)
			{
				if (control == LEFT)
				{
					tet->goRight();
					isMove = false;
				}
				else if (control == RIGHT)
				{
					tet->goLeft();
					isMove = false;
				}
				else if (control == ROTATE)
				{
					tet->wallKick(board);
					isMove = true;
				}
			}
			else
			{
				tet->goUp();
				isMove = false;
				board.setTetromino(*tet);
				delete tet;
				tet = nullptr;
				continue;
			}
		}
		
		if (board.isLine())
		{
			board.removeLine();
			isMove = true;
		}

		//Rendering
		if (isMove)
		{
			board.print();
			tet->print();
			isMove = false;
		}

		//Input
		if (_kbhit())
			control = _getch();
		else
			control = NULL;
	}
}