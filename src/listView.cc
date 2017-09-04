// listview helpers - include lines
void WINAPI lstView_insColumn(HWND hList, int index, int width, const char* name);


#define _LSTVW_F1_(CT, LT) \
int WINAPI lstView_iosText(HWND hList, int item, const CT* text, int iSub, LT* lvi, int mask); \
int WINAPI lstView_iosText(HWND hList, int item, const CT* text); \
int WINAPI lstView_iosText(HWND hList, int item, const CT* text, LPARAM data); \
int WINAPI lstView_iosText(HWND hList, int item, const CT* text, LPARAM data, int img); \
int WINAPI lstView_iosText(HWND hList, int item, int iSub, const CT* text); 
_LSTVW_F1_(char, LVITEMA); _LSTVW_F1_(WCHAR, LVITEMW);

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
int WINAPI listView_getFocus(HWND hList);
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
	
int WINAPI lstView_iosText(HWND hList, int item, 
	const WCHAR* text, int iSub, LVITEMW* lvi, int mask)
{
	lvi->mask = mask; lvi->pszText = (WCHAR*)text;
	int msg = LVM_SETITEMW; if(!(lvi->iSubItem = iSub)){
		u32 count = sendMessage(hList, LVM_GETITEMCOUNT);
		if(item >= count) { item = min(item & INT_MAX, count);
			msg = LVM_INSERTITEMW; }} lvi->iItem = item;
	ARGFIX(hList); sendMessageL(hList, msg, (LPARAM)lvi); return item;
}

int WINAPI lstView_iosText(HWND hList, int item, const char* text,
	int iSub, LVITEMA* lvi, int mask)
{
	SCOPE_EXIT(free(lvi->pszText));	return lstView_iosText(hList,
	item, utf816_dup(text).data, iSub, (LVITEMW*)lvi, mask);
}

#define _LSTVW_I1_(CT, LT) \
int WINAPI lstView_iosText(HWND hList, int item, const CT* text) { \
	LT lvi; return lstView_iosText(hList, item, text, 0, &lvi, LVIF_TEXT); } \
int WINAPI lstView_iosText(HWND hList, int item, int iSub, const CT* text) {\
	LT lvi; return lstView_iosText(hList, item, text, iSub, &lvi, LVIF_TEXT); }\
int WINAPI lstView_iosText(HWND hList, int item, const CT* text, LPARAM data) { \
	LT lvi; lvi.lParam = data; \
	return lstView_iosText(hList,item, text, 0, &lvi, LVIF_TEXT|LVIF_PARAM); }\
int WINAPI lstView_iosText(HWND hList, int item, const CT* text, LPARAM data, int img) { \
	LT lvi; lvi.lParam = data; lvi.lParam = data; lvi.iImage = img; \
	return lstView_iosText(hList, item, text, 0, &lvi, LVIF_TEXT|LVIF_PARAM|LVIF_IMAGE); }
_LSTVW_I1_(char, LVITEMA); _LSTVW_I1_(WCHAR, LVITEMW); 
	
void WINAPI lstView_iosInt(HWND hList, int item, int subItem, int val) { WCHAR buff[32];
	_itow(val, buff, 10); lstView_iosText(hList, item, subItem, buff); }
void WINAPI lstView_iosInt(HWND hList, int item, int val, LPARAM data) { WCHAR buff[32];
	_itow(val, buff, 10); lstView_iosText(hList, item, buff, data); }
void WINAPI lstView_setData(HWND hList, int item, LPARAM data) { LVITEMW lvi; lvi.mask 
	= LVIF_PARAM; lvi.lParam = data; sendMessageL(hList, LVM_SETITEMW, (LPARAM)&lvi); }
	
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
	int tmp = ListView_GetItemCount(hList)-1; if(item > tmp) item = tmp;
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
int WINAPI listView_getFocus(HWND hList) {
	return ListView_GetNextItem(hList, -1, LVIS_FOCUSED); }
void WINAPI listView_setFocus(HWND hList, int item) {
	ListView_SetItemState(hList, item, LVIS_FOCUSED, LVIS_FOCUSED); }
