#include "pch.h"
#define _USE_INIT_WINDOW_
#include "tipsware.h"

#define MAX_X_COUNT	30

void InitWindow()
{
	gp_window_title = "배열과 포인터의 관계";
}

NOT_USE_MESSAGE

int main()
{
	int data[5] = {1,2,3,4,5};
	char *p_start = (char *)data;
	
	SelectFontObject("굴림", 12);
	SetTextColor(RGB(0, 100, 255));
	
	printf(10, 10, "data 배열의 시작 주소: %p, data[0] 항목의 시작 주소: %p", data, &data[0]);
	
	SelectPenObject(RGB(0, 0, 128));
	SetTextColor(RGB(0, 0, 255));
	
	for (int i = 0, count = 0; i < 660; i += 22)
	{
		if(((int *)p_start - data) < 5)
		{
			SelectBrushObject(RGB(100, 255, 255));
			Rectangle(10 + i, 50, 30 + i, 70);
			printf(17 + i, 55, "%d", *p_start);
			Line(20 + i, 72, 20 + i, 480 - count);
			printf(17 + i, 483 - count, "%p", p_start);
			count += 20;
		}
		else
		{
			SelectBrushObject(RGB(228, 228, 255));
			Rectangle(10 + i, 50, 30 + i, 70);
		}
		++p_start;
	}
	ShowDisplay();
	return 0;
}