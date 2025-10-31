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
// Name:            DbTableIterator.h
//
// Description:     Contains AcDbTableIterator class
//////////////////////////////////////////////////////////////////////////////

#pragma once

struct AcCell;
struct AcCellRange;
class AcDbTable;
class AcDbLinkedTableData;


//*************************************************************************
// AcDbTableIterator
//*************************************************************************

class AcDbTableIterator
{
public:
    AcDbTableIterator(const AcDbTable* pTable);
    AcDbTableIterator(const AcDbTable* pTable, const AcCellRange* pRange,
        AcDb::TableIteratorOption nOption);
    AcDbTableIterator(const AcDbLinkedTableData* pTable);
    AcDbTableIterator(const AcDbLinkedTableData* pTable, const AcCellRange* pRange,
        AcDb::TableIteratorOption nOption);
    AcDbTableIterator(const AcCellRange& range);
    AcDbTableIterator(const AcCellRange& range, AcDb::TableIteratorOption nOption);
    ~AcDbTableIterator();

    void            start                   (void);
    void            step                    (void);
    bool            done                    (void);
    bool            seek                    (const AcCell& cell);
    const AcCell&   getCell                 (void) const;
    int             getRow                  (void) const;
    int             getColumn               (void) const;

protected:
    AcDbTableIterator(void);

protected:
    void        *   mpImpObj;
};
