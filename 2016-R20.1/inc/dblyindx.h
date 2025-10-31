//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2015 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
// AcDbIndex is the base class for all index implementations.
//
// These indexes are associated with Block Spaces, and can be used
// to perform an efficient filtered traversal of the block.
//

#ifndef AD_DBLYINDX_H
#define AD_DBLYINDX_H

#include "dbindex.h"

#pragma pack (push, 8)

class AcDbLayerIndex: public AcDbIndex
{
public:
    ACDB_DECLARE_MEMBERS(AcDbLayerIndex);
	     AcDbLayerIndex();
    virtual ~AcDbLayerIndex();
    virtual AcDbFilteredBlockIterator* newIterator(const AcDbFilter* pFilter)
                                                   const;

    virtual Acad::ErrorStatus rebuildFull(AcDbIndexUpdateData* pIdxData);

    Acad::ErrorStatus compute(AcDbLayerTable*       pLT,
                              AcDbBlockTableRecord* pBTR);

protected:
    virtual Acad::ErrorStatus rebuildModified(AcDbBlockChangeIterator* iter);
};

class AcDbImpLayerIndexIterator;
class AcDbLayerFilter;

class AcDbLayerIndexIterator : public AcDbFilteredBlockIterator
{
public:
    AcDbLayerIndexIterator(const AcDbLayerIndex*  pIndex,
                           const AcDbLayerFilter* pFilter);
    virtual ~AcDbLayerIndexIterator();

    virtual Acad::ErrorStatus start();
    virtual AcDbObjectId      next();
    virtual AcDbObjectId      id() const;
    virtual Acad::ErrorStatus seek(AcDbObjectId id);

    virtual double estimatedHitFraction() const;
    virtual Acad::ErrorStatus accepts(AcDbObjectId id, 
                      Adesk::Boolean& idPassesFilter) const;

private:
        AcDbImpLayerIndexIterator* mpImpIter;
};


#pragma pack (pop)

#endif // AD_DBLYINDX_H
