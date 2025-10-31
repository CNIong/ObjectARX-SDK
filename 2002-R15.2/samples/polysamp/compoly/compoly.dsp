# Microsoft Developer Studio Project File - Name="compoly" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=compoly - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "compoly.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "compoly.mak" CFG="compoly - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "compoly - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "compoly - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "compoly - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "compoly - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /Gm /GX /ZI /Od /I "..\..\..\inc" /I "..\\" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_NO_UUIDOF" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /I "..\..\..\inc" /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 rxapi.lib acge15.lib oleaprot.lib acrx15.lib axauto15.lib acdb15.lib asdkpolyobj.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:".\..\asdkcompoly.dbx" /pdbtype:sept /libpath:"..\..\..\lib" /libpath:"..\\"

!ELSEIF  "$(CFG)" == "compoly - Win32 Release MinSize"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMinSize"
# PROP BASE Intermediate_Dir "ReleaseMinSize"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMinSize"
# PROP Intermediate_Dir "ReleaseMinSize"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /Oy- /I "..\..\..\inc" /I "..\\" /D "NDEBUG" /D "_ATL_DLL" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_NO_UUIDOF" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /I "..\..\..\inc" /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 rxapi.lib acge15.lib oleaprot.lib acrx15.lib axauto15.lib acdb15.lib asdkpolyobj.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386 /out:".\..\asdkcompoly.dbx" /libpath:"..\..\..\lib" /libpath:"..\\"

!ELSEIF  "$(CFG)" == "compoly - Win32 Release MinDependency"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMinDependency"
# PROP BASE Intermediate_Dir "ReleaseMinDependency"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMinDependency"
# PROP Intermediate_Dir "ReleaseMinDependency"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /Oy- /I "..\..\..\inc" /I "..\\" /D "NDEBUG" /D "_ATL_STATIC_REGISTRY" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_NO_UUIDOF" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /I "..\..\..\inc" /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 rxapi.lib acge15.lib oleaprot.lib acrx15.lib axauto15.lib acdb15.lib asdkpolyobj.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386 /out:".\..\asdkcompoly.dbx" /libpath:"..\..\..\lib" /libpath:"..\\"

!ENDIF 

# Begin Target

# Name "compoly - Win32 Debug"
# Name "compoly - Win32 Release MinSize"
# Name "compoly - Win32 Release MinDependency"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\compoly.cpp
# End Source File
# Begin Source File

SOURCE=.\compoly.def
# End Source File
# Begin Source File

SOURCE=.\compoly.hpj

!IF  "$(CFG)" == "compoly - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Compiling Help
InputPath=.\compoly.hpj

"compoly.hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	hcw /c /e /m compoly.hpj

# End Custom Build

!ELSEIF  "$(CFG)" == "compoly - Win32 Release MinSize"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Compiling Help
InputPath=.\compoly.hpj

"compoly.hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	hcw /c /e /m compoly.hpj

# End Custom Build

!ELSEIF  "$(CFG)" == "compoly - Win32 Release MinDependency"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Compiling Help
InputPath=.\compoly.hpj

"compoly.hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	hcw /c /e /m compoly.hpj

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\compoly.idl

!IF  "$(CFG)" == "compoly - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing MIDL step
InputPath=.\compoly.idl

BuildCmds= \
	set path=%path%;..\..\..\inc \
	midl /Oicf  /tlb ".\compoly.tlb" /h ".\compoly.h" /iid   ".\compoly_i.c" ".\compoly.idl" \
	

".\compoly.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\compoly.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\compoly_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "compoly - Win32 Release MinSize"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing MIDL step
InputPath=.\compoly.idl

BuildCmds= \
	set path=%path%;..\..\..\inc \
	midl /Oicf  /tlb ".\compoly.tlb" /h ".\compoly.h" /iid   ".\compoly_i.c" ".\compoly.idl" \
	

".\compoly.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\compoly.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\compoly_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "compoly - Win32 Release MinDependency"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing MIDL step
InputPath=.\compoly.idl

BuildCmds= \
	set path=%path%;..\..\..\inc \
	midl /Oicf  /tlb ".\compoly.tlb" /h ".\compoly.h" /iid   ".\compoly_i.c" ".\compoly.idl" \
	

".\compoly.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\compoly.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\compoly_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\compoly.rc
# End Source File
# Begin Source File

SOURCE=.\ComPolygon.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\compoly.hm
# End Source File
# Begin Source File

SOURCE=.\ComPolygon.h
# End Source File
# Begin Source File

SOURCE=..\poly.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\compoly.RTF
# End Source File
# End Group
# Begin Source File

SOURCE=.\ComPolygon.rgs
# End Source File
# End Target
# End Project
