// message loop - include lines
int WINAPI simpleMsgLoop(void);
int WINAPI dialogMsgLoop(void);

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
