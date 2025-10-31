ARX Developer's Guide

 (C) Copyright 1998 by Autodesk, Inc.
Description:
  This program edemostartes reading and wirintg AcDbDatabase Objects.
  It implements createDwg() & readDwg().


1. Load testdb.arx
2. Command: ASDK_CREATE (or simply CREATE)

   test1.dwg should have been created in the current working
   directory containing 2 circles.

3. Command: ASDK_READ (or simply READ)

   This will open the drawing test1.dwg and read it into a new AcDbDatabase
   object.  It will then iterate through Model Space and print out the class
   names of all the entities it finds.

   WARNING:  due to lack of error checking in this sample,  if test1.dwg is
             not available (i.e. is not on the disk or is locked),  then
             this application will crash AutoCAD.

   The results of running this command should be that it prints:

   classname: AcDbCircle
   classname: AcDbCircle
   
   The Developer's Guide and the source code explains what took
   place in more detail.

