#ifndef _WIN32_HLP_H_
#define _WIN32_HLP_H_
#include <stdshit.h>
#include <windowsx.h>

#include "msgmap.h"
#include "sendmsg.cc"
#include "rectpnt.cc"
#include "children.cc"
#include "combobox.cc"
#include "radio-button.cc"
#include "tab-ctrl.cc"
#include "updw-ctrl.cc"
#include "stdwndclss.cc"
#include "listView.cc"
#include "msgloop.cc"
#include "listBox.cc"
#include "inputbox.cc"

// win32hlp: include lines
void WINAPI dlgButton_setCheck(HWND hwnd, int ctrlId, int state);

// drop.cc: include lines
xarray<xstr> WINAPI hDropGet(HANDLE hDrop);
xarray<wxstr> WINAPI hDropGetW(HANDLE hDrop);

// openfile.cc: include lines
void __thiscall dynOpenFileDlg_free(OPENFILENAMEA* ofn);
struct OpenFileName_ : OPENFILENAMEA { 
	~OpenFileName_() { dynOpenFileDlg_free(this); }
	cstr& cStr() { return *(cstr*)&lpstrFile; }
	xarray<xstr>& lst() { return *(xarray<xstr>*)&lpstrFile; }};
struct OpenFileName : OpenFileName_ { OpenFileName(); BOOL doModal(HWND hParent); };
struct SaveFileName : OpenFileName_ { SaveFileName(); BOOL doModal(HWND hParent); };

// selfiles.cc: include lines
WCHAR* selectFolderW(HWND hParent, const WCHAR* title, const WCHAR* initDir);
WCHAR* selectFilesW(HWND hParent, const WCHAR* title, const WCHAR* initDir);
cstr selectFolder(HWND hParent, cch* title, cch* initDir);
xarray<cch*> selectFiles(HWND hParent, cch* title, cch* initDir);

#endif
