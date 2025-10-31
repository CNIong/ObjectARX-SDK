 (C) Copyright 2004 by Autodesk, Inc.

Managed (.NET) Poly asdkPoly sample wrapper
-------------------------------------------

mgPoly - defines the .NET wrapper for asdkPoly and exposes a few of the asdkPoly functions.
mgPolyTestVB - is a VB.NET application which defines a command "testcreate". This command creates a .NET Poly wrapper object which in turn creates a asdkPoly object.

To test, load all arx's and dbx's. Then netload mgPoly.dll. Finally netload mgPolyTestVb.dll and invoke command "testcreate", to see the results of the command: Zoom->Extents

Note:  Assumes acmgd.dll and acdbmgd.dll are installed at C:\Program Files\AutoCAD 2006.

