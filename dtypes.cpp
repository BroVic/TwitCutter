#include "dtypes.h"

CLSID::CLSID()
{
	Data1 = SET_ZERO;
	Data2 = SET_ZERO;
	Data3 = SET_ZERO;
	for (int i = 0; i < 8; ++i)
	{
		Data4[i] = SET_ZERO;
	}
}

CLSID::~CLSID()
{
}

FILETIME::FILETIME()
{
	dwLowDateTime = SET_ZERO;
	dwHighDateTime = SET_ZERO;
}

FILETIME::~FILETIME()
{
}
