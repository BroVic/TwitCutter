// Controls for main() of the console application

#include "cmdctrl.h"

// Checks file extension
int check_extension(std::string &str)
{
	int len = str.length() + 1;
	char *tempstr = new (std::nothrow) char[len];
	if (tempstr == nullptr)
	{
		throw "Unable to allocate memory.";
	}

	// Ensure all are lower-case
	for (int i = 0; i < len; ++i)
	{
		tempstr[i] = tolower(str[i]);
	}
	tempstr[len] = '\0';

	str.assign(tempstr);

	if (str.compare(".doc") == 0)
	{
		return DOC;
	}
	else if (str.compare(".txt") == 0)
	{
		return TXT;
	}

	return NOFILE;
}