#define _CRT_SECURE_NO_WARNINGS

#include "UI.h"
#include "Intro.h"
#include "Player.h"

int main()
{
	int temp;
	
	ClearUI();
	Intro();

	Player* player = InitPlayer();
	
	while (1)
	{
		PrintScreen();
		printf("무엇을 할까? ");
		printf(">> ");
		temp = _getch();
		
		system("cls");
	}

}
