#include "UI.h"
#include "Intro.h"
#include "Battle.h"

bool StageClearFlag;

void RenewScreen(Player*, Enemy**, int);
bool PlayerAction(int, Player*, Enemy**, int);
void TurnEnd(Player*, Enemy**, int);
void PrintEffect(int, int);
void PrepareEnemyArr(Enemy**, int);
void OnPlayerTurnEnd(Player*, Enemy**, int);

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

	//�÷��̾� ����
	Player* player = InitPlayer();

	//CreateEnemySpriteArr();

	while (!StageClearFlag)
	{
		//enter stage
		//alloc enemy arr
		int enemyCnt = 3;
		StageClearFlag = false;
		Enemy** enemyArr = SpawnEnemy(enemyCnt);//����� -> �ϴ� ������ ��ȯ
		RenewScreen(player, enemyArr, enemyCnt);
		//enter battle
		while (1)
		{
			PrepareEnemyArr(enemyArr, enemyCnt);
			RenewScreen(player, enemyArr, enemyCnt);
			//�÷��̾��� ��
			while (player->Energy > 0 && !StageClearFlag)
			{
				if (player->MaxEnergy == player->Energy)
				{
					sprintf(Statement, "���� ��!");
					RenewScreen(player, enemyArr, enemyCnt);
				}
				int Selection;

				while (1)//�߸��� �Է� ���� ����
				{
					printf("������ �ұ�?\n>> ");
					scanf("%d", &Selection);
					//�÷��̾� ����
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
			OnPlayerTurnEnd(player, enemyArr, enemyCnt);
			Sleep(2000);
			sprintf(Statement, "����� ��!");
			RenewScreen(player, enemyArr, enemyCnt);
			Sleep(2000);
			//����� ��
			for (int i = 0; i < enemyCnt; i++)
			{
				if (enemyArr[i]->isAlive)
				{
					//enemy task
					//sprintf(Statement, "��� %s�� �ൿ", enemyArr[i]->Name);
					EnemyAction(player, enemyArr[i]);
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
		char tempEffectStatement[10] = "Ÿ��";
		ClearStatement();
		DrawSentenceCenterAlign(tempEffectStatement, strlen(tempEffectStatement),
			STATEMENT_DRAW_POS_I, STATEMENT_DRAW_POS_J);
		DrawMeleeAttackEffect(target);
		break;
	}
	case RANGE:
	{
		char tempEffectStatement[10] = "����!";
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
	if (sel < 1 || sel > 8) return 0;//�߸��� �Է��̶�� false ����

	enum PlayerActionEnum  playeractionenum = sel;

	switch (playeractionenum)
	{
	case MELEE:
		//melee attack logic
		printf("��� : ");
		for (int i = 0; i < enemyCnt; i++)
		{
			if (enemyArr[i]->isAlive)
				printf("%d. %s ", i + 1, enemyArr[i]->Name);
		}
		printf("\n>> ");
		int targetEnemy;
		scanf("%d", &targetEnemy);
		//�߸��� �Է� ����

		while ((targetEnemy > enemyCnt) || (targetEnemy <= 0) || !enemyArr[targetEnemy - 1]->isAlive)
		{
			RenewScreen(player, enemyArr, enemyCnt);
			printf("��� : ");
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
		if (PlayerRangeAttack(player, enemyArr, enemyCnt))
			PrintEffect(sel, 1);
		RenewScreen(player, enemyArr, enemyCnt);
		break;
	case DEFENSE:
		Player_Defense(player);
		RenewScreen(player, enemyArr, enemyCnt);
		break;
	case SKILL:
		//��ų
		break;
	case PLAYERINFO:
		//�� ����
		break;
	case ENEMYINFO:
		//�� ����
		break;
	case GAMEINFO:
		//���� ����
		break;
	case QUIT:
		//����
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

void PrepareEnemyArr(Enemy** enemyArr, int enemyCnt)
{
	int seed;
	srand(time(NULL));
	for (int i = 0; i < enemyCnt && enemyArr[i]->isAlive; i++)
	{
		//�����ذ�ȵ�
		seed = rand();
		enemyArr[i]->NextPattern = SetEnemyAction(enemyArr[i], seed);
		DrawEnemyAction(enemyArr[i]);
		DrawEnemyPatternStr(enemyArr[i]);
	}
}

void OnPlayerTurnEnd(Player* player, Enemy** enemyArr, int enemyCnt)
{
	//�� �� �� �����
	for (int i = 0; i < enemyCnt; i++)
	{
		if (enemyArr[i]->isAlive)
			enemyArr[i]->Armour = 0;
	}
	//����� -1
}