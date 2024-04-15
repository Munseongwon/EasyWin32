#include "pch.h"
#define _USE_INIT_WINDOW_
#include "tipsware.h"

#define MAX_X_COUNT		15
#define MAX_Y_COUNT		15
#define CX				30
#define CY				30

typedef struct AppData
{
	UINT8 g_is_onoff[MAX_X_COUNT][MAX_Y_COUNT];
}AD;


void InitWindow()
{
	gp_window_title = "2차원 격자 좌표 연습";
}

void OnLeftBtnDown(int a_mixed_key, POINT a_pos)
{
	AD *p_data = (AD *)GetAppData();
	unsigned int x = a_pos.x / CX;
	unsigned int y = a_pos.y / CY;

	if (x < MAX_X_COUNT && y < MAX_Y_COUNT)
	{
		p_data->g_is_onoff[y][x] += 128;
		Rectangle(x * CX, y * CY, (x+1)*CX+1, (y+1)*CY+1,
			RGB(0, 64, 0), RGB(0, p_data->g_is_onoff[y][x], 0));
		ShowDisplay();
	}
}

MOUSE_MESSAGE(OnLeftBtnDown, NULL, NULL)

int main()
{
	AD p_data = { {127,127} };
	memset(p_data.g_is_onoff, 127, sizeof(p_data.g_is_onoff));
	SetAppData(&p_data, sizeof(p_data));
	
	for (int y = 0; y < MAX_Y_COUNT; ++y) {
		for (int x = 0; x < MAX_X_COUNT; ++x) 
			Rectangle(x * CX, y * CY, (x + 1) * CX + 1, (y + 1) * CY + 1,
			RGB(0, 64, 0), RGB(0, 127, 0));
	}
	
	ShowDisplay();
	return 0;
}