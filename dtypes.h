// dtypes.h
// A header file containing definitions of all the major data used

#ifndef DTYPES_H_INCLUDED
#define DTYPES_H_INCLUDED

#include <cstdint>

using BYTE      = uint8_t;
using USHORT    = uint16_t;
using ULONG     = uint32_t;
using ULONGLONG = uint64_t;
using CHAR      = int8_t;
using SHORT     = int16_t;
using LONG      = int32_t;
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

