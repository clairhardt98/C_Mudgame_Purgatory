#pragma once
#include "Skill.h"
#include <stdlib.h>

typedef struct
{
	unsigned int Attack;
	unsigned int Defense;
	unsigned int Energy;

}Player;

Player* InitPlayer()
{
	Player* player = (Player*)malloc(sizeof(Player));
	player->Attack = 5;
	player->Defense = 5;
	player->Energy = 3;

	return player;
}