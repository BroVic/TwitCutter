// rcv.h

#ifndef _RCV_H_INCLUDED_
#define _RCV_H_INCLUDED_

#include <string>
#include <fstream>
#include <iostream>
#include "dllclnt.h"
#include "constants.h"


// Intial processing for file input
class TWTCTAPI MasterSelector;

class TWTCTAPI Receiver
{
private:
BEGIN_WARNINGS_ACTION
DISABLE_WARNING_4251
	std::ifstream docstream;
	std::string   fName;
	std::string   exte;
END_WARNINGS_ACTION

	friend class MasterSelector;
public:
	Receiver();
	~Receiver();
	void startJob(const std::string&);
private:
	void activate_stream();
	void get_file_ext();
};

#endif // !_RCV_H_INCLUDED_
