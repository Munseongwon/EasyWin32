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
	int data = 5;
	// 윈도우 배경색을 72,87,114로 설정
	Clear(0, RGB(72, 87, 114));
	// 앞으로 출력될 문자열은 분홍색을 사용하게 설정
	SetTextColor(RGB(230, 66, 234));
	// data 변수의 값을 10진 정숫값으로 화면에 출력
	printf(100, 50, "data : %d", data);
	printf(100, 70, "결과를 출력했습니다~");
	// 정보를 윈도우에 출력
	ShowDisplay();
	return 0;
}