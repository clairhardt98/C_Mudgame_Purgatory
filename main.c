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

	//�÷��̾� ����
	Player* player = InitPlayer();
	//�������� ����
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
			//�������� ���� �ȳ� ���
			int seed = rand();

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
			if (StageClearFlag)
			{
				//DestroyEnemyArr(enemyArr,enemyCnt);
				break;
			}
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
	//�� ǥ��
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
		if (!player->CanUseMelee)
		{
			sprintf(Statement, "Ÿ���� ����� �� ����!");
			return 0;
		}

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
		if (!player->CanUseRange)
		{
			sprintf(Statement, "������ ����� �� ����!");
			return 0;
		}
		if (PlayerRangeAttack(player, enemyArr, enemyCnt))
			PrintEffect(sel, 1);
		RenewScreen(player, enemyArr, enemyCnt);
		break;
	case DEFENSE:
		if (!player->CanUseDefense)
		{
			sprintf(Statement, "���� ����� �� ����!");
			return 0;
		}
		Player_Defense(player);
		RenewScreen(player, enemyArr, enemyCnt);
		break;
	case SKILL:
		if (!player->CanUseSkill || !player->HasSkill)
		{
			if(!player->CanUseSkill)
				sprintf(Statement, "��ų�� ����� �� ����!");

			if(!player->HasSkill)
				sprintf(Statement, "��ų�� �����ϰ� ���� �ʽ��ϴ�.");
			return 0;
		}
		
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
		//�����ذ�ȵ�
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
	//�� �� �� �����
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
	//���� �迭 ����
	for (int i = 0; i < RewardNum; i++)
	{
		GenerateRewardNo(rewardArr[i], player);
		SetReward(rewardArr[i]);
	}
	//������ �迭 ���
	//������ �Է�
	int Sel;
	scanf("%d", &Sel);
	Sel--;

	ApplyReward(rewardArr[Sel], player);
	//���� Ȯ�� ��� ���
}