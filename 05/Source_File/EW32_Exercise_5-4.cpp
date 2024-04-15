#include "pch.h"					// 컴파일 속도 향상
#include <time.h>					// time 함수 사용
#define _USE_INIT_WINDOW_			// 사용자 윈도우 전역 속성 초기화 함수 직접 지정
#include "tipsware.h"				// EasyWin32 사용

#define MAX_ELLIPSE_COUNT	200		// 원의 최댓값
#define WIN_WIDTH			600
#define WIN_HEIGHT			600

// 50개의 타원 정보를 저장할 배열 변수
int g_pos_x_list[MAX_ELLIPSE_COUNT];		// 타원의 중심 x좌표
int g_pos_y_list[MAX_ELLIPSE_COUNT];		// 타원의 중심 y좌표
int g_radius_list[MAX_ELLIPSE_COUNT];		// 타원의 반지름
COLORREF g_color_list[MAX_ELLIPSE_COUNT];	// 타원의 색상

void InitWindow()
{
	gp_window_title = "랜덤하게 원 출력하기";
}

void CreateEllipseData(int a_index)
{
	g_pos_x_list[a_index] = rand() % WIN_WIDTH;	// x 좌표(0 ~ 599)
	g_pos_y_list[a_index] = rand() % WIN_HEIGHT;   // y 좌표(0 ~ 599)
	g_radius_list[a_index] = rand() % (MAX_ELLIPSE_COUNT / 10) + 10; // 반지름(10~29)
	g_color_list[a_index] = RGB(rand() % 256, rand() % 256, rand() % 256); // 색상
}

// 타원의 반지름을 1줄여서 출력하는 함수
TIMER ShowEllipse(NOT_USE_TIMER_DATA)
{
	Clear(); // 윈도우에 그려진 그림 모두 지움
	for (int i = 0; i < MAX_ELLIPSE_COUNT; ++i) {
		--g_radius_list[i]; // 반지름의 길이 1 줄임
		if (0 == g_radius_list[i]) CreateEllipseData(i);
		ChangePenColor(g_color_list[i]);
		ChangeBrushColor(g_color_list[i]);
		Ellipse(g_pos_x_list[i] - g_radius_list[i], g_pos_y_list[i] - g_radius_list[i], 
			g_pos_x_list[i] + g_radius_list[i], g_pos_y_list[i] + g_radius_list[i]);
	}
	ShowDisplay();
}

NOT_USE_MESSAGE

int main()
{
	ChangeWorkSize(WIN_WIDTH, WIN_HEIGHT);
	SetSimpleColorMode();
	
	srand((UINT32)time(NULL));
	
	for (int i = 0; i < MAX_ELLIPSE_COUNT; ++i) CreateEllipseData(i);
	
	SetTimer(1, 100, ShowEllipse);
	
	return 0;
}