
Description:
 (C) Copyright 1998 by Autodesk, Inc.
  worldDraw/viewportDraw() (showing use of getNumPixelsInUnitSquare)

  This example demonstrates using viewportDraw,
  getModelToEyeTransform, doPerspective, RegenType, and
  polylineEye.
 
  In a regular display of a pyramid made of 6 lines,
  you cannot easily determine which lines are on the
  back side of the pyramid.  This example colors the
  pyramid edges blue if they're on the far side and
  yellow if they're on the front side, so that you get
  a sense of the visible and hidden edges of the pyramid.
  This example could have been done with viewport's world
  coordinate polyline geometry, but since the calculations
  on the vertices to figure out (per viewport) which edges
  were visible resulted in eye coordinates, I chose to
  exemplify polylineEye() which accepts them.  The only
  drawback about eye coordinate line geometry is that it
  cannot currently be linetyped; to do that you use
  polyline() with world coordinate vertices.

Procedure:
 1. Load viewgeom.arx
 2. Command: ASDKGEOM
 3. Command: ZOOM Extents
 4. Command: VPOINT 1,2,3

    Note the blue lines are the back side edges.

    The Developer's Guide and the source code explains what took
    place in more detail.
