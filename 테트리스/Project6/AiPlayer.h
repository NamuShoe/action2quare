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
	std::vector<std::vector<int>> aiBoardValue; // 게임판의 value 저장

public:
	int aiOutput = 0; //컴퓨터가 getKey로 전달하는 입력값
	int aiX[4] = { 0, }; // 내려놓을 곳 좌표를 저장
	int aiY[4] = { 0, }; // 내려놓을 곳 좌표를 저장
	int aiXYRP; //path순서(pointer) 저장
	int aiGameValue[HEIGHT][WIDTH]; //현재 게임판의 좌표value를 저장
	int aiGameUnder[HEIGHT][WIDTH]; //현재 게임판에서 블록아래 빈공간이 있는 곳을 저장
	bool aiCheck_on; //블록 놓을 위치 및 path 재계산이 필요한 경우 true

	AiPlayer();
	int AI_CheckAroundValue(Board& board, Tetromino& aiTet, Tetromino tet); //블록의 주변값을 더해 최종 값 계산
	void AI_Check(void); //블록을 놓을 위치 및 path찾는 함수
};