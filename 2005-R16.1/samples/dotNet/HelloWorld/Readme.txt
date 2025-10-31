		HelloWorld - .NET API Sample

This sample demonstrates the basics of using the .NET API with AutoCAD.  It defines four commands:

HELLO - Displays the obligitory 'Hello World' text to the AutoCAD command line.

HELLOFORM - Displays a .NET form dialog with custom text

HELLOTEXT - Instantiates an MTEXT entity, adds it to model space, and sets it's text contents to 'Hello World'

GETHELLO - Iterates through Model Space (now a collection) and finds every instance of MTEXT.

The sample creates a small toolbar, and includes a button for each command listed above.


To run the sample.  Build the application, and load from the \bin subfolder it into AutoCAD using the NETLOAD command.  This module attempts to load bitmap icons from the relative parent of the \bin folder, so make certain you load the HelloWorld.dll from this folder to test initially.


Note:  The reference path for this project is set to C:\Program Files\AutoCAD 2005, the default installation folder for AutoCAD.  If this sample is built against an non-default install location, or is built for AutoCAD OEM, then you will need to manually update the reference path for the acmgd and acdbmgd assemblies.


