#include "menu.h"
#include "game.h"

#define WindowWidth 12
#define WindowHeight 12.5

bool pauseButtonStatus = 0;
bool themeButtonStatus = 0;

int popRanklist = 0;
int popRUSure = 0;
int popHelp = 0;
int popAbout = 0;
int theme = 1;

extern Game game;

extern char * c[];

void drawHelp() {
	SetPenColor("Background1");
	drawRectangle(3, 3.2, 6, 5, 1);
	SetPenColor("Border1");
	drawRectangle(3, 3.2, 6, 5, 0);
	MovePen(4.3, 7.6);
	DrawTextString("KEYBOARD INSTRUCTIONS");
	MovePen(3.5, 6.9);
	DrawTextString("Left & Right                 Move");
	MovePen(3.5, 6.3);
	DrawTextString("Up                               Rotate");
	MovePen(3.5, 5.7);
	DrawTextString("Down                          Drop faster");
	MovePen(3.5, 5.1);
	DrawTextString("Space                         Drop to the bottom");
	MovePen(3.5, 4.5);
	DrawTextString("Shift                            Hold and Switch");
	setTextBoxColors(c[theme * 4], c[theme * 4 + 1], c[theme * 4 + 2], c[theme * 4 + 3], 0);
	setButtonColors(c[theme * 4], c[theme * 4 + 1], c[theme * 4 + 2], c[theme * 4 + 3], 0);
	setMenuColors(c[theme * 4], c[theme * 4 + 1], c[theme * 4 + 2], c[theme * 4 + 3], 0);
	if (button(GenUIID(0), 5, 3.5, 2, 0.5, "Dismiss")) {
		popHelp = 0;
	}
}

void drawAbout() {
	SetPenColor("Background1");
	drawRectangle(3, 3.2, 6, 5, 1);
	SetPenColor("Border1");
	drawRectangle(3, 3.2, 6, 5, 0);
	MovePen(5.6, 7.6);
	DrawTextString("ABOUT");
	MovePen(4.9, 6.9);
	DrawTextString("Made by Group 16");
	MovePen(5.3, 6.3);
	DrawTextString("Fan Andong");
	MovePen(5.25, 5.7);
	DrawTextString("Wang Caiyu");
	MovePen(5.3, 5.1);
	DrawTextString("Yao Zheyu");
	MovePen(4.3, 4.5);
	DrawTextString("2019 · No Right to Reserve");
	setTextBoxColors(c[theme * 4], c[theme * 4 + 1], c[theme * 4 + 2], c[theme * 4 + 3], 0);
	setButtonColors(c[theme * 4], c[theme * 4 + 1], c[theme * 4 + 2], c[theme * 4 + 3], 0);
	setMenuColors(c[theme * 4], c[theme * 4 + 1], c[theme * 4 + 2], c[theme * 4 + 3], 0);
	if (button(GenUIID(0), 5, 3.5, 2, 0.5, "Dismiss")) {
		popAbout = 0;
	}
}

void drawMenu() {
	static char * menulistGame[] = {
		"Game",
		"New Game | Ctrl-N",
		"Pause | Ctrl-P",
		"Ranklist",
		"Dark Theme",
		"Exit"
	};

	static char * menulistHelp[] = {
		"Help",
		"Read Help",
		"About"
	};

	double fH = GetFontHeight();
	double x = 0;
	double y = WindowHeight;
	double h = fH * 1.5;
	double w = TextStringWidth(menulistGame[0]) * 2;
	double wlist = TextStringWidth(menulistGame[0])*2.5;
	double xindent = WindowHeight / 20;
	int	selection;

	menulistGame[2] = pauseButtonStatus ? "Resume | Ctrl-P" : "Pause | Ctrl-P";
	menulistGame[4] = themeButtonStatus ? "Bright Theme" : "Dark Theme";

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
	case 4:
		setTextBoxColors(c[theme * 4], c[theme * 4 + 1], c[theme * 4 + 2], c[theme * 4 + 3], 0);
		setButtonColors(c[theme * 4], c[theme * 4 + 1], c[theme * 4 + 2], c[theme * 4 + 3], 0);
		setMenuColors(c[theme * 4], c[theme * 4 + 1], c[theme * 4 + 2], c[theme * 4 + 3], 0);
		theme = !theme;
		themeButtonStatus = !themeButtonStatus;
		break;
	case 5:
		exit(-1);
	}

	selection = menuList(GenUIID(0), x + w, y - h, w, wlist + 0.4, h, menulistHelp, sizeof(menulistHelp) / sizeof(menulistGame[0]));
	switch (selection) {
	case 1:
		popHelp = 1;
		if (switchGame(1) != -1) pauseButtonStatus = 1;
		break;
	case 2:
		popAbout = 1;
		if (switchGame(1) != -1) pauseButtonStatus = 1;
		break;
	}
}