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
	if (!strcmp(str, PLAYER))//player->enemy ����
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
			//������ ������ ���ϰ��ݸ�� ������ �� ����
		}

		//���� �ִϸ��̼� ��� ����
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
		//������ ���� �� �������ݸ�� ������ �� ����
	}
	//�������� �ִϸ��̼� ��� ����
}