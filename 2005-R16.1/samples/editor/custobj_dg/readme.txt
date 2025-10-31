(C) Copyright 1998 by Autodesk, Inc.

Description:

This program demonstrates creating a custom object class. Essentially, this means deriving a class from AcDbObject and providing your own implementations of dwgInFields, dwgOutFields, dxfInFields, and dxfOutFields.

1. Arxload custobj.arx.
2. Command: CREATE
3. Command: ITERATE
4. Command: ARX (then list the classes)
You should see AsdkMyClass in the class hierarchy.
5. Command: ARX (unload application)
6. Command: ARX (then list the classes)
Class AsdkMyClass will be missing from the class hierarchy.
7. Command: CREATE 
Prompt should say: Unknown command "CREATE".
