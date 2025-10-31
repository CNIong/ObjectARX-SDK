		DrawingBrowser - .NET API Sample

This sample demonstrates how to enumerate through the object model of the AutoCAD.Database object in the .NET api.

The sample defines the 'BROWSEDWG' command, which launches a tree control dialog with the heirarchy of methods and properties of all the subordinate objects below AutoCAD.Database.  In particular, it demonstrates the use of 'Reflection' to obtain these methods/properties recursively.

To use the sample, build the sample, and load it into AutoCAD from the \bin subfolder using the NETLOAD command.  The sample will attempt to locate the icons within the \images subfolder using a relative path, so it is necessary to load the sample from the \bin (or equivalent) folder.

Note:  The reference path for this project is set to C:\Program Files\AutoCAD 2005, the default installation folder for AutoCAD.  If this sample is built against an non-default install location, or is built for AutoCAD OEM, then you will need to manually update the reference path for the acmgd and acdbmgd assemblies.
