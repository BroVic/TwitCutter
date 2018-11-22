// warnings.h

// Macros to change warnings behaviour

#ifndef WARNINGS_H_INCLUDED
#define WARNINGS_H_INCLUDED

// Macros to suppress export warnings on STL object instances https://bit.ly/2CHM88w
#define BEGIN_WARNINGS_ACTION __pragma(warning(push))
#define DISABLE_WARNING_4251 __pragma(warning(disable:4251))
#define END_WARNINGS_ACTION __pragma(warning(pop))

#endif // !WARNINGS_H_INCLUDED

