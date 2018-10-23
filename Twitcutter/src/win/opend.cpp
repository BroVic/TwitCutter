// opend.cpp

#include "opend.h"

// Reads the content of a text file
BOOL LoadTextFileToEdit(HWND hwnd, LPCTSTR pszFileName)
{
	BOOL bSuccess = false;
	HANDLE hFile = CreateFile(pszFileName, GENERIC_READ, FILE_SHARE_READ,
		NULL, OPEN_EXISTING, 0, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		DWORD dwFileSize = GetFileSize(hFile, NULL);
		if (dwFileSize != 0xFFFFFFFF)
		{
			LPSTR pszFileText = static_cast<LPSTR>(GlobalAlloc(GPTR, dwFileSize + 1));
			if (pszFileText != NULL)
			{
				DWORD dwRead;
				if (ReadFile(hFile, pszFileText, dwFileSize, &dwRead, NULL))
				{
					pszFileText[dwFileSize] = 0;    // null terminator
					if (SetWindowText(hwnd, pszFileText))
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