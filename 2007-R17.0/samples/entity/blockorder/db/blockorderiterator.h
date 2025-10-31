//
// (C) Copyright 1998-1999 by Autodesk, Inc. 
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
#if !defined(_BLOCKORDERITERATOR_H)
#define _BLOCKORDERITERATOR_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "dbindex.h"
#include "blockOrderFilter.h"

class AsdkBlockOrderIterator : public AcDbFilteredBlockIterator
{
    const AsdkBlockOrderFilter* mpFilter;
    AcDbObjectId midBTR;
    AcDbObjectIdArray mIds,mBuffer;
    int mPos;
    bool mbMain;
public:
    AsdkBlockOrderIterator(const AsdkBlockOrderFilter* pFilter,const AcDbObjectId& idBTR);
    virtual ~AsdkBlockOrderIterator();

    virtual Acad::ErrorStatus start();
    virtual AcDbObjectId      next();
    virtual AcDbObjectId      id() const;
    virtual Acad::ErrorStatus seek(AcDbObjectId id);

    virtual double estimatedHitFraction() const;
    virtual Acad::ErrorStatus accepts(AcDbObjectId id, 
                      Adesk::Boolean& idPassesFilter) const;

    virtual Adesk::Boolean    buffersForComposition() const;
    virtual Acad::ErrorStatus addToBuffer(AcDbObjectId id);
};

#endif //_BLOCKORDERITERATOR_H