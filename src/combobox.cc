// combobox - include lines
void WINAPI dlgCombo_addStrs(HWND, DWORD, cch* const*, int);
int WINAPI dlgCombo_addStr(HWND, DWORD, cch*);
int WINAPI dlgCombo_addStr(HWND, DWORD, cch*, LPARAM);
int WINAPI dlgCombo_setData(HWND, DWORD, int, LPARAM);
LPARAM WINAPI dlgCombo_getData(HWND, DWORD, int);
int WINAPI dlgCombo_getSel(HWND, DWORD);
int WINAPI dlgCombo_setSel(HWND, DWORD, int);
int WINAPI dlgCombo_reset(HWND, DWORD);
cstr WINAPI dlgCombo_getText(HWND, DWORD, int);
int WINAPI dlgCombo_find(HWND, DWORD, cch*);
int WINAPI dlgCombo_selStr(HWND, DWORD, cch*);

// complex functions
LPARAM WINAPI dlgCombo_getData2(HWND h, DWORD c, int i);
int WINAPI dlgCombo_findData(HWND h, DWORD c, LPARAM d);


// combobox - source lines
void WINAPI dlgCombo_addStrs(HWND h, DWORD c, cch* const* s, int n)
{	for(int i = 0; i < n; i++) { dlgCombo_addStr(h, c, s[i]); }}
int WINAPI dlgCombo_addStr(HWND h, DWORD c, cch* s) {
	return sendDlgMsgU(h, c, CB_ADDSTRING, s); }
int WINAPI dlgCombo_addStr(HWND h, DWORD c, cch* s, LPARAM l) {
	int i = dlgCombo_addStr(h, c, s); if(i >= 0)
		dlgCombo_setData(h, c, i, l); return i; }
int WINAPI dlgCombo_setData(HWND h, DWORD c, int i, LPARAM l) {
	return sendDlgMsg(h, c, CB_SETITEMDATA, i, l); }
LPARAM WINAPI dlgCombo_getData(HWND h, DWORD c, int i) {
	return sendDlgMsg(h, c, CB_GETITEMDATA, i); }
int WINAPI dlgCombo_getSel(HWND h, DWORD c) {
	return sendDlgMsg(h, c, CB_GETCURSEL); }
int WINAPI dlgCombo_setSel(HWND h, DWORD c, int i) {
	return sendDlgMsg(h, c, CB_SETCURSEL, i); }		
int WINAPI dlgCombo_reset(HWND h, DWORD c) {
	return sendDlgMsg(h, c, CB_RESETCONTENT); }
cstr WINAPI dlgCombo_getText(HWND h, DWORD c, int i) {
	return getDlgTextIdx(h, c, CB_GETLBTEXT, i); }
int WINAPI dlgCombo_find(HWND h, DWORD c, cch* s) {
	return sendDlgMsgU(h, c, CB_FINDSTRING, -1, s); }
int WINAPI dlgCombo_findExact(HWND h, DWORD c, cch* s) {
	return sendDlgMsgU(h, c, CB_FINDSTRINGEXACT, -1, s); }
int WINAPI dlgCombo_selStr(HWND h, DWORD c, cch* s) {
	return sendDlgMsgU(h, c, CB_SELECTSTRING, -1, s); }
	
// complex functions
LPARAM WINAPI dlgCombo_getData2(HWND h, DWORD c, int i) { LPARAM 
	r = dlgCombo_getData(h, c, i); return (r != -1) ? r : 0; }
int WINAPI dlgCombo_findData(HWND h, DWORD c, LPARAM d) {
	int nImg = sendDlgMsg(h, c, CB_GETCOUNT);
	for(int i = 0; i < nImg; i++) { if(dlgCombo_getData(
	h, c, i) == d) { return i; } } return -1; 
}
