#ifndef _rxclass_h
#define _rxclass_h 1
//
// Copyright (C) 1992-1999 by Autodesk, Inc.
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
#include "rxobject.h"
#pragma pack (push, 8)

class AcRxClass: public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcRxClass);

    virtual AcRxObject* addX(AcRxClass*, AcRxObject*) = 0;
    virtual AcRxObject* getX(AcRxClass*) = 0;
    virtual AcRxObject* delX(AcRxClass*) = 0;
    virtual AcRxObject* queryX(AcRxClass*) = 0;

    virtual AcRxObject* create() = 0;
    virtual const char* appName() const = 0;
    virtual const char* dxfName() const = 0;
    virtual const char* name() const = 0;
    virtual void        getClassVersion(int& dwgVer,
                            int& maintVer) const = 0;
    virtual int         proxyFlags() const = 0;

    virtual bool isDerivedFrom(const AcRxClass*) const = 0;
    virtual AcRxClass*     myParent() const = 0;
    virtual AcRx::Ordering comparedTo(const AcRxObject*) const = 0;

    // The following are for Autodesk Internal use only
    //
    virtual void* pcPtr() const = 0;
    virtual void  setPcPtr(void*) = 0;
};

extern AcRxClass* newAcRxClass(
    const char* className,
    const char* parentClassName,
    int         proxyFlags = 0,
    AcRxObject* (*pseudoConstructor)() = NULL,
    const char* dxfName = NULL,
    const char* appName = NULL);

extern AcRxClass* newAcRxClass(
    const char* className,
    const char* parentClassName,
    int         dwgVer,
    int         maintVer,
    int         proxyFlags = 0,
    AcRxObject* (*pseudoConstructor)() = NULL,
    const char* dxfName = NULL,
    const char* appName = NULL);


extern "C" void acrxBuildClassHierarchy();

// Destruction:  DELETE CLASSES DURING APPLICATION UNLOAD ONLY !!!

extern "C" void deleteAcRxClass(AcRxClass* pClassObj);

inline bool AcRxObject::isKindOf(const AcRxClass* aClass) const
{
    AcRxClass* c;
    return ((c = isA()) == NULL) ? true : c->isDerivedFrom(aClass);
}

#pragma pack (pop)
#endif
