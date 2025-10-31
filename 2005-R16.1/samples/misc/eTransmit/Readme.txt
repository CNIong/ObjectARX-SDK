eTransmit Sample Readme.txt

 (C) Copyright 2004 by Autodesk, Inc.

eTransmit sample - Showing how to use the eTransmit COM API

This program demonstrates how to create a new responder object for
the AutoCAD eTransmit protocol. This samples uses ATL to implement
the COM server and object.

It also shows how to manually create a Transmittal package (containing all required files) 
for a selected list of drawings suitable for sending to another user.

The sample currently registers the following command:

-ADDNOTIFIER:    To activate the responder object.
-REMOVENOTIFIER: To deactivate the responder object.
-MYTRANSMIT: To manually create a Transmittal Package from a set of drawings, and other files. 

Extra Notes:-MYTRANSMIT

The command asks for the user to select a series of files to be attached to a Transmittal package by the eTransmit API. 
Next the user is asked where the eTransmit API is to put the folder structure of the 
Transmittal package(1). 
Once these have been selected, the sample creates the Transmittal package (just a folder 
structure containing the files required as in (1)) and displays the files as they are perceived 
by the Transmittal graph. The user must the Zip and send the files themselves.


