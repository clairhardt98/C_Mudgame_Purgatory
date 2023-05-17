#pragma once

#include <stdio.h>
#include <conio.h>
#include <Windows.h>

#define UIROW 40
#define UICOL 128

char ScreenArray[UIROW][UICOL];
void PrintScreen();
void ClearUI();
void PrintSentence(char*, int, int, int);

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