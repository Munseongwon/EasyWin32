#include "pch.h"					// 컴파일 속도 향상
#include <time.h>					// time 함수 사용
#define _USE_INIT_WINDOW_			// 사용자 윈도우 전역 속성 초기화 함수 직접 지정
#include "tipsware.h"				// EasyWin32 사용

#define DISPLAY_CX			600		// 출력할 영역의 폭
#define DISPLAY_CY			600		// 출력할 영역의 높이
#define MAX_ELLIPSE_COUNT	50		// 생성할 타원의 수
#define MAX_RADIUS			30		// 원의 반지름
#define X_COUNT				(DISPLAY_CX/(MAX_RADIUS*2))
#define Y_COUNT				(DISPLAY_CY/(MAX_RADIUS*2))

#define WIN_WIDTH			600		// 클라이언트 영역 폭
#define WIN_HEIGHT			600		// 클라이언트 영역 높이

// 50개의 타원 정보를 저장할 배열 변수
int g_pos_x_list[MAX_ELLIPSE_COUNT];		// 타원의 중심 x좌표
int g_pos_y_list[MAX_ELLIPSE_COUNT];		// 타원의 중심 y좌표
int g_radius_list[MAX_ELLIPSE_COUNT];		// 타원의 반지름
COLORREF g_color_list[MAX_ELLIPSE_COUNT];	// 타원의 색상

// 해당 칸에 원이 있는 지 여부를 기억하는 변수 (0-> 원x, 1->원o)
char g_grid_state[Y_COUNT][X_COUNT];

// 사용자 윈도우 전역 속성 초기화 함수
void InitWindow()
{
	// 창 제목 설정
	gp_window_title = "랜덤하게 원 출력하기";
}

// 타원 데이터 생성하는 함수
void CreateEllipseData(int a_index)
{
	// 타원의 x,y좌표를 랜덤으로 생성하는 변수 선언
	int x, y;
	// 중심점을 생성, 이 중심점이 다른 원과 겹쳐지면
	// 겹치지 않을 때까지 반복해서 생성
	do {
		x = rand() % X_COUNT;
		y = rand() % Y_COUNT;
	} while (g_grid_state[y][x]);

	// 현재 타원이 x, y 위치의 칸을 점유함
	g_grid_state[y][x] = 1;
	// 반지름
	g_radius_list[a_index] = rand() % (MAX_RADIUS - 5) + 5;
	// x좌표
	g_pos_x_list[a_index] = x * (MAX_RADIUS * 2) + g_radius_list[a_index];
	// y좌표
	g_pos_y_list[a_index] = y * (MAX_RADIUS * 2) + g_radius_list[a_index];
	// 색상
	g_color_list[a_index] = RGB(rand() % 256, rand() % 256, rand() % 256); 
}

// 타원의 반지름을 1줄여서 출력하는 함수
TIMER ShowEllipse(NOT_USE_TIMER_DATA)
{
	Clear(); // 윈도우에 그려진 그림 모두 지움
	int x, y;
	for (int i = 0; i < MAX_ELLIPSE_COUNT; ++i) {
		--g_radius_list[i]; // 반지름의 길이 1 줄임
		// 반지름이 0이면 새로운 타원 생성
		if (0 == g_radius_list[i]) {
			x = g_pos_x_list[i] / (MAX_RADIUS * 2);
			y = g_pos_y_list[i] / (MAX_RADIUS * 2);
			g_grid_state[y][x] = 0;
			CreateEllipseData(i);
		} 
		// 펜 색상 지정
		ChangePenColor(g_color_list[i]);
		// 브러시 색상 지정
		ChangeBrushColor(g_color_list[i]);
		// 타원 출력
		Ellipse(g_pos_x_list[i] - g_radius_list[i], g_pos_y_list[i] - g_radius_list[i], 
			g_pos_x_list[i] + g_radius_list[i], g_pos_y_list[i] + g_radius_list[i]);
	}
	// 정보를 윈도우에 출력
	ShowDisplay();
}

// 해당 프로그램은 어떠한 메시지도 사용하지 않음
NOT_USE_MESSAGE

// 프로그램 실행하는 메인 함수
int main()
{
	// 작업 영역 설정(600 * 600)
	ChangeWorkSize(600, 600);
	// 색상을 단순하게 지정하는 방식으로 변경
	SetSimpleColorMode();
	// 난수 기준값을 지정
	srand((UINT32)time(NULL));
	// MAX_ELLIPSE_COUNT 개의 타원을 임의의 위치, 크기, 색상 지정
	for (int i = 0; i < MAX_ELLIPSE_COUNT; ++i) CreateEllipseData(i);
	// 0.1초마다 ShowEllipse 함수 호출하는 타이머 생성
	SetTimer(1, 100, ShowEllipse);
	// 닫힘 버튼 클릭 시 프로그램 종료
	return 0;
}