// winprc.cpp

#include "winprc.h"


// Main Window Prodedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
		HWND hEdit;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_FILE_EXIT:
			PostMessage(hwnd, WM_CLOSE, 0, 0);
			break;
		case ID_FILE_OPEN:
		{
			OPENFILENAME ofn;
			char szFileName[MAX_PATH] = "";
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);  // SEE NOTE BELOW
			ofn.hwndOwner = hwnd;
			ofn.lpstrFilter = "Test Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
			ofn.lpstrFile = szFileName;
			ofn.nMaxFile = MAX_PATH;
			ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
			ofn.lpstrDefExt = "txt";

			if (GetOpenFileName(&ofn))
			{
				hEdit = GetDlgItem(hwnd, IDC_MAIN_UI);
				if (!LoadTextFileToEdit(hEdit, szFileName))
				{
					MessageBox(hwnd, "Could not read from text file.", "Error",
						MB_OK | MB_ICONINFORMATION);
				}
			}
		}
		case ID_HELP_ABOUT:
		{
			int ret = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_ABOUTDIALOG), hwnd, AboutDlgProc);
			if (ret == -1)
			{
				MessageBox(hwnd, "Dialog failed!", "Error", MB_OK | MB_ICONINFORMATION);
			}
		}
		break;
		default:
			break;
		}
	case WM_CREATE:
	{
		// Create edit control
		hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "",
			WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOVSCROLL,
			0, 0, 100, 100, hwnd, reinterpret_cast<HMENU>(IDC_MAIN_UI), GetModuleHandle(NULL), NULL);
		if (hEdit == nullptr)
		{
			MessageBox(hwnd, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);
		}

		HFONT hfDefault = static_cast<HFONT>(GetStockObject(DEFAULT_GUI_FONT));
		SendMessage(hwnd, WM_SETFONT, reinterpret_cast<WPARAM>(hfDefault), MAKELPARAM(false, 0));
	}
	break;
	case WM_SIZE:
	{
		RECT rcClient;
		GetClientRect(hwnd, &rcClient);
		hEdit = GetDlgItem(hwnd, IDC_MAIN_UI);
		SetWindowPos(hEdit, NULL, 0, 0, rcClient.right, rcClient.bottom, SWP_NOZORDER);
	}
	break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}
