#pragma once
#include <stdlib.h>


extern int RewardNum;
#define NORMAL_NUM 2
#define HARD_NUM 3
#define RANDOM_NUM 3
#define UNIQUE_NUM 5

#define REWARD_POS_I 17
#define REWARD_POS_J 28
#define REWARD_INTERVAL 5

typedef enum
{
	NORMAL,
	HARD,
	RANDOM,
	UNIQUE
}RewardRank;

typedef struct
{
	RewardRank Rank;
	char RankStr[10];
	char Name[20];
	char Discription[60];
	int RewardNo;
}Reward;

void GenerateRewardNo(Reward*, Player*,int);
void SetRewardNo(Reward*);
void ApplyReward(Reward*, Player*);
void PrintRewardScreen(Reward**,int);
void DrawRewardScreen(Reward*, int);


void GenerateRewardNo(Reward* reward, Player* player, int seed)
{
	
	int temp;
	if (player->HasUniqueReward)
		temp = seed % 100;
	else
		temp = seed % 95;

	if (temp >= 0 && temp < 40)
	{
		srand(time(NULL));
		int NormalNo = rand() % NORMAL_NUM;
		
		reward->RewardNo = NormalNo;
		//normal
	}
	else if (temp >= 40 && temp < 70)
	{
		//hard
		srand(time(NULL));
		int HardNo = rand() % HARD_NUM;
		
		reward->RewardNo = NORMAL_NUM + HardNo;

	}
	else if (temp >= 70 && temp < 95)
	{
		//random
		srand(time(NULL));
		int RandomNo = rand() % RANDOM_NUM;
		
		reward->RewardNo = NORMAL_NUM + HARD_NUM + RandomNo;
	}
	else
	{
		srand(time(NULL));
		int UniqueNo = rand() % UNIQUE_NUM;
		
		reward->RewardNo = NORMAL_NUM + HARD_NUM + RANDOM_NUM + UniqueNo;
		//unique
	}
}
void SetReward(Reward* reward)
{
	switch (reward->RewardNo)
	{
	case 0:
		reward->Rank = NORMAL;
		strcpy(reward->Name, "숫돌");
		strcpy(reward->Discription, "공격력 + 1");
		strcpy(reward->RankStr, "NORMAL");
		break;
	case 1:
		reward->Rank = NORMAL;
		strcpy(reward->Name, "두꺼운 방패");
		strcpy(reward->Discription, "방어력 + 1");		
		strcpy(reward->RankStr, "NORMAL");
		break;
	case 2:
		reward->Rank = HARD;
		strcpy(reward->Name, "사나운 타격");
		strcpy(reward->Discription, "공격력 + 2 방어력 - 1");
		strcpy(reward->RankStr, "HARD");
		break;
	case 3:
		reward->Rank = HARD;
		strcpy(reward->Name, "난폭한 타격");
		strcpy(reward->Discription, "공격력 + 3 수비력 - 2");
		strcpy(reward->RankStr, "HARD");

		break;
	case 4:
		reward->Rank = HARD;
		strcpy(reward->Name, "방패병의 비애");
		strcpy(reward->Discription, "방어력 + 2 수비력 - 1");
		strcpy(reward->RankStr, "HARD");

		break;
	case 5:
		reward->Rank = RANDOM;
		strcpy(reward->Name, "아귀");
		strcpy(reward->Discription, "공격력과 방어력이 랜덤하게 변화 : -1 ~ +1");
		strcpy(reward->RankStr, "RANDOM");

		break;
	case 6:
		reward->Rank = RANDOM;
		strcpy(reward->Name, "짝귀");
		strcpy(reward->Discription, "공격력과 방어력이 랜덤하게 변화 : -2 ~ +2");
		strcpy(reward->RankStr, "RANDOM");

		break;
	case 7:
		reward->Rank = RANDOM;
		strcpy(reward->Name, "마귀");
		strcpy(reward->Discription, "공격력과 방어력이 랜덤하게 변화 : -3 ~ +3");
		strcpy(reward->RankStr, "RANDOM");

		break;
	case 8:
		reward->Rank = UNIQUE;
		strcpy(reward->Name, "사무라이");
		strcpy(reward->Discription, "Attack + 4 Cannot Use Range");
		strcpy(reward->RankStr, "UNIQUE");

		break;
	case 9:
		reward->Rank = UNIQUE;
		strcpy(reward->Name, "기본기 숙련");
		strcpy(reward->Discription, "Attack + 2 Cannot Use Skill");
		strcpy(reward->RankStr, "UNIQUE");

		break;
	case 10:
		reward->Rank = UNIQUE;
		strcpy(reward->Name, "광전사");
		strcpy(reward->Discription, "에너지 + 2 Cannot Use Defense");
		strcpy(reward->RankStr, "UNIQUE");

		break;
	case 11:
		reward->Rank = UNIQUE;
		strcpy(reward->Name, "날렵한 검객");
		strcpy(reward->Discription, "에너지 + 1 Cannot Use Range");
		strcpy(reward->RankStr, "UNIQUE");

		break;
	case 12:
		reward->Rank = UNIQUE;
		strcpy(reward->Name, "풍성한 식탁");
		strcpy(reward->Discription, "앞으로 받을 보상의 선택지 + 1");
		strcpy(reward->RankStr, "UNIQUE");

		break;
	}
}
void ApplyReward(Reward* reward, Player* player)
{
	int tempAttackVar = 0;
	int tempDefenseVar = 0;
	switch (reward->RewardNo)
	{
	case 0:
		player->Attack += 1;
		break;
	case 1:
		player->Defense += 1;
		break;
	case 2:
		player->Attack += 2;
		if(player->Defense - 1 >=0)
			player->Defense -= 1;
		break;
	case 3:
		player->Attack += 3;
		if (player->Defense - 2 >= 0)
			player->Defense -= 2;
		break;
	case 4:
		if (player->Attack - 1 >= 0)
			player->Attack -= 1;
		player->Defense += 2;
		break;
	case 5:
		srand(time(NULL));
		tempAttackVar = rand() % 3 - 1;
		if (player->Attack + tempAttackVar > 1)
			player->Attack += tempAttackVar;
		else player->Attack = 1;

		srand(time(NULL));
		tempDefenseVar = rand() % 3 - 1;
		if (player->Defense + tempDefenseVar > 0)
			player->Defense += tempDefenseVar;
		else player->Defense = 0;
		break;
	case 6:
		srand(time(NULL));
		tempAttackVar = rand() % 5 - 2;
		if (player->Attack + tempAttackVar > 1)
			player->Attack += tempAttackVar;
		else player->Attack = 1;

		srand(time(NULL));
		tempDefenseVar = rand() % 5 - 2;
		if (player->Defense + tempDefenseVar > 0)
			player->Defense += tempDefenseVar;
		else player->Defense = 0;
		break;
	case 7:
		srand(time(NULL));
		tempAttackVar = rand() % 7 - 3;
		if (player->Attack + tempAttackVar > 1)
			player->Attack += tempAttackVar;
		else player->Attack = 1;

		srand(time(NULL));
		tempDefenseVar = rand() % 7 - 3;
		if (player->Defense + tempDefenseVar > 0)
			player->Defense += tempDefenseVar;
		else player->Defense = 0;
		break;
	case 8:
		player->Attack += 4;
		player->CanUseRange = false;
		player->HasUniqueReward = true;
		break;
	case 9:
		player->Attack += 2;
		player->CanUseRange = false;
		player->HasUniqueReward = true;
		break;
	case 10:
		player->MaxEnergy += 2;
		player->CanUseDefense = false;
		player->HasUniqueReward = true;
		break;
	case 11:
		player->MaxEnergy += 1;
		player->CanUseRange = false;
		player->HasUniqueReward = true;
		break;
	case 12:
		RewardNum += 1;
		player->HasUniqueReward = true;
		break;
	}
}
//
//void ApplyRewardNo0(Player* player)
//{
//	player->Attack += 1;
//}
//void ApplyRewardNo1(Player* player)
//{
//	player->Defense += 1;
//}
//void ApplyRewardNo2(Player* player)
//{
//	player->Attack += 2;
//	player->Defense -= 1;
//}
//void ApplyRewardNo3(Player* player)
//{
//	player->Attack += 3;
//	player->Defense -= 2;
//}
//void ApplyRewardNo4(Player* player)
//{
//	player->Attack -= 1;
//	player->Defense += 2;
//}
//void ApplyRewardNo5(Player* player)
//{
//	srand(time(NULL));
//	int tempAttackVar = rand() % 3 - 1;
//	if (player->Attack + tempAttackVar > 1)
//		player->Attack += tempAttackVar;
//	else player->Attack = 1;
//
//	srand(time(NULL));
//	int tempDefenseVar = rand() % 3 - 1;
//	if (player->Defense + tempDefenseVar > 0)
//		player->Defense += tempDefenseVar;
//	else player->Defense = 0;
//}
//void ApplyRewardNo6(Player* player)
//{
//	srand(time(NULL));
//	int tempAttackVar = rand() % 5 - 2;
//	if (player->Attack + tempAttackVar > 1)
//		player->Attack += tempAttackVar;
//	else player->Attack = 1;
//
//	srand(time(NULL));
//	int tempDefenseVar = rand() % 5 - 2;
//	if (player->Defense + tempDefenseVar > 0)
//		player->Defense += tempDefenseVar;
//	else player->Defense = 0;
//}
//void ApplyRewardNo7(Player* player)
//{
//	srand(time(NULL));
//	int tempAttackVar = rand() % 7 - 3;
//	if (player->Attack + tempAttackVar > 1)
//		player->Attack += tempAttackVar;
//	else player->Attack = 1;
//
//	srand(time(NULL));
//	int tempDefenseVar = rand() % 7 - 3;
//	if (player->Defense + tempDefenseVar > 0)
//		player->Defense += tempDefenseVar;
//	else player->Defense = 0;
//
//}
//void ApplyRewardNo8(Player* player)
//{
//	player->Attack += 4;
//	player->CanUseRange = false;
//	player->HasUniqueReward = true;
//}
//void ApplyRewardNo9(Player* player)
//{
//	player->Attack += 2;
//	player->CanUseRange = false;
//	player->HasUniqueReward = true;
//}
//void ApplyRewardNo10(Player* player)
//{
//	player->MaxEnergy += 2;
//	player->CanUseDefense = false;
//	player->HasUniqueReward = true;
//}
//void ApplyRewardNo11(Player* player)
//{
//	player->MaxEnergy += 1;
//	player->CanUseRange = false;
//	player->HasUniqueReward = true;
//}
//void ApplyRewardNo12(Player* player)
//{
//	RewardNum += 1;
//	player->HasUniqueReward = true;
//}

void PrintRewardScreen(Reward** rewardArr, int RewardNum)
{
	char rewardStr[10] = "REWARD!!";
	DrawSentenceCenterAlign(rewardStr, strlen(rewardStr), 5, 63);
	for (int i = 0; i < RewardNum; i++)
	{
		DrawRewardScreen(rewardArr[i], i);
	}
}

void DrawRewardScreen(Reward* reward, int RewardNum)
{
	char tempRewardStr[100];
	sprintf(tempRewardStr, "%d. %s [%s] : %s", RewardNum + 1, reward->Name, reward->RankStr, reward->Discription);
	DrawSentenceLeftAlign(tempRewardStr, strlen(tempRewardStr), REWARD_POS_I + RewardNum * REWARD_INTERVAL, REWARD_POS_J);
}