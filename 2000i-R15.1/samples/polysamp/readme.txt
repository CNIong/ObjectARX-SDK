(C) Copyright 1998-99 by Autodesk, Inc.



The polysamp application demonstrates several things:

 1) How to implement a custom entity class (polyobj project).

 2) How transactions work (polyui project).

 3) How to use the AcDbEntity::highlight() and AcDbEntity::unHighlight()
    methods (polyui project).

 4) How to implement an OLE Automation interface for a custom
    class (compoly project).

 5) How to split your application into a UI and a CustomObject section,
    so that the CustomObject section can be loaded by all ObjectDBX
    Host Applications.  This also illustrates how to export a custom
    entity class to another application (polyui and polyobj projects).

 6) How to build an Object Enabler so that AutoCAD users that don't have
    your application and encounter drawings that contain your CustomObjects
    can download your Object Enabler and avoid proxy entities/objects
    (objectenabler subdirectory).

****

The top level directory contains and builds two applications, asdkpolyobj.dbx 
and asdkpolyui.arx.

You must build asdkpolyobj.dbx first, since it exports symbols used by asdkpolyui.arx,
and is required in order to link asdkpolyui.arx.

Take note that asdkpolyobj.dbx does not link with acad.lib, acedapi.lib, 
acui15.lib, nor any library which directly or indirectly causes a 
dependency on acad.exe.

asdkpolyui.arx links with acad.lib and with acedapi.lib.

asdkpolyui.arx will run only in the presence of AutoCAD. Because it is linked
directly to asdkpolyobj.dbx, loading asdkpolyui.arx will cause the OS to implicitly 
load asdkpolyobj.dbx.  Therefore, when these two applications work as a pair,
within AutoCAD, it is necessary that asdkpolyobj.dbx be located where the OS
can find it:

1) Autodesk Shared directory
   (ie "C:\Program Files\Common Files\Autodesk Shared\")
2) A directory listed in the PATH environment variable
3) The AutoCAD search path

In addition, asdkpolyui.arx explicitly triggers the initialization code in 
asdkpolyobj.dbx by calling acrxLoadModule("asdkpolyobj.dbx").  This is required.

Asdkpolyobj.dbx is designed to be loadable by any ObjectDBX host application,
of which AutoCAD is only a single example.  When it is loaded directly,
as opposed to the implicit loading which occurs when paired with asdkpolyui.arx,
the rules for location are less strict.  In this case, the opportunity
exists to include the path to asdkpolyobj.dbx in the loading call.

Finally, note that asdkpolyobj.dbx and asdkpolyui.arx are being registered in
different areas of the registry.

The acrxRegisterApp() function now has a fifth argument, which defaults
to FALSE.  If FALSE, the app registers under AutoCAD, if TRUE, it registers
under the generic ObjectDBX registry location, where it can be found
by all ObjectDBX host applications.

The UI application demand loads on unknown command invocations.

The Custom Object application demand loads on Proxy detection.

****

The subdirectory "compoly" contains the files that demonstrate how
to implement an OLE Automation interface for the asdkpolyobj application.

In order to build the asdkcompoly.dbx, you must first build the
asdkpolyobj.dbx program to generate the asdkpolyobj.lib file that is needed
by asdkcompoly.dbx.

Before you can start using the Automation API you need to register asdkcompoly 
with COM.
To register Compoly you simple need to load it as an ObjectARX application (via the 
ARX command).

asdkCompoly.dbx will run only in the presence of AutoCAD. Because it is linked
directly to asdkpolyobj.dbx, loading asdkcompoly.dbx will cause the OS to implicitly 
load asdkpolyobj.dbx.  Therefore, when these two applications work as a pair,
within AutoCAD, it is necessary that asdkpolyobj.dbx be located where the OS
can find it:

1) Autodesk Shared directory
   (ie "C:\Program Files\Common Files\Autodesk Shared\")
2) A directory listed in the PATH environment variable
3) The AutoCAD search path

****

The subdirectory "objectenabler" contains the files that demonstrate how to
build an Object Enabler, a self extracting archive that can be used to
provide a .dbx application that will enable your application's custom objects
in drawings for which the AutoCAD user does not currently have your application
installed.

