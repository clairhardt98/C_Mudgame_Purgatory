#define _CRT_SECURE_NO_WARNINGS

#include "UI.h"
#include "Intro.h"
#include "Player.h"



int main()
{
	//���� �����غ�
	int Selection;
	ClearUI();
	Intro();

	//�÷��̾� ����
	Player* player = InitPlayer();
	PrintRoundUI();
	PrintMenuUI();
	//DrawPlayer();

	while (1)
	{
		PrintScreen();
		printf("������ �ұ�? ");
		printf(">> ");
		Selection = _getch();
		
		system("cls");
	}

}
