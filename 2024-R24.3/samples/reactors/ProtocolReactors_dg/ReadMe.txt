Copyright 2023 Autodesk, Inc.  All rights reserved.

Use of this software is subject to the terms of the Autodesk license 
agreement provided at the time of installation or download, or which 
otherwise accompanies this software in either electronic or hard copy form.   


This sample demonstrates custom block insertion points. To do so, it creates a block definition named ASDK_CUSTOM_BLOCK. It also implements an AcDbBlockInsertionPoints protocol extension reactor and registers it with the protocol reactor framework. This sample defines a single AutoCAD command named BLKINSPTS.

Another feature demonstrated in this sample is alignment points. These are defined in conjunction with the insertion points. When you attempt to insert the block using one of the custom insertion points, the alignment points cause the block to attempt to rotate itself so that it is correctly aligned with nearby geometry.

To use this sample:

1. Build the sample.
2. Load the ProtocolReactors.arx file in AutoCAD.
3. Run the BLKINSPTS command.

To use the custom insertion points:

4. Insert an instance of ASDK_CUSTOM_BLOCK.
5. To cycle through the custom insertion points, press the CTRL key repeatedly while at the prompt for specifying the insertion point.
6. To see the alignment point feature to best advantage, turn off OSNAP (F3) while inserting, and try to insert the block close to another entity.

