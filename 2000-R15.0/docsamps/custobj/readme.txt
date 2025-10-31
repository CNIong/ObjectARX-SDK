
Description:
 (C) Copyright 1998 by Autodesk, Inc.
  This program demonstrates what it takes to create a
  custom object class.  Essentially, this means deriving a
  class from AcDbObject and providing your own
  implementations of dwgInFields, dwgOutFields,
  dxfInFields, and dxfOutFields.

1.  Arxload custobj.arx
2.  Command: create
3.  Command: iterate
4.  Command: arx (and then list the classes)
    User must see AsdkMyClass in the class hierarchy
5.  Command: arx (unload application)
6.  Command: arx (then list the classes)
    Class AsdkMyClass will be missing from the class hierarchy
7.  Command: create (should say: Unknown command "CREATE".)
