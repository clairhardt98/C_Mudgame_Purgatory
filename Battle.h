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
