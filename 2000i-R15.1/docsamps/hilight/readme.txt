
Description:
 (C) Copyright 1998 by Autodesk, Inc.

	This program demonstrates how to use ARX API functions to
	highlight and unhighlight subentities of complex entities
	such as ACIS solids.

	One command is defined called "RUN" which calls the function
	highlightTest.  highlightTest uses acedSSGet to allow the
	user to select a complex entity.  It then passes the
	selection set to acedSSNameX to get the graphics system
	marker for the subentity actually selected with the
	pointing device.  This graphics system marker is then
	used to get the appropriate AcDbFullSubentIdPath object
	which can be used with the highlight and unhighlight
	functions of AcDbObject.


1. Load hilight.arx
2. Create a 3D solid
     Command: RECTANG 1,1 5,5
     Command: ZOOM Extents
     Command: EXTRUDE height 3, angle 0
     Command: VPOINT 1,1,1

3. Command: ASDK_RUN
4. Select an edge of the 3D object

   As you press enter, the edge selected will be highlighted, then one
   of its two faces will be hilighted, then the other face will be
   hilighted, then the whole 3D object will be hilighted.

   The Developer's Guide and the source code explains what took
   place in more detail.

