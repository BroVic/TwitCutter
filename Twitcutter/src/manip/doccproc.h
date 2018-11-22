// DdocProc.h: A Class for processing .DOC files

#ifndef DOCCPROC_H_INCLUDED
#define DOCCPROC_H_INCLUDED

#include <fstream>
#include <string>
#include <map>
#include "cfh.h"
#include "fib.h"
#include "clx.h"
#include "iproc.h"
#include "docapi.h"

// Forward declaration of user-defined
// member types such that our DLL macro
// definition can be properly applied.
struct DOCAPI CFHeader;
struct DOCAPI Fib;
struct DOCAPI DirEntry;
struct DOCAPI Clx;

class DOCAPI DoccProcessor 
	: public IProcessorLib
{
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
BEGIN_WARNINGS_ACTION
DISABLE_WARNING_4251
	std::map<uint8_t, uint16_t> altAnsiExclude;
	std::string                 stringColl;
	std::wstring                wstringColl;
	std::u16string              strmName;
END_WARNINGS_ACTION

	inline std::wstring transferUTFString(std::ifstream&, int, int);
	inline std::string transferAnsiString(std::ifstream&, int, int);
public:
	DoccProcessor();
	~DoccProcessor();
	std::string getString() const;
	void process_file(std::ifstream&);
	virtual void read_file_data(std::ifstream&) override final;
	virtual void collect_text(std::ifstream&) override final;
};
#endif // !DOCCPROC_H_INCLUDED




