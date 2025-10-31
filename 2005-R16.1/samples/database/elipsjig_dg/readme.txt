Description:
(C) Copyright 1998 by Autodesk, Inc.

AcEdJig Sample Program

This program demonstrates how to use AcEdJig to provide a user interface for AcDbEllipse creation that's slightly different from that provided by AutoCAD itself.
 
One limitation in its current form is that if the user tries to make the minor axis longer than the major axis, the resulting ellipse will be circular because the radius ratio cannot be larger than 1.0.

1. Load elipsjig.arx.
2. Command: ASDK_VELLIPSE
3. Select center point, major axis, and minor axis.

An ellipse should have been created.

  
