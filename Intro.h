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
	char Sentence[40] = "����� ��Ҽӿ��� ���� ��ϴ�";
	int Length = strlen(Sentence);
	DrawSentenceCenterAlign(Sentence, Length, UIROW / 2, UICOL / 2);
}

void PrintSecondIntroSentence()
{
	ClearUI();
	char Sentence[74] = "������ �ѷ��� ����� �콼 �˰� ���и� �߰��մϴ�";
	int Length = strlen(Sentence);
	DrawSentenceCenterAlign(Sentence, Length, UIROW / 2, UICOL / 2);
}

void PrintThirdIntroSentence()
{
	ClearUI();
	char Sentence[61] = "����� ���ſ� ���� �̲��� ���ư��ϴ�";
	int Length = strlen(Sentence);
	DrawSentenceCenterAlign(Sentence, Length, UIROW / 2, UICOL / 2);
}//