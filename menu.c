#include "menu.h"
#include "game.h"

#define WindowWidth 12
#define WindowHeight 12.5

bool pauseButtonStatus;

void drawMenu() {
	static char * menulistGame[] = {
		"Game",
		"New Game | Ctrl-B",
		"Pause | Ctrl-S",
		"Ranklist | Ctrl-E",
		"Preferences",
		"Themes",
		"Exit",
	};
	static char * selectedLabel = NULL;

	double fH = GetFontHeight();
	double x = 0; //fH/8;
	double y = WindowHeight;
	double h = fH * 1.5; // 控件高度
	double w = TextStringWidth(menulistGame[0]) * 2; // 控件宽度
	double wlist = TextStringWidth(menulistGame[0])*2.5;
	double xindent = WindowHeight / 20; // 缩进
	int	selection;

	menulistGame[2] = pauseButtonStatus ? "Resume | Ctrl-S" : "Pause | Ctrl-S";
	selection = menuList(GenUIID(0), x, y - h, w, wlist + 0.7, h, menulistGame, sizeof(menulistGame) / sizeof(menulistGame[0]));
	if (selection > 0) selectedLabel = menulistGame[selection];
	if (selection == 1) {
		newGame();
		pauseButtonStatus = 0;
	}
	if (selection == 2) {
		if (switchGame(!pauseButtonStatus) != -1) pauseButtonStatus = !pauseButtonStatus;
	}
	if (selection == 6) exit(-1); // choose to exit
}