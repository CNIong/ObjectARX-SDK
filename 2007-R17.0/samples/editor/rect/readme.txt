Rect sample Readme.txt

 (C) Copyright 2001-2003 by Autodesk, Inc.

This program duplicates but enhances the autolisp rectangle command but uses AcEdJig
 to adjust for the current ucs normal. In addition,elevation, and thickness are supported.

Note that system variables are NOT changed by this command. That is PLINEWID, CHAMFERA,
CHAMFERB, ELEVATION, are NOT affected by this command.

To test the sample, build and load the ARX, then issue the 'RECTANG' or 'RECTANGLE' command.


The sample demonstrates how to port the non MDI aware source (badrectang.cpp) to
the AutoCAD 2000-beyond family making it MDI aware (rectangle.cpp).

This sample demonstrates the use of the AcadAppInfo class to perform self-registration
for demand loading keys in the registry.  This is demonstrated for simplicity only.
Generally registration of these keys should be performed by an MSI installer.