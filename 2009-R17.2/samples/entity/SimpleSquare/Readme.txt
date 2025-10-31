SimpleSquare sample Readme.txt

 (C) Copyright 2001-2006 by Autodesk, Inc.

SimpleSquare
------

The SimpleSquare application demonstrates in short how to create an ARX custom entity, and create the UI portion to support it using nothing but VB.NET.  In more detail, the sample demonstrates:

 1) How to create a very simple custom entity.  It implements only a square with 4 grip points.

 2) How to create a managed wrapper in managed C++ to expose the functionality of that entity to .NET managed applications.

 3) How to expose events from the entity through managed C++ that .NET applications can receive notifications from the entity.

 4) How to implement a jig using VB.NET to place the square entity.

 5) How to subscribe to the exposed events (in #3) so that we can receive notifications from our custom entity in VB.NET.  The notification code shows an AutoCAD bubble notification window.

****

The Projects:

The code consists of two projects; a mixed managed C++ project (SimpleSquare) and a VB.NET project (SimpleSquareUI).  

SimpleSquare:

The SimpleSquare project implements the AsdkSimpleSquare class which defines the simple square custom entity.  The MgSimpleSquare class 
defines the managed wrapper which exposes the custom entity to the managed world.  Since the object enabler and the wrapper are both 
defined within the same module (AsdkSimpleSquare.dll), the object enabler will always have a wrapper available.

Demand loading for the object enabler is setup through the AcadAppInfo ObjectARX class during module-load for the object enabler. 

SimpleSquareUI:

The SimpleSquareUI implements all of the User Interface code to support the object enabler.  This includes a command which implements a Jig
to place the SimpleSquare, and demonstrates a simple handler for the events that are exposed by the wrapper for modification of the Square object.


To use the sample:

	Build both projects in Visual Studio.

	Launch AutoCAD

	NETLOAD - navigate to the output of the SimpleSquareUI project and load 'SimpleSquareUI'.

	RUN the 'JIGSQ' command to launch the jig which places the simple square.  Each square implements an event handler which fires
	notifications to the StatusBar when the square is modified.  Grip-edit the square on-screen to demonstrate.


Notes on further implementation along these lines:

This sample demonstrates only what is required to bridge the gap between unmanaged (ARX, C++) applications and those in the .NET managed world.
Since many User Interface implementation and productivity enhancements have been made in .NET, this is a particularly attractive option for
many developers who want to keep their existing C++ code, and build upon it with newer .NET technology.


Notes on Demand Loading Registration:

This sample demonstrates the use of the AcadAppInfo class to perform self-registration
for demand loading keys in the registry.  This is demonstrated for simplicity only.
Generally registration of these keys should be performed by an MSI installer.


The custom object application demand loads on proxy detection.
