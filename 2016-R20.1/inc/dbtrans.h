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
//  DESCRIPTION: Header for Transaction Modeler.

#ifndef   _ACDBTRANS_H__
#define   _ACDBTRANS_H__

#include "dbapserv.h"

#pragma pack (push, 8)

class AcTransaction;
class AcTransactionReactor;

class AcDbTransactionManager: public AcRxObject
{ 
public:
    ACRX_DECLARE_MEMBERS(AcDbTransactionManager);

    virtual AcTransaction*      startTransaction() = 0;
    virtual Acad::ErrorStatus   endTransaction  () = 0;
    virtual Acad::ErrorStatus   abortTransaction() = 0;

    virtual int                 numActiveTransactions() = 0;
    virtual AcTransaction*      topTransaction() = 0;
    virtual Acad::ErrorStatus   addNewlyCreatedDBRObject(AcDbObject* obj,
                                     bool add = true) = 0;

    virtual Acad::ErrorStatus   getAllObjects(AcDbVoidPtrArray& objs) = 0;

    virtual void                addReactor(AcTransactionReactor* reactor) = 0;
    virtual void                removeReactor(AcTransactionReactor* reactor) =0;

    virtual Acad::ErrorStatus   getObject(AcDbObject*& obj, AcDbObjectId id,
                                          AcDb::OpenMode mode, 
                                          bool openErasedObj = false) = 0; 

    virtual Acad::ErrorStatus   markObjectPageable(AcDbObject* pObject) = 0;
    virtual Acad::ErrorStatus   queueForGraphicsFlush() = 0;

};


class AcTransaction: public AcRxObject
{ 
public:
    ACRX_DECLARE_MEMBERS(AcTransaction);
    virtual 
    Acad::ErrorStatus getObject(AcDbObject*& obj, 
                                AcDbObjectId   objectId, AcDb::OpenMode mode,
                                bool openErasedObject = false) = 0;

    virtual 
    Acad::ErrorStatus markObjectPageable(AcDbObject* pObject) = 0;

    virtual Acad::ErrorStatus   getAllObjects(AcDbVoidPtrArray& objs) = 0;
};

class AcTransactionReactor: public AcRxObject
//
// Reactor for transaction management.
//
{
public:
    ACRX_DECLARE_MEMBERS(AcTransactionReactor);

    virtual void transactionAboutToStart (int& numTransactions,
        AcDbTransactionManager* transactionManagerPtr);
    virtual void transactionStarted      (int& numTransactions,
        AcDbTransactionManager* transactionManagerPtr);
    virtual void transactionAboutToEnd   (int& numTransactions,
        AcDbTransactionManager* transactionManagerPtr);
    virtual void transactionEnded        (int& numTransactions,
        AcDbTransactionManager* transactionManagerPtr);
    virtual void transactionAboutToAbort (int& numTransactions,
        AcDbTransactionManager* transactionManagerPtr);
    virtual void transactionAborted      (int& numTransactions,
        AcDbTransactionManager* transactionManagerPtr);
    virtual void endCalledOnOutermostTransaction (int& numTransactions,
        AcDbTransactionManager* transactionManagerPtr);
    virtual void objectIdSwapped (const AcDbObject* pTransResObj,
        const AcDbObject* pOtherObj,
        AcDbTransactionManager* transactionManagerPtr);
};

inline AcDbTransactionManager* acdbTransactionManagerPtr()
{
    return acdbHostApplicationServices()->workingTransactionManager();
}

#define acdbTransactionManager  acdbTransactionManagerPtr()

#pragma pack (pop)

#endif  // _ACDBTRANS_H__
