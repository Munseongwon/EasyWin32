#include "pch.h"
#define _USE_INIT_WINDOW_
#include "tipsware.h"

NOT_USE_MESSAGE

void InitWindow() 
{
	gp_window_title = "Tut - 02";
}

void DrawRedRectangle()
{	
	int ri = 0;
	while (ri < 20) {
		Rectangle(30 + 22 * ri, 120, 50 + 22 * ri, 140, RGB(12 * ri, 0, 0), RGB(12 * ri, 0, 0));
		++ri;
	}
	ri = 0;
	while (ri < 20) {
		Rectangle(30 + 21 * ri, 150, 70 + 21 * ri, 170, RGB(12 * ri, 0, 0), RGB(12 * ri, 0, 0));
		++ri;
	}
	ri = 0;
	while (ri < 40) {
		Rectangle(30 + 11 * ri, 180, 41 + 11 * ri, 200, RGB(6 * ri, 0, 0), RGB(6 * ri, 0, 0));
		++ri;
	}
}

void DrawGreenRectangle()
{
	int gi = 0; // green recatngle output index
	while (gi < 20)
	{
		Rectangle(30 + 22 * gi, 30, 50 + 22 * gi, 50, RGB(0, 12 * gi, 0), RGB(0, 12 * gi, 0));
		++gi;
	}
	gi = 0;
	while (gi < 20)
	{
		Rectangle(30 + 21 * gi, 60, 70 + 21 * gi, 80, RGB(0, 12 * gi, 0), RGB(0, 12 * gi, 0));
		++gi;
	}
	gi = 0;
	while (gi < 40) {
		Rectangle(30 + 11 * gi, 90, 41 + 11 * gi, 110, RGB(0, 6 * gi, 0), RGB(0, 6 * gi, 0));
		++gi;
	}
}

void DrawBlueRectangle()
{
	int bi = 0; // blue rectangle output index
	while (bi < 20)
	{
		Rectangle(30 + 22 * bi, 210, 50 + 22 * bi, 230, RGB(0, 0, bi * 12), RGB(0, 0, bi * 12));
		++bi;
	}
	bi = 0;
	while (bi < 20)
	{
		Rectangle(30 + 21 * bi, 240, 70 + 21 * bi, 260, RGB(0, 0, bi * 12), RGB(0, 0, bi * 12));
		++bi;
	}
	bi = 0;
	while (bi < 40)
	{
		Rectangle(30 + 11 * bi, 270, 41 + 11 * bi, 290, RGB(0, 0, bi * 6), RGB(0, 0, bi * 6));
		++bi;
	}
}

int main()
{
	DrawRedRectangle();
	DrawGreenRectangle();
	DrawBlueRectangle();
	ShowDisplay();
	return 0;
}