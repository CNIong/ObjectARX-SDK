
Polysamp Setup Readme.txt


(C) Copyright 2001-2008 by Autodesk, Inc.

This directory contains two Visual Studio Installer projects: PolyObjMSM and PolyOBJMSI.

PolyObjMSM builds an installer merge module for asdkpolyobj.dbx.

PolyOBJMSI builds a standalone installer by merging the merge module. This installer can be used as a LiveEnabler for this custom object.


Below are steps for recreating these projects from scratch.


PolyObjMSM
==========

1. In Visual Studio .NET, create a new Merge Module project. 

2. Name the project 'PolyObjMSM'. Make sure that you add this new project to the same solution that contains the C++ project that creates the custom object. This ensures that you can access the output of that project without having to use relative paths.

3. Right click on PolyObjMSM and choose Add\Project Output. Choose the output of the polyobj project.

4. Build your installer.

5. You will see that Visual Studio detected that asdkpolyobj.dbx depends on the C/C++ runtime library. Right click on this dependency and exclude it. ObjectDBX already installs this file you don't have to.

6. Now right click on PolyObjMSM again and choose View\Registry.

7. Create the following registry key:

HKLM\SOFTWARE\Autodesk\ObjectDBX\R18.0\Applications\AsdkPolyObj

8. Add the following named values:

Type	Name		Value
------------------------------
String	DESCRIPTION	ObjectARX SDK Polygon sample object
DWORD	LOADCTRLS	1
String	LOADER		[CommonFileFolder]\Autodesk Shared\asdkpolyobj.dbx
8. Build your merge module.


PolyObjMSI
==========

1. In Visual Studio .NET, create an new Installer project. 

2. Name the project 'PolyObjMSI'. Make sure that you add this new project to the same solution that contains the C++ project that creates the custom object. This ensures that you can access the output of that project without having to use relative paths.

3. Right click on PolyObjMSI and choose Add\Project Output. Choose the output of the PolyObjMSM project.

4. Build your installer.



