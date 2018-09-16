// dtypes.h

// Definition of the major data types used

// PURPOSE:
// For consistency, those parts of this application that interact
// directly with Microsoft APIs will use the same nomenclature for
// basic data types. These have been defined in this file.

#ifndef DTYPES_H_INCLUDED
#define DTYPES_H_INCLUDED

#include <minwindef.h>


	/*using BYTE        = unsigned char;
	using USHORT      = unsigned short;
	using ULONG       = unsigned int;
	using ULONGLONG   = unsigned long long;
	using DWORD       = unsigned int;
	using CHAR        = signed char;
	using SHORT       = short;
	using LONG        = int;
	using WCHAR       = char16_t;
	using BOOL        = bool;
	using VOID        = void;
*/
	struct CLSID
	{
		ULONG Data1;
		USHORT Data2;
		USHORT Data3;
		BYTE Data4[8];

		CLSID();
		~CLSID();
	}; // struct CLSID

	struct FILETIME
	{
		DWORD dwLowDateTime;
		DWORD dwHighDateTime;

		FILETIME();
		~FILETIME();
	};
#endif // !DTYPES_H_INCLUDED

