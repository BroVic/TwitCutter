// abtd.cpp

#include "resource.h"

// 'About' Dialog Procedure
BOOL CALLBACK AboutDlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
		return true;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK:
			EndDialog(hwnd, IDOK);
			break;
		default:
			break;
		}
	}
	break;
	default:
		return false;
	}
	return true;
}