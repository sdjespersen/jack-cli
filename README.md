# JMess - A utility to save your audio connections (mess) #

JMess can save an XML file with all the current [Jack Audio](http://jackaudio.org/) connections. This same file can be loaded to connect everything again. The XML file can also be edited. It also also has the option to disconnect all the clients.

**Why this fork?**

* No dependence on Qt.
* TSV is simpler than XML.

## Installation

* clone the repo
* `make` to build from source
* `cp jmess /usr/local/bin`

You will need Jack already installed.

Provided `Makefile` should work for \*nix systems.

## Usage

To save connections on Jack, use for example
[QjackCtl](http://qjackctl.sourceforge.net/) to make the connections you need.
To save them, just type in the command line:

`jmess -s jack_connections.tsv`

This will save your connections in a two-column tab-separated value format in
the file `jack_connections.tsv`. This is also hand-editable.

To load your connections from file, use:

`jmess -c jack_connections.tsv`

Note that the command above will make the connections that were saved in
`jack_connections.tsv` *while leaving intact existing connections*. In other
words, it will only *add* connections, never remove them. If you instead want to
get exactly the graph represented in `jack_connections.tsv`, use in combination
with the flag `-d` to disconnect all first:

`jmess -d -c jack_connections.tsv`

To disconnect all:

`jmess -d`

More exhaustive usage instructions are given if you run `jmess` with no
arguments.
