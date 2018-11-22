// docapi.h


// Define DLL linkage
#ifndef DOCAPI_H_INCLUDED
#define DOCAPI_H_INCLUDED

#include "warnings.h"

#ifdef DOCAPI_EXPORT
#define DOCAPI __declspec(dllexport)
#else
#define DOCAPI __declspec(dllimport)
#endif // DOCAPI_EXPORT

#endif // !DOCAPI_H_INCLUDED
