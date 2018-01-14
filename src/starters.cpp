#include "starters.h"

Parser::Parser()
{
}

Parser::~Parser()
{
}

std::string Parser::validate_args(int nArg, const char * arg)
{
  if (nArg < 2)
  {
    std::cout << "Enter the path of the file you want to parse: ";
    getline(std::cin, this->path);
  }
  else if (nArg > 2)
  {
    throw "Invalid entry. Accepts no more than 2 args";
  }
  else
  {
    this->path = arg;
  }

  if (this->path.length() > FILENAME_MAX)
  {
    throw "Path is too long for this application.";
  }
  return this->path.c_str();
}
