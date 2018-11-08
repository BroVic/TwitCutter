// resource.h

#ifndef _RESOURCE_H_INCLUDED_
#define _RESOURCE_H_INCLUDED_

#include <Windows.h>
#include <winres.h>

/***
TODO: Instead of using .rc files, build menu(s)
at runtime and as such quit using these macros
and instead use compile-time constants.
*/

// Resources
#define IDR_APPMENU       101
#define IDC_MAIN_EDIT     102
  // These values define individual
  // dialog box resources.
#define IDD_ABOUT         103
#define IDD_ADDFILE       104

// Icons
#define IDI_APPICON       201

// Menu commands
  // File menu
#define ID_FILE_NEW       1001
#define ID_FILE_OPEN      1002
#define ID_FILE_SAVE      1003
#define ID_FILE_SAVEAS    1004
#define ID_FILE_EXIT      1009
  
  // Edit menu
#define ID_EDIT_CUT       2001
#define ID_EDIT_COPY      2002
#define ID_EDIT_PASTE     2003
#define ID_EDIT_FIND      2004
#define ID_EDIT_REPLACE   2005
#define ID_EDIT_CLEAR     2006

// TwitCutter menu
#define ID_TWITCUT_GEN    3001
#define ID_TWITCUT_POST   3002

  // View menu
#define ID_VIEW           4001

  // Tools menu
#define ID_TOOLS_OPTIONS  5001

  // Help menu
#define ID_HELP_VIEW      6001
#define ID_HELP_REPORT    6002
#define ID_HELP_PRIVACY   6003
#define ID_HELP_UPDATE    6004
#define ID_HELP_ABOUT     6005


// Dialog Box(es)
BOOL CALLBACK AboutDlgProc(HWND, UINT, WPARAM, LPARAM);
#endif // !_RESOURCE_H_INCLUDED_
