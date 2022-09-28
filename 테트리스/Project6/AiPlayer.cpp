#include <iostream>
#include <utility>
#include <algorithm>
#include "AiPlayer.h"


bool compare(const std::pair<int, int>& a, const std::pair<int, int>& b);

AiPlayer::AiPlayer()
{
	aiBoardValue.resize(HEIGHT, std::vector<int>(WIDTH));
	aiX.resize(4, 0);
	aiY.resize(4, 0);
	aiXY.resize(4, { 0, 0 });

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
int AiPlayer::AI_CheckAroundValue(Board& board, Tetromino* aiTet)
{
	using std::pair;
	using std::vector;
	//system("cls");
	int sum = 0;
	vector<pair<int, int>> tempXY; // sum에 이미 넣은 값인지 아닌지 판별

	// 가이드의 현재 좌표 읽어오기

	Tetromino ai_Tet = *aiTet; // aiTet 복제
	ai_Tet.setX(2);
	ai_Tet.guideDown(board);

	Block* block;
	block = ai_Tet.getBlock(); // aiTet에 들어있는 블럭을 가져옴	

	int y = ai_Tet.getY(); // aiTet의 현재 x 좌표 여기에 블록의 디폴트 좌표를 더해서 값을 맞춰야 한다
	int x = ai_Tet.getX(); // aiTet의 현재 y 좌표 여기에 블록의 디폴트 좌표를 더해서 값을 맞춰야 한다

	int lX = 11, rX = 0; // aiX 좌표의 가장 왼쪽과 오른쪽을 찾는다

	int aiYIndex = 0; // aiY를 비교하기 위한 변수

	int saveLX = 0;
	int saveRX = 0;

	bool delay = false; // lX, rX 조작 변수

	int firstSearch = 0;
	int tlx = 11;


	for (int i = 0; i < 4; i++)
	{
		//std::cout << block[i].getY() + y << ", " << block[i].getX() + x << std::endl; 
		// 가이드의 현재 좌표 이걸로 aiBoardValue의 좌표 주변을 탐색하자
		aiX[i] = block[i].getY() + y;
		aiY[i] = block[i].getX() + x;

		aiXY[i] = { aiX[i], aiY[i] };

		tlx = tlx > aiX[i] ? aiX[i] : tlx; // 가장 왼쪽에 있는 X 값 찾기
	}

	// 좌측부터 탐색하는 함수(확인 필요)

	if (b_aiRot)
	{
		ai_Tet.setX(2);
		ai_Tet.setY(ai_Tet.getY() - indexLX);
		ai_Tet.guideDown(board);
		x = ai_Tet.getX(); // aiTet의 현재 y 좌표 여기에 블록의 디폴트 좌표를 더해서 값을 맞춰야 한다

		for (int i = 0; i < 4; i++)
		{
			aiX[i] -= indexLX;
			aiY[i] = block[i].getX() + x;
			aiXY[i] = { aiX[i], aiY[i] };
		}
	}

	else if (b_first && tlx != 1)
	{
		b_aiRot = true;
		indexLX = block[0].getY() - 1;

		ai_Tet.setX(2);
		ai_Tet.setY(ai_Tet.getY() - indexLX);
		ai_Tet.guideDown(board);
		x = ai_Tet.getX(); // aiTet의 현재 y 좌표 여기에 블록의 디폴트 좌표를 더해서 값을 맞춰야 한다
		for (int i = 0; i < 4; i++)
		{
			aiX[i] -= indexLX;
			aiY[i] = block[i].getX() + x;
			aiXY[i] = { aiX[i], aiY[i] };
		}
	}
	else
	{
		b_first = false;
		b_aiRot = false;
	}

	sort(aiXY.begin(), aiXY.end(), compare); // 오름차순 정렬


	for (int i = 0; i < 4; i++)
	{
		// Y값에 변동이 생기면 delay를 true로 바꾸고 밑에서 교환한다.
		// aiYIndex가 3보다 크면 배열 바깥으로 나가므로 예외처리
		if (aiYIndex == 3 || (aiYIndex < 3 && aiXY[aiYIndex].second != aiXY[aiYIndex + 1].second))
		{
			delay = true;
			if (lX > aiXY[i].first)
			{
				lX = aiXY[i].first;
				saveLX = i;
			}
			rX = rX < aiXY[i].first ? aiXY[i].first : rX;
			saveRX = i;
			aiYIndex++;
		}

		// 현 Y위치에서 가장 왼쪽과 오른쪽을 찾아낸다.
		else
		{
			if (lX > aiXY[i].first)
			{
				lX = aiXY[i].first;
				saveLX = i;
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
			int tmpLy = aiXY[saveLX].second;
			int tmpRy = aiXY[saveRX].second;

			if (aiBoardValue[tmpLy][lX - 1] > 0)
			{
				bool check = false;
				for (int j = 0; j < tempXY.size(); j++)
				{
					if ((tempXY[j].first == tmpLy) && tempXY[j].second == (lX - 1))
					{
						check = true;
					}
				}
				if (!check)
				{
					sum += aiBoardValue[tmpLy][lX - 1];
					tempXY.push_back({ tmpLy, lX - 1 });
				}
			}

			if (aiBoardValue[tmpRy][rX + 1] > 0)
			{
				bool check = false;

				for (int j = 0; j < tempXY.size(); j++)
				{
					if ((tempXY[j].first == tmpRy) && tempXY[j].second == (rX + 1))
					{
						check = true;
					}
				}
				if (!check)
				{
					sum += aiBoardValue[tmpRy][rX + 1];
					tempXY.push_back({ tmpRy, rX + 1 });
				}
			}
		}

		// 블록의 아래쪽이 음수가 아니라면 바닥의 값을 더한다.
		if (aiBoardValue[aiXY[i].second + 1][aiXY[i].first] > 0)
		{
			bool check = false;

			for (int j = 0; j < tempXY.size(); j++)
			{
				if (tempXY[j].first == aiXY[i].second + 1 && tempXY[j].second == aiXY[i].first )
				{
					check = true;
				}
			}
			if (!check)
			{
				sum += aiBoardValue[aiXY[i].second + 1][aiXY[i].first];
				tempXY.push_back({ aiXY[i].second + 1, aiXY[i].first });
			}
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

void AiPlayer::AI_Check(Board& board, Tetromino& aiTet, Tetromino* guideTet, Tetromino& tet)
{
	int aiX = 1; // 해당 좌표까지 X값 이동

	int aiR = 0; // 회전 횟수 총 4번 계산할 것이며 이 값에 따라서 최종적으로 블럭이 몇번 돌아야 하는지 정해짐

	int sum = 0;
	int max = 0; // 가장 큰 경우의 수를 저장하기 위함
	int indexX = 0;
	std::vector<int>xPos(4, 0);
	std::vector<int>yPos(4, 0);
	bool correct = false;

	// 가이드의 현재 좌표 읽어오기	
	aiTet = *guideTet;
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
				b_aiRot = false;
				break;
			}
			else if (j == 1)
			{
				b_first = true;
			}
			aiTet.setY(j);
			sum = AI_CheckAroundValue(board, &aiTet);
			if (max < sum)
			{
				max = sum;
				aiX = j;
				aiR = i;
				correct = b_aiRot;
				indexX = indexLX;
				xPos = Get_Xpos();
				yPos = Get_Ypos();
			}
		}
		aiTet.rotate(board);
		b_aiRot = false;
		b_rxDecision = false;
	}

	// main 함수에서 해당 좌표로 이동해야 하기 때문에 저장
	Set_AIx(aiX);

	// aiBoardValue에 값 저장
	for (int i = 0; i < 4; i++)
	{
		int x = xPos[i];
		int y = yPos[i];
		aiBoardValue[y][x] *= -1;
	}


	switch (aiR)
	{
	case 1:
		tet.rotate(board);
		if (correct)
		{
			for (int i = 0; i < 4; i++)
			{
				tet.getBlock()[i].setY(tet.getBlock()[i].getY() - indexX);
			}
		}
		break;
	case 2:
		tet.rotate(board);
		tet.rotate(board);
		if (correct)
		{
			for (int i = 0; i < 4; i++)
			{
				tet.getBlock()[i].setY(tet.getBlock()[i].getY() - indexX);
			}
		}
		break;
	case 3:
		tet.rotate(board);
		tet.rotate(board);
		tet.rotate(board);
		if (correct)
		{
			for (int i = 0; i < 4; i++)
			{
				tet.getBlock()[i].setY(tet.getBlock()[i].getY() - indexX);
			}
		}
		break;
	default:
		break;
	}
}

void AiPlayer::Ai_LineClear()
{
	bool lineClear = true; // 가득찬 라인이 있는지 확인
	bool pluckLine = false; // 가득찬 라인이 있으면 라인을 아래로 당김

	int line = -1;
	std::vector<int> num;

	// 탐색
	for (int i = HEIGHT - 2; i > 2; i--)
	{
		lineClear = false;
		for (int j = 1; j < WIDTH - 1; j++)
		{
			if (aiBoardValue[i][j] < 0)
			{
				lineClear = false;
				line = -1;
				break;
			}
			else
			{
				lineClear = true;
			}
		}
		if (lineClear)
		{
			line = i;
			num.push_back(i);
			pluckLine = true;
			for (int k = 1; k < WIDTH - 1; k++)
			{
				aiBoardValue[i][k] *= -1;				
			}
		}
	}
	sort(num.begin(), num.end()); // 오름차순 정렬
	if (pluckLine)
	{
		for (int i = 0; i < num.size(); i++)
		{
			for (int j = num[i]; j > 2; j--)
			{
				for (int k = 1; k < WIDTH - 1; k++)
				{
					if (aiBoardValue[j - 1][k] > 0)
					{
						aiBoardValue[j][k] *= -1;
						aiBoardValue[j - 1][k] *= -1;
					}
				}
			}	
		}
	}
}

// 두번 째 값을 기준으로 정렬하기 위한 함수
bool compare(const std::pair<int, int>& a, const std::pair<int, int>& b)
{
	if (a.second == b.second) // second 값이 같다면?
	{
		return a.first < b.first; // first 값이 더 작은게 앞으로 가게 해라!
	}
	return a.second < b.second; // second 값이 같지 않다면 더 큰 값이 뒤로 가게 해라!
}