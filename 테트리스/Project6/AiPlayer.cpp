#include <iostream>
#include "AiPlayer.h"
#include "Tetromino.h"

AiPlayer::AiPlayer()
{
	aiBoardValue.resize(HEIGHT, std::vector<int>(WIDTH));
}

int AiPlayer::AI_CheckAroundValue(Block& block, Tetromino tet)
{
	int sum = 0;
	int x = block.getX() + tet.getX();
	int y = block.getY() + tet.getY();

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
							if (((i == 0) && (aiGameValue[y + i - 1][x + j] > 0)) ||
								((i != 0) && (block.shape[block.type][rotation][i - 1][j] != 1) && (aiGameValue[y + i - 1][x + j] > 0))) sum += aiGameValue[y + i - 1][x + j];
							break;
						case 1:
							if ((i == 4) ||
								(block.shape[block.type][rotation][i + 1][j] != 1)) sum += aiGameValue[y + i + 1][x + j];
							break;
						case 2:
							if (((j == 0) && (aiGameValue[y + i][x + j - 1] > 0)) ||
								((j != 0) && (block.shape[block.type][rotation][i][j - 1] != 1) && (aiGameValue[y + i][x + j - 1] > 0))) sum += aiGameValue[y + i][x + j - 1];
							break;
						case 3:
							if (((j == 4) && aiGameValue[y + i][x + j + 1] > 0) ||
								((j != 4) && (block.shape[block.type][rotation][i][j + 1] != 1) && (aiGameValue[y + i][x + j + 1] > 0))) sum += aiGameValue[y + i][x + j + 1];
							break;
						}
					}
				}
			}
		}
	return sum;
}

void AiPlayer::AI_Check(void)
{
	int val = 0;

	if(aiCheck_on ==true){
		for (int i = 0; i < 10; i++) //초기화
		{
			aiX[i] = 0;
			aiY[i] = 0;
			aiR[i] = 0;
		}
		aiXYRP = 0;

		for (int i = 0; i < HEIGHT; i++) //value표(+값) 구하기
		{
			for (int j = 0; j < WIDTH; j++)
			{
				if (gameOrg[i][j] > 0) aiGameValue[i][j] = i;
				else aiGameValue[i][j] = 0;
			}
		}
		for (int i = 0; i < HEIGHT - 1; i++) //value표(-값) 구하기
		{ 
			for (int j = 0; j < WIDTH; j++)
			{
				if (aiGameValue[i][j] == 0 && (aiGameValue[i][j - 1] > 0 || aiGameValue[i][j + 1] > 0)) aiGameValue[i][j] = (-i);
			}
		}
		for (int i = 0; i < HEIGHT; i++) //under표 초기화
		{
			for (int j = 0; j < WIDTH; j++)
			{
				aiGameUnder[i][j] = 0;
			}
		}
		for (int i = 0; i < HEIGHT; i++) //under mark하기
		{
			for(int j=1;j<WIDTH-1;j++){
				if (gameOrg[i][j] > 0 && gameOrg[i - 1][j] == 0)
				{
					for (int k = i - 1; k > 0; k--)
					{
						if (gameOrg[k][j] > 0)
						{
							for (int m = i - 1; m > k; m--) aiGameUnder[m][j] = 1;
							break;
						}
					}
				}
			}
		}

		for (int i = 0; i < 21; i++) // 놓을 위치 및 path찾기
		{
			for (int j = 0; j < WIDTH; j++)
			{
				for (int k = 0; k < 4; k++)
				{		

					if (checkCrush(j, i + 1, k) == false && checkCrush(j, i, k) == true && AI_CheckAroundValue(j, i, k) > val)
					{
						bool onUnder = false; //onUnder는 hard drop이 가능한지 판별: false면 가능 , true면 불가능(위에 crush가 있음)						
						for (int m = 0; m < 4; m++)
						{ 
							for (int n = 0; n < 4; n++)
							{
								if (block.shape[block.type][k][m][n] == 1 && aiGameUnder[i + m][j + n] == 1)
								{
									onUnder = true;
								}
							}
						}					
						if(onUnder==false) // hard drop이 가능하면 단일path
						{		
							aiXYRP=0;
							val = AI_CheckAroundValue(j, i, k);
							aiX[0] = j;
							aiY[0] = i;
							aiR[0] = k;
						}
						// 우회 시작
						if (onUnder == true) // hard drop이 불가능하면 우회합니다.
						{
							aiXYRP = 0;

							if (checkCrush(j + 1, i, k) == false && checkCrush(j - 1, i, k) == false && checkCrush(j, i - 1, k) == false)
							{
								break;
							}
							int tempX1 = j;
							int tempY1 = i;
							int tempX2 = j;
							int tempY2 = i;
							int tempXYRP = 0;

							bool underStuck=true; //이 공간이 갇혀 있는지 아닌지를 판별. 무조건 갇혀 있다고 생각하고 출구가 있으면 false
							for (int s = 1; s > -2; s -= 2) //현재 한번 우회해서 갈수 있는지만 판별할수 있음..
							{ 
								for (int x = 0; x < WIDTH; x++)
								{
									if (underStuck == false)
									{
										break;
									}
									for (int y = 0; y < HEIGHT; y++)
									{
										if (tempY1 - y == 0)
										{
											underStuck = false;
											tempXYRP++;
											aiX[tempXYRP] = j + x * s;
											aiY[tempXYRP] = tempY1;
											aiR[tempXYRP] = k;
											break;
										}
										else if (checkCrush(j + x * s, tempY1 - y, k) == true)
										{
											tempX2 = j + x * s;
											tempY2 = tempY1 - y;
										}
										else if (checkCrush(tempX1 + x * s, tempY1 - y, k) == false)
										{
											break;
										}
									}
									if(tempX1==tempX2 && tempY1==tempY2 && x!=0) break;
									else 
									{
										tempX1=tempX2;
										tempY1=tempY2;
									}
								}
							}

							if(underStuck==false){ //1차로 우회가 가능한 경우 최종 path업데이트
								val = AI_CheckAroundValue(j, i, k);
								aiX[0] = j;
								aiY[0] = i;
								aiR[0] = k;
								aiXYRP = tempXYRP;
							}
							// 우회 종료
						}
					}
				}
			}
		}
		aiCheck_on = false;
	}
//실제 path로 찾아가게 하는 부분
	if (block.rotation != aiR[aiXYRP]) aiOutput = ROTATE;
	else if (aiX[aiXYRP] > block.x) aiOutput = RIGHT;
	else if (aiX[aiXYRP] < block.x) aiOutput = LEFT;
	else if (aiX[aiXYRP] == block.x) if (aiXYRP == 0) aiOutput = SPACE; else  aiOutput = DOWN;

	if (aiX[aiXYRP] == block.x && aiY[aiXYRP] == block.y && aiR[aiXYRP] == block.rotation && aiXYRP > 0) aiXYRP--;
}
