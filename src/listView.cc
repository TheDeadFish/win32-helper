// listview helpers - include lines
void WINAPI lstView_insColumn(HWND hList, int index, int width, const char* name);
void WINAPI lstView_iosItem(HWND hList, int item, int subItem, LVITEMA* lvi);
void WINAPI lstView_iosItem(HWND hList, int item, int subItem, LVITEMW* lvi);
void WINAPI lstView_iosText(HWND hList, int item, int subItem, const char* text);
void WINAPI lstView_iosText(HWND hList, int item, int subItem, const char* text, LPARAM data);
void WINAPI lstView_iosText(HWND hList, int item, int subItem, const WCHAR* text);
void WINAPI lstView_iosText(HWND hList, int item, int subItem, const WCHAR* text, LPARAM data);
void WINAPI lstView_iosInt(HWND hList, int item, int subItem, int val);
void WINAPI lstView_iosInt(HWND hList, int item, int subItem, int val, LPARAM data);
void WINAPI lstView_setData(HWND hList, int item, LPARAM data);
bool WINAPI lstView_getItem(HWND hList, int item, int subItem, LVITEMW* lvi);
LPARAM WINAPI lstView_getText(HWND hList, int item, int subItem, WCHAR* text, int max);
LPARAM WINAPI lstView_getData(HWND hList, int item);

// selection/focus
int WINAPI listView_getCurSel(HWND hList);
void WINAPI listView_setCurSel(HWND hList, int item);
int WINAPI listView_getSel(HWND hList, int item);
int WINAPI listView_nextSel(HWND hList, int iStart);
void WINAPI listView_setSel(HWND hList, int item, BOOL bSelect);
void WINAPI listView_setFocus(HWND hList, int item);

#define lstView_insText(a,b,c) lstView_iosText(a,(b)|0x80000000,0,c)
#define lstView_insTxtDat(a,b,c,d) lstView_iosText(a,(b)|0x80000000,0,c,d)
#define lstView_insInt(a,b,c) lstView_iosInt(a,(b)|0x80000000,0,c)
#define lstView_insIntDat(a,b,c,d) lstView_iosInt(a,(b)|0x80000000,0,c,d)

// listview helpers - source lines
void WINAPI lstView_insColumn(HWND hList, int index, int width, const char* name) {
	LVCOLUMNA LvCol; LvCol.mask=LVCF_TEXT|LVCF_WIDTH|LVCF_SUBITEM;
	LvCol.cx=width;	LvCol.pszText=(char*)name;
	SendMessage(hList,LVM_INSERTCOLUMNA,index,(LPARAM)&LvCol); }

#define lstView_iosItem_(set, ins, type) \
void WINAPI lstView_iosItem(HWND hList, int item, int subItem, type* lvi) { \
	lvi->iSubItem = subItem; int msg = set;	if((subItem == 0)&&(((item < 0) \
	&&(item &= INT_MAX, 1))||(item >= ListView_GetItemCount(hList)))) msg = ins; \
	lvi->iItem = item; SendMessage(hList, msg, 0, (LPARAM)lvi); asm(""); }
	
lstView_iosItem_(LVM_SETITEMW, LVM_INSERTITEMW, LVITEMW);
void WINAPI lstView_iosText(HWND hList, int item, int subItem, const WCHAR* text) {
	LVITEMW lvi; lvi.mask = LVIF_TEXT; lvi.pszText = (WCHAR*)text; 
	lstView_iosItem(hList, item, subItem, &lvi); }
void WINAPI lstView_iosText(HWND hList, int item, int subItem, const WCHAR* text, LPARAM data) {
	LVITEMW lvi; lvi.mask = LVIF_TEXT|LVIF_PARAM; lvi.pszText = (WCHAR*)text; lvi.lParam = data;
	lstView_iosItem(hList, item, subItem, &lvi); }
void WINAPI lstView_iosInt(HWND hList, int item, int subItem, int val) { char buff[32];
	sprintf(buff, "%d", val); lstView_iosText(hList, item, subItem, buff); }
void WINAPI lstView_iosInt(HWND hList, int item, int subItem, int val, LPARAM data) { char buff[32];
	sprintf(buff, "%d", val); lstView_iosText(hList, item, subItem, buff, data); }
void WINAPI lstView_setData(HWND hList, int item, LPARAM data) { LVITEMW lvi; 
	lvi.mask = LVIF_PARAM; lvi.lParam = data; lstView_iosItem(hList, item, 0, &lvi); }
	
// listView reading
bool WINAPI lstView_getItem(HWND hList, int item, int subItem, LVITEMW* lvi) {
	lvi->iItem = item; lvi->iSubItem = subItem;
	return SendMessage(hList, LVM_GETITEMW, 0, (LPARAM)lvi); }
LPARAM WINAPI lstView_getText(HWND hList, int item, int subItem, WCHAR* text, int max) {
	LVITEMW lvi; lvi.mask = LVIF_TEXT | LVIF_PARAM; lvi.pszText = text;
	lvi.cchTextMax = max; lstView_getItem(hList, item, subItem, &lvi); return lvi.lParam; }
LPARAM WINAPI lstView_getData(HWND hList, int item) { LVITEMW lvi; lvi.mask = LVIF_PARAM;
	lstView_getItem(hList, item, 0, &lvi); return lvi.lParam; }
	
// single-item selection
int WINAPI listView_getCurSel(HWND hList) {
	return listView_nextSel(hList, -1); }
void WINAPI listView_setCurSel(HWND hList, int item) 
{
	// deselect current selection
	for(int curItem = -1; (curItem = listView_nextSel(
		hList, curItem)) < 0;) { if(curItem != item)
		listView_setSel(hList, curItem, FALSE); }
		
	// select new item
	item = min(item, ListView_GetItemCount(hList)-1); 
	if(item >= 0) { ListView_SetItemState(hList, item,
		LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED); }
}
	
// mutli-item selection
int WINAPI listView_getSel(HWND hList, int item) {
	return ListView_GetItemState(hList, item, LVIS_SELECTED); }
int WINAPI listView_nextSel(HWND hList, int iStart) {
	return ListView_GetNextItem(hList, iStart, LVIS_SELECTED); }
void WINAPI listView_setSel(HWND hList, int item, BOOL bSelect) {
	ListView_SetItemState(hList, item, bSelect ? LVIS_SELECTED : 0, LVIS_SELECTED); }
void WINAPI listView_setFocus(HWND hList, int item) {
	ListView_SetItemState(hList, item, LVIS_FOCUSED, LVIS_FOCUSED); }
	
// listview helpers (ANSI) - source lines
lstView_iosItem_(LVM_SETITEMA, LVM_INSERTITEMA, LVITEMA);
void WINAPI lstView_iosText(HWND hList, int item, int subItem, const char* text) {
	LVITEMA lvi; lvi.mask = LVIF_TEXT; lvi.pszText = (char*)text; 
	lstView_iosItem(hList, item, subItem, &lvi); }
void WINAPI lstView_iosText(HWND hList, int item, int subItem, const char* text, LPARAM data) {
	LVITEMA lvi; lvi.mask = LVIF_TEXT|LVIF_PARAM; lvi.pszText = (char*)text; lvi.lParam = data;
	lstView_iosItem(hList, item, subItem, &lvi); }
