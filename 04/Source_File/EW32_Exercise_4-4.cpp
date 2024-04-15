#include "pch.h"
#define _USE_INIT_WINDOW_
#include "tipsware.h"

#define WIN_WIDTH	500
#define WIN_HEIGHT	200

enum CtrlBtnId
{
	IDC_L_MOVE = 1000,
	IDC_R_MOVE,
	IDC_PLUS_VAL,
	IDC_MINUS_VAL,
	IDC_STATE
};

// bit pattern test variable
unsigned char g_data = 0x00;
// 0: unsigned 1: signed
unsigned char g_sign_flag = 0;

void InitWindow()
{
	gp_window_title = "Shift && Bit Operator";
}

void ShowBitPattern(int a_x, int a_y, unsigned char a_data)
{
	Clear();

	if (g_sign_flag) {
		// Set TextColor
		SetTextColor(RGB(0, 200, 0));
		// State -> signed
		printf(a_x, a_y - 25, "부호 처리 상태(signed mode)");
	}
	else {
		// Set TextColor
		SetTextColor(RGB(168, 168, 168));
		// State -> unsigned
		printf(a_x, a_y - 25, "부호 무시 상태(unsigned mode)");
	}

	// Textcolor
	SetTextColor(RGB(0, 0, 255));
	// INT -> OCT
	printf(a_x, a_y + 30, "Value: 0x%02hhX (signed: %hhd, unsigned: %hhu)", a_data, a_data, a_data);

	// Text Color
	SetTextColor(RGB(0, 255, 255));
	// Line Color
	SelectPenObject(RGB(0, 0, 192));
	// Background color
	SelectBrushObject(RGB(0, 0, 64));

	// Output from MSB(7bit, 6bit, 5bit..)to LSB following
	for (int i = 140; i >= 0; i -= 20) {
		// Draw Bit in Rectangle
		Rectangle(a_x + i, a_y, (a_x + 20) + i, a_y + 24);
		// result -> 1 '1', result -> 0 '0'
		printf(a_x + i + 7, a_y + 5, "%d", a_data & 0x01);
		a_data >>= 1;
	}

	// represents display screen
	ShowDisplay();
}

void OnLeftBtnDown(int a_mixed_key, POINT a_pos)
{
	unsigned int x = ((unsigned int)a_pos.x - 30) / 20;
	unsigned int y = ((unsigned int)a_pos.y - 30) / 20;

	if (x < 8 && !y) {
		// consist of result that choose number bit
		// bit: 1->0, 0->1
		g_data ^= 0x80 >> x;
		// Output bit result
		ShowBitPattern(30, 30, g_data);
	}
}

void OnCommand(INT32 a_ctrl_id, INT32 a_notify_code, void* ap_ctrl)
{
	switch (a_ctrl_id)
	{
	case IDC_L_MOVE:
	{
		g_data <<= 1;
		ShowBitPattern(30, 30, g_data);
	}
	break;
	case IDC_R_MOVE:
	{
		if(g_sign_flag) g_data = (char)g_data >> 1;
		else g_data >>= 1;
		ShowBitPattern(30, 30, g_data);
	}	
	break;
	case IDC_PLUS_VAL:
	{
		++g_data;
		ShowBitPattern(30, 30, g_data);
	}
	break;
	case IDC_MINUS_VAL:
	{
		--g_data;
		ShowBitPattern(30, 30, g_data);
	}
	break;
	case IDC_STATE:
	{
		g_sign_flag = !g_sign_flag;
		ShowBitPattern(30, 30, g_data);
	}
	break;
	default:
	break;
	}
}

MOUSE_CMD_MESSAGE(OnLeftBtnDown, NULL, NULL, OnCommand)

int main()
{
	// set the window width, height
	ChangeWorkSize(WIN_WIDTH, WIN_HEIGHT);
	// output the bit value
	ShowBitPattern(30, 30, g_data);
	// initalize button to move bit at left or right 
	CreateButton("Move To Left (<<)", 30, 90, 118, 28, IDC_L_MOVE);
	CreateButton("Move To Right(>>)", 150, 90, 118, 28, IDC_R_MOVE);
	
	// initalize button to Set Value plus 1 or minus 1
	CreateButton("Plus 1", 30, 125, 118, 28, IDC_PLUS_VAL);
	CreateButton("Minus 1", 150, 125, 118, 28, IDC_MINUS_VAL);

	CreateButton("State Toggle", 30, 160, 118, 28, IDC_STATE);
	// finish the program
	return 0;
}