//
// (C) Copyright 1998-1999 by Autodesk, Inc. 
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
#include "stdafx.h"
#include "xrecordmanager.h"
#include "dbobjptr.h"
#include "adslib.h"
#include "acdocman.h"
//#include <memory.h>

const char* XRecordManager::m_strKey = "OARX_SIMPLEDYNPROPS";

Acad::ErrorStatus lockDocument(const AcDbObjectId& id)
{
    AcApDocument* pDocument;
    if ((pDocument = acDocManager->document(id.database()))==NULL)
        return Acad::eNoDocument;
    return acDocManager->lockDocument(pDocument, AcAp::kAutoWrite);
}

Acad::ErrorStatus XRecordManager::createDefaultData(const AcDbObjectId& id)
{
    Acad::ErrorStatus es;
    es = lockDocument(id);
    if (es!=Acad::eOk && es!=Acad::eNotApplicable)
        return es;
    AcDbObjectPointer<AcDbObject> pO(id,AcDb::kForWrite);
    if ((es=pO.openStatus())!=Acad::eOk)
        return es;
    AcDbObjectId idExtDict;
    if ((idExtDict=pO->extensionDictionary())==AcDbObjectId::kNull){
        if ((es=pO->createExtensionDictionary())!=Acad::eOk)
            return es;
        idExtDict= pO->extensionDictionary();
    }
    AcDbDictionaryPointer pExtDict(idExtDict,AcDb::kForWrite);
    if ((es=pExtDict.openStatus())!=Acad::eOk){
        AcDbObject* pObj;
        pO.release(pObj);
        pObj->cancel();
        return es;
    }
    AcDbObjectPointer<AcDbXrecord> pX;
    pX.create();
    if (pX.object()==NULL)
        return Acad::eOutOfMemory;
    resbuf * rb = acutBuildList(AcDb::kDxfReal,0.0,AcDb::kDxfReal,0.0,AcDb::kDxfInt32, 0,RTNONE);
    if (rb==NULL)
        return Acad::eOutOfMemory;
    if ((es=pX->setFromRbChain(*rb))!=Acad::eOk){
        acutRelRb(rb);
        return es;
    }
    acutRelRb(rb);
    AcDbObjectId idX;
    if ((es=pExtDict->setAt(m_strKey,pX.object(),idX))!=Acad::eOk){
        AcDbObject* pObj;
        pO.release(pObj);
        pObj->cancel();
        return es;
    }
    return Acad::eOk;
}
Acad::ErrorStatus XRecordManager::getXRecord(const AcDbObjectId& id,AcDbObjectId& idX)
{
    AcDbObjectPointer<AcDbObject> pO(id,AcDb::kForRead);
    Acad::ErrorStatus es;
    if ((es=pO.openStatus())!=Acad::eOk)
        return es;
    AcDbObjectId idExtDict;
    if ((idExtDict=pO->extensionDictionary())==AcDbObjectId::kNull)
        return Acad::eNotInDatabase;
    AcDbDictionaryPointer pExtDict(idExtDict,AcDb::kForRead);
    if ((es=pExtDict.openStatus())!=Acad::eOk)
        return es;
    return pExtDict->getAt(m_strKey,idX);
}

Acad::ErrorStatus XRecordManager::getData(const AcDbObjectId& id, long index, resbuf& result)
{
    Acad::ErrorStatus es;
    AcDbObjectId idX;
    if ((es=getXRecord(id,idX))!=Acad::eOk)
        return es;
    AcDbObjectPointer<AcDbXrecord> pX(idX,AcDb::kForRead);
    if ((es=pX.openStatus())!=Acad::eOk)
        return es;
    resbuf* rb;
    if ((es=pX->rbChain(&rb))!=Acad::eOk)
        return es;
    long i=0;
    resbuf* temp=rb;
    while (i<index && temp->rbnext!=NULL) 
        temp=temp->rbnext,i++;
    assert(i==index);
    memcpy(&result,temp,sizeof(resbuf));
    acutRelRb(rb);
    return Acad::eOk;
}

Acad::ErrorStatus XRecordManager::setData(const AcDbObjectId& id, long index, const resbuf& data)
{
    Acad::ErrorStatus es;
    es = lockDocument(id);
    if (es!=Acad::eOk && es!=Acad::eNotApplicable)
        return es;
    AcDbObjectId idX;
    if ((es=getXRecord(id,idX))!=Acad::eOk)
        return es;
    AcDbObjectPointer<AcDbXrecord> pX(idX,AcDb::kForWrite);
    if ((es=pX.openStatus())!=Acad::eOk)
        return es;
    resbuf* rb;
    if ((es=pX->rbChain(&rb))!=Acad::eOk)
        return es;
    long i=0;
    resbuf* temp=rb;
    while (i<index && temp->rbnext!=NULL) 
        temp=temp->rbnext,i++;
    assert(i==index);
    resbuf* next = temp->rbnext;
    memcpy(temp,&data,sizeof(resbuf));
    temp->rbnext = next;
    if ((es=pX->setFromRbChain(*rb))!=Acad::eOk){
        acutRelRb(rb);
        return es;
    }
    acutRelRb(rb);
    return Acad::eOk;
}

Acad::ErrorStatus XRecordManager::removeData(const AcDbObjectId& id)
{
    Acad::ErrorStatus es;
    es = lockDocument(id);
    if (es!=Acad::eOk && es!=Acad::eNotApplicable)
        return es;
    AcDbObjectPointer<AcDbObject> pO(id,AcDb::kForWrite);
    if ((es=pO.openStatus())!=Acad::eOk)
        return es;
    AcDbObjectId idExtDict;
    if ((idExtDict=pO->extensionDictionary())==AcDbObjectId::kNull)
        return Acad::eOk;
    AcDbDictionaryPointer pExtDict(idExtDict,AcDb::kForRead);
    if ((es=pExtDict.openStatus())!=Acad::eOk)
        return es;
    AcDbObjectId idX;
    if ((es=pExtDict->getAt(m_strKey,idX))!=Acad::eOk)
        return Acad::eOk;
    AcDbObjectPointer<AcDbXrecord> pX(idX,AcDb::kForWrite);
    if ((es=pX.openStatus())!=Acad::eOk)
        return es;
    pX->erase();
    //try to release the extension dictionary
    //if it still has entries then this is a nop
    pO->releaseExtensionDictionary();
    return Acad::eOk;

}

bool XRecordManager::isDataPresent(const AcDbObjectId& id)
{
    AcDbObjectId idX;
    return getXRecord(id,idX)==Acad::eOk?true:false;
}