// master.cpp

#include "master.h"

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
		DoccProcessor  doccPr;
		IProcessorLib& ip = doccPr;
		ip.process_file(obj.docstream);
		str = ip.getString();
	}
	break;
	case TXT:
	{
		TextProcessor textPr;
		IProcessorLib& ip = textPr;
		ip.read_file_data(obj.docstream);
		str = ip.getString();
	}
	break;
	}
	return str;
}
