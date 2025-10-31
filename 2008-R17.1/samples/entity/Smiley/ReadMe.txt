Smiley sample Readme.txt

 (C) Copyright 2001-2003 by Autodesk, Inc.

Smiley
------

The Smiley application demonstrates several things:

 1) How to implement a custom entity ObjectDBX enabler (SmileyDb project).
	* Implementing Osnap and Grip points
	* Different proxy graphics

 2) How to use this custom entity from an ObjectARX application (SmileyUi project).

 3) How to implement a COM Automation interface for a custom entity (SmileyDbCom project).

 4) How to implement a COM Automation interface for an ObjectARX application
    (SmileyUiCom project).

 5) How to support the Properties Window with categorised properties (SmileyDbCom project).


Use the SMILEY command to insert a new Smiley entity into the drawing.

****

You can load AsdkSmileyDb.dbx and AsdkSmileyUi.arx directly into AutoCAD.

To set up the COM wrappers, you need to modify the .REG file in the Smiley directory
to point to the appropriate DLL and TLB locations.

All four files (AsdkSmileyDb.dbx, AsdkSmileyUi.arx, AsdkSmileyDbCom.dll,
AsdkSmileyUiCom.dll) should be placed in the same directory.

AsdkSmileyDb.dbx is designed to be loadable by any ObjectDBX host application,
of which AutoCAD is only one example.

Finally, note that AsdkSmileyDb.dbx and AsdkSmileyUi.arx are being registered in
different areas of the registry.


Notes on Demand Loading Registration:

This sample demonstrates the use of the AcadAppInfo class to perform self-registration
for demand loading keys in the registry.  This is demonstrated for simplicity only.
Generally registration of these keys should be performed by an MSI installer.


The UI application demand loads on unknown command invocations.

The custom object application demand loads on proxy detection.
