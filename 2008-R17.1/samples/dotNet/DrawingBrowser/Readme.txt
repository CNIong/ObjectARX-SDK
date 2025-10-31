		DrawingBrowser - .NET API Sample

 (C) Copyright 2004 by Autodesk, Inc.

This sample demonstrates how to enumerate through the object model of the AutoCAD.Database object in the .NET api.

The sample defines the 'BROWSEDWG' command, which launches a tree control dialog with the heirarchy of methods and properties of all the subordinate objects below AutoCAD.Database.  In particular, it demonstrates the use of 'Reflection' to obtain these methods/properties recursively.

To use the sample, build the sample, and load it (DrawingBrowser.dll) into AutoCAD from the \bin subfolder using the NETLOAD command.  The sample will attempt to locate the icons within the \images subfolder using a relative path, so it is necessary to load the sample from the \bin (or equivalent) folder.

Note for use in AutoCAD OEM:  Copy the \Images subfolder to the stamped OEM application's root folder to test (i.e. ...\oem\TestProd\Images).  For the sample's DLL (DrawingBrowser.dll), select the 'Support' as the Build Destination.