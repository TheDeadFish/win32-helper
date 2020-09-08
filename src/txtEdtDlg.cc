#include "stdshit.h"
#include "../bin/win32hlp.h"

static
WINAPI void onSize(HWND hwnd)
{
	RECT rc; GetClientRect(hwnd, &rc);
	HWND hEdit = GetDlgItem(hwnd, 100);
	MoveWindow(hEdit, 0, 0, 
		rc.right, rc.bottom, TRUE);
}

static
LRESULT CALLBACK wndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	GET_WND_CONTEXT(HWND)
	
	WNDMSG_SWITCH(
		ON_MESSAGE(WM_CREATE, if(This) *This = hwnd)
		ON_MESSAGE(WM_DESTROY, DestroyNotify(hwnd);
			if(This) *This = NULL)
		ON_MESSAGE(WM_SIZE, onSize(hwnd))
	,)
}

WINAPI HWND txtEdtDlg_create(HWND* pHwnd, HWND hParent, LPCSTR title, int x, int y, int w, int h, DWORD flags)
{
	DWORD style = WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE | ES_READONLY;

	HWND hwnd = stdClass_create(widen(title), WS_OVERLAPPEDWINDOW|WS_VISIBLE,
		0, x, y, w, h, hParent, 0, wndProc, pHwnd);
	CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"", 
		style, 0, 0, 0, 0, hwnd, (HMENU)100, NULL, NULL);
	onSize(hwnd); return hwnd;
}

WINAPI void txtEdtDlg_setText(HWND hwnd, LPCSTR str)
{
	SetDlgItemTextW(hwnd, 100, 
		crlf_widen(str));
}

WINAPI char* txtEdtDlg_getText(HWND hwnd)
{
	return getDlgItemText(hwnd, 100);
}

