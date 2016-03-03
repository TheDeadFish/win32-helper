// combobox - include lines
void WINAPI dlgCombo_addStr(HWND hwnd, DWORD ctrlId, 
	const char* const* strs, int count);
void WINAPI dlgCombo_addStr(HWND hwnd, DWORD ctrlId, const WCHAR* str);
int WINAPI dlgCombo_getSel(HWND hwnd, DWORD ctrlId);
void WINAPI dlgCombo_setSel(HWND hwnd, DWORD ctrlId, int sel);
void WINAPI dlgCombo_reset(HWND hwnd, DWORD ctrlId);

// combobox - source lines
void WINAPI dlgCombo_addStr(HWND hwnd, DWORD ctrlId, const char* const* strs, int count)
{	for(int i = 0; i < count; i++) { SendDlgItemMessageA(hwnd,
	ctrlId, CB_ADDSTRING, 0, (LPARAM)strs[i]); } }
void WINAPI dlgCombo_addStr(HWND hwnd, DWORD ctrlId, const WCHAR* str) {
	SendDlgItemMessage(hwnd, ctrlId, CB_ADDSTRING, 0, (LPARAM)str); }
int WINAPI dlgCombo_getSel(HWND hwnd, DWORD ctrlId) {
	SendDlgItemMessage(hwnd, ctrlId, CB_GETCURSEL, 0, 0); }
void WINAPI dlgCombo_setSel(HWND hwnd, DWORD ctrlId, int sel) {
	SendDlgItemMessage(hwnd, ctrlId, CB_SETCURSEL, sel, 0); }
void WINAPI dlgCombo_reset(HWND hwnd, DWORD ctrlId) {
	SendDlgItemMessage(hwnd, ctrlId, CB_RESETCONTENT, 0, 0); }
