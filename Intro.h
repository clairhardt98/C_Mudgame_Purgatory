#pragma once
#include "UI.h"

void Intro();
void PrintFirstIntroSentence();
void PrintSecondIntroSentence();
void PrintThirdIntroSentence();

void Intro()
{
	int temp;
	PrintFirstIntroSentence();
	PrintScreen();
	printf(">>");
	temp = _getch();

	PrintSecondIntroSentence();
	PrintScreen();
	printf(">>");
	temp = _getch();

	PrintThirdIntroSentence();
	PrintScreen();
	printf(">>");
	temp = _getch();

	ClearUI();
}

void PrintFirstIntroSentence()
{
	char Sentence[40] = "You open your eyes in the dark.";
	int Length = strlen(Sentence);
	DrawSentenceCenterAlign(Sentence, Length, UIROW / 2, UICOL / 2);
}

void PrintSecondIntroSentence()
{
	ClearUI();
	char Sentence[74] = "Looking around, you find an rusty sword and shield.";
	int Length = strlen(Sentence);
	DrawSentenceCenterAlign(Sentence, Length, UIROW / 2, UICOL / 2);
}

void PrintThirdIntroSentence()
{
	ClearUI();
	char Sentence[61] = "You lead a heavy body and move.";
	int Length = strlen(Sentence);
	DrawSentenceCenterAlign(Sentence, Length, UIROW / 2, UICOL / 2);
}//