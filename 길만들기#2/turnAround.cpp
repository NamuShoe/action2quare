#include <iostream>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <vector>

#define ESC "\x1b"
#define CSI "\x1b["

using namespace std;

void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void sortPoint(int width, int height, vector<pair<int, int>>& p)
{
	int left = 0;
	int right = width - 1;
	int top = 0;
	int bottom = height - 1;

	while (left < right && top < bottom)
	{
		for (int i = left; i < right; i++)
			p.push_back({ i, top });

		for (int j = top; j < bottom; j++)
			p.push_back({ right, j });

		for (int k = right; k > left; k--)
			p.push_back({ k, bottom });

		for (int l = bottom; l > top; l--)
			p.push_back({ left, l });
		left += 1;
		right -= 1;
		top += 1;
		bottom -= 1;
	}
	if (width % 2 == 1 && height % 2 == 1)
	{
		if (width >= height)
			for (int i = left; i <= right; i++)
				p.push_back({ i, top });
		else
			for (int j = top; j <= bottom; j++)
				p.push_back({ right, j });
	}
}


int main()
{
	int cnt = -1;
	int width, height;
	double speed;
	bool isContinue = true;
	vector<pair<int, int>> point;
	unsigned long startTick = GetTickCount64();
	unsigned long pauseTick;
	unsigned long gapTick;

	cin >> width >> height >> speed;

	if (speed > 5)
		speed = 5.0;

	cout << ESC"[?12h" << ESC"[?25l";

	sortPoint(width, height, point);

	while (cnt < (int)point.size() - 1)
	{
		if (_kbhit() && _getch() == ' ')
		{
			pauseTick = GetTickCount64();
			gapTick = GetTickCount64() - startTick;
			isContinue = !isContinue;
			system("cls");
			gotoxy(point[cnt].first, point[cnt].second);
			cout << "O";
		}

		if (isContinue)
		{
			if (GetTickCount64() - startTick > 1 / speed * 1000)
			{
				startTick = GetTickCount64();
				cnt++;
				system("cls");
				gotoxy(point[cnt].first, point[cnt].second);
				cout << "O";
			}
		}
		else
		{
			if (GetTickCount64() - pauseTick > 500)
				pauseTick = GetTickCount64();
			else
			{
				if (GetTickCount64() - pauseTick > 250)
					system("cls");
				else
				{
					gotoxy(point[cnt].first, point[cnt].second);
					cout << "O";
				}
			}
			startTick = GetTickCount64() - gapTick;
		}
	}
	gotoxy(0, height);
}