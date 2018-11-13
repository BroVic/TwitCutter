// iodef.h

#ifndef _IODEF_H_INCLUDED_
#define _IODEF_H_INCLUDED_

#include <stdio.h>

// Redefine standard streams in newer compiler versions
#if _WIN32
#if _MSC_VER >= 1900
FILE _iob[] = { *stdin, *stdout, *stderr };
extern "C" FILE* __cdecl __iob_func(void) { return _iob; }
extern "C" void __imp__set_output_format(void) {};
#endif
#endif

#endif // !_IODEF_H_INCLUDED_

