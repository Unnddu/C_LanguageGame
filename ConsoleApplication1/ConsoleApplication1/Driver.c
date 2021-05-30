// Driver.c : This file contains the 
// 'main' function. Program execution begins and ends there.
#define _CRT_SECURE_NO_WARNINGS
/*
Date: 2021. 05. 31.
Name: KIMDAEJIN
*/
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include"Screen.h"
void Init();
void Update();
void Render();
void Release();
PLAYER g_Player;
char g_strPlayer[] = "  [[[[_[]_]]]]  ";
int g_nLength;
int main(void)
{
	int nKey = 0;
	int nRemain = 0;
	// initialization
	ScreenInit();
	Init();

	while (1)
	{
		if (_kbhit()) {
			nKey = _getch();
			if (nKey == 'q') { // quit
				break;
			}
			switch (nKey)
			{
			case 'a': // left move
				g_Player.nMoveX--;
				nRemain = g_nLength - (g_Player.nCenter->nX + 1);
				if (g_Player.nMoveX - g_Player.nCenter->nX < 0 ||
					g_Player.nMoveX + nRemain > 79) {
					g_Player.nMoveX--;
				}
				g_Player.nX = g_Player.nMoveX - g_Player.nCenter->nX;
				break;
			case 'd':
				g_Player.nMoveX++;
				nRemain = g_nLength - (g_Player.nCenter->nX + 1);
				if (g_Player.nMoveX + nRemain > 79 ||
					g_Player.nMoveX - g_Player.nCenter->nX < 0) {
					g_Player.nMoveX++;
				}
				g_Player.nX = g_Player.nMoveX - g_Player.nCenter->nX;
				break;
			}
		}
		Update(); // date update
		Render(); // print screen
	}

	// release
	Release();
	ScreenRelease();
	return 0;
}
void Init()
{
	g_Player.nCenter->nX = 4;
	g_Player.nCenter->nY = 0;
	g_Player.nMoveX = 20;
	g_Player.nY = g_Player.nMoveY = 22;
	g_Player.nX = g_Player.nMoveX - g_Player.nCenter->nX;
	g_nLength = strlen(g_strPlayer);
}
void Update()
{
}
// print code
void Render()
{
	char string[100] = { 0 };
	ScreenClear();

	// rendering start
	// 2 column flipping
	if (g_Player.nX < 0) { // left flipping
		ScreenPrint(0, g_Player.nMoveY, &g_strPlayer[g_Player.nX * -1]);
	}
	else if (g_Player.nMoveX + (g_nLength - g_Player.nCenter->nX + 1) > 79) {
		strncat(string, g_strPlayer, g_nLength - ((g_Player.nMoveX + g_Player.nCenter->nX
			+ 1) - 79));
		ScreenPrint(g_Player.nX, g_Player.nY, string);
	}
	else { // move 1 column
		ScreenPrint(g_Player.nX, g_Player.nY, g_strPlayer);
	}
	sprintf(string, "char mov pos: %d, %d", g_Player.nMoveX, g_Player.nY);
	ScreenPrint(0, 0, string);
	ScreenFlipping();
}
void Release()
{
}
