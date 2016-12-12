// rectpnt - include lines
#define RECT_XY(rc) (rc).left, (rc).top
#define RECT_WH(rc) (rc).right-(rc).left, (rc).bottom-(rc).top
#define RECT_LTRB(rc) RECT_XY(rc), (rc).right, (rc).bottom
#define RECT_XYWH(rc)  RECT_XY(rc), RECT_WH(rc)
#define XYWH_LTRB(rc) (rc).x, (rc).y, XYWH_R(rc), XYWH_B(rc)
static LONG RECT_W(RECT& rc) { return rc.right-rc.left; }
static LONG RECT_H(RECT& rc) { return rc.bottom-rc.top; }
static void setSize(RECT* rc, int width, int height) {
	rc->right = rc->left + width; rc->bottom = rc->top + height; }
bool WINAPI RectInRect(const RECT *big, const RECT *Small);
static POINT lParamToPnt(LPARAM lParam) { return POINT {
	GET_X_LPARAM(lParam),  GET_Y_LPARAM(lParam) }; }	
struct XYWH { LONG x, y, w, h; };
static LONG XYWH_R(XYWH& rc) { return rc.x+rc.w; }
static LONG XYWH_B(XYWH& rc) { return rc.y+rc.h; }

// rectpnt - source lines
bool WINAPI RectInRect(const RECT *big, const RECT *Small) {
	return (big->left <= Small->left) && (big->right >= Small->right)
		&& (big->top <= Small->top) && (big->bottom >= Small->bottom); }
	