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
	char Sentence[31] = "당신은 어둠속에서 눈을 뜹니다.";
	int Length = strlen(Sentence);
	PrintSentence(Sentence, Length, UIROW / 2, UICOL / 2);
}

void PrintSecondIntroSentence()
{
	ClearUI();
	char Sentence[52] = "주변을 살펴보던 당신은 낡은 검과 방패를 발견합니다.";
	int Length = strlen(Sentence);
	PrintSentence(Sentence, Length, UIROW / 2, UICOL / 2);
}

void PrintThirdIntroSentence()
{
	ClearUI();
	char Sentence[49] = "당신은 자리에서 일어나 무거운 발걸음을 옮깁니다.";
	int Length = strlen(Sentence);
	PrintSentence(Sentence, Length, UIROW / 2, UICOL / 2);
}