#pragma once

#include <stdbool.h>
#include "Stage.h"


#define MAXENEMY 3

#define ENEMY_SPRITE_HEIGHT 7
#define ENEMY_SPRITE_WIDTH 23

#define ENEMY_INTERVAL 2

#define ENEMY_SPRITE_STARTPOS_I 7//
#define ENEMY_SPRITE_STARTPOS_J 50

#define ENEMY_NAME_POS_I 5
#define ENEMY_NAME_POS_J 62

#define ENEMY_HEALTH_POS_I 16
#define ENEMY_HEALTH_POS_J ENEMY_NAME_POS_J

#define ENEMY_DAMAGE_POS_I 3
#define ENEMY_DAMAGE_POS_J 62

#define ENEMY_PATTERN_STR_POS_I 3
#define ENEMY_PATTERN_STR_POS_J 62

char EnemySprite[ENEMY_SPRITE_HEIGHT][ENEMY_SPRITE_WIDTH];

typedef enum 
{
	ENEMYATTACK = 1,
	ENEMYDEFENSE,
	ENEMYWEAKEN,
	ENEMYCRUSH
}EnemyPattern;

typedef struct
{
	char Name[20];
	unsigned int MaxHP;
	unsigned int CurrHP;
	int HPRandomVar;

	unsigned int Attack;
	unsigned int Defense;

	unsigned int Armour;

	unsigned int WeakenDuration;

	int EnemyNo;

	bool isAlive;

	float AttackDmgMultiplier;
	float ArmourMultiplier;
	float HitDmgMultiplier;

	EnemyPattern NextPattern;
	char NextPatternStr[10];
}Enemy;

//상대 생성 및 소멸
Enemy* InitEnemy(Stage*,int);
void DestroyEnemy(Enemy*);
Enemy** SpawnEnemy(Stage*);
void DestroyEnemyArr(Enemy**, int);

//출력
void SetRandomEnemyName(Enemy*, int);
void DisplayEnemyName(Enemy*);
//스프라이트 생성 및 출력
void CreateEnemySpriteArr();
void DrawEnemy(int);
void DrawEnemyArr(Enemy**, int);
//체력 출력
void DisplayEnemyHealth(Enemy*);

void DrawEnemyDamage(int, int);

void DrawEnemyPatternStr(Enemy*);

//void Enemy_Attack(Enemy*, Player*);
void Enemy_Defense(Enemy*);
void Enemy_Hit(Enemy*, int);
void Enemy_Die(Enemy*);


bool IsAllEnemyDead(Enemy**, int);

int getLine(FILE*);

Enemy* InitEnemy(Stage* round, int seed)
{
	Enemy* enemy = (Enemy*)malloc(sizeof(Enemy));

	enemy->isAlive = 1;
	enemy->HPRandomVar = round->HPRandomVar;
	enemy->MaxHP = round->MaxHP + seed % enemy->HPRandomVar;
	enemy->CurrHP = enemy->MaxHP;
	enemy->Attack = round->Attack;
	enemy->Defense = round->Defense;
	enemy->WeakenDuration = round->WeakenDuration;

	enemy->Armour = 0;

	enemy->AttackDmgMultiplier = 1.0f;
	enemy->ArmourMultiplier = 1.0f;
	enemy->HitDmgMultiplier = 1.0f;

	enemy->NextPattern = ENEMYATTACK;
	strcpy(enemy->NextPatternStr, "");
	SetRandomEnemyName(enemy, seed);
	return enemy;

}

void DestroyEnemy(Enemy* enemy)
{
	free(enemy);
}

Enemy** SpawnEnemy(Stage* round)
{
	srand(time(NULL));
	int EnemyCnt = round->ToCreateMonsterNum;
	Enemy** enemyArr = (Enemy**)malloc(EnemyCnt * sizeof(Enemy*));
	for (int i = 0; i < EnemyCnt; i++)
	{
		int seed = rand();
		enemyArr[i] = InitEnemy(round, seed);
		enemyArr[i]->EnemyNo = i;
		/*CreateEnemySpriteArr();
		DrawEnemy(enemyArr[i]->EnemyNo);

		DisplayEnemyName(enemyArr[i]);
		DisplayEnemyHealth(enemyArr[i]);*/
	}
	return enemyArr;
}

void DrawEnemyArr(Enemy** enemyArr, int length)
{
	for (int i = 0; i < length; i++)
	{
		if (enemyArr[i]->isAlive)
		{
			CreateEnemySpriteArr();
			DrawEnemy(enemyArr[i]->EnemyNo);

			DisplayEnemyName(enemyArr[i]);
			DisplayEnemyHealth(enemyArr[i]);
		}
	}
}

void DestroyEnemyArr(Enemy** enemyArr, int enemyCnt)
{
	//int length = sizeof(*enemyArr) / sizeof(enemyArr[0]);
	for (int i = 0; i < enemyCnt; i++)
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
	if (enemy->Armour > Dmg)
	{
		enemy->Armour -= Dmg;
	}
	else
	{
		int eDmg = Dmg - enemy->Armour;
		enemy->Armour = 0;
		DrawEnemyDamage(Dmg, enemy->EnemyNo);
		if (eDmg < enemy->CurrHP)
		{
			enemy->CurrHP -= eDmg;
			//sprintf(Statement, "%s가 %d만큼의 피해를 입었습니다.", enemy->Name, Dmg);
		}
		else
		{
			//sprintf(Statement, "%s가 죽었습니다.", enemy->Name);
			DrawEnemyDamage(Dmg, enemy->EnemyNo);
			enemy->CurrHP = 0;
			enemy->isAlive = 0;
		}
	}

	//피 0되면 죽는 로직
//printf("출력문 전달 완료\n");

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

	char tempNoName[30];
	sprintf(tempNoName, "%d. %s", enemy->EnemyNo + 1, enemy->Name);

	DrawSentenceCenterAlign(tempNoName, strlen(tempNoName), ENEMY_NAME_POS_I, ENEMY_NAME_POS_J + idx * (ENEMY_INTERVAL + ENEMY_SPRITE_WIDTH));
}

void SetRandomEnemyName(Enemy* enemy, int seed)
{
	//srand(time(NULL));
	FILE* fp = fopen("PurgatoryMobNameList.txt", "r");
	int length = getLine(fp);
	int random = seed % length;

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

void DisplayEnemyHealth(Enemy* enemy)
{
	int idx = enemy->EnemyNo;

	if (idx == 0)
		idx = 1;
	else if (idx == 1)
		idx = 0;

	char HealthLetter[20] = "";
	/*char CurrHPLetter[4] = "";
	sprintf(CurrHPLetter, "%d", enemy->CurrHP);
	char MaxHPLetter[4] = "";
	sprintf(MaxHPLetter, "%d", enemy->MaxHP);

	strcat(HealthLetter, CurrHPLetter);
	strcat(HealthLetter, " / ");
	strcat(HealthLetter, MaxHPLetter);*/
	if (enemy->Armour > 0)
	{
		sprintf(HealthLetter, "%d+(%d) / %d", enemy->CurrHP, enemy->Armour, enemy->MaxHP);
	}
	else sprintf(HealthLetter, "%d / %d", enemy->CurrHP, enemy->MaxHP);

	DrawSentenceCenterAlign(HealthLetter, strlen(HealthLetter), ENEMY_HEALTH_POS_I, ENEMY_HEALTH_POS_J + idx * (ENEMY_INTERVAL + ENEMY_SPRITE_WIDTH));
}

bool IsAllEnemyDead(Enemy** enemyArr, int enemyCnt)
{
	int DeadEnemyCnt = 0;
	for (int i = 0; i < enemyCnt; i++)
	{
		if (!enemyArr[i]->isAlive) DeadEnemyCnt++;
	}
	if (DeadEnemyCnt == enemyCnt) return true;
	else return false;
}

void DrawEnemyDamage(int Dmg, int enemyNo)
{
	int EnemyDamagePosJ;

	if (enemyNo == 0)
		EnemyDamagePosJ = 12 + ENEMY_SPRITE_STARTPOS_J + ENEMY_INTERVAL + ENEMY_SPRITE_WIDTH;
	else if (enemyNo == 1)
		EnemyDamagePosJ = 12 + ENEMY_SPRITE_STARTPOS_J;
	else
		EnemyDamagePosJ = 12 + ENEMY_SPRITE_STARTPOS_J + 2 * (ENEMY_INTERVAL + ENEMY_SPRITE_WIDTH);

	char DmgStr[10];
	sprintf(DmgStr, "-%d", Dmg);
	DrawSentenceCenterAlign(DmgStr, strlen(DmgStr), ENEMY_DAMAGE_POS_I, EnemyDamagePosJ);
}

void DrawEnemyPatternStr(Enemy* enemy)
{
	int EnemyStrPosJ;

	if (enemy->EnemyNo == 0)
		EnemyStrPosJ = 6 + ENEMY_SPRITE_STARTPOS_J + ENEMY_INTERVAL + ENEMY_SPRITE_WIDTH;
	else if (enemy->EnemyNo == 1)
		EnemyStrPosJ = 6 + ENEMY_SPRITE_STARTPOS_J;
	else
		EnemyStrPosJ = 6 + ENEMY_SPRITE_STARTPOS_J + 2 * (ENEMY_INTERVAL + ENEMY_SPRITE_WIDTH);

	DrawSentenceCenterAlign(enemy->NextPatternStr, strlen(enemy->NextPatternStr), ENEMY_PATTERN_STR_POS_I, EnemyStrPosJ);
}