#include "dtypes.h"

CLSID::CLSID()
{
	Data1 = SET_BYTES;
	Data2 = SET_BYTES;
	Data3 = SET_BYTES;
	for (int i = 0; i < 8; ++i)
		Data4[i] = SET_BYTES;
}

CLSID::~CLSID()
{
}

FILETIME::FILETIME()
{
	dwLowDateTime = SET_BYTES;
	dwHighDateTime = SET_BYTES;
}

FILETIME::~FILETIME()
{
}
