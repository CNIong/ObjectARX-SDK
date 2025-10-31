Copyright 2023 Autodesk, Inc.  All rights reserved.

Use of this software is subject to the terms of the Autodesk license 
agreement provided at the time of installation or download, or which 
otherwise accompanies this software in either electronic or hard copy form.   
//////////////////////////////////////////////////////////////////////////////


beginDeepCloneXlation() Notification and Wblock Modification Sample Code
 
This code demonstrates how to add additional objects during beginDeepCloneXlation().

Procedure:
1. Load clonreac.arx.
2. Command: ASDK_WATCH
3. Create a circle.
4. Create a new text style named "MY_STYLE".
5. Wblock using the circle.
Answer yes (the default) when asked to Wblock all text styles.
6. New drawing.
7. Insert the block.
8. List styles.

The added style should exist after insert.

The ObjectARX Developer's Guide and the source code explain what took place in more detail.
    
