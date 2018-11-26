// resource.h

#ifndef _RESOURCE_H_INCLUDED_
#define _RESOURCE_H_INCLUDED_

#include <Windows.h>

/***
TODO: Instead of using .rc files, build menu(s)
at runtime and as such quit using these macros
and instead use compile-time constants.
*/

// Non-value
constexpr int idC_Static      = -1;

// Resources
constexpr int idR_AppMenu     = 101;
constexpr int idC_MainEdit    = 102;

// These values define individual
// dialog box resources.
constexpr int idD_About       = 103;
// constexpr int idD_AddFile  = 104;

// Icons
constexpr int idAppIcon       = 201;

// Menu commands
  // File menu
constexpr int idFileNew       = 1001;
constexpr int idFileOpen      = 1002;
constexpr int idFileSave      = 1003;
constexpr int idFileSaveAs    = 1004;
constexpr int idFileExit      = 1009;
  
  // Edit menu
constexpr int idEditCut       = 2001;
constexpr int idEditCopy      = 2002;
constexpr int idEditPaste     = 2003;
constexpr int idEditFind      = 2004;
constexpr int idEditReplace   = 2005;
constexpr int idEditClear     = 2006;

  // TwitCutter menu
constexpr int idTwitcutGen    = 3001;
constexpr int idTwitcutPost   = 3002;

  // View menu
constexpr int idView          = 4001;

  // Tools menu
constexpr int idToolsOptions  = 5001;

  // Help menu
constexpr int idHelpView      = 6001;
constexpr int idHelpReport    = 6002;
constexpr int idHelpPrivacy   = 6003;
constexpr int idHelpUpdate    = 6004;
constexpr int idHelpAbout     = 6005;


// Dialog Box(es)
BOOL CALLBACK AboutDlgProc(HWND, UINT, WPARAM, LPARAM);
#endif // !_RESOURCE_H_INCLUDED_
