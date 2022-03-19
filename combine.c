#include <Windows.h>
#include <stdio.h>

#define WINDOWNAME L"Persona 4 Arena Ultimax"
// #define WINDOWNAME L"*无标题 - 记事本"
#define getbit(x, y)   ( (x) >> (y) & 1 ) 


HHOOK hHook;// __attribute__((section(".shr"), shared));
HMODULE g_hModule;

// __declspec(dllexport) 
int SetHook(void);
// __declspec(dllexport) 
void HookStop(void);


BOOL WINAPI DllMain(HMODULE hModule, DWORD wParam, LPVOID lpvReserved)
{
	switch( wParam )
	{
        case DLL_PROCESS_ATTACH:
			g_hModule = hModule;
			break;
        case DLL_PROCESS_DETACH:
			printf("[*]exit hook\n");
			break;	
	}
	return TRUE;
}

__declspec(dllexport) LRESULT (CALLBACK KeyboardProc)(int nCode, WPARAM wParam, LPARAM lParam) 
{
	if( nCode >= 0 )
	{
		if ( (int)getbit(lParam,31) == 0 )
		{
			switch(wParam)
			{
				case 0x51:
					keybd_event(0x53, 0, 0, 0);
					keybd_event(0x53, 0, KEYEVENTF_KEYUP, 0);
					keybd_event(0x44, 0, 0, 0);
					keybd_event(0x44, 0, KEYEVENTF_KEYUP, 0);
					return 1;
				case 0x45:
					keybd_event(0x53, 0, 0, 0);
					keybd_event(0x53, 0, KEYEVENTF_KEYUP, 0);
					keybd_event(0x41, 0, 0, 0);
					keybd_event(0x41, 0, KEYEVENTF_KEYUP, 0);
					return 1;
			}	
		}
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

__declspec(dllexport) int SetHook(void) 
{
    HWND hWnd = FindWindowW(NULL, WINDOWNAME);
	if (hWnd == NULL) return 1;
	DWORD __pid;
	DWORD threadid = GetWindowThreadProcessId(hWnd, &__pid);
	printf("[*]pid: %d\n", (unsigned int)__pid);
	if (threadid == 0) return 2;
    hHook = SetWindowsHookExW(WH_KEYBOARD, KeyboardProc, g_hModule, threadid);
	if (hHook == NULL) return 3;
	return 0;
}

__declspec(dllexport) void HookStop(void)
{
    if( hHook )
    {
        UnhookWindowsHookEx(hHook);
        hHook = NULL;
    }
}
