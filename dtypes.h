// dtypes.h
// A header file containing definitions of all the major data used

#ifndef DTYPES_H_INCLUDED
#define DTYPES_H_INCLUDED

using BYTE      = unsigned char;
using USHORT    = unsigned short;
using ULONG     = unsigned int;
using ULONGLONG = unsigned long long;
using CHAR      = signed char;
using SHORT     = short;
using LONG      = int;
using WCHAR     = char16_t;
using BOOL      = bool;
using VOID      = void;

constexpr int SET_ZERO = 0x0;

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
	ULONG dwLowDateTime;
	ULONG dwHighDateTime;

	FILETIME();
	~FILETIME();
};
#endif // !DTYPES_H_INCLUDED

