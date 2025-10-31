This sample shows how to implement a simple custom object snap to divide curves of all types
into thirds. If the mode is active then two "1/3" snap points will exist for each open curve,
and three for each closed curve.

Commands:
---------
SNAP2PLINE      Chooses to snap to a third of each polyline segment
SNAP2SEG        Chooses to snap to a third of the whole polyline

Classes:
--------
AsdkThirdOsnapInfo          abstract base class for the protocol extension
AsdkThirdOsnapEntityInfo    generic definition providing no functionality
AsdkThirdOsnapCurveInfo     generic function for all curves, except AcDbPolylines
AsdkThirdOsnapPolylineInfo  specialised function for AcDbPolylines and derived classes

AsdkThirdOsnapMode          object snap mode describing the third object snap
AsdkThirdGlyph              glyph definition
