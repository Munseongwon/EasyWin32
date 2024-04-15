#include "pch.h"
#define _USE_INIT_WINDOW_
#include "tipsware.h"

typedef struct AppData
{
	char g_is_clicked;
}AD;

void InitWindow()
{
	gp_window_title = "원 모양의 선 그리기";
}

void OnMouseLeftDown(int a_mixed_key, POINT a_pos)
{
	/*if (a_mixed_key & MK_CONTROL) {
		Rectangle(a_pos.x - 10, a_pos.y - 10, a_pos.x + 10, a_pos.y + 10);
	}
	else {
		Ellipse(a_pos.x - 10, a_pos.y - 10, a_pos.x + 10, a_pos.y + 10);
	}
	ShowDisplay();*/

	AD *p_data = (AD *)GetAppData();
	p_data->g_is_clicked = 1;
}

void OnMouseLeftUp(int a_mixed_key, POINT a_pos)
{
	AD *p_data = (AD *)GetAppData();
	p_data->g_is_clicked = 0;
}

void OnMouseMove(int a_mixed_key, POINT a_pos)
{
	AD *p_data = (AD *)GetAppData();
	if (p_data->g_is_clicked) {
		Ellipse(a_pos.x - 10, a_pos.y - 10, a_pos.x + 10, a_pos.y + 10);
		ShowDisplay();
	}
}

MOUSE_MESSAGE(OnMouseLeftDown, OnMouseLeftUp, OnMouseMove)

int main()
{
	AD data = { 0, };
	SetAppData(&data, sizeof(AD));
	SelectBrushObject(RGB(0, 0, 255));
	SelectPenObject(RGB(0, 255, 255), 3);
	return 0;
}