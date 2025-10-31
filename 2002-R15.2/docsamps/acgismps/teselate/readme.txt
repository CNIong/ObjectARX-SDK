
Description:
 (C) Copyright 1998 by Autodesk, Inc.
  worlDraw()/viewportDraw() (arc tesselation)

  Example of a unit circle centered at the origin that
  depends on a viewport's view of the circle and tries
  to draw the circle with a polyline with the minimum
  number of discernible segments.

  With the VPORTS command,  you can create 4 viewports,
  click on one,  zoom in on it,  clock on another and back
  up from it,  then do a REGENALL. All of the viewports
  will calculate the minimally-segmented polyline
  representation of the circle.  This demonstrates one
  reason why getNumPixelsInUnitSquare is needed.  This
  does not show how to optimally code this task.

Procedure:
 1. Load teselate.arx
 2. Command: ASDKTESSELATESAMP
 3. Command: Zoom Extents
 4. Command: VPORTS 4
 5. Zoom in or out from each viewports
 6. Command: REGENALL

    The segment sizes will re-calculate showing different values

    The Developer's Guide and the source code explains what took
    place in more detail.
