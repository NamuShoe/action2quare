#include <iostream>
#include "AiPlayer.h"


int AiPlayer::AI_CheckAroundValue(int x, int y, int rotation)
{
	int sum = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (block.shape[block.type][rotation][i][j] == 1) // 블럭 오브젝트에 블럭이 들어 있다면 실행
			{
				for (int k = 0; k < 4; k++)
				{
					switch (k) {
					case 0:
						if (((i == 0) && (comGameValue[y + i - 1][x + j] > 0)) ||
							((i != 0) && (block.shape[block.type][rotation][i - 1][j] != 1) && (comGameValue[y + i - 1][x + j] > 0))) sum += comGameValue[y + i - 1][x + j];
						break;
					case 1:
						if ((i == 4) ||
							(block.shape[block.type][rotation][i + 1][j] != 1)) sum += comGameValue[y + i + 1][x + j];
						break;
					case 2:
						if (((j == 0) && (comGameValue[y + i][x + j - 1] > 0)) ||
							((j != 0) && (block.shape[block.type][rotation][i][j - 1] != 1) && (comGameValue[y + i][x + j - 1] > 0))) sum += comGameValue[y + i][x + j - 1];
						break;
					case 3:
						if (((j == 4) && comGameValue[y + i][x + j + 1] > 0) ||
							((j != 4) && (block.shape[block.type][rotation][i][j + 1] != 1) && (comGameValue[y + i][x + j + 1] > 0))) sum += comGameValue[y + i][x + j + 1];
						break;
					}
				}
			}
		}
	}
	return sum;
}