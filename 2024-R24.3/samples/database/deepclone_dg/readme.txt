Copyright 2023 Autodesk, Inc.  All rights reserved.

Use of this software is subject to the terms of the Autodesk license 
agreement provided at the time of installation or download, or which 
otherwise accompanies this software in either electronic or hard copy form.   
//////////////////////////////////////////////////////////////////////////////


This application demonstrates deep cloning.
  cloneSameOwnerObjects()
  cloneDiffOwnerObjects()

Procedure:
1. Load deepclon.arx.
2. Draw one circle and one line.
3. Command: ASDK_DIFFOWNER
4. Select the circle for model space, then press enter.
5. Select the line for paper space, then press enter.

Two object IDs should be printed. The object IDs are retreived from an object ID map that was created during the deep clone process.

The ASDK_SAMEOWNER command is similar.

The ObjectARX Developer's Guide and the source code explain what took place in more detail.
   
