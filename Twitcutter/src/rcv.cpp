// rcv.cpp

#include "rcv.h"

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
		std::cerr << "Exception opening file: " << e.what() << "\n";
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
