AsdkBodyApp Sample

 (C) Copyright 1998 by Autodesk, Inc.
This sample demonstrates the use of AsdkAmodeler. The sample has two parts:
1. AsdkBodyObj.dbx
This defines a custom object AsdkBody and is loadable into ObjectDBX

2. AsdkBodyApp.arx
This defines some custom commands to create and modify the AsdkBody objects.

To use these applications, amodeler.arx must be in the AutoCAD directory.
This is because of the simple way the modeler gets loaded. First the OS
must find it and second AutoCAD must find it for the acrxLoadModule("AModeler.arx",1); 
call to succeed.


 

