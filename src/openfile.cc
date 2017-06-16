// openfile - include lines
void __thiscall dynOpenFileDlg_free(OPENFILENAMEA* ofn);
struct OpenFileName_ : OPENFILENAMEA { 
	~OpenFileName_() { dynOpenFileDlg_free(this); }
	cstr& cStr() { return *(cstr*)&lpstrFile; }
	xarray<cch*>& lst() { return *(xarray<cch*>*)&lpstrFile; }};
struct OpenFileName : OpenFileName_ { OpenFileName(); BOOL doModal(HWND hParent); };
struct SaveFileName : OpenFileName_ { SaveFileName(); BOOL doModal(HWND hParent); };

// openfile - source lines
xarray<cch*> __stdcall utf816_strLst_unpack(WCHAR* str) {
	xarray<cch*> lst = {}; if(str) while(*str) { lst.push_back(
	utf816_dup(str).data); str += strlen(str)+1; } return lst; }
WCHAR* __stdcall utf816_strLst_dup(cch* str) { if(!str) return 0; cch* 
	tmp = str; while(RW(tmp)) tmp++; return utf816_dup2(str, tmp-str+2); }

void dynOpenFileDlg_alloc(HWND hwnd, OPENFILENAMEW* ofn)
{
	int size = SendMessageW(hwnd, CDM_GETFOLDERPATH, 0, 0) +
		SendMessageW(hwnd, CDM_GETSPEC, 0, 0)+ofn->dwReserved+1;
	if(ofn->nMaxFile < size) { ofn->nMaxFile = size;
		xRealloc(ofn->lpstrFile, size); }
}

UINT_PTR CALLBACK dynOpenFileDlg_hook2(
   HWND hwnd, UINT uiMsg,
   WPARAM wParam, LPARAM lParam)
{
	OPENFILENAMEW* ofn = Void(
		GetWindowLongPtr(hwnd, GWL_USERDATA));
	if((uiMsg == WM_COMMAND)&&(wParam == IDOK))
		dynOpenFileDlg_alloc(hwnd, ofn);
	return ((DLGPROC)ofn->pvReserved)(
		hwnd, uiMsg, wParam, lParam);
}

void dynOpenFileDlg_init(HWND hwnd, LPARAM lParam)
{
	HWND hParent = GetParent(hwnd);
	SetWindowLongPtr(hParent, 
		GWL_USERDATA, (LONG_PTR)lParam);
	OPENFILENAMEW* ofn = Void(lParam);
	ofn->pvReserved = (void*)SetWindowLongPtrW(hParent, 
		GWL_WNDPROC, (LONG_PTR)dynOpenFileDlg_hook2);
}

UINT_PTR CALLBACK dynOpenFileDlg_hook(
   HWND hwnd, UINT uiMsg,
   WPARAM wParam, LPARAM lParam
){
	if(uiMsg == WM_INITDIALOG) {
		dynOpenFileDlg_init(hwnd, lParam);
	} ei(uiMsg == WM_NOTIFY) { 
		OFNOTIFYW* ofn = Void(lParam);
		if(ofn->hdr.code == CDN_SELCHANGE)
			dynOpenFileDlg_alloc(GetParent(hwnd), ofn->lpOFN);
	} return 0;
}

void __thiscall dynOpenFileDlg_free(OPENFILENAMEA* ofn)
{
	if(ofn->Flags & 0x200) freeLst(ofn->lpstrFile, 
	ofn->nMaxFile); else free(ofn->lpstrFile); 
}

BOOL WINAPI dynOpenFileDlg_doModal(OPENFILENAMEA* 
	pofn, HWND hwnd, typeof(&GetSaveFileNameW) fn)
{
	// initialize OPENFILENAMEW
	OPENFILENAMEW ofn; memcpy(&ofn,
		pofn, sizeof(OPENFILENAMEW));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.Flags |= OFN_ENABLEHOOK | OFN_EXPLORER;
	ofn.lpfnHook = dynOpenFileDlg_hook;
	
	// initialize utf16 strings
	ofn.lpstrFilter = utf816_strLst_dup(pofn->lpstrFilter);
	cstrW (__stdcall *fn2)(cch*) = utf816_dup; VARFIX(fn2);
	ofn.lpstrInitialDir = fn2(pofn->lpstrInitialDir);
	ofn.lpstrTitle = fn2(pofn->lpstrTitle);
	ofn.lpstrDefExt = fn2(pofn->lpstrDefExt);
	ofn.dwReserved += strlen(pofn->lpstrDefExt);
	{ cstrW tmp = {}; if(!(pofn->Flags & 0x200)) 
	{ tmp = fn2(pofn->lpstrFile); } ofn.lpstrFile = tmp.data;
	ofn.nMaxFile = tmp.slen+1; } dynOpenFileDlg_free(pofn);
	
	SCOPE_EXIT(	// free utf16 strings
	free((void*)ofn.lpstrFilter); free((void*)ofn.lpstrInitialDir);
	free((void*)ofn.lpstrTitle); free((void*)ofn.lpstrDefExt);
	// convert lpstrFile to utf8
	cstr (__stdcall *fn2)(const WCHAR*) = utf816_dup; 
	if(pofn->Flags & 0x200) { nothing(); fn2 = Void(
	utf816_strLst_unpack); } cstr tmp = fn2(ofn.lpstrFile);
	pofn->lpstrFile = tmp; pofn->nMaxFile = tmp.slen; 
	free((void*)ofn.lpstrFile)); return fn(&ofn);
}

OpenFileName::OpenFileName() { ZINIT; Flags =
	OFN_FILEMUSTEXIST|OFN_HIDEREADONLY;	}
SaveFileName::SaveFileName() { ZINIT; Flags =
	OFN_PATHMUSTEXIST|OFN_OVERWRITEPROMPT; }
BOOL OpenFileName::doModal(HWND hParent) { return 
	dynOpenFileDlg_doModal(this, hParent, GetOpenFileNameW); }
BOOL SaveFileName::doModal(HWND hParent) { return 
	dynOpenFileDlg_doModal(this, hParent, GetSaveFileNameW); }
