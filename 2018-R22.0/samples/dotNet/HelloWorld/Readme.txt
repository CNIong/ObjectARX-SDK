		HelloWorld - .NET API Sample

Copyright 2017 Autodesk, Inc.  All rights reserved.

Use of this software is subject to the terms of the Autodesk license 
agreement provided at the time of installation or download, or which 
otherwise accompanies this software in either electronic or hard copy form.   


This sample demonstrates the basics of using the .NET API with AutoCAD.  It defines three commands:

HELLO - Displays the obligitory 'Hello World' text to the AutoCAD command line.

HELLOFORM - Displays a .NET form dialog with custom text

HELLOTEXT - Instantiates an MTEXT entity, adds it to model space, and sets it's text contents to 'Hello World'

The sample creates a small toolbar, and includes a button for each command listed above.

To run the sample.  Build the application, and load from the \bin subfolder it into AutoCAD using the NETLOAD command.  This module attempts to load bitmap icons from the relative parent of the \bin folder, so make certain you load the HelloWorld.dll from this folder to test initially.

Note for AutoCAD OEM:  Copy the toolbar button bitmaps (tbBut0.bmp and tbBut1.bmp) to the stamped OEM product folder (e.g. ...\oem\TESTPROD\).  In the OEMMakeWizard, select the 'Support' folder as the build Destination for the HelloWorld.dll sample file.  


