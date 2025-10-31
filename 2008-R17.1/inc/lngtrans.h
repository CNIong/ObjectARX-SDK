//////////////////////////////////////////////////////////////////////////////
//
//  (C) Copyright 1997-2006 by Autodesk, Inc.
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
//////////////////////////////////////////////////////////////////////////////
//
//  DESCRIPTION:  Header for Long Transaction Manager.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef   _LTRANSMAN_H
#define   _LTRANSMAN_H

#include "rxnames.h"
#include "dbidar.h"
#pragma pack (push, 8)

class AcDbLongTransaction;
class AcDbDatabase;
class AcDbIdMapping;
class AcApDocument;

#define AC_LONG_TRANSACTION_MANAGER_OBJ _T("AcApLongTransactionManager")

class AcApLongTransactionReactor: public AcRxObject 
{ 
public:
    ACRX_DECLARE_MEMBERS(AcApLongTransactionReactor);

    // To identify and connect this notification with the deepClone
    // notifications, AcDbLongTransactionWorkSet::activeIdMap()
    // will return the cloning idMap.  CheckOut and CheckIn, for
    // the same transaction, will use different maps.  
    //
    virtual void beginCheckOut        (AcDbLongTransaction& ,
                                       AcDbObjectIdArray& originList);
    virtual void endCheckOut          (AcDbLongTransaction& );
    virtual void beginCheckIn         (AcDbLongTransaction& );
    virtual void endCheckIn           (AcDbLongTransaction& );
    virtual void abortLongTransaction (AcDbLongTransaction& );

protected:
    Acad::ErrorStatus veto ();  // beginCheckOut() can be vetoed

private:
    Adesk::UInt8 mVeto;

friend class AcApImpLongTransactionManager;
};

class AcApLongTransactionManager: public AcRxObject 
{ 
public:
    ACRX_DECLARE_MEMBERS(AcApLongTransactionManager);

    virtual Acad::ErrorStatus   checkOut(
                                   AcDbObjectId& transId,
                                   AcDbObjectIdArray& objList,
                                   AcDbObjectId toBlock,
                                   AcDbIdMapping& errorMap,
                                   AcDbObjectId lockBlkRef = 
                                       AcDbObjectId::kNull) = 0;

    virtual Acad::ErrorStatus   checkIn  (
                                   AcDbObjectId transId,
                                   AcDbIdMapping& errorMap,
                                   bool keepObjs = false) = 0;

    virtual Acad::ErrorStatus   abortLongTransaction(
                                   AcDbObjectId transId,
                                   bool keepObjs = false) = 0;

    virtual AcDbObjectId        currentLongTransactionFor(
                                   const AcApDocument* pDoc) const = 0;

    virtual void                addReactor(AcApLongTransactionReactor*) = 0;
    virtual void                removeReactor(AcApLongTransactionReactor*) = 0;

    // For filtering classes out of Long Transactions
    //
    virtual Acad::ErrorStatus   addClassFilter (AcRxClass* ) = 0;
    virtual bool                isFiltered (AcRxClass* ) const = 0;
};

extern AcApLongTransactionManager* acapLongTransactionManagerPtr();
#define acapLongTransactionManager  acapLongTransactionManagerPtr()

#pragma pack (pop)
#endif  // !_LTRANSMAN_H
