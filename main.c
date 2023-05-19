#include "UI.h"
#include "Intro.h"
#include "Battle.h"

bool StageClearFlag;

void RenewScreen(Player*, Enemy**, int);
bool PlayerAction(int, Player*, Enemy**, int);
void TurnEnd(Player*, Enemy**, int);
void PrintEffect(int, int);

int main()
{
	int Selection;
	ClearUI();
	Intro();

	//플레이어 생성
	Player* player = InitPlayer();

	//CreateEnemySpriteArr();

	while (!StageClearFlag)
	{
		//enter stage
		//alloc enemy arr
		int enemyCnt = 3;
		StageClearFlag = false;
		Enemy** enemyArr = SpawnEnemy(enemyCnt);//디버깅 -> 일단 세마리 소환
		RenewScreen(player, enemyArr, enemyCnt);
		//enter battle
		while (1)
		{
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
			if (StageClearFlag) break;
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
					sprintf(Statement, "상대 %s의 행동", enemyArr[i]->Name);
					RenewScreen(player, enemyArr, enemyCnt);
					Sleep(2000);
				}
			}
			//end of turn
			TurnEnd(player, enemyArr, enemyCnt);
		}
		//end of stage
		//reward logic
		DestroyEnemyArr(enemyArr);
	}
	//exit stage
	//set stage pointer to next stage
}

void RenewScreen(Player* player, Enemy** enemyArr, int enemyCnt)
{
	system("cls");
	ClearUI();
	DrawUI();
	DrawPlayer();
	DrawPlayerHP(player);
	DrawPlayerEnergy(player);
	DrawEnemyArr(enemyArr, enemyCnt);
	DrawStatement();
	PrintScreen();
}

void PrintEffect(int sel, int target)
{
	switch (sel)
	{
	case 1:
	{
		char tempEffectStatement[10] = "타격";
		ClearStatement();
		DrawSentenceCenterAlign(tempEffectStatement, strlen(tempEffectStatement),
			STATEMENT_DRAW_POS_I, STATEMENT_DRAW_POS_J);
		DrawMeleeAttackEffect(target);
		break;
	}
	case 2:
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
	if (sel < 1 || sel>8) return 0;//잘못된 입력이라면 false 리턴

	switch (sel)
	{
	case 1:
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
	case 2:
		if (PlayerRangeAttack(player, enemyArr, enemyCnt))
			PrintEffect(sel, 1);
		RenewScreen(player, enemyArr, enemyCnt);
		break;
	case 3:
		Player_Defense(player);
		RenewScreen(player, enemyArr, enemyCnt);
		break;
	case 4:
		//스킬
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	}
	if (IsAllEnemyDead(enemyArr, enemyCnt)) StageClearFlag = true;
	return 1;
}

void TurnEnd(Player* player, Enemy** enemyArr, int enemyCnt)
{
	player->Energy = player->MaxEnergy;
	player->Armour = 0;
}

