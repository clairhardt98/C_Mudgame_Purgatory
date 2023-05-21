#pragma once
#include <stdlib.h>


//#include <time.h>

extern int RewardNum;
#define NORMAL_NUM 2
#define HARD_NUM 3
#define RANDOM_NUM 3
#define UNIQUE_NUM 5
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
	char Name[20];
	char Discription[60];
	int RewardNo;
}Reward;

void GenerateRewardNo(Reward*, Player*);
void SetRewardNo(Reward*);
void ApplyReward(Reward*, Player*);
void PrintRewardScreen(Reward**,int);

void ApplyRewardNo0(Player*);
void ApplyRewardNo1(Player*);
void ApplyRewardNo2(Player*);
void ApplyRewardNo3(Player*);
void ApplyRewardNo4(Player*);
void ApplyRewardNo5(Player*);
void ApplyRewardNo6(Player*);
void ApplyRewardNo7(Player*);
void ApplyRewardNo8(Player*);
void ApplyRewardNo9(Player*);
void ApplyRewardNo10(Player*);
void ApplyRewardNo11(Player*);
void ApplyRewardNo12(Player*);

void GenerateRewardNo(Reward* reward, Player* player)
{
	srand(time(NULL));
	int temp;
	if (player->HasUniqueReward)
		temp = rand() % 100;
	else
		temp = rand() % 95;
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
		reward->RewardNo = HardNo;

	}
	else if (temp >= 70 && temp < 95)
	{
		//random
		srand(time(NULL));
		int RandomNo = rand() % RANDOM_NUM;
		reward->RewardNo = RandomNo;
	}
	else
	{
		srand(time(NULL));
		int UniqueNo = rand() % UNIQUE_NUM;
		reward->RewardNo = UniqueNo;
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
		break;
	case 1:
		reward->Rank = NORMAL;
		strcpy(reward->Name, "두꺼운 방패");
		strcpy(reward->Discription, "방어력 + 1");		
		break;
	case 2:
		reward->Rank = HARD;
		strcpy(reward->Name, "과격한 공격");
		strcpy(reward->Discription, "공격력 + 2 방어력 - 1");
		break;
	case 3:
		reward->Rank = HARD;
		strcpy(reward->Name, "난폭한 공격");
		strcpy(reward->Discription, "공격력 + 3 방어력 - 2");
		break;
	case 4:
		reward->Rank = HARD;
		strcpy(reward->Name, "방패병의 비애");
		strcpy(reward->Discription, "방어력 + 2 공격력 - 1");
		break;
	case 5:
		reward->Rank = RANDOM;
		strcpy(reward->Name, "아귀");
		strcpy(reward->Discription, "공격력과 방어력이 랜덤하게 -1 ~ +1");
		break;
	case 6:
		reward->Rank = RANDOM;
		strcpy(reward->Name, "짝귀");
		strcpy(reward->Discription, "공격력과 방어력이 랜덤하게 -2 ~ +2");
		break;
	case 7:
		reward->Rank = RANDOM;
		strcpy(reward->Name, "마귀");
		strcpy(reward->Discription, "공격력과 방어력이 랜덤하게 -3 ~ +3");
		break;
	case 8:
		reward->Rank = UNIQUE;
		strcpy(reward->Name, "사무라이");
		strcpy(reward->Discription, "공격력 + 4 절단을 사용할 수 없음");
		break;
	case 9:
		reward->Rank = UNIQUE;
		strcpy(reward->Name, "기본기 숙련");
		strcpy(reward->Discription, "공격력 + 2 스킬을 사용할 수 없음");
		break;
	case 10:
		reward->Rank = UNIQUE;
		strcpy(reward->Name, "광전사");
		strcpy(reward->Discription, "에너지 + 2 수비를 사용할 수 없음");
		break;
	case 11:
		reward->Rank = UNIQUE;
		strcpy(reward->Name, "날렵한 검객");
		strcpy(reward->Discription, "공격력 + 4 절단을 사용할 수 없음");
		break;
	case 12:
		reward->Rank = UNIQUE;
		strcpy(reward->Name, "풍성한 식탁");
		strcpy(reward->Discription, "앞으로 받는 보상의 선택지 + 1");
		break;
	}
}
void ApplyReward(Reward* reward, Player* player)
{
	switch (reward->RewardNo)
	{
	case 0:
		ApplyRewardNo0(reward, player);
		break;
	case 1:
		ApplyRewardNo1(reward, player);
		break;
	case 2:
		ApplyRewardNo2(reward, player);
		break;
	case 3:
		ApplyRewardNo3(reward, player);
		break;
	case 4:
		ApplyRewardNo4(reward, player);
		break;
	case 5:
		ApplyRewardNo5(reward, player);
		break;
	case 6:
		ApplyRewardNo6(reward, player);
		break;
	case 7:
		ApplyRewardNo7(reward, player);
		break;
	case 8:
		ApplyRewardNo8(reward, player);
		break;
	case 9:
		ApplyRewardNo9(reward, player);
		break;
	case 10:
		ApplyRewardNo10(reward, player);
		break;
	case 11:
		ApplyRewardNo11(reward, player);
		break;
	case 12:
		ApplyRewardNo12(reward, player);
		break;
	}
}

void ApplyRewardNo0(Player* player)
{
	player->Attack += 1;
}
void ApplyRewardNo1(Player* player)
{
	player->Defense += 1;
}
void ApplyRewardNo2(Player* player)
{
	player->Attack += 2;
	player->Defense -= 1;
}
void ApplyRewardNo3(Player* player)
{
	player->Attack += 3;
	player->Defense -= 2;
}
void ApplyRewardNo4(Player* player)
{
	player->Attack -= 1;
	player->Defense += 2;
}
void ApplyRewardNo5(Player* player)
{
	srand(time(NULL));
	int tempAttackVar = rand() % 3 - 1;
	if (player->Attack + tempAttackVar > 1)
		player->Attack += tempAttackVar;
	else player->Attack = 1;

	srand(time(NULL));
	int tempDefenseVar = rand() % 3 - 1;
	if (player->Defense + tempDefenseVar > 0)
		player->Defense += tempDefenseVar;
	else player->Defense = 0;
}
void ApplyRewardNo6(Player* player)
{
	srand(time(NULL));
	int tempAttackVar = rand() % 5 - 2;
	if (player->Attack + tempAttackVar > 1)
		player->Attack += tempAttackVar;
	else player->Attack = 1;

	srand(time(NULL));
	int tempDefenseVar = rand() % 5 - 2;
	if (player->Defense + tempDefenseVar > 0)
		player->Defense += tempDefenseVar;
	else player->Defense = 0;
}
void ApplyRewardNo7(Player* player)
{
	srand(time(NULL));
	int tempAttackVar = rand() % 7 - 3;
	if (player->Attack + tempAttackVar > 1)
		player->Attack += tempAttackVar;
	else player->Attack = 1;

	srand(time(NULL));
	int tempDefenseVar = rand() % 7 - 3;
	if (player->Defense + tempDefenseVar > 0)
		player->Defense += tempDefenseVar;
	else player->Defense = 0;

}
void ApplyRewardNo8(Player* player)
{
	player->Attack += 4;
	player->CanUseRange = false;
	player->HasUniqueReward = true;
}
void ApplyRewardNo9(Player* player)
{
	player->Attack += 2;
	player->CanUseRange = false;
	player->HasUniqueReward = true;
}
void ApplyRewardNo10(Player* player)
{
	player->MaxEnergy += 2;
	player->CanUseDefense = false;
	player->HasUniqueReward = true;
}
void ApplyRewardNo11(Player* player)
{
	player->MaxEnergy += 1;
	player->CanUseRange = false;
	player->HasUniqueReward = true;
}
void ApplyRewardNo12(Player* player)
{
	RewardNum += 1;
	player->HasUniqueReward = true;
}

