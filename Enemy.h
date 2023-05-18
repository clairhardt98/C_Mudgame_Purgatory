#pragma once
#include "stdlib.h"
#include "stdio.h"

#define MAXENEMY 3
#define ENEMY_SPRITE_HEIGHT 7
#define ENEMY_SPRITE_WIDTH 23

#define ENEMY_INTERVAL 2

#define ENEMY_SPRITE_STARTPOS_I 7
#define ENEMY_SPRITE_STARTPOS_J 50

#define ENEMY_NAME_POS_I 5
#define ENEMY_NAME_POS_J 63

char EnemySprite[ENEMY_SPRITE_HEIGHT][ENEMY_SPRITE_WIDTH];

typedef struct
{
	char Name[20];
	unsigned int MaxHP;
	unsigned int CurrHP;

	unsigned int Attack;
	unsigned int Defense;

	unsigned int Armour;

	int EnemyNo;

	float AttackDmgMultiplier;
	float ArmourMultiplier;
	float HitDmgMultiplier;
}Enemy;

Enemy* InitEnemy(int);
void DestroyEnemy(Enemy*);
Enemy** SpawnEnemy(int);
void DestroyEnemyArr(Enemy**);

void SetRandomEnemyName(Enemy*,int);
void DisplayEnemyName(Enemy*);

//void Enemy_Attack(Enemy*, Player*);
void Enemy_Defense(Enemy*);
void Enemy_Hit(Enemy*, int);
void Enemy_Die(Enemy*);

void CreateEnemySpriteArr();
void DrawEnemy(int);

int getLine(FILE*);

Enemy* InitEnemy(int seed)
{
	
	Enemy* enemy = (Enemy*)malloc(sizeof(Enemy));

	enemy->MaxHP = 10;
	enemy->CurrHP = enemy->MaxHP;
	enemy->Attack = 6;
	enemy->Defense = 3;

	enemy->Armour = 0;

	enemy->AttackDmgMultiplier = 1.0f;
	enemy->ArmourMultiplier = 1.0f;
	enemy->HitDmgMultiplier = 1.0f;

	SetRandomEnemyName(enemy,seed);
	return enemy;

}

void DestroyEnemy(Enemy* enemy)
{
	free(enemy);
}

Enemy** SpawnEnemy(int EnemyCnt)
{
	srand(time(NULL));
	Enemy **enemyArr = (Enemy**)malloc(EnemyCnt * sizeof(Enemy*));
	for (int i = 0; i < EnemyCnt; i++)
	{
		int seed = rand();
		enemyArr[i] = InitEnemy(seed);
		enemyArr[i]->EnemyNo = i;
		CreateEnemySpriteArr();
		DrawEnemy(enemyArr[i]->EnemyNo);
		
		DisplayEnemyName(enemyArr[i]);
		//체력 출력
		
	}
	return enemyArr;
}

void DestroyEnemyArr(Enemy** enemyArr)
{
	int length = sizeof(enemyArr) / sizeof(enemyArr[0]);
	for (int i = 0; i < length; i++)
	{
		free(enemyArr[i]);
	}
	free(enemyArr);
	ClearUI();
}
//void Enemy_Attack(Enemy* enemy, Player* player)
//{
//	int eDmg = (int)((float)enemy->Attack * enemy->AttackDmgMultiplier);
//	if (eDmg > 0)
//		Player_Hit(player, eDmg);
//}

void Enemy_Defense(Enemy* enemy)
{
	enemy->Armour += (int)((float)enemy->Defense * enemy->ArmourMultiplier);
}

void Enemy_Hit(Enemy* enemy, int Dmg)
{
	enemy->CurrHP -= Dmg;
	//피 0되면 죽는 로직
}

void CreateEnemySpriteArr()
{
	strcpy(EnemySprite[0], "            O      ^   ");
	strcpy(EnemySprite[1], "           | |    //   ");
	strcpy(EnemySprite[2], "         /|   |\\ //    ");
	strcpy(EnemySprite[3], "       [/]|   | %      ");
	strcpy(EnemySprite[4], "          || ||        ");
	strcpy(EnemySprite[5], "          || ||        ");
	strcpy(EnemySprite[6], "         === ===       ");
}

void DrawEnemy(int idx)
{
	if (idx == 0)
		idx = 1;
	else if (idx == 1)
		idx = 0;

	for (int i = 0; i < ENEMY_SPRITE_HEIGHT; i++)
		for (int j = 0; j < ENEMY_SPRITE_WIDTH; j++)
			ScreenArray[ENEMY_SPRITE_STARTPOS_I + i][ENEMY_SPRITE_STARTPOS_J + idx * (ENEMY_INTERVAL + ENEMY_SPRITE_WIDTH) + j] = EnemySprite[i][j];
}

void DisplayEnemyName(Enemy* enemy)
{
	int idx = enemy->EnemyNo;

	if (idx == 0)
		idx = 1;
	else if (idx == 1)
		idx = 0;

	PrintSentence(enemy->Name, strlen(enemy->Name), ENEMY_NAME_POS_I, ENEMY_NAME_POS_J + idx * (ENEMY_INTERVAL + ENEMY_SPRITE_WIDTH));
}

void SetRandomEnemyName(Enemy* enemy,int seed)
{
	//srand(time(NULL));
	FILE* fp = fopen("PurgatoryMobNameList.txt", "r");
	int length = getLine(fp);
	int random = seed % length;
	printf("Random : %d\n", random);

	for (int i = 0; i < length; i++)
	{
		fscanf(fp, "%s", enemy->Name);
		if (i == random) break;
	}
	fclose(fp);
}

int getLine(FILE* fp)
{
	int length = 0;
	char c;
	while ((c = fgetc(fp)) != EOF)
	{
		if (c == '\n')
			length++;
	}
	fseek(fp, 0, SEEK_SET);
	return length;
}