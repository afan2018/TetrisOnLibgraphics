#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "random.h"
#include "strlib.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stddef.h>

#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>

#include "imgui.h"
#include "game.h"

#define WindowWidth 12
#define WindowHeight 12
#define GameAreaWidth 8
#define GameAreaHeight 12

static int    stop = 0;   // 允许旋转
static int    start = 1; // 显示更多按钮

void DisplayClear(void); 
void startTimer(int id,int timeinterval);
void display(void); 
void drawBackground(void);
void drawGameArea(void);

void CharEventProcess(char ch) {
	uiGetChar(ch);
	display();
}

void KeyboardEventProcess(int key, int event) {
	uiGetKeyboard(key,event);
	switch (event) {
	case KEY_DOWN:
		switch (key) {
		case VK_LEFT:
			moveIt(0);
			break;
		case VK_RIGHT:
			moveIt(1);
			break;
		case VK_UP:
			rotateIt();
			break;
		case VK_DOWN:
			dropIt();
			break;
		case VK_SPACE:
			dropToBottom();
			break;
		}
	case KEY_UP:
		break;
	}
	display();
}

void MouseEventProcess(int x, int y, int button, int event) {
	uiGetMouse(x,y,button,event);
	display();
}

#define GAME_REFRESH_TIMER 1

void TimerEventProcess(int timerID) {
	if (timerID == GAME_REFRESH_TIMER) {
		refreshGame();
		display();
	}
}

void Main() {
	SetWindowTitle("Tetris By Group 16");
	SetWindowSize(WindowWidth, WindowHeight);

	InitGraphics();
	srand(time(NULL));

	registerCharEvent(CharEventProcess);
	registerKeyboardEvent(KeyboardEventProcess);
	registerMouseEvent(MouseEventProcess);
	registerTimerEvent(TimerEventProcess);

	startTimer(GAME_REFRESH_TIMER, 100);
}

void drawMenu() {
	static char * menulistGame[] = {
		"Game",
		"Start",
		"Stop",
		"Exit | Ctrl-E"
	};
	static char * selectedLabel = NULL;

	double fH = GetFontHeight();
	double x = 0; //fH/8;
	double y = WindowHeight;
	double h = fH * 1.5; // 控件高度
	double w = TextStringWidth(menulistGame[0]) * 2; // 控件宽度
	double wlist = TextStringWidth(menulistGame[0])*1.2;
	double xindent = WindowHeight / 20; // 缩进
	int    selection;

	menulistGame[1] = start ? "Start" : "Restart";
	menulistGame[2] = stop ? "Resume" : "Stop";
	selection = menuList(GenUIID(0), x, y - h, w, wlist + 0.5, h, menulistGame, sizeof(menulistGame) / sizeof(menulistGame[0]));
	if (selection > 0) selectedLabel = menulistGame[selection];
	if (selection == 1)
		start = !start;
	if (selection == 2)
		stop = !stop;
	if (selection == 3)
		exit(-1); // choose to exit

}

void display() {
	DisplayClear();
	drawBackground();
	drawGameArea();
	showBlock();
	drawMenu();
}

void drawBackground() {
	SetPenColor("black");
	SetPenSize(5000);
	MovePen(0, 0);
	DrawLine(12, 0);

}

void drawGameArea() {
	SetPenColor("red");
	SetPenSize(3);
	MovePen(GameAreaWidth, 0);
	DrawLine(0, GameAreaHeight);
}