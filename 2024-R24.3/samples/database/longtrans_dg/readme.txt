Copyright 2023 Autodesk, Inc.  All rights reserved.

Use of this software is subject to the terms of the Autodesk license 
agreement provided at the time of installation or download, or which 
otherwise accompanies this software in either electronic or hard copy form.   
//////////////////////////////////////////////////////////////////////////////
Description:

This sample program shows how to use long transactions.

1. Build and Load the ObjectARX application.
2. Command: LONGTRANS 
3. Choose a drawing that contains line entities.
4. The program will check out the line entities from the drawing you chose and bring them into the current model space.  
5. The program will then ask for a color (integer) and change these entities within the workset.  
6. Finally it will pause to let you see the new color (just hit return).
7. After the pause, the entities will be checked back into the orginal database and saved. 

Open the original database and see the new colors that were modified by the previous databse in the reference editing operation.

