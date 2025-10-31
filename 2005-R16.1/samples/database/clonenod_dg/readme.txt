Description:
(C) Copyright 1998 by Autodesk, Inc.

This example shows one way to deal with objects in the Named Object Dictionary during a wblockClone operation.

1. Load clonenod.arx.
2. Command: nodsetup
Command will create two new xrecords and add them to the nod.
3. Command: wblock and send the contents to a file
4. Command: open the file that was wblocked
5. Command: dxfout this file
6. Open the dxf file in text editor. 
There will be two xrecords in the file. These were added on the wblock operation during the beginDeepCloneXlation notification of the editor reactor.
