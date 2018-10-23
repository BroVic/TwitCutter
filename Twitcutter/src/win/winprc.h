// winprc.h

#ifndef _WINPRC_H_INCLUDED_
#define _WINPRC_H_INCLUDED_

#include <Windows.h>
#include "resource.h"
#include "abtd.h"
#include "opend.h"

constexpr unsigned int IDC_MAIN_UI = 101;

// The Main Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

// Read from a text file
BOOL LoadTextFileToEdit(HWND, LPCTSTR);

#endif // !_WINPRC_H_INCLUDED_
