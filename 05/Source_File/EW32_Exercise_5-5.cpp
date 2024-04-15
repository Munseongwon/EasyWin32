#include "pch.h"					// 컴파일 속도 향상
#include <time.h>					// time 함수 사용
#include <math.h>					// sqrt, pow 함수 사용
#define _USE_INIT_WINDOW_			// 사용자 윈도우 전역 속성 초기화 함수 직접 지정
#include "tipsware.h"				// EasyWin32 사용

#define MAX_ELLIPSE_COUNT	50		// 생성할 타원의 수
#define MAX_RADIUS			30		// 원의 반지름
#define DISPLAY_CX			600		// 출력할 영역의 폭
#define DISPLAY_CY			600		// 출력할 영역의 높이

#define WIN_WIDTH			600		// 작업 영역의 폭
#define WIN_HEIGHT			600		// 작업 영역의 높이

// 50개의 타원 정보를 저장할 배열 변수
int g_pos_x_list[MAX_ELLIPSE_COUNT];		// 타원의 중심 x좌표
int g_pos_y_list[MAX_ELLIPSE_COUNT];		// 타원의 중심 y좌표
int g_radius_list[MAX_ELLIPSE_COUNT];		// 타원의 반지름
COLORREF g_color_list[MAX_ELLIPSE_COUNT];	// 타원의 색상

// 사용자 윈도우 전역 속성 초기화 함수
void InitWindow()
{
	// 창 제목 설정
	gp_window_title = "랜덤하게 원 출력하기";
}

// 이미 존재하는 원과 생성된 원이 겹쳐지는 지 체크하는 함수
int IsOverlaped(int a_x, int a_y, int a_r)
{
	// 두 원의 중심 점 간의 거리 변수 선언
	int distance;
	for (int i = 0; i < MAX_ELLIPSE_COUNT; ++i) {
		// 두 원의 중심 점 간의 거리를 구함
		distance = (int)sqrt(pow(g_pos_x_list[i] - a_x, 2) + pow(g_pos_y_list[i] - a_y, 2));
		// 중심 간의 거리가 반지름을 합산한 것보다 작으면 두 원은 겹쳐짐
		if (distance < (g_radius_list[i] + a_r)) return 1;
	}
	return 0;	// 겹쳐진 원이 없음
}

// 타원 데이터 생성하는 함수
void CreateEllipseData(int a_index)
{
	//g_pos_x_list[a_index] = rand() % WIN_WIDTH;	// x 좌표(0 ~ 599)
	//g_pos_y_list[a_index] = rand() % WIN_HEIGHT;   // y 좌표(0 ~ 599)
	//g_radius_list[a_index] = rand() % (MAX_ELLIPSE_COUNT / 10) + 10; // 반지름(10~29)
	//g_color_list[a_index] = RGB(rand() % 256, rand() % 256, rand() % 256); // 색상
	
	// 타원의 x,y좌표, 반지름을 랜덤으로 생성하는 변수 선언
	int x, y, r = rand() % (MAX_RADIUS - 10) + 10;
	// 중심점을 생성, 이 중심점이 다른 원과 겹쳐지면
	// 겹치지 않을 때까지 반복해서 생성
	do {
		x = rand() % DISPLAY_CX;
		y = rand() % DISPLAY_CY;
	} while (IsOverlaped(x, y, r));

	g_pos_x_list[a_index] = x;	// x좌표
	g_pos_y_list[a_index] = y;	// y좌표
	g_radius_list[a_index] = r;	// 반지름
	g_color_list[a_index] = RGB(rand() % 256, rand() % 256, rand() % 256); // 색상
}

// 타원의 반지름을 1줄여서 출력하는 함수
TIMER ShowEllipse(NOT_USE_TIMER_DATA)
{
	Clear(); // 윈도우에 그려진 그림 모두 지움
	for (int i = 0; i < MAX_ELLIPSE_COUNT; ++i) {
		--g_radius_list[i]; // 반지름의 길이 1 줄임
		// 반지름이 0이면 새로운 타원 생성
		if (0 == g_radius_list[i]) CreateEllipseData(i);
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
	ChangeWorkSize(WIN_WIDTH, WIN_HEIGHT);
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