// sendMsg - include lines
LRESULT WINAPI sendMessage(HWND, UINT);
LRESULT WINAPI sendMessage(HWND, UINT, WPARAM);
LRESULT WINAPI sendMessageL(HWND, UINT, LPARAM);
LRESULT WINAPI sendDlgMsg(HWND, DWORD, UINT);
LRESULT WINAPI sendDlgMsg(HWND, DWORD, UINT, WPARAM);
LRESULT WINAPI sendDlgMsgL(HWND, DWORD, UINT, LPARAM);

static inline LRESULT sendMessage(HWND h, UINT m, 
	WPARAM w, LPARAM l) { return SendMessageW(h, m, w, l); }
static inline LRESULT WINAPI sendDlgMsg(HWND h, DWORD c, UINT m,
	WPARAM w, LPARAM l) { return SendDlgItemMessageW(h, c, m, w, l); }

// utf8 conversion
LRESULT WINAPI sendMessageU(HWND, UINT, cch* str);
LRESULT WINAPI sendMessageU(HWND, UINT, WPARAM, cch*);
LRESULT WINAPI sendDlgMsgU(HWND, DWORD, UINT, cch* str);
LRESULT WINAPI sendDlgMsgU(HWND, DWORD, UINT, WPARAM, cch*);

// special functions
cstr WINAPI getWndTextIdx(HWND h, DWORD m, DWORD i);
cstr WINAPI getDlgTextIdx(HWND h, DWORD c, DWORD m, DWORD i);

// sendMsg - source lines
LRESULT WINAPI sendMessage(HWND h, UINT m) {
	return SendMessageW(h, m, 0, 0); }
LRESULT WINAPI sendMessage(HWND h, UINT m, WPARAM w) {
	return SendMessageW(h, m, w, 0); }
LRESULT WINAPI sendMessageL(HWND h, UINT m, LPARAM l) {
	return SendMessageW(h, m, 0, l); }
LRESULT WINAPI sendDlgMsg(HWND h, DWORD c, UINT m) {
	return SendDlgItemMessageW(h, c, m, 0, 0); }
LRESULT WINAPI sendDlgMsg(HWND h, DWORD c, UINT m, WPARAM w) {
	return SendDlgItemMessageW(h, c, m, w, 0); }
LRESULT WINAPI sendDlgMsgL(HWND h, DWORD c, UINT m, LPARAM l) {
	return SendDlgItemMessageW(h, c, m, 0, l); }

// utf8 conversion
LRESULT WINAPI sendMessageU(HWND h, UINT m, cch* s) {
	return SendMessageW(h, m, 0, (LPARAM)widen(s).data); }
LRESULT WINAPI sendMessageU(HWND h, UINT m, WPARAM w, cch* s) {
	return SendMessageW(h, m, w, (LPARAM)widen(s).data); }
LRESULT WINAPI sendDlgMsgU(HWND h, DWORD c, UINT m, cch* s) {
	return SendDlgItemMessageW(h, c, m, 0, (LPARAM)widen(s).data); }
LRESULT WINAPI sendDlgMsgU(HWND h, DWORD c, UINT m, WPARAM w, cch* s) {
	return SendDlgItemMessageW(h, c, m, w, (LPARAM)widen(s).data); }
	
// special functions
cstr WINAPI getWndTextIdx(HWND h, DWORD m, DWORD i) {
	W32SARD_(sendMessage(h, m+1), sendMessage(h, m, i, (LPARAM)ws)) }
cstr WINAPI getDlgTextIdx(HWND h, DWORD c, DWORD m, DWORD i) {
	return getWndTextIdx(GetDlgItem(h, c), m, i); }
