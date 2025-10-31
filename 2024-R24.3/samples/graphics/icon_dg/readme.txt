Copyright 2023 Autodesk, Inc.  All rights reserved.

Use of this software is subject to the terms of the Autodesk license 
agreement provided at the time of installation or download, or which 
otherwise accompanies this software in either electronic or hard copy form.   


Description:

viewportDraw() (window coordinates)

This example demonstrates the main use of polylineDc(), polygonDc(), and getViewportDcCorners() -- graphics that depend on the physical layout of the viewport, like icons, markers, or borders that vary with the size of the viewport.

For the demonstration, this example draws a box in the upper right corner of the viewport. The box's width and height are always a tenth of the viewport's shortest dimension and are centered a tenth of the viewport's shortest dimension down and to the left of the upper right corner of the viewport.

Procedure:
1. Load icon.arx.
2. Command: ASDKICONSAMP
3. Command: TILEMODE 0
4. Command: MVIEW
   ON/OFF/Hideplot/Fit/2/3/4/Restore/<First Point>:
   Select First Point and Other Corner

You should see a red rectangular shape in the upper right corner proportional to the viewport.
   
The ObjectARX Developer's Guide and the source code explain what took place in more detail.
   
