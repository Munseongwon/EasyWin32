#include "pch.h"				// 컴파일 속도 향상
#define _USE_INIT_WINDOW_	// 사용자 윈도우 전역 속성 초기화 함수 직접 구현하도록 지정
#include "tipsware.h"			// EasyWin32 사용

// 사용자 윈도우 전역 속성 초기화 함수
void InitWindow()
{
	// 창 제목 설정
	gp_window_title = "문자열 출력하기";
}

// 이 프로그램은 어떠한 메시지도 사용하지 않음
NOT_USE_MESSAGE

int main()
{
	char a = 1, b = 2, c = 3;
	printf(10, 10, RGB(0, 128, 0), "a: %hhd, b: %hhd, c:%hhd", a, b, c);
	
	printf(10, 50, RGB(0, 100, 255), "a' addr: %p", &a);
	printf(10, 70, "b' addr: %p", &b);
	printf(10, 90, "c' addr: %p", &c);
	
	int a_b = &a - &b;
	int b_c = &b - &c;
	printf(10, 130, RGB(0, 0, 128), "a_b: %d, b_c: %d", a_b, b_c);
	*(&a - a_b) = 10;
	printf(10, 170, RGB(128, 0, 255), "a: %hhd, b: %hhd, c: %hhd", a, b, c);

	// 정보를 윈도우에 출력
	ShowDisplay();
	return 0;
}