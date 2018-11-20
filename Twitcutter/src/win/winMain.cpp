 // winMain.cpp

// Entry point for graphic user interface
#include "winMain.h"
#include "dllclnt.h"

static      WDim appDefs{}; // file scope
const auto  appName = appDefs.get_appName();
const auto  className = appDefs.get_mainWinClass();

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	constexpr int failWndReg = -1;
	constexpr int failWndCreate = -2;

	if (!register_winclass(hInstance, className))
	{
		MessageBox(
			nullptr,
			"Window Registration Failed!",
			"Error",
			MB_ICONEXCLAMATION | MB_OK);
		return failWndReg;
	}
	HWND hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		className,
		appName,
		WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		300,
		300, 
		nullptr,
		nullptr,
		hInstance,
		nullptr);
	if (!hwnd)
	{
		MessageBox(
			nullptr,
			"Window creation failed!", 
			"Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return failWndCreate;
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	MSG msg{};
	while (GetMessage(&msg, nullptr, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

// Register window class
bool register_winclass(HINSTANCE hInstance, const char* className)
{
	// Note that we are using uniform initialization for the
	// WNDCLASSEX instance. Thus, members 'style', 'cbClsExtra'
	// and 'cbWndExtra' evaluate to 0.
	WNDCLASSEX wc{};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW);
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_APPMENU);
	wc.lpszClassName = className;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
	{
		return false;
	}
	return true;
}

// Main Window Prodedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hEdit{};

	switch (message)
	{
	case WM_CREATE:
		hEdit = init_edit_control(hwnd, appDefs);
		break;
	case WM_SIZE:
		size_edit_cntrl(hwnd, appDefs, hEdit);
		break;
	case WM_COMMAND:
		use_command_options(hwnd, hEdit, wParam);
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

// Implementation of the WM_COMMAND message
void use_command_options(const HWND hwnd, HWND hEdit, WPARAM wParam)
{
	static TwitPrinter printer{};
	static TwitterClient tc{};

	switch (LOWORD(wParam))
	{
	case ID_FILE_EXIT:
		PostMessage(hwnd, WM_CLOSE, 0, 0);
		break;
	case ID_FILE_OPEN:
		create_openfile_dlg(hwnd, hEdit);   // TODO: Fix these arguments!
		break;
	case ID_TWITCUT_GEN:
		generate_tweets(hEdit, printer);
		break;
	case ID_TWITCUT_POST:
		if (tc.transferred_tweets(printer.get_chain()))
		{
			tc.post_all_tweets();
			//post(hEdit, tc);   // TODO: Disable if nothing loaded in control
		}
		break;
	case ID_HELP_ABOUT:
		create_about_dialog(hwnd);
		break;
	default:
		break;
	}
}

// Creates an edit control for the main app window
HWND init_edit_control(const HWND hwnd, const WDim& dim)
{
	HWND editHndl = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		editName.c_str(),
		emptyString.c_str(),
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL,
		dim.getX(),
		dim.getY(),
		dim.getWidth(),
		dim.getHeight(),
		hwnd,
		reinterpret_cast<HMENU>(IDC_MAIN_EDIT),
		GetModuleHandle(NULL),
		nullptr);
	if (!editHndl)
	{
		MessageBox(
			hwnd,
			"Could not create edit control.",
			"Error",
			MB_OK | MB_ICONERROR);
	}

	auto hfDefault = static_cast<HFONT>(GetStockObject(DEFAULT_GUI_FONT));
	SendMessage(
		editHndl,
		WM_SETFONT,
		reinterpret_cast<WPARAM>(hfDefault),
		MAKELPARAM(FALSE, 0));
	return editHndl;
}

// Ensures the proper sizing of the edit control
void size_edit_cntrl(const HWND hwnd, const WDim& dim, HWND editHndl)
{
	RECT rcClient{};
	GetClientRect(hwnd, &rcClient);
	editHndl = GetDlgItem(hwnd, IDC_MAIN_EDIT);
	SetWindowPos(
		editHndl,
		NULL,
		dim.getX(),
		dim.getY(),
		rcClient.right,
		rcClient.bottom,
		SWP_NOZORDER);
}

// Creates a common dialog box for opening files
void create_openfile_dlg(const HWND hwnd, HWND editHndl)
{
	char szFileName[MAX_PATH] = "";

	OPENFILENAME ofn{};
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
}

// Reads the content of a text file
BOOL LoadTextFileToEdit(const HWND hndl, const OPENFILENAME& obj)
{
	auto bSuccess = false;
	auto hFile = CreateFile(
		obj.lpstrFile,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);
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
		MessageBox(hwnd,
			"Dialog failed!",
			"Error",
			MB_OK | MB_ICONINFORMATION);
	}
}

// Generates the tweets
void generate_tweets(HWND hwnd, TwitPrinter& printer)
{
	std::string tmp{};
	// collect text from the control
	int txtLen = GetWindowTextLength(hwnd);
	if (txtLen)
	{
		char* buf = new (std::nothrow) char[txtLen];
		if (buf)
		{
			if (GetWindowText(hwnd, buf, txtLen))
			{
				std::string tmp = buf;
				if (!tmp.empty())
				{
					printer.set_fulltxt(tmp);
				}
			}
			// Check with GetLastError
		}
		delete[] buf;
	}
	// process the text into tweets
	printer.mkChain();
	// send tweets to the control
	tmp.clear();
	std::vector<std::string>  chain = printer.get_chain();
	for (auto twt : chain)
	{
		tmp.append(twt);
		tmp.append(separator);
	}

	display_text(hwnd, tmp.c_str());
}

// Displays test in the edit control
void display_text(const HWND hwnd, const char* str)
{
	if (SetWindowText(hwnd, str))
	{
		// Check with GetLastError, etc.
		MessageBox(
			hwnd,
			"All tweets were displayed in the window",
			"Success!",
			MB_OK | MB_ICONINFORMATION);
	}
	else
	{
		MessageBox(
			hwnd,
			"Could not display tweets in the window",
			"Error!",
			MB_OK | MB_ICONERROR);
	}
}
