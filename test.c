#include <Windows.h>
#include <stdio.h>
#include <string.h>

int main()
{
	char test1[10] = "apple";
	char test2[10] = "apple";
	char test3[100] = "";
	sprintf(test3, "\033[31m%s\033[0m", test2);
	/*printf("%s\n", test1);
	printf("%s\n", test2);
	printf("%s\n", test3);*/
	printf("test2 length : %d\n", strlen(test2));
	printf("test3 length : %d\n", strlen(test3));
}