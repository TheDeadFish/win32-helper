#include <stdshit.h>
#include "win32hlp.h"

#include "sendmsg.cc"
#include "children.cc"
#include "combobox.cc"
#include "radio-button.cc"
#include "tab-ctrl.cc"
#include "rectpnt.cc"
#include "updw-ctrl.cc"
#include "stdwndclss.cc"
#include "listView.cc"
#include "msgloop.cc"
#include "listBox.cc"
#include "inputbox.cc"

// win32hlp - source lines
void dlgButton_setCheck(HWND hwnd, int ctrlId, int state)
{
	CheckDlgButton(hwnd, ctrlId, 
		state ? BST_CHECKED : BST_UNCHECKED);
}
