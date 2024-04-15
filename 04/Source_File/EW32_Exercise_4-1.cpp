#include "pch.h"
#define _USE_INIT_WINDOW_
#include "tipsware.h"

unsigned char g_data = 0x00;

void InitWindow()
{
	gp_window_title = "Shift && Bit Operator";
}

void ShowBitPattern(int a_x, int a_y, unsigned char a_data)
{
	Clear();
	SetTextColor(RGB(0, 255, 255));
	SelectPenObject(RGB(0, 0, 192));
	SelectBrushObject(RGB(0, 0, 64));

	// Output from MSB(7bit, 6bit, 5bit..)to LSB following
	for (char i = 0; i < 8; ++i) {
		Rectangle(a_x + i * 20, a_y, (a_x + 20) + 20 * i, a_y + 24);
		// result -> 1 '1', result -> 0 '0'
		if (a_data & (0x80 >> i)) printf(a_x + i * 20 + 7, a_y + 5, "1");
		else printf(a_x + i * 20 + 7, a_y + 5, "0");
	}

	// Textcolor
	SetTextColor(RGB(0, 0, 255));
	// INT -> OCT
	printf(a_x, a_y + 30, "값: 0x%02hhX", a_data);
	// represents display screen
	ShowDisplay();
}

void OnLeftBtnDown(int a_mixed_key, POINT a_pos)
{
	unsigned int x = ((unsigned int)a_pos.x - 30) / 20;
	unsigned int y = ((unsigned int)a_pos.y - 30) / 20;

	if (x < 8 && !y) {
		// consist of result that choose number bit
		unsigned char value = 0x80 >> x;
		// bit: 1->0, 0->1
		if (g_data & value) g_data &= ~value; // 0
		else g_data |= value; // 1
		// Output bit result
		ShowBitPattern(30, 30, g_data);
	}
}

MOUSE_MESSAGE(OnLeftBtnDown, NULL, NULL)

int main()
{
	ShowBitPattern(30, 30, g_data);
	return 0;
}