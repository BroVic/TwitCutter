#ifndef CMDCTRL_H_INCLUDED
#define CMDCTRL_H_INCLUDED

#include <string>

enum ErrorCodes
{
	SUCCESS,
	TOO_MANY_ARGS,
	WRONG_FILE,
	PATH_TOO_LONG
};

enum FileExtensions
{
	NOFILE,
	DOC,
	TXT
};

int check_extension(std::string &);

#endif // !CMDCTRL_H_INCLUDED

