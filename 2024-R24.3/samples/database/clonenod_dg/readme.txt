Copyright 2023 Autodesk, Inc.  All rights reserved.

Use of this software is subject to the terms of the Autodesk license 
agreement provided at the time of installation or download, or which 
otherwise accompanies this software in either electronic or hard copy form.   
//////////////////////////////////////////////////////////////////////////////


This example shows one way to deal with objects in the Named Object Dictionary during a wblockClone operation.

1. Load clonenod.arx.
2. Command: nodsetup
Command will create two new xrecords and add them to the nod.
3. Command: wblock and send the contents to a file
4. Command: open the file that was wblocked
5. Command: dxfout this file
6. Open the dxf file in text editor. 
There will be two xrecords in the file. These were added on the wblock operation during the beginDeepCloneXlation notification of the editor reactor.
