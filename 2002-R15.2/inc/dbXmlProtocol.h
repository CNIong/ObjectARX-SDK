#pragma once
//
// (C) Copyright 1999 by Autodesk, Inc.
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
// DBXML.H
//
// DESCRIPTION: AcDbXmlObjectProtocol and AcDbXmlDatabaseProtocol 
// Protocol extension abstract base classes.
//
// NOTE:
// Default implementation to be attached to AcDbEntity as a catch-all. This
// guarantees that this protocol extension will be found  for any entity so
// the search up the AcRxClass tree will not fail and abort AutoCAD.  
//
#include "acdb.h"
#include "dbmain.h"
#include "dbxmlInFiler.h"
#include "dbxmlOutFiler.h"

#pragma pack(push, 8)

class AcDbXmlObjectProtocol : public AcRxObject
//
//  AcDbXmlObjectProtocol extension base class. 
//
{
public:
    AcDbXmlObjectProtocol(AcRxClass* pBaseClass);
    virtual ~AcDbXmlObjectProtocol();
    ACRX_DECLARE_MEMBERS(AcDbXmlObjectProtocol);

    virtual Acad::ErrorStatus xmlIn(AcDbObject* pObj, 
        AcDbXmlInFiler* pFiler);
    virtual Acad::ErrorStatus xmlOut(AcDbObject* pObj, 
        AcDbXmlOutFiler* pFiler);

    Acad::ErrorStatus superXmlIn(AcDbObject* pObj, AcDbXmlInFiler* pFiler);
    Acad::ErrorStatus superXmlOut(AcDbObject* pObj, AcDbXmlOutFiler* pFiler);

private:
    bool verifyImplementationContiguity();

    const AcRxClass* mpMyBaseClass;
    bool mImpIsContiguous;
    bool mImpVerified;
};


class AcDbXmlDatabaseProtocol : public AcRxObject
//
//  AcDbXmlDatabaseProtocol extension class. 
//
{
public:
    virtual ~AcDbXmlDatabaseProtocol();
    ACRX_DECLARE_MEMBERS(AcDbXmlDatabaseProtocol);
    virtual Acad::ErrorStatus xmlIn(AcDbDatabase* pDb,
        const char* xmlFilename,
        const char* logFilename=NULL);
    virtual Acad::ErrorStatus xmlOut(AcDbDatabase* pDb,
        const char* xmlFilename,
        const char* logFilename=NULL);
    virtual Acad::ErrorStatus xmlOut(AcDbDatabase* pDb,
        const char* xmlFilename,
        const char* logFilename,
        const AcDbObjectIdArray& ids);
};

#define ACDB_DECLARE_XMLOBJECTPROTOCOL(MyXmlProtocolExtensionClass) \
class MyXmlProtocolExtensionClass : public AcDbXmlObjectProtocol            \
{                                                                           \
public:                                                                     \
    MyXmlProtocolExtensionClass(AcRxClass* pBaseClass)                      \
        : AcDbXmlObjectProtocol(pBaseClass) { }                             \
    virtual Acad::ErrorStatus xmlIn(AcDbObject* pObj,                       \
        AcDbXmlInFiler* pFiler);                                            \
    virtual Acad::ErrorStatus xmlOut(AcDbObject* pObj,                      \
        AcDbXmlOutFiler* pFiler);                                           \
};

#pragma pack(pop)
