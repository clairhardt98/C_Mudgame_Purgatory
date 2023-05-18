#define _CRT_SECURE_NO_WARNINGS

#include "UI.h"
#include "Intro.h"
#include "Player.h"



int main()
{
	//게임 시작준비
	int Selection;
	ClearUI();
	Intro();

	//플레이어 생성
	Player* player = InitPlayer();
	PrintRoundUI();
	PrintMenuUI();
	//DrawPlayer();

	while (1)
	{
		PrintScreen();
		printf("무엇을 할까? ");
		printf(">> ");
		Selection = _getch();
		
		system("cls");
	}

}
