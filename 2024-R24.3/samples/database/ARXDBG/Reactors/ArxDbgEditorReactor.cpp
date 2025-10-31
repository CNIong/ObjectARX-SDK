//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxDbgEditorReactor.h"
#include "ArxDbgUtils.h"
#include "ArxDbgUiTdmIdMap.h"
#include "ArxDbgUiTdmObjects.h"



ACRX_NO_CONS_DEFINE_MEMBERS(ArxDbgEditorReactor, AcEditorReactor);

/****************************************************************************
**
**  ArxDbgEditorReactor::ArxDbgEditorReactor
**
**  **jma
**
*************************************/

ArxDbgEditorReactor::ArxDbgEditorReactor()
:	m_showDetails(false)
{
    acedEditor->addReactor(this);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::~ArxDbgEditorReactor
**
**  **jma
**
*************************************/

ArxDbgEditorReactor::~ArxDbgEditorReactor()
{
    acedEditor->removeReactor(this);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::showDetails
**
**  **jma
**
*************************************/

bool
ArxDbgEditorReactor::showDetails() const
{
	return m_showDetails;
}

/****************************************************************************
**
**  ArxDbgEditorReactor::setShowDetails
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::setShowDetails(bool showThem)
{
	m_showDetails = showThem;
}

/****************************************************************************
**
**  ArxDbgEditorReactor::unknownCommand
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::unknownCommand(const TCHAR* cmdStr, AcDbVoidPtrArray *al)
{
    CString str;

    str.Format(_T("Unknown Command: %s"), cmdStr);
    printReactorMessage(str);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::commandWillStart
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::commandWillStart(const TCHAR* cmdStr)
{
    CString str;

    str.Format(_T("Command Will Start: %s"), cmdStr);
    printReactorMessage(str);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::commandEnded
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::commandEnded(const TCHAR* cmdStr)
{
    CString str;

    str.Format(_T("Command Ended: %s"), cmdStr);
    printReactorMessage(str);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::commandCancelled
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::commandCancelled(const TCHAR* cmdStr)
{
    CString str;

    str.Format(_T("Command Cancelled: %s"), cmdStr);
    printReactorMessage(str);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::commandFailed
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::commandFailed(const TCHAR* cmdStr)
{
    CString str;

    str.Format(_T("Command Failed: %s"), cmdStr);
    printReactorMessage(str);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::lispWillStart
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::lispWillStart(const TCHAR* firstLine)
{
    CString str;

    str.Format(_T("Lisp Will Start: first line = %s"), firstLine);
    printReactorMessage(str);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::lispEnded
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::lispEnded()
{
    printReactorMessage(_T("Lisp Ended"));
}

/****************************************************************************
**
**  ArxDbgEditorReactor::lispCancelled
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::lispCancelled()
{
    printReactorMessage(_T("Lisp Cancelled"));
}

/****************************************************************************
**
**  ArxDbgEditorReactor::docCloseWillStart
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::docCloseWillStart(AcDbDatabase* db)
{
    printReactorMessage(_T("Doc Close Will Start"), db);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::beginDxfIn
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::beginDxfIn(AcDbDatabase* db)
{
    printReactorMessage(_T("Begin Dxf In"), db);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::abortDxfIn
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::abortDxfIn(AcDbDatabase* db)
{
    printReactorMessage(_T("Abort Dxf In"), db);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::dxfInComplete
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::dxfInComplete(AcDbDatabase* db)
{
    printReactorMessage(_T("Dxf In Complete"), db);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::beginDxfOut
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::beginDxfOut(AcDbDatabase* db)
{
    printReactorMessage(_T("Begin Dxf Out"), db);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::abortDxfOut
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::abortDxfOut(AcDbDatabase* db)
{
    printReactorMessage(_T("Abort Dxf Out"), db);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::dxfOutComplete
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::dxfOutComplete(AcDbDatabase* db)
{
    printReactorMessage(_T("Dxf Out Complete"), db);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::beginDwgOpen
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::beginDwgOpen(const TCHAR* filename)
{
    CString str;
    str.Format(_T("Begin DWG Open: \"%s\""), filename);
    printReactorMessage(str);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::endDwgOpen
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::endDwgOpen(const TCHAR* filename, AcDbDatabase* /*pDb*/)
{
    CString str;
    str.Format(_T("End DWG Open: \"%s\""), filename);
    printReactorMessage(str);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::dwgFileOpened
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::dwgFileOpened(AcDbDatabase* db, const TCHAR* fileName)
{
    CString str;
    str.Format(_T("DWG File Opened: \"%s\""), fileName);
    printReactorMessage(str, db);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::initialDwgFileOpenComplete
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::initialDwgFileOpenComplete(AcDbDatabase* db)
{
    printReactorMessage(_T("Initial DWG File Open Complete"), db);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::databaseConstructed
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::databaseConstructed(AcDbDatabase* db)
{
    printReactorMessage(_T("Database Constructed"), db);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::databaseToBeDestroyed
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::databaseToBeDestroyed(AcDbDatabase* db)
{
    printReactorMessage(_T("Database To Be Destroyed"), db);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::beginSave
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::beginSave(AcDbDatabase* db, const TCHAR* pIntendedName)
{
    CString str;

    str.Format(_T("Begin Save: intended name = \"%s\""), pIntendedName);
    printReactorMessage(str, db);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::saveComplete
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::saveComplete(AcDbDatabase* db, const TCHAR* pActualName)
{
    CString str;

    str.Format(_T("Save Complete: actual name = \"%s\""), pActualName);
    printReactorMessage(str, db);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::abortSave
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::abortSave(AcDbDatabase* db)
{
    printReactorMessage(_T("AbortSave"), db);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::beginInsert
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::beginInsert(AcDbDatabase* pTo, const TCHAR* pBlockName, AcDbDatabase* pFrom)
{
    CString str;

    str.Format(_T("Begin Insert: \"%s\""), pBlockName);
    printReactorMessage(str, pTo, pFrom);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::beginInsert
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::beginInsert(AcDbDatabase* pTo, const AcGeMatrix3d& xform, AcDbDatabase* pFrom)
{
    printReactorMessage(_T("Begin Insert (Matrix Form)"), pTo, pFrom);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::otherInsert
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::otherInsert(AcDbDatabase* pTo, AcDbIdMapping& idMap, AcDbDatabase* pFrom)
{
    printReactorMessage(_T("Other Insert"), pTo, pFrom);

	if (m_showDetails) {
		ArxDbgUiTdmIdMap dbox(&idMap, acedGetAcadDwgView(), _T("Other Insert"));
		dbox.DoModal();
	}
}

/****************************************************************************
**
**  ArxDbgEditorReactor::abortInsert
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::abortInsert(AcDbDatabase* pTo)
{
    printReactorMessage(_T("Abort Insert"), pTo);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::endInsert
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::endInsert(AcDbDatabase* pTo)
{
    printReactorMessage(_T("End Insert"), pTo);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::wblockNotice
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::wblockNotice(AcDbDatabase* db)
{
    printReactorMessage(_T("Wblock Notice"), db);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::beginWblock
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::beginWblock(AcDbDatabase* pTo, AcDbDatabase* pFrom, const AcGePoint3d*& insertionPoint)
{
    CString str, str2;
    str.Format(_T("Begin Wblock (1): insert pt = %s"),
                        ArxDbgUtils::ptToStr(*insertionPoint, str2));
    printReactorMessage(str, pTo, pFrom);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::beginWblock
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::beginWblock(AcDbDatabase* pTo, AcDbDatabase* pFrom, AcDbObjectId blockId)
{
    CString str, blkName;

    ArxDbgUtils::symbolIdToName(blockId, blkName);
    str.Format(_T("Begin Wblock (2): blkname = %s"), blkName);
    printReactorMessage(str, pTo, pFrom);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::beginWblock
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::beginWblock(AcDbDatabase* pTo, AcDbDatabase* pFrom)
{
    printReactorMessage(_T("Begin Wblock Entire Database"), pTo, pFrom);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::otherWblock
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::otherWblock(AcDbDatabase* pTo, AcDbIdMapping& idMap, AcDbDatabase* pFrom)
{
    printReactorMessage(_T("Other Wblock"), pTo, pFrom);

	if (m_showDetails) {
		ArxDbgUiTdmIdMap dbox(&idMap, acedGetAcadDwgView(), _T("Other Wblock"));
		dbox.DoModal();
	}
}

/****************************************************************************
**
**  ArxDbgEditorReactor::abortWblock
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::abortWblock(AcDbDatabase* pTo)
{
    printReactorMessage(_T("Abort Wblock"), pTo);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::endWblock
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::endWblock(AcDbDatabase* pTo)
{
    printReactorMessage(_T("End Wblock"), pTo);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::beginDeepClone
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::beginDeepClone(AcDbDatabase* pTo, AcDbIdMapping& idMap)
{
    CString str, str2;

	ArxDbgUtils::deepCloneContextToStr(idMap.deepCloneContext(), str2);

    str.Format(_T("Begin Deep Clone: context = %s"), static_cast<LPCTSTR>(str2));
    printReactorMessage(str, pTo);

	if (m_showDetails) {
		ArxDbgUiTdmIdMap dbox(&idMap, acedGetAcadDwgView(), _T("Begin Deep Clone"));
		dbox.DoModal();
	}
}

/****************************************************************************
**
**  ArxDbgEditorReactor::beginDeepCloneXlation
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::beginDeepCloneXlation(AcDbIdMapping& idMap, Acad::ErrorStatus* pRetStatus)
{
    printReactorMessage(_T("Begin Deep Clone Translation"));

	if (m_showDetails) {
		ArxDbgUiTdmIdMap dbox(&idMap, acedGetAcadDwgView(), _T("Begin Deep Clone Xlation"));
		dbox.DoModal();
	}
}

/****************************************************************************
**
**  ArxDbgEditorReactor::abortDeepClone
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::abortDeepClone(AcDbIdMapping& idMap)
{
    printReactorMessage(_T("Abort Deep Clone"));

	if (m_showDetails) {
		ArxDbgUiTdmIdMap dbox(&idMap, acedGetAcadDwgView(), _T("Abort Deep Clone"));
		dbox.DoModal();
	}
}

/****************************************************************************
**
**  ArxDbgEditorReactor::endDeepClone
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::endDeepClone(AcDbIdMapping& idMap)
{
    printReactorMessage(_T("End Deep Clone"));

	if (m_showDetails) {
		ArxDbgUiTdmIdMap dbox(&idMap, acedGetAcadDwgView(), _T("End Deep Clone"));
		dbox.DoModal();
	}
}

/****************************************************************************
**
**  ArxDbgEditorReactor::sysVarChanged
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::sysVarChanged(const TCHAR* varName, Adesk::Boolean success)
{
    CString str;

    str.Format(_T("Sysvar Changed: %s"), varName);
    printReactorMessage(str);
    if (success != Adesk::kTrue)
        acutPrintf(_T("\n*** SYSVAR NOT CHANGED SUCCESSFULLY!!! ***"));
}

/****************************************************************************
**
**  ArxDbgEditorReactor::sysVarWillChange
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::sysVarWillChange(const TCHAR* varName)
{
    CString str;

    str.Format(_T("Sysvar Will Change: %s"), varName);
    printReactorMessage(str);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::beginAttach
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::beginAttach(AcDbDatabase* pTo, const TCHAR* pName, AcDbDatabase* pFrom)
{
    CString str;

    str.Format(_T("Begin Attach: %s"), pName);
    printReactorMessage(str, pTo, pFrom);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::otherAttach
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::otherAttach(AcDbDatabase* pTo, AcDbDatabase* pFrom)
{
    printReactorMessage(_T("Other Attach"), pTo, pFrom);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::abortAttach
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::abortAttach(AcDbDatabase* pTo)
{
    printReactorMessage(_T("Abort Attach"), pTo);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::endAttach
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::endAttach(AcDbDatabase* pTo)
{
    printReactorMessage(_T("End Attach"), pTo);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::redirected
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::redirected(AcDbObjectId newId, AcDbObjectId oldId)
{
    printReactorMessage(_T("Redirected"), oldId);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::comandeered
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::comandeered(AcDbDatabase* pTo, AcDbObjectId id, AcDbDatabase* pFrom)
{
    printReactorMessage(_T("Comandeered"), id);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::beginRestore
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::beginRestore(AcDbDatabase* pTo, const TCHAR*, AcDbDatabase* pFrom)
{
    printReactorMessage(_T("Begin Restore"), pTo, pFrom);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::abortRestore
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::abortRestore(AcDbDatabase* pTo)
{
    printReactorMessage(_T("Abort Restore"), pTo);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::endRestore
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::endRestore(AcDbDatabase* pTo)
{
    printReactorMessage(_T("End Restore"), pTo);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::xrefSubcommandBindItem
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::xrefSubcommandBindItem(AcDbDatabase* pHost, int activity, AcDbObjectId blockId)
{
    CString str, str2;

    str.Format(_T("Xref sub-command bind item: activity = %s"),
                            xrefActivityToStr(activity, str2));
    printReactorMessage(str);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::xrefSubcommandAttachItem
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::xrefSubcommandAttachItem(AcDbDatabase* pHost, int activity, const TCHAR* pPath)
{
    CString str, str2;
    LPCTSTR tmpStr;

        // sometimes comes through as null!
    if (pPath == NULL)
        tmpStr = _T("(NULL)");
    else
        tmpStr = pPath;

    str.Format(_T("Xref sub-command attach item: activity = %s, path = %s"), 
                            xrefActivityToStr(activity, str2), tmpStr);
    printReactorMessage(str);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::xrefSubcommandOverlayItem
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::xrefSubcommandOverlayItem(AcDbDatabase* pHost, int activity, const TCHAR* pPath)
{
    CString str, str2;

    str.Format(_T("Xref sub-command overlay item: activity = %s, path = %s"), 
                            xrefActivityToStr(activity, str2), pPath);
    printReactorMessage(str);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::xrefSubcommandDetachItem
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::xrefSubcommandDetachItem(AcDbDatabase* pHost, int activity, AcDbObjectId blockId)
{
    CString str, str2;

    str.Format(_T("Xref sub-command detach item: activity = %s"),
                            xrefActivityToStr(activity, str2));

    printReactorMessage(str);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::xrefSubcommandPathItem
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::xrefSubcommandPathItem(int activity, AcDbObjectId blockId, const TCHAR* pNewPath)
{
    CString str, str2;

    str.Format(_T("Xref sub-command path item: activity = %s, path = %s"), 
                            xrefActivityToStr(activity, str2), pNewPath);
    printReactorMessage(str);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::xrefSubcommandReloadItem
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::xrefSubcommandReloadItem(AcDbDatabase* pHost, int activity, AcDbObjectId blockId)
{
    CString str, str2;

    str.Format(_T("Xref sub-command reload item: activity = %s"), 
                            xrefActivityToStr(activity, str2));
    printReactorMessage(str);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::xrefSubcommandUnloadItem
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::xrefSubcommandUnloadItem(AcDbDatabase* pHost, int activity, AcDbObjectId blockId)
{
    CString str, str2;

    str.Format(_T("Xref sub-command unload item: activity = %s"), 
                            xrefActivityToStr(activity, str2));
    printReactorMessage(str);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::undoSubcommandAuto
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::undoSubcommandAuto(int activity, Adesk::Boolean state)
{
    CString str, str2;
    str.Format(_T("Undo Subcommand Auto: activity = %s, state = %d"),
                    undoActivityToStr(activity, str2), state);

    printReactorMessage(str);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::undoSubcommandControl
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::undoSubcommandControl(int activity, int option)
{
    CString str, str2;
    str.Format(_T("Undo Subcommand Control: activity = %s, option = %d"),
                    undoActivityToStr(activity, str2), option);

    printReactorMessage(str);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::undoSubcommandBegin
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::undoSubcommandBegin(int activity)
{
    CString str, str2;
    str.Format(_T("Undo Subcommand Begin: activity = %s"), undoActivityToStr(activity, str2));

    printReactorMessage(str);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::undoSubcommandEnd
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::undoSubcommandEnd(int activity)
{
    CString str, str2;
    str.Format(_T("Undo Subcommand End: activity = %s"), undoActivityToStr(activity, str2));

    printReactorMessage(str);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::undoSubcommandMark
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::undoSubcommandMark(int activity)
{
    CString str, str2;
    str.Format(_T("Undo Subcommand Mark: activity = %s"), undoActivityToStr(activity, str2));

    printReactorMessage(str);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::undoSubcommandBack
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::undoSubcommandBack(int activity)
{
    CString str, str2;
    str.Format(_T("Undo Subcommand Back: activity = %s"), undoActivityToStr(activity, str2));

    printReactorMessage(str);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::undoSubcommandNumber
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::undoSubcommandNumber(int activity, int num)
{
    CString str, str2;
    str.Format(_T("Undo Subcommand Number: activity = %s, #%d"),
                        undoActivityToStr(activity, str2), num);

    printReactorMessage(str);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::pickfirstModified
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::pickfirstModified()
{
    printReactorMessage(_T("Pickfirst Modified"));
}

/****************************************************************************
**
**  ArxDbgEditorReactor::layoutSwitched
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::layoutSwitched(const TCHAR* newLayoutName)
{
    CString str;
    str.Format(_T("Layout Switched: %s"), newLayoutName);
    printReactorMessage(str);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::docFrameMovedOrResized
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::docFrameMovedOrResized(long hwndDocFrame, bool bMoved)
{
    if (bMoved)
        printReactorMessage(_T("Doc Frame Moved"));
    else
        printReactorMessage(_T("Doc Frame Resized"));
}

/****************************************************************************
**
**  ArxDbgEditorReactor::mainFrameMovedOrResized
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::mainFrameMovedOrResized(long hwndMainFrame, bool bMoved)
{
    if (bMoved)
        printReactorMessage(_T("Main Frame Moved"));
    else
        printReactorMessage(_T("Main Frame Resized"));
}

/****************************************************************************
**
**  ArxDbgEditorReactor::beginDoubleClick
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::beginDoubleClick(const AcGePoint3d& clickPoint)
{
    printReactorMessage(_T("Begin Double-click"));
}

/****************************************************************************
**
**  ArxDbgEditorReactor::beginRightClick
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::beginRightClick(const AcGePoint3d& clickPoint)
{
    printReactorMessage(_T("Begin Right-click"));
}

/****************************************************************************
**
**  ArxDbgEditorReactor::toolbarBitmapSizeWillChange
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::toolbarBitmapSizeWillChange(Adesk::Boolean bLarge)
{
    printReactorMessage(_T("Toolbar Bitmap Size Will Change"));
}

/****************************************************************************
**
**  ArxDbgEditorReactor::toolbarBitmapSizeChanged
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::toolbarBitmapSizeChanged(Adesk::Boolean bLarge)
{
    printReactorMessage(_T("Toolbar Bitmap Size Changed"));
}

/****************************************************************************
**
**  ArxDbgEditorReactor::beginWblockObjects
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::beginWblockObjects(AcDbDatabase* pFrom, AcDbIdMapping& idMap)
{
    printReactorMessage(_T("Begin Wblock Objects"), pFrom);

	if (m_showDetails) {
		ArxDbgUiTdmIdMap dbox(&idMap, acedGetAcadDwgView(), _T("Begin Wblock Objects"));
		dbox.DoModal();
	}
}

/****************************************************************************
**
**  ArxDbgEditorReactor::partialOpenNotice
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::partialOpenNotice(AcDbDatabase* db)
{
    printReactorMessage(_T("Partial Open Notice"), db);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::objectsLazyLoaded
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::objectsLazyLoaded(const AcDbObjectIdArray& idArray)
{
    printReactorMessage(_T("Objects Lazy Loaded"));

	if (m_showDetails) {
		ArxDbgUiTdmObjects dbox(idArray, acedGetAcadDwgView(), _T("Objects Lazy Loaded"));
		dbox.DoModal();
	}
}

/****************************************************************************
**
**  ArxDbgEditorReactor::beginQuit
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::beginQuit()
{
    printReactorMessage(_T("Begin Quit"));
}

/****************************************************************************
**
**  ArxDbgEditorReactor::quitAborted
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::quitAborted()
{
    printReactorMessage(_T("Quit Aborted"));
}

/****************************************************************************
**
**  ArxDbgEditorReactor::quitWillStart
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::quitWillStart()
{
    printReactorMessage(_T("Quit Will Start"));
}

/****************************************************************************
**
**  ArxDbgEditorReactor::modelessOperationWillStart
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::modelessOperationWillStart(const TCHAR* contextStr)
{
    printReactorMessage(_T("Modeless Operation Will Start"), contextStr);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::modelessOperationEnded
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::modelessOperationEnded(const TCHAR* contextStr)
{
    printReactorMessage(_T("Modeless Operation Ended"), contextStr);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::printReactorMessage(LPCTSTR event) const
{
    acutPrintf(_T("\n%-15s : [%s] "), _T("[ED REACTOR]"), event);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::printReactorMessage(LPCTSTR event, LPCTSTR msg) const
{
    acutPrintf(_T("\n%-15s : [%s, %s] "), _T("[EVENT REACTOR]"), event, msg);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::printReactorMessage(LPCTSTR event, AcDbDatabase* pDb) const
{
    CString str;

    acutPrintf(_T("\n%-15s : [%s]   (Db = %s)"), _T("[ED REACTOR]"), event, ArxDbgUtils::dbToStr(pDb, str));
}

/****************************************************************************
**
**  ArxDbgEditorReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::printReactorMessage(LPCTSTR event, AcDbDatabase* pTo, AcDbDatabase* pFrom) const
{
    CString tmpStr1, tmpStr2;
	ArxDbgUtils::dbToStr(pTo, tmpStr1);
	ArxDbgUtils::dbToStr(pFrom, tmpStr2);

    acutPrintf(_T("\n%-15s : [%s]   (To = %s, From = %s)"), _T("[ED REACTOR]"), event, tmpStr1, tmpStr2);
}

/****************************************************************************
**
**  ArxDbgEditorReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxDbgEditorReactor::printReactorMessage(LPCTSTR event, const AcDbObjectId& objId) const
{
    CString str;
    AcDbObject* obj;
    Acad::ErrorStatus es = acdbOpenAcDbObject(obj, objId, AcDb::kForRead);
    if (es == Acad::eOk) {
        acutPrintf(_T("\n%-15s : [%-18s: %s, %s] "), _T("[ED REACTOR]"), event,
                ArxDbgUtils::objToClassStr(obj), ArxDbgUtils::objToHandleStr(obj, str));
        obj->close();
    }
    else {
        ArxDbgUtils::rxErrorMsg(es);
        printReactorMessage(event);
    }
}

/****************************************************************************
**
**  ArxDbgEditorReactor::xrefActivityToStr
**
**  **jma
**
*************************************/

LPCTSTR
ArxDbgEditorReactor::xrefActivityToStr(int activity, CString& str)
{
    if (activity == kStart)
        str = _T("Start");
    else if (activity == kStartItem)
        str = _T("Start Item");
    else if (activity == kEndItem)
        str = _T("End Item");
    else if (activity == kEnd)
        str = _T("End");
    else if (activity == kWillAbort)
        str = _T("Will Abort");
    else if (activity == kAborted)
        str = _T("Aborted");
    else if (activity == kStartXBindBlock)
        str = _T("Start XBind Block");
    else if (activity == kStartXBindSymbol)
        str = _T("Start XBind Symbol");
    else {
        ASSERT(0);
        ArxDbgUtils::intToStr(activity, str);
    }

    return str;
}

/****************************************************************************
**
**  ArxDbgEditorReactor::undoActivityToStr
**
**  **jma
**
*************************************/

LPCTSTR
ArxDbgEditorReactor::undoActivityToStr(int activity, CString& str)
{
    if (activity == kNone)
        str = _T("None");
    else if (activity == kOne)
        str = _T("One");
    else if (activity == kAll)
        str = _T("All");
    else {
        ASSERT(0);
        ArxDbgUtils::intToStr(activity, str);
    }

    return str;
}
