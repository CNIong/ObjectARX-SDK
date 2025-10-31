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
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
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
// Name:            DbTableContent.h
//
// Description:     Contains the following classes: 
//                      AcDbTableContent
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "DbFormattedTableData.h"


//*************************************************************************
// AcDbTableContent
//*************************************************************************

class AcDbTableContent : public AcDbFormattedTableData
{
public:
    ACDB_DECLARE_MEMBERS(AcDbTableContent);

    ACDB_PORT AcDbTableContent(void);
    ACDB_PORT virtual ~AcDbTableContent(void);

    ACDB_PORT virtual AcDbObjectId tableStyleId(void) const;
    ACDB_PORT virtual Acad::ErrorStatus setTableStyleId(const AcDbObjectId& idTableStyle);
    ACDB_PORT virtual const ACHAR* cellStyle(int nRow, 
                                             int nCol) const;
    ACDB_PORT virtual Acad::ErrorStatus setCellStyle(int nRow, 
                                             int nCol, 
                                             const ACHAR* pszCellStyle);
    ACDB_PORT virtual double rowHeight      (int nRow) const;
    ACDB_PORT virtual Acad::ErrorStatus setRowHeight(int nRow, 
                                             double fWidth);
    ACDB_PORT virtual double columnWidth    (int nCol) const;
    ACDB_PORT virtual Acad::ErrorStatus setColumnWidth(int nCol, 
                                             double fWidth);

    ACDB_PORT virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* pFiler);
    ACDB_PORT virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const;
    ACDB_PORT virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* pFiler);
    ACDB_PORT virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const;
};
