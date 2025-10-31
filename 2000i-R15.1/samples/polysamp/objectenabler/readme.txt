
This example shows how to create a  self extracting archive that
contains the .dbx application that will enable your custom object
and prevent it from becoming a proxy. The process is to compress your 
ObjectDBX application(s), any support files, and a special ObjectDBX
application called "register.dbx" into a .cab file, prepend extract.exe
to it (making it a self extracting archive) and naming it appropriately
so that an ObjectDBX Host Application will detect, download, decompress 
and install your application(s).

Your self extracting archive and your cabinet files must have the same 
name as your application's logical appname. The case of the file names is 
important. For this example, AsdkPolyOBJ is the logical appname. The
cabinet file should be named AsdkPolyOBJ.cab and the self extracting archive
should be named AsdkPolyOBJ.exe.

A special dbx applet named "register.dbx" MUST be built and packaged
with your dbx application. An example project, registrar.dsp, is
provided. Basically, register.dbx is used to populate the system
registry with the settings needed by your dbx application.
Your register.dbx applet should populate the registry for a subsequent 
attempt by the system to load your ObjectDBX application. 

Your self extracting archive will be executed and extracted into
a temporary directory and the files will be moved to the
"%SYSTEM%/Program Files/Common Files/Autodesk Shared" directory.
The system will look for register.dbx (before moving the files),
load it to populate the registry, unload it, and then reattempt
to load your dbx application using the ObjectDBX dynamic linker.
If a register.dbx file is not found, the entire operation is aborted.

You will need to get the Cabinet SDK from Microsoft and install it
on your system.

You must create a .ddf file for your app's cabinet. See polyobj.ddf for a 
simple example. It assumes that AsdkPolyOBJ.dbx and register.dbx have
been built.

Run MakeCAB on the .ddf file. For example: makecab /f polyobj.ddf.

Use copy to concatenate the extract utility and your cabinet file into a
self extracting archive. For example:
copy /b extract.exe+YOURAPP.cab YOURAPP.exe
(this assumes that extract.exe and YOURAPP.cab are in the current directory).

To test your ObjectEnabler, obtain a test application from Autodesk.
You will need to specify a valid URL.
Local file systems are supported using the FILE: syntax. For example, if
AsdkPolyOBJ.exe is copied to d:\test, specify the URL "FILE://d|/test".
Ensure that the registry is free of any entries made by your application,
and that your application is removed from the ".../Common Files/..." directory.
Load a drawing that contains one of your custom objects. 
The ObjectDBX Host Application will search each of the URL paths
specified looking for the self extracting archive file. When it
finds YOUR_APP'S_LOGICAL_NAME.exe, it will be downloaded to a temporary
directory for extraction (%TEMP%\ObjectDBXdownLoad). The downloaded
file is executed, extracting register.dbx, YOURAPP.dbx, and any supporting
files. The files are moved to the ".../Autodesk Shared" directory and the 
temporary download directory is removed. Register.dbx is loaded to populate
the system registry with YOURAPP's settings.
YOURAPP.dbx is then loaded using the acrxDynamicLinker()->loadApp() method.
The drawing should load without turning your custom objects into proxy objects.
Your application should also now be registered with the system, so upon
loading the same drawing a second time, you should not be prompted to
search for the missing application.

That's all there is to it! Contact Autodesk to see about placing your
ObjectEnabler self extracting archive file on our official ObjectEnabler 
web site.
