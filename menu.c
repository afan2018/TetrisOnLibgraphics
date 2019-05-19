#include "menu.h"

#define WindowWidth 12
#define WindowHeight 12.5

bool start, stop;

void drawMenu() {
	static char * menulistGame[] = {
		"Game",
		"Start | Ctrl-B",
		"Stop | Ctrl-S",
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
	int	selection;

	menulistGame[1] = start ? "Thanks | Ctrl-B" : "Start | Ctrl-B";
	menulistGame[2] = stop ? "Resume | Ctrl-S" : "Stop | Ctrl-S";
	selection = menuList(GenUIID(0), x, y - h, w, wlist + 0.7, h, menulistGame, sizeof(menulistGame) / sizeof(menulistGame[0]));
	if (selection > 0) selectedLabel = menulistGame[selection];
	if (selection == 1)
		start = !start;
	if (selection == 2)
		stop = !stop;
	if (selection == 3)
		exit(-1); // choose to exit
}