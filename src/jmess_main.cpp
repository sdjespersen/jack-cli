/*
  JMess: A simple utility so save your jack-audio mess.

  Copyright (C) 2007-2010 Juan-Pablo Caceres.

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

#include "JMess.cpp"

void mainDialog(int argc, char* argv[]);
void printUsage();


int main(int argc, char** argv)
{
  mainDialog(argc, argv);
  return 0;
}


void mainDialog(int argc, char* argv[])
{

  // If no command arguments are given, print instructions
  if (argc == 1) {
    printUsage();
    std::exit(0);
  }

  // TODO: Don't attempt to create a connection until arguments have been parsed.
  // Create JMess Object for the following flags
  JMess jmessClient;

  // Usage example at:
  // http://www.gnu.org/software/libc/manual/html_node/Getopt-Long-Option-Example.html#Getopt-Long-Option-Example
  static struct option longopts[] = {
    { "disconnect-all", no_argument, NULL,  'd' },
    // TODO(sdjespersen): Add the option to make a single new connection
    // specified on the command line.
    { "load", required_argument, NULL, 'l' },
    { "print", no_argument, NULL,  'p' },
    { "save", required_argument, NULL,  's' },
    { "help", no_argument, NULL, 'h' }, // Print Help
    { NULL, 0, NULL, 0 }
  };

  int ch;
  while ((ch = getopt_long(argc, argv, "dl:ps:h", longopts, NULL)) != -1) {
    switch (ch) {
    case 'd':
      jmessClient.disconnectAll();
      break;
    case 'l':
      jmessClient.loadConnections(optarg);
      break;
    case 'p':
      jmessClient.printConnections();
      break;
    case 's':
      jmessClient.saveConnections(optarg);
      break;
    case 'h':
      printUsage();
      break;
    }
  }

  // Warn user if undefined options were entered
  if (optind < argc) {
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "WARNING: The following entered options have no effect" << std::endl;
    std::cout << "         and will be ignored!" << std::endl;
    std::cout << "         Type jmess to see options." << std::endl;
    for( ; optind < argc; optind++) {
      printf("argument: %s\n", argv[optind]);
    }
    std::cout << "------------------------------------------------------" << std::endl;
  }
}


void printUsage()
{
  std::cout << "JMess: A simple utility so save your jack-audio mess." << std::endl;
  std::cout << "Copyright (C) 2007-2016 Juan-Pablo Caceres." << std::endl;
  std::cout << "" << std::endl;
  std::cout << "Usage: " << std::endl;
  std::cout << "--------------------------------------------" << std::endl;
  std::cout << " -h, --help                    Prints this help" << std::endl;
  std::cout << " -l, --load inputfile.tsv      Load the connections specified at inputfile.tsv" << std::endl;
  std::cout << " -p, --print                   Print current connections to stdout" << std::endl;
  std::cout << " -s, --save outputfile.tsv     Save current connections in output.tsv" << std::endl;
  std::cout << " -d, --disconnect-all          Remove all connections" << std::endl;
  std::cout << "" << std::endl;
}
