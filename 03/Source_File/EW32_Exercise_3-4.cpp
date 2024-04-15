#include "pch.h"
#define _USE_INIT_WINDOW_
#include "tipsware.h"

typedef struct AppData
{
	char g_is_onoff;
}AD;

void InitWindow()
{
	gp_window_title = "Tut03-04";
}

void OnMouseLeftDown(int a_mixed_key, POINT a_pos)
{
	AD *p_data = (AD *)GetAppData();
	if ((a_pos.x >= 100 && a_pos.x <= 200) && (a_pos.y >= 100 && a_pos.y <= 200)) {
		// p_data->g_is_onoff = !p_data->g_is_onoff;
		/*if (p_data->g_is_onoff) Rectangle(100, 100, 200, 200, RGB(0, 128, 0), RGB(0, 255, 0));
		else Rectangle(100, 100, 200, 200, RGB(0, 128, 0), RGB(0, 128, 0));*/
		
		p_data->g_is_onoff += 128;
		Rectangle(100, 100, 200, 200, RGB(0, 128, 0), RGB(0, p_data->g_is_onoff, 0));
		ShowDisplay();
	}
}

MOUSE_MESSAGE(OnMouseLeftDown, NULL, NULL)

int main()
{
	AD data = { 127, };
	SetAppData(&data, sizeof(AD));
	Rectangle(100, 100, 200, 200, RGB(0, 128, 0), RGB(0, 128, 0));
	ShowDisplay();
	return 0;
}