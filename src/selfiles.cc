#include <stdshit.h>
#include <shlobj.h>
#include <windowsx.h>
#define MAX_VTABLE 32
#define GetPIDLItem(pida, i) (LPCITEMIDLIST)(((LPBYTE)pida)+(pida)->aoffset[i+1])

// non-portable evil 
WCHAR* GetItemName(LPCITEMIDLIST pidl)
{
	// locate extention block
	if((pidl->mkid.abID[0] & 0x70) != 0x30) return NULL;
	Void endPtr; 
	if(pidl->mkid.abID[0] & 0x04) {
		endPtr = wcschr((WCHAR*)&pidl->mkid.abID[12], '\0')+1;
	} else {
		endPtr = strchr((char*)&pidl->mkid.abID[12], '\0')+1;
		if(endPtr.dword(1) != 0xbeef0004) endPtr += 1; }
	if(endPtr.dword(1) != 0xbeef0004) return NULL;
	
	// get fileName
	static const byte offset[] = {20, 0, 0, 0, 38, 42, 46};
	size_t index = endPtr.word(1)-3;
	//asm("" : "=r"(index) : "r"(index));
	if((index >= ARRAYSIZE(offset))
	||(offset[index] == 0)) return NULL;
	return endPtr+offset[index];
	
	//int offset;
	//switch(endPtr.word(1)) {
	//case 3: offset = 20; break; case 7: offset = 38; break;
	//case 8: offset = 42; break; case 9: offset = 46; break;
	//default: return NULL; }
	//return endPtr+offset;
}

LPWSTR WINAPI ConvertToNULLTerm(
	LPWSTR pchRead, DWORD flags) { 
	LPWSTR pchWrite = pchRead;
	for ( ; ; ) 
	{ 
		// locate start of string
		while(*pchRead == ' ') pchRead++;
		if(*pchRead == '\"') pchRead++;
		LPWSTR pchBegin = pchRead;
		if(!*pchBegin) break;

		// locate end of string
		{ WCHAR ch; for(;;) { ch = *pchRead; pchRead++;
		if(ch == '\"') goto BREAK2; if(ch == '\0') break; }
		pchRead[0] = 0; BREAK2: pchRead[-1] = 0;}

		// copy the string
		LPWSTR pchWrite2 = pchWrite;
		while(pchBegin < pchRead) {
			WRI(pchWrite2, RDI(pchBegin)); }
		
		// validate file attributes
		if(flags & OFN_FILEMUSTEXIST) {
		DWORD atribs = GetFileAttributesW(pchWrite);
		if(atribs == INVALID_FILE_ATTRIBUTES)
			return pchWrite;
		} pchWrite = pchWrite2;
	}
	
	*pchWrite = '\0';		
	return NULL;
}

// static context
struct SelectFilesCtx : OPENFILENAMEW{
	HWND hwnd, hEdit;
	bool fSelChangedPending;
	bool bUserPressedOk; 
	WNDPROC ofnWndProc; 
	size_t oscComProc;
	size_t vtable[MAX_VTABLE];
	
	void init(HWND hdlg);
	void onChange(void);
	int onSelect(void);
	
	
	static LRESULT CALLBACK OFNFolderProc( HWND hwnd, 
		UINT uMsg, WPARAM wParam, LPARAM lParam);
	static UINT_PTR CALLBACK OFNHookProc(HWND hdlg,
		UINT uiMsg, WPARAM wParam,LPARAM lParam);
	static HRESULT __stdcall OnStateChange_hook(
		VOID* This, VOID *ppshv, ULONG uChange);
};


void SelectFilesCtx::init(HWND hdlg)
{
	// initialize dialog
	fSelChangedPending = false; hwnd = GetParent(hdlg);
	hEdit = (HWND)SendMessageW(GetDlgItem(
		hwnd, cmb13), CBEM_GETEDITCONTROL, 0, 0);
	SendMessageW(hwnd,CDM_SETCONTROLTEXT,
		IDOK,(LPARAM)L"Select");
		
	// hook file dialog
	SetPropW(hwnd, L"pOFN", (HANDLE)this);
	ofnWndProc = (WNDPROC) SetWindowLongPtrW(
		hwnd,GWLP_WNDPROC,(LONG_PTR)OFNFolderProc);
		
	// hook ICommDlgBrowser::OnStateChange
	IUnknown* lpObj =  Void(SendMessage(hwnd, WM_USER+7, 0, 0));
	ICommDlgBrowser* lpObjCdb;
	lpObj->QueryInterface(IID_ICommDlgBrowser, (void**)&lpObjCdb);
	lpObjCdb->Release(); size_t*& lpVtab = *(size_t**)lpObjCdb;
	memcpyX(vtable, lpVtab, MAX_VTABLE); lpVtab = vtable;
	oscComProc = vtable[4];
	vtable[4] = (size_t)OnStateChange_hook;		
}

void SelectFilesCtx::onChange(void)
{
	// get IShellView
	fSelChangedPending = FALSE;
	IShellBrowser* isb = Void(SendMessage(hwnd, WM_USER+7, 0, 0));
	IShellView* isv; isb->QueryActiveShellView(&isv); 
	isv->Release();
	
	// get selection data
	IDataObject *ido; if(FAILED(isv->GetItemObject( SVGIO_SELECTION, 
		IID_IDataObject, (void **)&ido))) { NOSEL:
			SetWindowTextW(hEdit, L""); return; }
	SCOPE_EXIT(ido->Release());	
	FORMATETC fmte = { RegisterClipboardFormat(CFSTR_SHELLIDLIST),
		NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL }; STGMEDIUM medium;
	if (FAILED(ido->GetData(&fmte, &medium))) goto NOSEL;
	SCOPE_EXIT(GlobalFree(medium.hGlobal));	
	LPIDA pida = (LPIDA)GlobalLock(medium.hGlobal);
	
	// build name list
	xVector<WCHAR> buff;
	for(int i = 0; i < pida->cidl; i++) {
		LPCITEMIDLIST pidl = GetPIDLItem(pida, i);	
		if(WCHAR* itemName = GetItemName(pidl)) {
			int strLen = wcslen(itemName);
			WCHAR* curPos = buff.xnalloc(strLen+3);
			WRI(curPos, '\"'); curPos = memcpyX(curPos,
			itemName, strLen); RI(curPos) = 0x200022;
		}
	}
	
	// update edit control
	if(buff) { buff.end()[-1] = 0;
		SetWindowTextW(hEdit, buff); }
	else goto NOSEL;
}

//static
int SelectFilesCtx::onSelect(void)
{
	// read path
	int pathLen = SendMessageW(hwnd, CDM_GETFOLDERPATH, 
		nMaxFile, (LPARAM)lpstrFile);
	if(pathLen < 2) return 0;
	if(!(Flags & OFN_ALLOWMULTISELECT)) {
	if(lpstrFile[pathLen-2] != '\\') { VARFIX(pathLen);
		RI(lpstrFile+pathLen-1) = '\\';	pathLen++; }
	ADDP(pathLen,-1); }
	
	// read name
	int nameLen = GetWindowTextLengthW(hEdit);
	if(nMaxFile < pathLen+nameLen+2) { nMaxFile = 
		pathLen+nameLen+2; xRealloc(lpstrFile, nMaxFile); }
	nameLen = GetWindowText(hEdit, lpstrFile+pathLen, nMaxFile);
	lpstrFile[pathLen+nameLen+1] = 0;

	// process buffer
	if(wcschr(lpstrFile+pathLen, '\\')) return IDOK;
	if(LPWSTR err = ConvertToNULLTerm(lpstrFile+pathLen, Flags)) {
		SetWindowTextW(hEdit, err); return IDOK; }
	bUserPressedOk = true; return IDCANCEL;	
}

// GetOpenFileName hooking
#define CDM_SELCHANGE (CDM_LAST + 102)
HRESULT __stdcall SelectFilesCtx::OnStateChange_hook(
	VOID* This, VOID *ppshv, ULONG uChange) 
{
	SelectFilesCtx* ctx = Void(*(size_t**)This) - 
		offsetof(SelectFilesCtx, vtable);
	if((uChange == CDBOSC_SELCHANGE)
	&&(!ctx->fSelChangedPending)) {
		ctx->fSelChangedPending = true;
		PostMessageW(ctx->hwnd, CDM_SELCHANGE, 0, 0); 
		return 0;
	} else {
		return HOTCALL(OnStateChange_hook,ctx->oscComProc)
			(This, ppshv, uChange);
	}
}

// GetOpenFileName hook procedures
LRESULT CALLBACK SelectFilesCtx::OFNFolderProc( HWND hWnd, 
	UINT uMsg, WPARAM wParam, LPARAM lParam ) 
{
	SelectFilesCtx* lpOFN = (SelectFilesCtx*)
		GetPropW(hWnd, L"pOFN");

	if((uMsg==WM_COMMAND) && (wParam==IDOK)) {
	if(!(wParam = lpOFN->onSelect())) return 0; }
	ei(uMsg == CDM_SELCHANGE) {
		lpOFN->onChange(); return 0; }
		
	return CallWindowProcW(lpOFN->ofnWndProc,
		hWnd, uMsg, wParam, lParam); }
		
UINT_PTR CALLBACK SelectFilesCtx::OFNHookProc(HWND hdlg,
	UINT uiMsg, WPARAM wParam,LPARAM lParam)
{
	if(uiMsg==WM_INITDIALOG) {
		((SelectFilesCtx*)lParam)->init(hdlg); }
	return 0;
}

WCHAR* selectFiles(HWND hParent, 
	const WCHAR* title, const WCHAR* filter,
	const WCHAR* initDir, DWORD flags)
{
	SelectFilesCtx ofn = {};
	ofn.lStructSize = sizeof(OPENFILENAMEW);
	ofn.hwndOwner = hParent; ofn.lpstrFilter = filter;  
	ofn.lpstrInitialDir = initDir; ofn.Flags = flags;
	ofn.lpstrTitle = title; ofn.nMaxFile = MAX_PATH+1;
	ofn.lpstrFile = xCalloc(MAX_PATH+1);
	ofn.lpfnHook = SelectFilesCtx::OFNHookProc;
	if((GetOpenFileNameW(&ofn))
	&&(ofn.Flags & OFN_ALLOWMULTISELECT))
		ofn.lpstrFile[ofn.nFileOffset-1] = 0;
	ei(!ofn.bUserPressedOk) free_ref(ofn.lpstrFile);
	return ofn.lpstrFile;
}

WCHAR* selectFolderW(HWND hParent, const WCHAR* title, const WCHAR* initDir) {
	return selectFiles(hParent,	title ? title : L"Select Folder",
		L"Folders\0*.\0", initDir, OFN_HIDEREADONLY | OFN_ENABLEHOOK
		| OFN_EXPLORER |  OFN_ENABLESIZING | OFN_PATHMUSTEXIST); }
WCHAR* selectFilesW(HWND hParent, const WCHAR* title, const WCHAR* initDir) {
	return selectFiles(hParent, title ? title : L"Select Files",
		L"All Files (*.*)\0*.*\0", initDir, OFN_ALLOWMULTISELECT |
	OFN_NODEREFERENCELINKS | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY |
	OFN_ENABLEHOOK | OFN_EXPLORER | OFN_ENABLESIZING | OFN_PATHMUSTEXIST); }
	
cstr selectFolder(HWND hParent, cch* title, cch* initDir)
{
	return narrowFree(selectFolderW(hParent, wxstr(
		utf816_dup(title)), wxstr(utf816_dup(initDir))));
}

xarray<cch*> __stdcall dynOpenFileDlg_unpack(
	WCHAR* path, size_t nFileOffset);


xarray<cch*> selectFiles(HWND hParent, cch* title, cch* initDir)
{
	WCHAR* path = selectFilesW(hParent, wxstr(
		utf816_dup(title)), wxstr(utf816_dup(initDir)));
	xarray<cch*> lst = {}; if(!path) return lst;
	
	return dynOpenFileDlg_unpack(path, wcslen(path)+1);
	
	
	
	
	/*GET_RETPAIR(auto pathLen, auto name, utf816_size(path));
	do { GET_RETPAIR(int 
		nameSize, auto name2, utf816_size(name));
		char* buff = xmalloc(nameSize+pathLen);
		utf816_cpy(utf816_cpy(buff, path), name);
		lst.push_back(buff); name = name2; 
	}while(*name); return lst;*/
}		
