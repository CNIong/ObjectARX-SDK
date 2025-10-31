Copyright 2023 Autodesk, Inc.  All rights reserved.

Use of this software is subject to the terms of the Autodesk license 
agreement provided at the time of installation or download, or which 
otherwise accompanies this software in either electronic or hard copy form.   


Description:
 
worldDraw()/viewportDraw() (arc tesselation)

This sample shows a unit circle centered at the origin that depends on a viewport's view of the circle. The program attempts to draw the circle with a polyline with the minimum number of discernible segments.

With the VPORTS command, create four viewports. Click on one and zoom in on it, and click on another and zoom out from it. Then do a REGENALL. All of the viewports will calculate the minimally-segmented polyline representation of the circle. This demonstrates one reason getNumPixelsInUnitSquare() is necessary. 

Note: This sample does not show how to optimally code this task.

Procedure:
1. Load teselate.arx.
2. Command: ASDKTESSELATESAMP
3. Command: Zoom Extents
4. Command: VPORTS 4
5. Zoom in or out from each viewport.
6. Command: REGENALL

The segment sizes will re-calculate showing different values.

The ObjectARX Developer's Guide and the source code explain what took place in more detail.
