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
	if (len > characterLimit)
	{
		twtNumb = len / characterLimit;
		if (len % characterLimit != 0)
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
		cutoff = fullText.rfind(spaceChar, characterLimit);
		piece = fullText.substr(0, cutoff);
		piece.push_back(spaceChar);
		piece.push_back(openingTag);
		piece += std::to_string(++denom);
		piece.push_back(divisor);
		piece += std::to_string(twtNumb);
		piece.push_back(closingTag);
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
