#include "GenericProc.h"

GenericProc::GenericProc()
{
	_denom    = {};
	_twtNumb  = {};
}

GenericProc::~GenericProc()
{
	_docstream.close();
}

int GenericProc::globalProcess(std::string filename)
{
	_docstream.open(filename, std::ios::binary);
	if (!_docstream.is_open())
	{
		std::cerr << "Could not open the file." << std::endl;
		return ERR_NO_OPEN;
	}
	if (!_docstream.good())
	{
		std::cerr << "The file is probably corrupted." << std::endl;
		return ERR_NOT_GOOD;
	}
	if (!_docstream.tellg() == ZERO_OFFSET)
		_docstream.seekg(ZERO_OFFSET, std::ios::beg);

	// Receives stream
	ddocProcessor.process_file(_docstream);

	// Produces chain
	makeChain();

	printChain();

	return 0;
}

// Estimate number of tweets from the string
void GenericProc::estimateTweetNum()
{
	int len = _fullText.length();
	if (len > SET_LIMIT)
	{
		_twtNumb = len / SET_LIMIT;
		if (len % SET_LIMIT != 0)
		{
			++_twtNumb;
		}
	}
	return;
}

void GenericProc::spliceString()
{
	unsigned int cutoff{};
	
	while(!_fullText.empty())
	{
		if (MAX_LIMIT - SET_LIMIT > 5)
		{
			cutoff = _fullText.rfind(' ', SET_LIMIT);
		}
		else
		{
			std::cerr << "The string length are too high" << std::endl;
		}
		
		_piece = _fullText.substr(0, cutoff);
		
		if (!_piece.empty())
		{
			++_denom;

			_piece.push_back(OPEN_TAG);
			_piece += std::to_string(_denom);
			_piece.push_back(DIVISOR);
			_piece += std::to_string(_twtNumb);
			_piece.push_back(CLOSE_TAG);

			chain.push_back(_piece);
		}
		else
		{
			return;
		}
		
		_fullText = _fullText.erase(0, cutoff);
	}
	
	return;
}

void GenericProc::makeChain()
{
	_fullText = ddocProcessor.getCollectedString();
	
	estimateTweetNum();
	
	spliceString();
	
	
	return;
}

void GenericProc::printChain()
{
	std::cout << "Commencing printing of available text blocks." << std::endl
		<< std::endl;
	
	int numb = chain.size();
	int i = 0;
	while (i < numb)
	{
		std::cout << i + 1 << " " << this->chain[i] << std::endl
			<< std::endl;
		i++;
	}
	
	if (i == numb)
	{
		std::cout << "All available tweets have been displayed/printed." << std::endl
			<< std::endl;
	}
	else
	{
		std::cerr << "There was a problem counting/printing the text blocks." << std::endl;
	}
	
	return;
}
