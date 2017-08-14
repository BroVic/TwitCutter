// genericproc.cpp

#include "genericproc.h"

//////////////////////////////////////////////////////////////////
///////////////         INPUT CLASS         //////////////////////
//////////////////////////////////////////////////////////////////

//--- Class Receiver ---//
Receiver::Receiver()
{
}

Receiver::~Receiver()
{
	_docstream.close();
}

void Receiver::startJob(const std::string &file)
{
	_fName.assign(file);
	if (_fName.length() != file.length())
	{
		throw "There was a problem reading the filename.";
	}
	activate_stream();
	get_file_ext();
}

void Receiver::activate_stream()
{
	_docstream.open(_fName, std::ios::binary);
	if (!_docstream.is_open())
	{
		throw "Could not open the file." ;
	}
	if (!_docstream.good())
	{
		throw "The file is probably corrupted.";
	}
	if (!_docstream.tellg() == ZERO_OFFSET)
		_docstream.seekg(ZERO_OFFSET, std::ios::beg);

}

void Receiver::get_file_ext()
{
	std::string::size_type dot = _fName.rfind('.');
	_exte = _fName.substr(dot);
}

//--- Class DocSelector (friend class of Receiver) ---//

int DocSelectorStart::fType = -1;

DocSelectorStart::DocSelectorStart()
{
}

DocSelectorStart::~DocSelectorStart()
{

}

int DocSelectorStart::check_extension(Receiver &obj)
{
	int tag;
	try
	{
		tag = select_extension(obj);
	}
	catch (const char* excep)
	{
		std::cerr << "An exception was caught." << excep << std::endl;
	}

	if (tag == NOFILE)
	{
		std::cerr << "Unrecognized file format.\nExiting the program." << std::endl;
		return WRONG_FILE;
	}
	return tag;
}

int DocSelectorStart::select_extension(Receiver &obj)
{
	std::string temp(obj._exte);
	int len = temp.length() + 1;
	char *tempstr = new (std::nothrow) char[len];
	/*if (tempstr == nullptr)
	{
	throw "Unable to allocate memory.";
	}*/

	// Ensure all are lower-case
	for (int i = 0; i < len; ++i)
	{
		tempstr[i] = tolower(temp[i]);
	}
	tempstr[len] = '\0';

	temp.assign(tempstr);

	if (temp.compare(".doc") == 0)
	{
		return DOC;
	}
	else if (temp.compare(".txt") == 0)
	{
		return TXT;
	}
	else
	{
		return NOFILE;
	}
}

void DocSelectorStart::chooseFormat(Receiver &obj)
{		// Decision on file processing
	
	fType = check_extension(obj);

	switch (fType)
	{
	case NOFILE:
		throw "Unsupported file format.";
		break;
	case DOC:
		doccProcessor.process_file(obj._docstream);
		break;
	case TXT:
		// txtProcessor.process_file(obj._docstream);
		break;
	/*default:
		break;*/
	}
	
}

       //////////////////// -oo-  ////////////////////////////



////////////////////////////////////////////////////////////////////
///////////////         OUTPUT CLASSES        //////////////////////
////////////////////////////////////////////////////////////////////

// Methods for Class TwtProcessor (definitions)
TwtProcessor::TwtProcessor()
{
	_denom    = {};
	_twtNumb  = {};
}

TwtProcessor::~TwtProcessor()
{
}


void TwtProcessor::estimTwtNum()
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

void TwtProcessor::spliceStr()
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

void TwtProcessor::collectStr()
{		// Collects extracted string from various document formats
	_fullText.assign(DoccProc::stringColl);
}

void TwtProcessor::mkChain()
{
	collectStr();

	estimTwtNum();
	
	spliceStr();
}


// Methods for Class TwtPrinter (definitions)
TwtPrinter::TwtPrinter()
{
}

TwtPrinter::~TwtPrinter()
{
}

void TwtPrinter::publish()
{
	displayInConsole();

	writeToDisk();
}

template<class T>
inline void TwtPrinter::printChain(T &obj)
{
	std::cout << "Printing available text blocks..." << std::endl
		<< std::endl;
	
	int numb = chain.size();
	int i = 0;
	while (i < numb)
	{
		obj << i + 1 << " " << this->chain[i] << std::endl;
		printALine(obj);
		i++;
	}
	
	if (i == numb)
	{
		obj << "--- All available tweets have been displayed. ---" << std::endl;
		printALine(obj);
	}
	else
	{
		obj << "There was a problem counting/printing the text blocks." << std::endl;
	}
}

void TwtPrinter::displayInConsole()
{
	printChain(std::cout);
}

void TwtPrinter::writeToDisk()
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
void TwtPrinter::printALine(T &t)
{
	char dash{ '-' };
	for (size_t i = 0; i < 10; i++)
	{
		t << dash;
	}
	t << std::endl;
}

         ////////////////// -oo- //////////////////////////

DocSelectorFinish::DocSelectorFinish()
{
}

DocSelectorFinish::~DocSelectorFinish()
{
}
