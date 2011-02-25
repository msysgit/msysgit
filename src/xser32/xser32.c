/* fake clipboard routines for sh.exe not to load user32.dll */
#include <windef.h>

__declspec(dllexport)
BOOL WINAPI OpenClipboard(HWND hWndNewOwner)
{
    return FALSE;   /* always fails */
}

__declspec(dllexport)
BOOL WINAPI CloseClipboard(void)
{
    return TRUE;    /* ok */
}

__declspec(dllexport)
HANDLE WINAPI GetClipboardData(UINT uFormat)
{
    return NULL;    /* always fail */
}



BOOL APIENTRY DllMain (HINSTANCE hInst, DWORD reason, LPVOID reserved)
{
    return TRUE;
}
