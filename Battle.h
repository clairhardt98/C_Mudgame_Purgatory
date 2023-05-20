#pragma once
#include <string.h>
#include <stdbool.h>
#include "Player.h"
#include "Enemy.h"

#define MELEE_ATTACK_EFFECT_POS_I
#define MELEE_ATTACK_EFFECT_POS_J

#define RANGE_ATTACK_EFFECT_POS_I 10
#define RANGE_ATTACK_EFFECT_POS_J 88



void PlayerMeleeAttack(Player*, Enemy*);
bool PlayerRangeAttack(Player*, Enemy**, int);

EnemyPattern SetEnemyAction(Enemy*, int);
void DrawEnemyAction(Enemy*);
void EnemyAction(Player*, Enemy*);

void EnemyAttack(Enemy*, Player*);

void PlayerMeleeAttack(Player* player, Enemy* enemy)
{
	//printf("������ : %d, �ʿ� ������ : %d\n", player->Energy, player->MeleeAttackEnergyNeeded);
	if (player->Energy >= player->MeleeAttackEnergyNeeded)
	{
		int Dmg = (int)((float)player->Attack * player->AttackDmgMultiplier);
		if (Dmg > 0)
			Enemy_Hit(enemy, Dmg);
		player->Energy -= player->MeleeAttackEnergyNeeded;
	}
	else
	{
		//������ ������ ���ϰ��ݸ�� ������ �� ����
	}

	//���� �ִϸ��̼� ��� ����

}

void EnemyAttack(Enemy* enemy, Player* player)
{

	int Dmg = (int)((float)enemy->Attack * enemy->AttackDmgMultiplier);
	if (Dmg > 0)
		Player_Hit(player, Dmg);
}

bool PlayerRangeAttack(Player* player, Enemy** enemyArr, int enemyCnt)
{
	if (player->Energy >= player->RangeAttackEnergyNeeded)
	{
		int Dmg = (int)((float)player->Attack * player->AttackDmgMultiplier);
		if (Dmg > 0)
		{
			for (int i = 0; i < enemyCnt; i++)
			{
				if (enemyArr[i]->isAlive)
					Enemy_Hit(enemyArr[i], Dmg);
			}
		}
		player->Energy -= player->RangeAttackEnergyNeeded;
		return 1;
	}
	else
	{
		sprintf(Statement, "�������� �����մϴ�!");
		return 0;
	}
	//�������� �ִϸ��̼� ��� ����
}

void DrawRangeAttackEffect()
{
	char RangeAttackEffect[70] = "<===============================================================>";

	DrawSentenceCenterAlign(RangeAttackEffect, strlen(RangeAttackEffect),
		RANGE_ATTACK_EFFECT_POS_I, RANGE_ATTACK_EFFECT_POS_J - 2);

	PrintScreen();
	Sleep(1000);
}

void DrawMeleeAttackEffect(int enemyNo)
{

	int EffectStartPos_i = ENEMY_SPRITE_STARTPOS_I;
	int EffectStartPos_j;
	if (enemyNo == 0)
		EffectStartPos_j = 9 + ENEMY_SPRITE_STARTPOS_J + ENEMY_INTERVAL + ENEMY_SPRITE_WIDTH;
	else if (enemyNo == 1)
		EffectStartPos_j = 9 + ENEMY_SPRITE_STARTPOS_J;
	else
		EffectStartPos_j = 9 + ENEMY_SPRITE_STARTPOS_J + 2 * (ENEMY_INTERVAL + ENEMY_SPRITE_WIDTH);

	for (int i = 0; i < ENEMY_SPRITE_HEIGHT; i++)
		for (int j = 0; j < ENEMY_SPRITE_WIDTH; j++)
		{
			if (j == i)
				DrawSentenceCenterAlign("\\", 1, EffectStartPos_i + i, EffectStartPos_j + j);
		}
	PrintScreen();
	Sleep(1000);
}

EnemyPattern SetEnemyAction(Enemy* enemy, int seed)
{
	int temp = seed % 10;
	EnemyPattern EPattern;
	if (temp == 0)
	{
		EPattern = ENEMYATTACKWITHWEAKEN;
	}
	else if (temp > 0 && temp <= 2)
	{
		EPattern = ENEMYWEAKEN;
	}
	else if (temp > 2 && temp <= 4)
	{
		EPattern = ENEMYDEFENSE;
	}
	else
	{
		EPattern = ENEMYATTACK;
	}
	return EPattern;
}

void DrawEnemyAction(Enemy* enemy)
{
	switch (enemy->NextPattern)
	{
	case ENEMYATTACK:
	{
		sprintf(enemy->NextPatternStr, "!%d", enemy->Attack);
		break;
	}

	case ENEMYDEFENSE:
	{
		sprintf(enemy->NextPatternStr, "@%d", enemy->Defense);
		//�� ��� �Լ�
		break;
	}

	case ENEMYWEAKEN:
	{
		sprintf(enemy->NextPatternStr, "#%d", enemy->WeakenDuration);
		//��ȭ �Լ�
		break;
	}

	case ENEMYATTACKWITHWEAKEN:
	{
		sprintf(enemy->NextPatternStr, "!%d #%d", enemy->Attack / 2, enemy->WeakenDuration / 2);
		break;
	}

	}
}

void EnemyAction(Player* player, Enemy* enemy)
{
	switch (enemy->NextPattern)
	{
	case ENEMYATTACK:
	{
		sprintf(Statement, "��� %d. %s�� ����!", enemy->EnemyNo + 1, enemy->Name);
		EnemyAttack(enemy, player);
		break;
	}

	case ENEMYDEFENSE:
	{
		sprintf(Statement, "��� %d. %s�� ���!", enemy->EnemyNo + 1, enemy->Name);
		Enemy_Defense(enemy);
		break;
	}

	case ENEMYWEAKEN:
	{
		sprintf(Statement, "��� %d. %s�� ��ȭ!", enemy->EnemyNo + 1, enemy->Name);
		//��ȭ �Լ�
		break;
	}

	case ENEMYATTACKWITHWEAKEN:
	{
		sprintf(Statement, "��� %d. %s�� �ļ�!", enemy->EnemyNo + 1, enemy->Name);
		//���� �����ϰ� ��ȭ��Ű�� �Լ�
		break;
	}

	}
	//Ȯ�� -> ���� 50, ���� 20, ��ȭ 20, ���� �� ��ȭ 10
	//0~9�� rand�� �̴´� ->0 : ���� �� ��ȭ, 1~2 : ��ȭ, 3~4 : ���� 5~9 : ����
}
