// winprc.h

#ifndef _WINPRC_H_INCLUDED_
#define _WINPRC_H_INCLUDED_

#include <Windows.h>
#include <string>
#include "resource.h"
#include "appset.h"
#include "abtd.h"
#include "print.h"


// Character constants
constexpr char nullterminator = '\0';
const std::string separator{ "\r\n" };
const std::string emptyString{ "" };
const std::string editName{ "EDIT" };

// The Main Window Procedure
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Creates an edit control for the main app window
HWND init_edit_control(const HWND, const WDim&);

// Ensures the proper sizing of the edit control
void size_edit_cntrl(const HWND, const WDim&, HWND);

// Opens a text file and reads it into memory
void create_openfile_dlg(const HWND, HWND);

// Read from a text file
BOOL LoadTextFileToEdit(const HWND, const OPENFILENAME&);

// Creates the 'About' dialog box
void create_about_dialog(const HWND);

// Generates the tweets
void generate_tweets(HWND);
#endif // !_WINPRC_H_INCLUDED_
