Copyright 2023 Autodesk, Inc.  All rights reserved.

Use of this software is subject to the terms of the Autodesk license 
agreement provided at the time of installation or download, or which 
otherwise accompanies this software in either electronic or hard copy form.   

Sub-section: Using a Database Reactor.
Program dbreact.cpp

1.	Load the arx application.
2.	Command: watch (The reactor is added to the current database.)
	The function watchDb does this.
3.	Draw a line in ACAD (The notification functions objectModified
	and objectAppended display information).
4.	Erase the line (The notification function objectErased displays
	information.  Try (un)erasing also.).
5.	Command: clear (Function clearreactors removes the reactor from
	the database and deletes the database reactor.)

The sample demonstrates the database reactor for multiple documents by default.  A separate 'WATCH' and 'CLEAR' command can be issued for each open document.

A simpler, single document version of the code is available with the 'dbreact.cpp' included in the folder, but not by default in the project.  To use this version, replace the .cpp file in the project.