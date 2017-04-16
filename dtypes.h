// dtypes.h
// A header file containing definitions of all the major data
// types used in this application



#ifndef DTYPES_H_INCLUDED
#define DTYPES_H_INCLUDED

#include <cstdint>

using BYTE = uint8_t;
using CHAR = int8_t;
using WORD = uint16_t;
using DWORD = uint32_t;
using LONG = int32_t;
using WCHAR = wchar_t;
using ULONGLONG = uint64_t;

struct CLSID
{
	DWORD Data1;
	WORD Data2;
	WORD Data3;
	BYTE Data4[8];
}; // struct CLSID

struct FILETIME
{
	DWORD dwLowDateTime;
	DWORD dwHighDateTime;
};



#endif // !DTYPES_H_INCLUDED

