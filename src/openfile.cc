// openfile - include lines
struct OpenFileName260_ : OPENFILENAME {
	TCHAR fileName[MAX_PATH+1]; void __thiscall init(DWORD Flags); };
struct OpenFileName260 : OpenFileName260_ { 
	OpenFileName260(); BOOL doModal(HWND hParent); };
struct SaveFileName260 : OpenFileName260_ {
	SaveFileName260(); BOOL doModal(HWND hParent); };
		
// openfile - source lines
void OpenFileName260_::init(DWORD Flags) {
	memset(&hInstance, 0, size_t(fileName+4)-size_t(&hInstance));
	this->Flags = Flags;  this->lStructSize = sizeof(OPENFILENAME);
	this->lpstrFile = fileName; this->nMaxFile = MAX_PATH; }
OpenFileName260::OpenFileName260() { init(OFN_FILEMUSTEXIST|OFN_HIDEREADONLY); }
SaveFileName260::SaveFileName260()  { init(OFN_PATHMUSTEXIST|OFN_OVERWRITEPROMPT); }
BOOL OpenFileName260::doModal(HWND hParent) {
	this->hwndOwner = hParent; return GetOpenFileName(this); }
BOOL SaveFileName260::doModal(HWND hParent) {
	this->hwndOwner = hParent; BOOL result = GetSaveFileName(this); 
	if(result && !nFileExtension && nFilterIndex) {
		LPCTSTR extPos = lpstrFilter; for(int i = 1; 
			i < nFilterIndex*2; i++) extPos += _tcslen(extPos)+1;
		int curPos = _tcslen(fileName);
		while(TCHAR ch = *++extPos) { if(ch == ';') break;
			if(curPos >= MAX_PATH) return FALSE;
			fileName[curPos++] = ch; } fileName[curPos] = '\0';
	} return result;
}
