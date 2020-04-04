#include <stdshit.h>
#include "../bin/win32hlp.h"

xarray<cch*> __stdcall dynOpenFileDlg_unpack(
	WCHAR* path, size_t nFileOffset)
{
	SCOPE_EXIT(free(path));
	xarray<cch*> lst = {}; 
	
	if(!nFileOffset) return lst;
	WCHAR* name = path+nFileOffset;
	if(name[-1] != '\0') name[-1] = 0;
	ei(name[-2] == '\\') name[-2] = 0;
	size_t pathLen = utf816_size(path);
	
	do { GET_RETPAIR(
		int nameSize, auto name2, utf816_size(name));
		char* buff = xmalloc(nameSize+pathLen);
		char* tmp = utf816_cpy(buff, path); *tmp = '\\'; 
		utf816_cpy(tmp+1, name); lst.push_back(buff); 
		name = (WCHAR*)name2; }while(*name); 
	return lst;
}

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
	if(ofn.lpstrDefExt = fn2(pofn->lpstrDefExt))
		ofn.dwReserved = strlen(ofn.lpstrDefExt);
	{ cstrW tmp = {}; if(!(pofn->Flags & 0x200)) 
	{ tmp = fn2(pofn->lpstrFile); } ofn.lpstrFile = tmp.data;
	ofn.nMaxFile = tmp.slen+1; } dynOpenFileDlg_free(pofn);
	
	SCOPE_EXIT(	// free utf16 strings
	free((void*)ofn.lpstrFilter); free((void*)ofn.lpstrInitialDir);
	free((void*)ofn.lpstrTitle); free((void*)ofn.lpstrDefExt);
	// convert lpstrFile to utf8
	if(!(pofn->Flags & 0x200)) { auto tmp = narrowFree(ofn.lpstrFile);
		pofn->lpstrFile = tmp; pofn->nMaxFile = tmp.slen;
	} else { auto tmp = dynOpenFileDlg_unpack(ofn.lpstrFile, ofn.nFileOffset);
		pofn->lpstrFile = (char*)tmp.data; pofn->nMaxFile = tmp.len; });
	return fn(&ofn);
}

OpenFileName::OpenFileName() { ZINIT; Flags =
	OFN_FILEMUSTEXIST|OFN_HIDEREADONLY;	}
SaveFileName::SaveFileName() { ZINIT; Flags =
	OFN_PATHMUSTEXIST|OFN_OVERWRITEPROMPT; }
BOOL OpenFileName::doModal(HWND hParent) { return 
	dynOpenFileDlg_doModal(this, hParent, GetOpenFileNameW); }
BOOL SaveFileName::doModal(HWND hParent) { return 
	dynOpenFileDlg_doModal(this, hParent, GetSaveFileNameW); }
