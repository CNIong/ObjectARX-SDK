
Description:
 (C) Copyright 2003-2006 by Autodesk, Inc.

	The TextFileField sample defines a custom field in a DBX module and provides the accompanying
User Interface integration in an ARX module. The custom field reads in the contents of an external text
file and returns that to the framework, providing funcitonality that is comparable to the RTEXT object
found in the AutoCAD EXpress Tools.

How to use the sample:

1. Load AsdkTextFileField.dbx and AsdkTextFileFieldUI.arx.
2. Create an MText object, using the "MT" command. Place it in the drawing.
3. Right-click within the MText editor and select "Insert Field...".
4. Within the Insert Field UI, select
 the new "External Files" category.
   You should now see the "Text File Field" appear in the list.
5. Browse or enter the path to a text file.
6. Select OK. The contents of the file should now be displayed as the field value.
