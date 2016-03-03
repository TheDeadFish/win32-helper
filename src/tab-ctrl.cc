// tab control - include lines
void WINAPI addDlgTabPage(HWND hwnd, UINT ctrlId, int index, LPCSTR tabName);
void WINAPI renameDlgTabPage(HWND hwnd, UINT ctrlId, int index, LPCSTR tabName);
void WINAPI addDlgTabPage(HWND hwnd, UINT ctrlId, int index, LPCWSTR tabName);
void WINAPI renameDlgTabPage(HWND hwnd, UINT ctrlId, int index, LPCWSTR tabName);
void WINAPI removeDlgTabPage(HWND hwnd, UINT ctrlId, int index);
void WINAPI resetDlgTabCtrl(HWND hwnd, UINT ctrlId);
int WINAPI setDlgTabPage(HWND hwnd, UINT ctrlID, int page);
int WINAPI getDlgTabPage(HWND hwnd, UINT ctrlID);


// tab control (ANSI) - source lines
void WINAPI addDlgTabPage(HWND hwnd, UINT ctrlId, int index, LPCSTR tabName) {
	TCITEMA tcItem = {TCIF_TEXT}; tcItem.pszText = (char*)tabName;
	SendDlgItemMessage(hwnd, ctrlId, TCM_INSERTITEMA, index, (LPARAM)&tcItem); }
void WINAPI renameDlgTabPage(HWND hwnd, UINT ctrlId, int index, LPCSTR tabName) {
	TCITEMA tcItem = {TCIF_TEXT}; tcItem.pszText = (char*)tabName;
	SendDlgItemMessage(hwnd, ctrlId, TCM_SETITEMA, index, (LPARAM)&tcItem); }

// tab control (WIDE) - source lines
void WINAPI addDlgTabPage(HWND hwnd, UINT ctrlId, int index, LPCWSTR tabName) {
	TCITEMW tcItem = {TCIF_TEXT}; tcItem.pszText = (WCHAR*)tabName;
	SendDlgItemMessage(hwnd, ctrlId, TCM_INSERTITEMW, index, (LPARAM)&tcItem); }
void WINAPI renameDlgTabPage(HWND hwnd, UINT ctrlId, int index, LPCWSTR tabName) {
	TCITEMW tcItem = {TCIF_TEXT}; tcItem.pszText = (WCHAR*)tabName;
	SendDlgItemMessage(hwnd, ctrlId, TCM_SETITEMW, index, (LPARAM)&tcItem); }
void WINAPI removeDlgTabPage(HWND hwnd, UINT ctrlId, int index) {
	SendDlgItemMessage(hwnd, ctrlId, TCM_DELETEITEM, index, 0); }
void WINAPI resetDlgTabCtrl(HWND hwnd, UINT ctrlId) {
	SendDlgItemMessage(hwnd, ctrlId, TCM_DELETEALLITEMS, 0, 0); }
int WINAPI setDlgTabPage(HWND hwnd, UINT ctrlID, int page) {
	return SendDlgItemMessage(hwnd, ctrlID, TCM_SETCURSEL, page, 0); }
int WINAPI getDlgTabPage(HWND hwnd, UINT ctrlID) {
	return SendDlgItemMessage(hwnd, ctrlID, TCM_GETCURSEL, 0, 0); }
