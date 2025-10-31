
Polysamp\demandload sample Readme.txt

 (C) Copyright 1998 - 2006 by Autodesk, Inc.

Demand Loading PolySamp

This readme demonstrates how to Demand Load an ObjectARX app
via Command Invocation, Proxy Detection, and AutoCAD Startup.

Execute these tasks in order first:

  1. Using a text editor, update polysamp.reg.

     [HKEY_LOCAL_MACHINE\SOFTWARE\Autodesk\AutoCAD\R17.1\ACAD-5001:409]

     Install ID now uses the country code. Change "ACAD-5001:409" in the registry
     if you're using this for a localized version.

     Change the path of polyui.arx to reflect your environment.

     ; Application registry section
     [HKEY_LOCAL_MACHINE\SOFTWARE\Autodesk\AutoCAD\R17.1\ACAD-5001:409\Applications\AsdkPolyCAD]
     "LOADER"="c:\\ObjectARX\\samples\\entity\\polysamp\\asdkpolyui.arx"

  2. Build polyui.arx and asdkpolyobj.dbx.

  3. Move or Copy asdkpolyobj.dbx to the Autodesk Shared directory
     (i.e. "C:\Program Files\Common Files\Autodesk Shared\")
     (see - \ObjectARX\samples\polysamp\readme.txt for additional locations).

I. Command Invocation

     [HKEY_LOCAL_MACHINE\SOFTWARE\Autodesk\AutoCAD\R17.1\ACAD-5001:409\Applications\AsdkPolyCAD\Commands]
     "ASDK_POLY"="POLY"

  1. Using File Manager or File Explorer, double click on polysamp.reg.
     (This will add/update your system's registry.)

  2. Start AutoCAD and set the system variable DEMANDLOAD to 3 (default).

  3. Invoking the command POLY defined in polyui.arx will Demand
     Load polyui.arx which then loads asdkpolyobj.dbx.

     Create a poly and save the drawing (poly.dwg) for Proxy Detection.

     Handling ambiguous commands (the same command name from multiple applications):
     Due to this possible situation, the registry key "Groups" provides a way to
     determine the application to demand load according to the command.

     [HKEY_LOCAL_MACHINE\SOFTWARE\Autodesk\AutoCAD\R17.1\ACAD-5001:409\Applications\AsdkPolyCAD\Groups]
     "ASDK_POLYGON"="ASDK_POLYGON"

     Invoking ASDK_POLYGON.POLY from the command line, invokes the desired command.

II. Proxy Detection

     [HKEY_LOCAL_MACHINE\SOFTWARE\Autodesk\AutoCAD\R17.1\ACAD-5001:409\Applications\AsdkPolyCAD]
     "LOADCTRLS"=dword:0000000d
     
  1. Assuming the Command Invocations above have been done, quit and start
     a new AutoCAD session.

  2. Check to make sure polyui.arx is not loaded.

  3. Open poly.dwg and polyui.arx will be Demand Loaded.


III. AutoCAD Startup:

  1. Update polysamp.reg with a text editor.

     Change: "LOADCTRLS"=dword:0000000d

         To: "LOADCTRLS"=dword:00000002

  2. Using File Manager or File Explorer, double click on polysamp.reg.
     This adds to or updates your system's registry.

  3. The next time AutoCAD is started, polyui.arx is Demand Loaded.



Refer to the ObjectARX Developer's Guide for more information on Demand Loading.

