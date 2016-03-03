// updw-ctrl - include lines
UINT WINAPI setDlgSpinRange(HWND hwnd, UINT ctrlID, UINT min, UINT max); 
void WINAPI setDlgSpinValue(HWND hwnd, UINT ctrlId, UINT value);
UINT WINAPI getDlgSpinValue(HWND hwnd, UINT ctrlId);
UINT WINAPI validateDlgSpin(HWND hwnd, UINT ctrlId);
HWND WINAPI setDlgSpinValue(HWND hwnd, UINT ctrlId, 
	UINT min, UINT max, UINT value);
void WINAPI setDlgSpinInc(HWND hwnd, UINT increment);

// updw-ctrl - source lines
UINT WINAPI setDlgSpinRange(HWND hwnd, UINT ctrlId, UINT min, UINT max) {
	SendDlgItemMessage(hwnd, ctrlId, UDM_SETRANGE32, min, max); 
	return validateDlgSpin(hwnd, ctrlId); }
void WINAPI setDlgSpinValue(HWND hwnd, UINT ctrlId, UINT value) {
	SendDlgItemMessage(hwnd, ctrlId, UDM_SETPOS32, 0, value); }
UINT WINAPI getDlgSpinValue(HWND hwnd, UINT ctrlId) {
	return SendDlgItemMessage(hwnd, ctrlId, UDM_GETPOS32, 0, 0); }
UINT WINAPI validateDlgSpin(HWND hwnd, UINT ctrlId) {
	UINT value = getDlgSpinValue(hwnd, ctrlId);
	setDlgSpinValue(hwnd, ctrlId, value); return value; }
HWND WINAPI setDlgSpinValue(HWND hwnd, UINT ctrlId, 
	UINT min, UINT max, UINT value) { hwnd = GetDlgItem(hwnd, ctrlId);
	SendMessage(hwnd, UDM_SETRANGE32, min, max);
	SendMessage(hwnd, UDM_SETPOS32, 0, value); return hwnd; }
void WINAPI setDlgSpinInc(HWND hwnd, UINT increment) { UDACCEL accel[2];
	accel[0] = UDACCEL{0, increment}; accel[1] = UDACCEL{3, increment*2};
	SendMessage(hwnd, UDM_SETACCEL, 2, (LPARAM)&accel); }
