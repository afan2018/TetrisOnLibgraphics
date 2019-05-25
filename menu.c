#include "menu.h"
#include "game.h"

#define WindowWidth 12
#define WindowHeight 12.5

bool pauseButtonStatus;

int popRanklist = 0;

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
	switch (selection) {
	case 1:
		newGame();
		pauseButtonStatus = 0;
		break;
	case 2:
		if (switchGame(!pauseButtonStatus) != -1)
			pauseButtonStatus = !pauseButtonStatus;
		break;
	case 3:
		popRanklist = 1;
		break;
	case 6:
		exit(-1);
	}
}