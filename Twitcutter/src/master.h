// master.h

// Select options for input processing

#ifndef _MASTER_H_INCLUDED_
#define _MASTER_H_INCLUDED_

#include <string>
#include "rcv.h"
#include "constants.h"
#include "doccproc.h"
#include "txtproc.h"
#include "dllclnt.h"

class MasterSelector
{
private:
	int fType;
public:
	MasterSelector();
	~MasterSelector();
	std::string enable_options(Receiver&);
private:
	int check_extension(Receiver&);
	int select_extension(Receiver&);
};

#endif // !_MASTER_H_INCLUDED_

