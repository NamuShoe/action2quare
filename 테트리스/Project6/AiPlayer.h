#pragma once
#include <vector>
#include "Board.h"
#include "Tetromino.h"

#define WIDTH	12
#define HEIGHT	21

class AiPlayer
{
private:
	int width = WIDTH;
	int height = HEIGHT;
	Block blocks[HEIGHT][WIDTH];

public:
	int aiMove; // Tetromino 쪽에 이동하는 함수들이 있음 ai가 이동할 함수
	std::vector<int> aiX;
	std::vector<int> aiY;

	int aiExaminValue(int x, int y, int rotation); // 블록의 주변값을 더해 최종적인 값 검토
	void AiExamine();
	void print();
};