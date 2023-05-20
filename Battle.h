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
	//printf("에너지 : %d, 필요 에너지 : %d\n", player->Energy, player->MeleeAttackEnergyNeeded);
	if (player->Energy >= player->MeleeAttackEnergyNeeded)
	{
		int Dmg = (int)((float)player->Attack * player->AttackDmgMultiplier);
		if (Dmg > 0)
			Enemy_Hit(enemy, Dmg);
		player->Energy -= player->MeleeAttackEnergyNeeded;
	}
	else
	{
		//에너지 없을때 단일공격명령 내렸을 때 로직
	}

	//공격 애니메이션 출력 로직

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
		sprintf(Statement, "에너지가 부족합니다!");
		return 0;
	}
	//광역공격 애니메이션 출력 로직
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
		//적 방어 함수
		break;
	}

	case ENEMYWEAKEN:
	{
		sprintf(enemy->NextPatternStr, "#%d", enemy->WeakenDuration);
		//약화 함수
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
		sprintf(Statement, "상대 %d. %s의 공격!", enemy->EnemyNo + 1, enemy->Name);
		EnemyAttack(enemy, player);
		break;
	}

	case ENEMYDEFENSE:
	{
		sprintf(Statement, "상대 %d. %s의 방어!", enemy->EnemyNo + 1, enemy->Name);
		Enemy_Defense(enemy);
		break;
	}

	case ENEMYWEAKEN:
	{
		sprintf(Statement, "상대 %d. %s의 약화!", enemy->EnemyNo + 1, enemy->Name);
		//약화 함수
		break;
	}

	case ENEMYATTACKWITHWEAKEN:
	{
		sprintf(Statement, "상대 %d. %s의 파쇄!", enemy->EnemyNo + 1, enemy->Name);
		//적이 공격하고 약화시키는 함수
		break;
	}

	}
	//확률 -> 공격 50, 수비 20, 약화 20, 공격 및 약화 10
	//0~9를 rand로 뽑는다 ->0 : 공격 및 약화, 1~2 : 약화, 3~4 : 수비 5~9 : 공격
}
