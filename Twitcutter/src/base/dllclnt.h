// dllclnt.h

// Interface class to enable DLL export

#ifndef _DLLCLNT_H_INCLUDED_
#define _DLLCLNT_H_INCLUDED_

#include <fstream>

#define DLLEXPORT __declspec(dllexport)

class DLLEXPORT IProcessorLib
{
public:
	virtual void process_file(std::ifstream&) = 0;
};
#endif // !_DLLCLNT_H_INCLUDED_

