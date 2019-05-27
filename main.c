#include "imgui.h"
#include "game.h"
#include "menu.h"
#include "data.h"

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
	SetWindowTitle("Tetris By Group 16");
	SetWindowSize(WindowWidth, WindowHeight);

	InitGraphics();
	InitConsole();
	srand(time(NULL));

	registerCharEvent(CharEventProcess);
	registerKeyboardEvent(KeyboardEventProcess);
	registerMouseEvent(MouseEventProcess);
	registerTimerEvent(TimerEventProcess);

	startTimer(1, 40);

	initData();
}

void drawGlobalBackground() {
	SetPenColor("black");
	drawRectangle(0, 0, WindowWidth, WindowHeight, 1);
}

extern int popNameQuery;
extern int popRanklist;
extern int popContinueQuery;

void display() {
	DisplayClear();
	drawGlobalBackground();
	drawGameArea();
	showBlock();
	drawMenu();
	drawScoreboard();
	drawLevelboard();
	drawGoalboard();
	drawNextDropping();
	drawHoldDropping();
	if (popRanklist) drawRanklist();
	if (popNameQuery) drawNameQuery();
	if (popContinueQuery) drawContinueQuery();
}
