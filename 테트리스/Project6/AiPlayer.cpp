#include <iostream>
#include "AiPlayer.h"

AiPlayer::AiPlayer()
{
	aiBoardValue.resize(HEIGHT, std::vector<int>(WIDTH));

	// 2차원 벡터 초기화 블럭이 실제로 움직일 공간을 음수로 채워 넣는다
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			aiBoardValue[i][j] = -i;
		}
	}

	// 세로 벽 값 지정
	for (int i = 0; i < aiBoardValue.size(); i++)
	{
		aiBoardValue[i][0] = aiBoardValue[i][11] = i;
	}

	// 바닥 값 지정
	for (int i = 0; i < aiBoardValue[0].size(); i++)
	{
		aiBoardValue[20][i] = aiBoardValue[20][i] = 20;
	}
}

// 가이드의 좌표를 가져옴
int AiPlayer::AI_CheckAroundValue(Board &board, Tetromino &aiTet, Tetromino tet)
{
	system("cls");
	int sum = 0;
	
	
	// 가이드의 현재 좌표 읽어오기
	aiTet = tet;
	aiTet.guideDown(board);

	Block* block;
	block = aiTet.getBlock(); // aiTet에 들어있는 블럭을 가져옴	

	int y = aiTet.getY(); // aiTet의 현재 x 좌표 여기에 블록의 디폴트 좌표를 더해서 값을 맞춰야 한다
	int x = aiTet.getX(); // aiTet의 현재 y 좌표 여기에 블록의 디폴트 좌표를 더해서 값을 맞춰야 한다

	int lX = 11, rX = 0; // aiX 좌표의 가장 왼쪽과 오른쪽을 찾는다

	int aiYIndex = 0; // aiY를 비교하기 위한 변수
	
	int saveLX = 0;
	int saveRX = 0;

	int highY = 0; // aiY 좌표의 가장 아래쪽과 위쪽을 찾는다. highY 아래쪽, lowY 위쪽

	bool delay = false; // lX, rX 조작 변수

	for (int i = 0; i < 4; i++)
	{
		//std::cout << block[i].getY() + y << ", " << block[i].getX() + x << std::endl; 
		// 가이드의 현재 좌표 이걸로 aiBoardValue의 좌표 주변을 탐색하자
		aiX[i] = block[i].getY() + y;
		aiY[i] = block[i].getX() + x;

		highY = highY < aiY[i] ? aiY[i] : highY; // 가장 큰 Y값을 찾는다.
	}
	
	for (int i = 0; i < 4; i++)
	{
		// Y값에 변동이 생기면 delay를 true로 바꾸고 밑에서 교환한다.
		// aiYIndex가 4보다 크면 배열 바깥으로 나가므로 예외처리
		if (aiYIndex < 4 && (aiY[aiYIndex] != aiY[aiYIndex + 1] || aiYIndex == 3))
		{
			delay = true;
			lX = lX > aiX[i] ? aiX[i] : lX;
			rX = rX < aiX[i] ? aiX[i] : rX;
			aiYIndex++;
		}

		// 현 Y위치에서 가장 왼쪽과 오른쪽을 찾아낸다.
		else
		{
			if (lX > aiX[i])
			{
				lX = aiX[i];
				saveLX = i;
			}
			if (rX < aiX[i])
			{
				rX = aiX[i];
				saveRX = i;
			}
			aiYIndex++;
		}

		if (rX > 10)
		{
			b_rxDecision = true; // rx가 10이 되면 true.
			return -1;
		}
		// delay가 true이면 현 y좌표에서 가장 왼쪽과 오른쪽을 찾았다는 뜻이 된다.
		// Y의 현재 좌표가 가장 밑이라면 탐색 시작 가장 왼쪽과 오른쪽의 값이 음수가 아니라면 값을 더한다.
		if (delay)
		{
			if (aiBoardValue[aiY[saveLX]][lX - 1] > 0) sum += aiBoardValue[aiY[saveLX]][lX - 1];
			if (aiBoardValue[aiY[saveRX]][rX + 1] > 0) sum += aiBoardValue[aiY[saveRX]][rX + 1];
		}

		// 가장 밑의 블록의 아래쪽이 음수가 아니라면 바닥의 값을 더한다.
		if (aiBoardValue[aiY[i] + 1][aiX[i]] > 0 && aiY[i] == highY)
		{
			sum += aiBoardValue[aiY[i] + 1][aiX[i]];
		}

		// 다음 오는 Y값의 값이 바뀌므로 lX, rX의 값을 초기화 해준다.
		if (delay)
		{
			delay = false;
			lX = 11;
			rX = 0;
		}
	}
	return sum;
}

void AiPlayer::AI_Check(Board& board, Tetromino& aiTet, Tetromino ai_Tet, Tetromino& tet)
{	
	int aiX = 1; // 해당 좌표까지 X값 이동

	int aiR = 0; // 회전 횟수 총 4번 계산할 것이며 이 값에 따라서 최종적으로 블럭이 몇번 돌아야 하는지 정해짐

	int sum = 0;
	int max = 0; // 가장 큰 경우의 수를 저장하기 위함

	// 가이드의 현재 좌표 읽어오기
	aiTet = ai_Tet;

	Block* block;
	block = aiTet.getBlock(); // aiTet에 들어있는 블럭을 가져옴	

	// 왼쪽 끝부터 오른쪽 끝까지 돌려가며 4번 탐색하여 값이 가장 큰곳의 위치를 찾아냄
	for (int i = 0; i < 4; i++)
	{
		for (int j = 1; j <= 10; j++)
		{
			if (b_rxDecision)
			{
				b_rxDecision = false;
				break;
			}
			aiTet.setY(j);
			sum = AI_CheckAroundValue(board, aiTet, aiTet);
			if (max < sum)
			{
				max = sum;
				aiX = j;
				aiR = i;
			}
		}
		aiTet.rotate(board);
	}

	// main 함수에서 해당 좌표로 이동해야 하기 때문에 저장
	Set_AIx(aiX);
	Set_AIr(aiR);

	// 나온 값 만큼 회전
	for (int i = 0; i < aiR; i++)
	{
		aiTet.rotate(board);
	}

	// aiBoardValue에 값 저장을 위하여 해당 위치로 세팅한다.
	aiTet.setY(aiX);
	aiTet.guideDown(board);

	// aiBoardValue에 값 저장
	for (int i = 0; i < 4; i++)
	{
		int x = block[i].getY() + aiTet.getY();
		int y = block[i].getX() + aiTet.getX();
		aiBoardValue[y][x] *= -1;
	}
}
