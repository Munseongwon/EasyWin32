#include "pch.h"
#include <time.h>
#define _USE_INIT_WINDOW_
#include "tipsware.h"

#define DISPLAY_CX			600
#define DISPLAY_CY			600
#define MAX_ELLIPSE_COUNT	50
#define MAX_RADIUS			30
#define X_COUNT				(DISPLAY_CX/(MAX_RADIUS*2))
#define Y_COUNT				(DISPLAY_CY/(MAX_RADIUS*2))

typedef struct CircleData
{
	int x, y, r;
	COLORREF color;
}CD;

typedef struct AppData
{
	char g_grid_state[Y_COUNT][X_COUNT];
	CD g_circle[MAX_ELLIPSE_COUNT];
}AD;

void InitWindow()
{
	gp_window_title = "랜덤 원 그리기";
}

void CreateEllipseData(AD *p_app, CD *ap_data)
{
	int x, y;
	do {
		x = rand() % X_COUNT;
		y = rand() % Y_COUNT;
	} while (p_app->g_grid_state[y][x]);

	p_app->g_grid_state[y][x] = 1;

	ap_data->r = rand() % (MAX_RADIUS - 5) + 5;
	ap_data->x = x * (MAX_RADIUS * 2) + ap_data->r;
	ap_data->y = y * (MAX_RADIUS * 2) + ap_data->r;
	ap_data->color = RGB(rand() % 256, rand() % 256, rand() % 256);
}

TIMER ShowEllipse(NOT_USE_TIMER_DATA)
{
	Clear();
	AD *p_app = (AD *)GetAppData();

	int x, y;
	CD *p_start = p_app->g_circle, *p_limit = p_app->g_circle + MAX_ELLIPSE_COUNT;
	while (p_start < p_limit) {
		p_start->r--;
		if (p_start->r == 0) {
			x = p_start->x / (MAX_RADIUS * 2);
			y = p_start->y / (MAX_RADIUS * 2);
			p_app->g_grid_state[y][x] = 0;
			CreateEllipseData(p_app, p_start);
		}

		ChangePenColor(p_start->color);
		ChangeBrushColor(p_start->color);
		Ellipse(p_start->x - p_start->r, p_start->y - p_start->r, p_start->x + p_start->r, p_start->y + p_start->r);
		++p_start;
	}
	ShowDisplay();
}

NOT_USE_MESSAGE

int main()
{
	AD p_data;
	memset(&p_data, 0, sizeof(p_data));
	srand((UINT32)time(NULL));
	
	for (int i = 0; i < MAX_ELLIPSE_COUNT; ++i) CreateEllipseData(&p_data, p_data.g_circle + i);
	SetAppData(&p_data, sizeof(p_data));
	
	ChangeWorkSize(600, 600);
	SetSimpleColorMode();

	SetTimer(1, 100, ShowEllipse);
	return 0;
}