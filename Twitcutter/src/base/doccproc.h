// DdocProc.h: A Class for processing .DOC files

#ifndef DOCCPROC_H_INCLUDED
#define DOCCPROC_H_INCLUDED

#include <fstream>
#include "dllclnt.h"
#include "cfh.h"
#include "clx.h"
#include "fib.h"
#include <string>
#include <map>

// For decisions on encoding
constexpr int UNICODE  = 0;
constexpr int ANSI     = 1;

// Forward declaration of user-defined
// member types such that our DLL macro
// definition can be properly applied.
struct TWTCTAPI CFHeader;
struct TWTCTAPI Fib;
struct TWTCTAPI DirEntry;
struct TWTCTAPI Clx;

class TWTCTAPI DoccProcessor 
	: public IProcessorLib
{
	// Start member data
	CFHeader                    olehdr;
	Fib                         fib;
	DirEntry                    root;
	Clx                         clxobj;
	uint16_t                    sectSz;
	wchar_t                     utfChar;
	unsigned char               ansiChar;
    unsigned long               wdocStart;
	unsigned long               tablStart;
    unsigned long               clxOffset;
	unsigned long               strmOffset;
	// We want to be rid of pesky warnings on
	// non-exported STL classes, since we are
	// not on our lives even considering it.
	// Source: https://bit.ly/2CHM88w
#pragma warning(push)
#pragma warning(disable:4251)
	std::map<uint8_t, uint16_t> altAnsiExclude;
	std::string                 stringColl;
	std::wstring                wstringColl;
	std::u16string              strmName;
#pragma warning(pop)
	// End of member data
public:
	DoccProcessor();
	~DoccProcessor();
	std::string getString() const;
	void process_file(std::ifstream&);
	void read_file_data(std::ifstream&);
	void collect_text(std::ifstream&);
private:
	inline std::wstring transferUTFString(std::ifstream&, int, int);
	inline std::string transferAnsiString(std::ifstream&, int, int);
};
#endif // !DOCCPROC_H_INCLUDED
