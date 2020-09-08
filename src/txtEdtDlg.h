#pragma once

// creation api
WINAPI HWND txtEdtDlg_create(HWND* pHwnd, HWND hParent, LPCSTR title, int x, int y, int w, int h, DWORD flags=0);
static HWND txtEdtDlg_create(HWND* pHwnd, HWND hParent, LPCSTR title, int w, int h, DWORD flags=0) {
	return txtEdtDlg_create(pHwnd, hParent, title, CW_USEDEFAULT, CW_USEDEFAULT, w, h, flags); }
static HWND txtEdtDlg_create(HWND* pHwnd, HWND hParent, LPCSTR title, DWORD flags=0) {
	return txtEdtDlg_create(pHwnd, hParent, title, CW_USEDEFAULT, CW_USEDEFAULT, flags); }

// control api
WINAPI void txtEdtDlg_setText(HWND hwnd, LPCSTR);
WINAPI char* txtEdtDlg_getText(HWND hwnd);
