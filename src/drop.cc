#include <stdshit.h>

cstr WINAPI ansi_to_utf8(cch* ansi, int len)
{
	WCHAR buff[2000];
	if(!MultiByteToWideChar(CP_ACP,0, 
		ansi, len, buff, sizeof(buff)))
	return {0,0}; return utf816_dup(buff);
}

#define _HDROP_READ_(nm, XT, CT, DP) \
 xarray<XT> WINAPI nm(const CT* p, const CT* e) \
{	xarray<XT> ret = {};; for(const CT* b;; p++) { b = p; \
	for(;; p++) { if(p >= e) return ret; if(!*p) break; } \
	if(p == b) return ret; rNew(ret.xnxalloc(),DP); } }

_HDROP_READ_(hDropReadW8, xstr, WCHAR, utf816_dup(b))
_HDROP_READ_(hDropReadA8, xstr, char, ansi_to_utf8(b,p-b))
_HDROP_READ_(hDropReadWW, wxstr, WCHAR, xstrdup(b))
_HDROP_READ_(hDropReadAW, wxstr, char, ansi_to_wide_dup(b,p-b))

#define _HDROP_GET_(nm, xt, fw, fa) \
xarray<xt> WINAPI nm(HANDLE hDrop) \
{ \
	/* validate DROPFILES header */ \
	size_t blockSize = GlobalSize(hDrop); \
	DROPFILES* dropFiles = Void(GlobalLock(hDrop)); \
	SCOPE_EXIT(GlobalUnlock(hDrop)); \
	if((blockSize < sizeof(DROPFILES) \
	||(blockSize < dropFiles->pFiles))) return {0,0}; \
\
	/* get the dropFiles data*/ \
	Void begPos = Void(dropFiles, dropFiles->pFiles); \
	Void endPos = Void(dropFiles, blockSize); \
	return (dropFiles->fWide) ?  \
		fw(begPos, endPos-1) : fa(begPos, endPos); \
}

_HDROP_GET_(hDropGet, xstr, hDropReadW8, hDropReadA8);
_HDROP_GET_(hDropGetW, wxstr, hDropReadWW, hDropReadAW);
