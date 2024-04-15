#include "pch.h"
#define _USE_INIT_WINDOW_
#include "tipsware.h"

#define MAX_X_COUNT	19
#define MAX_Y_COUNT	19
#define CX			30
#define CY			30

typedef struct AppData
{
	unsigned char g_state[MAX_Y_COUNT][MAX_X_COUNT];
	unsigned char g_step = 0;
}AD;

void InitWindow()
{
	gp_window_title = "격자 연습(오목 구성하기)";
}

void OnLeftBtnDown(int a_mixed_key, POINT a_pos)
{
	AD *p_app = (AD *)GetAppData();
	unsigned int x = a_pos.x / CX, y = a_pos.y / CY;
	if (x < MAX_X_COUNT && y < MAX_Y_COUNT && !p_app->g_state[y][x]) {
		p_app->g_state[y][x] = p_app->g_step + 1;
		Ellipse(x * CX, y * CY, (x + 1) * CX + 1, (y + 1) * CY + 1,
			0, 0x00FFFFFF * p_app->g_step);
		p_app->g_step = !p_app->g_step;
		ShowDisplay();
	}
}

MOUSE_MESSAGE(OnLeftBtnDown, NULL, NULL)

int main()
{
	AD p_data = { {0,0}, 0 };
	SetAppData(&p_data, sizeof(AD));
	// 오목판 그림, 오목돌의 개수 19개 맞게 놓을 수 있도록 설정
	for (int y = 0; y < MAX_Y_COUNT - 1; ++y) {
		for (int x = 0; x < MAX_X_COUNT - 1; ++x) {
			Rectangle(20 + x * CX, 15 + y * CY, 20 + (x + 1) * CX + 1, 15 + (y + 1) * CY + 1,
				RGB(0, 0, 0), RGB(229, 181, 82));
		}
	}
	// 정보를 윈도우에 출력
	ShowDisplay();
	return 0;
}
