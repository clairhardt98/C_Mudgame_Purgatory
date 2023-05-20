#pragma once
#include "Skill.h"
#include "Enemy.h"
#include <stdlib.h>

#define PLAYER_SPRITE_HEIGHT 17
#define PLAYER_SPRITE_WIDTH 38

#define PLAYER_HP_POS_I 20
#define PLAYER_HP_POS_J 15

#define PLAYER_ENERGY_POS_I PLAYER_HP_POS_I
#define PLAYER_ENERGY_POS_J 33

char PlayerSprite[PLAYER_SPRITE_HEIGHT][PLAYER_SPRITE_WIDTH];

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
	unsigned int DefenseEnergyNeeded;

	float AttackDmgMultiplier;
	float ArmourMultiplier;
	float HitDmgMultiplier;

}Player;

Player* InitPlayer();
void DestroyPlayer(Player*);

//void Player_MeleeAttack(Player*, Enemy*);
//void Player_RangeAttack(Player*, Enemy**);
void Player_Defense(Player*);
void Player_Hit(Player*, int);
void Player_Die(Player*);

void CreatePlayerSpriteArr();
void DrawPlayer();

void DrawPlayerHP(Player*);
void DrawPlayerEnergy(Player*);


Player* InitPlayer()
{
	CreatePlayerSpriteArr();
	DrawPlayer();
	Player* player = (Player*)malloc(sizeof(Player));
	player->Attack = 5;
	player->Defense = 5;

	player->MaxEnergy = 3;
	player->Energy = player->MaxEnergy;

	player->MeleeAttackEnergyNeeded = 1;
	player->RangeAttackEnergyNeeded = 2;
	player->DefenseEnergyNeeded = 1;

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

//void Player_MeleeAttack(Player* player, Enemy* enemy)
//{
//	if (player->Energy >= player->MeleeAttackEnergyNeeded)
//	{
//		int Dmg = (int)((float)player->Attack * player->AttackDmgMultiplier);
//		if (Dmg > 0)
//			Enemy_Hit(enemy, Dmg);
//		player->Energy -= player->MeleeAttackEnergyNeeded;
//	}
//	else
//	{
//		//에너지 없을때 단일공격명령 내렸을 때 로직
//	}
//
//	//공격 애니메이션 출력 로직
//}
//
//void Player_RangeAttack(Player* player, Enemy** enemy)
//{
//	if (player->Energy >= player->MeleeAttackEnergyNeeded)
//	{
//		int Dmg = (int)((float)player->Attack * player->AttackDmgMultiplier);
//		if (Dmg > 0)
//		{
//			for (int i = 0; i < MAXENEMY; i++)
//			{
//				Enemy_Hit(enemy[i], Dmg);
//			}
//		}
//		player->Energy -= player->RangeAttackEnergyNeeded;
//	}
//	else
//	{
//		//에너지 없을 때 광역공격명령 내렸을 때 로직
//	}
//	//광역공격 애니메이션 출력 로직
//}

void Player_Defense(Player* player)
{
	if (player->Energy >= player->DefenseEnergyNeeded)
	{
		int tempArmour = (int)(player->Defense * player->ArmourMultiplier);
		player->Armour += tempArmour;
		player->Energy -= player->DefenseEnergyNeeded;
		sprintf(Statement, "이번 턴 방어도가 %d 증가합니다.", tempArmour);
	}
}

void Player_Hit(Player* player, int Dmg)
{
	//int eDmg = (int)((float)player->Armour - (float)Dmg * player->HitDmgMultiplier);
	int eDmg = player->Armour - Dmg;
	if (eDmg < 0)
	{
		player->CurrHP += eDmg;
		player->Armour = 0;
	}
	else
	{
		player->Armour -= Dmg;
	}
}

void Player_Die(Player* player)
{
	//사망 시 로직
}

void CreatePlayerSpriteArr()
{
	strcpy(PlayerSprite[0], "       _____________            .     ");
	strcpy(PlayerSprite[1], "      /             \\          /|\\    ");
	strcpy(PlayerSprite[2], "     /               \\        / | \\   ");
	strcpy(PlayerSprite[3], "    /                 \\      /  |  \\  ");
	strcpy(PlayerSprite[4], "   |                   |     |  |  |  ");
	strcpy(PlayerSprite[5], "   |                   |     |  |  |  ");
	strcpy(PlayerSprite[6], "   \\                  /      |  |  |  ");
	strcpy(PlayerSprite[7], "    \\                /       |  |  |  ");
	strcpy(PlayerSprite[8], "     \\              /        |  |  |  ");
	strcpy(PlayerSprite[9], "       ------------          |  |  |  ");
	strcpy(PlayerSprite[10], "_________________________    |  |  |  ");
	strcpy(PlayerSprite[11], "                         |   |  |  |  ");
	strcpy(PlayerSprite[12], "                         | -----------");
	strcpy(PlayerSprite[13], "                         | |         |");
	strcpy(PlayerSprite[14], "                         | |         |");
	strcpy(PlayerSprite[15], "                         | -----------");
	strcpy(PlayerSprite[16], "                         |    |   |   ");
}

void DrawPlayer()
{
	//CreatePlayerSpriteArr();
	int PlayerSpriteStartPosI = 22;
	int PlayerSpriteStartPosJ = 1;

	for (int i = 0; i < PLAYER_SPRITE_HEIGHT; i++)
		for (int j = 0; j < PLAYER_SPRITE_WIDTH; j++)
			ScreenArray[PlayerSpriteStartPosI + i][PlayerSpriteStartPosJ + j] = PlayerSprite[i][j];
}

void DrawPlayerHP(Player* player)
{
	char PlayerHPStr[20];
	if(player->Armour > 0)
		sprintf(PlayerHPStr, "%d+(%d) / %d", player->CurrHP, player->Armour, player->MaxHP);
	else
		sprintf(PlayerHPStr, "%d / %d", player->CurrHP, player->MaxHP);
	DrawSentenceCenterAlign(PlayerHPStr, strlen(PlayerHPStr), PLAYER_HP_POS_I, PLAYER_HP_POS_J);
}

void DrawPlayerEnergy(Player* player)
{
	char PlayerEnergyStr[7];
	sprintf(PlayerEnergyStr, "%d / %d", player->Energy, player->MaxEnergy);
	DrawSentenceCenterAlign(PlayerEnergyStr, strlen(PlayerEnergyStr), PLAYER_ENERGY_POS_I, PLAYER_ENERGY_POS_J);
}