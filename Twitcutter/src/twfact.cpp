// twfact.cpp

#include "twfact.h"

TwtProcessor::TwtProcessor()
{
	denom = {};
	twtNumb = {};
}

TwtProcessor::~TwtProcessor()
{
}


void TwtProcessor::estimTwtNum()
{
	unsigned int len = fullText.length();
	if (len > CHARACTER_LIMIT)
	{
		twtNumb = len / CHARACTER_LIMIT;
		if (len % CHARACTER_LIMIT != 0)
		{
			++twtNumb;
		}
	}
	return;
}

void TwtProcessor::spliceStr()
{
	unsigned int cutoff{};
	while (denom != twtNumb)
	{
		cutoff = fullText.rfind(SPACE, CHARACTER_LIMIT);
		piece = fullText.substr(0, cutoff);
		piece.push_back(SPACE);
		piece.push_back(OPEN_TAG);
		piece += std::to_string(++denom);
		piece.push_back(DIVISOR);
		piece += std::to_string(twtNumb);
		piece.push_back(CLOSE_TAG);
		chain.push_back(piece);
		fullText = fullText.erase(0, cutoff);
	}
}

void TwtProcessor::mkChain()
{
	estimTwtNum();
	spliceStr();
}

// TODO: Implement properly
int TwtProcessor::reset_maxChainLen(char newVal)
{
	if (newVal < 1)
	{
		// say something but do nothing
		return -1;
	}
	else if (newVal == chain.size())
	{
		// nothing to change; notify
		return 0;
	}
	maxChainLen = newVal;
	return 1;
}
