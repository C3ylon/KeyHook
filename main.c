#include <stdio.h>
#include <Windows.h>
#include <conio.h>

int main(void) 
{	
    HMODULE hDll = LoadLibraryA("hook.dll");
    if( hDll == NULL )
    {
        printf("LoadLibrary(%s) failed!!! [%d]", "hook.dll", (int)GetLastError());
        return -1;
    }
    int(*SetHook)(void) = (void*)GetProcAddress(hDll, "SetHook");
    void(*HookStop)(void) = (void*)GetProcAddress(hDll, "HookStop");
    int wrongcode= SetHook();
    switch(wrongcode)
    {
        case 1:
            printf("[!]hWnd == NULL\n");
            FreeLibrary(hDll);
	        return -1;
        case 2:
            printf("[!]threadid == 0\n");
            FreeLibrary(hDll);
	        return -1;
        case 3:
            printf("[!]hHook == NULL\n");
            FreeLibrary(hDll);
	        return -1;
    }
    while( _getch() != 'q' );
    HookStop();
    FreeLibrary(hDll);
	return 0;
}
