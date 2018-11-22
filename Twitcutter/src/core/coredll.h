// coredll.h


#ifndef COREDLL_H_INCLUDED
#define COREDLL_H_INCLUDED

#include "warnings.h"

#ifdef EXPORT_COREDLL
#define TWITCUTAPI __declspec(dllexport)
#else
#define TWITCUTAPI __declspec(dllimport)
#endif // EXPORT_COREDLL

#endif // !COREDLL_H_INCLUDED

