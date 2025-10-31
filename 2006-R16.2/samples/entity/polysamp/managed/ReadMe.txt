 (C) Copyright 2004 by Autodesk, Inc.

Managed (.NET) Poly asdkPoly sample wrapper
-------------------------------------------

mgPoly - defines the .NET wrapper for asdkPoly and exposes a few of the asdkPoly functions.
mgPolyTestVB - is a VB.NET application which defines a command "testcreate". This command creates a .NET Poly wrapper object which in turn creates a asdkPoly object.

To test, load all arx's and dbx's. Then netload mgPoly.dll. Finally netload mgPolyTestVb.dll and invoke command "testcreate", to see the results of the command: Zoom->Extents

Note:  In order to compile this project, you must implement the _vcclrit.h header (included in the project) from the contents of this file at: http://support.microsoft.com/?id=814472.  The contents of this header are given under 'Users of Visual Studio.NET 2002'.  Copy the contents here, and comment out the #error given in the header.


