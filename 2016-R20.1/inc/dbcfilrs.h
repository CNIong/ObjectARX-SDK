//
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
//
// DESCRIPTION:
//
// This file contains "filer" class definitions of AcDbDeepCloneFiler
// and AcDbWblockCloneFiler.  These filers maintain a queue of typed
// object id's. All read/write requests are forwarded to a contained 
// "real" filer, except for object id's which are removed/added from/to 
// the queue.  The classes provide protocol for writing either "owned"
// or "hard" objects in the queue.

#ifndef AD_DBCFILERS_H
#define AD_DBCFILERS_H 1

#include "dbfiler.h"
#pragma pack (push, 8)

class AcDbWblockCloneFiler;
class AcDbImpDeepCloneFiler;

class AcDbDeepCloneFiler: public AcDbDwgFiler
{
    friend class AcDbSystemInternals;
public:
    ACRX_DECLARE_MEMBERS(AcDbDeepCloneFiler);
    AcDbDeepCloneFiler();
    virtual ~AcDbDeepCloneFiler();

    // overridden from AcDbDwgFiler 
    //
    virtual Acad::ErrorStatus filerStatus() const;
    virtual AcDb::FilerType   filerType() const;
    virtual void              setFilerStatus(Acad::ErrorStatus);
    virtual void              resetFilerStatus();

    virtual Acad::ErrorStatus readHardOwnershipId(AcDbHardOwnershipId*);
    virtual Acad::ErrorStatus writeHardOwnershipId(const AcDbHardOwnershipId&);

    virtual Acad::ErrorStatus readSoftOwnershipId(AcDbSoftOwnershipId*);
    virtual Acad::ErrorStatus writeSoftOwnershipId(const AcDbSoftOwnershipId&);

    virtual Acad::ErrorStatus readHardPointerId(AcDbHardPointerId*);
    virtual Acad::ErrorStatus writeHardPointerId(const AcDbHardPointerId&);

    virtual Acad::ErrorStatus readSoftPointerId(AcDbSoftPointerId*);
    virtual Acad::ErrorStatus writeSoftPointerId(const AcDbSoftPointerId&);

    virtual Acad::ErrorStatus readInt8(Adesk::Int8 *);
    virtual Acad::ErrorStatus writeInt8(Adesk::Int8);

    // This flavor of readString may go away in a future release.
    virtual Acad::ErrorStatus readString(ACHAR **);
    virtual Acad::ErrorStatus writeString(const ACHAR *);

    virtual Acad::ErrorStatus readString(AcString &);
    virtual Acad::ErrorStatus writeString(const AcString &);

    virtual Acad::ErrorStatus readBChunk(ads_binary*);
    virtual Acad::ErrorStatus writeBChunk(const ads_binary&);

    virtual Acad::ErrorStatus readAcDbHandle(AcDbHandle*);
    virtual Acad::ErrorStatus writeAcDbHandle(const AcDbHandle&);

    virtual Acad::ErrorStatus readInt64(Adesk::Int64*);
    virtual Acad::ErrorStatus writeInt64(Adesk::Int64);

    virtual Acad::ErrorStatus readInt32(Adesk::Int32*);
    virtual Acad::ErrorStatus writeInt32(Adesk::Int32);

    virtual Acad::ErrorStatus readInt16(Adesk::Int16*);
    virtual Acad::ErrorStatus writeInt16(Adesk::Int16);

    virtual Acad::ErrorStatus readUInt64(Adesk::UInt64*);
    virtual Acad::ErrorStatus writeUInt64(Adesk::UInt64);

    virtual Acad::ErrorStatus readUInt32(Adesk::UInt32*);
    virtual Acad::ErrorStatus writeUInt32(Adesk::UInt32);

    virtual Acad::ErrorStatus readUInt16(Adesk::UInt16*);
    virtual Acad::ErrorStatus writeUInt16(Adesk::UInt16);

    virtual Acad::ErrorStatus readUInt8(Adesk::UInt8*);
    virtual Acad::ErrorStatus writeUInt8(Adesk::UInt8);

    virtual Acad::ErrorStatus readBoolean(Adesk::Boolean*);
    virtual Acad::ErrorStatus writeBoolean(Adesk::Boolean);

    virtual Acad::ErrorStatus readBool(bool*);
    virtual Acad::ErrorStatus writeBool(bool);

    virtual Acad::ErrorStatus readDouble(double*);
    virtual Acad::ErrorStatus writeDouble(double);

    virtual Acad::ErrorStatus readPoint2d(AcGePoint2d*);
    virtual Acad::ErrorStatus writePoint2d(const AcGePoint2d&);

    virtual Acad::ErrorStatus readPoint3d(AcGePoint3d*);
    virtual Acad::ErrorStatus writePoint3d(const AcGePoint3d&);

    virtual Acad::ErrorStatus readVector2d(AcGeVector2d*);
    virtual Acad::ErrorStatus writeVector2d(const AcGeVector2d&);

    virtual Acad::ErrorStatus readVector3d(AcGeVector3d*);
    virtual Acad::ErrorStatus writeVector3d(const AcGeVector3d&);

    virtual Acad::ErrorStatus readScale3d(AcGeScale3d*);
    virtual Acad::ErrorStatus writeScale3d(const AcGeScale3d&);

    virtual Acad::ErrorStatus readBytes(void*, Adesk::UIntPtr);
    virtual Acad::ErrorStatus writeBytes(const void*, Adesk::UIntPtr);

    virtual Acad::ErrorStatus readAddress(void **);
    virtual Acad::ErrorStatus writeAddress(const void *);

    virtual Acad::ErrorStatus seek(Adesk::Int64 nOffset, int nMethod);
    virtual Adesk::Int64      tell() const;

    virtual Acad::ErrorStatus addReferences(AcDbIdRefQueue&);
    virtual              bool usesReferences() const;
    virtual AcDbFilerController& controller() const;

    // Protocol specific to AcDbDeepCloneFiler
    //
    virtual bool              getNextOwnedObject(AcDbObjectId& id);
    virtual bool              moreOwnedObjects() const;

protected:
    AcDbDeepCloneFiler(AcDbSystemInternals*);
private:
    AcDbImpDeepCloneFiler*      mpImpFiler;
};

class AcDbWblockCloneFiler: public  AcDbDeepCloneFiler
{
    friend class AcDbSystemInternals;
public:
    ACRX_DECLARE_MEMBERS(AcDbWblockCloneFiler);

    AcDbWblockCloneFiler();

    virtual Acad::ErrorStatus addReferences(AcDbIdRefQueue&);
    virtual              bool usesReferences() const;

    virtual bool              getNextHardObject(AcDbObjectId& id);
    virtual bool              moreHardObjects() const;

    virtual AcDb::FilerType   filerType() const;
};

#pragma pack (pop)
#endif
