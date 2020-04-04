#include <windows.h>
#include "drawItem.h"

void drawItem_focus(DRAWITEMSTRUCT* di)
{
	if(di->itemAction != ODA_SELECT) {
		if((di->itemState & ODS_SELECTED)
		&&(!(di->itemState & ODS_NOFOCUSRECT)))
			DrawFocusRect(di->hDC, &di->rcItem);
	}
}

void drawItem_erase(DRAWITEMSTRUCT* di)
{
	PatBlt(di->hDC, di->rcItem.left, di->rcItem.top, 
		di->rcItem.right-di->rcItem.left, 
		di->rcItem.bottom-di->rcItem.top, 
		PATCOPY);
}

void DrawItem_Color::lbInit(DRAWITEMSTRUCT* di)
{
	int nTextColor;
	
	if(di->itemState & (ODS_SELECTED|ODS_DISABLED))
	{
		int nTextColor = COLOR_GRAYTEXT;
		if(di->itemState & ODS_SELECTED) {
			brSave = SelectObject(di->hDC, SYSHBR(HIGHLIGHT)); 
			rgbBkSave = SetBkColor(di->hDC, SYSRGB(HIGHLIGHT));
			nTextColor = COLOR_HIGHLIGHTTEXT;	}
		rgbSave = SetTextColor(di->hDC, GetSysColor(nTextColor)); 
	}
	
	drawItem_erase(di);
}

void DrawItem_Color::restore(DRAWITEMSTRUCT* di)
{
	if(!brSave) return;
	SelectObject(di->hDC, brSave);
	SetTextColor(di->hDC, rgbSave);
	SetBkColor(di->hDC, rgbBkSave);
}
