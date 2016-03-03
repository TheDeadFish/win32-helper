// radio button - include lines
void WINAPI CheckDlgRadio(HWND hDlg, int nIDButton);
int WINAPI GetDlgRadioCheck(HWND hDlg, int first, int last);

// radio button - source lines
void WINAPI CheckDlgRadio(HWND hDlg, int nIDButton) {
	HWND hwnd = GetDlgItem(hDlg, nIDButton);
	for(HWND hwndT = hwnd; hwndT; hwndT = GetWindow(hwndT, GW_HWNDPREV)) {
		SendMessage(hwndT, BM_SETCHECK, hwnd == hwndT, 0);
		if(GetWindowLong(hwndT, GWL_STYLE) & WS_GROUP) break; }
	while(hwnd = GetWindow(hwnd, GW_HWNDNEXT)) {
		if(GetWindowLong(hwnd, GWL_STYLE) & WS_GROUP) break;
		if(!(SendMessage(hwnd, WM_GETDLGCODE, 0, 0) & DLGC_RADIOBUTTON)) break;
		SendMessage(hwnd, BM_SETCHECK, FALSE, 0); } }
int WINAPI GetDlgRadioCheck(HWND hDlg, int first, int last) {
	for(int i = first; i <= last; i++) if(IsDlgButtonChecked(hDlg, i))
		return i-first; return 0; }
