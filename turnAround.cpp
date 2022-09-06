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

    while (left <= right && top <= bottom)
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
    if (width == height && width % 2 == 1)
        p.push_back({ (width - 1) / 2, (height - 1) / 2 });
}


int main()
{
    int cnt = 0;
    int width, height;
    double speed;
    bool isBlink = true;
    vector<pair<int, int>> point;
    unsigned long startTick = GetTickCount64();
    unsigned long pauseTick;
    unsigned long blinkTick;

    cin >> width >> height >> speed;

    if (speed > 5)
        speed = 5.0;

    cout << ESC"[?12h" << ESC"[?25l";

    sortPoint(width, height, point);

    while (cnt < point.size())
    {
        if (GetTickCount64() - startTick <= 1 / speed * 1000)
            continue;
        else
            startTick = GetTickCount64();

        if (_kbhit() && _getch() == ' ')
        {
            pauseTick = GetTickCount64() - startTick;
            blinkTick = GetTickCount64();
            while (true)
            {
                if (_kbhit() && _getch() == ' ')
                    break;

                if (GetTickCount64() - blinkTick <= 500)
                {
                    if (GetTickCount64() - blinkTick <= 250)
                    {
                        system("cls");
                    }
                    else
                    {
                        gotoxy(point[cnt].first, point[cnt].second);
                        cout << "O";
                    }
                    continue;
                }
                else
                    blinkTick = GetTickCount64();
            }
            startTick = GetTickCount64() - pauseTick;
        }
        system("cls");
        gotoxy(point[cnt].first, point[cnt].second);
        cout << "O";
        cnt++;
    }
    gotoxy(0, height);
}