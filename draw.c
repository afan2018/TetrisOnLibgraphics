#include "draw.h"

#define WindowWidth 12
#define WindowHeight 12.5
int pics = 0;
extern int popRanklist;
extern int popHelp;
void drawButtons()
{
	double fH = GetFontHeight();
	double h = fH * 2;  // 控件高度
	double x = WindowWidth / 2.5;
	double y = WindowHeight / 2 - h;
	double w = WindowWidth / 5; // 控件宽度

	if (button(GenUIID(0), x, y, w, h, "Start"))
	{
		pics = 1;
		newGame();
	}

	if (button(GenUIID(0), x, y - 1.5*h, w, h, "Ranklist"))
	{
		popRanklist = 1;
	}

	if (button(GenUIID(0), x, y - 3 * h, w, h, "Random Button Colors"))
	{
		static char * c[] = { "Black","Dark Gray","Gray","Light Gray","White", "Cyan",
			"Brown", "Red", "Orange", "Yellow", "Green","Blue","Violet", "Magenta" };
		int N = sizeof(c) / sizeof(c[0]);
		static int times = 0; times++;
		setButtonColors(c[times%N], c[(times + 1) % N], c[(times + 2) % N], c[(times + 3) % N], 1);
	}

	if (button(GenUIID(0), x, y - 4.5 * h, w, h, "Help"))
	{
		popHelp = 1;
	}

}

void drawT()
{
	SetPenSize(2);
	SetPenColor("Black");
	MovePen(1.4, 10);
	DrawLine(0.4, 0);
	DrawLine(0, -1);
	DrawLine(0.4, 0);
	DrawLine(0, 1);
	DrawLine(0.4, 0);
	DrawLine(0, 0.4);
	DrawLine(-1.2, 0);
	DrawLine(0, -0.4);

	MovePen(4.6, 10);
	DrawLine(0.4, 0);
	DrawLine(0, -1);
	DrawLine(0.4, 0);
	DrawLine(0, 1);
	DrawLine(0.4, 0);
	DrawLine(0, 0.4);
	DrawLine(-1.2, 0);
	DrawLine(0, -0.4);
}

void drawE()
{
	SetPenSize(2);
	SetPenColor("Black");
	MovePen(3.1, 9);
	DrawLine(1, 0);
	DrawLine(0, 0.34);
	DrawLine(-0.66, 0);
	DrawLine(0, 0.19);
	DrawLine(0.66, 0);
	DrawLine(0, 0.34);
	DrawLine(-0.66, 0);
	DrawLine(0, 0.19);
	DrawLine(0.66, 0);
	DrawLine(0, 0.34);
	DrawLine(-1, 0);
	DrawLine(0, -1.4);
}

void drawR()
{
	SetPenSize(2);
	SetPenColor("Black");
	MovePen(6.3, 10.4);
	DrawLine(0.8, 0);
	DrawLine(0, -0.8);
	DrawLine(-0.3, 0);
	DrawLine(0.5, -0.6);
	DrawLine(-0.3, 0);
	DrawLine(-0.5, 0.6);
	DrawLine(0, -0.6);
	DrawLine(-0.2, 0);
	DrawLine(0, 1.4);
	
	MovePen(6.5, 10.2);
	DrawLine(0.4, 0);
	DrawLine(0, -0.4);
	DrawLine(-0.4, 0);
	DrawLine(0, 0.4);
}

void drawI()
{
	SetPenSize(2);
	SetPenColor("Black");
	MovePen(7.8, 10.4);
	DrawLine(0.4, 0);
	DrawLine(0, -0.4);
	DrawLine(-0.4, 0);
	DrawLine(0, 0.4);

	MovePen(7.8, 9.8);
	DrawLine(0.4, 0);
	DrawLine(0, -0.8);
	DrawLine(-0.4, 0);
	DrawLine(0, 0.8);
}

void drawS()
{
	SetPenSize(2);
	SetPenColor("Black");
	MovePen(8.7, 10.4);
	DrawLine(1, 0);
	DrawLine(0, -0.2);
	DrawLine(-0.7, 0);
	DrawLine(0, -0.4);
	DrawLine(0.7, 0);
	DrawLine(0, -0.8);
	DrawLine(-1, 0);
	DrawLine(0, 0.2);

	DrawLine(0.7, 0);
	DrawLine(0, 0.4);
	DrawLine(-0.7, 0);
	DrawLine(0, 0.8);
	
}