Copyright 2023 Autodesk, Inc.  All rights reserved.

Use of this software is subject to the terms of the Autodesk license 
agreement provided at the time of installation or download, or which 
otherwise accompanies this software in either electronic or hard copy form.   

Managed (.NET) Poly asdkPoly sample wrapper
-------------------------------------------

mgPoly - defines the .NET wrapper for asdkPoly and exposes a few of the asdkPoly functions.
mgPolyTestVB - is a VB.NET application which defines a command "testcreate". This command creates a .NET Poly wrapper object which in turn creates a asdkPoly object.

To test, load all arx's and dbx's. Then netload mgPoly.dll. Finally netload mgPolyTestVb.dll and invoke command "testcreate", to see the results of the command: Zoom->Extents

To build mgPolyTestVB successfully, add the reference path to acdbmgd.dll and acmgd.dll
in the ..\..\..\..\inc-win32 or ..\..\..\..\inc-x64 folder. You may also require to manually add a reference path to 
mgPoly.dll built by the mgPoly project.