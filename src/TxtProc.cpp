#include "TxtProc.h"

TxtProc::TxtProc()
{
}

TxtProc::~TxtProc()
{
	
}

void TxtProc::read_txtfile(std::ifstream &input)
{
	if (!input.is_good())
	{
		throw "Input stream was corrupted.";
	}
	
	input.read(_textString, input.size());
}


std::string TxtProc::getString()
{
	return _textString;
}
