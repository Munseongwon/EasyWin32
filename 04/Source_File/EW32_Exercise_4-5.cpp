#include "pch.h"
#define _USE_INIT_WINDOW_
#include "tipsware.h"

#define MAX_COUNT	30

void InitWindow()
{
	gp_window_title = "EW32 - Tut04";
}

NOT_USE_MESSAGE

int main()
{
	char a = 6, b = 7, c = 8;
	unsigned int min_addr;
	min_addr = (unsigned int)&c;
	if ((unsigned int)&b < min_addr) min_addr = (unsigned int)&b;
	if ((unsigned int)&a < min_addr) min_addr = (unsigned int)&a;

	SelectFontObject("consolas", 18);
	SetTextColor(RGB(0, 100, 255));
	printf(10, 10, "a의 주소: %p, b의 주소: %p, c의 주소: %p", &a, &b, &c);
	
	SelectPenObject(RGB(0, 0, 128));
	SetTextColor(RGB(0, 0, 255));
	for (int i = 0, count = 0; i < MAX_COUNT; ++i)
	{
		if ((min_addr + i) == (unsigned int)&a ||
			(min_addr + i) == (unsigned int)&b ||
			(min_addr + i) == (unsigned int)&c)
		{
			SelectBrushObject(RGB(100, 255, 255));
			Rectangle(10 + i * 22, 50, MAX_COUNT + i * 22, 70);
			printf(15 + i * 22, 52, "%d", *(char*)(min_addr + i));
			Line(20 + i * 22, 72, 20 + i * 22, 160 - count * 20);
			printf(17 + i * 22, 163 - count * 20, "%p", (char *)min_addr + i);
			++count;
		}
		else {
			SelectBrushObject(RGB(228, 255, 255));
			Rectangle(10 + i * 22, 50, MAX_COUNT + i * 22, 70);
		}
	}	
	ShowDisplay();
	return 0;
}


#include "pch.h"
#define _USE_INIT_WINDOW_
#include "tipsware.h"

#define MAX_COUNT	30

void InitWindow()
{
	gp_window_title = "EW32 - Tut04";
}

NOT_USE_MESSAGE

int main()
{
	char a = 6, b = 7, c = 8;
	char *p_start;

	p_start = &c;
	if (&b < p_start) p_start = &b;
	if (&a < p_start) p_start = &a;

	SelectFontObject("consolas", 18);
	SetTextColor(RGB(0, 100, 255));
	printf(10, 10, "a의 주소: %p, b의 주소: %p, c의 주소: %p", &a, &b, &c);

	SelectPenObject(RGB(0, 0, 128));
	SetTextColor(RGB(0, 0, 255));
	
	for (int i = 0, count = 0; i < MAX_COUNT; ++i)
	{
		if ((p_start + i) == &a ||
			(p_start + i) == &b || (p_start + i) == &c)
		{
			SelectBrushObject(RGB(100, 255, 255));
			Rectangle(10 + i * 22, 50, MAX_COUNT + i * 22, 70);
			printf(15 + i * 22, 52, "%d", *(p_start + i));
			Line(20 + i * 22, 72, 20 + i * 22, 160 - count * 20);
			printf(17 + i * 22, 163 - count * 20, "%p", p_start + i);
			++count;
		}
		else
		{
			SelectBrushObject(RGB(228, 255, 255));
			Rectangle(10 + i * 22, 50, MAX_COUNT + i * 22, 70);
		}
	}

	ShowDisplay();
	return 0;
}

#include "pch.h"
#define _USE_INIT_WINDOW_
#include "tipsware.h"

#define MAX_COUNT	30

void InitWindow()
{
	gp_window_title = "EW32 - Tut04";
}

NOT_USE_MESSAGE

int main()
{
	char a = 6, b = 7, c = 8;
	char *p_start;

	p_start = &c;
	if (&b < p_start) p_start = &b;
	if (&a < p_start) p_start = &a;

	SelectFontObject("consolas", 18);
	SetTextColor(RGB(0, 100, 255));
	printf(10, 10, "a의 주소: %p, b의 주소: %p, c의 주소: %p", &a, &b, &c);

	SelectPenObject(RGB(0, 0, 128));
	SetTextColor(RGB(0, 0, 255));

	for (int i = 0, count = 0; i < 660; i+=22)
	{
		if (p_start == &a || p_start== &b || p_start == &c)
		{
			SelectBrushObject(RGB(100, 255, 255));
			Rectangle(10 + i, 50, MAX_COUNT + i, 70);
			printf(15 + i, 52, "%d", *p_start);
			Line(20 + i, 72, 20 + i, 160 - count);
			printf(17 + i, 163 - count, "%p", p_start);
			count+=20;
		}
		else
		{
			SelectBrushObject(RGB(228, 255, 255));
			Rectangle(10 + i, 50, MAX_COUNT + i, 70);
		}
		++p_start;
	}

	ShowDisplay();
	return 0;
}











