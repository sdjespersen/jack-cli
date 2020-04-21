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


#include <jack/jack.h>
#include <fstream>
#include <sstream>

#include "JMess.h"

JMess::JMess()
{
  // Open a client connection to the JACK server.  Starting a new server only to
  // list its ports seems pointless, so we specify JackNoStartServer.
  internal_client_ = jack_client_open("lsp", JackNoStartServer, &internal_status_);
  if (internal_client_ == NULL) {
    if (internal_status_ & JackServerFailed) {
      std::cerr << "JACK server not running" << std::endl;
    } else {
      std::cerr << "jack_client_open() failed, status = 0x%2.0x\n" << internal_status_ << std::endl;
    }
    exit(1);
  }
}


JMess::~JMess()
{
  if (jack_client_close(internal_client_))
    std::cerr << "ERROR: Could not close the hidden jmess jack client." << std::endl;
}


void JMess::saveConnections(std::string outfile)
{
  std::ofstream s(outfile);
  writeConnections(s);
}

void JMess::printConnections() {
  writeConnections(std::cout);
}

void JMess::writeConnections(std::ostream &os) {
  auto cxns = getConnections();
  for (auto it = cxns.begin(); it != cxns.end(); ++it) {
    os << it->read << "\t" << it->write << std::endl;
  }
}

std::vector<JMess::Connection> JMess::getConnections()
{
  std::vector<JMess::Connection> cxns;

  const char **ports, **connections_i; // vector of ports and connections

  // Get active output ports.
  ports = jack_get_ports(internal_client_, NULL, NULL, JackPortIsOutput);
  for (unsigned int i = 0; ports[i]; ++i) {
    auto port_name = jack_port_by_name(internal_client_, ports[i]);
    connections_i = jack_port_get_all_connections(internal_client_, port_name);
    if (connections_i != 0) {
      for (unsigned int j = 0; connections_i[j]; ++j) {
      	cxns.push_back({std::string(ports[i]), std::string(connections_i[j])});
      }
    }
  }

  return cxns;
}


/** @brief Disconnect all the clients. */
void JMess::disconnectAll()
{
  auto cxns = getConnections();

  for (auto it = cxns.begin(); it != cxns.end(); ++it) {
    if (jack_disconnect(internal_client_, it->read.c_str(), it->write.c_str())) {
      std::cerr << "WARNING: port " << it->read << "and port: " << it->write
          << " could not be disconnected.\n";
    }
  }
}


/** @brief Parse the TSV file of saved connections. */
std::vector<JMess::Connection> parseConnectionFile(std::string infile)
{
  std::ifstream connections_file(infile);
  std::vector<JMess::Connection> cxns;
  std::string line;
  while (std::getline(connections_file, line)) {
    std::istringstream iss(line);
    std::string read, write;
    iss >> read >> write;
    cxns.push_back({read, write});
  }
  return cxns;
}


/** @brief Connect ports specified in input TSV file. */
void JMess::loadConnections(std::string infile)
{
  std::vector<JMess::Connection> cxns = parseConnectionFile(infile);

  for (auto it = cxns.begin(); it != cxns.end(); ++it) {
    std::cerr << "Connecting: " << it->read << " => " << it->write << std::endl;

    if (jack_connect(internal_client_, it->read.c_str(), it->write.c_str())) {
    	// Display a warning only if the error is not because the ports are already
    	// connected, in case the program doesn't display anyting.
    	if (EEXIST !=  jack_connect(internal_client_, it->read.c_str(), it->write.c_str())) {
    	  std::cerr << "WARNING: port: " << it->read << "and port: " << it->write
  	       << " could not be connected." << std::endl;
      }
    }
  }
}
