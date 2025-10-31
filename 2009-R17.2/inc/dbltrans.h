#ifndef AD_DBLTRANS_H
#define AD_DBLTRANS_H 1
//
// (C) Copyright 1997-2006 by Autodesk, Inc.
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
// DESCRIPTION: Exported AcDbLongTransaction classes

#include "dbmain.h"
#include "AdAChar.h"

#pragma pack (push, 8)

class AcDbLongTransWorkSetIterator : public AcRxObject
{
public:
    virtual ~AcDbLongTransWorkSetIterator() {};
    ACRX_DECLARE_MEMBERS(AcDbLongTransWorkSetIterator);

    virtual void           start (bool incRemovedObjs = false,
                                  bool incSecondaryObjs = false) = 0; 

    virtual bool           done () = 0;
    virtual void           step () = 0;

    virtual AcDbObjectId   objectId () const = 0;

    virtual bool           curObjectIsErased () const = 0;
    virtual bool           curObjectIsRemoved () const = 0;
    virtual bool           curObjectIsPrimary () const = 0;

};

class AcDbLongTransaction : public AcDbObject
{
public:
    AcDbLongTransaction();
    ~AcDbLongTransaction();
    ACDB_DECLARE_MEMBERS(AcDbLongTransaction);

    enum { kSameDb      = 0,
           kXrefDb      = 1,
           kUnrelatedDb = 2  };

    int                  type () const;
    AcDbObjectId         originBlock() const;
    AcDbObjectId         destinationBlock() const;

    Acad::ErrorStatus    getLongTransactionName(ACHAR*&) const;

    Acad::ErrorStatus    addToWorkSet (AcDbObjectId id);
    Acad::ErrorStatus    removeFromWorkSet (AcDbObjectId id);
    Acad::ErrorStatus    syncWorkSet ();

    // The parameter includes both erased and removed objects
    //
    Acad::ErrorStatus    newWorkSetIterator(
                             AcDbLongTransWorkSetIterator*& pNewIter,
                             bool incRemovedObjs = false,
                             bool incSecondaryObjs = false) 
                                 const;

    AcDbObjectId         originObject(AcDbObjectId id) const;

    bool                 workSetHas(AcDbObjectId id, 
                                    bool bIncErased = false) const;

    AcDbIdMapping*       activeIdMap();

    void                 regenWorkSetWithDrawOrder();

    bool                 disallowDrawOrder();
};

#pragma pack (pop)

#endif
