#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <Winsock2.h>
#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <process.h>

#define TIMEFINGER 31 // Use in timing

#define A 97
#define S 115
#define D 100
#define W 119

#define GAME_NUMBER 6
#define RSP 1
#define TIMING 2
#define TAZA 3
#define WASD 4
#define UD 5
#define MY 6

#define Xx 32
#define Ox 32 

#define PORT 4578
#define PACKET_SIZE 1024
#define COM0_IP "192.168.35.99"         //COM0 IP주소 입력

SOCKET hSock, hListen;
int score = 0;
char wasd_made[30] = { 0, };

void tutorial_rsp(); // Game Tutorial
void tutorial_timing();
void tutorial_wasd();
void tutorial_taza();
void tutorial_updown();
void tutorial_memory();

int wasd(); // Game - wasd
void wasd_map();
void wasd_make();

void rsp(); // Game - rsp
void rsp_map();
void rsp_print_r(int x, int y);
void rsp_print_s(int x, int y);
void rsp_print_p(int x, int y);

void timing(); // Game - timing
void timing_print_finger();
void timing_print_line(int i);
void timing_cleanline();

void taza(); // Game - taza
void taza_map();

void updown(); // Game - updown

void memory(); // Game - memory

void ox(int x); // timing & rsp

void start_motion(); // all game
void end_motion(int x);

int menu();   // Other Functions
void score_save();
void check_score();

void rand_start(int* sequence); //게임 순서 랜덤으로 정하기

void textcolor(int color_number);  // Win API Functions
void gotoxy(int x, int y);
void cursorview(char show);
void set_gamesize();

int sock_main(int flag);
int chatting_COM0(SOCKET hCOM1);
int chatting_COM1(SOCKET hCOM0);
void chatting_recv(SOCKET hCOM);
void sock_clean(SOCKET hSock, SOCKET hListen);
int flag_com();

int main()
{

	int start = menu(); // if Enter = start
	int i, game_start[GAME_NUMBER] = { RSP, TIMING, TAZA, WASD, UD, MY }; //게임 순서 정할 때 
	int flag = 0;
	flag = flag_com();

	rand_start(game_start);

	if (start == 1)
	{
		system("cls");
		for (i = 0; i < GAME_NUMBER; i++) {

			if (game_start[i] == RSP) {
				tutorial_rsp();
				fflush(stdin);
				rsp();
			}
			else if (game_start[i] == TIMING)
			{
				tutorial_timing();
				fflush(stdin);
				timing();
			}
			else if (game_start[i] == TAZA)
			{
				tutorial_taza();
				fflush(stdin);
				taza();
			}

			if (game_start[i] == WASD)
			{
				tutorial_wasd();
				fflush(stdin);
				wasd();
			}
			if (game_start[i] == UD)
			{
				tutorial_updown();
				fflush(stdin);
				updown();
			}
			if (game_start[i] == MY)
			{
				tutorial_memory();
				fflush(stdin);
				memory();
			}
		}

		int fin = sock_main(flag);
		system("cls");
		if (fin == TRUE) {
			printf("YOU WIN!!!");
		}
		else if (fin == 2) {
			printf("DRAW!");
		}
		else
			printf("YOU LOSE....");
		score_save();
	}

	sock_clean(hSock, hListen);
	system("pause");
	return 0;
}

int menu()
{
	system("mode con cols=48 lines=37"); // cols = 세로, lines = 가로 
	while (1)
	{
		gotoxy(0, 2);   textcolor(4);   printf("################################################");
		gotoxy(0, 4);   textcolor(7);   printf("             < Mini Game - Party >             ");
		gotoxy(0, 6);   textcolor(4);   printf("################################################"); textcolor(7);

		gotoxy(6, 9);   textcolor(2);   printf("====================================");   textcolor(7);
		gotoxy(6, 10);   printf(":                                  :");
		gotoxy(6, 11);   printf(":  < 게임 설명 >                   :");
		gotoxy(6, 12);   printf(":                                  :");
		gotoxy(6, 13);   printf(":  ◈ 여러 미니게임을 클리어 하자! :");
		gotoxy(6, 14);   printf(":                                  :");
		gotoxy(6, 15);   printf(":  ⊙ 채팅을 통한 더 큰 재미!      :");
		gotoxy(6, 16);   printf(":                                  :");
		gotoxy(6, 17);   printf(":                                  :");
		gotoxy(6, 18);   printf(":                                  :");
		gotoxy(6, 19);   printf(":    < 게임 방법 >                 :");
		gotoxy(6, 20);   printf(":                                  :");
		gotoxy(6, 21);   printf(":  ♤ 매 게임마다 설명 등장!       :");
		gotoxy(6, 22);   printf(":                                  :");
		gotoxy(6, 23);   printf(":  ◑ 설명을 잘 읽어보자!          :");
		gotoxy(6, 24);   printf(":                                  :");
		gotoxy(6, 25);   printf(":  ※ 난이도는 점점 어려워진다!    :");
		gotoxy(6, 26);   printf(":                                  :");
		gotoxy(6, 27);   printf(":                                  :");
		gotoxy(6, 28);   textcolor(2);   printf("===================================="); textcolor(7);

		gotoxy(9, 31);   textcolor(9);   printf("------------------------------"); textcolor(7);
		gotoxy(9, 32);   printf(":       ENTER : start !!     :");
		gotoxy(9, 33);   printf(":       SPACE : exit         :");
		gotoxy(9, 34);   textcolor(9);   printf("------------------------------"); textcolor(7);

		cursorview(0);
		int input;
		input = _getch();

		if (input == 32) // SPACE
		{
			system("cls");
			exit(0);
		}

		else if (input == 13) // ENTER
			return 1;

		else
		{
			system("cls");
			continue;
		}
	}
}

void rsp()
{
	set_gamesize();

	srand(time(NULL));
	int i, leftside, rightside, input, check, save_rsp;
	double start = 0, finish = 0;

	fflush(stdin);
	start_motion();
	for (i = 0; i <= 9; i++)
	{
		system("cls");
		rsp_map();
		leftside = rand() % 3 + 1;
		rightside = rand() % 3 + 1;

		switch (leftside)
		{
		case 1:
			rsp_print_s(5, 3); break;
		case 2:
			rsp_print_r(5, 3); break;
		case 3:
			rsp_print_p(5, 3); break;
		}

		switch (rightside)
		{
		case 1:
			rsp_print_s(67, 3); break;
		case 2:
			rsp_print_r(67, 3); break;
		case 3:
			rsp_print_p(67, 3); break;
		}

		check = (leftside - rightside);
		switch (check)
		{
		case -1:
			save_rsp = 100;
			break;
		case -2:
			save_rsp = A;
			break;
		case 1:
			save_rsp = A;
			break;
		case 2:
			save_rsp = D;
			break;
		default:
			save_rsp = S;
			break;
		}

		start = (int)(time(NULL));
		while (1)
		{
			if (_kbhit())
			{
				input = _getch();
				if (input == save_rsp)
				{
					score++;
					ox(1);
					break;
				}
				else
				{
					ox(0);
					break;
				}
			}
			finish = (int)(time(NULL));
			if (finish - start >= 1.5)
			{
				ox(0);
				break;
			}
		}
	}
	end_motion(score);
	system("cls");
}

void rsp_map()
{
	int i;
	for (i = 0; i <= 40; i++)
	{
		gotoxy(55, i);
		printf("|");
	}
}

void rsp_print_s(int x, int y)
{
	gotoxy(x, y);     printf("  ;*!!*.         .*!:;$;    \n");
	gotoxy(x, y + 1); printf(" .*-....=.        =-....!~   \n");
	gotoxy(x, y + 2); printf(" ;~......=       :;......=  \n");
	gotoxy(x, y + 3); printf(" =,......!,     .$.......=.   \n");
	gotoxy(x, y + 4); printf(" $-.......*     ~!.......*,    \n");
	gotoxy(x, y + 5); printf(" !;.......$.    =........=.  \n");
	gotoxy(x, y + 6); printf(" -=.......;-   ,*........=.   \n");
	gotoxy(x, y + 7); printf("  =,......,!   ;-.......,! \n");
	gotoxy(x, y + 8); printf("   -*.......$   !........*,  \n");
	gotoxy(x, y + 9); printf("    *.......=, .!........=  \n");
	gotoxy(x, y + 10); printf("    -!......~: :-.......$,   \n");
	gotoxy(x, y + 11); printf("     $.......* ;.......=,  \n");
	gotoxy(x, y + 12); printf("     :;......;,;......*-  \n");
	gotoxy(x, y + 13); printf("     ,#.......*~.....;=~;!.  \n");
	gotoxy(x, y + 14); printf("      #............,*......=   \n");
	gotoxy(x, y + 15); printf("     -=...-:;;;::::!.......=!!,  \n");
	gotoxy(x, y + 16); printf("     =,.:=;,......,;*:....-~..!.  \n");
	gotoxy(x, y + 17); printf("    ,=,$:............;;...*...-;  \n");
	gotoxy(x, y + 18); printf("    :;$...............#..~-....=   \n");
	gotoxy(x, y + 19); printf("    *#...............-:..=....,! \n");
	gotoxy(x, y + 20); printf("    =!........~:~--~=~..$.....:,  \n");
	gotoxy(x, y + 21); printf("    =;............*!..-*......!\n");
	gotoxy(x, y + 22); printf("    ;*..............,*#,....,$ \n");
	gotoxy(x, y + 23); printf("    ,#.................,--:=#, \n");
	gotoxy(x, y + 24); printf("     !:....................~= \n");
	gotoxy(x, y + 25); printf("     .#....................!. \n");
	gotoxy(x, y + 26); printf("      ,#..................-#, \n");
	gotoxy(x, y + 27); printf("       ~#~...............:$, \n");
	gotoxy(x, y + 28); printf("        -#=~...,~~,....~=!.\n");
	gotoxy(x, y + 29); printf("          .;==!;:,.;:~:*;.\n");
}

void rsp_print_r(int x, int y)
{
	gotoxy(x, y);     printf("            ,!*!*-      \n");
	gotoxy(x, y + 1); printf("           ,=,...:=.--.   \n");
	gotoxy(x, y + 2); printf("          .=,.....=#*!=!.    \n");
	gotoxy(x, y + 3); printf("          ;:......$....:=      \n");
	gotoxy(x, y + 4); printf("         .=......-,.....*-    \n");
	gotoxy(x, y + 5); printf("         ;~......$......~;,,     \n");
	gotoxy(x, y + 6); printf("         $......~.......-$;=$.     \n");
	gotoxy(x, y + 7); printf("        ,!......$.......~:..-@    \n");
	gotoxy(x, y + 8); printf("       .=:.....-,.......!....:$  \n");
	gotoxy(x, y + 9); printf("     ;#$==-....*........!....,@ \n");
	gotoxy(x, y + 10); printf("   =*....,-!:~;.......,:.....@. \n");
	gotoxy(x, y + 11); printf("  :$.........~=,......!......@=-\n");
	gotoxy(x, y + 12); printf(" .@............:,.....:.....,*.:, \n");
	gotoxy(x, y + 13); printf(" ~:.............!....:,.....~,..$ \n");
	gotoxy(x, y + 14); printf(" #...................;......*...@  \n");
	gotoxy(x, y + 15); printf(".$..................~,.....-;...@ \n");
	gotoxy(x, y + 16); printf(",!....,~............!......!...,$ \n");
	gotoxy(x, y + 17); printf("-~......;~,.....:..!,.....-~...=- \n");
	gotoxy(x, y + 18); printf("~~........:!-,,~;.--......!....@.\n");
	gotoxy(x, y + 19); printf("-!...........---!!@......!....:; \n");
	gotoxy(x, y + 20); printf(".$...............@$,....*.....@  \n");
	gotoxy(x, y + 21); printf(" #...............$.@::$*.....!,  \n");
	gotoxy(x, y + 22); printf(" -;..............;..,.,*....:* \n");
	gotoxy(x, y + 23); printf(" .@....................,;*::*  \n");
	gotoxy(x, y + 24); printf("  -=.......................;-  \n");
	gotoxy(x, y + 25); printf("   !!......................# \n");
	gotoxy(x, y + 26); printf("    **....................!; \n");
	gotoxy(x, y + 27); printf("     ;$-.................;=  \n");
	gotoxy(x, y + 28); printf("      -$=:,....--......-=*.\n");
	gotoxy(x, y + 29); printf("        ~*$$$$=**$!;;*$$: \n");
}

void rsp_print_p(int x, int y)
{
	gotoxy(x, y - 1); printf("                     -.   \n");
	gotoxy(x, y);     printf("                   ,$$#;   \n");
	gotoxy(x, y + 1); printf("                   $-.,$-  \n");
	gotoxy(x, y + 2); printf("         .=@#;    -!...:*  \n");
	gotoxy(x, y + 3); printf("         *=..!~   !~...,$   \n");
	gotoxy(x, y + 4); printf("         #....$   =,....$   .!#*,  \n");
	gotoxy(x, y + 5); printf("        .$....-,  $,....$   =,.;@. \n");
	gotoxy(x, y + 6); printf("        .$.....$  #.....$  ;,...$:  \n");
	gotoxy(x, y + 7); printf("         $.....#. $.....= ,;....*:  \n");
	gotoxy(x, y + 8); printf("         *,....;- =....,= *.....$-  \n");
	gotoxy(x, y + 9); printf("        ::....,; !....~!,~.....#. \n");
	gotoxy(x, y + 10); printf("        -=.....# ;....:-;.....:!  \n");
	gotoxy(x, y + 11); printf("        .#.....#.~....!,~.....#.  \n");
	gotoxy(x, y + 12); printf("         =-....;~-....!;.....~;  \n");
	gotoxy(x, y + 13); printf("         :;.....#,...,*:.....#.~~!#   \n");
	gotoxy(x, y + 14); printf("         -=.....!....:*.....:--,...=   \n");
	gotoxy(x, y + 15); printf("         .$..........,-.....@-.....!  \n");
	gotoxy(x, y + 16); printf("         .$.................~.......$  \n");
	gotoxy(x, y + 17); printf("   ,*=*!~,=.........................;$  \n");
	gotoxy(x, y + 18); printf("  :$-....!#~-......................-#-\n");
	gotoxy(x, y + 19); printf("  @-......!**=*-..................-#~  \n");
	gotoxy(x, y + 20); printf(" ,@,...........-*................~#.  \n");
	gotoxy(x, y + 21); printf("  =#,............*..............#=.\n");
	gotoxy(x, y + 22); printf("   :@!...........,~............=*\n");
	gotoxy(x, y + 23); printf("    .!@~..........!...........@,\n");
	gotoxy(x, y + 24); printf("     ,#;.........,...........@\n");
	gotoxy(x, y + 25); printf("      ,#,.................~=\n");
	gotoxy(x, y + 26); printf("       :=.................#,\n");
	gotoxy(x, y + 27); printf("       ,@,...............:#\n");
	gotoxy(x, y + 28); printf("        !=..............~@, \n");
	gotoxy(x, y + 29); printf("        .=!....~;,.....;@. \n");
	gotoxy(x, y + 30); printf("          *#$$#@=#=;;*##. \n");
}

void timing()
{
	set_gamesize();

	int i, j, input, speed, real_score = 0;
	start_motion();
	for (i = 0; i <= 7; i++)
	{
		system("cls");
		gotoxy(90, 1);      printf(" ㅡㅡㅡㅡㅡㅡㅡㅡㅡ");
		gotoxy(90, 2);      printf(" |                |");
		gotoxy(90, 3);      printf(" |                |");
		gotoxy(90, 4);      printf(" |                |");
		gotoxy(90, 5);      printf(" |                |");
		gotoxy(90, 6);      printf(" |                |");
		gotoxy(90, 7);      printf(" ㅡㅡㅡㅡㅡㅡㅡㅡㅡ");
		for (j = 0; j <= 37; j++)
		{
			timing_print_finger();
			if (_kbhit())
			{
				input = _getch();
				if (j == 34)
				{
					score++;
					real_score++;
					ox(1);
					timing_cleanline();
					timing_print_finger();
					break;
				}
				else
				{
					timing_cleanline();
					break;
				}
			}

			timing_print_line(j);
			speed = 70 - i * 8;
			Sleep(speed);
			gotoxy(100, 4);    printf("%d", real_score);   cursorview(0);
		}
	}
	end_motion(real_score);
	system("cls");
}

void timing_print_finger()
{
	gotoxy(3, 30);   printf("            ,,,.\n");
	gotoxy(3, 31);   printf("         ,,. .,.\n");
	gotoxy(3, 32);   printf(",,,,,..,.    .,,........,.\n");
	gotoxy(3, 33);   printf("-   ,,.                 .,--"); textcolor(4); printf("=\n"); textcolor(7); // *******
	gotoxy(3, 34);   printf("-   ,.        .,,,,,,,,,.\n");
	gotoxy(3, 35);   printf("-   ,.            .-\n");
	gotoxy(3, 36);   printf("-   ,.        .,,,,.\n");
	gotoxy(3, 37);   printf("-   ,.        ....,\n");
	gotoxy(3, 38);   printf("-,,,-. .,,,....,,,\n"); //26칸

	gotoxy(79, 30);   printf("             .,,,.\n");
	gotoxy(79, 31);   printf("            .,. .,,\n");
	gotoxy(79, 32);   printf("  .,,,,,,,,,,,,    .,..,,,,, \n");
	gotoxy(79, 33);   textcolor(4); printf("="); textcolor(7); printf("--,.                 ,,-   ,\n");
	gotoxy(79, 34);   printf("   ,,,,,,,,,,.        .-   ,\n");
	gotoxy(79, 35);   printf("        -,            .-   ,\n");
	gotoxy(79, 36);   printf("        .,,,,.        .-   ,\n");
	gotoxy(79, 37);   printf("         ,....        .-   ,\n");
	gotoxy(79, 38);   printf("          ,,,....,,,. .-,,,-\n");
	cursorview(0);
}

void timing_print_line(int i)
{

	gotoxy(TIMEFINGER, i - 1);   printf("                                                ");
	gotoxy(TIMEFINGER, i);       printf("  ==============================================");   cursorview(0);

}

void timing_cleanline()
{
	int i;
	for (i = 0; i <= 39; i++)
	{
		gotoxy(TIMEFINGER, i);
		printf("                                                ");
	}
}

void taza()
{
	set_gamesize();

	int score_taza = 0, line_score = 25, times, input, real_score = 0;
	time_t start, end;
	time(&start);
	start_motion();
	system("cls");
	taza_map();
	cursorview(0);
	while (1) {
		if (_kbhit())
		{
			_getch();
			score_taza++;
			real_score++;

			if (score_taza >= 10)
			{
				line_score -= 2;
				gotoxy(20, line_score);    printf("------------------------------");
				cursorview(0);
				score_taza -= 10;
			}
		}
		time(&end);
		times = 12 - (int)(difftime(end, start));
		gotoxy(0, 0);    printf("%d", times);   cursorview(0);
		if (times == 0 || line_score < 1)
		{
			end_motion(real_score);
			break;
		}
	}
	score -= real_score / 10;
}

void taza_map()
{
	gotoxy(15, 1);    printf("120--                               |");
	gotoxy(15, 3);    printf("110--                               |");
	gotoxy(15, 5);    printf("100--                               |");
	gotoxy(15, 7);    printf(" 90--                               |");
	gotoxy(15, 9);    printf(" 80--                               |");
	gotoxy(15, 11);   printf(" 70--                               |");
	gotoxy(15, 13);   printf(" 60--                               |");
	gotoxy(15, 15);   printf(" 50--                               |");
	gotoxy(15, 17);   printf(" 40--                               |");
	gotoxy(15, 19);   printf(" 30--                               |");
	gotoxy(15, 21);   printf(" 20--                               |");
	gotoxy(15, 23);   printf(" 10--                               |");
	gotoxy(15, 25);   printf(" 00---------------------------------|\n");
}

int wasd()
{
	set_gamesize();

	int i, input, print, times, real_score = 0;
	time_t start, end;
	time(&start);
	system("cls");
	start_motion();
	wasd_map();
	wasd_make();
	for (i = 0; i < 20; i++)
	{
		gotoxy(30, 13);   printf("%c", wasd_made[i]);
		gotoxy(57, 13);   printf("%c", wasd_made[i + 1]);
		gotoxy(80, 13);   printf("%c", wasd_made[i + 2]);
		print = wasd_made[i + 1];
		while (1) {
			if (_kbhit())
			{
				input = _getch();
				if (input == print)
				{
					score++;
					real_score++;
					gotoxy(90, 0);
					printf("              ");
					gotoxy(90, 0);
					printf("잘 입력했어!!");
					cursorview(0);
					break;
				}
				else {
					gotoxy(90, 0);
					printf("잘못 입력했어!!");
					cursorview(0);
					Sleep(1000);
					gotoxy(90, 0);
					printf("               ");
				}
			}

			time(&end);
			times = 15 - (int)(difftime(end, start));
			gotoxy(0, 0);    printf("%d", times);   cursorview(0);

			if (times == 0)
				break;
			cursorview(0);
		}
	}
	end_motion(real_score);
	system("cls");
	return score;
}

void wasd_map()
{
	gotoxy(48, 10);      printf(" ㅡㅡㅡㅡㅡㅡㅡㅡㅡ");
	gotoxy(48, 11);      printf(" |                |");
	gotoxy(48, 12);      printf(" |                |");
	gotoxy(48, 13);      printf(" |                |");
	gotoxy(48, 14);      printf(" |                |");
	gotoxy(48, 15);      printf(" |                |");
	gotoxy(48, 16);      printf(" ㅡㅡㅡㅡㅡㅡㅡㅡㅡ");
}

void wasd_make()
{
	int y, i, x = 0;
	srand(time(NULL));
	for (i = 1; i <= 20; i++)
	{
		y = rand() % 4 + 1;
		switch (y) {
		case 1:
			x = A;   break;
		case 2:
			x = S;   break;
		case 3:
			x = D;   break;
		case 4:
			x = W;   break;
		}
		wasd_made[i] = x;
	}
}

void updown()
{

	int updown; // 컴퓨터가 정하는 수
	int count = 0; // 몇 번 안에 맞출 건지
	int i, j; // 반복문
	int input; // 사용자가 입력한 숫자
	int again = 0; // 게임 반복
	int base_score = 5;// 기본 점수


	updown = rand() % 10000 + 1; // 랜덤 정하기

	system("cls");
	set_gamesize();
	start_motion();
	system("cls");


	gotoxy(51, 4); printf("시도 횟수 입력\n");
	gotoxy(51, 5); printf("(1부터 100까지) \n");

	gotoxy(57, 8); scanf("%d", &count);

	while (1)
	{
		if (count < 1 || count > 100)
		{
			gotoxy(52, 8); printf("                  \n");
			gotoxy(57, 8); printf("X");
			Sleep(500);
			gotoxy(52, 8); printf("                  \n");
			gotoxy(57, 8); scanf("%d", &count);
		}
		else
			break;
	}

	Sleep(500);
	system("cls");

	wasd_map();

	for (i = 1; i <= count; i++)
	{
		gotoxy(53, 9); printf("%d번째 시도", i);
		gotoxy(56, 13); scanf("%d", &input);


		while (1)
		{
			if (input < 0 || input > 10000)
			{
				gotoxy(57, 13); printf("X");
				Sleep(100);
				gotoxy(53, 13); printf("           \n");
				gotoxy(55, 13); scanf("%d", &input);
			}
			else
				break;
		}

		if (updown > input)
		{
			gotoxy(72, 13 + i); printf("%d ↑. \n", input);
		}
		else if (updown < input)
		{
			gotoxy(72, 13 + i); printf("%d ↓ \n", input);

		}
		else if (updown == input)
		{
			gotoxy(48, 17);
			printf("%d번 만에 성공!", i);
			score = base_score + (10 - i / input) * 5; // 기본 점수 + 가산점
			break;
		}
		gotoxy(53, 13); printf("             \n");

		printf("\n");
	}
	if (updown != input)
	{
		gotoxy(49, 17);
		printf("실패! 정답은 %d!", updown);
	}
	Sleep(5000);
}

void memory()
{

	int rd[16]; // 랜덤으로 배열 넣기
	int i = 0, j = 6, k = 3; // i는 기본 반복문 j는 레벨 6부터
	int user[16] = { 0, }; // 사용자가 넣는 배열
	int count = 0; // 틀린 횟수
	int correct = 0; // 맞은 횟수
	int sec = 3;

	time_t start, end;
	int times;
	time(&start);

	srand(time(NULL));

	system("cls");
	set_gamesize();
	start_motion();



	for (j = 6; j < 15; j++) // level1부터 level10까지
	{
		Sleep(1000);
		system("cls");
		wasd_map();


		for (i = 0; i < j; i++)
		{
			rd[i] = rand() % 9; // 랜덤으로 인덱스에 하나하나 받기
			gotoxy(i + 50, 13);
			printf("%d", rd[i]);

		}
		Sleep(5000);
		gotoxy(50, 13);
		printf("           \n");
		fflush(stdin);
		int sec = 0;
		for (i = 0; i < j; i++)
		{
			gotoxy(50 + i, 13);
			user[i] = _getche();
		}

		if (i > j)
		{
			ox(0);
		}

		printf("\n");

		for (i = 0; i < j; i++)
		{
			if (rd[i] != (user[i] - 48)) // 원소 하나하나 맞는지 판별
			{
				count++;
				ox(0);
				break;
			}
			else if (rd[i] == (user[i] - 48))
			{
				correct++;
			}
		}
		if (correct == j)
		{
			ox(1);
		}

		Sleep(100);

	}
	score = 10 - count;
	end_motion(score);
}

void ox(int x)
{
	system("cls");
	if (x == 1)
	{
		system("color 0B");
		gotoxy(Ox, 4);   printf("              ...;;;;;;... \n");
		gotoxy(Ox, 5);   printf("           -;;;:~,.   ..-~;;;:, \n");
		gotoxy(Ox, 6);   printf("         .:;;~.               ,:;;~ \n");
		gotoxy(Ox, 7);   printf("       :;;.                     -;;- \n");
		gotoxy(Ox, 8);   printf("     ,;;,                         -;;.\n");
		gotoxy(Ox, 9);   printf("    ~;~                             ;;, \n");
		gotoxy(Ox, 10);   printf("   :;-                               ~;- \n");
		gotoxy(Ox, 11);   printf("   ~;,                                 ~;, \n");
		gotoxy(Ox, 12);   printf("  -;-              -:;;;;;;:,            :;. \n");
		gotoxy(Ox, 13);   printf("  .;~           .:;;~..  .,:;;~           ;: \n");
		gotoxy(Ox, 14);   printf("  :;.          -;;.          -;;.         -;- \n");
		gotoxy(Ox, 15);   printf(" .;-          -;~              :;.         :; \n");
		gotoxy(Ox, 16);   printf(" ~;.         ,;~                ;;         -;. \n");
		gotoxy(Ox, 17);   printf(" ::          ;:                 .;~        .;- \n");
		gotoxy(Ox, 18);   printf(".;~         ,;-                  :;         :: \n");
		gotoxy(Ox, 19);   printf(".;-         ~;                   -;.        :; \n");
		gotoxy(Ox, 20);   printf(",;-         ~;                   .;.        :; \n");
		gotoxy(Ox, 21);   printf(".;-         ~;                   -;.        :; \n");
		gotoxy(Ox, 22);   printf(".;~         ,;-                  :;         ;: \n");
		gotoxy(Ox, 23);   printf(" ::          ;:                 .;~        .;- \n");
		gotoxy(Ox, 24);   printf(" ~;.         ,;~                ;;         -;. \n");
		gotoxy(Ox, 25);   printf(" .;-          -;~             .:;.         :; \n");
		gotoxy(Ox, 26);   printf("  ~;.          ,;:,          -;;.         -;, \n");
		gotoxy(Ox, 27);   printf("  .;:           .~;;~,....-:;;-           ;: \n");
		gotoxy(Ox, 28);   printf("   -;-             --:;;;;;;~             :;. \n");
		gotoxy(Ox, 29);   printf("    ~;,                                 ~;, \n");
		gotoxy(Ox, 30);   printf("     ~;-                               ~;, \n");
		gotoxy(Ox, 31);   printf("      ~;~                            .:;, \n");
		gotoxy(Ox, 32);   printf("       ,;;,                         ~;:. \n");
		gotoxy(Ox, 33);   printf("        ~;:,                     -;;- \n");
		gotoxy(Ox, 34);   printf("         .~;;~,               ,:;;- \n");
		gotoxy(Ox, 35);   printf("           .-:;;:~-,.....,,-~:;;~, \n");
		gotoxy(Ox, 36);   printf("               ,-~:;;;;;;;;;:~-.  \n");
	}
	else
	{
		system("color 0E");
		gotoxy(Xx, 4);   printf("  :;~ .:;~                          ,;;, ,;;.\n");
		gotoxy(Xx, 5);   printf(" .;~    -;:                        ~;~    .;~ \n");
		gotoxy(Xx, 6);   printf(" .;-     .;;,                    .;;,     .;~\n");
		gotoxy(Xx, 7);   printf(" :;,      ~;~                  ,;:.      :;.\n");
		gotoxy(Xx, 8);   printf("  :;~      ,;;                ~;~      ,;;. \n");
		gotoxy(Xx, 9);   printf("   -;:      .;;,            .;;,      ~;:\n");
		gotoxy(Xx, 10);   printf("    .;;,      ~;~          ,;;.      :;-  \n");
		gotoxy(Xx, 11);   printf("      :;~      ,;;.       ~;~      ,;;.\n");
		gotoxy(Xx, 12);   printf("       -;:      .;;,    .;;,      ~;:\n");
		gotoxy(Xx, 13);   printf("        .;;,      ~;~  -;;.      :;-\n");
		gotoxy(Xx, 14);   printf("          :;~      ,;;:;~      ,;;.\n");
		gotoxy(Xx, 15);   printf("           -;:      .;;,      ~;:\n");
		gotoxy(Xx, 16);   printf("            .;;,            .:;-\n");
		gotoxy(Xx, 17);   printf("              :;-          ,;;.\n");
		gotoxy(Xx, 18);   printf("               -;:        ~;~\n");
		gotoxy(Xx, 19);   printf("               -;:        ~;:\n");
		gotoxy(Xx, 20);   printf("              ~;~          ,;:. \n");
		gotoxy(Xx, 21);   printf("            .;;,            .:;-\n");
		gotoxy(Xx, 22);   printf("           -;:.     .:;,      ~;~\n");
		gotoxy(Xx, 23);   printf("          :;~      ,;;~;~      ,;:.\n");
		gotoxy(Xx, 24);   printf("        .:;,      ~;~  -;:.     .:;- \n");
		gotoxy(Xx, 25);   printf("       -;:.     .:;-    .;;,      ~;~ \n");
		gotoxy(Xx, 26);   printf("      ~;~      ,;:.       ~;~      ,;:. \n");
		gotoxy(Xx, 27);   printf("    .:;,      ~;~          -;:.     .:;- \n");
		gotoxy(Xx, 28);   printf("   -;:.     .:;,            .:;,      ~;~ \n");
		gotoxy(Xx, 29);   printf("  ~;~      ,;;.               ~;~      ,;:. \n");
		gotoxy(Xx, 30);   printf(" :;,      ~;~                  -;:.     .:;. \n");
		gotoxy(Xx, 31);   printf(".;-     .:;,                    .:;,     .;~\n");
		gotoxy(Xx, 32);   printf(".;~    -;:.                       ~;~    .;~ \n");
		gotoxy(Xx, 33);   printf(" ~;-.,~;~                          ,;:,.-:;.\n");
		gotoxy(Xx, 34);   printf("  -:;;:,                            .~;;;~.\n");
	}
	cursorview(0);
	Sleep(1000);
	system("color 0F");
}

void start_motion()
{
	int i = 0;
	system("cls");
	for (i = 3; i > 0; i--)
	{
		gotoxy(53, 18);    printf("%d", i);
		cursorview(0);
		Sleep(1000);
	}
}

void end_motion(int x)
{
	system("cls");
	gotoxy(45, 15);       printf("********끝********");
	cursorview(0);
	Sleep(1000);
	system("cls");
	gotoxy(45, 15);       printf("********%d개********", x);
	cursorview(0);
	Sleep(2000);
}

void gotoxy(int x, int y)
{
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void check_score()
{
	system("mode con cols=30 lines=20");
	system("puase");
	gotoxy(50, 10);    printf("*******현재의 점수: %d점*******", score);
}

void cursorview(char show)//커서숨기기
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

void textcolor(int color_number)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}

void tutorial_timing()
{
	system("mode con cols=50 lines=25");
	system("color 0F");

	gotoxy(0, 3);      printf("\t< 타이밍 게임 >");
	gotoxy(0, 7);      printf("\t말그대로 타이밍을 맞춰봅시다!    ");
	gotoxy(0, 9);      printf("\t줄이 내려오는 타이밍에 맞춰서..      ");
	gotoxy(0, 11);      printf("\t\'아무 키\'나 눌러주세요!   ");
	gotoxy(0, 20);      printf("\t시작하려면 아무키나 누르세요...");

	cursorview(0);

	if (_getch())
		return;

}

void tutorial_wasd()
{
	system("mode con cols=50 lines=25");
	system("color 0F");

	gotoxy(0, 3);      printf("\t< WASD >");
	gotoxy(0, 7);      printf("\tWASDWASDWASDWASDWASDWASDWASDWASD !!!!   ");
	gotoxy(0, 9);      printf("\t타자를 좋아하는 당신의 마음을 보여주세요!      ");
	gotoxy(0, 11);      printf("\t사각형 안에 있는 글자를 입력하세요!!");
	gotoxy(0, 15);      printf("\t제한시간 : 10 초 ");
	gotoxy(0, 20);      printf("\t시작하려면 아무키나 누르세요...");

	cursorview(0);

	fflush(stdin);

	if (_getch())
		return;
}

void tutorial_taza()
{
	system("mode con cols=50 lines=25");
	system("color 0F");

	gotoxy(0, 3);      printf("\t< Taza ( 타자 ) >");
	gotoxy(0, 7);      printf("\t아무키나 최대한 많이,   ");
	gotoxy(0, 9);      printf("\t그리고 빨리 입력하세요 !!");
	gotoxy(0, 11);      printf("\t당신의 스트레스를 풀 수 있는 기회!");
	gotoxy(0, 14);      printf("\t최대 100점까지 획득 가능 !!");
	gotoxy(0, 16);      printf("\t제한시간 : 8 초 ");
	gotoxy(0, 21);      printf("\t시작하려면 아무키나 누르세요...");

	cursorview(0);

	fflush(stdin);

	if (_getch())
		return;
}

void tutorial_rsp()
{
	system("mode con cols=50 lines=25");
	system("color 0F");

	gotoxy(0, 3);      printf("\t< 가위 바위 보 >");
	gotoxy(0, 7);      printf("\t왼쪽이 이기면 \'A\'      ");
	gotoxy(0, 9);      printf("\t오른쪽이 이기면 \'D\'      ");
	gotoxy(0, 11);      printf("\t비기면 \'S\'를 눌러주세요!   ");
	gotoxy(0, 15);      printf("\t제한시간 : 2 초   ");
	gotoxy(0, 20);      printf("\t시작하려면 아무키나 누르세요...");

	if (_getch())
		return;
}

void tutorial_updown()
{
	system("mode con cols=50 lines=25");
	system("color 0f");

	gotoxy(0, 3);		printf("\t< 업 다운 >");
	gotoxy(0, 7);		printf("\t 범위는 1부터 10000!");
	gotoxy(0, 9);		printf("\t 시도 횟수는 1부터 100!");
	gotoxy(0, 11);		printf("\t 시도 횟수를 넘으면 패배!");
	gotoxy(0, 15);		printf("\t 시도 횟수 안에 맞추면 가산점!");
	gotoxy(0, 20);		printf("\t시작하려면 아무키나 누르세요...");

	if (_getch())
		return;
}

void tutorial_memory()
{
	system("mode con cols=50 lines=25");
	system("color 0f");

	gotoxy(0, 3);		printf("\t< 기억력 테스트 >");
	gotoxy(0, 7);		printf("\t 기억력을 마음껏 테스트하세요!");
	gotoxy(0, 9);		printf("\t 6자리부터 15자리의 숫자!");
	gotoxy(0, 11);		printf("\t 숫자 외울 시간 : 5 초");
	gotoxy(0, 15);		printf("\t 입력 제한시간 : 3 초	");
	gotoxy(0, 20);		printf("\t시작하려면 아무키나 누르세요...");

	if (_getch())
		return;
}


void score_save()
{
	int select = 0;
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	char* name = (char*)malloc(sizeof(char) * 40);
	printf("이름을 입력하세요: ");    scanf("%s", name);
	system("cls");
	printf("%s님의 점수는\n", name);
	Sleep(2000);
	printf("*****%d점 입니다!!*****", score);
	Sleep(2000);
	FILE* day_save;

	day_save = fopen("check_point.txt", "a+");

	fprintf(day_save, "%s: %d점   %d-%d-%d %d:%d:%d\n\n\n", name, score, tm.tm_year + 1900,
		tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

	fclose(day_save);

	free(name);
}

void set_gamesize()
{
	system("mode con cols=110 lines=41");
	system("color 0F");
}

int sock_main(int flag) {

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	int fin;
	system("cls");
	printf("******채팅******\n");
	if (flag == FALSE) //COM0 (SERVER)
	{
		hListen = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		SOCKADDR_IN tListenAddr;                  //소켓 구성요소 담을 구조체 생성
		memset(&tListenAddr, 0, sizeof(SOCKADDR_IN));
		tListenAddr.sin_family = AF_INET;                                       //주소 정보
		tListenAddr.sin_port = htons(PORT);
		tListenAddr.sin_addr.s_addr = htonl(INADDR_ANY);                        //ip주소 설정 - 현재 동작되는 컴퓨터의 ip 주소

		bind(hListen, (SOCKADDR*)& tListenAddr, sizeof(tListenAddr));            //소캣의 주소정보 전달
		listen(hListen, SOMAXCONN);                                              //접속 승인

		SOCKADDR_IN tCom1Addr;                                                   //소켓 정보 담을 구조체 생성
		memset(&tCom1Addr, 0, sizeof(SOCKADDR_IN));                         //구조체 0으로 초기화
		int iClntSize = sizeof(tCom1Addr);
		hSock = accept(hListen, (SOCKADDR*)& tCom1Addr, &iClntSize);    //접속 요청 수락
		fin = chatting_COM0(hSock);
	}
	else           //COM1 (CLIENT)
	{

		hSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);        //IPV4타입, 연결지향형 소켓, TCP 사용 

		SOCKADDR_IN tAddr;                                     //구조체 생성
		tAddr.sin_family = AF_INET;
		tAddr.sin_port = htons(PORT);
		tAddr.sin_addr.s_addr = inet_addr(COM0_IP);

		connect(hSock, (SOCKADDR*)& tAddr, sizeof(tAddr));       //지정된 소켓에 연결(=bind)
		fin = chatting_COM1(hSock);
	}
	closesocket(hSock);
	closesocket(hListen);
	return fin;
}

int chatting_COM0(SOCKET hCOM1)
{
	int fin;
	int nRcv, strLen;
	char message[PACKET_SIZE];
	char indi[2] = { 'q' };
	bool a;
	while (1)
	{
		_beginthread(chatting_recv, 0, hCOM1);
		printf("\nYOU : ");
		fgets(message, 30, stdin);                                     //message 입력받음
		a = (message[0] == indi[0]) ? FALSE : TRUE;                    //q인지 판단
		if (a == FALSE)
		{
			printf("\nClose...\n");
			send(hCOM1, message, strlen(message), 0);
			break;
		}

		strLen = strlen(message);
		send(hCOM1, message, strLen, 0);                            //message 보냄
	}
	char r_message[PACKET_SIZE];
	recv(hCOM1, r_message, PACKET_SIZE, 0);
	system("cls");
	printf("COM1 SCORE : %d", r_message[0]);
	fin = (int)r_message[0];
	char s_message[3] = { 0 , };
	s_message[0] = score;
	send(hCOM1, s_message, strlen(s_message), 0);
	if (score > fin)
		fin = TRUE;
	else if (score == fin)
		fin = 2;
	else
		fin = FALSE;           //TRUE : 이김, FALSE : 짐
	return fin;
}

int chatting_COM1(SOCKET hCOM0)
{                //채팅 부분
	int nRcv, fin;
	char message[PACKET_SIZE];
	char indi[2] = { 'q' };                   //q를 누르면 채팅 끔
	system("cls");
	while (1)
	{
		printf("\nYOU : ");
		fgets(message, 30, stdin);
		BOOL a = (message[0] == indi[0]) ? FALSE : TRUE;       //a 로 채팅을 끌지 말지 판단
		if (a == FALSE)
		{
			send(hCOM0, message, strlen(message), 0);      //q를 보내 server도 채팅을 끄게 함
			printf("\nClose..\n");
			break;
		}
		send(hCOM0, message, strlen(message), 0);       //message를 보냄

		_beginthread(chatting_recv, 0, hCOM0);
	}
	char s_message[3] = { 0, };
	s_message[0] = score;
	send(hCOM0, s_message, strlen(s_message), 0);

	char r_message[PACKET_SIZE] = { 0, };
	recv(hCOM0, r_message, PACKET_SIZE, 0);
	system("cls");
	printf("COM0 score : %d", r_message[0]);
	fin = (int)r_message[0];

	if (score > fin)
		fin = TRUE;
	else if (score == fin)
		fin = 2;
	else
		fin = FALSE;           //TRUE : 이김, FALSE : 짐
	return fin;
}

void chatting_recv(SOCKET hCOM)
{
	int nRcv;
	char recv_message[PACKET_SIZE];
	char indi[2] = { 'q' };

	while (1)
	{
		nRcv = recv(hCOM, recv_message, sizeof(recv_message) - 1, 0);        //message를 받음

		recv_message[nRcv] = '\0';                     //메세지 뒤에 널문자 붙여줌
		BOOL a = (recv_message[0] == indi[0]) ? FALSE : TRUE;          //q 판단
		if (a == FALSE)
		{
			printf("\nClose Server Connection...\n");
			break;
		}

		printf("\nOPPOSITE : %s", recv_message);

	}

	return;
}

void sock_clean(SOCKET hSock, SOCKET hListen)
{
	closesocket(hSock);
	closesocket(hListen);

	WSACleanup();
}

int flag_com() {
	system("cls");
	int flag;
	printf("COM1(CLIENT) : 1\n");                      //CLIENT
	printf("COM0(SERVER) : 0\n을 입력하세요\n");       //SERVER
	scanf("%d", &flag);
	return flag;
}

void rand_start(int* sequence)
{
	srand(time(NULL));
	int i, tmp, x, y;
	for (i = 0; i < 40; i++)   //40번 섞음
	{
		x = rand() % GAME_NUMBER;
		y = rand() % GAME_NUMBER;

		if (x != y)
		{
			tmp = *(sequence + x);
			*(sequence + x) = *(sequence + y);
			*(sequence + y) = tmp;
		}
	}
	return;
}
