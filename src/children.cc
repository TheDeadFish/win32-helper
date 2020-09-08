// children - include lines
RECT WINAPI GetChildRect(HWND hWnd); RECT WINAPI GetChildRect(HWND hWnd, UINT ctrlId);
XYWH WINAPI GetChildXywh(HWND hWnd); XYWH WINAPI GetChildXywh(HWND hWnd, UINT ctrlId);
RECT WINAPI MurderChild(HWND hWnd, UINT ctrlId);
HWND WINAPI PossessChild(HWND hwnd, UINT ctrlId,WNDPROC wndProc, void* This);
HWND WINAPI PossessWindow(HWND hwnd, WNDPROC wndProc, void* This);
void WINAPI EnableDlgItem(HWND hwnd, UINT ctrlId, BOOL bEnable);
void WINAPI EnableDlgItems(HWND hwnd, const WORD* dlgItems, int itemCount, BOOL bEnable);
void WINAPI ShowDlgItems(HWND hwnd, const WORD* dlgItems, int itemCount, BOOL bShow);
BOOL WINAPI IsButtonChecked(HWND hButton);
void WINAPI DestroyNotify(HWND hwnd);

// children - source lines
RECT WINAPI GetChildRect(HWND hWnd) { RECT rect;
	GetWindowRect(hWnd, &rect);  MapWindowPoints(HWND_DESKTOP,
	GetParent(hWnd), (LPPOINT) &rect, 2); return rect; }
XYWH WINAPI GetChildXywh(HWND hWnd) { RECT rect = GetChildRect(hWnd); 
	XYWH ret = {RECT_XYWH(rect)}; return ret; }
RECT WINAPI GetChildRect(HWND hWnd, UINT ctrlId) {
	return GetChildRect(GetDlgItem(hWnd, ctrlId)); }
XYWH WINAPI GetChildXywh(HWND hWnd, UINT ctrlId) {
	return GetChildXywh(GetDlgItem(hWnd, ctrlId)); }	
RECT WINAPI MurderChild(HWND hWnd, UINT ctrlId) {
	HWND hChild = GetDlgItem(hWnd, ctrlId);
	RECT childRect = GetChildRect(hChild);
	DestroyWindow(hChild); return childRect; }
HWND WINAPI PossessChild(HWND hwnd, UINT ctrlId,WNDPROC wndProc, void* This)
{ 	return PossessWindow(GetDlgItem(hwnd, ctrlId), wndProc, This); }
HWND WINAPI PossessWindow(HWND hwnd, WNDPROC wndProc, void* This) {
	SendMessage(hwnd, WM_DESTROY, 0, 0); 
	SendMessage(hwnd, WM_NCDESTROY, 0, 0);
	SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)wndProc);
	SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)This);	
	wndProc(hwnd, WM_CREATE, 0, 0); return hwnd; }
void WINAPI EnableDlgItem(HWND hwnd, UINT ctrlId, BOOL bEnable) {
	EnableWindow(GetDlgItem(hwnd, ctrlId), bEnable); }
void WINAPI EnableDlgItems(HWND hwnd, const WORD* dlgItems,
	int itemCount, BOOL bEnable)
{	for(int i = 0; i < itemCount; i++) 
		EnableDlgItem(hwnd, dlgItems[i], bEnable); }	
void WINAPI ShowDlgItems(HWND hwnd, const WORD* dlgItems,
	int itemCount, BOOL bShow)
{	for(int i = 0; i < itemCount; i++)  ShowWindow(GetDlgItem(
		hwnd, dlgItems[i]), bShow ? SW_SHOWNA : SW_HIDE); }
BOOL WINAPI IsButtonChecked(HWND hButton) {
	return SendMessage(hButton, BM_GETCHECK, 0, 0); }
void WINAPI DestroyNotify(HWND hwnd) {
	HWND hParent = GetWindow(hwnd, GW_OWNER);
	SendMessage(hParent, WM_PARENTNOTIFY, 
		WM_DESTROY, (LPARAM)hwnd); }
