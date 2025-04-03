#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"conio2.h"

#define MENUX 4 //wspolrzedna x menu
#define MENUY 2 //wspolrzedna y menu
#define MENUXSIZE 35 //wielkosc menu w poziomie
#define MENUYSIZE 12 //wielkosc menu w pionie
#define FIELDX 45 //wspolrzedna x planszy
#define FIELDY 2 //wspolrzedna y planszy
#define VERTICALBORDER 179 //znak poziomej granicy menu
#define HORIZONTALBORDER 196 //znak pionowej granicy menu
#define FIELDCHAR 197 //znak pustej planszy
#define BORDER 1 //wielkosc granicy
#define BORDERCHAR 42 //znak granicy planszy
#define PLAYER0CHAR 67 //znak gracza 0
#define PLAYER1CHAR 66 //znak gracza 1
#define DEATHCHAR 35 //znak zbitego pionka
#define PLATYER0INDEX 0 //numer gracza 0
#define PLATYER1INDEX 1 //numer gracza 1

//tworzenie i wyrysowywanie menu
void printMenu(int x, int y, int player0score, int player1score) /*wypisuje menu*/
{
	char txt[1000];
	textbackground(BLACK);
	textcolor(LIGHTGRAY); /*kolor tekstu*/
	gotoxy(MENUX - 1, MENUY - 1);
	putch(FIELDCHAR);
	gotoxy(MENUX + MENUXSIZE, MENUY - 1);
	putch(FIELDCHAR);
	gotoxy(MENUX + MENUXSIZE, MENUY + MENUYSIZE);
	putch(FIELDCHAR);
	gotoxy(MENUX - 1, MENUY + MENUYSIZE);
	putch(FIELDCHAR);

	for (int i = MENUX; i < MENUXSIZE + MENUX; i++)
	{
		gotoxy(i, MENUY - 1);
		putch(HORIZONTALBORDER);
	}

	for (int i = MENUX; i < MENUXSIZE + MENUX; i++)
	{
		gotoxy(i, MENUY + MENUYSIZE);
		putch(HORIZONTALBORDER);
	}

	for (int i = MENUY; i < MENUYSIZE + MENUY; i++)
	{
		gotoxy(MENUX - 1, i);
		putch(VERTICALBORDER);
	}

	for (int i = MENUY; i < MENUYSIZE + MENUY; i++)
	{
		gotoxy(MENUX + MENUXSIZE, i);
		putch(VERTICALBORDER);
	}

	gotoxy(MENUX, MENUY);
	cputs("Franciszek Gwarek 193192");
	gotoxy(MENUX, MENUY + 1);
	cputs("Zaimplementowane funkcje: a-h, j, k");
	gotoxy(MENUX, MENUY + 2);
	cputs("sztalki : poruszanie sie po planszy");
	gotoxy(MENUX, MENUY + 3);
	cputs("q       : wyjdz z gry");
	gotoxy(MENUX, MENUY + 4);
	cputs("n       : rozpocznij nowa gre");
	gotoxy(MENUX, MENUY + 5);
	cputs("i       : poloz kamien na planszy");
	gotoxy(MENUX, MENUY + 6);
	cputs("s       : zapisz gre");
	gotoxy(MENUX, MENUY + 7);
	cputs("l       : wczytaj gre");
	gotoxy(MENUX, MENUY + 8);
	cputs("f       : zakoncz gre");
	gotoxy(MENUX, MENUY + 9);
	sprintf(txt, "obecna pozycja kurosra: %d x %d ", x - FIELDX, y - FIELDY);
	cputs(txt);
	gotoxy(MENUX, MENUY + 10);
	sprintf(txt, "wynik gracza 1: %d ", player0score);
	cputs(txt);
	gotoxy(MENUX, MENUY + 11);
	sprintf(txt, "wynik gracza 2: %d ", player1score);
	cputs(txt);
}

//wyrysowywanie planszy
void printField(char** field, int size0) {
	for (int y = FIELDY; y < FIELDY + size0 + BORDER * 2; y++)
	{
		for (int x = FIELDX; x < FIELDX + size0 + BORDER * 2; x++)
		{
			gotoxy(x, y);
			textbackground(YELLOW);
			textcolor(BLACK);
			putch(field[y - FIELDY][x - FIELDX]);
		}
	}
}

//tworzenie pustej planszy
void makeField(char** field, int size0) {
	for (int i = 0; i < size0 + BORDER * 2; i++)
	{
		for (int j = 0; j < size0 + BORDER * 2; j++)
		{
			if (i == 0 || i == size0 + BORDER || j == 0 || j == size0 + BORDER) field[i][j] = BORDERCHAR;
			else field[i][j] = FIELDCHAR;
		}
	}

}

//przepisywanie planszy (do Ko)
void rewriteField(char** fieldfrom, char** fieldto, int size0) {
	for (int i = 0; i < size0 + 2; i++)
	{
		for (int j = 0; j < size0 + 2; j++)
		{
			fieldto[i][j] = fieldfrom[i][j];
		}
	}

}

//porównywanie planszy (do Ko)
int comparisonField(char** fieldbefore, char** fieldnow, int size0) {

	int check = 0;
	for (int i = 0; i < size0 + 2; i++)
	{
		for (int j = 0; j < size0 + 2; j++)
		{
			if (fieldnow[i][j] != fieldbefore[i][j]) check++;
		}
	}
	return check;
}

//sprawdzanie czy bedzie oddech jesli zbije
int checkKoBreath(int x, int y, int player, char** field, int breath) {


	char enemy = 0;
	char me = 0;
	int idenemy = 0;
	if (player == PLATYER0INDEX)
	{
		me = PLAYER0CHAR;
		enemy = PLAYER1CHAR;
		idenemy = PLATYER1INDEX;
	}
	else if (player == PLATYER1INDEX) {
		me = PLAYER1CHAR;
		enemy = PLAYER0CHAR;
		idenemy = PLATYER0INDEX;
	}

	if (field[y - FIELDY][x - FIELDX] == BORDERCHAR) breath = 0;

	else if ((field[y - FIELDY - 1][x - FIELDX] == enemy || field[y - FIELDY - 1][x - FIELDX] == BORDERCHAR)
		&& (field[y - FIELDY + 1][x - FIELDX] == enemy || field[y - FIELDY + 1][x - FIELDX] == BORDERCHAR)
		&& (field[y - FIELDY][x - FIELDX - 1] == enemy || field[y - FIELDY][x - FIELDX - 1] == BORDERCHAR)
		&& field[y - FIELDY][x - FIELDX + 1] == FIELDCHAR - 256)
	{
		breath = -1;
		field[y - FIELDY][x - FIELDX] = FIELDCHAR;
	}
	else if ((field[y - FIELDY - 1][x - FIELDX] == enemy || field[y - FIELDY - 1][x - FIELDX] == BORDERCHAR)
		&& (field[y - FIELDY + 1][x - FIELDX] == enemy || field[y - FIELDY + 1][x - FIELDX] == BORDERCHAR)
		&& field[y - FIELDY][x - FIELDX - 1] == FIELDCHAR - 256
		&& (field[y - FIELDY][x - FIELDX + 1] == enemy || field[y - FIELDY][x - FIELDX + 1] == BORDERCHAR))
	{
		breath = -1;
		field[y - FIELDY][x - FIELDX] = FIELDCHAR;
	}
	else if ((field[y - FIELDY - 1][x - FIELDX] == enemy || field[y - FIELDY - 1][x - FIELDX] == BORDERCHAR)
		&& field[y - FIELDY + 1][x - FIELDX] == FIELDCHAR - 256
		&& (field[y - FIELDY][x - FIELDX - 1] == enemy || field[y - FIELDY][x - FIELDX - 1] == BORDERCHAR)
		&& (field[y - FIELDY][x - FIELDX + 1] == enemy || field[y - FIELDY][x - FIELDX + 1] == BORDERCHAR))
	{
		breath = -1;
		field[y - FIELDY][x - FIELDX] = FIELDCHAR;
	}
	else if (field[y - FIELDY - 1][x - FIELDX] == FIELDCHAR - 256
		&& (field[y - FIELDY + 1][x - FIELDX] == enemy || field[y - FIELDY + 1][x - FIELDX] == BORDERCHAR)
		&& (field[y - FIELDY][x - FIELDX - 1] == enemy || field[y - FIELDY][x - FIELDX - 1] == BORDERCHAR)
		&& (field[y - FIELDY][x - FIELDX + 1] == enemy || field[y - FIELDY][x - FIELDX + 1] == BORDERCHAR))
	{
		breath = -1;
		field[y - FIELDY][x - FIELDX] = FIELDCHAR;
	}

	return breath;
}

//sprawdzanie oddechu do stawiania
int checkBreath2(int x, int y, int player, char** field, int breath, int size0, int x0, int y0) {

	char enemy = 0;
	char me = 0;
	int idenemy = 0;
	if (player == PLATYER0INDEX)
	{
		me = PLAYER0CHAR;
		enemy = PLAYER1CHAR;
		idenemy = PLATYER1INDEX;
	}
	else if (player == PLATYER1INDEX) {
		me = PLAYER1CHAR;
		enemy = PLAYER0CHAR;
		idenemy = PLATYER0INDEX;
	}


	if ((field[y - FIELDY - 1][x - FIELDX] == enemy || field[y - FIELDY - 1][x - FIELDX] == BORDERCHAR || field[y - FIELDY - 1][x - FIELDX] == DEATHCHAR)
		&& (field[y - FIELDY + 1][x - FIELDX] == enemy || field[y - FIELDY + 1][x - FIELDX] == BORDERCHAR || field[y - FIELDY + 1][x - FIELDX] == DEATHCHAR)
		&& (field[y - FIELDY][x - FIELDX - 1] == enemy || field[y - FIELDY][x - FIELDX - 1] == BORDERCHAR || field[y - FIELDY][x - FIELDX - 1] == DEATHCHAR)
		&& (field[y - FIELDY][x - FIELDX + 1] == enemy || field[y - FIELDY][x - FIELDX + 1] == BORDERCHAR || field[y - FIELDY][x - FIELDX + 1] == DEATHCHAR))
	{
		breath = checkKoBreath(x, y - 1, idenemy, field, breath) + checkKoBreath(x, y + 1, idenemy, field, breath) + checkKoBreath(x - 1, y, idenemy, field, breath) + checkKoBreath(x + 1, y, idenemy, field, breath);
	}
	else if (field[y - FIELDY - 1][x - FIELDX] == FIELDCHAR - 256 || field[y - FIELDY + 1][x - FIELDX] == FIELDCHAR - 256 || field[y - FIELDY][x - FIELDX - 1] == FIELDCHAR - 256 || field[y - FIELDY][x - FIELDX + 1] == FIELDCHAR - 256)
		breath++;
	else if (field[y - FIELDY - 1][x - FIELDX] == me || field[y - FIELDY + 1][x - FIELDX] == me || field[y - FIELDY][x - FIELDX - 1] == me || field[y - FIELDY][x - FIELDX + 1] == me)
	{
		int fieldbefore = 0;
		if (field[y - FIELDY][x - FIELDX] == FIELDCHAR - 256) {
			field[y - FIELDY][x - FIELDX] = me;
			fieldbefore = 1;
		}

		if (field[y - FIELDY - 1][x - FIELDX] == me && (y - 1) != y0) breath = breath + checkBreath2(x, y - 1, player, field, breath, size0, x, y);
		if (field[y - FIELDY + 1][x - FIELDX] == me && (y + 1) != y0) breath = breath + checkBreath2(x, y + 1, player, field, breath, size0, x, y);
		if (field[y - FIELDY][x - FIELDX - 1] == me && (x - 1) != x0) breath = breath + checkBreath2(x - 1, y, player, field, breath, size0, x, y);
		if (field[y - FIELDY][x - FIELDX + 1] == me && (x + 1) != x0) breath = breath + checkBreath2(x + 1, y, player, field, breath, size0, x, y);

		if (fieldbefore == 1) {
			if (breath == 0) field[y - FIELDY][x - FIELDX] = FIELDCHAR;
		}

	}
	else if ((field[y - FIELDY - 1][x - FIELDX] != enemy && (y - 1) != y0)
		|| (field[y - FIELDY + 1][x - FIELDX] != enemy && (y + 1) != y0)
		|| (field[y - FIELDY][x - FIELDX - 1] != enemy && (x - 1) != x0)
		|| (field[y - FIELDY][x - FIELDX + 1] != enemy && (x + 1) != x0))
		breath++;


	return breath;
}

//sprawdzanie oddechu do usmiercana
int checkBreath(int x, int y, int player, char** field, int breath, int size0, int x0, int y0) {

	char enemy = 0;
	char me = 0;
	int idenemy = 0;
	if (player == PLATYER0INDEX)
	{
		me = PLAYER0CHAR;
		enemy = PLAYER1CHAR;
		idenemy = PLATYER1INDEX;
	}
	else if (player == PLATYER1INDEX) {
		me = PLAYER1CHAR;
		enemy = PLAYER0CHAR;
		idenemy = PLATYER0INDEX;
	}


	if ((field[y - FIELDY - 1][x - FIELDX] == enemy || field[y - FIELDY - 1][x - FIELDX] == BORDERCHAR || field[y - FIELDY - 1][x - FIELDX] == DEATHCHAR)
		&& (field[y - FIELDY + 1][x - FIELDX] == enemy || field[y - FIELDY + 1][x - FIELDX] == BORDERCHAR || field[y - FIELDY + 1][x - FIELDX] == DEATHCHAR)
		&& (field[y - FIELDY][x - FIELDX - 1] == enemy || field[y - FIELDY][x - FIELDX - 1] == BORDERCHAR || field[y - FIELDY][x - FIELDX - 1] == DEATHCHAR)
		&& (field[y - FIELDY][x - FIELDX + 1] == enemy || field[y - FIELDY][x - FIELDX + 1] == BORDERCHAR || field[y - FIELDY][x - FIELDX + 1] == DEATHCHAR))
	{
		breath = 0;
	}
	else if (field[y - FIELDY - 1][x - FIELDX] == FIELDCHAR - 256 || field[y - FIELDY + 1][x - FIELDX] == FIELDCHAR - 256 || field[y - FIELDY][x - FIELDX - 1] == FIELDCHAR - 256 || field[y - FIELDY][x - FIELDX + 1] == FIELDCHAR - 256)
		breath++;
	else if (field[y - FIELDY - 1][x - FIELDX] == me || field[y - FIELDY + 1][x - FIELDX] == me || field[y - FIELDY][x - FIELDX - 1] == me || field[y - FIELDY][x - FIELDX + 1] == me)
	{
		if (field[y - FIELDY - 1][x - FIELDX] == me && (y - 1) != y0) breath = breath + checkBreath(x, y - 1, player, field, breath, size0, x, y);
		if (field[y - FIELDY + 1][x - FIELDX] == me && (y + 1) != y0) breath = breath + checkBreath(x, y + 1, player, field, breath, size0, x, y);
		if (field[y - FIELDY][x - FIELDX - 1] == me && (x - 1) != x0) breath = breath + checkBreath(x - 1, y, player, field, breath, size0, x, y);
		if (field[y - FIELDY][x - FIELDX + 1] == me && (x + 1) != x0) breath = breath + checkBreath(x + 1, y, player, field, breath, size0, x, y);


	}
	else if (field[y - FIELDY - 1][x - FIELDX] != enemy || field[y - FIELDY + 1][x - FIELDX] != enemy || field[y - FIELDY][x - FIELDX - 1] != enemy || field[y - FIELDY][x - FIELDX + 1] != enemy)
		breath++;


	return breath;
}

//sprawdzanie zbicia
int checkDeath(char** field, int player, int size0) {

	int breath = 0;
	char enemy = 0;
	int playerscore = 0;
	if (player == PLATYER0INDEX) enemy = PLAYER0CHAR;
	else if (player == PLATYER1INDEX) enemy = PLAYER1CHAR;

	for (int y = FIELDY + 1; y < FIELDY + size0 + 1; y++)
	{
		for (int x = FIELDX + 1; x < FIELDX + size0 + 1; x++)
		{
			breath = 0;
			if (field[y - FIELDY][x - FIELDX] == enemy)
			{
				breath = checkBreath(x, y, player, field, breath, size0, 0, 0);
				if (breath == 0) {
					field[y - FIELDY][x - FIELDX] = DEATHCHAR;
					playerscore++;
				}
			}

		}
	}
	for (int y = FIELDY + 1; y < FIELDY + size0 + 1; y++)
	{
		for (int x = FIELDX + 1; x < FIELDX + size0 + 1; x++)
		{
			if (field[y - FIELDY][x - FIELDX] == DEATHCHAR) {
				field[y - FIELDY][x - FIELDX] = FIELDCHAR;

			}

		}
	}
	return playerscore;
}

//k³adzenie pionka
int putCounter(int player, char** field, int x, int y, int size0) {

	int breath = 0;
	char enemy = 0;
	char me = 0;
	int idenemy = 0;
	if (player == PLATYER0INDEX)
	{
		me = PLAYER0CHAR;
		enemy = PLAYER1CHAR;
		idenemy = PLATYER1INDEX;
	}
	else if (player == PLATYER1INDEX) {
		me = PLAYER1CHAR;
		enemy = PLAYER0CHAR;
		idenemy = PLATYER0INDEX;
	}

	breath = checkBreath2(x, y, player, field, breath, size0, 0, 0);
	if (field[y - FIELDY][x - FIELDX] == PLAYER0CHAR || field[y - FIELDY][x - FIELDX] == PLAYER1CHAR || breath == 0)
	{
		return player;
	}
	else if (breath < 0) {
		putch(PLAYER0CHAR);
		field[y - FIELDY][x - FIELDX] = me;
		player = player + 2;
		return player;
	}
	else {
		putch(PLAYER0CHAR);
		field[y - FIELDY][x - FIELDX] = me;
		return idenemy;
	}

	return 0;
}

//wprowadzanie nazwy pliku
void fileName(char text[100], char gamesave[30]) {

	int sign = 0;
	int i = 0;

	textbackground(BLACK);
	textcolor(LIGHTGRAY);
	gotoxy(MENUX, MENUY + 14);
	cputs("wpisz nazwe pliku: ");
	gotoxy(MENUX, MENUY + 16);
	cputs("enter - potwierdz");

	for (; ; ) {
		sign = getch();
		if (sign == '\r') break;
		gamesave[i] = sign;
		gotoxy(MENUX + 19, MENUY + 14);
		sprintf(text, "%s ", gamesave);
		cputs(text);
		i++;
	}
	gamesave[i] = '\0';
}

//zapisywanie gry do pliku
void saveGame(char** field, int size, int checkko, int player0score, int player1score)
{
	char text[100] = { };
	char gamesave[30] = { };
	char c = '#';

	fileName(text, gamesave);

	FILE* file = fopen(gamesave, "w");

	if (file != NULL)
	{
		fprintf(file, "%d", player0score);
		fprintf(file, "%c", c);
		fprintf(file, "%d", player1score);
		fprintf(file, "%c", c);
		fprintf(file, "%d", size);
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				fprintf(file, "%c", field[i][j]);

			}
		}
		fprintf(file, "%c", checkko);

		fclose(file);
	}
}

//wczytywanie gry do pliku
int loadGame(char** field, int& size, int& player0score, int& player1score)
{
	int checkko = 0;
	char text[100] = { };
	char gamesave[30] = { };
	char c = {};

	fileName(text, gamesave);

	FILE* file = fopen(gamesave, "r");
	if (file != NULL)
	{
		fscanf(file, "%d", &player0score);
		fscanf(file, "%c", &c);
		fscanf(file, "%d", &player1score);
		fscanf(file, "%c", &c);
		fscanf(file, "%d", &size);

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				fscanf(file, "%c", &field[i][j]);

			}
		}
		fscanf(file, "%d", &checkko);

		fclose(file);
	}
	return checkko;
}

//rysowanie menu wyboru rozmiaru planszy
void printSizeMenu() {

	clrscr();
	textbackground(BLACK);
	textcolor(LIGHTGRAY); /*kolor tekstu*/
	gotoxy(MENUX, MENUY);
	cputs("Wybierz rozmiar menu klikajac odpowiednia literke");
	gotoxy(MENUX, MENUY + 1);
	cputs("a - 9");
	gotoxy(MENUX, MENUY + 2);
	cputs("b - 13");
	gotoxy(MENUX, MENUY + 3);
	cputs("c - 19");
	gotoxy(MENUX, MENUY + 4);
	cputs("d - dodaj wlasny rozmiar");
	gotoxy(MENUX, MENUY + 6);
	cputs("enter - potwierdz wybor rozmiaru");
}

//rysowanie menu i wybor wlasnego rozmiaru planszy
int chooseFieldSize() {

	text_info info;
	gettextinfo(&info);

	int sign = 0;
	int size0 = 9;
	char text[100] = {};

	do {
		sign = getch();
		if (sign == 'a') size0 = 9;
		if (sign == 'b') size0 = 13;
		if (sign == 'c') size0 = 19;
		if (sign == 'd') {
			clrscr();
			gotoxy(MENUX, MENUY);
			cputs("Wpisz rozmiar planszy: ");
			gotoxy(MENUX, MENUY + 1);
			cputs("enter - potwierdz wybor rozmiaru");
			int size0before = 0;
			for (; ; ) {
				sign = getch();
				if (sign == '\r') {
					if ((FIELDY + size0 + BORDER * 2) > info.screenheight)
					{
						sign = 'd';
						gotoxy(MENUX, MENUY + 5);
						cputs("NIEPRAWIDLOWY ROZMIAR! WPISZ INNY ROZMIAR");
					}
					else break;
				}
				if (sign == 'd')
				{
					sign = getch();
					size0before = 0;
					size0 = 0;
				}
				size0 = (int)sign;
				size0 = size0 - 48 + size0before;
				size0before = size0 * 10;
				gotoxy(MENUX + MENUXSIZE - 12, MENUY);
				sprintf(text, "%d ", size0);
				cputs(text);
			}


		}

	} while (sign != '\r');
	return size0;
}

//gra z handicapem
void handicap(char** field, int size0, int x, int y) {

	int sign = 0;

	clrscr();
	textbackground(BLACK);
	textcolor(LIGHTGRAY); /*kolor tekstu*/
	gotoxy(MENUX, MENUY);
	cputs("Czy chcesz skorzystac z handicapa?");
	gotoxy(MENUX, MENUY + 2);
	cputs("tak - wcisnij 1");
	gotoxy(MENUX, MENUY + 3);
	cputs("nie - wcisnij 0");

	sign = getch();

	if (sign == '1') {
		clrscr();
		gotoxy(MENUX, MENUY);
		cputs("i - postaw pionek");
		gotoxy(MENUX, MENUY + 1);
		cputs("enter - zakoncz handicap");
		printField(field, size0);
		gotoxy(x, y);
		textbackground(LIGHTGREEN);
		putch(field[y - FIELDY][x - FIELDX]);
		sign = 0;
		for (; ; ) {
			sign = getch();
			if (sign == '\r') break;
			else if (sign == 0) /*jeœli strza³ki*/
			{
				printField(field, size0); /*wypisuje plansze*/
				sign = getch();
				if (sign == 0x48)
				{
					if (y == FIELDY + 1) y = y;
					else y--;
				}
				else if (sign == 0x50) {
					if (y == (FIELDY + size0)) y = y;
					else y++;
				}
				else if (sign == 0x4b)
				{
					if (x == FIELDX + 1) x = x;
					else x--;
				}
				else if (sign == 0x4d)
				{
					if (x == (FIELDX + size0)) x = x;
					else x++;
				}
				gotoxy(x, y);
				textbackground(LIGHTGREEN);
				putch(field[y - FIELDY][x - FIELDX]);
			}
			else if (sign == 'i') /*jeœli stawianie pionka*/
			{
				gotoxy(x, y);
				textbackground(LIGHTGREEN);
				putch(PLAYER0CHAR);
				field[y - FIELDY][x - FIELDX] = PLAYER1CHAR;
				printField(field, size0);
				gotoxy(x, y);
				textbackground(LIGHTGREEN);
				putch(field[y - FIELDY][x - FIELDX]);
			}
		}

	}
}

//inicjalizacja planszy dynamicznej
void initializeField(char** field, int size) {
	for (int i = 0; i < size; i++)
		field[i] = new char[size];
}

//usuwanie planszy dynamicznej
void deleteField(char** field, int size) {
	for (int i = 0; i < size; i++)
		delete[] field[i];

	delete[] field;
}

//funkcja glowna
int main() {
	int sign = 0, x = FIELDX + 1, y = FIELDY + 1;

#ifndef __cplusplus
	Conio2_Init();
#endif

	settitle("Franciszek Gwarek, 193192");

	_setcursortype(_NOCURSOR);

	printSizeMenu();

	int size0 = chooseFieldSize();

	int size = size0 + BORDER * 2;

	char** field = new char* [size];
	initializeField(field, size);

	char** fieldbefore1 = new char* [size];
	initializeField(fieldbefore1, size);

	char** fieldbefore2 = new char* [size];
	initializeField(fieldbefore2, size);

	int player = PLATYER0INDEX;
	int player0score = 0;
	int player1score = 0;

	makeField(field, size0);
	makeField(fieldbefore1, size0);
	makeField(fieldbefore2, size0);

	handicap(field, size0, x, y);

	textbackground(BLACK);
	clrscr();
	textcolor(LIGHTGRAY);

	printMenu(x, y, player0score, player1score); /*wypisuje menu*/
	printField(field, size0); /*wypisuje plansze*/

	gotoxy(FIELDX + 1, FIELDY + 1);
	textbackground(LIGHTGREEN);
	putch(FIELDCHAR);
	int score0before = player0score;
	int score1before = player0score;
	int checkko = 0;

	do
	{
		sign = getch();
		textcolor(BLACK);

		if (sign == 0) //przesuniecie pionka
		{
			printField(field, size0); /*wypisuje plansze*/
			sign = getch();
			if (sign == 0x48)
			{
				if (y != (FIELDY + BORDER)) y--;
			}
			else if (sign == 0x50) {
				if (y != (FIELDY + size0)) y++;
			}
			else if (sign == 0x4b)
			{
				if (x != (FIELDX + BORDER)) x--;
			}
			else if (sign == 0x4d)
			{
				if (x != (FIELDX + size0)) x++;
			}
			gotoxy(x, y);
			textbackground(LIGHTGREEN);
			putch(field[y - FIELDY][x - FIELDX]);
			printMenu(x, y, player0score, player1score); /*wypisuje menu*/
		}
		else if (sign == 'n') //nowa gra
		{
			player0score = 0;
			player1score = 0;
			player = PLATYER0INDEX;

			deleteField(field, size);
			field = NULL;
			deleteField(fieldbefore1, size);
			fieldbefore1 = NULL;
			deleteField(fieldbefore2, size);
			fieldbefore2 = NULL;

			textbackground(BLACK);
			clrscr();
			textcolor(LIGHTGRAY);

			printSizeMenu();
			size0 = chooseFieldSize();
			size = size0 + BORDER * 2;
			field = new char* [size];
			initializeField(field, size);

			fieldbefore1 = new char* [size];
			initializeField(fieldbefore1, size);

			fieldbefore2 = new char* [size];
			initializeField(fieldbefore2, size);

			makeField(field, size0);
			makeField(fieldbefore1, size0);
			makeField(fieldbefore2, size0);
			x = FIELDX + 1;
			y = FIELDY + 1;
			handicap(field, size0, x, y);

			textbackground(BLACK);
			clrscr();
			textcolor(LIGHTGRAY);
			printField(field, size0); //wypisuje planszê
			gotoxy(x, y);
			textbackground(LIGHTGREEN);
			putch(FIELDCHAR);
			printMenu(x, y, player0score, player1score); //wypisuje menu

		}
		else if (sign == 'i') //stawianie pionka
		{
			gotoxy(x, y);
			textbackground(LIGHTGREEN);
			int playerbefore = player;
			player = putCounter(playerbefore, field, x, y, size0); /*sprawdzanie czy mo¿na postawiæ*/
			score0before = player0score;
			score1before = player1score;

			if (player == 2) {
				player0score = score0before + 1;
				player = PLATYER1INDEX;
				checkko = comparisonField(fieldbefore2, field, size0);
			}
			else if (player == 3) {
				player1score = score1before + 1;
				player = PLATYER0INDEX;
				checkko = comparisonField(fieldbefore2, field, size0);
			}
			else checkko = comparisonField(fieldbefore1, field, size0);

			player0score = player0score + checkDeath(field, 1, size0); /*sprawdza czy coœ zosta³o zbite i wynik 1 gracza*/
			player1score = player1score + checkDeath(field, 0, size0); /*sprawdza czy coœ zosta³o zbite i wynik 2 gracza*/
			if (checkko == 0) {
				rewriteField(fieldbefore1, field, size0);
				player = playerbefore;
				player0score = score0before;
				player1score = score1before;
			}
			else {
				rewriteField(fieldbefore1, fieldbefore2, size0);
				rewriteField(field, fieldbefore1, size0);
			}
			printMenu(x, y, player0score, player1score);
			printField(field, size0);
			gotoxy(x, y);
			textbackground(LIGHTGREEN);
			putch(field[y - FIELDY][x - FIELDX]);

		}
		else if (sign == 's') //zapisywanie gry
		{
			saveGame(field, size0, checkko, player0score, player1score);
			clrscr();
			printMenu(x, y, player0score, player1score);
			printField(field, size0);
			gotoxy(x, y);
			textbackground(LIGHTGREEN);
			putch(field[y - FIELDY][x - FIELDX]);
		}
		else if (sign == 'l') //wczytywanie gry
		{

			checkko = loadGame(field, size, player0score, player1score);

			textbackground(BLACK);
			clrscr();
			textcolor(LIGHTGRAY);

			x = FIELDX + 1;
			y = FIELDY + 1;

			printMenu(x, y, player0score, player1score); /*wypisuje menu*/
			printField(field, size0); /*wypisuje plansze*/

			gotoxy(FIELDX + 1, FIELDY + 1);
			textbackground(LIGHTGREEN);
			putch(field[y - FIELDY][x - FIELDX]);
		}
	} while (sign != 'q'); //koniec gry

	deleteField(field, size);
	deleteField(fieldbefore1, size);
	deleteField(fieldbefore2, size);

	gotoxy(MENUX, FIELDY + size0 + 3);
	textbackground(BLACK);
	textcolor(LIGHTGRAY);
	char end[50] = "GRA ZAKONCZONA:";
	char txt[100] = {};
	gotoxy(MENUX + 6, MENUY + 15);
	sprintf(txt, "%s", end);
	cputs(txt);
	gotoxy(MENUX + 6, MENUY + 16);
	if (player0score > player1score) cputs("Wygral gracz 1!");
	else if (player1score > player0score) cputs("Wygral gracz 2!");
	else cputs("Mamy remis!");
	gotoxy(1, MENUY + 18);
	_setcursortype(_NORMALCURSOR);
	return 0;
}
