# Microsoft Developer Studio Project File - Name="ism" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=ism - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "IsmExample.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "IsmExample.mak" CFG="ism - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ism - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ism - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ism - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ism___Wi"
# PROP BASE Intermediate_Dir "ism___Wi"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "ACRXAPP" /D "_USRDLL" /D "CS_USEDLL" /D "CS_APP" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FR /FD /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MD /W3 /GX /Zi /O2 /Oy- /I "..\..\inc" /D "WIN32" /D "_WINDOWS" /D "ACRXAPP" /D "_USRDLL" /D "CS_USEDLL" /D "CS_APP" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo /o".\Debug\ismtest.bsc"
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\..\lib\acISMobj15.lib /nologo /base:"0x1c000000" /subsystem:windows /dll /debug /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"msvcrt.lib" /out:".\IsmExample.arx"
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 ..\..\lib\rxapi.lib ..\..\lib\acISMobj15.lib ..\..\lib\acrx15.lib ..\..\lib\acutil15.lib ..\..\lib\acad.lib ..\..\lib\acdb15.lib ..\..\lib\acge15.lib ..\..\lib\acedapi.lib /nologo /base:"0x1c000000" /subsystem:windows /dll /pdb:none /map /machine:I386 /nodefaultlib:"msvcrtd.lib" /out:"./release/IsmExample.arx"

!ELSEIF  "$(CFG)" == "ism - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /Zi /I "..\..\inc" /D "WIN32" /D "_WINDOWS" /D "ACRXAPP" /D "_USRDLL" /D "CS_USEDLL" /D "CS_APP" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FD /c
# SUBTRACT BASE CPP /Fr /YX
# ADD CPP /nologo /MD /W3 /GX /Zi /Od /I "..\..\inc" /D "WIN32" /D "_WINDOWS" /D "ACRXAPP" /D "_USRDLL" /D "CS_USEDLL" /D "CS_APP" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FR /FD /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /mktyplib203 /win32
# ADD MTL /nologo /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\..\lib\rxapi.lib ..\..\lib\acISMobj15.lib ..\..\lib\acrx15.lib ..\..\lib\acutil15.lib ..\..\lib\acad.lib ..\..\lib\acdb15.lib ..\..\lib\acge15.lib ..\..\lib\acedapi.lib /nologo /base:"0x1c000000" /subsystem:windows /dll /pdb:none /map /machine:I386 /nodefaultlib:"msvcrtd.lib" /out:".\IsmExample.arx"
# ADD LINK32 ..\..\lib\rxapi.lib ..\..\lib\acISMobj15.lib ..\..\lib\acrx15.lib ..\..\lib\acutil15.lib ..\..\lib\acad.lib ..\..\lib\acdb15.lib ..\..\lib\acge15.lib ..\..\lib\acedapi.lib /nologo /base:"0x1c000000" /subsystem:windows /dll /incremental:no /map /debug /machine:I386 /nodefaultlib:"msvcrtd.lib" /out:"./Debug/IsmExample.arx"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "ism - Win32 Release"
# Name "ism - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\access.cpp
# End Source File
# Begin Source File

SOURCE=.\CustomApplication.cpp
# End Source File
# Begin Source File

SOURCE=.\CustomApplication.def
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\access.h
# End Source File
# Begin Source File

SOURCE=.\CustomApplication.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
