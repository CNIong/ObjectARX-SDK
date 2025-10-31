Copyright 2023 Autodesk, Inc.  All rights reserved.

Use of this software is subject to the terms of the Autodesk license 
agreement provided at the time of installation or download, or which 
otherwise accompanies this software in either electronic or hard copy form.   


Description:

This program demonstrates how to use ObjectARX API functions to highlight and unhighlight subentities of complex entities such as ACIS solids.

One command, RUN, is defined. It calls the function highlightTest(). highlightTest() uses acedSSGet to allow the user to select a complex entity.  It then passes the selection set to acedSSNameX to get the graphics system marker for the subentity actually selected with the pointing device. This graphics system marker is then used to get the appropriate AcDbFullSubentIdPath object, which can be used with the highlight and unhighlight functions of AcDbObject.

1. Load hilight.arx.
2. Create a 3D solid.
Command: RECTANG 1,1 5,5
Command: ZOOM Extents
Command: EXTRUDE height 3, angle 0
Command: VPOINT 1,1,1
3. Command: ASDK_RUN
4. Select an edge of the 3D object.

As you press enter, the selected edge will be highlighted. Then one of its two faces will be highlighted, followed by the other face. Finally the whole 3D object will be highlighted.

The ObjectARX Developer's Guide and the source code explain what took place in more detail.

