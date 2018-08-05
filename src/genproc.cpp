// genproc.cpp

#include "genproc.h"
#include "print.h"

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

//--- Class MasterSelector(friend class of Receiver) ---//

MasterSelector::MasterSelector()
{
	fType = STATIC;
}

MasterSelector::~MasterSelector()
{

}

int MasterSelector::check_extension(Receiver &obj)
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
		throw "Unrecognized file format.\nExiting the program.";
	}
	return tag;
}

int MasterSelector::select_extension(Receiver &obj)
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

void MasterSelector::enable_options(Receiver &obj)
{		// Decision on file processing
	TwitPrinter twitPr;
	fType = check_extension(obj);
	switch (fType)
	{
	case NOFILE:
		throw "Unsupported file format.";
		break;
	case DOC:
	{
		DoccProc doccPr;
		doccPr.process_file(obj._docstream);
		twitPr.setFulltxt(doccPr.getString());
	}
	break;
	case TXT:
	{
		TextProc textPr;
		textPr.read_textfile(obj._docstream);
		twitPr.setFulltxt(textPr.getString());
	}
	break;

	}

	twitPr.mkChain();

	twitPr.publish();
}

       //////////////////// -oo-  ////////////////////////////



////////////////////////////////////////////////////////////////////
///////////////         OUTPUT CLASSES        //////////////////////
////////////////////////////////////////////////////////////////////

// Member functions for Class TwtProcessor (definitions)
TwtProcessor::TwtProcessor()
{
	denom    = {};
	twtNumb  = {};
}

TwtProcessor::~TwtProcessor()
{
}


void TwtProcessor::estimTwtNum()
{
	unsigned int len = _fullText.length();
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

	while(!_fullText.empty())
	{
		if (CHARACTER_MAX - CHARACTER_LIMIT > 5)
		{
			cutoff = _fullText.rfind(' ', CHARACTER_LIMIT);
		}
		else
		{
			std::cerr << "The string length are too high" << std::endl;
		}

		_piece = _fullText.substr(0, cutoff);

		if (_piece.empty())
		{
			++denom;
			_piece.push_back(OPEN_TAG);
			_piece += std::to_string(denom);
			_piece.push_back(DIVISOR);
			_piece += std::to_string(twtNumb);
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

//void TwtProcessor::collectStr()
//{		// Collects extracted string from various document formats
//	_fullText.assign(_stringColl);
//}

void TwtProcessor::mkChain()
{
	// collectStr();
	estimTwtNum();
	spliceStr();
}

void TwtProcessor::setFulltxt(std::string s_in)
{
	_fullText.assign(s_in);
}
         ////////////////// -oo- //////////////////////////
