#include "game.h"
#include "menu.h"
#include "data.h"
#include "side.h"
#include "draw.h"
#include <windows.h>

#define WindowWidth 12
#define WindowHeight 12.5

void DisplayClear(void);
void display(void);
void drawGameArea(void);

void CharEventProcess(char ch) {
	uiGetChar(ch);
	display();
}

void KeyboardEventProcess(int key, int event) {
	uiGetKeyboard(key, event);
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
		case VK_SHIFT:
			holdDropping();
			break;
		}
	case KEY_UP:
		break;
	}
	display();
}

void MouseEventProcess(int x, int y, int button, int event) {
	uiGetMouse(x, y, button, event);
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
	SetWindowTitle("Tetris");
	SetWindowSize(WindowWidth, WindowHeight);

	InitGraphics();
	//InitConsole();
	srand(time(NULL));

	registerCharEvent(CharEventProcess);
	registerKeyboardEvent(KeyboardEventProcess);
	registerMouseEvent(MouseEventProcess);
	registerTimerEvent(TimerEventProcess);

	startTimer(1, 40);

	initData();
}

extern int theme;

void drawGlobalBackground() {
	SetPenColor(theme ? "white" : "black");
	drawRectangle(0, 0, WindowWidth, WindowHeight, 1);
}
extern int pics;
extern int popNameQuery;
extern int popRanklist;
extern int popContinueQuery;
extern int popRUSure;
extern int popHelp;
extern int popAbout;

void display() {
	DisplayClear();
	if (pics == 1) {
		drawGlobalBackground();
		drawGameArea();
		showBlock();
		drawMenu();
		drawScoreboard();
		drawLevelboard();
		drawGoalboard();
		drawNextDropping();
		drawHoldDropping();
	}
	if (pics == 0) {
		drawT();
		drawE();
		drawR();
		drawI();
		drawS();
		drawButtons();
	}
	if (popRanklist) drawRanklist();
	if (popNameQuery) drawNameQuery();
	if (popContinueQuery) drawLoadGameQuery();
	if (popRUSure) drawRUSure();
	if (popHelp) drawHelp();
	if (popAbout) drawAbout();
}