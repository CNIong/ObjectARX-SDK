
Description:
 (C) Copyright 1998 by Autodesk, Inc.
  This program demonstrates deriving from AcDbObject and 
  establishing ownership trees.
 
  In order to show all aspects of this mechanism, a custom
  object class is used that has two data members one to
  store an integer (simulating real data) and the other
  stores a hard ownership objectId.
 
  Ownership consists of two parts:
 
  1) The owner object stores the owned object's objectId
  and files it out/in to DWG and DXF
 
  2) The owned object has it's setOwnerId() member called
  with the owned object's objectId as the parameter.  This
  sets up the backpointer link so that the owned object
  knows who it's owner is.  This is used by such things as
  WBLOCK to walk "up" the ownership tree.
 
  Setting backpointers is taken care of by AutoCAD during
  operations that use the dwg and dxf filers, so a custom
  object/entity class doesn't need to worry about this for
  it's dwgInFields and dxfInFields members.  But, any class
  member functions that set any ownership Id data members
  in the class should take care of setting the owned
  object's backpointers by opening the owned objects and
  calling their setOwnerId() member functions using the
  owner object's objectId as the parameter for the calls.

1. Load ownrshp.arx
2. Command: ASDK_CREATE
3. Command: ASDK_LISTREE

   A similar output below should be printed.

   Intdata: 1  ObjId: 38012248  Backpointer: 38012240 OwnedObj: 38012232
   Intdata: 2  ObjId: 38012232  Backpointer: 38012248 OwnedObj: 38012224
   Intdata: 3  ObjId: 38012224  Backpointer: 38012232 OwnedObj: 0

   The Developer's Guide and the source code explains what took
   place in more detail.

