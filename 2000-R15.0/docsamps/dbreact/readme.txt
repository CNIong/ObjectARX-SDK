
Sub-section: Using a Database Reactor
 (C) Copyright 1998 by Autodesk, Inc.
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
