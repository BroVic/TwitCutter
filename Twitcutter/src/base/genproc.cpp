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
	docstream.close();
}

void Receiver::startJob(const std::string &file)
{
	fName.assign(file);
	if (fName.length() != file.length())
	{
		throw "There was a problem reading the filename.";
	}
	activate_stream();
	get_file_ext();
}

void Receiver::activate_stream()
{
	// Enable exception before opening stream
	docstream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		docstream.open(fName, std::ios::binary);
	}
	catch (std::ifstream::failure e)
	{
		std::cerr << "Exception opening file: " << std::strerror(errno) << "\n";
	}
	
	if (docstream.good())
	{
		if (!docstream.tellg() == ZERO_OFFSET)
			docstream.seekg(ZERO_OFFSET, std::ios::beg);
	}
}

void Receiver::get_file_ext()
{
	std::string::size_type dot = fName.rfind('.');
	exte = fName.substr(dot);
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
	std::string temp(obj.exte);
	int len = temp.length() + 1;
	char *tempstr = new (std::nothrow) char[len];
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

std::string MasterSelector::enable_options(Receiver &obj)
{		// Decision on file processing
	std::string str;
	fType = check_extension(obj);
	switch (fType)
	{
	case NOFILE:
		throw "Unsupported file format.";
		break;
	case DOC:
	{
		DoccProcessor doccPr;
		doccPr.process_file(obj.docstream);
		str = doccPr.getString();
	}
	break;
	case TXT:
	{
		TextProcessor textPr;
		textPr.read_textfile(obj.docstream);
		str = textPr.getString();
	}
	break;
	}
	return str;
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
	while(denom != twtNumb)
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

void TwtProcessor::setFulltxt(std::string& s_in)
{
	fullText.assign(s_in);
}
         ////////////////// -oo- //////////////////////////
