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


#ifndef __JMESS_H
#define __JMESS_H

#include <iostream>
#include <string>
#include <vector>

#include <jack/jack.h>


/** @brief Small utility to save and load all jack client connections.
 *
 * Saves a TSV file with all the current jack connections. This same file can
 * be loaded to connect everything again. The TSV file can also be hand-edited.
 *
 * Also provides the option to disconnect all.
 */
class JMess {

public:
  /** @brief Class constructor. Opens an internal jack client. */
  JMess();

  /** @brief Class destructor. Closes the internal jack client. */
  virtual ~JMess();

  /** @brief Disconnect all input ports from all output ports. */
  void disconnectAll();

  /** @brief Print a TSV of all existing connections to stdout. */
  void printConnections();

  /** @brief Save a TSV of all existing connections to @a outfile. */
  void saveConnections(std::string outfile);

  /** @brief Load connections from the TSV file @a infile. */
  void loadConnections(std::string infile);

  /** @brief A Jack connection from read port (input) to write port (output). */
  struct Connection {
    std::string read;
    std::string write;
  };

private:

  /** @brief Write the list of all connections to the given output stream. */
  void writeConnections(std::ostream &os);

  /** @brief Return a list of all existing connections. */
  std::vector<Connection> getConnections();

  jack_client_t *internal_client_;
  jack_status_t internal_status_;
};
#endif
