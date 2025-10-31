Copyright 2023 Autodesk, Inc.  All rights reserved.

Use of this software is subject to the terms of the Autodesk license 
agreement provided at the time of installation or download, or which 
otherwise accompanies this software in either electronic or hard copy form.   
//////////////////////////////////////////////////////////////////////////////

Description:

This program demonstrates reading and writing AcDbDatabase Objects. It implements createDwg() and readDwg().


1. Load testdb.arx
2. Command: ASDK_CREATE (or simply CREATE)
test1.dwg, containing two circles, should have been created in the current working directory.
3. Command: ASDK_READ (or simply READ)
This will open the drawing test1.dwg and read it into a new AcDbDatabase. It will then iterate through model space and print out the class names of all the entities it finds.

The results of running this command should be that it prints:

classname: AcDbCircle
classname: AcDbCircle
   
The ObjectARX Developer's Guide and the source code explain what took place in more detail.

