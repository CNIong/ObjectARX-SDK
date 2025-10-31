# Microsoft Developer Studio Generated NMAKE File, Based on mzfrd32.dsp
!IF "$(CFG)" == ""
CFG=mzfrd32 - Win32 Release
!MESSAGE No configuration specified. Defaulting to mzfrd32 - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "mzfrd32 - Win32 Release" && "$(CFG)" != "mzfrd32 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "mzfrd32.mak" CFG="mzfrd32 - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "mzfrd32 - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "mzfrd32 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "mzfrd32 - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\mzfrd32.dll"


CLEAN :
	-@erase "$(INTDIR)\mzfrd.obj"
	-@erase "$(INTDIR)\mzfrd.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\mzfrd32.dll"
	-@erase "$(OUTDIR)\mzfrd32.exp"
	-@erase "$(OUTDIR)\mzfrd32.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "..\..\inc" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "_MBCS" /D "CS_EXPORT" /Fp"$(INTDIR)\mzfrd32.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\mzfrd.res" /i "..\..\inc" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\mzfrd32.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\mzfrd32.pdb" /machine:I386 /def:".\mzfrd32.def" /out:"$(OUTDIR)\mzfrd32.dll" /implib:"$(OUTDIR)\mzfrd32.lib" 
DEF_FILE= \
	".\mzfrd32.def"
LINK32_OBJS= \
	"$(INTDIR)\mzfrd.obj" \
	"$(INTDIR)\mzfrd.res"

"$(OUTDIR)\mzfrd32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "mzfrd32 - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\mzfrd32.dll"


CLEAN :
	-@erase "$(INTDIR)\mzfrd.obj"
	-@erase "$(INTDIR)\mzfrd.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\mzfrd32.dll"
	-@erase "$(OUTDIR)\mzfrd32.exp"
	-@erase "$(OUTDIR)\mzfrd32.ilk"
	-@erase "$(OUTDIR)\mzfrd32.lib"
	-@erase "$(OUTDIR)\mzfrd32.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "_MBCS" /D "CS_EXPORT" /Fp"$(INTDIR)\mzfrd32.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\mzfrd.res" /i "..\..\inc" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\mzfrd32.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\mzfrd32.pdb" /debug /machine:I386 /def:".\mzfrd32.def" /out:"$(OUTDIR)\mzfrd32.dll" /implib:"$(OUTDIR)\mzfrd32.lib" 
DEF_FILE= \
	".\mzfrd32.def"
LINK32_OBJS= \
	"$(INTDIR)\mzfrd.obj" \
	"$(INTDIR)\mzfrd.res"

"$(OUTDIR)\mzfrd32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("mzfrd32.dep")
!INCLUDE "mzfrd32.dep"
!ELSE 
!MESSAGE Warning: cannot find "mzfrd32.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "mzfrd32 - Win32 Release" || "$(CFG)" == "mzfrd32 - Win32 Debug"
SOURCE=.\mzfrd.cpp

"$(INTDIR)\mzfrd.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\mzfrd.rc

"$(INTDIR)\mzfrd.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

