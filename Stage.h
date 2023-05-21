#pragma once
#include "UI.h"

#define MAXSTAGE 3
#define MAXROUND 10
typedef struct
{
	int StageCnt;

	int RoundCnt;
	int ToCreateMonsterNum;

	int HPRandomVar;
	int MaxHP;
	int Attack;
	int Defense;
	int WeakenDuration;
}Stage;

Stage** InitStageArr();
Stage* InitStage();
void ConfigStage(Stage**);

void PrintStageEnterScreen(int);
void PrintStageClearScreen(int);
void DrawRoundStr(int);

Stage* InitStage()
{
	Stage* stage = (Stage *) malloc(sizeof(Stage));
	return stage;
}
Stage** InitStageArr()
{
	Stage** stageArr = (Stage**)malloc(MAXROUND * sizeof(Stage*));
	for (int i = 0; i < MAXROUND; i++)
	{
		stageArr[i] = InitStage();
	}
	ConfigStage(stageArr);
	return stageArr;
}

void ConfigStage(Stage** stageArr)
{
	//1라운드
	stageArr[0]->StageCnt = 1;
	stageArr[0]->RoundCnt = 1;
	stageArr[0]->ToCreateMonsterNum = 1;
	stageArr[0]->HPRandomVar = 2;
	stageArr[0]->MaxHP = 10;
	stageArr[0]->Attack = 5;
	stageArr[0]->Defense = 3;
	stageArr[0]->WeakenDuration = 2;
	//2라운드
	stageArr[1]->StageCnt = 1;
	stageArr[1]->RoundCnt = 2;
	stageArr[1]->ToCreateMonsterNum = 2;
	stageArr[1]->HPRandomVar = 2;
	stageArr[1]->MaxHP = 10;
	stageArr[1]->Attack = 5;
	stageArr[1]->Defense = 3;
	stageArr[1]->WeakenDuration = 2;
	//3라운드
	stageArr[2]->StageCnt = 1;
	stageArr[2]->RoundCnt = 3;
	stageArr[2]->ToCreateMonsterNum = 3;
	stageArr[2]->HPRandomVar = 2;
	stageArr[2]->MaxHP = 12;
	stageArr[2]->Attack = 5;
	stageArr[2]->Defense = 3;
	stageArr[2]->WeakenDuration = 2;
	//4라운드
	stageArr[3]->StageCnt = 1;
	stageArr[3]->RoundCnt = 4;
	stageArr[3]->ToCreateMonsterNum = 1;
	stageArr[3]->HPRandomVar = 4;
	stageArr[3]->MaxHP = 14;
	stageArr[3]->Attack = 6;
	stageArr[3]->Defense = 4;
	stageArr[3]->WeakenDuration = 3;
	//5라운드
	stageArr[4]->StageCnt = 1;
	stageArr[4]->RoundCnt = 5;
	stageArr[4]->ToCreateMonsterNum = 2;
	stageArr[4]->HPRandomVar = 4;
	stageArr[4]->MaxHP = 14;
	stageArr[4]->Attack = 6;
	stageArr[4]->Defense = 4;
	stageArr[4]->WeakenDuration = 3;
	//6라운드
	stageArr[5]->StageCnt = 1;
	stageArr[5]->RoundCnt = 6;
	stageArr[5]->ToCreateMonsterNum = 3;
	stageArr[5]->HPRandomVar = 4;
	stageArr[5]->MaxHP = 14;
	stageArr[5]->Attack = 6;
	stageArr[5]->Defense = 4;
	stageArr[5]->WeakenDuration = 3;
	//7라운드(중간보스)
	stageArr[6]->StageCnt = 1;
	stageArr[6]->RoundCnt = 7;
	stageArr[6]->ToCreateMonsterNum = 1;
	stageArr[6]->HPRandomVar = 6;
	stageArr[6]->MaxHP = 56;
	stageArr[6]->Attack = 8;
	stageArr[6]->Defense = 5;
	stageArr[6]->WeakenDuration = 3;
	//8라운드
	stageArr[7]->StageCnt = 1;
	stageArr[7]->RoundCnt = 8;
	stageArr[7]->ToCreateMonsterNum = 3;
	stageArr[7]->HPRandomVar = 4;
	stageArr[7]->MaxHP = 16;
	stageArr[7]->Attack = 6;
	stageArr[7]->Defense = 4;
	stageArr[7]->WeakenDuration = 3;
	//9라운드(상점 라운드)
	stageArr[8]->StageCnt = 1;
	stageArr[8]->RoundCnt = 9;
	stageArr[8]->ToCreateMonsterNum = 1;
	stageArr[8]->HPRandomVar = 2;
	stageArr[8]->MaxHP = 18;
	stageArr[8]->Attack = 5;
	stageArr[8]->Defense = 3;
	stageArr[8]->WeakenDuration = 2;
	//19라운드(보스)
	stageArr[9]->StageCnt = 1;
	stageArr[9]->RoundCnt = 19;
	stageArr[9]->ToCreateMonsterNum = 1;
	stageArr[9]->HPRandomVar = 9;
	stageArr[9]->MaxHP = 199;
	stageArr[9]->Attack = 8;
	stageArr[9]->Defense = 3;
	stageArr[9]->WeakenDuration = 3;

}

void PrintStageEnterScreen(int roundIdx)
{
	int temp;
	char str[20];
	sprintf(str, "Round %d", roundIdx + 1);
	ClearUI();
	DrawSentenceCenterAlign(str, strlen(str), UIROW / 2, UICOL / 2);
	PrintScreen();
	temp = _getch();
}

void PrintStageClearScreen(int roundIdx)
{
	int temp;
	char str[20];
	sprintf(str, "Round %d Clear!", roundIdx + 1);
	ClearUI();
	DrawSentenceCenterAlign(str, strlen(str), UIROW / 2, UICOL / 2);
	PrintScreen();
	temp = _getch();
}

void DrawRoundStr(int roundIdx)
{
	char str[20];
	sprintf(str, "Round %d", roundIdx);
	DrawSentenceCenterAlign(str, strlen(str), 2, 8);
}