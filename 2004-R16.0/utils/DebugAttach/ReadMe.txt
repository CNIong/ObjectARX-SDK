ObjectARX DebugAttach Addin
	
1.	The DebugAttach Addin for Visual Studio's VC++ .NET implements a work around for the known debugging issue with locked version of AutoCAD 2004. In locked version of AutoCAD 2004 developers cannot start AutoCAD in the VC++ .NET debugger. 

2.	The recommended work around for this issue is to invoke AutoCAD 2004 manually and then attach the VC++ .NET debugger to a running acad.exe process. This can be done by setting the Project->Debugging->Attach property to “Yes”. Invoke AutoCAD 2004, start the debugger in VC++ .NET and then attach to acad.exe by using the Processes dialog. The Processes dialog can be invoked using the menu Debug->Processes.

3.	The DebugAttach Addin is designed to automate the above process, so that debugging AutoCAD 2004 is no different from debugging any other VC++ project.

4.	The DebugAttach Addin will trap the VC++ .NET IDE’s debug start commands (and also with short cut commands F5,F10 or F11) and starts AutoCAD 2004 and sets the Project->Debugging->Attach property to “Yes”. This will enable Debugger to attach to the acad.exe automatically. When the debugging stops, the Attach property is set back to its original value.

5.	This Addin is inactive for all VC++ projects whose output file name does not have either of the extensions ".arx" or ".dbx".

6.	The developer can toggle the active status of the Addin by clicking on the command button on the toolbar. If inactive, the VC++ .NET IDE’s normal behavior is restored.
