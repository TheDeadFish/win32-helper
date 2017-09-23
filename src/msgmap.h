// window context helpers
#define GET_WND_CONTEXT(type) \
	type* This = (type*)GetWindowLongPtr(hwnd, GWL_USERDATA);
#define INIT_DLG_CONTEXT(type, func) \
	if(uMsg == WM_INITDIALOG) { \
		SetWindowLongPtr(hwnd, DWL_USER, lParam); \
		type* This = (type*)lParam; func; return TRUE; } \
	type* This = (type*)GetWindowLongPtr(hwnd, DWL_USER); \
	if(This == NULL) return FALSE;	
#define MEMBER_WNDPROC2(type, name) \
	ALWAYS_INLINE LRESULT name(HWND hwnd, UINT uMsg, WPARAM w, LPARAM lParam); \
	static LRESULT CALLBACK c##name(HWND hwnd, UINT uMsg, WPARAM w, LPARAM lParam) { \
		GET_WND_CONTEXT(type); return This->name(hwnd, uMsg, w, lParam); }
#define MEMBER_DLGPROC(type, name, func) \
	ALWAYS_INLINE INT_PTR name(HWND hwnd, UINT uMsg, WPARAM w, LPARAM lParam); \
	static INT_PTR CALLBACK c##name(HWND hwnd, UINT uMsg, WPARAM w, LPARAM lParam) { \
		INIT_DLG_CONTEXT(type, func); return This->name(hwnd, uMsg, w, lParam); }
#define MEMBER_DLGPROC2(t, n) MEMBER_DLGPROC(t,n, This->MACRO_CAT(n,Init)(hwnd))
		
// message handling macros
#define DLGMSG_SWITCH(cse, def) { LONG_PTR msgResult = 0; HWND& sender = *(HWND*)&lParam; \
	switch(uMsg) { cse; default: switch(uMsg) { def; default: return FALSE; }} \
	if(msgResult) { SetWindowLongPtr(hwnd, DWL_MSGRESULT, msgResult); } return TRUE; }
#define WNDMSG_SWITCH(cse, def) { LONG_PTR msgResult = 0; HWND& sender = *(HWND*)&lParam; \
	switch(uMsg) { cse; default: switch(uMsg) { def; default: return DefWindowProc( \
		hwnd, uMsg, wParam, lParam); }} return msgResult; }
#define CASE_COMMAND(cse, def) case WM_COMMAND: { HWND& sender = *(HWND*)&lParam; \
	switch(wParam) { cse; default: switch(uMsg) { def; default: break; }}} break;
#define CASE_NOTIFY(cse, def) case WM_NOTIFY: { NMHDR& hdr = *(NMHDR*)lParam; switch( \
	hdr.idFrom | (hdr.code<<16)) { cse; default: switch(uMsg) { def; default: break; }}} break;

// basic handlers
#define ON_MESSAGE(msg, f) case msg: { f; break; }
#define ON_MSGRNG(m1, m2, f) case m1 ... m2: { f; break; }
#define OM_MOUSEMSG(f) ON_MSGRNG(WM_MOUSEFIRST, WM_MOUSELAST, f)
#define CASE_XY(x, y) case MAKELPARAM(y, x):
#define ON_CONTROL(nc, id, f) case MAKELPARAM(id, nc): { f; break; }
#define ON_COMMAND(id, f) ON_CONTROL(0, id, f)	
#define ON_NOTIFY(nc, id, f) ON_CONTROL(nc, id, f)
#define ON_CONTROL_RANGE(nc, id, id2, f) case MAKELPARAM(id, nc) ... MAKELPARAM(id2, nc): \
	{ int index = LOWORD(wParam)-id; f; break; }
#define ON_NOTIFY_RANGE(nc, id, id2, f) case MAKELPARAM(id, nc) ... MAKELPARAM(id2, nc): \
	{ int index = hdr.idFrom -id; f; break; }
#define ON_COMMAND_RANGE(id, id2, f) ON_CONTROL_RANGE(0, id, id2, f)
#define ON_RADIO_RNG(id, id2, f) ON_COMMAND_RANGE(id, id2, \
	if(IsButtonChecked((HWND)lParam)) f; )

// WM_CTLCOLOR
#define ON_MESSAGE0(msg, f) case msg: { f; return 0; }
#define ON_CTLCOLORSTATIC(f) ON_MESSAGE0(WM_CTLCOLORSTATIC,f)
#define ON_CTLCOLOREDIT(f) ON_MESSAGE0(WM_CTLCOLOREDIT,f)
#define ON_CTLCOLORBTN(f) ON_MESSAGE0(WM_CTLCOLORBTN,f)

// listview handlers
#define ON_LVN_NOTIFY(nc, id, f) ON_NOTIFY(nc, id, \
	NMLISTVIEW& nmv = *(LPNMLISTVIEW)lParam; f)
#define ON_LVN_ITEMACT(nc, id, f) ON_NOTIFY(nc, id, \
	NMITEMACTIVATE& nmv = *(LPNMITEMACTIVATE)lParam; f)
#define ON_LVN_KEYDOWN(id, f) ON_NOTIFY(LVN_KEYDOWN, id, \
	NMLVKEYDOWN& nmv = *(LPNMLVKEYDOWN)lParam; f)
#define ON_LVN_STATECHG(id, f) ON_LVN_NOTIFY(LVN_ITEMCHANGED, id, \
	if(nmv.uChanged & LVIF_STATE) { f; } )
	
// message reflection
#include <olectl.h>
#define REFLECT_DRAWITEM ON_MESSAGE(WM_DRAWITEM, drawItemReflect(lParam))
static void drawItemReflect(LPARAM lParam) {
	LPDRAWITEMSTRUCT lpDIS = (LPDRAWITEMSTRUCT) lParam;
	SendMessageW(lpDIS->hwndItem, OCM_DRAWITEM, 0, lParam); }
