#pragma once
#include <vector>
#include "Board.h"
#include "Tetromino.h"

#define WIDTH	12
#define HEIGHT	21
#define CEILLING -1
#define WALL 1

class AiPlayer
{
private:
	std::vector<std::vector<int>> aiBoardValue; //현재 게임판의 좌표value를 저장
	int m_aiX = 0; // 최종적으로 이동할 ai의 X좌표
	int m_aiR = 0; // 최종적으로 돌아갈 ai의 회전 횟수
	int indexLX = 0;

	bool b_rxDecision = false;
	bool b_firstSearch = false;
	bool b_aiRot = false;
	bool b_first = false;
public:
	std::vector<int> aiX; // 내려놓을 곳 좌표를 저장
	std::vector<int> aiY; // 내려놓을 곳 좌표를 저장
	std::vector<std::pair<int, int>> aiXY; // 순차 정렬을 위한 페어

	AiPlayer();
	int AI_CheckAroundValue(Board& board, Tetromino* aiTet); //블록의 주변값을 더해 최종 값 계산
	void AI_Check(Board& board, Tetromino& aiTet, Tetromino* guideTet, Tetromino& tet); //블록을 놓을 위치 및 path찾는 함수
	void Ai_LineClear();

	void Set_AIx(int x) { m_aiX = x; }

	int Get_AIx() { return m_aiX; }
	int Get_AIr() { return m_aiR; }
	std::vector<int> Get_Xpos() { return aiX; }
	std::vector<int> Get_Ypos() { return aiY; }
};