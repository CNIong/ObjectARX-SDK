
An ObjectEnabler is a self extracting archive that ultimately
contains a .dbx application that will enable your custom object
and prevent it from becoming a proxy. The process for building an
ObjectEnabler is to compress your .dbx application into a .cab file, 
prepend extract.exe to it (making it a self extracting archive) and 
naming it appropriately so that AutoCAD will detect, download, decompress 
and install your application.

The case of the file names is important. Your self extracting archive,
your cabinet file and your dbx application must all have the same name as your 
application's logical appname. For this example, AsdkPolyOBJ is the logical 
appname. The cabinet file must be named AsdkPolyOBJ.cab, the self 
extracting archive AsdkPolyOBJ.exe and the dbx application AsdkPolyOBJ.dbx.

Your application must register itself when it is first loaded in order to
complete the process.

You will need to get the Cabinet SDK from Microsoft and install it
on your system.

You must create a .ddf file for your app's cabinet. See polyobj.ddf for a 
simple example. It is assumed that AsdkPolyOBJ.dbx has already been built.

Run MakeCAB on the .ddf file. For example: makecab /f polyobj.ddf.

Use copy to concatenate the extract utility and your cabinet file into a
self extracting archive. For example:
copy /b extract.exe+YOURAPP.cab YOURAPP.exe
(this assumes that extract.exe and YOURAPP.cab are in the current directory).

To test your ObjectEnabler, start AutoCAD and set the ObjectARX Search Path
(one way is to use the _options command). You will need to enter a valid URL.
Local file systems are supported using the FILE: syntax. For example, if
AsdkPolyOBJ.exe is copied to d:\test, enter the URL "FILE://d|/test".
Ensure that the registry is free of any entries made by your application.
Load a drawing that contains one of your custom objects. You should get a
dialog informing you that a custom object for which there is no registered
application has been detected. You will be asked if you want to search for
the missing application. Choose Yes. AutoCAD will search each of the URL paths
specified looking for the application. Remember, case is important. When AutoCAD
finds YOURAPP.exe, it will be downloaded to a temporary
directory for extraction (%TEMP%\ObjectARXdownLoad). The downloaded file is
executed by AutoCAD, extracting YOURAPP.dbx which is then placed in the 
/Program Files/Common Files/Autodesk Shared/ directory. The temporary download 
directory is then removed. YOURAPP.dbx is then loaded using the 
acrxDynamicLinker->LoadModule() method. The drawing should
load without turning your custom object into a proxy object. Your application
should also now be registered with the system, so upon loading the same drawing
a second time, you should not be prompted to search for the missing application.

That's all there is to it! Contact Autodesk to see about placing your
ObjectEnabler on our official ObjectEnabler web site.
