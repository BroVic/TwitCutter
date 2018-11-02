// winMain.cpp

// Entry point for graphic user interface

#include "winprc.h"

const char g_szClassName[] = "twitcutterWindowClass";
bool register_winclass(HINSTANCE);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (!register_winclass(hInstance))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error", MB_ICONEXCLAMATION | MB_OK);
		return -1;
	}

	// Create window
	HWND hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, g_szClassName, "TwitCutter", WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, CW_USEDEFAULT, 300, 300, 
		NULL, NULL, hInstance, NULL);
	if (hwnd == nullptr)
	{
		MessageBox(NULL, "Window creation failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return -2;
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// Message loop
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}


// Register window class
bool register_winclass(HINSTANCE hInstance)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
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