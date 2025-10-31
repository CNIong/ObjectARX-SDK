Copyright 2017 Autodesk, Inc.  All rights reserved.

Use of this software is subject to the terms of the Autodesk license 
agreement provided at the time of installation or download, or which 
otherwise accompanies this software in either electronic or hard copy form.   


		TabExtension - .NET API Sample

This sample demonstrates how to extend the extensible tabbed dialogs of AutoCAD using VB.NET.

The following commands are defined:

TabDemo - Hooks the appropriate events to insert a tab on the Option, Drafting Settings and Customization dialogs. Run this command once and then invoke the dialog to see the new tab.

To run the sample.  Build the application, and load it into AutoCAD using the NETLOAD command.  You will find the tabextension.dll module in the \bin subfolder.