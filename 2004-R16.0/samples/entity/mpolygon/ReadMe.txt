MPOLYGON ReadMe

(C) Copyright 2002 by Autodesk, Inc.

This application is to provide help in developing and understanding the API to the MPolygon
entity. There is no built-in command to create MPolygons in AutoCAD, so this sample demonstrates
how to create MPolygon objects programmatically using the API exposed from AcMPolygonObj16.dbx 
through AcDbMPolygon16.lib.

AcMPolygonObj16.dbx is loaded at run time (when the application is loaded into AutoCAD). 
Without loading this .dbx we can't append the MPOLYGON object to the drawing database.

The application defines two commands:

MPOLY

This command creates an MPolygon from the selected boundaries. These boundaries can be
AcDbCircle, AcDbPolyline or AcDb2dPolyline objects.


MPADDLOOP

When editing a polygon by adding, deleting, or moving boundaries, the composition of the 
polygon tree changes, but the boundary type (outer/inner) property of the boundaries does 
not automatically change. This may cause the polygon to become unbalanced, which means 
the nesting order of the boundaries does not follow an alternating outer/inner/outer order.

The area between an inner and outer boundary is filled or not filled in an alternating manner.
In a balanced polygon, the filled area represents the total area of the polygon object. 
However, the filled area may not accurately reflect the area of the polygon when it is 
unbalanced. The actual total area of the polygon is always calculated by subtracting the
sum of the area of all inner boundaries from the sum of the area of all outer boundaries

Given this explanation, the 'MPADDLOOP' command demonstrates adding new boundaries to an
existing MPolygon. It will add any number of AcDbCircle, AcDbPolyline or AcDb2dPolyline
boundaries to an existing MPolygon object and calls balanceTree() to balance it.

