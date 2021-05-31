#include"Frame.h"
#include"Screen.h"
ENEMY g_Enemy;
CANNON g_Cannon;
char g_strCannon[] = "¢Á";
int g_sHPScore = 80;
PLAYER g_Player;
char g_strPlayer[] = "[[[[_[]_]]]]";
int g_nLength;
void Init()
{
	g_Player.nCenter->nX = 5;
	g_Player.nCenter->nY = 0;
	g_Player.nMoveX = 20;
	g_Player.nY = g_Player.nMoveY = 22;
	g_Player.nX = g_Player.nMoveX - g_Player.nCenter->nX;
	g_nLength = strlen(g_strPlayer);

	// ball initialization 
	g_Cannon.nIsReady = 1;
	g_Cannon.nMoveX = g_Player.nMoveX;
	g_Cannon.nMoveY = g_Player.nMoveY - 1;
	g_Cannon.MoveTime = 10; // speed

	// enemy init
	int length = 0;
	g_Enemy.nMoveX = 20;
	g_Enemy.nMoveY = 2;
	g_Enemy.nLength = 1;
	g_Enemy.MoveTime = 100;
	g_Enemy.OldTime = clock();
	g_Enemy.nDist = 1;
	length = g_Enemy.nLength * 2 + 1; // array max index
	for (int i = 0; i < length; i++) {
		g_Enemy.nLineX[i] = g_Enemy.nMoveX + 2 * (i + 1);
	}
}
void Update()
{
	clock_t CurTime = clock();
	int length = g_Enemy.nLength * 2 + 1;

	// cannon mov processing
	if (g_Cannon.nIsReady == 0) { // if moving
		// Movement by move time interval
		if ((CurTime - g_Cannon.OldTime) > g_Cannon.MoveTime) {
			if (g_Cannon.nMoveY - 1 > 0) {
				g_Cannon.nMoveY--;
				g_Cannon.OldTime = CurTime;

				// crash & kill
				if ( g_Cannon.nMoveX >= g_Enemy.nLineX[0] &&
					g_Cannon.nMoveX + 1 <= g_Enemy.nLineX[length - 1]) {
					if (g_Cannon.nMoveY <= g_Enemy.nMoveY) {
						// Cannon init
						g_Cannon.nIsReady = 1;
						g_Cannon.nMoveX = g_Player.nMoveX;
						g_Cannon.nMoveY = g_Player.nMoveY - 1;
						--g_sHPScore;
					}
				}
				// crash & safe
				else if ((g_Cannon.nMoveX >= g_Enemy.nLineX[0] - 2 &&
					g_Cannon.nMoveX <= g_Enemy.nLineX[0] - 1) ||
					(g_Cannon.nMoveX + 1 >= g_Enemy.nLineX[0] - 2 &&
					g_Cannon.nMoveX + 1 <= g_Enemy.nLineX[0] - 1) ||
					(g_Cannon.nMoveX >= g_Enemy.nLineX[length - 1] + 2 &&
						g_Cannon.nMoveX <= g_Enemy.nLineX[length - 1] + 3) ||
					g_Cannon.nMoveX + 1 <= g_Enemy.nLineX[length - 1] + 3) {
					if (g_Cannon.nMoveY <= g_Enemy.nMoveY) {
						// Cannon init
						g_Cannon.nIsReady = 1;
						g_Cannon.nMoveX = g_Player.nMoveX;
						g_Cannon.nMoveY = g_Player.nMoveY - 1;
					}
				}

			}
			else {
				// Cannon init
				g_Cannon.nIsReady = 1;
				g_Cannon.nMoveX = g_Player.nMoveX;
				g_Cannon.nMoveY = g_Player.nMoveY - 1;
			}
		}
	}
	else {
		g_Cannon.nMoveX = g_Player.nMoveX;
	}

	// enemy mov processing
	if ((CurTime - g_Enemy.OldTime) > g_Enemy.MoveTime) {
		g_Enemy.OldTime = CurTime;
		if (g_Enemy.nMoveX + g_Enemy.nDist >= 0 &&
			((g_Enemy.nLineX[length - 1] + 3) + g_Enemy.nDist) <= 79) {
			g_Enemy.nMoveX += g_Enemy.nDist * 2; // speed
			for (int i = 0; i < length; i++) {
				g_Enemy.nLineX[i] = g_Enemy.nMoveX + 2 * (i + 1);
			}
		}
		else {
			g_Enemy.nDist *= -1;
		}
	}

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

	// cannon
	ScreenPrint(g_Cannon.nMoveX, g_Cannon.nMoveY, g_strCannon);

	// enemy
	int length = 0;
	ScreenPrint(g_Enemy.nMoveX, g_Enemy.nMoveY, "<");
	length = g_Enemy.nLength * 2 + 1;
	for (int i = 0; i < length; i++) {
		ScreenPrint(g_Enemy.nLineX[i], g_Enemy.nMoveY, "{");
	}
	ScreenPrint(g_Enemy.nLineX[length - 1] + 2, g_Enemy.nMoveY, "~");
	for (int i = 0; i < g_sHPScore; i++) {
		ScreenPrint(0 + i, 0, ":]"); // hp bar
	}
	ScreenPrint(0, 0, string);
	ScreenFlipping();
}
void Release()
{
}
void MainLoop()
{
	int nKey = 0;
	int nRemain = 0;
	while (1)
	{
		if (_kbhit()) {
			nKey = _getch();
			if (nKey == 'q' || nKey == 'Q' || g_sHPScore == 0) { // quit
				break;
			}
			switch (nKey)
			{
			case 'A':
			case 'a': // left move
				if (g_Player.nMoveX > 0) {
					g_Player.nMoveX--;
					nRemain = g_nLength - (g_Player.nCenter->nX + 1);
					if (g_Player.nMoveX - g_Player.nCenter->nX < 0 ||
						g_Player.nMoveX + nRemain > 79) {
						g_Player.nMoveX--;
					}
					g_Player.nX = g_Player.nMoveX - g_Player.nCenter->nX;
				}
				break;
			case 'D':
			case 'd':
				if (g_Player.nMoveX + 1 < 79) {
					g_Player.nMoveX++;
					nRemain = g_nLength - (g_Player.nCenter->nX + 1);
					if (g_Player.nMoveX + nRemain > 79 ||
						g_Player.nMoveX - g_Player.nCenter->nX < 0) {
						g_Player.nMoveX++;
					}
					g_Player.nX = g_Player.nMoveX - g_Player.nCenter->nX;
				}
				break;
			case 'S':
			case 's':
				if (g_Cannon.nIsReady) {
					g_Cannon.nMoveX = g_Player.nMoveX;
					g_Cannon.nMoveY = g_Player.nMoveY - 1;
					g_Cannon.OldTime = clock();
					g_Cannon.nIsReady = 0;
				}
				break;
			}
		}
		Update(); // date update
		Render(); // print screen
	}
}