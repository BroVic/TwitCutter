// winMain.cpp

// Entry point for graphic user interface

#include "winprc.h"


const char g_szClassName[] = "TwitCutterWindowClass";
bool register_winclass(HINSTANCE);

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	constexpr int failWndReg = -1;
	constexpr int failWndCreate = -2;

	if (!register_winclass(hInstance))
	{
		MessageBox(
			nullptr,
			"Window Registration Failed!",
			"Error",
			MB_ICONEXCLAMATION | MB_OK);
		return failWndReg;
	}

	// Create window
	HWND hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		"TwitCutter",
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

	// Message loop
	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}


// Register window class
bool register_winclass(HINSTANCE hInstance)
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
	wc.lpszClassName = g_szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
	{
		return false;
	}
	return true;
}