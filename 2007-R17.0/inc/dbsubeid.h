#ifndef GEOMENT_DBSUBEID_H
#define GEOMENT_DBSUBEID_H
//
// (C) Copyright 1993-2006 by Autodesk, Inc.
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

#include "acdb.h"
#include "dbidar.h"

#pragma pack (push, 8)

class AcDbSubentId
{
public:
    AcDbSubentId();
    AcDbSubentId(AcDb::SubentType type, int index);
    AcDbSubentId(AcRxClass* pTypeClass, int index);

    bool               operator ==(const AcDbSubentId& id) const;
    bool               operator !=(const AcDbSubentId& id) const;

    AcDb::SubentType   type () const;
    void               setType(AcDb::SubentType);
    AcRxClass*         typeClass () const;
    void               setTypeClass(AcRxClass* pClass);
    int                index() const;
    void               setIndex(int);
    
private:
    AcDb::SubentType mType;
    int              mIndex;
    AcRxClass*       mpTypeClass;
};

extern const AcDbSubentId kNullSubentId;

const int kNullSubentIndex = 0;

class AcDbFullSubentPath
{
public:
    AcDbFullSubentPath();
    AcDbFullSubentPath(AcDb::SubentType type, int index);
    AcDbFullSubentPath(AcDbObjectId entId, AcDb::SubentType type, int index);
    AcDbFullSubentPath(AcDbObjectId entId, AcDbSubentId subId);
    AcDbFullSubentPath(AcDbObjectIdArray objectIds, AcDbSubentId subId);
    AcDbFullSubentPath(const AcDbFullSubentPath&);
    ~AcDbFullSubentPath();

    AcDbFullSubentPath&     operator =  (const AcDbFullSubentPath&);


    bool           operator ==(const AcDbFullSubentPath& id) const;
    bool           operator !=(const AcDbFullSubentPath& id) const;

    void                objectIds(AcDbObjectIdArray& objectIds) const;
    AcDbObjectIdArray&  objectIds();
    const AcDbObjectIdArray&  objectIds() const;
    const AcDbSubentId  subentId () const;
    AcDbSubentId&       subentId ();
    
private:                            
    AcDbObjectIdArray mObjectIds;
    AcDbSubentId      mSubentId;
};

// inlines

inline AcDb::SubentType
AcDbSubentId::type () const
{
    return mType;
}

inline void
AcDbSubentId::setType(AcDb::SubentType type)
{
    mType = type;
    if (mType != AcDb::kClassSubentType)
        mpTypeClass = NULL;
}

inline int
AcDbSubentId::index() const
{
    return mIndex;
}

inline void  
AcDbSubentId::setIndex(int index)
{
    mIndex = index;
}

inline AcRxClass* 
AcDbSubentId::typeClass() const
{
    return mpTypeClass;
}

inline void
AcDbSubentId::setTypeClass(AcRxClass* pTypeClass)
{
    mpTypeClass = pTypeClass;
    if (mpTypeClass != NULL)
        mType = AcDb::kClassSubentType;
}

inline
AcDbSubentId::AcDbSubentId() 
    : mType(AcDb::kNullSubentType), mIndex(kNullSubentIndex), mpTypeClass(NULL)
{
}

inline
AcDbSubentId::AcDbSubentId(AcDb::SubentType t, int i) 
    : mType(t), mIndex(i), mpTypeClass(NULL)
{
}

inline
AcDbSubentId::AcDbSubentId(AcRxClass* pTypeClass, int i) 
    : mType(AcDb::kClassSubentType), mIndex(i), mpTypeClass(pTypeClass)
{
}

inline bool
AcDbSubentId::operator ==(const AcDbSubentId& id) const
{
    return ((mIndex == id.mIndex) 
            && (mType == id.mType) 
            && (mpTypeClass == id.mpTypeClass));
}


inline bool
AcDbSubentId::operator !=(const AcDbSubentId& id) const
{
    return ((mIndex != id.mIndex) 
            || (mType != id.mType)
            || (mpTypeClass != id.mpTypeClass));
}

inline
AcDbFullSubentPath::AcDbFullSubentPath() 
{
}

inline
AcDbFullSubentPath::AcDbFullSubentPath(AcDb::SubentType type, int index)
    : mSubentId(type, index)
{
}

inline void
AcDbFullSubentPath::objectIds(AcDbObjectIdArray& objectIds) const
{
    objectIds = mObjectIds;
}

inline AcDbObjectIdArray&
AcDbFullSubentPath::objectIds()
{
    return mObjectIds;
}

inline const AcDbObjectIdArray&
AcDbFullSubentPath::objectIds() const
{
    return mObjectIds;
}

inline const AcDbSubentId
AcDbFullSubentPath::subentId () const
{
    return mSubentId;
}

inline AcDbSubentId&
AcDbFullSubentPath::subentId ()
{
    return mSubentId;
}

#pragma pack (pop)

#endif

