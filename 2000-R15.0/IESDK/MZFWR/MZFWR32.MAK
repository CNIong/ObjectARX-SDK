# Microsoft Developer Studio Generated NMAKE File, Based on mzfwr32.dsp
!IF "$(CFG)" == ""
CFG=mzfwr32 - Win32 Release
!MESSAGE No configuration specified. Defaulting to mzfwr32 - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "mzfwr32 - Win32 Release" && "$(CFG)" != "mzfwr32 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "mzfwr32.mak" CFG="mzfwr32 - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "mzfwr32 - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "mzfwr32 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "mzfwr32 - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\mzfwr32.dll"


CLEAN :
	-@erase "$(INTDIR)\mzfwr.obj"
	-@erase "$(INTDIR)\mzfwr.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\mzfwr32.dll"
	-@erase "$(OUTDIR)\mzfwr32.exp"
	-@erase "$(OUTDIR)\mzfwr32.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "..\..\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "CS_EXPORT" /D "_WINDLL" /D "_MBCS" /Fp"$(INTDIR)\mzfwr32.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\mzfwr.res" /i "..\..\inc" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\mzfwr32.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\mzfwr32.pdb" /machine:I386 /def:".\mzfwr32.def" /out:"$(OUTDIR)\mzfwr32.dll" /implib:"$(OUTDIR)\mzfwr32.lib" 
DEF_FILE= \
	".\mzfwr32.def"
LINK32_OBJS= \
	"$(INTDIR)\mzfwr.obj" \
	"$(INTDIR)\mzfwr.res"

"$(OUTDIR)\mzfwr32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "mzfwr32 - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\mzfwr32.dll"


CLEAN :
	-@erase "$(INTDIR)\mzfwr.obj"
	-@erase "$(INTDIR)\mzfwr.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\mzfwr32.dll"
	-@erase "$(OUTDIR)\mzfwr32.exp"
	-@erase "$(OUTDIR)\mzfwr32.ilk"
	-@erase "$(OUTDIR)\mzfwr32.lib"
	-@erase "$(OUTDIR)\mzfwr32.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\inc" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "CS_EXPORT" /D "_WINDLL" /D "_MBCS" /Fp"$(INTDIR)\mzfwr32.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\mzfwr.res" /i "..\..\inc" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o".\WinDebug\mzfwr.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\mzfwr32.pdb" /debug /machine:I386 /def:".\mzfwr32.def" /out:"$(OUTDIR)\mzfwr32.dll" /implib:"$(OUTDIR)\mzfwr32.lib" 
DEF_FILE= \
	".\mzfwr32.def"
LINK32_OBJS= \
	"$(INTDIR)\mzfwr.obj" \
	"$(INTDIR)\mzfwr.res"

"$(OUTDIR)\mzfwr32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

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


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("mzfwr32.dep")
!INCLUDE "mzfwr32.dep"
!ELSE 
!MESSAGE Warning: cannot find "mzfwr32.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "mzfwr32 - Win32 Release" || "$(CFG)" == "mzfwr32 - Win32 Debug"
SOURCE=.\mzfwr.cpp

"$(INTDIR)\mzfwr.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\mzfwr.rc

"$(INTDIR)\mzfwr.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

