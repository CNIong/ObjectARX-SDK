//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright 2005-2009 by Autodesk, Inc.
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
// Name:            DbSectionManager.h
//
// Description:     Header for AcDbSectionManager and 
//                  AcDbSectionManagerIterator classes.
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "AdAChar.h"
#include "DbSection.h"


class AcDbSection;
class AcDbSectionManagerIterator;
class AcDbImpSectionManager;


//*************************************************************************
// AcDbSectionManager
//*************************************************************************

class AcDbSectionManager : public AcDbObject
{
public:
    ACDB_DECLARE_MEMBERS(AcDbSectionManager);

    ACDB_PORT Acad::ErrorStatus getSection  (const ACHAR* pszName, 
                                             AcDbObjectId& id) const;
    ACDB_PORT Acad::ErrorStatus getSection  (const ACHAR* pszName, 
                                             AcDbSection*& pSecPlane, 
                                             AcDb::OpenMode mode) const;
    ACDB_PORT Acad::ErrorStatus getLiveSection(AcDbObjectId& id) const;
    ACDB_PORT Acad::ErrorStatus getLiveSection(AcDbSection*& pSecPlane,
                                             AcDb::OpenMode mode) const;
    ACDB_PORT int   numSections             (void) const;
    ACDB_PORT Acad::ErrorStatus newIterator (AcDbSectionManagerIterator*& pIterator) const;
    ACDB_PORT Acad::ErrorStatus getUniqueSectionName(const ACHAR* pszBaseName, 
                                             ACHAR*& pszUniqueName) const;

    // Base class overrides
    ACDB_PORT virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler* pFiler);
    ACDB_PORT virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const;
    ACDB_PORT virtual Acad::ErrorStatus dxfInFields (AcDbDxfFiler* pFiler);
    ACDB_PORT virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const;

public:
    // TODO: These should be protected
    ACDB_PORT AcDbSectionManager(void);
    ACDB_PORT ~AcDbSectionManager(void);

protected:
    ACDB_PORT virtual Acad::ErrorStatus subGetClassID  (CLSID* pClsid) const;
};


//*************************************************************************
// AcDbSectionManagerIterator
//*************************************************************************

class AcDbSectionManagerIterator
{
public:
    ACDB_PORT virtual ~AcDbSectionManagerIterator(void);

    ACDB_PORT void  start                   (void);
    ACDB_PORT void  step                    (void);
    ACDB_PORT bool  done                    (void) const;

    ACDB_PORT AcDbObjectId      getSection  (void) const;
    ACDB_PORT Acad::ErrorStatus getSection  (AcDbSection*& pSecPlane, 
                                             AcDb::OpenMode openMode) const;

protected:
    ACDB_PORT AcDbSectionManagerIterator(AcDbSectionManager* pMgr);

protected:
    void            *   mpImpObj;

    friend AcDbImpSectionManager;
};
