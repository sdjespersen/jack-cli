# `jackc`: A command-line client for [JACK](http://jackaudio.org/)

`jackc` can:
* Print a TSV with all current connections to stdout.
* Save a TSV with all the current connections to a selected file.
* Load a TSV with connections to make and make them.
* Disconnect everything.

**Why this fork?**

* No dependence on Qt.
* TSV is simpler than XML.

## Installation

* clone the repo
* `make` to build from source
* `cp jackc /usr/local/bin`

You will need Jack already installed.

Provided `Makefile` should work for \*nix systems.

## Usage

To save connections on Jack, use for example
[QjackCtl](http://qjackctl.sourceforge.net/) to make the connections you need.
To save them, just type in the command line:

`jackc -s jack_connections.tsv`

This will save your connections in a two-column tab-separated value format in
the file `jack_connections.tsv`. This is also hand-editable.

To load your connections from file, use:

`jackc -l jack_connections.tsv`

Note that the command above will make the connections that were saved in
`jack_connections.tsv` *while leaving intact existing connections*. In other
words, it will only *add* connections, never remove them. If you instead want to
get exactly the graph represented in `jack_connections.tsv`, use in combination
with the flag `-d` to disconnect all first:

`jackc -d -l jack_connections.tsv`

To disconnect all:

`jackc -d`

More exhaustive usage instructions are given if you run `jackc` with no
arguments.
