// standard window class - include lines
HWND msgWnd_create(WNDPROC wndProc, LPVOID userData, LPVOID createParams);
HWND stdClass_create(LPCTSTR lpWindowName, DWORD dwStyle, DWORD dwExStyle, HWND hWndParent,
	HMENU hMenu, WNDPROC wndProc, LPVOID userData =0 , LPVOID createParams = 0);
HWND stdClass_create(LPCTSTR lpWindowName, DWORD dwStyle, DWORD dwExStyle,
	int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu,
	WNDPROC wndProc, LPVOID userData = 0 , LPVOID createParams = 0);
		
// standard window class - source lines
struct StdClassCtx {WNDPROC wndProc; LPVOID userData; LPVOID createParams; };
static LRESULT CALLBACK stdClass_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if(uMsg == WM_NCCREATE) { CREATESTRUCT& cs = *(CREATESTRUCT*)lParam; StdClassCtx& ctx = 
	*(StdClassCtx*)cs.lpCreateParams; cs.lpCreateParams = ctx.createParams; SetWindowLongPtr(
	hwnd, GWL_USERDATA, (LONG_PTR)ctx.userData); if(ctx.wndProc != NULL) { SetWindowLongPtr(
	hwnd, GWL_WNDPROC, (LONG_PTR)ctx.wndProc);	return ctx.wndProc(hwnd, uMsg, wParam, lParam);
	}} return DefWindowProc(hwnd, uMsg, wParam, lParam); }
HWND msgWnd_create(WNDPROC wndProc, LPVOID userData, LPVOID createParams) { return 
	stdClass_create(0, 0, 0, HWND_MESSAGE, 0, wndProc, userData, createParams); }
HWND stdClass_create(LPCTSTR a, DWORD b, DWORD c, HWND d, HMENU e, WNDPROC f, LPVOID g,
	LPVOID h) { return stdClass_create( a, b, c, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
	CW_USEDEFAULT, d, e, f, g, h); }
HWND stdClass_create(LPCTSTR lpWindowName, DWORD dwStyle, DWORD dwExStyle, int X, int Y, 
	int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, WNDPROC wndProc, LPVOID userData,
	LPVOID createParams) { static volatile ATOM wndAtom;if(wndAtom == 0) { WNDCLASS wc = {0};
	wc.lpfnWndProc = stdClass_proc; wc.hInstance = GetModuleHandle(NULL); wc.lpszClassName = 
	_T("dfswCls150130"); if(ATOM tmp = RegisterClass(&wc)) wndAtom = tmp; } StdClassCtx ctx =
	{wndProc, userData, createParams}; return CreateWindowEx(dwExStyle, MAKEINTATOM(wndAtom),
	lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, NULL, &ctx); }
