// dllclnt.h

// Interface class to enable DLL export
#include "stdafx.h"

#ifndef _DLLCLNT_H_INCLUDED_
#define _DLLCLNT_H_INCLUDED_

#include <fstream> 
#include <string>

// For DLL build on Win32
#if defined(_WIN32) && defined(_WINDLL)
#define TWTCT_BUILD_DLL _WINDLL
#endif

// Provide alternatively for export and import
#ifdef _WIN32
#ifdef TWTCT_BUILD_DLL
#define TWTCTAPI __declspec(dllexport)
#else
#define TWTCTAPI __declspec(dllimport)
#endif
#elif defined(_GNUC_) // && when using GNU shared library (TODO)
#define TWTCTAPI __attribute__((visibility(*default*)))
#else
#define TWTCTAPI
#endif

// Abstract class to enable selective
// export/import of member function(s)
class TWTCTAPI IProcessorLib
{
public:
	virtual ~IProcessorLib();
	virtual std::string getString() const = 0;
	virtual void process_file(std::ifstream&) = 0;
	virtual void read_file_data(std::ifstream&) = 0;
	virtual void collect_text(std::ifstream&) = 0;
};
#endif // !_DLLCLNT_H_INCLUDED_

