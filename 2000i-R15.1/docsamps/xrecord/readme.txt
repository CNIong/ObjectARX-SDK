
 (C) Copyright 1998 by Autodesk, Inc.
Description:

This program demonstrates using xrecords.  Two commands
are defined in this program:  CREATE, and LISTXREC.

To allow all three comparison programs to be loaded at the same time, 
the commands are slightly different for ObjectARX, LADSRX and AutoLISP:

    ARX:  ASDK_CREATE and ASDK_LISTXREC
    ADS:  ASDK_ADS_CREATE and ASDK_ADS_LISTXREC
    LISP: ASDK_LISP_CREATE and ASDK_LISP_LISTXREC

The CREATE command calls the function createXrecord()
which instantiates an xrecord object and adds it to a
dictionary object in the named objects dictionary.

The LISTXREC command calls the listXrecord() function
which opens the dictionary containing the xrecord created
by the CREATE command and then calls the printList()
function to print out the data stored in the xrecord.

There are three versions of this program. The first is in
pure ObjectARX, the second uses the old C style functions,
and the thrid uses AutoLISP.

To use xrecord.arx:

1. Start AutoCAD and open a new drawing.

2. Type the ARX command and load xrecord.arx.

3. Type the CREATE command, defined by xrecord.arx. This will create
    a test xrecord.

4. Type the LISTXREC command, defined by xrecord.arx. This will list 
    out the xrecord created above.

LISTXREC command is not meant to run before CREATE. Doing so, will
cause AutoCAD to error.

