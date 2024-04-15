#include "pch.h"
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
	IDC_BTN,
	IDC_DEL
};

void InitWindow()
{
	gp_window_title = "파일 및 디렉토리 이름 출력";
}

void OnCommand(INT32 a_ctrl_id, INT32 a_notify_code, void *ap_ctrl)
{
	if (a_ctrl_id == IDC_BTN || (a_ctrl_id == IDC_LIST && a_notify_code == IDC_NOTIFY_CODE)) {
		void *p_list_box = FindControl(IDC_LIST);
		void *p_edit = FindControl(IDC_EDIT);
		char str[MAX_PATH];

		GetCtrlName(p_edit, str, MAX_PATH);
		ListBox_ResetContent(p_list_box);

		WIN32_FIND_DATA file_data;
		HANDLE h_find = FindFirstFile(str, &file_data);
		if (INVALID_HANDLE_VALUE != h_find) {
			do {
				if (file_data.cFileName[0] != '.' || file_data.cFileName[1]) {
					ListBox_InsertString(p_list_box, -1, file_data.cFileName);
				}
			} while (FindNextFile(h_find, &file_data));
			FindClose(h_find);
		}
	}
	else if (a_ctrl_id == IDC_DEL) {
		ListBox_ResetContent(FindControl(IDC_LIST));
	}
}

CMD_MESSAGE(OnCommand)

int main()
{
	ChangeWorkSize(WIN_WIDTH, WIN_HEIGHT);
	Clear(0, WIN_COLOR);
	
	CreateListBox(10, 10, 515, 150, IDC_LIST);
	void *p_edit = CreateEdit(10, 167, 406, 24, IDC_EDIT, 0);
	EnableEnterKey(p_edit);

	char path[MAX_PATH];
	int len = GetCurrentDirectory(MAX_PATH, path);
	memcpy(path + len, "\\*.*", 5);
	SetCtrlName(p_edit, path);

	CreateButton("보기", 420, 164, 50, 28, IDC_BTN);
	CreateButton("리셋", 475, 164, 50, 28, IDC_DEL);
	ShowDisplay();
	return 0;
}