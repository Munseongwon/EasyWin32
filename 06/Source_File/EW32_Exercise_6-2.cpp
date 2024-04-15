#include "pch.h"
#define _USE_INIT_WINDOW_
#include "tipsware.h"

#define WIN_WIDTH	590
#define WIN_HEIGHT	200
#define WIN_COLOR	RGB(72, 87, 114)

enum CtrlTypeId
{
	IDC_LIST = 1000,
	IDC_NOTIFY_CODE = 1000,
	IDC_EDIT,
	IDC_ADD,
	IDC_DEL,
	IDC_RESET
};

void InitWindow()
{
	gp_window_title = "컨트롤 실습";
}

void OnCommand(INT32 a_ctrl_id, INT32 a_notify_code, void *ap_ctrl)
{
	if (a_ctrl_id == IDC_ADD || (a_ctrl_id == IDC_EDIT && a_notify_code == IDC_NOTIFY_CODE)) {
		void *p_edit = FindControl(IDC_EDIT);
		char str[64];
		GetCtrlName(p_edit, str, 64);
		SetCtrlName(p_edit, "");

		void *p_list_box = FindControl(IDC_LIST);
		ListBox_InsertString(p_list_box, -1, str);
	}
	else if (a_ctrl_id == IDC_DEL){
		void* p_list_box = FindControl(IDC_LIST);
		ListBox_DeleteString(p_list_box, 2);
	}
	else if (a_ctrl_id == IDC_RESET) {
		ListBox_ResetContent(FindControl(IDC_LIST));
	}
}

CMD_MESSAGE(OnCommand)

int main()
{
	ChangeWorkSize(WIN_WIDTH, WIN_HEIGHT);
	Clear(0, WIN_COLOR);
	
	CreateListBox(10, 10, 570, 150, IDC_LIST);
	
	void *p_edit = CreateEdit(10, 167, 406, 24, IDC_EDIT, 0);
	EnableEnterKey(p_edit);

	CreateButton("추가", 420, 164, 50, 28, IDC_ADD);
	CreateButton("삭제", 475, 164, 50, 28, IDC_DEL);
	CreateButton("리셋", 530, 164, 50, 28, IDC_RESET);

	ShowDisplay();
	return 0;
}