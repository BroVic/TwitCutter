// TwitCutter
//
// cmdmain.cpp
// Entry point for the console application

// A document file is passed as an argument at the command line
// twtcut.exe [file]
// TwitCutter's main function is all about the initial preparation of the file
// such that it checks the file whether it is in a format that can be treated 
// and, if so, culminates in passing the path of the file to a generic
// processor object of class 'DocSelector' for appropriate handling. An attempt
// has been made at making this an interactive experience for the user.

#include <string>
#include <iostream>
#include "rcv.h"
#include "master.h"
#include "starters.h"
#include "print.h"
#include "twclient.h"
#include "twfact.h"


int main(int argc, char** argv)
{
	Parser prs{};
	auto path = prs.validate_args(argc, argv[1]);

	Receiver jobIn{};
	jobIn.startJob(path);

	MasterSelector s{};
	std::string txt = s.enable_options(jobIn); // This is stupid, walahi!
  
	TwitPrinter p{};
	p.set_fulltxt(txt);
	p.mkChain();
	p.publish();

	char ans{};
	std::cout << "Post text as tweets... (Y/N) ";
	std::cin >> ans;
	if (tolower(ans) == 'y')
	{
		TwitterClient app{};
		app.post_all_tweets();
	}
	else if (tolower(ans) == 'n')
	{
		std::cout << "Text will not be posted online\n";
	}
	else
	{
		std::cerr << "Invalid entry\n";
	}
}
