// winprc.cpp

#include "winprc.h"


// Main Window Prodedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hEdit;
	switch (message)
	{
	case WM_CREATE:
	{
		hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "",
			WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
			0, 0, 100, 100, hwnd, reinterpret_cast<HMENU>(IDC_MAIN_EDIT), GetModuleHandle(NULL), NULL);
		if (hEdit == nullptr)
		{
			MessageBox(hwnd, "Could not create edit control.", "Error", MB_OK | MB_ICONERROR);
		}

		auto hfDefault = static_cast<HFONT>(GetStockObject(DEFAULT_GUI_FONT));
		SendMessage(hEdit, WM_SETFONT, reinterpret_cast<WPARAM>(hfDefault), MAKELPARAM(FALSE, 0));
	}
	break;
	case WM_SIZE:
	{
		RECT rcClient;
		GetClientRect(hwnd, &rcClient);
		hEdit = GetDlgItem(hwnd, IDC_MAIN_EDIT);
		SetWindowPos(hEdit, NULL, 0, 0, rcClient.right, rcClient.bottom, SWP_NOZORDER);
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_FILE_EXIT:
			PostMessage(hwnd, WM_CLOSE, 0, 0);
			break;
		case ID_FILE_OPEN:
			create_openfile_dlg(hwnd, hEdit);
			break;
		case ID_HELP_ABOUT:
			create_about_dialog(hwnd);
			break;
		default:
			break;
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


// Creates a common dialog box for opening files
void create_openfile_dlg(HWND hwnd, HWND editHndl)
{
	char szFileName[MAX_PATH] = "";
	
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFilter = "Word 97-2003 Documents (*.doc)\0*.doc\0All Files (*.*)\0*.*\0";
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = "doc";

	if (GetOpenFileName(&ofn))
	{
		Receiver jobIn{};
		jobIn.startJob(ofn.lpstrFile);

		MasterSelector sel{};
		SetWindowText(editHndl, sel.enable_options(jobIn).c_str());
		/*if (!LoadTextFileToEdit(editHndl, ofn))
		{
			MessageBox(hwnd, "Could not read from the opened file.", "Error",
				MB_OK | MB_ICONINFORMATION);
		}*/
	}
	else
	{
		MessageBox(hwnd, "Could not open the file.", "Error!",
			MB_OK | MB_ICONINFORMATION);
	}
}

// Reads the content of a text file
BOOL LoadTextFileToEdit(const HWND hndl, const OPENFILENAME& obj)
{
	auto bSuccess = false;
	auto hFile = CreateFile(obj.lpstrFile, GENERIC_READ, FILE_SHARE_READ,
		NULL, OPEN_EXISTING, 0, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		auto dwFileSize = GetFileSize(hFile, NULL);
		if (dwFileSize != 0xFFFFFFFF)
		{
			auto pszFileText = static_cast<LPSTR>(GlobalAlloc(GPTR, dwFileSize + 1));
			if (pszFileText != NULL)
			{
				DWORD dwRead{};
				if (ReadFile(hFile, pszFileText, dwFileSize, &dwRead, NULL))
				{
					pszFileText[dwFileSize] = nullterminator;
					if (SetWindowText(hndl, pszFileText))
					{
						bSuccess = true;
					}
				}
				GlobalFree(pszFileText);
			}
		}
		CloseHandle(hFile);
	}
	return bSuccess;
}

void create_about_dialog(HWND hwnd)
{
	auto ret = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_ABOUT), hwnd, AboutDlgProc);
	if (ret == -1)
	{
		MessageBox(hwnd, "Dialog failed!", "Error", MB_OK | MB_ICONINFORMATION);
	}
}