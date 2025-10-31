#ifndef AD_DBSPINDX_H
#define AD_DBSPINDX_H
//
// (C) Copyright 1993-1999 by Autodesk, Inc.
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
// Concrete implementation for 3d spatial indexing.
//
#include "dbindex.h"

#pragma pack (push, 8)

class AcDbSpatialIndex: public AcDbIndex
{
public:
    ACDB_DECLARE_MEMBERS(AcDbSpatialIndex);
	     AcDbSpatialIndex();
    virtual ~AcDbSpatialIndex();

    virtual AcDbFilteredBlockIterator* newIterator(const AcDbFilter* pFilter)
                                                   const;

    virtual Acad::ErrorStatus rebuildFull(AcDbIndexUpdateData* pIdxData);

protected:
    virtual Acad::ErrorStatus rebuildModified(AcDbBlockChangeIterator* iter);
};

class AcDbImpSpatialIndexIterator;
class AcDbSpatialFilter;

class AcDbSpatialIndexIterator : public AcDbFilteredBlockIterator
{
public:
	AcDbSpatialIndexIterator(const AcDbSpatialIndex*  pIndex,
                                 const AcDbSpatialFilter* pFilter);
        virtual ~AcDbSpatialIndexIterator();

	virtual Acad::ErrorStatus start();
	virtual AcDbObjectId      next();
	virtual AcDbObjectId      id() const;
	virtual Acad::ErrorStatus seek(AcDbObjectId id);

        virtual double estimatedHitFraction() const;
        virtual Acad::ErrorStatus accepts(AcDbObjectId id,
                                    Adesk::Boolean& stat) const;

private:
        AcDbImpSpatialIndexIterator* mpImpIter;
};


#pragma pack (pop)

#endif // AD_DBSPINDX_H
