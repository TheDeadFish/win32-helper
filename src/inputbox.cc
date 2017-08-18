// inputbox - include lines
char* WINAPI inputBox(HWND hwnd, cch* title,
	cch* prompt, cch* content);

// inputbox - source lines
struct InputBox_t { cch* title;	cch* prompt; cch* content; };
		
INT_PTR CALLBACK InputBoxProc(
	HWND hwnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam)
{
	DLGMSG_SWITCH(ON_MESSAGE(WM_INITDIALOG, 
		setWindowText(hwnd, ((InputBox_t*)lParam)->title);
		setDlgItemText(hwnd, 1001, ((InputBox_t*)lParam)->prompt);
		setDlgItemText(hwnd, 1000, ((InputBox_t*)lParam)->content))
	  CASE_COMMAND(ON_COMMAND(IDCANCEL, EndDialog(hwnd, 0))
	  ON_COMMAND(IDOK, EndDialog(hwnd, (INT_PTR)
		getDlgItemText(hwnd, 1000).data)),)
	,)
}

__attribute__((section(".text$inpBoxDlgTmpl")))
static const u32 dlgTmpl[] = { 0x90C80840,0x00000000,0x00000004,0x00EE0000,
0x0000004F,0x00490000,0x0070006E,0x00740075,0x00420020,0x0078006F,0x00080000,
0x0053004D,0x00530020,0x00650068,0x006C006C,0x00440020,0x0067006C,0x00000000,
0x50810080,0x00000000,0x003A0007,0x000E00E0,0xFFFF03E8,0x00000081,0x00000000,
0x50010001,0x00000000,0x000600B5,0x000E0032,0xFFFF0001,0x004F0080,0x0000004B,
0x00000000,0x50010000,0x00000000,0x001800B5,0x000E0032,0xFFFF0002,0x00430080,
0x006E0061,0x00650063,0x0000006C,0x00000000,0x50020080,0x00000000,0x00060007,
0x0030009F,0xFFFF03E9,0x00000082,0x00000000 };

char* WINAPI inputBox(HWND hwnd, cch* title,
	cch* prompt, cch* content)
{
	InputBox_t tmp = {title, prompt, content};
	return (char*)DialogBoxIndirectParam(NULL, (LPCDLGTEMPLATE)
		dlgTmpl, hwnd, InputBoxProc, (LPARAM)&tmp);
}
