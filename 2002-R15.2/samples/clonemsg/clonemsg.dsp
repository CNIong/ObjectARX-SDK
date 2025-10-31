# Microsoft Developer Studio Project File - Name="clonemsg" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=clonemsg - Win32 Direct
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "clonemsg.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "clonemsg.mak" CFG="clonemsg - Win32 Direct"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "clonemsg - Win32 Direct" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "clonemsg - Win32 ExtDict SoftPointer" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "clonemsg - Win32 ExtDict HardPointer" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "clonemsg - Win32 NOD SoftPointer" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "clonemsg - Win32 NOD HardPointer" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "clonemsg - Win32 Direct"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\WinDebug"
# PROP BASE Intermediate_Dir ".\WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Direct"
# PROP Intermediate_Dir ".\Direct"
# PROP Ignore_Export_Lib 0
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /Gm /GX /ZI /Od /I "..\..\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "ACRXAPP" /D "WIN" /D "DIRECT" /YX /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 rxapi.lib acutil15.lib acrx15.lib acad.lib acedapi.lib acge15.lib acdb15.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:".\Direct\clonemsg.arx" /libpath:"..\..\lib"
# SUBTRACT LINK32 /nodefaultlib /force

!ELSEIF  "$(CFG)" == "clonemsg - Win32 ExtDict SoftPointer"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Dictiona"
# PROP BASE Intermediate_Dir ".\Dictiona"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\ExtDSoft"
# PROP Intermediate_Dir ".\ExtDSoft"
# PROP Ignore_Export_Lib 0
# ADD BASE CPP /nologo /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "ACRXAPP" /D "WIN" /D "XLATE" /D "NOD" /FR /YX /c
# ADD CPP /nologo /MD /W3 /Gm /GX /ZI /Od /I "..\..\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "ACRXAPP" /D "WIN" /D "XLATE" /YX /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rxapi.lib acad.lib acedapi.lib libacge.lib /nologo /base:"0x1c000000" /subsystem:windows /dll /debug /machine:I386 /force /out:"WinDebug/clonemsg.arx"
# SUBTRACT BASE LINK32 /nodefaultlib
# ADD LINK32 rxapi.lib acutil15.lib acrx15.lib acad.lib acedapi.lib acge15.lib acdb15.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:".\ExtDSoft\clonemsg.arx" /libpath:"..\..\lib"
# SUBTRACT LINK32 /nodefaultlib /force

!ELSEIF  "$(CFG)" == "clonemsg - Win32 ExtDict HardPointer"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Extensio"
# PROP BASE Intermediate_Dir ".\Extensio"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\ExtDHard"
# PROP Intermediate_Dir ".\ExtDHard"
# PROP Ignore_Export_Lib 0
# ADD BASE CPP /nologo /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "ACRXAPP" /D "WIN" /D "XLATE" /D "NOD" /FR /YX /c
# ADD CPP /nologo /MD /W3 /Gm /GX /ZI /Od /I "..\..\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "ACRXAPP" /D "WIN" /D "XLATE" /D "HARDPOINTER" /YX /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rxapi.lib acad.lib acedapi.lib libacge.lib /nologo /base:"0x1c000000" /subsystem:windows /dll /debug /machine:I386 /force /out:"WinDebug/clonemsg.arx"
# SUBTRACT BASE LINK32 /nodefaultlib
# ADD LINK32 rxapi.lib acutil15.lib acrx15.lib acad.lib acedapi.lib acge15.lib acdb15.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:".\ExtDHard\clonemsg.arx" /libpath:"..\..\lib"
# SUBTRACT LINK32 /nodefaultlib /force

!ELSEIF  "$(CFG)" == "clonemsg - Win32 NOD SoftPointer"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Namedobj"
# PROP BASE Intermediate_Dir ".\Namedobj"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\NoDSoft"
# PROP Intermediate_Dir ".\NoDSoft"
# PROP Ignore_Export_Lib 0
# ADD BASE CPP /nologo /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "ACRXAPP" /D "WIN" /D "XLATE" /D "NOD" /FR /YX /c
# ADD CPP /nologo /MD /W3 /Gm /GX /ZI /Od /I "..\..\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "ACRXAPP" /D "WIN" /D "XLATE" /D "NOD" /YX /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rxapi.lib acad.lib acedapi.lib libacge.lib /nologo /base:"0x1c000000" /subsystem:windows /dll /debug /machine:I386 /force /out:"WinDebug/clonemsg.arx"
# SUBTRACT BASE LINK32 /nodefaultlib
# ADD LINK32 rxapi.lib acutil15.lib acrx15.lib acad.lib acedapi.lib acge15.lib acdb15.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:".\NoDSoft\clonemsg.arx" /libpath:"..\..\lib"
# SUBTRACT LINK32 /nodefaultlib /force

!ELSEIF  "$(CFG)" == "clonemsg - Win32 NOD HardPointer"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Namedob0"
# PROP BASE Intermediate_Dir ".\Namedob0"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\NoDHard"
# PROP Intermediate_Dir ".\NoDHard"
# PROP Ignore_Export_Lib 0
# ADD BASE CPP /nologo /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "ACRXAPP" /D "WIN" /D "XLATE" /D "NOD" /FR /YX /c
# ADD CPP /nologo /MD /W3 /Gm /GX /ZI /Od /I "..\..\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "ACRXAPP" /D "WIN" /D "XLATE" /D "NOD" /D "HARDPOINTER" /Fr /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rxapi.lib acad.lib acedapi.lib libacge.lib /nologo /base:"0x1c000000" /subsystem:windows /dll /debug /machine:I386 /force /out:"WinDebug/clonemsg.arx"
# SUBTRACT BASE LINK32 /nodefaultlib
# ADD LINK32 rxapi.lib acutil15.lib acrx15.lib acad.lib acedapi.lib acge15.lib acdb15.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:".\NoDHard\clonemsg.arx" /libpath:"..\..\lib"
# SUBTRACT LINK32 /nodefaultlib /force

!ENDIF 

# Begin Target

# Name "clonemsg - Win32 Direct"
# Name "clonemsg - Win32 ExtDict SoftPointer"
# Name "clonemsg - Win32 ExtDict HardPointer"
# Name "clonemsg - Win32 NOD SoftPointer"
# Name "clonemsg - Win32 NOD HardPointer"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\arxutils.cpp
# End Source File
# Begin Source File

SOURCE=.\clonemsg.def
# End Source File
# Begin Source File

SOURCE=.\edreact.cpp
# End Source File
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# Begin Source File

SOURCE=.\MkrEnti.cpp
# End Source File
# Begin Source File

SOURCE=.\MKROBJE.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\arxutils.h
# End Source File
# Begin Source File

SOURCE=.\edreact.h
# End Source File
# Begin Source File

SOURCE=.\main.h
# End Source File
# Begin Source File

SOURCE=.\MkrEnti.h
# End Source File
# Begin Source File

SOURCE=.\MKROBJE.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
