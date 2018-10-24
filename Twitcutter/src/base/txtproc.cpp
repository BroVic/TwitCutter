#include "txtproc.h"


TextProcessor::TextProcessor()
{
}

TextProcessor::~TextProcessor()
{

}

void TextProcessor::read_textfile(std::ifstream &input)
{
	if (!input.good())
	{
		throw "Input stream was corrupted.";
	}

	std::string temp;
	while (!input.eof())
    {
        std::getline(input, temp);
        textString.append(temp);
    }
    assert(!textString.empty());
}


std::string TextProcessor::getString()
{
	return textString;
}
