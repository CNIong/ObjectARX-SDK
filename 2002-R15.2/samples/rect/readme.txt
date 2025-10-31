Rect sample Readme.txt

 (C) Copyright 2001 by Autodesk, Inc.

This program duplicates but enhances the autolisp rectangle command, formerly
in acadr14.lsp, but uses AcEdJig to adjust for the current ucs normal. In addition,
elevation, and thickness are supported. Note that system variables are NOT changed
by this command. That is PLINEWID, CHAMFERA, CHAMFERB, ELEVATION, are NOT affected
by this command.

The sample demonstrates how to port the non MDI aware source (badrectang.cpp) to
the AutoCAD 2002 family making it MDI aware (rectangle.cpp).
