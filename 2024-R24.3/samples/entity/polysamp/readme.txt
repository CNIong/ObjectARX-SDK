Copyright 2023 Autodesk, Inc.  All rights reserved.

Use of this software is subject to the terms of the Autodesk license 
agreement provided at the time of installation or download, or which 
otherwise accompanies this software in either electronic or hard copy form.   


The polysamp application demonstrates several things:

 1) How to implement a custom entity class (polyobj project).

 2) How transactions work (polyui project).

 3) How to use the AcDbEntity::highlight() and AcDbEntity::unHighlight()
    methods (polyui project).

 4) How to implement an OLE Automation interface for a custom
    class (compoly project).

 5) How to implement a .NET wrapper (manged project) 

 6) How to create a command in VB.NET that creates a .NET Poly wrapper
    which in turn creates an asdkPoly object. (managedTestVB)

 7) How to split your application into a UI and a CustomObject section,
    so that the CustomObject section can be loaded by all ObjectDBX
    Host Applications.  This also illustrates how to export a custom
    entity class to another application (polyui and polyobj projects).

 8) How to build an Object Enabler so that AutoCAD users who don't have
    your application and encounter drawings that contain your CustomObjects
    can download your Object Enabler and avoid proxy entities/objects
    (objectenabler subdirectory).

 9) How to implement AcDbAssocPersSubentIdPE for a custom entity. 
    This protocol extention reveals subentities of the entity to the 
    Associative Framework. When the entity exposes this protocol extension, 
    it can participate in associative relations represented by the Associative 
    Framework, such as geometric and dimensional constraints can be created 
    between the custom entities and other entities in the drawing.

10) How to implement AcDbAssocPersSubentIdPE::createNewPersSubent() so that
    the returned AcDbAssocPersSubentId persistently identifies the subentity
    of the custom entity. When the topology of the entity changes (number of 
    sides changes), AcDbAssocPersSubentIdPE::getTransientSubentIds() takes
    the AcDbAssocPersSubentId and returns a "corresponding" subentity in the
    current state of the entity.

11) How to make a custom entity constrainable by using a general and 
    reusable ConstrainedRigidEntityAssocPersSubentIdPE class that
    handles the case when the constrained custom entity changes shape
    during dragging.

12) How to allow associative dimensions on a custom entity by the custom
    entity exposing AcDbAssocPersSubentIdPE.

****

The top level directory contains and builds two applications, asdkpolyobj.dbx 
and polyui.arx.

You must build asdkpolyobj.dbx first, since it exports symbols used by polyui.arx,
and is required in order to link polyui.arx.

Take note that asdkpolyobj.dbx does not link with acad.lib, 
acui21.lib, nor any library which directly or indirectly causes a 
dependency on acad.exe.

Polyui.arx links with acad.lib.

Polyui.arx will run only in the presence of AutoCAD. Because Polyui.arx is linked
directly to asdkpolyobj.dbx, loading polyui.arx will cause the OS to implicitly 
load asdkpolyobj.dbx.  Therefore, when these two applications work as a pair
within AutoCAD, it is necessary that asdkpolyobj.dbx be located where the OS
can find it, that is in one of the following locations

1) The Autodesk Shared directory.
   (C:\Program Files\Common Files\Autodesk Shared\)
2) A directory listed in the PATH environment variable.
3) The AutoCAD search path.

In addition, polyui.arx explicitly triggers the initialization code in 
asdkpolyobj.dbx by calling acrxLoadModule("asdkpolyobj.dbx").  This is required.

Asdkpolyobj.dbx is designed to be loadable by any ObjectDBX host application,
of which AutoCAD is an example of an ObjectDBX host.  When Asdkpolyobj.dbx is
loaded directly, as opposed to the implicit loading which occurs when paired
with polyui.arx, the rules for location are less strict.  In this case, the
opportunity exists to include the path to asdkpolyobj.dbx in the loading call.

Finally, note that asdkpolyobj.dbx and polyui.arx are being registered in
different areas of the registry.


The UI application demand loads on unknown command invocations.

The Custom Object application demand loads on Proxy detection.

This sample demonstrates the use of the AcadAppInfo class to perform self-registration
for demand loading keys in the registry.  This is demonstrated for simplicity only.
Generally registration of these keys should be performed by an MSI installer.

The UI Application defines the following commands:

POLY		- Creates the base polygon object
PPOLY		- Poly command which interacts with the Properties Palette
DRAGPOLY	- Creates a polygon object by way of a Jig
POLYEDIT	- various editing commands from a commandline / context menu options set
TRANSACT	- Demonstrats multi-edit commands using transactions that can be rolled back
HILITPOLY	- Higlighting on a polygon entity
HILITSOLID	- Highlighting on a polygon solid
CREATEINSERT	- Nested Insert creation
HILITINSERT	- Highlight of insert
USEDRAGDATA	- cloneMeForDragging behavior
POLYCLEANUI	- Cleans the menus and toolbars in this sample



****

The subdirectory \compoly contains the files that demonstrate how
to implement an OLE Automation interface for the asdkpolyobj application.

In order to build the compoly.dbx, you must first build the
asdkpolyobj.dbx program to generate the asdkpolyobj.lib file that is needed
by compoly.dbx.

Before you can start using the Automation API you need to register Compoly 
with COM. To register Compoly you simple need to load it as an ObjectARX
application (via the ARX command).

This sample demonstrates the use of the DllRegisterServer to perform self-registration
for the defined COM servers in the registry.  This is demonstrated for simplicity only.
Generally registration of these keys should be performed by an MSI installer.

Compoly.dbx will only run in the presence of AutoCAD. Because Compoly.dbx is
linked directly to asdkpolyobj.dbx, loading compoly.dbx causes the OS to implicitly 
load asdkpolyobj.dbx.  Therefore, when these two applications work as a pair,
within AutoCAD, asdkpolyobj.dbx be located where the OS can find it, that is
in one of the following locations:

1) A directory listed in the PATH environment variable
2) The AutoCAD search path

****
