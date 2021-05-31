#include<time.h>
void Init();
void Update();
void Render();
void Release();
void MainLoop();
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
typedef struct _CANNON
{
	int nIsReady;
	int nMoveX, nMoveY;
	clock_t MoveTime;
	clock_t OldTime;
} CANNON;
typedef struct _ENEMY
{
	int nMoveX, nMoveY;
	int nLength;
	int nLineX[7];
	int nDist;
	clock_t MoveTime;
	clock_t OldTime;
} ENEMY;