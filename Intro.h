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
	char Sentence[40] = "당신은 어둠속에서 눈을 뜹니다";
	int Length = strlen(Sentence);
	DrawSentenceCenterAlign(Sentence, Length, UIROW / 2, UICOL / 2);
}

void PrintSecondIntroSentence()
{
	ClearUI();
	char Sentence[74] = "주위를 둘러본 당신은 녹슨 검과 방패를 발견합니다";
	int Length = strlen(Sentence);
	DrawSentenceCenterAlign(Sentence, Length, UIROW / 2, UICOL / 2);
}

void PrintThirdIntroSentence()
{
	ClearUI();
	char Sentence[61] = "당신은 무거운 몸을 이끌고 나아갑니다";
	int Length = strlen(Sentence);
	DrawSentenceCenterAlign(Sentence, Length, UIROW / 2, UICOL / 2);
}//