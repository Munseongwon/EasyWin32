// EW32_Exercise.cpp
// Visual Studio 2022 x86 Debug Mode

#include "pch.h"
#include <math.h>
#define _USE_INIT_WINDOW_
#include "tipsware.h"

NOT_USE_MESSAGE

void InitWindow() 
{
	gp_window_title = "Tut-01";
}

int main()
{
	Ellipse(100, 100, 200, 200, RGB(0, 255, 100), RGB(0, 128, 64));
	
	int x = (int)(cos(45 * 3.141592 / 180) * 50);
	
	Rectangle(150 - x, 150 - x, 150 + x, 150 + x, RGB(0, 100, 255), RGB(0, 0, 128));
	return 0;
}