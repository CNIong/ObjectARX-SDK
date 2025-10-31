Copyright 2023 Autodesk, Inc.  All rights reserved.

Use of this software is subject to the terms of the Autodesk license 
agreement provided at the time of installation or download, or which 
otherwise accompanies this software in either electronic or hard copy form.   


Description:
 
worldDraw/viewportDraw() (showing use of getNumPixelsInUnitSquare)

This example demonstrates using viewportDraw(), getModelToEyeTransform(), doPerspective(), RegenType(), and polylineEye().
 
In a regular display of a pyramid made of six lines, you cannot easily determine which lines are on the back side of the pyramid. This example colors the pyramid edges blue if they're on the far side and yellow if they're on the front side, so that you get a sense of the visible and hidden edges of the pyramid.

This example could have been done with viewport's world coordinate polyline geometry. However, because the calculations on the vertices to figure out (per viewport) which edges were visible resulted in eye coordinates, this example uses polylineEye(), which accepts eye coordinates. The only drawback with eye coordinate line geometry is that it does not accept line types. For line types, use polyline() with world coordinate vertices.

Procedure:
1. Load viewgeom.arx.
2. Command: ASDKGEOM
3. Command: ZOOM Extents
4. Command: VPOINT 1,2,3

Note the blue lines are the back side edges.

The ObjectARX Developer's Guide and the source code explain what took place in more detail.
