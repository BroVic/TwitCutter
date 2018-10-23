// abtd.cpp

#include "abtd.h"

// 'About' Dialog Procedure
BOOL CALLBACK AboutDlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:

		return true;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			EndDialog(hwnd, IDOK);
		}
		break;
	default:
		return false;
	}
	return true;
}
