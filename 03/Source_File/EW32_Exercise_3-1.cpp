#include "pch.h"
#define _USE_INIT_WINDOW_
#include "tipsware.h"

// NOT_USE_MESSAGE

void InitWindow()
{
	gp_window_title = "사각형 및 원 그리기";
}

void OnMouseLeftDown(int a_mixed_key, POINT a_pos)
{
	if (a_mixed_key & MK_CONTROL) {
		Rectangle(a_pos.x - 10, a_pos.y - 10, a_pos.x + 10, a_pos.y + 10);
	}
	else {
		Ellipse(a_pos.x - 10, a_pos.y - 10, a_pos.x + 10, a_pos.y + 10);
	}
	ShowDisplay();
}

MOUSE_CMD_MESSAGE(OnMouseLeftDown, NULL, NULL, NULL)

int main()
{
	SelectBrushObject(RGB(0, 0, 200));
	SelectPenObject(RGB(0, 100, 200));
	return 0;
}