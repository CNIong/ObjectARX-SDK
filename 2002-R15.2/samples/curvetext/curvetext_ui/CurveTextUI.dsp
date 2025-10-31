# Microsoft Developer Studio Project File - Name="CurveTextUI" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=CurveTextUI - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CurveTextUI.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CurveTextUI.mak" CFG="CurveTextUI - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CurveTextUI - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CurveTextUI - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CurveTextUI - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /Oy- /I "..\..\..\inc" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "ACRXAPP" /D "RADPACK" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 curveText.lib rxapi.lib acad.lib acedapi.lib acgiapi.lib acrx15.lib acdb15.lib acge15.lib acutil15.lib adui15.lib acui15.lib /nologo /subsystem:windows /dll /machine:I386 /out:"..\Curvetext.arx" /libpath:"..\..\..\lib" /libpath:"..\CurveText_DB\Release"

!ELSEIF  "$(CFG)" == "CurveTextUI - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "CurveTex"
# PROP BASE Intermediate_Dir "CurveTex"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /Gm /GX /ZI /Od /I "..\..\..\inc" /D "_DEBUG" /D "ACRXAPP" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 curveText.lib rxapi.lib acad.lib acrx15.lib acdb15.lib acge15.lib acedapi.lib acgiapi.lib acutil15.lib adui15.lib acui15.lib /nologo /subsystem:windows /dll /debug /machine:I386 /nodefaultlib:"mfco42d.lib" /out:"..\Curvetext.arx" /pdbtype:sept /libpath:"..\..\..\lib" /libpath:"..\CurveText_DB\Debug"

!ENDIF 

# Begin Target

# Name "CurveTextUI - Win32 Release"
# Name "CurveTextUI - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\ContextMenu.cpp
# ADD CPP /Yu
# End Source File
# Begin Source File

SOURCE=.\curveText.def
# End Source File
# Begin Source File

SOURCE=.\CurveTextDialog.cpp
# ADD CPP /Yu
# End Source File
# Begin Source File

SOURCE=.\CurvetextHelper.cpp
# ADD CPP /Yu
# End Source File
# Begin Source File

SOURCE=.\CurveTextJig.cpp
# ADD CPP /Yu
# End Source File
# Begin Source File

SOURCE=.\InputPointMonitor.cpp
# ADD CPP /Yu
# End Source File
# Begin Source File

SOURCE=.\MAIN.CPP
# ADD CPP /Yu
# End Source File
# Begin Source File

SOURCE=.\resourceHelper.cpp
# ADD CPP /Yu
# End Source File
# Begin Source File

SOURCE=.\STDAFX.CPP
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Utils.cpp
# ADD CPP /Yu
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\ContextMenu.h
# End Source File
# Begin Source File

SOURCE=.\CurveTextDialog.h
# End Source File
# Begin Source File

SOURCE=.\CurveTextHelper.h
# End Source File
# Begin Source File

SOURCE=.\CurveTextJig.h
# End Source File
# Begin Source File

SOURCE=.\InputPointMonitor.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\resourcehelper.h
# End Source File
# Begin Source File

SOURCE=.\STDAFX.H
# End Source File
# Begin Source File

SOURCE=.\Utils.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "*.rc"
# Begin Source File

SOURCE=.\curveText.rc
# End Source File
# End Group
# End Target
# End Project
