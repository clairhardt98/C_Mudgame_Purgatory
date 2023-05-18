#pragma once

#include <stdio.h>
#include <conio.h>
#include <Windows.h>

#define UIROW 40
#define UICOL 128

char ScreenArray[UIROW][UICOL];

void ClearUI();
void PrintScreen();
void PrintSentence(char*, int, int, int);
void PrintRoundUI();
void PrintMenuUI();

void PrintScreen()
{
	system("mode con cols=128 lines=43");


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

void PrintSentence(char* Sentence, int Length, int Startpos_i, int Startpos_j)
{
	for (int j = 0; j < Length; j++)
		ScreenArray[Startpos_i][Startpos_j + j - Length/2] = Sentence[j];
}

void PrintRoundUI()
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

	ScreenArray[VerticalStartPos / 2][HorizontalStartPos / 2] = '/';
}

void PrintMenuUI()
{
	int HorizontalStartPos = 50;
	int VerticalStartPos = 26;

	for (int i = HorizontalStartPos; i < UICOL - 1; i++)
		ScreenArray[VerticalStartPos][i] = '-';
	for (int i = VerticalStartPos; i < UIROW - 1; i++)
		ScreenArray[i][HorizontalStartPos] = '|';

	ScreenArray[VerticalStartPos][UICOL - 1] = '+';
	ScreenArray[UIROW - 1][HorizontalStartPos] = '+';
	ScreenArray[VerticalStartPos][HorizontalStartPos] = '+';
}