// winprc.h

#ifndef _WINPRC_H_INCLUDED_
#define _WINPRC_H_INCLUDED_

#include <stdio.h>
#include <Windows.h>
#include <string>
#include "resource.h"
#include "rcv.h"
#include "wdim.h"
#include "print.h"
#include "twclient.h"
#include "twfact.h"
#include "master.h"
#include "iodef.h"

// Character constants
constexpr char nullterminator = '\0';
const std::string separator{ "\r\n" };
const std::string emptyString{ "" };
const std::string editName{ "EDIT" };


// FUNCTION DEFINITIONS
// Window Class registration
bool register_winclass(HINSTANCE, const char*);

// The Main Window Procedure
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Implementation of the WM_COMMAND message
void use_command_options(const HWND, HWND, WPARAM);

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
void generate_tweets(HWND, TwitPrinter&);

// Displays test in the edit control
void display_text(const HWND, const char*);

#endif // !_WINPRC_H_INCLUDED_
