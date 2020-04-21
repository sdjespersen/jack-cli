# JMess - A utility to save your audio connections (mess) #

JMess can save an XML file with all the current [Jack Audio](http://jackaudio.org/) connections. This same file can be loaded to connect everything again. The XML file can also be edited. It also also has the option to disconnect all the clients.

## Download and Installation ##
There is a Linux and a Mac OS X version of JMees. To install just download, uncompress, and follow the instrunctions on `INSTALL.txt`.

## Using JMess ##

To save connections on Jack, use for example [QjackCtl](http://qjackctl.sourceforge.net/) to make the connections you need. To save them, just type in the command line:

`jmess -s filename.xml`

This will save your connections in a file filename.xml. This is an XML file that you can edit, if you want.

To load your connections from a file, just type:

`jmess -c filename.xml`

Note that if you have connections running, the command above is going to connect what was saved on the filename.xml, keeping the connections that you have. If you want to get exactly what was saved on filename.xml, use the flag -d to disonnect all:

`jmess -d -c filename.xml`

If you just want to disconnect all from the command line:

`jmess -d`

For a complete list of options, just type:

`jmess`
jmess : Build Instructions for Linux and MacOS X

jmess can save an XML file with all the current jack connections. This same file can
be loaded to connect evrything again. The XML file can also be edited.
It alse also has the option to disconnect all the clients.

---
MacOS X (10.4 or higher) Installation:

If you are installing on MacOS X, a binary is provided.  You just need to have JackOSX installed on your machine
http://www.jackosx.com/

TO install (using Terminal): go to bin/ directory and type:

   sudo cp jmess /usr/bin/
   (enter your password when prompted)

   sudo chmod 755 /usr/bin/jmess
   (now you can run jmess from any directory using Terminal)

---
Dependencies:

You need to have installed the libraries in your system:
qt4-devel
jack-audio-connection-kit-devel

If you are using yum (in Fedora Core 12 for example) you can just install
them (as root) with:
yum install qt4-devel jack-audio-connection-kit-devel


If you want to build on MacOS X, you need JackOSX
http://www.jackosx.com/
and Qt 4.2 or higher. A Binary installer is porvided at:
http://www.trolltech.com/download?target=ftp://ftp.trolltech.com/qt/source/qt-mac-opensource-4.3.0.dmg


---
Build:

to build on Linux or Mac OS X, just go to the /src directory and type the following two command:

   ./build

						    
If evreything works fine, you will have the excecutable jmess ready to use. It is located at the ../bin directory. If you wish, you can install it in your system. Just type (as root):

   make install

If you want to uninstall:

   make uninstall


---
Usage:

For a list a commands, just type:
./jmess

If you want to save your current connections (connected with qjackctl for example)
just type:

./jmess -s filename.xml

All your connections are saved in filename.xml.

If you want to load them:
./jmess -c filename.xml
						    
And if you first want to disconnect all and the load the saved connections:
./jmess -d -c filename.xml

If you just want to disconnect all:
./jmess -d


---
Juan-Pablo Caceres
Please contact me with bugs, suggestions at:
jcaceres [at] ccrma [dot] stanford [dot] edu

