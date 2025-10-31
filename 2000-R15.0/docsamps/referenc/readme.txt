
Description:
 (C) Copyright 1998 by Autodesk, Inc.
	This program demostrates interobject references.
	
	It creates a class that extends AcDbEllipse by adding 
	in functionality to store a dynamic array of hard 
	pointer ObjectIds.

	The subErase() member function has been overriden and
	implemented such that whenever an object of this class is
	erased,  the object's pointed to by the hardpointer ids
	stored within the object will also be erased.

1. Load referenc.arx
2. Command: ASDK_ELLIPSES

   Several concentric ellipses centered at 4,4,0 should appear
   in the graphics screen.

   Listing one of the ellipse using LIST command should print
   10 ReferenceId.

   The Developer's Guide and the source code explains what took
   place in more detail.

