//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright 2006-2007  by Autodesk, Inc.
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
// Name:            DbLinkedData.h
//
// Description:     Data classes
//                  Contains the following classes: 
//                      AcDbLinkedData
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "AcValue.h"
#include "DbDataLink.h"


//*************************************************************************
// AcDbLinkedData
//*************************************************************************

class AcDbLinkedData : public AcDbObject
{
public:
    ACDB_DECLARE_MEMBERS(AcDbLinkedData);

    ACDB_PORT AcDbLinkedData(void);
    ACDB_PORT virtual ~AcDbLinkedData(void);

    ACDB_PORT virtual Acad::ErrorStatus clear(void);
    ACDB_PORT virtual bool isEmpty          (void) const;

    ACDB_PORT virtual const ACHAR* name     (void) const;
    ACDB_PORT virtual Acad::ErrorStatus setName(const ACHAR* pszName);
    ACDB_PORT virtual const ACHAR* description(void) const;
    ACDB_PORT virtual Acad::ErrorStatus setDescription(const ACHAR* pszDescription);

    ACDB_PORT virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* pFiler);
    ACDB_PORT virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const;
    ACDB_PORT virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* pFiler);
    ACDB_PORT virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const;
};

typedef AcArray<AcDbLinkedData*> AcDbDataArray;
