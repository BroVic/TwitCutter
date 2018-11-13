// iodef.h

#include <stdio.h>

#if _WIN32
#if _MSC_VER >= 1900
// Redefine standard streams in newer compiler versions
FILE _iob[] = { *stdin, *stdout, *stderr };
extern "C" FILE* __cdecl __iob_func(void) { return _iob; }
extern "C" void __imp__set_output_format(void) {};
#endif
#endif