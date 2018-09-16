// print.cpp

//
// Print out of generated tweet-sized text
//
#include "print.h"


// Methods for Class TwtPrinter (definitions)
TwitPrinter::TwitPrinter()
{
}

TwitPrinter::~TwitPrinter()
{
}

void TwitPrinter::publish()
{
	this->displayInConsole();

	this->writeToDisk();
}

template<class T>
inline void TwitPrinter::printChain(T &obj)
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
void TwitPrinter::printALine(T &t)
{
	char dash{ '-' };
	for (size_t i = 0; i < 10; i++)
	{
		t << dash;
	}
	t << std::endl;
}
