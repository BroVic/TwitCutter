// genericproc.cpp

#include "genericproc.h"

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

	displayChainInConsole();

	writeChainToDisk();

	return 0;
}

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
}

void GenericProc::makeChain()
{
	_fullText = ddocProcessor.getCollectedString();
	
	estimateTweetNum();
	
	spliceString();
}

template<class T>
inline void GenericProc::printChain(T &obj)
{
	std::cout << "Printing available text blocks..." << std::endl
		<< std::endl;
	
	int numb = chain.size();
	int i = 0;
	while (i < numb)
	{
		obj << i + 1 << " " << this->chain[i] << std::endl;
		printLine(obj);
		i++;
	}
	
	if (i == numb)
	{
		obj << "--- All available tweets have been displayed. ---" << std::endl;
		printLine(obj);
	}
	else
	{
		obj << "There was a problem counting/printing the text blocks." << std::endl;
	}
}

void GenericProc::displayChainInConsole()
{
	printChain(std::cout);
}

void GenericProc::writeChainToDisk()
{
	char response{};
	std::cout << "\nWrite tweets to disk? (Y/N) ";
	std::cin >> response;
	if (tolower(response) == 'n')
	{
		return;
	}
	else if (tolower(response) == 'y')
	{
		// generate a file name
		std::string filename;
		std::cout << "Provide a filename (defaults to '.TXT'): ";
		std::cin >> filename;
		filename.append(".txt");

		_printer.open(filename.c_str());
		if (!_printer.is_open())
		{
			std::cerr << "Could not open '" << filename.c_str() << "'." << std::endl;
			return;
		}
		
		printChain(_printer);
				
		_printer.close();
	}
	else
	{
		std::cerr << "Invalid response." << std::endl;
	}
}

template<class T>
void GenericProc::printLine(T &t)
{
	char dash{ '-' };
	for (size_t i = 0; i < 10; i++)
	{
		t << dash;
	}
	t << std::endl;
}
