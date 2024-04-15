#include "pch.h"
#define _USE_INIT_WINDOW_
#include "tipsware.h"

#define MAX_X_COUNT	5

#define CX	30
#define CY	30

// 127: off, 255: on
// unsigned char g_is_onoff[MAX_X_COUNT] = {127,127,127,127,127};
unsigned char g_is_off = 0;

void InitWindow()
{
	gp_window_title = "Tut04 - 05";
}

//if (a_pos.y >= 0 && a_pos.y <= CY && a_pos.x >= 0) {
//	if (a_pos.x < CX) {
//		g_is_onoff_0 += 128;
//		Rectangle(0, 0, CX, CY, RGB(0, 64, 0), RGB(0, g_is_onoff_0, 0));
//	}
//	else if (a_pos.x < CX * 2) {
//		g_is_onoff_1 += 128;
//		Rectangle(CX, 0, CX * 2, CY, RGB(0, 64, 0), RGB(0, g_is_onoff_1, 0));
//	}
//	else if (a_pos.x < CX * 3) {
//		g_is_onoff_2 += 128;
//		Rectangle(CX * 2, 0, CX * 3, CY, RGB(0, 64, 0), RGB(0, g_is_onoff_2, 0));
//	}
//	else if (a_pos.x < CX * 4) {
//		g_is_onoff_3 += 128;
//		Rectangle(CX * 3, 0, CX * 4, CY, RGB(0, 64, 0), RGB(0, g_is_onoff_3, 0));
//	}
//	else if (a_pos.x < CX * 5) {
//		g_is_onoff_4 += 128;
//		Rectangle(CX * 4, 0, CX * 5, CY, RGB(0, 64, 0), RGB(0, g_is_onoff_4, 0));
//	}
//}

//if (y == 0) {
//	if (x == 0) {
//		g_is_onoff_0 += 128;
//		Rectangle(x * CX, 0, (x + 1) * CX, CY, RGB(0, 64, 0), RGB(0, g_is_onoff_0, 0));
//	}
//	else if (x == 1) {
//		g_is_onoff_1 += 128;
//		Rectangle(x * CX, 0, (x + 1) * CX, CY, RGB(0, 64, 0), RGB(0, g_is_onoff_1, 0));
//	}
//	else if (x == 2) {
//		g_is_onoff_2 += 128;
//		Rectangle(x * CX, 0, (x + 1) * CX, CY, RGB(0, 64, 0), RGB(0, g_is_onoff_2, 0));
//	}
//	else if (x == 3) {
//		g_is_onoff_3 += 128;
//		Rectangle(x * CX, 0, (x + 1) * CX, CY, RGB(0, 64, 0), RGB(0, g_is_onoff_3, 0));
//	}
//	else if (x == 4) {
//		g_is_onoff_4 += 128;
//		Rectangle(x * CX, 0, (x + 1) * CX, CY, RGB(0, 64, 0), RGB(0, g_is_onoff_4, 0));
//	}
//}

void OnLeftBtnDown(int a_mixed_key, POINT a_pos)
{
	unsigned int x = a_pos.x / CX;  // 0 1 2 3 4 
	unsigned int y = a_pos.y / CY;  // 0 1 2 3 4
	
	if (x < MAX_X_COUNT && !y)
	{
		/*g_is_onoff[x] += 128;
		Rectangle(x * CX, 0, (x + 1) * CX, CY, RGB(0, 64, 0), RGB(0, g_is_onoff[x], 0));*/
		
		unsigned char step = 0x32; // 유효비트: 0 ~ 4
		
		for (unsigned char i = 0; i < x; ++i) step /= 2;
		
		// 1->0, 0->1
		if ((g_is_off % step) / (step / 2)) {
			Rectangle(x * CX, 0, (x + 1) * CX, CY, RGB(0, 64, 0), RGB(0, 128, 0));
			g_is_off = g_is_off - step / 2;
		}
		else {
			Rectangle(x * CX, 0, (x + 1) * CX, CY, RGB(0, 64, 0), RGB(0, 255, 0));
			g_is_off = g_is_off + step / 2;
		}
		ShowDisplay();
	}
}

MOUSE_MESSAGE(OnLeftBtnDown, NULL, NULL)

int main()
{
	for (int i = 0; i < MAX_X_COUNT; ++i) {
		Rectangle(i * CX, 0, (i + 1) * CX, CY, RGB(0, 64, 0), RGB(0, 128, 0));
	}
	ShowDisplay();
	return 0;
}