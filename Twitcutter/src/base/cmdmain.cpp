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
#include "genproc.h"
#include "starters.h"
#include "print.h"
#include "post.h"

FILE _iob[] = { *stdin, *stdout, *stderr };
extern "C" FILE * __cdecl __iob_func(void) { return _iob; }
extern "C" void __imp__set_output_format(void) {};

int main(int argc, char** argv)
{
  Parser prs;
  auto path = prs.validate_args(argc, argv[1]);

  Receiver jobIn;
  jobIn.startJob(path);

  MasterSelector sel;
  std::string txt = sel.enable_options(jobIn);
  
  TwitPrinter twitPr;
  twitPr.setFulltxt(txt);
  twitPr.mkChain();
  twitPr.publish();

  char ans{};
  std::cout << "Post text as tweets... (Y/N) ";
  std::cin >> ans;
  if (tolower(ans) == 'y')
  {
	  TwitterClient app;
	  app.setup_twitter_oauth();
	  app.post_status(twitPr);
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
