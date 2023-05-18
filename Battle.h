#pragma once
#include <string.h>
#include "Player.h"
#include "Enemy.h"

#define PLAYER "PLAYER"
#define ENEMY "ENEMY"

void MeleeAttack(Player*, Enemy*, char* str);
void RangeAttack(Player*, Enemy**);

void MeleeAttack(Player* player, Enemy* enemy, char* str)
{
	if (!strcmp(str, PLAYER))//player->enemy 공격
	{
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
	else
	{
		int eDmg = (int)((float)enemy->Attack * enemy->AttackDmgMultiplier);
		if (eDmg > 0)
			Player_Hit(player, eDmg);
	}
}

void RangeAttack(Player* player, Enemy** enemy)
{
	if (player->Energy >= player->MeleeAttackEnergyNeeded)
	{
		int Dmg = (int)((float)player->Attack * player->AttackDmgMultiplier);
		if (Dmg > 0)
		{
			for (int i = 0; i < MAXENEMY; i++)
			{
				Enemy_Hit(enemy[i], Dmg);
			}
		}
		player->Energy -= player->RangeAttackEnergyNeeded;
	}
	else
	{
		//에너지 없을 때 광역공격명령 내렸을 때 로직
	}
	//광역공격 애니메이션 출력 로직
}