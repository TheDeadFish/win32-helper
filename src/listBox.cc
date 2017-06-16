// listbox - include lines
int WINAPI listBox_addStr(HWND, DWORD, cch*);
int WINAPI listBox_addStr(HWND, DWORD, cch*, LPARAM);
int WINAPI listBox_setData(HWND, DWORD, int, LPARAM);
LPARAM WINAPI listBox_getData(HWND, DWORD, int item);
int WINAPI listBox_getCurSel(HWND, DWORD);
int WINAPI listBox_setCurSel(HWND, DWORD, int);
int WINAPI listBox_getSel(HWND, DWORD, int);
int WINAPI listBox_setSel(HWND, DWORD, int, int);
int WINAPI listBox_selCount(HWND, DWORD);
int WINAPI listBox_reset(HWND, DWORD);
cstr WINAPI listBox_getText(HWND, DWORD, int);
int WINAPI listBox_find(HWND, DWORD, cch*);
int WINAPI listBox_selStr(HWND, DWORD, cch*);

// complex functions
xarray<int> WINAPI listBox_selItems(HWND, DWORD);

// combobox - source lines
int WINAPI listBox_addStr(HWND hwnd, DWORD ctrlId, cch* str) {
	return sendDlgMsgU(hwnd, ctrlId, LB_ADDSTRING, str); }
int WINAPI listBox_addStr(HWND hwnd, DWORD ctrlId, cch* str, LPARAM lParam) {
	int item = listBox_addStr(hwnd, ctrlId, str); if(item >= 0)
		listBox_setData(hwnd, ctrlId, item, lParam); return item; }
int WINAPI listBox_setData(HWND hwnd, DWORD ctrlId, int item, LPARAM lParam) {
	return sendDlgMsg(hwnd, ctrlId, LB_SETITEMDATA, item, lParam); }
LPARAM WINAPI listBox_getData(HWND hwnd, DWORD ctrlId, int item) {
	return sendDlgMsg(hwnd, ctrlId, LB_GETITEMDATA, item); }
int WINAPI listBox_getCurSel(HWND hwnd, DWORD ctrlId) {
	return sendDlgMsg(hwnd, ctrlId, LB_GETCURSEL); }
int WINAPI listBox_setCurSel(HWND hwnd, DWORD ctrlId, int item) {
	return sendDlgMsg(hwnd, ctrlId, LB_SETCURSEL, item); }
int WINAPI listBox_getSel(HWND hwnd, DWORD ctrlId, int item) {
	return sendDlgMsg(hwnd, ctrlId, LB_GETSEL, item); }
int WINAPI listBox_setSel(HWND hwnd, DWORD ctrlId, int state, int item) {
	return sendDlgMsg(hwnd, ctrlId, LB_SETSEL, state, item); }
int WINAPI listBox_selCount(HWND hwnd, DWORD ctrlId) {
	return sendDlgMsg(hwnd, ctrlId, LB_GETSELCOUNT); }
int WINAPI listBox_reset(HWND hwnd, DWORD ctrlId) {
	return sendDlgMsg(hwnd, ctrlId, LB_RESETCONTENT); }
cstr WINAPI listBox_getText(HWND h, DWORD c, int i) {
	return getDlgTextIdx(h, c, LB_GETTEXT, i); }
int WINAPI listBox_find(HWND h, DWORD c, cch* s) {
	return sendDlgMsgU(h, c, LB_FINDSTRING, -1, s); }
int WINAPI listBox_selStr(HWND h, DWORD c, cch* s) {
	return sendDlgMsgU(h, c, LB_SELECTSTRING, -1, s); }


// complex functions
xarray<int> WINAPI listBox_selItems(HWND hwnd, DWORD ctrlId) { int nSel = 
	listBox_selCount(hwnd, ctrlId); if(nSel < 0) return {0,0}; int* buff = 
	xMalloc(nSel); nSel = sendDlgMsg(hwnd, ctrlId, LB_GETSELITEMS, nSel, (LPARAM)buff);
	if(nSel < 0) { free(buff); return {0,0}; } return {buff, nSel}; }
