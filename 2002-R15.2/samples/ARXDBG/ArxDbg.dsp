# Microsoft Developer Studio Project File - Name="ArxDbg" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=ArxDbg - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ArxDbg.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ArxDbg.mak" CFG="ArxDbg - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ArxDbg - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ArxDbg - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ArxDbg - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /GX /O2 /Oy- /I "." /I ".\inc" /I "..\..\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 acad.lib acdb15.lib acedapi.lib acge15.lib acgiapi.lib achapi15.lib acISMobj15.lib acrx15.lib acutil15.lib acui15.lib adui15.lib rxapi.lib /nologo /subsystem:windows /dll /machine:I386 /out:".\Release\ArxDbg.arx" /libpath:"../../lib"

!ELSEIF  "$(CFG)" == "ArxDbg - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /Gm /GX /Zi /Od /I "." /I ".\inc" /I "..\..\inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 acad.lib acdb15.lib acedapi.lib acge15.lib acgiapi.lib achapi15.lib acISMobj15.lib acrx15.lib acutil15.lib acui15.lib adui15.lib rxapi.lib /nologo /subsystem:windows /dll /debug /machine:I386 /nodefaultlib:"msvcrtd" /out:".\Debug\ArxDbgd.arx" /libpath:"../../lib"
# SUBTRACT LINK32 /nodefaultlib

!ENDIF 

# Begin Target

# Name "ArxDbg - Win32 Release"
# Name "ArxDbg - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\AcadUtils\AcadStr.cpp
# End Source File
# Begin Source File

SOURCE=.\ArxDbg.def

!IF  "$(CFG)" == "ArxDbg - Win32 Release"

!ELSEIF  "$(CFG)" == "ArxDbg - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ArxDbg.rc
# End Source File
# Begin Source File

SOURCE=.\App\ArxDbgApp.cpp
# End Source File
# Begin Source File

SOURCE=.\App\ArxDbgAppEditorReactor.cpp
# End Source File
# Begin Source File

SOURCE=.\Snoop\ArxDbgCloneSet.cpp
# End Source File
# Begin Source File

SOURCE=.\AdeskLogo\ArxDbgCmdAdeskLogo.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphicsContainer\ArxDbgCmdGraphicsContainer.cpp
# End Source File
# Begin Source File

SOURCE=.\Reactors\ArxDbgCmdReactors.cpp
# End Source File
# Begin Source File

SOURCE=.\Snoop\ArxDbgCmdSnoop.cpp
# End Source File
# Begin Source File

SOURCE=.\Tests\ArxDbgCmdTests.cpp
# End Source File
# Begin Source File

SOURCE=.\ArxDbgd.def

!IF  "$(CFG)" == "ArxDbg - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ArxDbg - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Reactors\ArxDbgDatabaseReactor.cpp
# End Source File
# Begin Source File

SOURCE=.\AdeskLogo\ArxDbgDbAdeskLogo.cpp
# End Source File
# Begin Source File

SOURCE=.\AdeskLogo\ArxDbgDbAdeskLogoStyle.cpp
# End Source File
# Begin Source File

SOURCE=.\BaseClasses\ArxDbgDbDictRecord.cpp
# End Source File
# Begin Source File

SOURCE=.\BaseClasses\ArxDbgDbEntity.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphicsContainer\ArxDbgDbGraphicsContainer.cpp
# End Source File
# Begin Source File

SOURCE=.\Reactors\ArxDbgDLinkerReactor.cpp
# End Source File
# Begin Source File

SOURCE=.\AcadUtils\ArxDbgDocLockWrite.cpp
# End Source File
# Begin Source File

SOURCE=.\Reactors\ArxDbgDocumentReactor.cpp
# End Source File
# Begin Source File

SOURCE=.\Filers\ArxDbgDwgFiler.cpp
# End Source File
# Begin Source File

SOURCE=.\Reactors\ArxDbgEdInputContextReactor.cpp
# End Source File
# Begin Source File

SOURCE=.\Reactors\ArxDbgEditorReactor.cpp
# End Source File
# Begin Source File

SOURCE=.\App\ArxDbgEdUiContext.cpp
# End Source File
# Begin Source File

SOURCE=.\Reactors\ArxDbgEventReactor.cpp
# End Source File
# Begin Source File

SOURCE=.\Reactors\ArxDbgGsReactor.cpp
# End Source File
# Begin Source File

SOURCE=.\Prompt\ArxDbgKeywordArray.cpp
# End Source File
# Begin Source File

SOURCE=.\Reactors\ArxDbgLayoutManagerReactor.cpp
# End Source File
# Begin Source File

SOURCE=.\Reactors\ArxDbgLongTransactionReactor.cpp
# End Source File
# Begin Source File

SOURCE=.\App\ArxDbgOptions.cpp
# End Source File
# Begin Source File

SOURCE=.\ArxDbgp.def
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Reactors\ArxDbgPersistentEntReactor.cpp
# End Source File
# Begin Source File

SOURCE=.\Reactors\ArxDbgPersistentObjReactor.cpp
# End Source File
# Begin Source File

SOURCE=.\AcadUtils\ArxDbgRbList.cpp
# End Source File
# Begin Source File

SOURCE=.\Filers\ArxDbgReferenceFiler.cpp
# End Source File
# Begin Source File

SOURCE=.\AcadUtils\ArxDbgSelSet.cpp
# End Source File
# Begin Source File

SOURCE=.\Reactors\ArxDbgTransactionReactor.cpp
# End Source File
# Begin Source File

SOURCE=.\Reactors\ArxDbgTransientEntReactor.cpp
# End Source File
# Begin Source File

SOURCE=.\Reactors\ArxDbgTransientObjReactor.cpp
# End Source File
# Begin Source File

SOURCE=.\App\ArxDbgUiDlgAboutBox.cpp
# End Source File
# Begin Source File

SOURCE=.\Snoop\ArxDbgUiDlgClassDict.cpp
# End Source File
# Begin Source File

SOURCE=.\Tests\ArxDbgUiDlgColor.cpp
# End Source File
# Begin Source File

SOURCE=.\Snoop\ArxDbgUiDlgDxf.cpp
# End Source File
# Begin Source File

SOURCE=.\Filers\ArxDbgUiDlgFilerTest.cpp
# End Source File
# Begin Source File

SOURCE=.\Ui\ArxDbgUiDlgGenericDefId.cpp
# End Source File
# Begin Source File

SOURCE=.\Snoop\ArxDbgUiDlgObjectId.cpp
# End Source File
# Begin Source File

SOURCE=.\Snoop\ArxDbgUiDlgObjState.cpp
# End Source File
# Begin Source File

SOURCE=.\Snoop\ArxDbgUiDlgReactors.cpp
# End Source File
# Begin Source File

SOURCE=.\Tests\ArxDbgUiDlgSelSet.cpp
# End Source File
# Begin Source File

SOURCE=.\Snoop\ArxDbgUiDlgServiceDict.cpp
# End Source File
# Begin Source File

SOURCE=.\Ui\ArxDbgUiDlgSplash.cpp
# End Source File
# Begin Source File

SOURCE=.\Snoop\ArxDbgUiDlgSysRegistry.cpp
# End Source File
# Begin Source File

SOURCE=.\Tests\ArxDbgUiDlgTestCurves.cpp
# End Source File
# Begin Source File

SOURCE=.\Tests\ArxDbgUiDlgWorldDraw.cpp
# End Source File
# Begin Source File

SOURCE=.\Snoop\ArxDbgUiDlgXdata.cpp
# End Source File
# Begin Source File

SOURCE=.\Prompt\ArxDbgUiPrAngle.cpp
# End Source File
# Begin Source File

SOURCE=.\Prompt\ArxDbgUiPrAngleDef.cpp
# End Source File
# Begin Source File

SOURCE=.\Prompt\ArxDbgUiPrBase.cpp
# End Source File
# Begin Source File

SOURCE=.\Prompt\ArxDbgUiPrCorner.cpp
# End Source File
# Begin Source File

SOURCE=.\Prompt\ArxDbgUiPrDist.cpp
# End Source File
# Begin Source File

SOURCE=.\Prompt\ArxDbgUiPrDistDef.cpp
# End Source File
# Begin Source File

SOURCE=.\Prompt\ArxDbgUiPrDouble.cpp
# End Source File
# Begin Source File

SOURCE=.\Prompt\ArxDbgUiPrDoubleDef.cpp
# End Source File
# Begin Source File

SOURCE=.\Prompt\ArxDbgUiPrEntity.cpp
# End Source File
# Begin Source File

SOURCE=.\Prompt\ArxDbgUiPrInt.cpp
# End Source File
# Begin Source File

SOURCE=.\Prompt\ArxDbgUiPrIntDef.cpp
# End Source File
# Begin Source File

SOURCE=.\Prompt\ArxDbgUiPrKeyWord.cpp
# End Source File
# Begin Source File

SOURCE=.\Prompt\ArxDbgUiPrKeyWordDef.cpp
# End Source File
# Begin Source File

SOURCE=.\Prompt\ArxDbgUiPrPoint.cpp
# End Source File
# Begin Source File

SOURCE=.\Prompt\ArxDbgUiPrString.cpp
# End Source File
# Begin Source File

SOURCE=.\Prompt\ArxDbgUiPrStringDef.cpp
# End Source File
# Begin Source File

SOURCE=.\Snoop\ArxDbgUiTdcClasses.cpp
# End Source File
# Begin Source File

SOURCE=.\TransDbClones\ArxDbgUiTdcCloneSet.cpp
# End Source File
# Begin Source File

SOURCE=.\Snoop\ArxDbgUiTdcCmds.cpp
# End Source File
# Begin Source File

SOURCE=.\Snoop\ArxDbgUiTdcDatabase.cpp
# End Source File
# Begin Source File

SOURCE=.\Snoop\ArxDbgUiTdcDbObjectBase.cpp
# End Source File
# Begin Source File

SOURCE=.\Snoop\ArxDbgUiTdcDict.cpp
# End Source File
# Begin Source File

SOURCE=.\Snoop\ArxDbgUiTdcDocs.cpp
# End Source File
# Begin Source File

SOURCE=.\Snoop\ArxDbgUiTdcEntities.cpp
# End Source File
# Begin Source File

SOURCE=.\Snoop\ArxDbgUiTdcHostAppSrv.cpp
# End Source File
# Begin Source File

SOURCE=.\Snoop\ArxDbgUiTdcIdMap.cpp
# End Source File
# Begin Source File

SOURCE=.\TransDbClones\ArxDbgUiTdcInsert.cpp
# End Source File
# Begin Source File

SOURCE=.\Snoop\ArxDbgUiTdcLongTrans.cpp
# End Source File
# Begin Source File

SOURCE=.\Snoop\ArxDbgUiTdcObjects.cpp
# End Source File
# Begin Source File

SOURCE=.\Reactors\ArxDbgUiTdcObjReactorsBase.cpp
# End Source File
# Begin Source File

SOURCE=.\App\ArxDbgUiTdcOptions.cpp
# End Source File
# Begin Source File

SOURCE=.\Reactors\ArxDbgUiTdcPersistentReactors.cpp
# End Source File
# Begin Source File

SOURCE=.\Snoop\ArxDbgUiTdcReferences.cpp
# End Source File
# Begin Source File

SOURCE=.\Snoop\ArxDbgUiTdcRxObjectBase.cpp
# End Source File
# Begin Source File

SOURCE=.\Snoop\ArxDbgUiTdcSymTbl.cpp
# End Source File
# Begin Source File

SOURCE=.\Reactors\ArxDbgUiTdcSysReactors.cpp
# End Source File
# Begin Source File

SOURCE=.\Reactors\ArxDbgUiTdcTransientReactors.cpp
# End Source File
# Begin Source File

SOURCE=.\TransDbClones\ArxDbgUiTdcWblockClone.cpp
# End Source File
# Begin Source File

SOURCE=.\Snoop\ArxDbgUiTdmDatabase.cpp
# End Source File
# Begin Source File

SOURCE=.\Snoop\ArxDbgUiTdmEditor.cpp
# End Source File
# Begin Source File

SOURCE=.\Snoop\ArxDbgUiTdmEntities.cpp
# End Source File
# Begin Source File

SOURCE=.\Snoop\ArxDbgUiTdmIdMap.cpp
# End Source File
# Begin Source File

SOURCE=.\Snoop\ArxDbgUiTdmLongTrans.cpp
# End Source File
# Begin Source File

SOURCE=.\Snoop\ArxDbgUiTdmObjects.cpp
# End Source File
# Begin Source File

SOURCE=.\Reactors\ArxDbgUiTdmReactors.cpp
# End Source File
# Begin Source File

SOURCE=.\Snoop\ArxDbgUiTdmReferences.cpp
# End Source File
# Begin Source File

SOURCE=.\TransDbClones\ArxDbgUiTdmTransDbClones.cpp
# End Source File
# Begin Source File

SOURCE=.\AcadUtils\ArxDbgUtilsAcadUi.cpp
# End Source File
# Begin Source File

SOURCE=.\AcadUtils\ArxDbgUtilsDb.cpp
# End Source File
# Begin Source File

SOURCE=.\AcadUtils\ArxDbgUtilsDict.cpp
# End Source File
# Begin Source File

SOURCE=.\AcadUtils\ArxDbgUtilsGe.cpp
# End Source File
# Begin Source File

SOURCE=.\AcadUtils\ArxDbgUtilsSymTbl.cpp
# End Source File
# Begin Source File

SOURCE=.\Tests\ArxDbgWorldDraw.cpp
# End Source File
# Begin Source File

SOURCE=.\AcadUtils\ArxDbgXdata.cpp
# End Source File
# Begin Source File

SOURCE=.\Tests\EntMakeTest.cpp
# End Source File
# Begin Source File

SOURCE=.\Tests\MapTest.cpp
# End Source File
# Begin Source File

SOURCE=.\MfcExt\SdStrList.cpp
# End Source File
# Begin Source File

SOURCE=.\AcadUtils\SdStrObjId.cpp
# End Source File
# Begin Source File

SOURCE=.\AcadUtils\SdSysVar.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Tests\TblMakeTest.cpp
# End Source File
# Begin Source File

SOURCE=.\MfcExt\UiUtils.cpp
# End Source File
# Begin Source File

SOURCE=.\Tests\XformTest.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\Inc\AcadStdafx.h
# End Source File
# Begin Source File

SOURCE=.\Inc\AcadStr.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgApp.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgAppEditorReactor.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgCmd.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgCmdAdeskLogo.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgCmdReactors.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgCmdSnoop.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgCmdTests.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgDatabaseReactor.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgDbAdeskLogo.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgDbAdeskLogoStyle.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgDbDictRecord.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgDbEntity.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgDbGraphicsContainer.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgDlgColor.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgDLinkerReactor.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgDocumentReactor.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgDwgFiler.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgEdInputContextReactor.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgEditorReactor.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgEdUiContext.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgEventReactor.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgGsReactor.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgKeywordArray.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgLayoutManagerReactor.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgLongTransactionReactor.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgPersistentEntReactor.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgPersistentObjReactor.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgRbList.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgSelSet.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgTransactionReactor.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgTransientEntReactor.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgTransientObjReactor.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiDlgAboutBox.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiDlgClassDict.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiDlgColor.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiDlgDxf.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiDlgFilerTest.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiDlgGenericDefId.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiDlgObjState.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiDlgReactors.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiDlgServiceDict.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiDlgSplash.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiDlgSysRegistry.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiDlgTestCurves.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiDlgWorldDraw.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiDlgXdata.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiPrAngle.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiPrAngleDef.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiPrBase.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiPrCorner.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiPrDist.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiPrDistDef.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiPrDouble.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiPrDoubleDef.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiPrEntity.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiPrInt.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiPrIntDef.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiPrKeyWord.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiPrKeyWordDef.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiPrompts.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiPrPoint.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiPrString.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiPrStringDef.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiPsDatabase.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiPsEntities.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiTdcClasses.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiTdcCmds.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiTdcDatabase.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiTdcDbObjectBase.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiTdcDict.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiTdcDocs.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiTdcEntities.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiTdcIdMap.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiTdcLongTrans.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiTdcObjects.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiTdcObjReactorsBase.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiTdcOptions.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiTdcPersistentReactors.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiTdcRxObjectBase.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiTdcSymTbl.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiTdcSysReactors.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiTdcTransientReactors.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiTdmDatabase.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiTdmEditor.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiTdmEntities.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiTdmIdMap.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiTdmLongTrans.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiTdmObjects.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUiTdmReactors.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUtils.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgUtilsGe.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgWorldDraw.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ArxDbgXdata.h
# End Source File
# Begin Source File

SOURCE=.\Inc\EntMakeTest.h
# End Source File
# Begin Source File

SOURCE=.\Inc\ExtDwgDbox.h
# End Source File
# Begin Source File

SOURCE=.\Inc\FilerTestDbox.h
# End Source File
# Begin Source File

SOURCE=.\Inc\MapTest.h
# End Source File
# Begin Source File

SOURCE=.\Res_ArxDbg.h
# End Source File
# Begin Source File

SOURCE=.\Inc\SdStrList.h
# End Source File
# Begin Source File

SOURCE=.\Inc\SdStrObjId.h
# End Source File
# Begin Source File

SOURCE=.\Inc\SdSysVar.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Inc\TblMakeTest.h
# End Source File
# Begin Source File

SOURCE=.\Inc\XformTest.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\ArxDbg.rc2
# End Source File
# Begin Source File

SOURCE=.\res\arxdbg_b.bmp
# End Source File
# Begin Source File

SOURCE=.\res\dwg.bmp
# End Source File
# Begin Source File

SOURCE=.\res\splash.bmp
# End Source File
# End Group
# Begin Group "Libraries"

# PROP Default_Filter ".lib"
# End Group
# End Target
# End Project
