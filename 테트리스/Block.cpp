#include "Block.h"
#include <iostream>
#include <windows.h>

using namespace std;

void gotoxy(int x, int y)
{
	COORD pos = { y * 2, x }; // 2차원 배열 x, y와 반대
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

Block::Block()
{
	x = 0;
	y = 0;
	color = Color::Black;
	fill = false;
}

Block::Block(int x, int y, Color color) : x(x), y(y), color(color)
{
	fill = false;
}

Block::Block(int x, int y, Color color, bool fill) : x(x), y(y), color(color), fill(fill)
{
}

void Block::print(int x, int y)
{
	gotoxy(x, y);
	switch (color)
	{
	case Black:
		cout << BLACK"  ";
		break;
	case Red:
		cout << RED"  ";
		break;
	case Orange:
		cout << ORANGE"  ";
		break;
	case Yellow:
		cout << YELLOW"  ";
		break;
	case Green:
		cout << GREEN"  ";
		break;
	case Sky_blue:
		cout << SKY_BLUE"  ";
		break;
	case Blue:
		cout << BLUE"  ";
		break;
	case Purple:
		cout << PURPLE"  ";
		break;
	case White:
		cout << WHITE"  ";
		break;
	default:
		break;
	}
}

void Block::guidePrint(int x, int y)
{
	gotoxy(x, y);
	switch (color)
	{
	case Black:
		cout << BLACK"  ";
		break;
	case Red:
		cout << GUIDE_RED"  ";
		break;
	case Orange:
		cout << GUIDE_ORANGE"  ";
		break;
	case Yellow:
		cout << GUIDE_YELLOW"  ";
		break;
	case Green:
		cout << GUIDE_GREEN"  ";
		break;
	case Sky_blue:
		cout << GUIDE_SKY_BLUE"  ";
		break;
	case Blue:
		cout << GUIDE_BLUE"  ";
		break;
	case Purple:
		cout << GUIDE_PURPLE"  ";
		break;
	default:
		break;
	}
}