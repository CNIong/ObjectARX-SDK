//
//
// Copyright (C) 1992-2007 by Autodesk, Inc.
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

#pragma once

#include "rxobject.h"
#include "AdAChar.h"
#pragma pack (push, 8)

class __declspec(novtable) AcRxClass: public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcRxClass);

    virtual AcRxObject* addX(AcRxClass*, AcRxObject*) = 0;
    // Deprecated: The getX() method will be removed in a future
    // release.  Please use queryX() instead.
    virtual AcRxObject* getX(const AcRxClass*) = 0;
    virtual AcRxObject* delX(AcRxClass*) = 0;
    virtual AcRxObject* queryX(const AcRxClass*) = 0;

    virtual AcRxObject* create() = 0;
    virtual const ACHAR* appName() const = 0;
    virtual const ACHAR* dxfName() const = 0;
    virtual const ACHAR* name() const = 0;
    virtual void        getClassVersion(int& dwgVer,
                            int& maintVer) const = 0;
    virtual int         proxyFlags() const = 0;

    virtual bool isDerivedFrom(const AcRxClass*) const = 0;
    virtual AcRxClass*     myParent() const = 0;
    virtual AcRx::Ordering comparedTo(const AcRxObject*) const = 0;

    virtual AppNameChangeFuncPtr appNameCallbackPtr() const = 0;
};

AcRxClass* newAcRxClass(
    const ACHAR* className,
    const ACHAR* parentClassName,
    int         proxyFlags = 0,
    AcRxObject* (*pseudoConstructor)() = NULL,
    const ACHAR* dxfName = NULL,
    const ACHAR* appName = NULL);

AcRxClass* newAcRxClass(
    const ACHAR* className,
    const ACHAR* parentClassName,
    int         dwgVer,
    int         maintVer,
    int         proxyFlags = 0,
    AcRxObject* (*pseudoConstructor)() = NULL,
    const ACHAR* dxfName = NULL,
    const ACHAR* appName = NULL,
    AppNameChangeFuncPtr func = NULL);


void acrxBuildClassHierarchy();

// Destruction:  DELETE CLASSES DURING APPLICATION UNLOAD ONLY !!!

void deleteAcRxClass(AcRxClass* pClassObj);

inline bool AcRxObject::isKindOf(const AcRxClass* pOtherClass) const
{
    const AcRxClass * pMyClass = this->isA();
    return pMyClass == NULL ? false : pMyClass->isDerivedFrom(pOtherClass);

}

#pragma pack (pop)

