#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>


int i; // 반복문
int input; // 입력받는 숫자의 갯수
int count = 0; // 숫자 

void player_turn()
{
	printf("숫자를 몇 개 부르시겠습니까? ");
	scanf_s("%d", &input);

	while (1)
	{
		if (input > 3 || input < 1)
		{
			printf("다시 입력해주세요. ");
			scanf_s("%d", &input);
		}
		else
			break;
	}

	printf("\n");
	printf("플레이어의 턴 : ");

	for (i = 0; i < input; i++)
	{
		count++;
		printf("%d ", count);
		Sleep(300);
		if (count == 31)
		{
			printf("\n");
			printf("게임이 종료되었습니다. ");
			Sleep(100);
			exit(0);
		}

	}

	printf("\n");

}


int main()
{
	srand(time(NULL)); // 랜덤 위해서
	while (1)
		player_turn();
}
