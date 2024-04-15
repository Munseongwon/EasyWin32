#include "pch.h"
#include <stdio.h>
#define _USE_INIT_WINDOW_
#include "tipsware.h"

#define WIN_WIDTH	540
#define WIN_HEIGHT	200
#define WIN_COLOR	RGB(72, 87, 114)

enum CtrlTypeId
{
	IDC_LIST = 1000,
	IDC_NOTIFY_CODE = 1000,
	IDC_EDIT,
	IDC_SHOW,
	IDC_RESET
};

typedef struct AppData
{
	void *p_list_box;
	void *p_edit;
}AD;

void InitWindow()
{
	gp_window_title = "파일 리스트 및 목록 탐색하기";
}

// 지정된 경로에 있는 디렉토리 혹은 파일 이름을 리스트 박스에 보여주는 함수
void ShowItemInDirectory()
{
	AD *p_app = (AD *)GetAppData();
	p_app->p_list_box = FindControl(IDC_LIST);
	p_app->p_edit = FindControl(IDC_EDIT);
	char str[MAX_PATH], name[MAX_PATH];
	
	GetCtrlName(p_app->p_edit, str, MAX_PATH);
	ListBox_ResetContent(p_app->p_list_box);

	WIN32_FIND_DATA file_data;
	HANDLE h_find = FindFirstFile(str, &file_data);
	if (INVALID_HANDLE_VALUE != h_find) {
		do
		{
			// 디렉토리: 이름, 1로, 파일: 0으로 설정
			if (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				// "." 이름을 가진 항목을 목록에 추가하지 않음
				if (file_data.cFileName[0] != '.' || file_data.cFileName[1]) {
					// 디렉터리 -> 항목 이름을 '[이름]' 형식으로 추가
					sprintf_s(name, MAX_PATH, "[%s]", file_data.cFileName);
					// 검색된 파일 또는 파일 이름을 리스트 박스에 추가
					ListBox_InsertString(p_app->p_list_box, -1, name);
				}
			}
			else ListBox_InsertString(p_app->p_list_box, -1, file_data.cFileName);
		} while (FindNextFile(h_find, &file_data)); // 다음 항목 탐색
		FindClose(h_find); // 파일 검색과 관련된 정보를 닫음
	}
}

// 리스트 박스에서 디렉토리 더블 클릭, 해당 디렉토리로 이동하는 함수
void ChangeDirectory()
{
	AD *p_app = (AD *)GetAppData();
	p_app->p_list_box = FindControl(IDC_LIST);
	p_app->p_edit = FindControl(IDC_EDIT);
	char path[MAX_PATH], name[MAX_PATH];

	// 에디트 컨트롤에 입력된 문자열을 path 변수에 복사
	GetCtrlName(p_app->p_edit, path, MAX_PATH);
	// 에디트 컨트롤에 입력된 문자열의 길이를 얻음
	int path_len = Edit_GetLength(p_app->p_edit);
	// 리스트 박스에서 사용자가 더블 클릭한 항목의 위치를 얻음
	int index = ListBox_GetCurSel(p_app->p_list_box);
	// 리스트 박스에서 사용자가 더블 클릭한 항목의 문자열을 얻음
	ListBox_GetText(p_app->p_list_box, index, name, MAX_PATH);
	// 디렉토리인 경우에만 처리
	if (name[0] == '[') {
		// '[' 문자 제외하고 탐색	
		char *p = name + 1;
		// 디렉토리 이름의 끝 위치 탐색
		while (*p != ']') ++p;
		// ']' 문자 제거
		*p = 0;
		// 디렉토리 이름의 길이를 구함
		int name_len = p - (name + 1);
		// 경로의 끝 위치에서 앞으로 이동하면서 경로 탐색
		p = path + path_len - 1;
		// 필터 제거를 위해 필터 앞에 있는 '\' 문자를 찾음
		while (*p != '\\') --p;
		// 부모 디렉토리 이동
		if (name_len == 2 && !memcmp(name + 1, "..", 2)) {
			--p;
			while (*p != '\\') --p;
			*++p = 0;
			strcat_s(p, MAX_PATH - (p - path), "*.*");
		}
		// 자식 디렉토리로 이동
		else {
			*++p = 0;
			strcat_s(p, MAX_PATH - (p - path), name + 1);
			strcat_s(p, MAX_PATH - (p - path), "\\*.*");
		}
		// 변경된 경로를 에디트 컨트롤에 다시 출력
		SetCtrlName(p_app->p_edit, path);
		// 지정된 경로에 있는 항목들을 리스트 박스에 출력
		ShowItemInDirectory();
	}
}

// 컨트롤 조작 함수
void OnCommand(INT32 a_ctrl_id, INT32 a_notify_code, void *ap_ctrl)
{
	AD *p_app = (AD *)GetAppData();
	if (a_ctrl_id == IDC_SHOW || (a_ctrl_id == IDC_EDIT && a_notify_code == IDC_NOTIFY_CODE)) {
		ShowItemInDirectory();
	}
	else if (a_ctrl_id == IDC_LIST) {
		if (a_notify_code == LBN_DBLCLK) ChangeDirectory();
	}
	else if (a_ctrl_id == IDC_RESET) {
		ListBox_ResetContent(p_app->p_list_box);
	}
}

// 컨트롤 조작하는 함수 등록하는 매크로 함수
CMD_MESSAGE(OnCommand)

// 프로그램 실행하는 메인 함수
int main()
{
	ChangeWorkSize(WIN_WIDTH, WIN_HEIGHT);
	Clear(0, WIN_COLOR);
	
	AD p_data = { 0, };
	SetAppData(&p_data, sizeof(AD));

	LONG style = GetWindowLongA(gh_main_wnd, GWL_STYLE);
	SetWindowLongA(gh_main_wnd, GWL_STYLE, style & ~(WS_THICKFRAME | WS_MAXIMIZEBOX));
	
	p_data.p_list_box = CreateListBox(10, 10, 515, 150, IDC_LIST);
	p_data.p_edit = CreateEdit(10, 167, 406, 24, IDC_EDIT, 0);
	EnableEnterKey(p_data.p_edit);
	
	char path[MAX_PATH];
	int len = GetCurrentDirectory(MAX_PATH, path);
	memcpy(path + len, "\\*.*", 5);
	SetCtrlName(p_data.p_edit, path);

	CreateButton("보기", 420, 164, 50, 28, IDC_SHOW);
	CreateButton("리셋", 475, 164, 50, 28, IDC_RESET);

	ShowDisplay();
	return 0;
}