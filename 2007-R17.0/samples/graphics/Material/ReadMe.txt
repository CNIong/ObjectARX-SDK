Material Sample Readme.txt

(C) Copyright 2002-2006 by Autodesk, Inc.

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
2) AsdkMaterialUi.arx - Defines the following commands which allow the user
to create, enumerate and modify AsdkMaterial entities:

MATCREATE - 	Instantiates a custom entity with the current material.

MATLIST -	Lists the database materials.
	
MATADD -	Adds a database material

TEXMATADD - 	Adds a database texture material

MATDELETE - 	Removes a database material

MATMODIFY - 	Demonstrates modification of materials, cycling through several presets.

MATREPLACE - 	Replaces a given material or all materials in the database



Notes on Demand Loading Registration:

This sample demonstrates the use of the AcadAppInfo class to perform self-registration
for demand loading keys in the registry.  This is demonstrated for simplicity only.
Generally registration of these keys should be performed by an MSI installer.