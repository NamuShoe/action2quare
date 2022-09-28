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
	int m_aiX; // 최종적으로 이동할 ai의 X좌표
	int m_aiR; // 최종적으로 돌아갈 ai의 회전 횟수
	bool b_rxDecision = false;
public:
	int aiOutput = 0; //컴퓨터가 getKey로 전달하는 입력값
	int aiX[4] = { 0, }; // 내려놓을 곳 좌표를 저장
	int aiY[4] = { 0, }; // 내려놓을 곳 좌표를 저장

	AiPlayer();
	int AI_CheckAroundValue(Board &board, Tetromino &aiTet, Tetromino tet); //블록의 주변값을 더해 최종 값 계산
	void AI_Check(Board& board, Tetromino& aiTet, Tetromino ai_Tet, Tetromino& tet); //블록을 놓을 위치 및 path찾는 함수
	
	void Set_AIx(int x) { m_aiX = x; }
	void Set_AIr(int r) { m_aiR = r; }
	int Get_AIx() { return m_aiX; }
	int Get_AIr() { return m_aiR; }
};