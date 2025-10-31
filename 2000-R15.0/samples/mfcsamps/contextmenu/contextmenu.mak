# Microsoft Developer Studio Generated NMAKE File, Based on contextmenu.dsp
!IF "$(CFG)" == ""
CFG=contextmenu - Win32 Debug
!MESSAGE No configuration specified. Defaulting to contextmenu - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "contextmenu - Win32 Release" && "$(CFG)" !=\
 "contextmenu - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "contextmenu.mak" CFG="contextmenu - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "contextmenu - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "contextmenu - Win32 Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
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

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\contextmenu.arx"

!ELSE 

ALL : "$(OUTDIR)\contextmenu.arx"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\arxmfctmpl.obj"
	-@erase "$(INTDIR)\cmdarx.obj"
	-@erase "$(INTDIR)\contextmenu.pch"
	-@erase "$(INTDIR)\contextmenu.res"
	-@erase "$(INTDIR)\defaultarx.obj"
	-@erase "$(INTDIR)\editarx.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\contextmenu.arx"
	-@erase "$(OUTDIR)\contextmenu.exp"
	-@erase "$(OUTDIR)\contextmenu.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\..\..\..\coreacad\include" /I\
 "..\..\..\..\coreacad\rx\api" /I "..\..\..\..\coreacad\ads" /I\
 "..\..\..\..\coreacad\db\api\inc" /I "..\..\..\..\coreacad\gelib\api\inc" /D\
 "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D\
 "ACRXAPP" /D "RADPACK" /Fp"$(INTDIR)\contextmenu.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\contextmenu.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\contextmenu.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=$(LIB_ACDB) $(LIB_ACAD) $(LIB_ACED) $(LIB_ACRX) /nologo\
 /base:"0x1c000000" /subsystem:windows /dll\
 /incremental:no /pdb:"$(OUTDIR)\contextmenu.pdb" /machine:I386\
 /nodefaultlib:"MSVCRTD.LIB" /def:".\contextmenu.def"\
 /out:"$(OUTDIR)\contextmenu.arx" /implib:"$(OUTDIR)\contextmenu.lib" 
DEF_FILE= \
	".\contextmenu.def"
LINK32_OBJS= \
	"$(INTDIR)\arxmfctmpl.obj" \
	"$(INTDIR)\cmdarx.obj" \
	"$(INTDIR)\contextmenu.res" \
	"$(INTDIR)\defaultarx.obj" \
	"$(INTDIR)\editarx.obj" \
	"$(INTDIR)\StdAfx.obj"

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

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\contextmenu.arx"

!ELSE 

ALL : "$(OUTDIR)\contextmenu.arx"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\arxmfctmpl.obj"
	-@erase "$(INTDIR)\cmdarx.obj"
	-@erase "$(INTDIR)\contextmenu.pch"
	-@erase "$(INTDIR)\contextmenu.res"
	-@erase "$(INTDIR)\defaultarx.obj"
	-@erase "$(INTDIR)\editarx.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\contextmenu.arx"
	-@erase "$(OUTDIR)\contextmenu.exp"
	-@erase "$(OUTDIR)\contextmenu.ilk"
	-@erase "$(OUTDIR)\contextmenu.lib"
	-@erase "$(OUTDIR)\contextmenu.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\..\..\..\coreacad\include" /I\
 "..\..\..\..\coreacad\rx\api" /I "..\..\..\..\coreacad\ads" /I\
 "..\..\..\..\coreacad\db\api\inc" /I "..\..\..\..\coreacad\gelib\api\inc" /D\
 "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D\
 "ACRXAPP" /D "RADPACK" /D "DEBUG_AUTOCAD" /Fp"$(INTDIR)\contextmenu.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\contextmenu.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\contextmenu.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=$(LIB_ACDB) $(LIB_ACAD) $(LIB_ACED) $(LIB_ACRX) /nologo\
 /base:"0x1c000000" /subsystem:windows /dll\
 /incremental:yes /pdb:"$(OUTDIR)\contextmenu.pdb" /debug /machine:I386\
 /nodefaultlib:"MSVCRT.LIB" /def:".\contextmenu.def"\
 /out:"$(OUTDIR)\contextmenu.arx" /implib:"$(OUTDIR)\contextmenu.lib"\
 /pdbtype:sept 
DEF_FILE= \
	".\contextmenu.def"
LINK32_OBJS= \
	"$(INTDIR)\arxmfctmpl.obj" \
	"$(INTDIR)\cmdarx.obj" \
	"$(INTDIR)\contextmenu.res" \
	"$(INTDIR)\defaultarx.obj" \
	"$(INTDIR)\editarx.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\contextmenu.arx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "contextmenu - Win32 Release" || "$(CFG)" ==\
 "contextmenu - Win32 Debug"
SOURCE=.\arxmfctmpl.cpp

!IF  "$(CFG)" == "contextmenu - Win32 Release"

DEP_CPP_ARXMF=\
	"..\..\..\..\coreacad\ads\ads.h"\
	"..\..\..\..\coreacad\ads\adsdef.h"\
	"..\..\..\..\coreacad\db\api\inc\acdb.h"\
	"..\..\..\..\coreacad\db\api\inc\dbaudita.h"\
	"..\..\..\..\coreacad\db\api\inc\dbboiler.h"\
	"..\..\..\..\coreacad\db\api\inc\dbcurve.h"\
	"..\..\..\..\coreacad\db\api\inc\dbdim.h"\
	"..\..\..\..\coreacad\db\api\inc\dbents.h"\
	"..\..\..\..\coreacad\db\api\inc\dbfiler.h"\
	"..\..\..\..\coreacad\db\api\inc\dbhandle.h"\
	"..\..\..\..\coreacad\db\api\inc\dbid.h"\
	"..\..\..\..\coreacad\db\api\inc\dbid_ops.h"\
	"..\..\..\..\coreacad\db\api\inc\dbidapps.h"\
	"..\..\..\..\coreacad\db\api\inc\dbidar.h"\
	"..\..\..\..\coreacad\db\api\inc\dbintar.h"\
	"..\..\..\..\coreacad\db\api\inc\dbmain.h"\
	"..\..\..\..\coreacad\db\api\inc\dbmtext.h"\
	"..\..\..\..\coreacad\db\api\inc\dbptrar.h"\
	"..\..\..\..\coreacad\db\api\inc\dbsubeid.h"\
	"..\..\..\..\coreacad\gelib\api\inc\acarray.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gecurv3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gedblar.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gedll.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geent2d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geent3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gegbl.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gegblabb.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gegblge.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gegblnew.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geintarr.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geintrvl.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gelent3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gelibver.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geline3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gepent3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geplanar.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geplane.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gepnt2d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gepnt3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geponc3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gept2dar.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gept3dar.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gescl3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gesurf.h"\
	"..\..\..\..\coreacad\gelib\api\inc\getol.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gevc3dar.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gevec2d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gevec3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gevptar.h"\
	"..\..\..\..\coreacad\include\acadstrc.h"\
	"..\..\..\..\coreacad\include\accmd.h"\
	"..\..\..\..\coreacad\include\aced.h"\
	"..\..\..\..\coreacad\include\adesk.h"\
	"..\..\..\..\coreacad\include\dbcolor.h"\
	"..\..\..\..\coreacad\include\dbjig.h"\
	"..\..\..\..\coreacad\include\drawable.h"\
	"..\..\..\..\coreacad\include\rxdefs.h"\
	"..\..\..\..\coreacad\include\rxnames.h"\
	"..\..\..\..\coreacad\include\rxsys.h"\
	"..\..\..\..\coreacad\rx\api\rxboiler.h"\
	"..\..\..\..\coreacad\rx\api\rxclass.h"\
	"..\..\..\..\coreacad\rx\api\rxdict.h"\
	"..\..\..\..\coreacad\rx\api\rxditer.h"\
	"..\..\..\..\coreacad\rx\api\rxdlinkr.h"\
	"..\..\..\..\coreacad\rx\api\rxevent.h"\
	"..\..\..\..\coreacad\rx\api\rxiter.h"\
	"..\..\..\..\coreacad\rx\api\rxobject.h"\
	"..\..\..\..\coreacad\rx\api\rxsrvice.h"\
	".\cmdarx.h"\
	".\defaultarx.h"\
	".\editarx.h"\
	".\resourcehelper.h"\
	

"$(INTDIR)\arxmfctmpl.obj" : $(SOURCE) $(DEP_CPP_ARXMF) "$(INTDIR)"\
 "$(INTDIR)\contextmenu.pch"


!ELSEIF  "$(CFG)" == "contextmenu - Win32 Debug"

DEP_CPP_ARXMF=\
	"..\..\..\..\coreacad\ads\ads.h"\
	"..\..\..\..\coreacad\ads\adsdef.h"\
	"..\..\..\..\coreacad\db\api\inc\acdb.h"\
	"..\..\..\..\coreacad\db\api\inc\dbaudita.h"\
	"..\..\..\..\coreacad\db\api\inc\dbboiler.h"\
	"..\..\..\..\coreacad\db\api\inc\dbcurve.h"\
	"..\..\..\..\coreacad\db\api\inc\dbdim.h"\
	"..\..\..\..\coreacad\db\api\inc\dbents.h"\
	"..\..\..\..\coreacad\db\api\inc\dbfiler.h"\
	"..\..\..\..\coreacad\db\api\inc\dbhandle.h"\
	"..\..\..\..\coreacad\db\api\inc\dbid.h"\
	"..\..\..\..\coreacad\db\api\inc\dbid_ops.h"\
	"..\..\..\..\coreacad\db\api\inc\dbidapps.h"\
	"..\..\..\..\coreacad\db\api\inc\dbidar.h"\
	"..\..\..\..\coreacad\db\api\inc\dbintar.h"\
	"..\..\..\..\coreacad\db\api\inc\dbmain.h"\
	"..\..\..\..\coreacad\db\api\inc\dbmtext.h"\
	"..\..\..\..\coreacad\db\api\inc\dbptrar.h"\
	"..\..\..\..\coreacad\db\api\inc\dbsubeid.h"\
	"..\..\..\..\coreacad\gelib\api\inc\acarray.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gecurv3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gedblar.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gedll.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geent2d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geent3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gegbl.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gegblabb.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gegblge.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gegblnew.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geintarr.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geintrvl.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gelent3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gelibver.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geline3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gepent3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geplanar.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geplane.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gepnt2d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gepnt3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geponc3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gept2dar.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gept3dar.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gescl3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gesurf.h"\
	"..\..\..\..\coreacad\gelib\api\inc\getol.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gevc3dar.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gevec2d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gevec3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gevptar.h"\
	"..\..\..\..\coreacad\include\acadstrc.h"\
	"..\..\..\..\coreacad\include\accmd.h"\
	"..\..\..\..\coreacad\include\aced.h"\
	"..\..\..\..\coreacad\include\adesk.h"\
	"..\..\..\..\coreacad\include\dbcolor.h"\
	"..\..\..\..\coreacad\include\dbjig.h"\
	"..\..\..\..\coreacad\include\drawable.h"\
	"..\..\..\..\coreacad\include\rxdefs.h"\
	"..\..\..\..\coreacad\include\rxnames.h"\
	"..\..\..\..\coreacad\include\rxsys.h"\
	"..\..\..\..\coreacad\rx\api\rxboiler.h"\
	"..\..\..\..\coreacad\rx\api\rxclass.h"\
	"..\..\..\..\coreacad\rx\api\rxdict.h"\
	"..\..\..\..\coreacad\rx\api\rxditer.h"\
	"..\..\..\..\coreacad\rx\api\rxdlinkr.h"\
	"..\..\..\..\coreacad\rx\api\rxevent.h"\
	"..\..\..\..\coreacad\rx\api\rxiter.h"\
	"..\..\..\..\coreacad\rx\api\rxobject.h"\
	"..\..\..\..\coreacad\rx\api\rxsrvice.h"\
	".\cmdarx.h"\
	".\defaultarx.h"\
	".\editarx.h"\
	".\resourcehelper.h"\
	

"$(INTDIR)\arxmfctmpl.obj" : $(SOURCE) $(DEP_CPP_ARXMF) "$(INTDIR)"\
 "$(INTDIR)\contextmenu.pch"


!ENDIF 

SOURCE=.\cmdarx.cpp

!IF  "$(CFG)" == "contextmenu - Win32 Release"

DEP_CPP_CMDAR=\
	"..\..\..\..\coreacad\ads\ads.h"\
	"..\..\..\..\coreacad\ads\adsdef.h"\
	"..\..\..\..\coreacad\db\api\inc\acdb.h"\
	"..\..\..\..\coreacad\db\api\inc\dbaudita.h"\
	"..\..\..\..\coreacad\db\api\inc\dbboiler.h"\
	"..\..\..\..\coreacad\db\api\inc\dbfiler.h"\
	"..\..\..\..\coreacad\db\api\inc\dbhandle.h"\
	"..\..\..\..\coreacad\db\api\inc\dbid.h"\
	"..\..\..\..\coreacad\db\api\inc\dbid_ops.h"\
	"..\..\..\..\coreacad\db\api\inc\dbidapps.h"\
	"..\..\..\..\coreacad\db\api\inc\dbidar.h"\
	"..\..\..\..\coreacad\db\api\inc\dbintar.h"\
	"..\..\..\..\coreacad\db\api\inc\dbmain.h"\
	"..\..\..\..\coreacad\db\api\inc\dbptrar.h"\
	"..\..\..\..\coreacad\db\api\inc\dbsubeid.h"\
	"..\..\..\..\coreacad\gelib\api\inc\acarray.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gecurv3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gedblar.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gedll.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geent2d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geent3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gegbl.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gegblabb.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gegblge.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gegblnew.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geintarr.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geintrvl.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gelent3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gelibver.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geline3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gepent3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gepnt2d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gepnt3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geponc3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gept3dar.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gescl3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\getol.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gevc3dar.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gevec2d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gevec3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gevptar.h"\
	"..\..\..\..\coreacad\include\acadstrc.h"\
	"..\..\..\..\coreacad\include\accmd.h"\
	"..\..\..\..\coreacad\include\aced.h"\
	"..\..\..\..\coreacad\include\adesk.h"\
	"..\..\..\..\coreacad\include\dbcolor.h"\
	"..\..\..\..\coreacad\include\dbjig.h"\
	"..\..\..\..\coreacad\include\drawable.h"\
	"..\..\..\..\coreacad\include\rxdefs.h"\
	"..\..\..\..\coreacad\include\rxnames.h"\
	"..\..\..\..\coreacad\include\rxsys.h"\
	"..\..\..\..\coreacad\rx\api\rxboiler.h"\
	"..\..\..\..\coreacad\rx\api\rxclass.h"\
	"..\..\..\..\coreacad\rx\api\rxdict.h"\
	"..\..\..\..\coreacad\rx\api\rxditer.h"\
	"..\..\..\..\coreacad\rx\api\rxdlinkr.h"\
	"..\..\..\..\coreacad\rx\api\rxevent.h"\
	"..\..\..\..\coreacad\rx\api\rxiter.h"\
	"..\..\..\..\coreacad\rx\api\rxobject.h"\
	"..\..\..\..\coreacad\rx\api\rxsrvice.h"\
	".\cmdarx.h"\
	".\resourcehelper.h"\
	

"$(INTDIR)\cmdarx.obj" : $(SOURCE) $(DEP_CPP_CMDAR) "$(INTDIR)"\
 "$(INTDIR)\contextmenu.pch"


!ELSEIF  "$(CFG)" == "contextmenu - Win32 Debug"

DEP_CPP_CMDAR=\
	"..\..\..\..\coreacad\ads\ads.h"\
	"..\..\..\..\coreacad\ads\adsdef.h"\
	"..\..\..\..\coreacad\db\api\inc\acdb.h"\
	"..\..\..\..\coreacad\db\api\inc\dbaudita.h"\
	"..\..\..\..\coreacad\db\api\inc\dbboiler.h"\
	"..\..\..\..\coreacad\db\api\inc\dbfiler.h"\
	"..\..\..\..\coreacad\db\api\inc\dbhandle.h"\
	"..\..\..\..\coreacad\db\api\inc\dbid.h"\
	"..\..\..\..\coreacad\db\api\inc\dbid_ops.h"\
	"..\..\..\..\coreacad\db\api\inc\dbidapps.h"\
	"..\..\..\..\coreacad\db\api\inc\dbidar.h"\
	"..\..\..\..\coreacad\db\api\inc\dbintar.h"\
	"..\..\..\..\coreacad\db\api\inc\dbmain.h"\
	"..\..\..\..\coreacad\db\api\inc\dbptrar.h"\
	"..\..\..\..\coreacad\db\api\inc\dbsubeid.h"\
	"..\..\..\..\coreacad\gelib\api\inc\acarray.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gecurv3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gedblar.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gedll.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geent2d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geent3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gegbl.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gegblabb.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gegblge.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gegblnew.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geintarr.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geintrvl.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gelent3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gelibver.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geline3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gepent3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gepnt2d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gepnt3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geponc3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gept3dar.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gescl3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\getol.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gevc3dar.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gevec2d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gevec3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gevptar.h"\
	"..\..\..\..\coreacad\include\acadstrc.h"\
	"..\..\..\..\coreacad\include\accmd.h"\
	"..\..\..\..\coreacad\include\aced.h"\
	"..\..\..\..\coreacad\include\adesk.h"\
	"..\..\..\..\coreacad\include\dbcolor.h"\
	"..\..\..\..\coreacad\include\dbjig.h"\
	"..\..\..\..\coreacad\include\drawable.h"\
	"..\..\..\..\coreacad\include\rxdefs.h"\
	"..\..\..\..\coreacad\include\rxnames.h"\
	"..\..\..\..\coreacad\include\rxsys.h"\
	"..\..\..\..\coreacad\rx\api\rxboiler.h"\
	"..\..\..\..\coreacad\rx\api\rxclass.h"\
	"..\..\..\..\coreacad\rx\api\rxdict.h"\
	"..\..\..\..\coreacad\rx\api\rxditer.h"\
	"..\..\..\..\coreacad\rx\api\rxdlinkr.h"\
	"..\..\..\..\coreacad\rx\api\rxevent.h"\
	"..\..\..\..\coreacad\rx\api\rxiter.h"\
	"..\..\..\..\coreacad\rx\api\rxobject.h"\
	"..\..\..\..\coreacad\rx\api\rxsrvice.h"\
	".\cmdarx.h"\
	".\resourcehelper.h"\
	

"$(INTDIR)\cmdarx.obj" : $(SOURCE) $(DEP_CPP_CMDAR) "$(INTDIR)"\
 "$(INTDIR)\contextmenu.pch"


!ENDIF 

SOURCE=.\contextmenu.rc
DEP_RSC_CONTE=\
	".\res\contextmenu.rc2"\
	

"$(INTDIR)\contextmenu.res" : $(SOURCE) $(DEP_RSC_CONTE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\defaultarx.cpp

!IF  "$(CFG)" == "contextmenu - Win32 Release"

DEP_CPP_DEFAU=\
	"..\..\..\..\coreacad\ads\ads.h"\
	"..\..\..\..\coreacad\ads\adsdef.h"\
	"..\..\..\..\coreacad\db\api\inc\acdb.h"\
	"..\..\..\..\coreacad\db\api\inc\dbaudita.h"\
	"..\..\..\..\coreacad\db\api\inc\dbboiler.h"\
	"..\..\..\..\coreacad\db\api\inc\dbfiler.h"\
	"..\..\..\..\coreacad\db\api\inc\dbhandle.h"\
	"..\..\..\..\coreacad\db\api\inc\dbid.h"\
	"..\..\..\..\coreacad\db\api\inc\dbid_ops.h"\
	"..\..\..\..\coreacad\db\api\inc\dbidapps.h"\
	"..\..\..\..\coreacad\db\api\inc\dbidar.h"\
	"..\..\..\..\coreacad\db\api\inc\dbintar.h"\
	"..\..\..\..\coreacad\db\api\inc\dbmain.h"\
	"..\..\..\..\coreacad\db\api\inc\dbptrar.h"\
	"..\..\..\..\coreacad\db\api\inc\dbsubeid.h"\
	"..\..\..\..\coreacad\gelib\api\inc\acarray.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gecurv3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gedblar.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gedll.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geent2d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geent3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gegbl.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gegblabb.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gegblge.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gegblnew.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geintarr.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geintrvl.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gelent3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gelibver.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geline3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gepent3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gepnt2d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gepnt3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geponc3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gept3dar.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gescl3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\getol.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gevc3dar.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gevec2d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gevec3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gevptar.h"\
	"..\..\..\..\coreacad\include\acadstrc.h"\
	"..\..\..\..\coreacad\include\accmd.h"\
	"..\..\..\..\coreacad\include\aced.h"\
	"..\..\..\..\coreacad\include\adesk.h"\
	"..\..\..\..\coreacad\include\dbcolor.h"\
	"..\..\..\..\coreacad\include\dbjig.h"\
	"..\..\..\..\coreacad\include\drawable.h"\
	"..\..\..\..\coreacad\include\rxdefs.h"\
	"..\..\..\..\coreacad\include\rxnames.h"\
	"..\..\..\..\coreacad\include\rxsys.h"\
	"..\..\..\..\coreacad\rx\api\rxboiler.h"\
	"..\..\..\..\coreacad\rx\api\rxclass.h"\
	"..\..\..\..\coreacad\rx\api\rxdict.h"\
	"..\..\..\..\coreacad\rx\api\rxditer.h"\
	"..\..\..\..\coreacad\rx\api\rxdlinkr.h"\
	"..\..\..\..\coreacad\rx\api\rxevent.h"\
	"..\..\..\..\coreacad\rx\api\rxiter.h"\
	"..\..\..\..\coreacad\rx\api\rxobject.h"\
	"..\..\..\..\coreacad\rx\api\rxsrvice.h"\
	".\defaultarx.h"\
	".\resourcehelper.h"\
	

"$(INTDIR)\defaultarx.obj" : $(SOURCE) $(DEP_CPP_DEFAU) "$(INTDIR)"\
 "$(INTDIR)\contextmenu.pch"


!ELSEIF  "$(CFG)" == "contextmenu - Win32 Debug"

DEP_CPP_DEFAU=\
	"..\..\..\..\coreacad\ads\ads.h"\
	"..\..\..\..\coreacad\ads\adsdef.h"\
	"..\..\..\..\coreacad\db\api\inc\acdb.h"\
	"..\..\..\..\coreacad\db\api\inc\dbaudita.h"\
	"..\..\..\..\coreacad\db\api\inc\dbboiler.h"\
	"..\..\..\..\coreacad\db\api\inc\dbfiler.h"\
	"..\..\..\..\coreacad\db\api\inc\dbhandle.h"\
	"..\..\..\..\coreacad\db\api\inc\dbid.h"\
	"..\..\..\..\coreacad\db\api\inc\dbid_ops.h"\
	"..\..\..\..\coreacad\db\api\inc\dbidapps.h"\
	"..\..\..\..\coreacad\db\api\inc\dbidar.h"\
	"..\..\..\..\coreacad\db\api\inc\dbintar.h"\
	"..\..\..\..\coreacad\db\api\inc\dbmain.h"\
	"..\..\..\..\coreacad\db\api\inc\dbptrar.h"\
	"..\..\..\..\coreacad\db\api\inc\dbsubeid.h"\
	"..\..\..\..\coreacad\gelib\api\inc\acarray.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gecurv3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gedblar.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gedll.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geent2d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geent3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gegbl.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gegblabb.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gegblge.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gegblnew.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geintarr.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geintrvl.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gelent3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gelibver.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geline3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gepent3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gepnt2d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gepnt3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geponc3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gept3dar.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gescl3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\getol.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gevc3dar.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gevec2d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gevec3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gevptar.h"\
	"..\..\..\..\coreacad\include\acadstrc.h"\
	"..\..\..\..\coreacad\include\accmd.h"\
	"..\..\..\..\coreacad\include\aced.h"\
	"..\..\..\..\coreacad\include\adesk.h"\
	"..\..\..\..\coreacad\include\dbcolor.h"\
	"..\..\..\..\coreacad\include\dbjig.h"\
	"..\..\..\..\coreacad\include\drawable.h"\
	"..\..\..\..\coreacad\include\rxdefs.h"\
	"..\..\..\..\coreacad\include\rxnames.h"\
	"..\..\..\..\coreacad\include\rxsys.h"\
	"..\..\..\..\coreacad\rx\api\rxboiler.h"\
	"..\..\..\..\coreacad\rx\api\rxclass.h"\
	"..\..\..\..\coreacad\rx\api\rxdict.h"\
	"..\..\..\..\coreacad\rx\api\rxditer.h"\
	"..\..\..\..\coreacad\rx\api\rxdlinkr.h"\
	"..\..\..\..\coreacad\rx\api\rxevent.h"\
	"..\..\..\..\coreacad\rx\api\rxiter.h"\
	"..\..\..\..\coreacad\rx\api\rxobject.h"\
	"..\..\..\..\coreacad\rx\api\rxsrvice.h"\
	".\defaultarx.h"\
	".\resourcehelper.h"\
	

"$(INTDIR)\defaultarx.obj" : $(SOURCE) $(DEP_CPP_DEFAU) "$(INTDIR)"\
 "$(INTDIR)\contextmenu.pch"


!ENDIF 

SOURCE=.\editarx.cpp

!IF  "$(CFG)" == "contextmenu - Win32 Release"

DEP_CPP_EDITA=\
	"..\..\..\..\coreacad\ads\ads.h"\
	"..\..\..\..\coreacad\ads\adsdef.h"\
	"..\..\..\..\coreacad\db\api\inc\acdb.h"\
	"..\..\..\..\coreacad\db\api\inc\dbaudita.h"\
	"..\..\..\..\coreacad\db\api\inc\dbboiler.h"\
	"..\..\..\..\coreacad\db\api\inc\dbfiler.h"\
	"..\..\..\..\coreacad\db\api\inc\dbhandle.h"\
	"..\..\..\..\coreacad\db\api\inc\dbid.h"\
	"..\..\..\..\coreacad\db\api\inc\dbid_ops.h"\
	"..\..\..\..\coreacad\db\api\inc\dbidapps.h"\
	"..\..\..\..\coreacad\db\api\inc\dbidar.h"\
	"..\..\..\..\coreacad\db\api\inc\dbintar.h"\
	"..\..\..\..\coreacad\db\api\inc\dbmain.h"\
	"..\..\..\..\coreacad\db\api\inc\dbptrar.h"\
	"..\..\..\..\coreacad\db\api\inc\dbsubeid.h"\
	"..\..\..\..\coreacad\gelib\api\inc\acarray.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gecurv3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gedblar.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gedll.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geent2d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geent3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gegbl.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gegblabb.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gegblge.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gegblnew.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geintarr.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geintrvl.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gelent3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gelibver.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geline3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gepent3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gepnt2d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gepnt3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geponc3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gept3dar.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gescl3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\getol.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gevc3dar.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gevec2d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gevec3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gevptar.h"\
	"..\..\..\..\coreacad\include\acadstrc.h"\
	"..\..\..\..\coreacad\include\accmd.h"\
	"..\..\..\..\coreacad\include\aced.h"\
	"..\..\..\..\coreacad\include\adesk.h"\
	"..\..\..\..\coreacad\include\dbcolor.h"\
	"..\..\..\..\coreacad\include\dbjig.h"\
	"..\..\..\..\coreacad\include\drawable.h"\
	"..\..\..\..\coreacad\include\rxdefs.h"\
	"..\..\..\..\coreacad\include\rxnames.h"\
	"..\..\..\..\coreacad\include\rxsys.h"\
	"..\..\..\..\coreacad\rx\api\rxboiler.h"\
	"..\..\..\..\coreacad\rx\api\rxclass.h"\
	"..\..\..\..\coreacad\rx\api\rxdict.h"\
	"..\..\..\..\coreacad\rx\api\rxditer.h"\
	"..\..\..\..\coreacad\rx\api\rxdlinkr.h"\
	"..\..\..\..\coreacad\rx\api\rxevent.h"\
	"..\..\..\..\coreacad\rx\api\rxiter.h"\
	"..\..\..\..\coreacad\rx\api\rxobject.h"\
	"..\..\..\..\coreacad\rx\api\rxsrvice.h"\
	".\editarx.h"\
	".\resourcehelper.h"\
	

"$(INTDIR)\editarx.obj" : $(SOURCE) $(DEP_CPP_EDITA) "$(INTDIR)"\
 "$(INTDIR)\contextmenu.pch"


!ELSEIF  "$(CFG)" == "contextmenu - Win32 Debug"

DEP_CPP_EDITA=\
	"..\..\..\..\coreacad\ads\ads.h"\
	"..\..\..\..\coreacad\ads\adsdef.h"\
	"..\..\..\..\coreacad\db\api\inc\acdb.h"\
	"..\..\..\..\coreacad\db\api\inc\dbaudita.h"\
	"..\..\..\..\coreacad\db\api\inc\dbboiler.h"\
	"..\..\..\..\coreacad\db\api\inc\dbfiler.h"\
	"..\..\..\..\coreacad\db\api\inc\dbhandle.h"\
	"..\..\..\..\coreacad\db\api\inc\dbid.h"\
	"..\..\..\..\coreacad\db\api\inc\dbid_ops.h"\
	"..\..\..\..\coreacad\db\api\inc\dbidapps.h"\
	"..\..\..\..\coreacad\db\api\inc\dbidar.h"\
	"..\..\..\..\coreacad\db\api\inc\dbintar.h"\
	"..\..\..\..\coreacad\db\api\inc\dbmain.h"\
	"..\..\..\..\coreacad\db\api\inc\dbptrar.h"\
	"..\..\..\..\coreacad\db\api\inc\dbsubeid.h"\
	"..\..\..\..\coreacad\gelib\api\inc\acarray.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gecurv3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gedblar.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gedll.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geent2d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geent3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gegbl.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gegblabb.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gegblge.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gegblnew.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geintarr.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geintrvl.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gelent3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gelibver.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geline3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gepent3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gepnt2d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gepnt3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\geponc3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gept3dar.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gescl3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\getol.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gevc3dar.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gevec2d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gevec3d.h"\
	"..\..\..\..\coreacad\gelib\api\inc\gevptar.h"\
	"..\..\..\..\coreacad\include\acadstrc.h"\
	"..\..\..\..\coreacad\include\accmd.h"\
	"..\..\..\..\coreacad\include\aced.h"\
	"..\..\..\..\coreacad\include\adesk.h"\
	"..\..\..\..\coreacad\include\dbcolor.h"\
	"..\..\..\..\coreacad\include\dbjig.h"\
	"..\..\..\..\coreacad\include\drawable.h"\
	"..\..\..\..\coreacad\include\rxdefs.h"\
	"..\..\..\..\coreacad\include\rxnames.h"\
	"..\..\..\..\coreacad\include\rxsys.h"\
	"..\..\..\..\coreacad\rx\api\rxboiler.h"\
	"..\..\..\..\coreacad\rx\api\rxclass.h"\
	"..\..\..\..\coreacad\rx\api\rxdict.h"\
	"..\..\..\..\coreacad\rx\api\rxditer.h"\
	"..\..\..\..\coreacad\rx\api\rxdlinkr.h"\
	"..\..\..\..\coreacad\rx\api\rxevent.h"\
	"..\..\..\..\coreacad\rx\api\rxiter.h"\
	"..\..\..\..\coreacad\rx\api\rxobject.h"\
	"..\..\..\..\coreacad\rx\api\rxsrvice.h"\
	".\editarx.h"\
	".\resourcehelper.h"\
	

"$(INTDIR)\editarx.obj" : $(SOURCE) $(DEP_CPP_EDITA) "$(INTDIR)"\
 "$(INTDIR)\contextmenu.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "contextmenu - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\..\..\coreacad\include" /I\
 "..\..\..\..\coreacad\rx\api" /I "..\..\..\..\coreacad\ads" /I\
 "..\..\..\..\coreacad\db\api\inc" /I "..\..\..\..\coreacad\gelib\api\inc" /D\
 "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D\
 "ACRXAPP" /D "RADPACK" /Fp"$(INTDIR)\contextmenu.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\contextmenu.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "contextmenu - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\..\..\..\coreacad\include"\
 /I "..\..\..\..\coreacad\rx\api" /I "..\..\..\..\coreacad\ads" /I\
 "..\..\..\..\coreacad\db\api\inc" /I "..\..\..\..\coreacad\gelib\api\inc" /D\
 "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D\
 "ACRXAPP" /D "RADPACK" /D "DEBUG_AUTOCAD" /Fp"$(INTDIR)\contextmenu.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\contextmenu.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

