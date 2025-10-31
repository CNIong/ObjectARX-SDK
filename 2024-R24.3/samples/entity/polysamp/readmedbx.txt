Copyright 2023 Autodesk, Inc.  All rights reserved.

Use of this software is subject to the terms of the Autodesk license 
agreement provided at the time of installation or download, or which 
otherwise accompanies this software in either electronic or hard copy form.   


The polysamp application demonstrates several things:

 1) How to implement a custom entity class (polyobj project).


 2) How to implement an OLE Automation interface for a custom
    class (compoly project).

****

The top level directory contains and builds one application, asdkpolyobj.dbx.

Asdkpolyobj.dbx is designed to be loadable by any ObjectDBX host application,
of which AutoCAD is an example of an ObjectDBX host. Note that asdkpolyobj.dbx is registered for demandloading on Proxy detection. 

This version of the sample (the ObjectDBX version) does not perform demand-load registration.  Please refer to the ObjectARX project 'polyui' which performs this demand-load registration using the AcadAppInfo class.

For a demonstration of demand-load registry entries using a .reg file, see the 'Demandload' subfolder containing a .reg file and a separate readme for instructions.

****

The subdirectory \compoly contains the files that demonstrate how
to implement an OLE Automation interface for the asdkpolyobj application.

In order to build asdkcompoly.dbx, you must first build the
asdkpolyobj.dbx program to generate the asdkpolyobj.lib file that is needed
by asdkcompoly.dbx.

****




