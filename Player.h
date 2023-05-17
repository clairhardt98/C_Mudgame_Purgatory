#pragma once
#include "Skill.h"
#include "Enemy.h"
#include <stdlib.h>

typedef struct
{
	unsigned int MaxHP;
	unsigned int CurrHP;

	unsigned int Attack;
	unsigned int Defense;

	unsigned int Energy;
	unsigned int MaxEnergy;

	unsigned int Armour;

	unsigned int MeleeAttackEnergyNeeded;
	unsigned int RangeAttackEnergyNeeded;

	float AttackDmgMultiplier;
	float ArmourMultiplier;
	float HitDmgMultiplier;

}Player;

Player* InitPlayer();
void DestroyPlayer(Player*);

void Player_MeleeAttack(Player*, Enemy*);
void Player_RangeAttack(Player*, Enemy**);
void Player_Defense(Player*);
void Player_Hit(Player*, int);
void Player_Die(Player*);

void DrawPlayer();


Player* InitPlayer()
{
	Player* player = (Player*)malloc(sizeof(Player));
	player->Attack = 5;
	player->Defense = 5;

	player->MaxEnergy = 3;
	player->Energy = player->MaxEnergy;

	player->Armour = 0;

	player->MaxHP = 60;
	player->CurrHP = player->MaxHP;

	player->AttackDmgMultiplier = 1;
	player->ArmourMultiplier = 1;
	player->HitDmgMultiplier = 1;

	return player;
}

void DestroyPlayer(Player* player)
{
	free(player);
}

void Player_MeleeAttack(Player* player, Enemy* enemy)
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

void Player_RangeAttack(Player* player, Enemy** enemy)
{
	if (player->Energy >= player->MeleeAttackEnergyNeeded)
	{
		int Dmg = (int) ((float)player->Attack * player->AttackDmgMultiplier);
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

void Player_Defense(Player* player)
{
	player->Armour += (int)(player->Defense * player->ArmourMultiplier);
}

void Player_Hit(Player* player, int Dmg)
{
	int eDmg = player->Armour - (int)((float)Dmg * player->HitDmgMultiplier);

	if (eDmg < 0)
	{
		player->CurrHP -= eDmg;
		player->Armour = 0;
	}
	else
	{
		player->Armour -= eDmg;
	}
}

void Player_Die(Player* player)
{
	//사망 시 로직
}

