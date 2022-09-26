#pragma once
#include <vector>
#include "Block.h"

#define WIDTH	12
#define HEIGHT	21

class AiPlayer : public Board
{
private:
	std::vector<std::vector<int>> aiBoardValue;

	int width = WIDTH;
	int height = HEIGHT;
	
	int gameOrg[HEIGHT][WIDTH]; // 게임판            /*게임판에서 게임이 진행되고, cpy에는 이전 게임 frame이 기록되어 있음.*/
	int gameCpy[HEIGHT][WIDTH]; // 게임판 비교용 cpy /*cpy와 비교하여 변화가 있는 부분만 게임을 새로 그림     

	Block aiBoard[HEIGHT][WIDTH];
public:
	int aiOutput; //컴퓨터가 getKey로 전달하는 입력값
	int aiX[10]; //블록 path X좌표모음집(현재 [0]과 [1]만 사용)
	int aiY[10]; //블록 path Y좌표모음집(현재 [0]과 [1]만 사용)
	int aiR[10]; //블록 path 회전값모음집(현재 미사용)
	int aiXYRP; //path순서(pointer) 저장
	int aiGameValue[HEIGHT][WIDTH]; //현재 게임판의 좌표value를 저장
	int aiGameUnder[HEIGHT][WIDTH]; //현재 게임판에서 블록아래 빈공간이 있는 곳을 저장
	bool aiCheck_on; //블록 놓을 위치 및 path 재계산이 필요한 경우 true

	AiPlayer();
	int AI_CheckAroundValue(Block& block, Tetromino tet); //블록의 주변값을 더해 최종 값 계산
	void AI_Check(void); //블록을 놓을 위치 및 path찾는 함수
};