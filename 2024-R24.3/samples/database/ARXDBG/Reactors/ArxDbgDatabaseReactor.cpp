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

#include "ArxDbgDatabaseReactor.h"
#include "ArxDbgUtils.h"
#include "ArxDbgUiTdmObjects.h"



ACRX_NO_CONS_DEFINE_MEMBERS(ArxDbgDatabaseReactor, AcDbDatabaseReactor);

/****************************************************************************
**
**  ArxDbgDatabaseReactor::ArxDbgDatabaseReactor
**
**  **jma
**
*************************************/

ArxDbgDatabaseReactor::ArxDbgDatabaseReactor()
{
}

/****************************************************************************
**
**  ArxDbgDatabaseReactor::~ArxDbgDatabaseReactor
**
**  **jma
**
*************************************/

ArxDbgDatabaseReactor::~ArxDbgDatabaseReactor()
{
}

/****************************************************************************
**
**  ArxDbgDatabaseReactor::showDetails
**
**  **jma
**
*************************************/

bool
ArxDbgDatabaseReactor::showDetails() const
{
	return m_showDetails;
}

/****************************************************************************
**
**  ArxDbgDatabaseReactor::setShowDetails
**
**  **jma
**
*************************************/

void
ArxDbgDatabaseReactor::setShowDetails(bool showThem)
{
	m_showDetails = showThem;
}

/****************************************************************************
**
**  ArxDbgDatabaseReactor::objectAppended
**
**  **jma
**
*************************************/

void
ArxDbgDatabaseReactor::objectAppended(const AcDbDatabase* db, const AcDbObject* obj)
{
    printReactorMessage(db, _T("Appended"), obj);
}

/****************************************************************************
**
**  ArxDbgDatabaseReactor::objectUnAppended
**
**  **jma
**
*************************************/

void
ArxDbgDatabaseReactor::objectUnAppended(const AcDbDatabase* db, const AcDbObject* obj)
{
    printReactorMessage(db, _T("Un-Appended"), obj);
}

/****************************************************************************
**
**  ArxDbgDatabaseReactor::objectReAppended
**
**  **jma
**
*************************************/

void
ArxDbgDatabaseReactor::objectReAppended(const AcDbDatabase* db, const AcDbObject* obj)
{
    printReactorMessage(db, _T("Re-Appended"), obj);
}

/****************************************************************************
**
**  ArxDbgDatabaseReactor::objectOpenedForModify
**
**  **jma
**
*************************************/

void
ArxDbgDatabaseReactor::objectOpenedForModify(const AcDbDatabase* db, const AcDbObject* obj)
{
    printReactorMessage(db, _T("Opened For Modify"), obj);
}

/****************************************************************************
**
**  ArxDbgDatabaseReactor::objectModified
**
**  **jma
**
*************************************/

void
ArxDbgDatabaseReactor::objectModified(const AcDbDatabase* db, const AcDbObject* obj)
{
    printReactorMessage(db, _T("Modified"), obj);
}

/****************************************************************************
**
**  ArxDbgDatabaseReactor::objectErased
**
**  **jma
**
*************************************/

void
ArxDbgDatabaseReactor::objectErased(const AcDbDatabase* db, const AcDbObject* obj,
                            Adesk::Boolean erased)
{
    if (erased)
        printReactorMessage(db, _T("Erased"), obj);
    else
        printReactorMessage(db, _T("Un-erased"), obj);
}

/****************************************************************************
**
**  ArxDbgDatabaseReactor::headerSysVarWillChange
**
**  **jma
**
*************************************/

void
ArxDbgDatabaseReactor::headerSysVarWillChange(const AcDbDatabase* db, const TCHAR* name)
{
    printReactorMessage(db, _T("SysVar Will Change"), name);
}

/****************************************************************************
**
**  ArxDbgDatabaseReactor::headerSysVarChanged
**
**  **jma
**
*************************************/

void
ArxDbgDatabaseReactor::headerSysVarChanged(const AcDbDatabase* db, const TCHAR* name,
                                        Adesk::Boolean bSuccess)
{
    printReactorMessage(db, _T("SysVar Changed"), name);
    if (bSuccess != Adesk::kTrue)
        acutPrintf(_T("\n*** SYSVAR NOT CHANGED SUCCESSFULLY!!! ***"));
}

/****************************************************************************
**
**  ArxDbgDatabaseReactor::proxyResurrectionCompleted
**
**  **jma
**
*************************************/

void
ArxDbgDatabaseReactor::proxyResurrectionCompleted(const AcDbDatabase* db,
										const TCHAR* appname, AcDbObjectIdArray& objects)
{
	printReactorMessage(db, _T("Proxy Resurrection Completed"), appname);

	if (m_showDetails) {
		CString str;
		str.Format(_T("Resurrected Proxies: %s"), appname);
		ArxDbgUiTdmObjects dbox(objects, acedGetAcadDwgView(), str);
		dbox.DoModal();
	}
}

/****************************************************************************
**
**  ArxDbgDatabaseReactor::goodbye
**
**  **jma
**
*************************************/

void
ArxDbgDatabaseReactor::goodbye(const AcDbDatabase* db)
{
	printReactorMessage(db, _T("Goodbye"));
}

/****************************************************************************
**
**  ArxDbgDatabaseReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxDbgDatabaseReactor::printReactorMessage(const AcDbDatabase* db, LPCTSTR event, const AcDbObject* obj) const
{
    CString str, str2;
    ArxDbgUtils::objToHandleStr(obj, str);
    str2.Format(_T("<DB REACTOR: %p>"), db);
    
    acutPrintf(_T("\n%-15s : <%-18s: %s, %s> "), str2, event,
                        ArxDbgUtils::objToClassStr(obj), str);
}

/****************************************************************************
**
**  ArxDbgDatabaseReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxDbgDatabaseReactor::printReactorMessage(const AcDbDatabase* db, LPCTSTR event, const LPCTSTR str) const
{
    CString str2;
    str2.Format(_T("<DB REACTOR: %p>"), db);

    acutPrintf(_T("\n%-15s : <%-18s: %s> "), str2, event, str);
}

/****************************************************************************
**
**  ArxDbgDatabaseReactor::printReactorMessage
**
**  **jma
**
*************************************/

void
ArxDbgDatabaseReactor::printReactorMessage(const AcDbDatabase* db, LPCTSTR event) const
{
    CString str2;
    str2.Format(_T("<DB REACTOR: %p>"), db);

    acutPrintf(_T("\n%-15s : <%-18s> "), str2, event);
}


