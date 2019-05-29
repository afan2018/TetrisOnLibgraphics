#include "menu.h"
#include "game.h"

#define WindowWidth 12
#define WindowHeight 12.5

bool pauseButtonStatus = 0;

int popRanklist = 0;
int popRUSure = 0;
int theme = 1;

extern Game game;

void drawMenu() {
	static char * menulistGame[] = {
		"Game",
		"New Game | Ctrl-N",
		"Pause | Ctrl-P",
		"Ranklist | Ctrl-E",
		"Preferences",
		"Themes",
		"Exit"
	};

	static char * menulistHelp[] = {
		"Help",
		"Read Help",
		"About"
	};

	double fH = GetFontHeight();
	double x = 0; //fH/8;
	double y = WindowHeight;
	double h = fH * 1.5; // ¿Ø¼þ¸ß¶È
	double w = TextStringWidth(menulistGame[0]) * 2; // ¿Ø¼þ¿í¶È
	double wlist = TextStringWidth(menulistGame[0])*2.5;
	double xindent = WindowHeight / 20; // Ëõ½ø
	int	selection;

	menulistGame[2] = pauseButtonStatus ? "Resume | Ctrl-S" : "Pause | Ctrl-S";

	char * c[] = { "Menu1","Menu1","Menu2","Menu2","Menu3","Menu3","Menu4","Menu4" };

	setTextBoxColors(c[theme * 4], c[theme * 4 + 1], c[theme * 4 + 2], c[theme * 4 + 3], 0);
	setButtonColors(c[theme * 4], c[theme * 4 + 1], c[theme * 4 + 2], c[theme * 4 + 3], 0);
	setMenuColors(c[theme * 4], c[theme * 4 + 1], c[theme * 4 + 2], c[theme * 4 + 3], 0);

	selection = menuList(GenUIID(0), x, y - h, w, wlist + 0.7, h, menulistGame, sizeof(menulistGame) / sizeof(menulistGame[0]));

	switch (selection) {
	case 1:
		if (switchGame(1) != -1) {
			popRUSure = 1;
		}
		else {
			newGame();
			pauseButtonStatus = 0;
		}
		break;
	case 2:
		if (switchGame(!pauseButtonStatus) != -1)
			pauseButtonStatus = !pauseButtonStatus;
		break;
	case 3:
		popRanklist = 1;
		break;
	case 5:
		if (theme) theme = 1;
		setTextBoxColors(c[theme * 4], c[theme * 4 + 1], c[theme * 4 + 2], c[theme * 4 + 3], 0);
		setButtonColors(c[theme * 4], c[theme * 4 + 1], c[theme * 4 + 2], c[theme * 4 + 3], 0);
		setMenuColors(c[theme * 4], c[theme * 4 + 1], c[theme * 4 + 2], c[theme * 4 + 3], 0);
		theme = !theme;
		break;
	case 6:
		exit(-1);
	}
	selection = menuList(GenUIID(0), x + w, y - h, w, wlist + 0.4, h, menulistHelp, sizeof(menulistHelp) / sizeof(menulistGame[0]));
	switch (selection) {
	case 1:
		break;
	case 2:
		break;
	}
}