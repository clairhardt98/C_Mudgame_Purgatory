#define _CRT_SECURE_NO_WARNINGS
#include "UI.h"
#include "Intro.h"
#include "Battle.h"
#include "Rewards.h"


bool StageClearFlag;
int TurnCnt = 1;
int RoundIdx = -1;
int RewardNum = 3;

void RenewScreen(Player*, Enemy**, int);
bool PlayerAction(int, Player*, Enemy**, int);
void OnTurnEnd(Player*, Enemy**, int);
void PrintEffect(int, int);
void PrepareEnemyArr(Enemy**, int);
void OnPlayerTurnEnd(Player*, Enemy**, int);
void OnRoundStart(Player*);
void RewardStage(Player*);
void OnClearGame(Player*, Stage**);
void OnPlayerDeath(Player*, Stage**);
void DrawMyInfo(Player*);
void DrawEnemyArrInfo(Enemy**, int);
void DrawQuitScreen();

enum PlayerActionEnum
{
	MELEE = 1,
	RANGE,
	DEFENSE,
	SKILL,
	PLAYERINFO,
	ENEMYINFO,
	GAMEINFO,
	QUIT
};


int main()
{
	ClearUI();
	Intro();

	//플레이어 생성
	Player* player = InitPlayer();
	//스테이지 생성
	Stage** stageArr = InitStageArr();
	

	while (1)//game start
	{
		//enter round
		RoundIdx++;
		PrintStageEnterScreen(RoundIdx);
		
		//alloc enemy arr
		OnRoundStart(player);
		StageClearFlag = false;
		int enemyCnt = stageArr[RoundIdx]->ToCreateMonsterNum;
		
		Enemy** enemyArr = SpawnEnemy(stageArr[RoundIdx]);
		
		//enter battle
		while (1)
		{
			
			//스테이지 시작 안내 출력
			int seed = rand();

			PrepareEnemyArr(enemyArr, enemyCnt);
			//RenewScreen(player, enemyArr, enemyCnt);

			//플레이어의 턴
			while (player->Energy > 0 && !StageClearFlag)
			{
				
				if (player->MaxEnergy == player->Energy)
				{
					sprintf(Statement, " 나의 턴!");
					//RenewScreen(player, enemyArr, enemyCnt);
				}
				int Selection;

				RenewScreen(player, enemyArr, enemyCnt);
				while (1)//잘못된 입력 검출 로직
				{
					
					printf("무엇을 할까?\n>> ");
					scanf("%d", &Selection);
					if (Selection == 99)
					{
						RoundIdx = 9;
						StageClearFlag = true;
					}
					//플레이어 로직
					if (PlayerAction(Selection, player, enemyArr, enemyCnt))
						break;
					else
					{
						RenewScreen(player, enemyArr, enemyCnt);
						continue;
					}

				}
			}
			if (StageClearFlag)
			{
				//DestroyEnemyArr(enemyArr,enemyCnt);
				break;
			}
			OnPlayerTurnEnd(player, enemyArr, enemyCnt);
			Sleep(2000);
			sprintf(Statement, " 상대의 턴!");
			RenewScreen(player, enemyArr, enemyCnt);
			Sleep(2000);
			//상대의 턴
			for (int i = 0; i < enemyCnt; i++)
			{
				if (enemyArr[i]->isAlive)
				{
					//enemy task
					//sprintf(Statement, "상대 %s의 행동", enemyArr[i]->Name);
					EnemyAction(player, enemyArr[i]);
					RenewScreen(player, enemyArr, enemyCnt);
					Sleep(2000);
					//플레이어 사망 체크
					if (player->CurrHP == 0)
					{
						OnPlayerDeath(player, stageArr);
					}

				}
			}
			//end of turn
			OnTurnEnd(player, enemyArr, enemyCnt);
		}
		//end of stage
		//reward logic
		DestroyEnemyArr(enemyArr,enemyCnt);
		PrintStageClearScreen(RoundIdx);
		
		if (RoundIdx == 9)
		{
			break;
		}
		else
		{
			RewardStage(player);
		}
		
	}
	//exit stage
	//set stage pointer to next stage
	//게임 엔딩(라운드 10 클리어)
	OnClearGame(player, stageArr);

}

void RenewScreen(Player* player, Enemy** enemyArr, int enemyCnt)
{
	system("cls");
	ClearUI();
	DrawUI();
	DrawRoundStr(RoundIdx + 1);
	//턴 표시
	DrawPlayer();
	DrawPlayerHP(player);
	DrawPlayerEnergy(player);
	DrawPlayerDebuff(player);
	DrawEnemyArr(enemyArr, enemyCnt);
	for (int i = 0; i < enemyCnt; i++)
	{
		if (enemyArr[i]->isAlive)
			DrawEnemyPatternStr(enemyArr[i]);
	}
	DrawStatement();
	PrintScreen();
}

void PrintEffect(int sel, int target)
{
	enum PlayerActionEnum  playeractionenum = sel;

	switch (playeractionenum)
	{
	case MELEE:
	{
		char tempEffectStatement[10] = "타격!";
		ClearStatement();
		DrawSentenceCenterAlign(tempEffectStatement, strlen(tempEffectStatement),
			STATEMENT_DRAW_POS_I, STATEMENT_DRAW_POS_J);
		DrawMeleeAttackEffect(target);
		break;
	}
	case RANGE:
	{
		char tempEffectStatement[10] = "절단!";
		ClearStatement();
		DrawSentenceCenterAlign(tempEffectStatement, strlen(tempEffectStatement),
			STATEMENT_DRAW_POS_I, STATEMENT_DRAW_POS_J);
		DrawRangeAttackEffect();
		break;
	}

	}
}

bool PlayerAction(int sel, Player* player, Enemy** enemyArr, int enemyCnt)
{
	if (sel < 1 || sel > 8) return 0;//잘못된 입력이라면 false 리턴

	enum PlayerActionEnum  playeractionenum = sel;

	switch (playeractionenum)
	{
	case MELEE:
		if (!player->CanUseMelee)
		{
			sprintf(Statement, "타격을 사용할 수 없다!");
			return 0;
		}

		//melee attack logic
		printf("Target : ");
		for (int i = 0; i < enemyCnt; i++)
		{
			if (enemyArr[i]->isAlive)
				printf("%d. %s ", i + 1, enemyArr[i]->Name);
		}
		printf("\n>> ");
		int targetEnemy;
		scanf("%d", &targetEnemy);
		//잘못된 입력 로직

		while ((targetEnemy > enemyCnt) || (targetEnemy <= 0) || !enemyArr[targetEnemy - 1]->isAlive)
		{
			RenewScreen(player, enemyArr, enemyCnt);
			printf("Target : ");
			for (int i = 0; i < enemyCnt; i++)
			{
				if (enemyArr[i]->isAlive)
					printf("%d. %s ", i + 1, enemyArr[i]->Name);
			}

			printf("\n>> ");
			scanf("%d", &targetEnemy);
		}


		PlayerMeleeAttack(player, enemyArr[targetEnemy - 1]);
		PrintEffect(sel, targetEnemy - 1);

		break;
	case RANGE:
		if (!player->CanUseRange)
		{
			sprintf(Statement, "절단을 사용할 수 없다!");
			return 0;
		}
		if (PlayerRangeAttack(player, enemyArr, enemyCnt))
			PrintEffect(sel, 1);
		break;
	case DEFENSE:
		if (!player->CanUseDefense)
		{
			sprintf(Statement, "수비를 사용할 수 없다!");
			return 0;
		}
		Player_Defense(player);
		break;
	case SKILL:
		if (!player->CanUseSkill || !player->HasSkill)
		{
			if(!player->CanUseSkill)
				sprintf(Statement, "스킬을 사용할 수 없다!");

			if(!player->HasSkill)
				sprintf(Statement, "스킬을 보유하고 있지 않습니다");
			return 0;
		}
		
		//스킬
		break;
	case PLAYERINFO:
		DrawMyInfo(player);
		break;
	case ENEMYINFO:
		DrawEnemyArrInfo(enemyArr,enemyCnt);
		break;
	case GAMEINFO:
		//게임 정보
		break;
	case QUIT:
		DrawQuitScreen();
		exit(1);
		break;
	}
	if (IsAllEnemyDead(enemyArr, enemyCnt)) StageClearFlag = true;
	return 1;
}

void OnTurnEnd(Player* player, Enemy** enemyArr, int enemyCnt)
{
	player->Energy = player->MaxEnergy;
	player->Armour = 0;
	
		
	TurnCnt++;
}

void PrepareEnemyArr(Enemy** enemyArr, int enemyCnt)
{
	srand(time(NULL));
	for (int i = 0; i < enemyCnt; i++)
	{
		//아직해결안됨
		if (enemyArr[i]->isAlive)
		{
			int seed = rand();
			enemyArr[i]->NextPattern = SetEnemyAction(enemyArr[i], seed);
			DrawEnemyAction(enemyArr[i]);
			DrawEnemyPatternStr(enemyArr[i]);
		}
		
	}
}

void OnPlayerTurnEnd(Player* player, Enemy** enemyArr, int enemyCnt)
{
	//적 방어도 다 지우기
	for (int i = 0; i < enemyCnt; i++)
	{
		if (enemyArr[i]->isAlive)
			enemyArr[i]->Armour = 0;
	}

	if (player->RemainedWeakness > 0)
	{
		player->RemainedWeakness--;
	}
		
	else if(player->RemainedWeakness == 0)
	{
		player->IsWeakened = false;
		player->AttackDmgMultiplier = 1.0f;
	}
	
}

void OnRoundStart(Player* player)
{
	TurnCnt = 1;
	player->Energy = player->MaxEnergy;
	player->Armour = 0;
	if (player->IsWeakened)
	{
		player->IsWeakened = false;
		player->RemainedWeakness = 0;
		player->AttackDmgMultiplier = 1.0f;
	}
	
}

void RewardStage(Player* player)
{
	srand(time(NULL));
	Reward** rewardArr = (Reward**)malloc(RewardNum * sizeof(Reward*));

	for (int i = 0; i < RewardNum; i++)
	{
		int seed = rand();
		rewardArr[i] = (Reward*)malloc(RewardNum * sizeof(Reward));
		GenerateRewardNo(rewardArr[i], player, seed);
		if (i > 0 && rewardArr[i]->RewardNo == rewardArr[i-1]->RewardNo)
		{
			free(rewardArr[i]);
			i--;
			continue;
		}
		SetReward(rewardArr[i]);
	}
	//중복 방지 로직 필요
	//선택지 배열 출력
	ClearUI();
	PrintRewardScreen(rewardArr, RewardNum);
	PrintScreen();
	
	//선택지 입력
	int Sel;
	printf("보상을 선택\n>> ");
	scanf("%d", &Sel);
	Sel--;
	
	ApplyReward(rewardArr[Sel], player);
	for (int i = 0; i < RewardNum; i++)
	{
		free(rewardArr[i]);
	}
	free(rewardArr);
}

void OnClearGame(Player* player, Stage** stageArr)
{
	//동적할당 해제
	DestroyPlayer(player);
	DestroyStageArr(stageArr);
	//클리어 화면 출력
	char clearstr[3][100];
	char endStr[10] = "End";
	strcpy(clearstr[0], "적이 쓰러진 곳에서 희미한 빛이 새어나옵니다");
	strcpy(clearstr[1], "당신은 그 곳을 향해 걸어나갑니다");
	strcpy(clearstr[2], "이 길에 끝이 있는지는 아무도 모릅니다...");
	for (int i = 0; i < 3; i++)
	{
		ClearUI();
		DrawPlayer();
		DrawSentenceCenterAlign(clearstr[i], strlen(clearstr[i]), 20, 64);
		PrintScreen();
		int temp = _getch();
	}
	ClearUI();
	DrawSentenceCenterAlign(endStr, strlen(endStr), 20, 64);
	PrintScreen();
	int temp = _getch();
	//게임 종료
	exit(1);

}

void OnPlayerDeath(Player* player, Stage** stageArr)
{
	DestroyPlayer(player);
	DestroyStageArr(stageArr);

	char endStr[10] = "You Died";
	ClearUI();
	DrawSentenceCenterAlign(endStr, strlen(endStr), 20, 64);
	PrintScreen();
	int temp = _getch();
	exit(1);
}

void DrawMyInfo(Player* player)
{
	DrawMyInfoUI();
	DrawPlayerStatus(player);
	PrintScreen();
	printf("아무 키나 눌러 게임으로 돌아가기\n>>");
	int temp = _getch();
}

void DrawEnemyArrInfo(Enemy** enemyArr, int enemyCnt)
{
	
	for (int i = 0; i < enemyCnt; i++)
	{
		if(enemyArr[i]->isAlive)
			DrawEnemyStatus(enemyArr[i]);
	}
	PrintScreen();
	printf("아무 키나 눌러 게임으로 돌아가기\n>>");
	int temp = _getch();
}

void DrawQuitScreen()
{
	char quitStr[10] = "Bye";
	ClearUI();
	DrawSentenceCenterAlign(quitStr, strlen(quitStr), 20, 64);
	PrintScreen();
	printf("아무 키나 눌러 종료\n>>");
	int temp = _getch();
}