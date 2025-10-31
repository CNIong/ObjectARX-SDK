#ifndef   _ACDBTRANS_H__
#define   _ACDBTRANS_H__
//
//  (C) Copyright 1993-2002 by Autodesk, Inc.  
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
//  DESCRIPTION: Header for Transaction Modeler.

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

#endif   _ACDBTRANS_H__
