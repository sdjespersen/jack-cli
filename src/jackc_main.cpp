/*
  jackc: A simple command-line JACK client.

  Copyright (C) 2007-2010 Juan-Pablo Caceres.

  Major contributions in 2020 by Scott Jespersen.

  Permission is hereby granted, free of charge, to any person
  obtaining a copy of this software and associated documentation
  files (the "Software"), to deal in the Software without
  restriction, including without limitation the rights to use,
  copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the
  Software is furnished to do so, subject to the following
  conditions:

  The above copyright notice and this permission notice shall be
  included in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
  OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
  OTHER DEALINGS IN THE SOFTWARE.
*/


#include <iostream>
#include <cstdlib>
#include <string>
#include <getopt.h>

#include "JackCli.cpp"

void mainDialog(int argc, char* argv[]);
void printUsageAndExit();


int main(int argc, char** argv)
{
  mainDialog(argc, argv);
  return 0;
}


void mainDialog(int argc, char* argv[])
{
  // If no command arguments are given, print instructions
  if (argc == 1) {
    printUsageAndExit();
  }

  // Usage example at:
  // http://www.gnu.org/software/libc/manual/html_node/Getopt-Long-Option-Example.html#Getopt-Long-Option-Example
  static struct option longopts[] = {
    { "disconnect-all", no_argument, NULL,  'd' },
    { "load", required_argument, NULL, 'l' },
    { "print", no_argument, NULL,  'p' },
    { "save", required_argument, NULL,  's' },
    { "help", no_argument, NULL, 'h' }, // Print Help
    { NULL, 0, NULL, 0 }
  };

  // Accumulate arguments
  bool disconnect_all = false;
  std::string load_from_file;
  bool print_cxns = false;
  std::string save_to_file;

  int ch;
  while ((ch = getopt_long(argc, argv, "dl:ps:h", longopts, NULL)) != -1) {
    switch (ch) {
    case 'd':
      disconnect_all = true;
      break;
    case 'l':
      load_from_file = optarg;
      break;
    case 'p':
      print_cxns = true;
      break;
    case 's':
      save_to_file = optarg;
      break;
    case 'h':
      printUsageAndExit();
    }
  }

  // Warn user if undefined options were entered
  if (optind < argc) {
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "WARNING: The following entered options have no effect" << std::endl;
    std::cout << "         and will be ignored!" << std::endl;
    std::cout << "         Type jackc to see options." << std::endl;
    for( ; optind < argc; optind++) {
      printf("argument: %s\n", argv[optind]);
    }
    std::cout << "------------------------------------------------------" << std::endl;
  }

  // Finally, take action
  JackCli jack_cli;

  if (disconnect_all)
    jack_cli.disconnectAll();
  if (!load_from_file.empty())
    jack_cli.loadConnections(load_from_file);
  if (print_cxns)
    jack_cli.printConnections();
  if (!save_to_file.empty())
    jack_cli.saveConnections(save_to_file);
}


void printUsageAndExit()
{
  std::cout << "jackc: A simple command-line JACK client." << std::endl;
  std::cout << "Copyright (C) 2007-2016 Juan-Pablo Caceres." << std::endl;
  std::cout << "Major contributions in 2020 by Scott Jespersen." << std::endl;
  std::cout << "" << std::endl;
  std::cout << "Usage: " << std::endl;
  std::cout << "--------------------------------------------" << std::endl;
  std::cout << " -h, --help                    Prints this help" << std::endl;
  std::cout << " -l, --load inputfile.tsv      Load the connections specified at inputfile.tsv" << std::endl;
  std::cout << " -p, --print                   Print current connections to stdout" << std::endl;
  std::cout << " -s, --save outputfile.tsv     Save current connections in output.tsv" << std::endl;
  std::cout << " -d, --disconnect-all          Remove all connections" << std::endl;
  std::cout << "" << std::endl;
  exit(0);
}
