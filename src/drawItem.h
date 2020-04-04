#pragma once

__stdcall void drawItem_erase(DRAWITEMSTRUCT* di);
__stdcall void drawItem_focus(DRAWITEMSTRUCT* di);

struct DrawItem_Color
{
	HGDIOBJ brSave=0;
	DWORD rgbSave;
	DWORD rgbBkSave;
	
	void lbInit(DRAWITEMSTRUCT* di);
	void restore(DRAWITEMSTRUCT* di);
};

#define SYSRGB(x) GetSysColor(COLOR_##x)
#define SYSHBR(x) GetSysColorBrush(COLOR_##x)
