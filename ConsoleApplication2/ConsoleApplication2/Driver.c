// Driver.c : This file contains the 'main' function. 
// Program execution begins and ends there.
#define _CRT_SECURE_NO_WARNINGS
/*
Date: 2021. 05. 31.
Name: KIMDAEJIN
<-: a, ->: d, shot: s, quit: q
*/
#include<time.h>
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include"Frame.h"
#include"Screen.h"

int main(void)
{
	// initialization
	ScreenInit();
	Init();

	MainLoop();

	// release
	Release();
	ScreenRelease();
	return 0;
}