Copyright 2023 Autodesk, Inc.  All rights reserved.

Use of this software is subject to the terms of the Autodesk license 
agreement provided at the time of installation or download, or which 
otherwise accompanies this software in either electronic or hard copy form.   
//////////////////////////////////////////////////////////////////////////////


Description:

This program demonstrates using xrecords. Two commands are defined in this program: ASDK_CREATE and ASDK_LISTXREC.

The ASDK_CREATE command calls the function createXrecord(), which instantiates an xrecord object and adds it to a dictionary object in the named objects dictionary.

The ASDK_LISTXREC command calls the listXrecord() function, which opens the dictionary containing the xrecord created by the ASDK_CREATE command and then calls the printList() function to print out the data stored in the xrecord.

To use xrecord.arx:

1. Start AutoCAD and open a new drawing.
2. Type the ARX command and load xrecord.arx.
3. Type the ASDK_CREATE command, defined by xrecord.arx. 
This will create a test xrecord.
4. Type the ASDK_LISTXREC command, defined by xrecord.arx. 
This will list out the xrecord created above.

WARNING: ASDK_LISTXREC command is not meant to be run before ASDK_CREATE. Doing so will cause an error in AutoCAD.

