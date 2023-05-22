#pragma once

#include <stdio.h>
#include <conio.h>
#include <Windows.h>


#define UIROW 40
#define UICOL 128

#define MENU_BOX_WIDTH 77
#define MENU_BOX_HEIGHT 10

#define MENU_BOX_STARTPOS_I 30
#define MENU_BOX_STARTPOS_J 50

#define STATEMENT_MAXLENGTH 60
#define STATEMENT_ARRSIZE 5

#define STATEMENT_DRAW_POS_I 28
#define STATEMENT_DRAW_POS_J 88

char ScreenArray[UIROW][UICOL];
char Statement[STATEMENT_MAXLENGTH + 1];
int StatementPrintCnt = 0;//

void ClearUI();
void PrintScreen();
void DrawSentenceCenterAlign(char*, int, int, int);
void DrawSentenceLeftAlign(char*, int, int, int);
void DrawUI();
void DrawRoundUI();
void DrawMenuUI();
void DrawPlayerMenuUI();
void DrawInfoMenuUI();
void DrawMenuSentence();
void DrawStatement();

void PrintScreen()
{
	system("mode con cols=128 lines=47");


	for (int i = 0; i < UIROW; i++)
	{
		for (int j = 0; j < UICOL; j++)
		{
			printf("%c", ScreenArray[i][j]);
		}
		printf("\n");
	}

}

void ClearUI()
{
	//printf("%p", &ScreenArray[10][10]);
	for (int i = 0; i < UIROW; i++)
	{
		for (int j = 0; j < UICOL; j++)
		{
			//각 꼭지점 + 찍기
			if ((i == 0 && j == 0) || (i == 0 && j == UICOL - 1) || (i == UIROW - 1 && j == 0) || (i == UIROW - 1 && j == UICOL - 1))
				ScreenArray[i][j] = '+';

			else if (i == 0 || i == UIROW - 1)
				ScreenArray[i][j] = '-';
			else if (j == 0 || j == UICOL - 1)
				ScreenArray[i][j] = '|';
			else
				ScreenArray[i][j] = ' ';
		}
	}
}

void DrawSentenceCenterAlign(char* Sentence, int Length, int Startpos_i, int Startpos_j)
{
	for (int j = 0; j < Length; j++)
		ScreenArray[Startpos_i][Startpos_j + j - Length / 2] = Sentence[j];
}

void DrawSentenceLeftAlign(char* Sentence, int Length, int Startpos_i, int Startpos_j)
{
	for (int j = 0; j < Length; j++)
		ScreenArray[Startpos_i][Startpos_j + j] = Sentence[j];
}

void DrawRoundUI()
{
	int HorizontalStartPos = 16;
	int VerticalStartPos = 4;
	for (int i = 1; i < HorizontalStartPos; i++)
		ScreenArray[VerticalStartPos][i] = '-';
	for (int i = 1; i < VerticalStartPos; i++)
		ScreenArray[i][HorizontalStartPos] = '|';

	ScreenArray[VerticalStartPos][0] = '+';
	ScreenArray[0][HorizontalStartPos] = '+';
	ScreenArray[VerticalStartPos][HorizontalStartPos] = '+';

	//ScreenArray[VerticalStartPos / 2][HorizontalStartPos / 2] = '/';
}

void DrawMenuUI()
{
	for (int i = MENU_BOX_STARTPOS_J; i < MENU_BOX_STARTPOS_J + MENU_BOX_WIDTH; i++)
		ScreenArray[MENU_BOX_STARTPOS_I][i] = '-';
	for (int i = MENU_BOX_STARTPOS_I; i < MENU_BOX_STARTPOS_I + MENU_BOX_HEIGHT; i++)
		ScreenArray[i][MENU_BOX_STARTPOS_J] = '|';

	ScreenArray[MENU_BOX_STARTPOS_I][MENU_BOX_STARTPOS_J + MENU_BOX_WIDTH] = '+';
	ScreenArray[MENU_BOX_STARTPOS_I + MENU_BOX_HEIGHT - 1][MENU_BOX_STARTPOS_J] = '+';
	ScreenArray[MENU_BOX_STARTPOS_I][MENU_BOX_STARTPOS_J] = '+';
}

void DrawPlayerMenuUI()
{
	int PlayerMenuWidth = MENU_BOX_WIDTH / 2 - 3;
	int PlayerMenuHeight = MENU_BOX_HEIGHT - 2;
	int StartPos_I = MENU_BOX_STARTPOS_I + 1;
	int StartPos_J = MENU_BOX_STARTPOS_J + 2;

	for (int i = StartPos_I; i < StartPos_I + PlayerMenuHeight; i++)
	{
		ScreenArray[i][StartPos_J] = '|';
		ScreenArray[i][StartPos_J + PlayerMenuWidth] = '|';
	}

	for (int i = StartPos_J; i < StartPos_J + PlayerMenuWidth; i++)
	{
		ScreenArray[StartPos_I][i] = '-';
		ScreenArray[StartPos_I + PlayerMenuHeight - 1][i] = '-';
	}

	ScreenArray[StartPos_I][StartPos_J] = '+';
	ScreenArray[StartPos_I + PlayerMenuHeight - 1][StartPos_J] = '+';
	ScreenArray[StartPos_I][StartPos_J + PlayerMenuWidth] = '+';
	ScreenArray[StartPos_I + PlayerMenuHeight - 1][StartPos_J + PlayerMenuWidth] = '+';
}

void DrawInfoMenuUI()
{
	int PlayerMenuWidth = MENU_BOX_WIDTH / 2 - 3;
	int PlayerMenuHeight = MENU_BOX_HEIGHT - 2;
	int StartPos_I = MENU_BOX_STARTPOS_I + 1;
	int StartPos_J = MENU_BOX_STARTPOS_J + PlayerMenuWidth + 5;

	for (int i = StartPos_I; i < StartPos_I + PlayerMenuHeight; i++)
	{
		ScreenArray[i][StartPos_J] = '|';
		ScreenArray[i][StartPos_J + PlayerMenuWidth] = '|';
	}

	for (int i = StartPos_J; i < StartPos_J + PlayerMenuWidth; i++)
	{
		ScreenArray[StartPos_I][i] = '-';
		ScreenArray[StartPos_I + PlayerMenuHeight - 1][i] = '-';
	}

	ScreenArray[StartPos_I][StartPos_J] = '+';
	ScreenArray[StartPos_I + PlayerMenuHeight - 1][StartPos_J] = '+';
	ScreenArray[StartPos_I][StartPos_J + PlayerMenuWidth] = '+';
	ScreenArray[StartPos_I + PlayerMenuHeight - 1][StartPos_J + PlayerMenuWidth] = '+';
}

void DrawUI()
{
	DrawRoundUI();
	DrawMenuUI();
	DrawPlayerMenuUI();
	DrawInfoMenuUI();
	DrawMenuSentence();
	//DrawStatement();
}

void DrawMenuSentence()
{
	char MeleeAttackStr[20] = "1. 타격";
	char RangeAttackStr[20] = "2. 절단";
	char DefenseStr[20] = "3. 수비";
	char SkillStr[20] = "4. ???";
	char PlayerInfoStr[20] = "5. 내 정보";
	char EnemyInfoStr[20] = "6. 상대 정보";
	char GameInfoStr[20] = "7. 게임 정보";
	char SaveQuitStr[20] = "8. 종료";

	DrawSentenceLeftAlign(MeleeAttackStr, strlen(MeleeAttackStr), MENU_BOX_STARTPOS_I + 3, MENU_BOX_STARTPOS_J + 5);
	DrawSentenceLeftAlign(RangeAttackStr, strlen(RangeAttackStr), MENU_BOX_STARTPOS_I + 3, MENU_BOX_STARTPOS_J + MENU_BOX_WIDTH / 4 + 4);
	DrawSentenceLeftAlign(DefenseStr, strlen(DefenseStr), MENU_BOX_STARTPOS_I + 6, MENU_BOX_STARTPOS_J + 5);
	DrawSentenceLeftAlign(SkillStr, strlen(SkillStr), MENU_BOX_STARTPOS_I + 6, MENU_BOX_STARTPOS_J + MENU_BOX_WIDTH / 4 + 4);
	DrawSentenceLeftAlign(PlayerInfoStr, strlen(PlayerInfoStr), MENU_BOX_STARTPOS_I + 3, MENU_BOX_STARTPOS_J + MENU_BOX_WIDTH / 2 + 5);
	DrawSentenceLeftAlign(EnemyInfoStr, strlen(EnemyInfoStr), MENU_BOX_STARTPOS_I + 3, MENU_BOX_STARTPOS_J + 3 * MENU_BOX_WIDTH / 4 + 5);
	DrawSentenceLeftAlign(GameInfoStr, strlen(GameInfoStr), MENU_BOX_STARTPOS_I + 6, MENU_BOX_STARTPOS_J + MENU_BOX_WIDTH / 2 + 5);
	DrawSentenceLeftAlign(SaveQuitStr, strlen(SaveQuitStr), MENU_BOX_STARTPOS_I + 6, MENU_BOX_STARTPOS_J + 3 * MENU_BOX_WIDTH / 4 + 5);

}

void DrawStatement()
{
	DrawSentenceCenterAlign(Statement, strlen(Statement), STATEMENT_DRAW_POS_I, STATEMENT_DRAW_POS_J);
	//strcpy(Statement, " ");
}

void ClearStatement()
{
	for (int i = 0; i < STATEMENT_MAXLENGTH; i++)
		Statement[i] = ' ';
	DrawSentenceCenterAlign(Statement, STATEMENT_MAXLENGTH, STATEMENT_DRAW_POS_I, STATEMENT_DRAW_POS_J);
}