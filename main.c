#include "UI.h"
#include "Intro.h"
#include "Battle.h"



int main()
{
	int Selection;
	ClearUI();
	Intro();

	//�÷��̾� ����
	Player* player = InitPlayer();
	PrintRoundUI();
	PrintMenuUI();
	//CreateEnemySpriteArr();
	
	while (1)
	{
		PrintRoundUI();
		PrintMenuUI();
		DrawPlayer();
		PrintScreen();
		printf("������ �ұ�? ");
		printf(">> ");
		scanf("%d", &Selection);
		
		Enemy** enemyArr = SpawnEnemy(Selection);
		PrintScreen();
		printf("������ �ұ�? ");
		printf(">> ");
		scanf("%d", &Selection);
		DestroyEnemyArr(enemyArr);
		system("cls");
	}
	
}
