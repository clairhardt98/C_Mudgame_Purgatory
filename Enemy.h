#pragma once
#include "Player.h"
#define MAXENEMY 3

typedef struct
{
	unsigned int Attack;
	unsigned int Defense;

	unsigned int HP;
	unsigned int CurrHP;
}Enemy;

void Enemy_Hit(Enemy*, int);

void Enemy_Hit(Enemy* enemy, int Dmg)
{
	enemy->CurrHP -= Dmg;
	//피 0되면 죽는 로직
}
