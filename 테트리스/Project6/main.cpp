#include "Tetromino.h"
#include "Board.h"
#include "AiPlayer.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <algorithm>
#include <deque>

#define LEFT	'a'
#define RIGHT	'd'
#define ROTATE	' '
#define DOWN	's'

#define MILLI_SECOND 1000

using namespace std;

void setNextTetro(deque<int>& d);
void showNextTetro(Tetromino tetro, int x, int y);

int main()
{
	cout << "\x1b[?12h" << "\x1b[?25l";
	cout << BLACK;

	double speed = 1;
	int playerSelect = 1;
	ULONGLONG startTick = GetTickCount64();
	Board board;
	char control = NULL;
	deque<int> tetroDeque;

	Tetromino* tet = nullptr;
	Tetromino* guideTet = nullptr;
	Tetromino nextTet = NULL;

	int aiR = 0, aiX = 1;
	AiPlayer aiPlayer;
	Tetromino* aiTet = nullptr;
	bool b_aiThink = true;

	cout << "1. 테트리스 시작, 2. AI 테트리스 시범 플레이: ";
	cin >> playerSelect;
	cout << "\nspeed: ";
	cin >> speed; // 초당 움직일 횟수

	system("cls");

	while (true)
	{
		switch (playerSelect)
		{
		case 1:
			//Input------------------------------------------------------------
			if (_kbhit())//키 입력 있으면 true, 없으면 false
				control = _getch();//입력 키 반환
			else
				control = NULL;//입력 키 비움


			//Logic------------------------------------------------------------
			if (tet == nullptr)//테트로미노가 없을 경우
			{
				if (tetroDeque.size() < 7)
					setNextTetro(tetroDeque);//데큐에 새로운 테트로미노 추가

				tet = new Tetromino(tetroDeque.front());//tetroDuque의 첫번째 생성
				guideTet = new Tetromino(tetroDeque.front());
				tetroDeque.pop_front();//tetroDuque의 첫번째 삭제
				if (tet->isBlock(board))//생성 될 때 충돌할 경우 GameOver
					break;
			}

			switch (control)//_getch로 입력 받은 키
			{
			case LEFT:
				tet->goLeft(board);
				break;
			case RIGHT:
				tet->goRight(board);
				break;
			case ROTATE:
				tet->rotate(board);
				break;
			case DOWN:
				tet->goDown(board);
				startTick = GetTickCount64();//아래로 갈 경우, 시간 초기화
				break;
			}

			if (GetTickCount64() - startTick > 1.0 / speed * MILLI_SECOND)//일정 시간이 지날 경우
			{
				startTick = GetTickCount64();//시간 초기화
				tet->goDown(board);//테트로미노를 아래로
			}

			if (tet->isFixed())//테트로미노가 고정됐을 경우
			{
				board.setTetromino(*tet);
				board.removeLine();
				delete tet;//테트로미노 삭제
				tet = nullptr;//테트로미노 nullptr로 초기화
				continue;
			}

			//Rendering------------------------------------------------------------
			if (tet->isChange())//테트로미노에 변경이 있을 경우
			{
				board.print();//보드 출력
				guideTet->guidePrint(board, *tet);//가이드테트로미노 출력
				tet->print();//테트로미노 출력
				for (int i = 0; i < 5; i++)
					showNextTetro(Tetromino(tetroDeque[i]), 1 + (4 * i), 13);
			}
			break;
		case 2:
			//Input------------------------------------------------------------
			//if (_kbhit())//키 입력 있으면 true, 없으면 false
			//	control = _getch();//입력 키 반환
			//else
			//	control = NULL;//입력 키 비움

			//Logic------------------------------------------------------------
			if (tet == nullptr)//테트로미노가 없을 경우
			{
				if (tetroDeque.size() < 7)
					setNextTetro(tetroDeque);//데큐에 새로운 테트로미노 추가

				tet = new Tetromino(tetroDeque.front());//tetroDuque의 첫번째 생성
				guideTet = new Tetromino(tetroDeque.front());
				aiTet = new Tetromino(tetroDeque.front());
				tetroDeque.pop_front();//tetroDuque의 첫번째 삭제
				if (tet->isBlock(board))//생성 될 때 충돌할 경우 GameOver
					break;
			}

			//switch (control)//_getch로 입력 받은 키
			//{
			//case LEFT:
			//	tet->goLeft(board);
			//	break;
			//case RIGHT:
			//	tet->goRight(board);
			//	break;
			//case ROTATE:
			//	tet->rotate(board);
			//	break;
			//case DOWN:
			//	tet->goDown(board);
			//	startTick = GetTickCount64();//아래로 갈 경우, 시간 초기화
			//	break;
			//}
			if (GetTickCount64() - startTick > 1.0 / 200)//일정 시간이 지날 경우
			{
				if (b_aiThink)
				{
					// 이 부분은 컴퓨터가 생각하는 부분이 들어가야 한다.
					aiPlayer.AI_Check(board, *aiTet, *tet, *tet);
					b_aiThink = false;
				}
				else
				{
					// 이 부분은 컴퓨터가 생각한 것을 토대로 실제 키를 입력하는 부분이 들어가야 한다.

					// Get_AIr에 저장된 회전 횟수 만큼 회전한다.
					if (aiPlayer.Get_AIr() > aiR)
					{
						aiR++;
						tet->rotate(board);
					}

					// 이동해야 하는 X값이 현재 좌표보다 크다면
					if (aiPlayer.Get_AIx() > tet->getY())
					{
						tet->goRight(board);
					}
					// 이동해야 하는 X값이 현재 좌표보다 작다면
					else if (aiPlayer.Get_AIx() < tet->getY())
					{
						tet->goLeft(board);
					}
					// 이동해야 하는 X값이 현재 좌표와 같다면
					else if (aiPlayer.Get_AIx() == tet->getY())
					{
						tet->goDown(board);
					}
				}
			}

			if (GetTickCount64() - startTick > 1.0 / speed * MILLI_SECOND)//일정 시간이 지날 경우
			{
				startTick = GetTickCount64();//시간 초기화
				tet->goDown(board);//테트로미노를 아래로
			}

			if (tet->isFixed())//테트로미노가 고정됐을 경우
			{
				b_aiThink = true;
				board.setTetromino(*tet);
				board.removeLine();
				delete tet;//테트로미노 삭제
				tet = nullptr;//테트로미노 nullptr로 초기화
				continue;
			}

			//Rendering------------------------------------------------------------
			if (tet->isChange())//테트로미노에 변경이 있을 경우
			{
				board.print();//보드 출력
				guideTet->guidePrint(board, *tet);//가이드테트로미노 출력
				tet->print();//테트로미노 출력
				for (int i = 0; i < 5; i++)
					showNextTetro(Tetromino(tetroDeque[i]), 1 + (4 * i), 13);
			}
			break;

		default:
			cout << "잘못된 값 입니다.\n";
			cout << "1. 테트리스 시작, 2. AI 테트리스 시범 플레이: ";
			cin >> playerSelect;
			break;
		}	
 	}
	system("cls");
	cout << BLACK"GAME OVER";
}

void setNextTetro(deque<int>& d)//다음에 나올 테트로미노 추가
{
	deque<int> temp;
	for (int i = 0; i < 7; i++)
		temp.push_back(i);

	random_shuffle(temp.begin(), temp.end());

	for (int i = 0; i < 7; i++)
		d.push_back(temp[i]);
}

void showNextTetro(Tetromino tetro, int x, int y)//다음에 나올 테트로미노 출력
{
	tetro.setX(x);
	tetro.setY(y);
	tetro.print();
}