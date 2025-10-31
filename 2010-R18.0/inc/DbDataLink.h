//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright 2006-2007 by Autodesk, Inc.
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE. AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
// 
//////////////////////////////////////////////////////////////////////////////
// 
// Name:            DbDataLink.h
//
// Description:     Data link classes
//                  Contains the following classes: 
//                      AcDbDataLink
//                      AcDbDataLinkManager
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "AcString.h"


class AcValue;
class AcDbLinkedData;
class AcDbDataLink;
class AcDbDataLinkManager;
class AcDbImpDataLinkManager;
class AcDbDataAdapter;
class AcTableSystemInternals;

// Excel data adapter id
#define ACDB_DATA_ADAPTER_EXCEL         ACRX_T(/*MSG0*/"AcExcel")

//*************************************************************************
// AcDbDataLink
//*************************************************************************

class AcDbDataLink : public AcDbObject
{
public:
    ACDB_DECLARE_MEMBERS(AcDbDataLink);

    ACDB_PORT AcDbDataLink(void);
    ACDB_PORT virtual ~AcDbDataLink(void);

    ACDB_PORT AcString name                 (void) const;
    ACDB_PORT Acad::ErrorStatus setName     (const ACHAR* pszName);
    ACDB_PORT const ACHAR* description      (void) const;
    ACDB_PORT Acad::ErrorStatus setDescription(const ACHAR* pszDescription);
    ACDB_PORT AcString getToolTip           (void) const;
    ACDB_PORT Acad::ErrorStatus setToolTip  (const ACHAR* pszToolTip);
    ACDB_PORT const ACHAR* dataAdapterId    (void) const;
    ACDB_PORT Acad::ErrorStatus setDataAdapterId(const ACHAR* pszAdapterId);
    ACDB_PORT const ACHAR* connectionString (void) const;
    ACDB_PORT Acad::ErrorStatus setConnectionString(const ACHAR* pszConnectionString);
    ACDB_PORT AcDb::DataLinkOption option   (void) const;
    ACDB_PORT Acad::ErrorStatus setOption   (AcDb::DataLinkOption nOption);
    ACDB_PORT int   updateOption            (void) const;
    ACDB_PORT Acad::ErrorStatus setUpdateOption(int nOption);
    ACDB_PORT Acad::ErrorStatus update      (AcDb::UpdateDirection nDir, 
                                             AcDb::UpdateOption nOption);
    ACDB_PORT Acad::ErrorStatus getUpdateStatus(AcDb::UpdateDirection* pDir, 
                                             SYSTEMTIME* pTime, 
                                             AcString* pErrMessage) const;
    ACDB_PORT Acad::ErrorStatus setUpdateStatus(const ACHAR* pszErrMessage);
    ACDB_PORT bool  isValid                 (void) const;
    ACDB_PORT int   getTargets              (AcDbObjectIdArray& targetIds) const;
    ACDB_PORT Acad::ErrorStatus getSourceFiles(AcDb::DataLinkGetSourceContext nContext, 
                                             AcStringArray& files) const;
    ACDB_PORT Acad::ErrorStatus repathSourceFiles(LPCTSTR pszBasePath, 
                                             AcDb::PathOption nOption);
    ACDB_PORT Acad::ErrorStatus getCustomData(const ACHAR* pszKey, 
                                             AcValue* pData) const;
    ACDB_PORT Acad::ErrorStatus setCustomData(const ACHAR* pszKey, 
                                             const AcValue* pData);

    ACDB_PORT virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* pFiler);
    ACDB_PORT virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const;
    ACDB_PORT virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* pFiler);
    ACDB_PORT virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const;
};

typedef AcArray<AcDbDataLink*> AcDbDataLinkArray;


//*************************************************************************
// AcDbDataLinkManager
//*************************************************************************

class AcDbDataLinkManager : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbDataLinkManager);

    ACDB_PORT virtual ~AcDbDataLinkManager(void);

    ACDB_PORT Acad::ErrorStatus createDataLink(const ACHAR* pszAdapterId, 
                                             const ACHAR* pszName, 
                                             const ACHAR* pszDescription, 
                                             const ACHAR* pszConnectionString, 
                                             AcDbObjectId& idDataLink);
    ACDB_PORT Acad::ErrorStatus getDataLink (const ACHAR* pszName, 
                                             AcDbObjectId& idDataLink) const;
    ACDB_PORT Acad::ErrorStatus getDataLink (const ACHAR* pszName, 
                                             AcDbDataLink*& pDataLink, 
                                             AcDb::OpenMode mode) const;
    ACDB_PORT int   dataLinkCount           (void) const;
    ACDB_PORT int   getDataLink             (AcDbObjectIdArray& dataLinks) const;
    ACDB_PORT Acad::ErrorStatus addDataLink (AcDbDataLink* pDataLink);
    ACDB_PORT Acad::ErrorStatus addDataLink (AcDbDataLink* pDataLink, 
                                             AcDbObjectId& idDataLink);
    Acad::ErrorStatus removeDataLink        (const ACHAR* pszKey, 
                                             AcDbObjectId& idDataLink);
    ACDB_PORT Acad::ErrorStatus removeDataLink(const AcDbObjectId& idDataLink);

    ACDB_PORT Acad::ErrorStatus update      (const AcDbObjectIdArray& dataIds, 
                                             AcDb::UpdateDirection nDir,
                                             AcDb::UpdateOption nOption);
    ACDB_PORT Acad::ErrorStatus update      (AcDb::UpdateDirection nDir, 
                                             AcDb::UpdateOption nOption);

protected:
    ACDB_PORT AcDbDataLinkManager(void);

private:
    void        *   mpImpObj;
    friend AcTableSystemInternals;
    friend AcDbImpDataLinkManager;
};
