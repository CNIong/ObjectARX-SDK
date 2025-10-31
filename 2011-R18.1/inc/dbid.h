//
// (C) Copyright 1993-2009 by Autodesk, Inc. 
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
//
// DESCRIPTION:
//
// This file contains lightweight id classes distinguishing between
// different types of object id's. A distinction is made between an
// owned object and a reference or "pointer to" an object, as well as
// whether the relationship protects the object from purge (hard/soft).
//
// Hard-owner:  
//
// An owned object protected from purge. A layer symbol table and
// layer 0 is an example of a hard-owner relationship.
//
// Soft-owner:
//
// An owned object not protected from purge. All symbol tables own
// their records, but that relationship does not usually protect
// the records from purge.
//
// Hard-pointer:
//
// A reference to an object that is not owned, but protected from
// purge. An entity, for example, does not own the layer it is on
// but its reference to it protects it from purge.
//
// Soft-pointer:
//
// A reference to an object that is not owned, and not protected
// from purge. 

#ifndef _AD_DBID_H
#define _AD_DBID_H 1

#include "adesk.h"
#include "dbhandle.h"

#pragma pack(push, 8)

class AcDbDatabase;
class AcDbStub;
class AcRxClass;

class AcDbObjectId 
{
public:
    AcDbObjectId();
    AcDbObjectId(const AcDbStub*);

    static const   AcDbObjectId  kNull;

    bool           isNull() const;
    void           setNull();

    Adesk::IntDbId     asOldId     () const;
    AcDbObjectId&  setFromOldId(Adesk::IntDbId oldId);
#ifdef _WIN64
  private:
    // catch attempts to set it from a 32-bit long
    AcDbObjectId&  setFromOldId(long);

  public:
    // need this overload to allow passing of unsigned 64-bit
    inline AcDbObjectId&  setFromOldId(Adesk::UIntPtr nUnsignedId)
    {
        const Adesk::IntDbId nSignedId =
                        static_cast<Adesk::IntDbId>(nUnsignedId);
        return this->setFromOldId(nSignedId);
    }
#endif

    bool           isValid() const;

    AcDbObjectId&  operator =  (const AcDbObjectId&);
    AcDbObjectId&  operator =  (const AcDbStub*);

    bool           operator <  (const AcDbObjectId&) const;
    bool           operator >  (const AcDbObjectId&) const;
    bool           operator >= (const AcDbObjectId&) const;
    bool           operator <= (const AcDbObjectId&) const;
    bool           operator == (const AcDbObjectId&) const;
    bool           operator != (const AcDbObjectId&) const;

    bool           operator <  (const AcDbStub*) const;
    bool           operator >  (const AcDbStub*) const;
    bool           operator >= (const AcDbStub*) const;
    bool           operator <= (const AcDbStub*) const;
    bool           operator == (const AcDbStub*) const;
    bool           operator != (const AcDbStub*) const;

    operator       AcDbStub*   () const;

    AcDbDatabase* database() const;
    AcDbDatabase* originalDatabase() const;
    void          convertToRedirectedId();
    bool          isErased() const;
    bool          isEffectivelyErased() const;
    bool          isResident() const;
    bool          objectLeftOnDisk() const;
    AcDbHandle    handle() const;
    AcDbHandle    nonForwardedHandle() const;

    AcRxClass*    objectClass() const;

protected:
    AcDbStub*  mId;
};

class AcDbHardOwnershipId : public AcDbObjectId
{
public:
    AcDbHardOwnershipId();
    AcDbHardOwnershipId(const AcDbObjectId&);
    AcDbHardOwnershipId(const AcDbStub*);

    AcDbHardOwnershipId& operator =(const AcDbHardOwnershipId&);
    AcDbHardOwnershipId& operator =(const AcDbObjectId&);
    AcDbHardOwnershipId& operator =(const AcDbStub*);

    bool           operator != (const AcDbObjectId&) const;
    bool           operator != (const AcDbStub*) const;
    bool           operator == (const AcDbObjectId&) const;
    bool           operator == (const AcDbStub*) const;

    operator AcDbStub* () const;
};

class AcDbSoftOwnershipId : public AcDbObjectId
{
public:
    AcDbSoftOwnershipId();
    AcDbSoftOwnershipId(const AcDbObjectId&);
    AcDbSoftOwnershipId(const AcDbStub*);

    AcDbSoftOwnershipId& operator =(const AcDbSoftOwnershipId&);
    AcDbSoftOwnershipId& operator =(const AcDbObjectId&);
    AcDbSoftOwnershipId& operator =(const AcDbStub*);
    bool           operator != (const AcDbObjectId&) const;
    bool           operator != (const AcDbStub*) const;
    bool           operator == (const AcDbObjectId&) const;
    bool           operator == (const AcDbStub*) const;

    operator AcDbStub* () const;
};

class AcDbHardPointerId : public AcDbObjectId
{
public:
    AcDbHardPointerId();
    AcDbHardPointerId(const AcDbObjectId&);
    AcDbHardPointerId(const AcDbStub*);

    AcDbHardPointerId& operator =(const AcDbHardPointerId&);
    AcDbHardPointerId& operator =(const AcDbObjectId&);
    AcDbHardPointerId& operator =(const AcDbStub*);
    bool           operator != (const AcDbObjectId&) const;
    bool           operator != (const AcDbStub*) const;
    bool           operator == (const AcDbObjectId&) const;
    bool           operator == (const AcDbStub*) const;

    operator AcDbStub* () const;
};

class AcDbSoftPointerId : public AcDbObjectId
{
public:
    AcDbSoftPointerId();
    AcDbSoftPointerId(const AcDbObjectId&);
    AcDbSoftPointerId(const AcDbStub*);

    AcDbSoftPointerId& operator =(const AcDbSoftPointerId&);
    AcDbSoftPointerId& operator =(const AcDbObjectId&);
    AcDbSoftPointerId& operator =(const AcDbStub*);
    bool           operator != (const AcDbObjectId&) const;
    bool           operator != (const AcDbStub*) const;
    bool           operator == (const AcDbObjectId&) const;
    bool           operator == (const AcDbStub*) const;

    operator AcDbStub* () const;
};


//////////////////// AcDbObjectId inlines ////////////////////

inline
AcDbObjectId::AcDbObjectId()
{ mId = NULL; }

//inline
//AcDbObjectId::AcDbObjectId(const AcDbObjectId& id)
//{ mId = id.mId; }

inline
AcDbObjectId::AcDbObjectId(const AcDbStub* pStub)
{ mId = const_cast<AcDbStub*>(pStub); }

inline bool
AcDbObjectId::isNull() const
{ return mId == NULL; }

inline void
AcDbObjectId::setNull()
{ mId = NULL; }

inline
Adesk::IntDbId AcDbObjectId::asOldId() const
{
    return reinterpret_cast<Adesk::IntDbId>(this->mId);
}

inline
AcDbObjectId& AcDbObjectId::setFromOldId(Adesk::IntDbId oldId)
{
    this->mId = reinterpret_cast<AcDbStub*>(oldId);
    return *this;
}

inline 
AcDbObjectId& AcDbObjectId::operator = (const AcDbObjectId& id)
{ mId = id.mId; return *this; }

inline 
AcDbObjectId& AcDbObjectId::operator = (const AcDbStub* pStub)
{ mId = const_cast<AcDbStub*>(pStub); return *this; }

inline
AcDbObjectId::operator AcDbStub* () const
{ return mId; }

//////////////////// AcDbHardOwnershipId inlines ////////////////////

inline
AcDbHardOwnershipId::AcDbHardOwnershipId() {}

inline
AcDbHardOwnershipId::AcDbHardOwnershipId(const AcDbObjectId& id)
  : AcDbObjectId(id) {}

inline
AcDbHardOwnershipId::AcDbHardOwnershipId(const AcDbStub* pStub)
  : AcDbObjectId(pStub) {}

inline
AcDbHardOwnershipId& AcDbHardOwnershipId::operator  = (
    const AcDbHardOwnershipId& id)
{ AcDbObjectId::operator=(id); return *this; }

inline
AcDbHardOwnershipId& AcDbHardOwnershipId::operator = (const AcDbObjectId& id)
{ AcDbObjectId::operator=(id); return *this; }

inline 
AcDbHardOwnershipId& AcDbHardOwnershipId::operator = (const AcDbStub* pStub)
{ mId = const_cast<AcDbStub*>(pStub); return *this; }

inline 
bool AcDbHardOwnershipId::operator != (const AcDbObjectId& id) const
{ return AcDbObjectId::operator!=(id); }

inline 
bool AcDbHardOwnershipId::operator != (const AcDbStub* pStub) const
{ return AcDbObjectId::operator!=(pStub); }

inline 
bool AcDbHardOwnershipId::operator == (const AcDbObjectId& id) const
{ return AcDbObjectId::operator==(id); }

inline 
bool AcDbHardOwnershipId::operator == (const AcDbStub* pStub) const
{ return AcDbObjectId::operator==(pStub); }

inline
AcDbHardOwnershipId::operator AcDbStub* () const
{ return mId; }

//////////////////// AcDbSoftOwnershipId inlines ////////////////////

inline
AcDbSoftOwnershipId::AcDbSoftOwnershipId() {}

inline
AcDbSoftOwnershipId::AcDbSoftOwnershipId(const AcDbObjectId& id)
  : AcDbObjectId(id) {}

inline
AcDbSoftOwnershipId::AcDbSoftOwnershipId(const AcDbStub* pStub)
  : AcDbObjectId(pStub) {}

inline
AcDbSoftOwnershipId& AcDbSoftOwnershipId::operator = (
    const AcDbSoftOwnershipId& id)
{ AcDbObjectId::operator=(id); return *this; }

inline
AcDbSoftOwnershipId& AcDbSoftOwnershipId::operator = (const AcDbObjectId& id)
{ AcDbObjectId::operator=(id); return *this; }

inline 
AcDbSoftOwnershipId& AcDbSoftOwnershipId::operator = (const AcDbStub* pStub)
{ mId = const_cast<AcDbStub*>(pStub); return *this; }

inline 
bool AcDbSoftOwnershipId::operator != (const AcDbObjectId& id) const
{ return AcDbObjectId::operator!=(id); }

inline 
bool AcDbSoftOwnershipId::operator != (const AcDbStub* pStub) const
{ return AcDbObjectId::operator!=(pStub); }

inline 
bool AcDbSoftOwnershipId::operator == (const AcDbObjectId& id) const
{ return AcDbObjectId::operator==(id); }

inline 
bool AcDbSoftOwnershipId::operator == (const AcDbStub* pStub) const
{ return AcDbObjectId::operator==(pStub); }

inline
AcDbSoftOwnershipId::operator AcDbStub* () const
{ return mId; }

//////////////////// AcDbHardPointerId inlines ////////////////////

inline
AcDbHardPointerId::AcDbHardPointerId() {}

inline
AcDbHardPointerId::AcDbHardPointerId(const AcDbObjectId& id)
  : AcDbObjectId(id) {}

inline
AcDbHardPointerId::AcDbHardPointerId(const AcDbStub* pStub)
  : AcDbObjectId(pStub) {}

inline
AcDbHardPointerId& AcDbHardPointerId::operator = (
    const AcDbHardPointerId& id)
{ AcDbObjectId::operator=(id); return *this; }

inline
AcDbHardPointerId& AcDbHardPointerId::operator = (const AcDbObjectId& id)
{ AcDbObjectId::operator=(id); return *this; }

inline 
AcDbHardPointerId& AcDbHardPointerId::operator = (const AcDbStub* pStub)
{ mId = const_cast<AcDbStub*>(pStub); return *this; }

inline 
bool AcDbHardPointerId::operator != (const AcDbObjectId& id) const
{ return AcDbObjectId::operator!=(id); }

inline 
bool AcDbHardPointerId::operator != (const AcDbStub* pStub) const
{ return AcDbObjectId::operator!=(pStub); }

inline 
bool AcDbHardPointerId::operator == (const AcDbObjectId& id) const
{ return AcDbObjectId::operator==(id); }

inline 
bool AcDbHardPointerId::operator == (const AcDbStub* pStub) const
{ return AcDbObjectId::operator==(pStub); }

inline
AcDbHardPointerId::operator AcDbStub* () const
{ return mId; }

//////////////////// AcDbSoftPointerId inlines ////////////////////

inline
AcDbSoftPointerId::AcDbSoftPointerId() {}

inline
AcDbSoftPointerId::AcDbSoftPointerId(const AcDbObjectId& id)
  : AcDbObjectId(id) {}

inline
AcDbSoftPointerId::AcDbSoftPointerId(const AcDbStub* pStub)
  : AcDbObjectId(pStub) {}

inline
AcDbSoftPointerId& AcDbSoftPointerId::operator = (const AcDbSoftPointerId& id)
{ AcDbObjectId::operator=(id); return *this; }

inline
AcDbSoftPointerId& AcDbSoftPointerId::operator = (const AcDbObjectId& id)
{ AcDbObjectId::operator=(id); return *this; }

inline 
AcDbSoftPointerId& AcDbSoftPointerId::operator = (const AcDbStub* pStub)
{ mId = const_cast<AcDbStub*>(pStub); return *this; }

inline 
bool AcDbSoftPointerId::operator != (const AcDbObjectId& id) const
{ return AcDbObjectId::operator!=(id); }

inline 
bool AcDbSoftPointerId::operator != (const AcDbStub* pStub) const
{ return AcDbObjectId::operator!=(pStub); }

inline 
bool AcDbSoftPointerId::operator == (const AcDbObjectId& id) const
{ return AcDbObjectId::operator==(id); }

inline 
bool AcDbSoftPointerId::operator == (const AcDbStub* pStub) const
{ return AcDbObjectId::operator==(pStub); }

inline
AcDbSoftPointerId::operator AcDbStub* () const
{ return mId; }

#define ADSK_ACDBOBJECTID_DEFINED
#include "acarrayhelper.h"

#pragma pack(pop)

#endif
