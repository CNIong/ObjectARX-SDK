#ifndef AD_DBDIMDATA_H
#define AD_DBDIMDATA_H
//
// (C) Copyright 2002 by Autodesk, Inc.
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

#include "acdb.h"
#include "acarray.h"
#include "dbdim.h"

class AcDbDimData;

typedef AcArray<AcDbDimData> AcDbDimDataArray;
typedef AcArray<AcDbDimData*> AcDbDimDataPtrArray;
typedef AcGeVector3d (*DimDataSetValueFuncPtr) (AcDbDimData* pThis,
                                        AcDbEntity* pEnt, 
                                        double newValue,
                                        const AcGeVector3d& offset);

class AcDbDimData
{
public:
    enum DimDataFlags {
        kDimEditable           = 0x1,
        kDimInvisible          = 0x2,
        kDimFocal              = 0x4,
        kDimHideIfValueIsZero  = 0x8
    };

    AcDbDimData();
    AcDbDimData(AcDbDimension* pDim, 
                DimDataSetValueFuncPtr setDimFunc = NULL,
                unsigned int bitFlags = 0,
                void* appData = NULL);

    ~AcDbDimData();

    AcDbDimData(const AcDbDimData&);
    AcDbDimData&  operator = (const AcDbDimData&);
    AcDbDimension* dimension() const;
    Acad::ErrorStatus setDimension(AcDbDimension* pDim);
    AcDbObjectId ownerId() const;
    Acad::ErrorStatus setOwnerId(const AcDbObjectId& objId);
    unsigned int bitFlags() const;
    Acad::ErrorStatus setBitFlags(unsigned int flags);
    bool isDimFocal() const;
    Acad::ErrorStatus setDimFocal(bool focal);
    bool isDimEditable() const;
    Acad::ErrorStatus setDimEditable(bool editable);
    bool isDimInvisible() const;
    Acad::ErrorStatus setDimInvisible(bool invisible);
    bool isDimHideIfValueIsZero() const;
    Acad::ErrorStatus setDimHideIfValueIsZero(bool hide);
    void *appData() const;
    Acad::ErrorStatus setAppData(void* appData);
    DimDataSetValueFuncPtr dimValueFunc() const;
    Acad::ErrorStatus setDimValueFunc(DimDataSetValueFuncPtr funcPtr);

private:
    AcDbDimension*      mpDim;
    AcDbObjectId        mOwnerId;
    unsigned int        mBitFlags;
    void*               mpAppData;
    DimDataSetValueFuncPtr  mpSetDimValueFunc;
};

inline AcDbDimData::AcDbDimData() : 
    mpDim(NULL), 
    mBitFlags(0),
    mpSetDimValueFunc(NULL),
    mpAppData (NULL)
{
}

inline AcDbDimData::AcDbDimData(AcDbDimension* pDim, 
                   DimDataSetValueFuncPtr setValueFunc,
                   unsigned int bitFlags,
                   void* appData) :
    mpDim(pDim),
    mpSetDimValueFunc(setValueFunc),
    mBitFlags(bitFlags),
    mpAppData(appData)
{
}

inline AcDbDimData::AcDbDimData(const AcDbDimData& src)
{
    *this = src;
}

inline AcDbDimData::~AcDbDimData()
{
    if (mpDim) 
        delete mpDim;
}

inline AcDbDimData& AcDbDimData::operator = (const AcDbDimData& src)
{
    if (this == &src)
        return *this;

    mpDim = (AcDbDimension*)src.dimension()->clone();
    mOwnerId = src.ownerId();
    mpSetDimValueFunc = src.dimValueFunc();
    mBitFlags = src.bitFlags();
    mpAppData = src.appData();
    return *this;
}

inline AcDbDimension*
AcDbDimData::dimension() const
{
    return mpDim;
}

inline Acad::ErrorStatus
AcDbDimData::setDimension(AcDbDimension* pDim)
{
    mpDim = pDim;
    return Acad::eOk;
}

inline AcDbObjectId
AcDbDimData::ownerId() const
{
    return mOwnerId;
}

inline Acad::ErrorStatus
AcDbDimData::setOwnerId(const AcDbObjectId& objId)
{
    mOwnerId = objId;
    return Acad::eOk;
}

inline unsigned int 
AcDbDimData::bitFlags() const
{
    return mBitFlags;
}

inline Acad::ErrorStatus
AcDbDimData::setBitFlags(unsigned int flags)
{
    mBitFlags = flags;
    return Acad::eOk;
}

inline bool
AcDbDimData::isDimFocal() const
{
    return !!(mBitFlags & kDimFocal);
}

inline Acad::ErrorStatus
AcDbDimData::setDimFocal(bool focal)
{
    if (focal)
        mBitFlags |= kDimFocal;
    else
        mBitFlags &= ~kDimFocal;
    return Acad::eOk;
}

inline bool
AcDbDimData::isDimEditable() const
{
    return !!(mBitFlags & kDimEditable);
}

inline Acad::ErrorStatus
AcDbDimData::setDimEditable(bool editable)
{
    if (editable)
        mBitFlags |= kDimEditable;
    else
        mBitFlags &= ~kDimEditable;
    return Acad::eOk;
}

inline bool
AcDbDimData::isDimInvisible() const
{
    return !!(mBitFlags & kDimInvisible);
}

inline Acad::ErrorStatus
AcDbDimData::setDimInvisible(bool invisible)
{
    if (invisible)
        mBitFlags |= kDimInvisible;
    else
        mBitFlags &= ~kDimInvisible;
    return Acad::eOk;
}

inline bool
AcDbDimData::isDimHideIfValueIsZero() const
{
    return !!(mBitFlags & kDimHideIfValueIsZero);
}

inline Acad::ErrorStatus
AcDbDimData::setDimHideIfValueIsZero(bool hide)
{
    if (hide)
        mBitFlags |= kDimHideIfValueIsZero;
    else
        mBitFlags &= ~kDimHideIfValueIsZero;
    return Acad::eOk;
}

inline void*
AcDbDimData::appData() const
{
    return mpAppData;
}

inline Acad::ErrorStatus
AcDbDimData::setAppData(void* appData)
{
    mpAppData = appData;
    return Acad::eOk;
}

inline DimDataSetValueFuncPtr
AcDbDimData::dimValueFunc() const
{
    return mpSetDimValueFunc;
}

inline Acad::ErrorStatus
AcDbDimData::setDimValueFunc(DimDataSetValueFuncPtr funcPtr)
{
    mpSetDimValueFunc = funcPtr;
    return Acad::eOk;
}

#endif // AD_DBDIMDATA_H



