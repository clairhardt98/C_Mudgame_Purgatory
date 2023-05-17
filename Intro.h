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
	char Sentence[31] = "����� ��Ҽӿ��� ���� ��ϴ�.";
	int Length = strlen(Sentence);
	PrintSentence(Sentence, Length, UIROW / 2, UICOL / 2);
}

void PrintSecondIntroSentence()
{
	ClearUI();
	char Sentence[52] = "�ֺ��� ���캸�� ����� ���� �˰� ���и� �߰��մϴ�.";
	int Length = strlen(Sentence);
	PrintSentence(Sentence, Length, UIROW / 2, UICOL / 2);
}

void PrintThirdIntroSentence()
{
	ClearUI();
	char Sentence[49] = "����� �ڸ����� �Ͼ ���ſ� �߰����� �ű�ϴ�.";
	int Length = strlen(Sentence);
	PrintSentence(Sentence, Length, UIROW / 2, UICOL / 2);
}