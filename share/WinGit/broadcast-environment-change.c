#include <windows.h>

int main(int argc, char **argv)
{
	DWORD result;
	return !SendMessageTimeout(HWND_BROADCAST, WM_SETTINGCHANGE,
		0, (LPARAM)"Environment", SMTO_ABORTIFHUNG, 500, &result);
}
