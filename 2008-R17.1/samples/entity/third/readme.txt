Third sample Readme.txt

(C) Copyright 2001-2006 by Autodesk, Inc. 

This sample shows how to implement a simple custom object snap to divide curves of all types
into thirds. If the mode is active, then two "1/3" snap points will exist for each open curve,
and three for each closed curve.

Commands:
---------
SNAP2PLINE      Chooses to snap to a third of each polyline segment
SNAP2SEG        Chooses to snap to a third of the whole polyline

Classes:
--------
AsdkThirdOsnapInfo          Abstract base class for the protocol extension.
AsdkThirdOsnapEntityInfo    Generic definition providing no functionality.
AsdkThirdOsnapCurveInfo     Generic function for all curves, except AcDbPolylines.
AsdkThirdOsnapPolylineInfo  Specialized function for AcDbPolylines and derived classes.

AsdkThirdOsnapMode          Object snap mode describing the third object snap.
AsdkThirdGlyph              Glyph definition.

To use test this sample applilcation do the following:
1. Draw a polyline.
2. Run the APPLOAD command and Load third.arx
3. Run the line command, before selecting a point move the cursor over the previously drawn polyline

Results. 
A snap point with the text of 1/3 appears on the polyline