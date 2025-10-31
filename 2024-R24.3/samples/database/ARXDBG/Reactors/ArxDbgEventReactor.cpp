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

#include "ArxDbgEventReactor.h"
#include "ArxDbgUtils.h"
#include "ArxDbgUiTdmIdMap.h"



ACRX_NO_CONS_DEFINE_MEMBERS(ArxDbgEventReactor, AcRxEventReactor);

/****************************************************************************
**
**  ArxDbgEventReactor::ArxDbgEventReactor
**
**  **jma
**
*************************************/

ArxDbgEventReactor::ArxDbgEventReactor()
:	m_showDetails(false)
{
    acrxEvent->addReactor(this);
}

/****************************************************************************
**
**  ArxDbgEventReactor::~ArxDbgEventReactor
**
**  **jma
**
*************************************/

ArxDbgEventReactor::~ArxDbgEventReactor()
{
    acrxEvent->removeReactor(this);
}

/****************************************************************************
**
**  ArxDbgEventReactor::showDetails
**
**  **jma
**
*************************************/

bool
ArxDbgEventReactor::showDetails() const
{
	return m_showDetails;
}

/****************************************************************************
**
**  ArxDbgEventReactor::setShowDetails
**
**  **jma
**
*************************************/

void
ArxDbgEventReactor::setShowDetails(bool showThem)
{
	m_showDetails = showThem;
}

/****************************************************************************
**
**  ArxDbgEventReactor::beginDxfIn
**
**  **jma
**
*************************************/

void
ArxDbgEventReactor::beginDxfIn(AcDbDatabase* db)
{
    printReactorMessage(_T("Begin Dxf In"), db);
}

/****************************************************************************
**
**  ArxDbgEventReactor::abortDxfIn
**
**  **jma
**
*************************************/

void
ArxDbgEventReactor::abortDxfIn(AcDbDatabase* db)
{
    printReactorMessage(_T("Abort Dxf In"), db);
}

/****************************************************************************
**
**  ArxDbgEventReactor::dxfInComplete
**
**  **jma
**
*************************************/

void
ArxDbgEventReactor::dxfInComplete(AcDbDatabase* db)
{
    printReactorMessage(_T("Dxf In Complete"), db);
}

/****************************************************************************
**
**  ArxDbgEventReactor::beginDxfOut
**
**  **jma
**
*************************************/

void
ArxDbgEventReactor::beginDxfOut(AcDbDatabase* db)
{
    printReactorMessage(_T("Begin Dxf Out"), db);
}

/****************************************************************************
**
**  ArxDbgEventReactor::abortDxfOut
**
**  **jma
**
*************************************/

void
ArxDbgEventReactor::abortDxfOut(AcDbDatabase* db)
{
    printReactorMessage(_T("Abort Dxf Out"), db);
}

/****************************************************************************
**
**  ArxDbgEventReactor::dxfOutComplete
**
**  **jma
**
*************************************/

void
ArxDbgEventReactor::dxfOutComplete(AcDbDatabase* db)
{
    printReactorMessage(_T("Dxf Out Complete"), db);
}

/****************************************************************************
**
**  ArxDbgEventReactor::dwgFileOpened
**
**  **jma
**
*************************************/

void
ArxDbgEventReactor::dwgFileOpened(AcDbDatabase* db, const TCHAR* fileName)
{
    CString str;
    str.Format(_T("DWG File Opened: \"%s\""), fileName);
    printReactorMessage(str, db);
}

/****************************************************************************
**
**  ArxDbgEventReactor::initialDwgFileOpenComplete
**
**  **jma
**
*************************************/

void
ArxDbgEventReactor::initialDwgFileOpenComplete(AcDbDatabase* db)
{
    printReactorMessage(_T("Initial DWG File Open Complete"), db);
}

/****************************************************************************
**
**  ArxDbgEventReactor::databaseConstructed
**
**  **jma
**
*************************************/

void
ArxDbgEventReactor::databaseConstructed(AcDbDatabase* db)
{
    printReactorMessage(_T("Database Constructed"), db);
}

/****************************************************************************
**
**  ArxDbgEventReactor::databaseToBeDestroyed
**
**  **jma
**
*************************************/

void
ArxDbgEventReactor::databaseToBeDestroyed(AcDbDatabase* db)
{
    printReactorMessage(_T("Database To Be Destroyed"), db);
}

/****************************************************************************
**
**  ArxDbgEventReactor::beginSave
**
**  **jma
**
*************************************/

void
ArxDbgEventReactor::beginSave(AcDbDatabase* db, const TCHAR* pIntendedName)
{
    CString str;

    str.Format(_T("Begin Save: intended name = \"%s\""), pIntendedName);
    printReactorMessage(str, db);
}

/****************************************************************************
**
**  ArxDbgEventReactor::saveComplete
**
**  **jma
**
*************************************/

void
ArxDbgEventReactor::saveComplete(AcDbDatabase* db, const TCHAR* pActualName)
{
    CString str;

    str.Format(_T("Save Complete: actual name = \"%s\""), pActualName);
    printReactorMessage(str, db);
}

/****************************************************************************
**
**  ArxDbgEventReactor::abortSave
**
**  **jma
**
*************************************/

void
ArxDbgEventReactor::abortSave(AcDbDatabase* db)
{
    printReactorMessage(_T("AbortSave"), db);
}

/****************************************************************************
**
**  ArxDbgEventReactor::beginInsert
**
**  **jma
**
*************************************/

void
ArxDbgEventReactor::beginInsert(AcDbDatabase* pTo, const TCHAR* pBlockName, AcDbDatabase* pFrom)
{
    CString str;

    str.Format(_T("Begin Insert: \"%s\""), pBlockName);
    printReactorMessage(str, pTo, pFrom);
}

/****************************************************************************
**
**  ArxDbgEventReactor::beginInsert
**
**  **jma
**
*************************************/

void
ArxDbgEventReactor::beginInsert(AcDbDatabase* pTo, const AcGeMatrix3d& xform, AcDbDatabase* pFrom)
{
    printReactorMessage(_T("Begin Insert (Matrix Form)"), pTo, pFrom);
}

/****************************************************************************
**
**  ArxDbgEventReactor::otherInsert
**
**  **jma
**
*************************************/

void
ArxDbgEventReactor::otherInsert(AcDbDatabase* pTo, AcDbIdMapping& idMap, AcDbDatabase* pFrom)
{
    printReactorMessage(_T("Other Insert"), pTo, pFrom);

	if (m_showDetails) {
		ArxDbgUiTdmIdMap dbox(&idMap, acedGetAcadDwgView(), _T("Other Insert"));
		dbox.DoModal();
	}
}

/****************************************************************************
**
**  ArxDbgEventReactor::abortInsert
**
**  **jma
**
*************************************/

void
ArxDbgEventReactor::abortInsert(AcDbDatabase* pTo)
{
    printReactorMessage(_T("Abort Insert"), pTo);
}

/****************************************************************************
**
**  ArxDbgEventReactor::endInsert
**
**  **jma
**
*************************************/

void
ArxDbgEventReactor::endInsert(AcDbDatabase* pTo)
{
    printReactorMessage(_T("End Insert"), pTo);
}

/****************************************************************************
**
**  ArxDbgEventReactor::wblockNotice
**
**  **jma
**
*************************************/

void
ArxDbgEventReactor::wblockNotice(AcDbDatabase* db)
{
    printReactorMessage(_T("Wblock Notice"), db);
}

/****************************************************************************
**
**  ArxDbgEventReactor::beginWblock
**
**  **jma
**
*************************************/

void
ArxDbgEventReactor::beginWblock(AcDbDatabase* pTo, AcDbDatabase* pFrom, const AcGePoint3d*& insertionPoint)
{
    CString str, str2;
    str.Format(_T("Begin Wblock (1): insert pt = %s"),
                        ArxDbgUtils::ptToStr(*insertionPoint, str2));
    printReactorMessage(str, pTo, pFrom);
}

/****************************************************************************
**
**  ArxDbgEventReactor::beginWblock
**
**  **jma
**
*************************************/

void
ArxDbgEventReactor::beginWblock(AcDbDatabase* pTo, AcDbDatabase* pFrom, AcDbObjectId blockId)
{
    CString str, blkName;

    ArxDbgUtils::symbolIdToName(blockId, blkName);
    str.Format(_T("Begin Wblock (2): blkname = %s"), blkName);
    printReactorMessage(str, pTo, pFrom);
}

/****************************************************************************
**
**  ArxDbgEventReactor::beginWblock
**
**  **jma
**
*************************************/

void
ArxDbgEventReactor::beginWblock(AcDbDatabase* pTo, AcDbDatabase* pFrom)
{
    printReactorMessage(_T("Begin Wblock Entire Database"), pTo, pFrom);
}

/****************************************************************************
**
**  ArxDbgEventReactor::otherWblock
**
**  **jma
**
*************************************/

void
ArxDbgEventReactor::otherWblock(AcDbDatabase* pTo, AcDbIdMapping& idMap, AcDbDatabase* pFrom)
{
    printReactorMessage(_T("Other Wblock"), pTo, pFrom);

	if (m_showDetails) {
		ArxDbgUiTdmIdMap dbox(&idMap, acedGetAcadDwgView(), _T("Other Wblock"));
		dbox.DoModal();
	}
}

/****************************************************************************
**
**  ArxDbgEventReactor::abortWblock
**
**  **jma
**
*************************************/

void
ArxDbgEventReactor::abortWblock(AcDbDatabase* pTo)
{
    printReactorMessage(_T("Abort Wblock"), pTo);
}

/****************************************************************************
**
**  ArxDbgEventReactor::endWblock
**
**  **jma
**
*************************************/

void
ArxDbgEventReactor::endWblock(AcDbDatabase* pTo)
{
    printReactorMessage(_T("End Wblock"), pTo);
}

/****************************************************************************
**
**  ArxDbgEventReactor::beginDeepClone
**
**  **jma
**
*************************************/

void
ArxDbgEventReactor::beginDeepClone(AcDbDatabase* pTo, AcDbIdMapping& idMap)
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
**  ArxDbgEventReactor::beginDeepCloneXlation
**
**  **jma
**
*************************************/

void
ArxDbgEventReactor::beginDeepCloneXlation(AcDbIdMapping& idMap, Acad::ErrorStatus* pRetStatus)
{
    printReactorMessage(_T("Begin Deep Clone Translation"));

	if (m_showDetails) {
		ArxDbgUiTdmIdMap dbox(&idMap, acedGetAcadDwgView(), _T("Begin Deep Clone Xlation"));
		dbox.DoModal();
	}
}

/****************************************************************************
**
**  ArxDbgEventReactor::abortDeepClone
**
**  **jma
**
*************************************/

void
ArxDbgEventReactor::abortDeepClone(AcDbIdMapping& idMap)
{
    printReactorMessage(_T("Abort Deep Clone"));

	if (m_showDetails) {
		ArxDbgUiTdmIdMap dbox(&idMap, acedGetAcadDwgView(), _T("Abort Deep Clone"));
		dbox.DoModal();
	}
}

/****************************************************************************
**
**  ArxDbgEventReactor::endDeepClone
**
**  **jma
**
*************************************/

void
ArxDbgEventReactor::endDeepClone(AcDbIdMapping& idMap)
{
    printReactorMessage(_T("End Deep Clone"));

	if (m_showDetails) {
		ArxDbgUiTdmIdMap dbox(&idMap, acedGetAcadDwgView(), _T("End Deep Clone"));
		dbox.DoModal();
	}
}

/****************************************************************************
**
**  ArxDbgEventReactor::beginWblockObjects
**
**  **jma
**
*************************************/

void
ArxDbgEventReactor::beginWblockObjects(AcDbDatabase* pFrom, AcDbIdMapping& idMap)
{
    printReactorMessage(_T("Begin Wblock Objects"), pFrom);

	if (m_showDetails) {
		ArxDbgUiTdmIdMap dbox(&idMap, acedGetAcadDwgView(), _T("Begin Wblock Objects"));
		dbox.DoModal();
	}
}

/****************************************************************************
**
**  ArxDbgEventReactor::partialOpenNotice
**
**  **jma
**
*************************************/

void
ArxDbgEventReactor::partialOpenNotice(AcDbDatabase* db)
{
    printReactorMessage(_T("Partial Open Notice"), db);
}

/****************************************************************************
**
**  ArxDbgEventReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxDbgEventReactor::printReactorMessage(LPCTSTR event) const
{
    acutPrintf(_T("\n%-15s : [%s] "), _T("[EVENT REACTOR]"), event);
}

/****************************************************************************
**
**  ArxDbgEventReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxDbgEventReactor::printReactorMessage(LPCTSTR event, AcDbDatabase* pDb) const
{
    CString str;

    acutPrintf(_T("\n%-15s : [%s]   (Db = %s)"), _T("[EVENT REACTOR]"), event, ArxDbgUtils::dbToStr(pDb, str));
}

/****************************************************************************
**
**  ArxDbgEventReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxDbgEventReactor::printReactorMessage(LPCTSTR event, AcDbDatabase* pTo, AcDbDatabase* pFrom) const
{
    CString tmpStr1, tmpStr2;
	ArxDbgUtils::dbToStr(pTo, tmpStr1);
	ArxDbgUtils::dbToStr(pFrom, tmpStr2);

    acutPrintf(_T("\n%-15s : [%s]   (To = %s, From = %s)"), _T("[EVENT REACTOR]"), event, tmpStr1, tmpStr2);
}

/****************************************************************************
**
**  ArxDbgEventReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxDbgEventReactor::printReactorMessage(LPCTSTR event, const AcDbObjectId& objId) const
{
    CString str;
    AcDbObject* obj;
    Acad::ErrorStatus es = acdbOpenAcDbObject(obj, objId, AcDb::kForRead);
    if (es == Acad::eOk) {
        acutPrintf(_T("\n%-15s : [%-18s: %s, %s] "), _T("[EVENT REACTOR]"), event,
                ArxDbgUtils::objToClassStr(obj), ArxDbgUtils::objToHandleStr(obj, str));
        obj->close();
    }
    else {
        ArxDbgUtils::rxErrorMsg(es);
        printReactorMessage(event);
    }
}

