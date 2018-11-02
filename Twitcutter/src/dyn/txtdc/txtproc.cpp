#include "txtproc.h"


TextProcessor::TextProcessor() 
	: errBadStream{ "Input stream was corrupted." },
	txtString{}
{
}

TextProcessor::~TextProcessor()	
{
}

void TextProcessor::process_file(std::ifstream& s)
{
	read_file_data(s);
	collect_text(s);
}

void TextProcessor::read_file_data(std::ifstream &input)
{
	if (!input.good())
	{
		 std::cerr << errBadStream << '\n';
	}

	std::string tmp{""};
	while (!input.eof())
    {
        std::getline(input, tmp);
		txtString.append(tmp);
    }
    assert(!txtString.empty());
}

void TextProcessor::collect_text(std::ifstream &)
{
}


std::string TextProcessor::getString() const
{
	return txtString;
}
