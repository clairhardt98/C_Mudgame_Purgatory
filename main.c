#include "UI.h"
#include "Intro.h"
#include "Battle.h"



int main()
{
	int Selection;
	ClearUI();
	Intro();

	//플레이어 생성
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
		printf("무엇을 할까? ");
		printf(">> ");
		scanf("%d", &Selection);
		
		Enemy** enemyArr = SpawnEnemy(Selection);
		PrintScreen();
		printf("무엇을 할까? ");
		printf(">> ");
		scanf("%d", &Selection);
		DestroyEnemyArr(enemyArr);
		system("cls");
	}
	
}
