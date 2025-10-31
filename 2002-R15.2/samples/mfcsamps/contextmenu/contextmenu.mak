# Microsoft Developer Studio Generated NMAKE File, Based on contextmenu.dsp
# Tweaked by ProjectWatcher Add-In ver 99.11.5.1
!IF "$(CFG)" == ""
CFG=contextmenu - Win32 Debug
!MESSAGE No configuration specified. Defaulting to contextmenu - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "contextmenu - Win32 Release" && "$(CFG)" != "contextmenu - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "contextmenu.mak" CFG="contextmenu - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "contextmenu - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "contextmenu - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "contextmenu - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\contextmenu.arx"


CLEAN :
	-@erase "$(INTDIR)\arxmfctmpl.obj"
	-@erase "$(INTDIR)\cmdarx.obj"
	-@erase "$(INTDIR)\contextmenu.pch"
	-@erase "$(INTDIR)\contextmenu.res"
	-@erase "$(INTDIR)\defaultarx.obj"
	-@erase "$(INTDIR)\editarx.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\contextmenu.arx"
	-@erase "$(OUTDIR)\contextmenu.exp"
	-@erase "$(OUTDIR)\contextmenu.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /Oy- /I "..\..\..\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_AFXEXT" /D "ACRXAPP" /D "RADPACK" /Fp"$(INTDIR)\contextmenu.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\contextmenu.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\contextmenu.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=acad.lib acdb15.lib acedapi.lib acrx15.lib acutil15.lib rxapi.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\contextmenu.pdb" /machine:I386 /def:".\contextmenu.def" /out:"$(OUTDIR)\contextmenu.arx" /implib:"$(OUTDIR)\contextmenu.lib" /libpath:"..\..\..\lib" 
DEF_FILE= \
	".\contextmenu.def"
LINK32_OBJS= \
	"$(INTDIR)\arxmfctmpl.obj" \
	"$(INTDIR)\cmdarx.obj" \
	"$(INTDIR)\defaultarx.obj" \
	"$(INTDIR)\editarx.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\contextmenu.res"

"$(OUTDIR)\contextmenu.arx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "contextmenu - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\contextmenu.arx" "$(OUTDIR)\contextmenu.bsc"


CLEAN :
	-@erase "$(INTDIR)\arxmfctmpl.obj"
	-@erase "$(INTDIR)\arxmfctmpl.sbr"
	-@erase "$(INTDIR)\cmdarx.obj"
	-@erase "$(INTDIR)\cmdarx.sbr"
	-@erase "$(INTDIR)\contextmenu.pch"
	-@erase "$(INTDIR)\contextmenu.res"
	-@erase "$(INTDIR)\defaultarx.obj"
	-@erase "$(INTDIR)\defaultarx.sbr"
	-@erase "$(INTDIR)\editarx.obj"
	-@erase "$(INTDIR)\editarx.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\contextmenu.arx"
	-@erase "$(OUTDIR)\contextmenu.bsc"
	-@erase "$(OUTDIR)\contextmenu.exp"
	-@erase "$(OUTDIR)\contextmenu.ilk"
	-@erase "$(OUTDIR)\contextmenu.lib"
	-@erase "$(OUTDIR)\contextmenu.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /Gm /GX /ZI /Od /I "..\..\..\inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_AFXEXT" /D "ACRXAPP" /D "RADPACK" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\contextmenu.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\contextmenu.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\contextmenu.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\arxmfctmpl.sbr" \
	"$(INTDIR)\cmdarx.sbr" \
	"$(INTDIR)\defaultarx.sbr" \
	"$(INTDIR)\editarx.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\contextmenu.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=acad.lib acdb15.lib acedapi.lib acrx15.lib acutil15.lib rxapi.lib /nologo /base:"0x1c000000" /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\contextmenu.pdb" /debug /machine:I386 /def:".\contextmenu.def" /out:"$(OUTDIR)\contextmenu.arx" /implib:"$(OUTDIR)\contextmenu.lib" /pdbtype:sept /libpath:"..\..\..\lib" 
DEF_FILE= \
	".\contextmenu.def"
LINK32_OBJS= \
	"$(INTDIR)\arxmfctmpl.obj" \
	"$(INTDIR)\cmdarx.obj" \
	"$(INTDIR)\defaultarx.obj" \
	"$(INTDIR)\editarx.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\contextmenu.res"

"$(OUTDIR)\contextmenu.arx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("contextmenu.dep")
!INCLUDE "contextmenu.dep"
!ELSE 
!MESSAGE Warning: cannot find "contextmenu.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "contextmenu - Win32 Release" || "$(CFG)" == "contextmenu - Win32 Debug"
SOURCE=.\arxmfctmpl.cpp

!IF  "$(CFG)" == "contextmenu - Win32 Release"


"$(INTDIR)\arxmfctmpl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\contextmenu.pch"


!ELSEIF  "$(CFG)" == "contextmenu - Win32 Debug"


"$(INTDIR)\arxmfctmpl.obj"	"$(INTDIR)\arxmfctmpl.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\contextmenu.pch"


!ENDIF 

SOURCE=.\cmdarx.cpp

!IF  "$(CFG)" == "contextmenu - Win32 Release"


"$(INTDIR)\cmdarx.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\contextmenu.pch"


!ELSEIF  "$(CFG)" == "contextmenu - Win32 Debug"


"$(INTDIR)\cmdarx.obj"	"$(INTDIR)\cmdarx.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\contextmenu.pch"


!ENDIF 

SOURCE=.\contextmenu.rc

"$(INTDIR)\contextmenu.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\defaultarx.cpp

!IF  "$(CFG)" == "contextmenu - Win32 Release"


"$(INTDIR)\defaultarx.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\contextmenu.pch"


!ELSEIF  "$(CFG)" == "contextmenu - Win32 Debug"


"$(INTDIR)\defaultarx.obj"	"$(INTDIR)\defaultarx.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\contextmenu.pch"


!ENDIF 

SOURCE=.\editarx.cpp

!IF  "$(CFG)" == "contextmenu - Win32 Release"


"$(INTDIR)\editarx.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\contextmenu.pch"


!ELSEIF  "$(CFG)" == "contextmenu - Win32 Debug"


"$(INTDIR)\editarx.obj"	"$(INTDIR)\editarx.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\contextmenu.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "contextmenu - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /Oy- /I "..\..\..\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_AFXEXT" /D "ACRXAPP" /D "RADPACK" /Fp"$(INTDIR)\contextmenu.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\contextmenu.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "contextmenu - Win32 Debug"

CPP_SWITCHES=/nologo /MD /W3 /Gm /GX /ZI /Od /I "..\..\..\inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_AFXEXT" /D "ACRXAPP" /D "RADPACK" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\contextmenu.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\contextmenu.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

