#include <iostream>
#include "AiPlayer.h"


// 현재 블럭 위치로 보내서 프린트
void AiPlayer::print()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			blocks[i][j].print(i, j + 20);
		}
		std::cout << BLACK"          ";
	}
}