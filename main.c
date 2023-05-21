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
	int Selection;
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
			RenewScreen(player, enemyArr, enemyCnt);

			//플레이어의 턴
			while (player->Energy > 0 && !StageClearFlag)
			{
				if (player->MaxEnergy == player->Energy)
				{
					sprintf(Statement, "나의 턴!");
					RenewScreen(player, enemyArr, enemyCnt);
				}
				int Selection;

				while (1)//잘못된 입력 검출 로직
				{
					printf("무엇을 할까?\n>> ");
					scanf("%d", &Selection);
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
			sprintf(Statement, "상대의 턴!");
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
				}
			}
			//end of turn
			OnTurnEnd(player, enemyArr, enemyCnt);
		}
		//end of stage
		//reward logic
		DestroyEnemyArr(enemyArr,enemyCnt);
		PrintStageClearScreen(RoundIdx);
	}
	//exit stage
	//set stage pointer to next stage
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
		char tempEffectStatement[10] = "타격";
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
		printf("대상 : ");
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
			printf("대상 : ");
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

		RenewScreen(player, enemyArr, enemyCnt);
		break;
	case RANGE:
		if (!player->CanUseRange)
		{
			sprintf(Statement, "절단을 사용할 수 없다!");
			return 0;
		}
		if (PlayerRangeAttack(player, enemyArr, enemyCnt))
			PrintEffect(sel, 1);
		RenewScreen(player, enemyArr, enemyCnt);
		break;
	case DEFENSE:
		if (!player->CanUseDefense)
		{
			sprintf(Statement, "수비를 사용할 수 없다!");
			return 0;
		}
		Player_Defense(player);
		RenewScreen(player, enemyArr, enemyCnt);
		break;
	case SKILL:
		if (!player->CanUseSkill || !player->HasSkill)
		{
			if(!player->CanUseSkill)
				sprintf(Statement, "스킬을 사용할 수 없다!");

			if(!player->HasSkill)
				sprintf(Statement, "스킬을 보유하고 있지 않습니다.");
			return 0;
		}
		
		//스킬
		break;
	case PLAYERINFO:
		//내 정보
		break;
	case ENEMYINFO:
		//적 정보
		break;
	case GAMEINFO:
		//게임 정보
		break;
	case QUIT:
		//종료
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
	Reward** rewardArr = (Reward*)malloc(RewardNum * sizeof(Reward*));
	//보상 배열 세팅
	for (int i = 0; i < RewardNum; i++)
	{
		GenerateRewardNo(rewardArr[i], player);
		SetReward(rewardArr[i]);
	}
	//선택지 배열 출력
	//선택지 입력
	int Sel;
	scanf("%d", &Sel);
	Sel--;

	ApplyReward(rewardArr[Sel], player);
	//보상 확인 결과 출력
}