// print.cpp

//
// Print out of generated tweet-sized text
//
#include "print.h"


// Methods for Class TwtPrinter (definitions)
TwitPrinter::TwitPrinter()
	: printer{},
	lastMsg{ "--- All available tweets have been displayed. ---\n" }
{
}

TwitPrinter::~TwitPrinter()
{
}

void TwitPrinter::publish()
{
	displayInConsole();
	writeToDisk();
}

const std::string TwitPrinter::get_lastMsg() const
{
	return lastMsg;
}

template<class T>
inline void TwitPrinter::printChain(T &obj)
{
	std::cout << "Printing available text blocks...\n\n";

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
		obj << get_lastMsg();
		printALine(obj);
	}
	else
	{
		obj << "There was a problem counting/printing the text blocks.\n";
	}
}

void TwitPrinter::displayInConsole()
{
	printChain(std::cout);
}

void TwitPrinter::writeToDisk()
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

		printer.open(filename.c_str());
		if (!printer.is_open())
		{
			std::cerr << "Could not open '" << filename.c_str() << "'." << std::endl;
			return;
		}

		printChain(printer);

		printer.close();
	}
	else
	{
		std::cerr << "Invalid response." << std::endl;
	}
}

template<class T>
void TwitPrinter::printALine(T &t)
{
	char dash{ '-' };
	for (size_t i = 0; i < 10; i++)
	{
		t << dash;
	}
	t << std::endl;
}
