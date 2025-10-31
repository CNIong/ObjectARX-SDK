#ifndef AD_DBIDMAP_H
#define AD_DBIDMAP_H 1
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
//
// DESCRIPTION:  Mapping class for object id's.

#include "acdb.h"
#include "rxobject.h"

#pragma pack (push, 8)

class AcDbDatabase;

class AcDbIdPair
{
public:
    AcDbIdPair();
    AcDbIdPair(const AcDbIdPair&);
    AcDbIdPair(AcDbObjectId key, AcDbObjectId value,
               bool isCloned,
               bool isPrimary = false,
               bool isOwnerXlated = true);

    AcDbObjectId   key() const;
    AcDbObjectId   value() const;
    bool           isCloned() const;
    bool           isPrimary() const;
    bool           isOwnerXlated() const;

    void 	   setKey(AcDbObjectId);
    void	   setValue(AcDbObjectId);
    void	   setIsCloned(bool isCloned);
    void	   setIsPrimary(bool isPrimary);
    void	   setIsOwnerXlated(bool isOwnerXlated);

private:
    AcDbObjectId   mKey;
    AcDbObjectId   mValue;
    bool           mIsCloned : 1;
    bool           mIsPrimary : 1;
    bool           mIsOwnerXlated : 1;
};

class AcDbIdMappingIter;
class AcDbImpIdMapping;
class AcDbImpIdMappingIter;

class AcDbIdMapping: public  AcRxObject
{
public:
    AcDbIdMapping();
    virtual ~AcDbIdMapping();
    ACRX_DECLARE_MEMBERS(AcDbIdMapping);

    virtual Acad::ErrorStatus		assign(const AcDbIdPair&);
    virtual bool          		compute(AcDbIdPair&) const;
    virtual bool                        change(const AcDbIdPair&);
    virtual bool              		del(AcDbObjectId key);

	    Acad::ErrorStatus   destDb(AcDbDatabase*& db) const;
	    Acad::ErrorStatus   setDestDb(AcDbDatabase* db);
	    Acad::ErrorStatus   origDb(AcDbDatabase*& db) const;

	    AcDb::DeepCloneType deepCloneContext() const;
            AcDb::DuplicateRecordCloning duplicateRecordCloning() const;

    virtual Acad::ErrorStatus   copyFrom(const AcRxObject* other);

private:
    friend class AcDbSystemInternals;
    friend class AcDbImpIdMappingIter;
    AcDbIdMapping(const AcDbIdMapping&);
    AcDbIdMapping& operator= (const AcDbIdMapping&);
    AcDbImpIdMapping* mpImp;
};


class AcDbIdMappingIter: public  AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbIdMappingIter);
    AcDbIdMappingIter(const AcDbIdMapping&);
    virtual ~AcDbIdMappingIter();

    virtual Acad::ErrorStatus	iterateOn(const AcDbIdMapping&);

    virtual void		start();
    virtual bool           	getMap(AcDbIdPair&);
    virtual bool           	next();
    virtual bool          	done();

private:
    friend class		AcDbSystemInternals;
    AcDbImpIdMappingIter*	mpImp;
};

inline
AcDbObjectId AcDbIdPair::key() const
{ return mKey; }

inline
AcDbObjectId AcDbIdPair::value() const
{ return mValue; }

inline
bool AcDbIdPair::isCloned() const
{ return mIsCloned; }

inline
bool AcDbIdPair::isPrimary() const
{ return mIsPrimary; }

inline
bool AcDbIdPair::isOwnerXlated() const
{ return mIsOwnerXlated; }

inline
void AcDbIdPair::setKey(AcDbObjectId key)
{ mKey = key; }

inline
void AcDbIdPair::setValue(AcDbObjectId value)
{ mValue = value; }

inline
void AcDbIdPair::setIsCloned(bool isCloned)
{ mIsCloned = isCloned; }

inline
void AcDbIdPair::setIsPrimary(bool isPrimary)
{ mIsPrimary = isPrimary; }

inline
void AcDbIdPair::setIsOwnerXlated(bool isOwnerXlated)
{ mIsOwnerXlated = isOwnerXlated; }

#pragma pack (pop)

#endif

