
Demand Loading PolySamp/PolyCAD 2000

This readme will demonstrate how to Demand Load an ObjectARX app
via Command Invocation, Proxy Detection, and AutoCAD Startup.

DO THESE FIRST

  1. Using a text editor, update polysamp.reg

     [HKEY_LOCAL_MACHINE\SOFTWARE\Autodesk\AutoCAD\R15.0\ACAD-1:409]

     Install ID now uses the country code. Change "ACAD-1:409" in the registry
     if you're using this for a localized version.

     Change the path of polyui.arx to reflect your environment.

     ; Application file location
     [HKEY_LOCAL_MACHINE\SOFTWARE\Autodesk\ObjectARX\3.0\SampleApps\PolySamp\AsdkPolyCAD\Loader]
     "MODULE"="c:\\ObjectARX\\samples\\polysamp\\asdkpolyui.arx"

  2. Build asdkpolyui.arx and asdkpolyobj.dbx

  3. Move or Copy asdkpolyobj.dbx to Autodesk Shared directory
     (i.e. "C:\Program Files\Common Files\Autodesk Shared\")
     (see - \ObjectARX\samples\polysamp\readme.txt for additional locations)

I. Command Invocation

     [HKEY_LOCAL_MACHINE\SOFTWARE\Autodesk\ObjectARX\3.0\SampleApps\PolySamp\AsdkPolyCAD\Commands]
     "ASDK_POLY"="POLY"

  1. Using File Manager or File Explorer, double click on polysamp.reg.
     (This will add/update your system's registry)

  2. Start AutoCAD and set the system variable DEMANDLOAD to 3 (default).

  3. Invoking the command POLY defined in asdkpolyui.arx will Demand
     Load asdkpolyui.arx which then loads asdkpolyobj.dbx

     Create a poly and save the drawing (poly.dwg) for Proxy Detection.

     Handling ambiguous commands (the same command name from multiple apps)
     Due to this possible situation, registry key "Groups" is introduced as a 
     way to determine the desired app to demand load associated with a
     command.

     [HKEY_LOCAL_MACHINE\SOFTWARE\Autodesk\ObjectARX\3.0\SampleApps\PolySamp\AsdkPolyCAD\Groups]
     "ASDK_POLYGON"="ASDK_POLYGON"

     Invoking ASDK_POLYGON.POLY from command line, will invoke the desired command.

     Currently, ambiguous commands setup for demand loading will result 
     in unkown command, when group name is not used. A handler will be 
     provided in future release.

II. Proxy Detection

     [HKEY_LOCAL_MACHINE\SOFTWARE\Autodesk\AutoCAD\R15.0\ACAD-1:409\Applications\AsdkPolyCAD]
     "LOADCTRLS"=dword:0000000d
     
  1. Assuming Command Invocation above have been done, quit and start
     a new AutoCAD session.

  2. Check to make sure asdkpolyui.arx is not loaded.

  3. Open poly.dwg and asdkpolyui.arx will be Demand Loaded.


III. AutoCAD Startup

  1. Update polysamp.reg with a text editor.

     Change: "LOADCTRLS"=dword:0000000d

         To: "LOADCTRLS"=dword:00000002

  2. Using File Manager or File Explorer, double click on polysamp.reg.
     (This will add/update your system's registry)

  3. The next time AutoCAD is started, asdkpolyui.arx will always be
     Demand Loaded.



Refer to ObjectARX Developer's Guide for more info on Demand Loading.

For 3rd party developers, we recommend placing your application's registry 
under your company name. For example, replacing  
"\Autodesk\ObjectARX\3.0\SampleApps\PolySamp" with your company name.

InstallShield sample in ObjectARX CD provides another methods of setting 
up Demand Loading.

