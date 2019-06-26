#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define TIMEFINGER 31 // Use in timing
#define A 97
#define S 115
#define D 100
#define W 119
#define START 2
#define Xx 32
#define Ox 32 

int score = 0;
char wasd_made[30] = { 0, };

int tutorial_rsp(); // Game Tutorial
int tutorial_timing();
int tutorial_wasd();
int tutorial_taza();

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

void ox(int x); // timing & rsp

void start_motion(); // all game
void end_motion(int x);

int menu();	// Other Functions
void score_save();
void check_score();

void textcolor(int color_number);  // Win API Functions
void gotoxy(int x, int y);
void cursorview(char show);
void set_gamesize();

int main() 
{

	int start = menu(); // if Enter = start
	int game_start; // start값 랜덤으로 나오게 바꿔서 게임 랜덤 실행 구현해보장

	if (start == 1) 
	{
		system("cls");

		game_start = tutorial_rsp();
		if (game_start == START)
		{
			fflush(stdin);
			rsp();
		}

		game_start = tutorial_timing();
		if (game_start == START)
		{
			fflush(stdin);
			timing();
		}

		game_start = tutorial_taza();
		if (game_start == START)
		{
			fflush(stdin);
			taza();
		}

		game_start = tutorial_wasd();
		if (game_start == START)
		{
			fflush(stdin);
			wasd();
		}

		score_save();
	}
	system("pause");
	return 0;
}

int menu()
{
	system("mode con cols=48 lines=37"); // cols = 세로, lines = 가로 
	while (1)
	{
		gotoxy(0, 2);	textcolor(4);	printf("################################################");
		gotoxy(0, 4);   textcolor(7);	printf("             < Mini Game - Party >	   	    ");
		gotoxy(0, 6);	textcolor(4);	printf("################################################"); textcolor(7);
				
		gotoxy(6, 9);	textcolor(2);	printf("====================================");	textcolor(7);
		gotoxy(6, 10);	printf(":		    	                 :");
		gotoxy(6, 11);	printf(":  < 게임 설명 >	                 :"); 
		gotoxy(6, 12);	printf(":   	                         :");
		gotoxy(6, 13);	printf(":	◈ 여러 미니게임을 클리어 하자!  :");
		gotoxy(6, 14);	printf(":		    	                 :");
		gotoxy(6, 15);	printf(":	⊙ 채팅을 통한 더 큰 재미!	 :");
		gotoxy(6, 16);	printf(":  	    	                 :");
		gotoxy(6, 17);	printf(":  	    	                 :");
		gotoxy(6, 18);	printf(":  	    	                 :");
		gotoxy(6, 19);	printf(":	 < 게임 방법 >	    	         :"); 
		gotoxy(6, 20);	printf(":		    	                 :");
		gotoxy(6, 21);	printf(":	♤ 매 게임마다 설명 등장!	 :");
		gotoxy(6, 22);	printf(":	   	                         :");
		gotoxy(6, 23);	printf(":	◑ 설명을 잘 읽어보자!	 	 :");
		gotoxy(6, 24);	printf(":		    	                 :");
		gotoxy(6, 25);	printf(":	※ 난이도는 점점 어려워진다!     :");
		gotoxy(6, 26);	printf(":		    	                 :");
		gotoxy(6, 27);	printf(":		    	                 :");
		gotoxy(6, 28);	textcolor(2);	printf("===================================="); textcolor(7);

		gotoxy(9, 31);	textcolor(9);	printf("------------------------------"); textcolor(7);
		gotoxy(9, 32);	printf(":       ENTER : start !!     :");
		gotoxy(9, 33);	printf(":       SPACE : exit         :");
		gotoxy(9, 34);	textcolor(9);	printf("------------------------------"); textcolor(7);

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
		gotoxy(90, 1);		printf(" ㅡㅡㅡㅡㅡㅡㅡㅡㅡ"); 
		gotoxy(90, 2);		printf(" |                |");
		gotoxy(90, 3);		printf(" |                |");
		gotoxy(90, 4);		printf(" |                |");
		gotoxy(90, 5);		printf(" |                |");
		gotoxy(90, 6);		printf(" |                |");
		gotoxy(90, 7);		printf(" ㅡㅡㅡㅡㅡㅡㅡㅡㅡ");
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
			gotoxy(100, 4);	 printf("%d", real_score);	cursorview(0);
		}
	}
	end_motion(real_score);
	system("cls");
}

void timing_print_finger()
{
	gotoxy(3, 30);	printf("            ,,,.\n");
	gotoxy(3, 31);	printf("         ,,. .,.\n");
	gotoxy(3, 32);	printf(",,,,,..,.    .,,........,.\n");
	gotoxy(3, 33);	printf("-   ,,.                 .,--"); textcolor(4); printf("=\n"); textcolor(7); // *******
	gotoxy(3, 34);	printf("-   ,.        .,,,,,,,,,.\n");
	gotoxy(3, 35);	printf("-   ,.            .-\n");
	gotoxy(3, 36);	printf("-   ,.        .,,,,.\n");
	gotoxy(3, 37);	printf("-   ,.        ....,\n");
	gotoxy(3, 38);	printf("-,,,-. .,,,....,,,\n"); //26칸

	gotoxy(79, 30);	printf("             .,,,.\n");
	gotoxy(79, 31);	printf("            .,. .,,\n");
	gotoxy(79, 32);	printf("  .,,,,,,,,,,,,    .,..,,,,, \n");
	gotoxy(79, 33);	textcolor(4); printf("="); textcolor(7); printf("--,.                 ,,-   ,\n");
	gotoxy(79, 34);	printf("   ,,,,,,,,,,.        .-   ,\n");
	gotoxy(79, 35);	printf("        -,            .-   ,\n");
	gotoxy(79, 36);	printf("        .,,,,.        .-   ,\n");
	gotoxy(79, 37);	printf("         ,....        .-   ,\n");
	gotoxy(79, 38);	printf("          ,,,....,,,. .-,,,-\n");
	cursorview(0);
}

void timing_print_line(int i)
{

	gotoxy(TIMEFINGER, i - 1);	printf("                                                ");
	gotoxy(TIMEFINGER, i);	    printf("  ==============================================");	cursorview(0);

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
			input = _getch();
			if (input == A || input == S || input == W || input == D)
			{
				score_taza++;
				real_score++;
			}
			if (score_taza >= 10)
			{
				line_score -= 2;
				gotoxy(20, line_score);	 printf("------------------------------");
				cursorview(0);
				score_taza -= 10;
			}
		}
		time(&end);
		times = 12 - (int)(difftime(end, start));
		gotoxy(0, 0);	 printf("%d", times);	cursorview(0);
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
	gotoxy(15, 1);	printf("120--                               |");
	gotoxy(15, 3);	printf("110--								|");
	gotoxy(15, 5);  printf("100--								|");
	gotoxy(15, 7);	printf(" 90--								|");
	gotoxy(15, 9);	printf(" 80--								|");
	gotoxy(15, 11);	printf(" 70--								|");
	gotoxy(15, 13);	printf(" 60--								|");
	gotoxy(15, 15);	printf(" 50--								|");
	gotoxy(15, 17);	printf(" 40--								|");
	gotoxy(15, 19);	printf(" 30--								|");
	gotoxy(15, 21);	printf(" 20--								|");
	gotoxy(15, 23);	printf(" 10--								|");
	gotoxy(15, 25);	printf(" 00---------------------------------|\n");
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
		gotoxy(30, 13);	printf("%c", wasd_made[i]);
		gotoxy(57, 13);	printf("%c", wasd_made[i + 1]);
		gotoxy(80, 13);	printf("%c", wasd_made[i + 2]);
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
			gotoxy(0, 0);	 printf("%d", times);	cursorview(0);

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
	gotoxy(48, 10);		printf(" ㅡㅡㅡㅡㅡㅡㅡㅡㅡ");
	gotoxy(48, 11);		printf(" |                |");
	gotoxy(48, 12);		printf(" |                |");
	gotoxy(48, 13);		printf(" |                |");
	gotoxy(48, 14);		printf(" |                |");
	gotoxy(48, 15);		printf(" |                |");
	gotoxy(48, 16);		printf(" ㅡㅡㅡㅡㅡㅡㅡㅡㅡ");
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
			x = A;	break;
		case 2:
			x = S;	break;
		case 3:
			x = D;	break;
		case 4:
			x = W;	break;
		}
		wasd_made[i] = x;
	}
}

void ox(int x)
{
	system("cls");
	if (x == 1)
	{
		system("color 0B");
		gotoxy(Ox, 4);	printf("              ...;;;;;;... \n");
		gotoxy(Ox, 5);	printf("           -;;;:~,.   ..-~;;;:, \n");
		gotoxy(Ox, 6);	printf("         .:;;~.               ,:;;~ \n");
		gotoxy(Ox, 7);	printf("       :;;.                     -;;- \n");
		gotoxy(Ox, 8);	printf("     ,;;,                         -;;.\n");
		gotoxy(Ox, 9);	printf("    ~;~                             ;;, \n");
		gotoxy(Ox, 10);	printf("   :;-                               ~;- \n");
		gotoxy(Ox, 11);	printf("   ~;,                                 ~;, \n");
		gotoxy(Ox, 12);	printf("  -;-              -:;;;;;;:,            :;. \n");
		gotoxy(Ox, 13);	printf("  .;~           .:;;~..  .,:;;~           ;: \n");
		gotoxy(Ox, 14);	printf("  :;.          -;;.          -;;.         -;- \n");
		gotoxy(Ox, 15);	printf(" .;-          -;~              :;.         :; \n");
		gotoxy(Ox, 16);	printf(" ~;.         ,;~                ;;         -;. \n");
		gotoxy(Ox, 17);	printf(" ::          ;:                 .;~        .;- \n");
		gotoxy(Ox, 18);	printf(".;~         ,;-                  :;         :: \n");
		gotoxy(Ox, 19);	printf(".;-         ~;                   -;.        :; \n");
		gotoxy(Ox, 20);	printf(",;-         ~;                   .;.        :; \n");
		gotoxy(Ox, 21);	printf(".;-         ~;                   -;.        :; \n");
		gotoxy(Ox, 22);	printf(".;~         ,;-                  :;         ;: \n");
		gotoxy(Ox, 23);	printf(" ::          ;:                 .;~        .;- \n");
		gotoxy(Ox, 24);	printf(" ~;.         ,;~                ;;         -;. \n");
		gotoxy(Ox, 25);	printf(" .;-          -;~             .:;.         :; \n");
		gotoxy(Ox, 26);	printf("  ~;.          ,;:,          -;;.         -;, \n");
		gotoxy(Ox, 27);	printf("  .;:           .~;;~,....-:;;-           ;: \n");
		gotoxy(Ox, 28);	printf("   -;-             --:;;;;;;~             :;. \n");
		gotoxy(Ox, 29);	printf("    ~;,                                 ~;, \n");
		gotoxy(Ox, 30);	printf("     ~;-                               ~;, \n");
		gotoxy(Ox, 31);	printf("      ~;~                            .:;, \n");
		gotoxy(Ox, 32);	printf("       ,;;,                         ~;:. \n");
		gotoxy(Ox, 33);	printf("        ~;:,                     -;;- \n");
		gotoxy(Ox, 34);	printf("         .~;;~,               ,:;;- \n");
		gotoxy(Ox, 35);	printf("           .-:;;:~-,.....,,-~:;;~, \n");
		gotoxy(Ox, 36);	printf("               ,-~:;;;;;;;;;:~-.  \n");
	}
	else
	{
		system("color 0E");
		gotoxy(Xx, 4);	printf("  :;~ .:;~                          ,;;, ,;;.\n");
		gotoxy(Xx, 5);	printf(" .;~    -;:                        ~;~    .;~ \n");
		gotoxy(Xx, 6);	printf(" .;-     .;;,                    .;;,     .;~\n");
		gotoxy(Xx, 7);	printf(" :;,      ~;~                  ,;:.      :;.\n");
		gotoxy(Xx, 8);	printf("  :;~      ,;;                ~;~      ,;;. \n");
		gotoxy(Xx, 9);	printf("   -;:      .;;,            .;;,      ~;:\n");
		gotoxy(Xx, 10);	printf("    .;;,      ~;~          ,;;.      :;-  \n");
		gotoxy(Xx, 11);	printf("      :;~      ,;;.       ~;~      ,;;.\n");
		gotoxy(Xx, 12);	printf("       -;:      .;;,    .;;,      ~;:\n");
		gotoxy(Xx, 13);	printf("        .;;,      ~;~  -;;.      :;-\n");
		gotoxy(Xx, 14);	printf("          :;~      ,;;:;~      ,;;.\n");
		gotoxy(Xx, 15);	printf("           -;:      .;;,      ~;:\n");
		gotoxy(Xx, 16);	printf("            .;;,            .:;-\n");
		gotoxy(Xx, 17);	printf("              :;-          ,;;.\n");
		gotoxy(Xx, 18);	printf("               -;:        ~;~\n");
		gotoxy(Xx, 19);	printf("               -;:        ~;:\n");
		gotoxy(Xx, 20);	printf("              ~;~          ,;:. \n");
		gotoxy(Xx, 21);	printf("            .;;,            .:;-\n");
		gotoxy(Xx, 22);	printf("           -;:.     .:;,      ~;~\n");
		gotoxy(Xx, 23);	printf("          :;~      ,;;~;~      ,;:.\n");
		gotoxy(Xx, 24);	printf("        .:;,      ~;~  -;:.     .:;- \n");
		gotoxy(Xx, 25);	printf("       -;:.     .:;-    .;;,      ~;~ \n");
		gotoxy(Xx, 26);	printf("      ~;~      ,;:.       ~;~      ,;:. \n");
		gotoxy(Xx, 27);	printf("    .:;,      ~;~          -;:.     .:;- \n");
		gotoxy(Xx, 28);	printf("   -;:.     .:;,            .:;,      ~;~ \n");
		gotoxy(Xx, 29);	printf("  ~;~      ,;;.               ~;~      ,;:. \n");
		gotoxy(Xx, 30);	printf(" :;,      ~;~                  -;:.     .:;. \n");
		gotoxy(Xx, 31);	printf(".;-     .:;,                    .:;,     .;~\n");
		gotoxy(Xx, 32);	printf(".;~    -;:.                       ~;~    .;~ \n");
		gotoxy(Xx, 33);	printf(" ~;-.,~;~                          ,;:,.-:;.\n");
		gotoxy(Xx, 34);	printf("  -:;;:,                            .~;;;~.\n");
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
		gotoxy(53, 18);	 printf("%d", i);
		cursorview(0);
		Sleep(1000);
	}
}

void end_motion(int x)
{
	system("cls");
	gotoxy(45, 15);		 printf("********끝********");
	cursorview(0);
	Sleep(1000);
	system("cls");
	gotoxy(45, 15);		 printf("********%d개********", x);
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
	gotoxy(50, 10);	 printf("*******현재의 점수: %d점*******", score);
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

int tutorial_timing()
{
	system("mode con cols=50 lines=25");
	system("color 0F");

	gotoxy(0, 3);		printf("\t< 타이밍 게임 >");
	gotoxy(0, 7);		printf("\t말그대로 타이밍을 맞춰봅시다! 	");
	gotoxy(0, 9);		printf("\t줄이 내려오는 타이밍에 맞춰서..		");
	gotoxy(0, 11);		printf("\t\'아무 키\'나 눌러주세요!	");
	gotoxy(0, 20);		printf("\t시작하려면 아무키나 누르세요...");

	cursorview(0);

	if(_getch())
		return START;

}

int tutorial_wasd() 
{
	system("mode con cols=50 lines=25");
	system("color 0F");

	gotoxy(0, 3);		printf("\t< WASD >");
	gotoxy(0, 7);		printf("\tWASDWASDWASDWASDWASDWASDWASDWASD !!!!	");
	gotoxy(0, 9);		printf("\t타자를 좋아하는 당신의 마음을 보여주세요!		");
	gotoxy(0, 11);		printf("\t사각형 안에 있는 글자를 입력하세요!!");
	gotoxy(0, 15);		printf("\t제한시간 : 10 초 ");
	gotoxy(0, 20);		printf("\t시작하려면 아무키나 누르세요...");

	cursorview(0);

	fflush(stdin);

	if (_getch()) 
		return START;
}

int tutorial_taza()
{
	system("mode con cols=50 lines=25");
	system("color 0F");

	gotoxy(0, 3);		printf("\t< Taza ( 타자 ) >");
	gotoxy(0, 7);		printf("\t아무키나 최대한 많이,	");
	gotoxy(0, 9);		printf("\t그리고 빨리 입력하세요 !!");
	gotoxy(0, 11);		printf("\t당신의 스트레스를 풀 수 있는 기회!");
	gotoxy(0, 14);		printf("\t최대 100점까지 획득 가능 !!");
	gotoxy(0, 16);		printf("\t제한시간 : 8 초 ");
	gotoxy(0, 21);		printf("\t시작하려면 아무키나 누르세요...");
	
	cursorview(0);
	
	fflush(stdin);

	if(_getch())
		return START;
}

int tutorial_rsp()
{
	system("mode con cols=50 lines=25");
	system("color 0F");

	gotoxy(0, 3);		printf("\t< 가위 바위 보 >");
	gotoxy(0, 7);		printf("\t왼쪽이 이기면 \'A\'		");
	gotoxy(0, 9);		printf("\t오른쪽이 이기면 \'D\'		");
	gotoxy(0, 11);		printf("\t비기면 \'S\'를 눌러주세요!	");
	gotoxy(0, 15);		printf("\t제한시간 : 2 초	");
	gotoxy(0, 20);		printf("\t시작하려면 아무키나 누르세요...");

	if(_getch())
		return START;
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