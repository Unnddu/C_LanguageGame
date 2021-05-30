#pragma once
void ScreenInit();
void ScreenClear();
void ScreenRelease();
void ScreenFlipping();
void SetColor(unsigned short);
void ScreenPrint(int, int, char*);
typedef struct _POSITION
{
	int nX, nY;
} POSITION;
typedef struct _PLAYER
{
	POSITION nCenter[10];
	int nMoveX, nMoveY;
	int nX, nY;
	int nIndex;
} PLAYER;