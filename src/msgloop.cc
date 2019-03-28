// message loop - include lines
int WINAPI simpleMsgLoop(void);
int WINAPI dialogMsgLoop(void);
int WINAPI dialogMsgPeek(void);


// message loop - source lines
int WINAPI simpleMsgLoop(void) { MSG Msg;
	while(GetMessage(&Msg, NULL, 0, 0) > 0)	{
		TranslateMessage(&Msg);	DispatchMessage(&Msg); 
	} return Msg.wParam; }
int WINAPI dialogMsgLoop(void) { MSG Msg;
	while(GetMessage(&Msg, NULL, 0, 0) > 0)	{
		if(!IsDialogMessage(GetActiveWindow(), &Msg)) 	{
			TranslateMessage(&Msg);	DispatchMessage(&Msg); 
	}} return Msg.wParam; }
	
int WINAPI dialogMsgPeek(void) { MSG Msg;
	while(PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE))	{
		if(Msg.message == WM_QUIT) {
			return Msg.wParam ? Msg.wParam : INT_MIN; }
		if(!IsDialogMessage(GetActiveWindow(), &Msg)) 	{
			TranslateMessage(&Msg);	DispatchMessage(&Msg); 
	}} return 0; 
}
