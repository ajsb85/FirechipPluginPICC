FirechipPluginPICC vs 1
======================

What does this program:

This sources contains a dockable function list for Firechip IDE version 1.0.
With this plugin you could easy browse between functions in a file.

For generating the dll file use VC++ 6. The project is included.

If you create a new project for VC 7/8 or MinGW please sent me the
complete project. I will integrate it.

This is the second implementation of the Perforce plugin for Firechip IDE.

This version can be build both for ANSI and UNICODE, but note that I only
use UNICODE versions of Firechip IDE these days, so the ANSI version is untested, 
except that it compiles cleanly under VS 2008.

To use this, copy the DLL to your Firechip IDE pluings directory.

Note that the p4.exe file must be in your path (this is the default).

As always, this software comes without any guaranteees whatsoever, so
don't blame me if you end up reverting a lot of work down the drain.

The plugins side is:


Have fun

Alexander Salas
alexander@firechip.info
