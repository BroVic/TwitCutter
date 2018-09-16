// TwitCutter
//
// CmdMain.cpp
// Main source file for command-line access to the application

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

int main(int argc, char** argv)
{
  Parser prs;
  std::string path;
  path = prs.validate_args(argc, argv[1]);

  Receiver jobIn;
  jobIn.startJob(path);

  MasterSelector sel;
  sel.enable_options(jobIn);

  std::cout << "OPERATION COMPLETED." << std::endl;
}