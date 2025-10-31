Material Sample Readme.txt

(C) Copyright 2002-2003 by Autodesk, Inc.

This sample demonstrates several things:

1) How to use the AcDbMaterial API to create materials and assign
them to custom entities. (MaterialUi project).
2) How to use the material dictionary to query, add, and remove 
materials. (MaterialUi project).
3) How to implement a custom entity ObjectDBX enabler 
(MaterialDb project).
4) How to implement an ObjectARX command (MaterialUi project).

The project has two components:

1) AsdkMaterialDb.dbx - Defines the custom entity AsdkMaterial,
which is a multi-polygon entity with materials applied to subentities.
2) AsdkMaterialUi.arx - Defines the command MAT that lets the user
create AsdkMaterial entities.

Special note: In Ui\MaterialCmd.cpp the AvLib API, 
AvRprefSyncDatabase, is used.  This API is used to enable or disable 
the synchronization of render and database materials.  Since the 
setting for this is stored in the registry under HKEY_LOCAL_MACHINE,
the program must have Power User privileges or greater to use this
API.  In practice, this API should only be called at your 
application's install time, when writing to HKLM is allowed.  The 
use of this API here is for demonstration purposes only.


Notes on Demand Loading Registration:

This sample demonstrates the use of the AcadAppInfo class to perform self-registration
for demand loading keys in the registry.  This is demonstrated for simplicity only.
Generally registration of these keys should be performed by an MSI installer.