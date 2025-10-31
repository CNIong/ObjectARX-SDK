//
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

#pragma once

#include "acbasedefs.h"
#include "rxobject.h"
#include "AdAChar.h"
#pragma pack (push, 8)

class AcRxMemberCollection;
class AcRxAttributeCollection;
class AcRxSet;
class AcRxImpClass;
class AcRxMemberCollectionBuilder;
typedef void (*AcRxMemberCollectionConstructorPtr)(AcRxMemberCollectionBuilder&, void*);

class AcRxClass: public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS_EXPIMP(AcRxClass, ACBASE_PORT);

    ACBASE_PORT AcRxObject* addX(AcRxClass*, AcRxObject*);
    // Deprecated: The getX() method will be removed in a future
    // release.  Please use queryX() instead.
    ACBASE_PORT AcRxObject* getX(const AcRxClass*);
    ACBASE_PORT AcRxObject* delX(AcRxClass*);
    ACBASE_PORT AcRxObject* queryX(const AcRxClass*);

    ACBASE_PORT AcRxObject* create();
    ACBASE_PORT const ACHAR* appName() const;
    ACBASE_PORT const ACHAR* dxfName() const;
    ACBASE_PORT const ACHAR* name() const;
    ACBASE_PORT void        getClassVersion(int& dwgVer,
                            int& maintVer) const;
    ACBASE_PORT int         proxyFlags() const;

    ACBASE_PORT bool isDerivedFrom(const AcRxClass*) const;
    ACBASE_PORT AcRxClass*     myParent() const;
    ACBASE_PORT AcRx::Ordering comparedTo(const AcRxObject*) const;

    ACBASE_PORT AppNameChangeFuncPtr appNameCallbackPtr() const;

    ACBASE_PORT const AcRxSet* descendants() const;
    ACBASE_PORT AcRxMemberCollection* members() const;
    ACBASE_PORT const AcRxAttributeCollection& attributes() const;
    ACBASE_PORT AcRxAttributeCollection& attributes();
protected:
    AcRxClass(const ACHAR* name, const ACHAR* parent, AcRxMemberCollectionConstructorPtr memberConstruct, void* userData = NULL);
    virtual ~AcRxClass();
private:
    AcRxClass();
    friend class AcRxImpClass;
    AcRxImpClass* m_pImp;
};

ACBASE_PORT AcRxClass* newAcRxClass(
    const ACHAR* className,
    const ACHAR* parentClassName,
    int         proxyFlags = 0,
    AcRxObject* (*pseudoConstructor)() = NULL,
    const ACHAR* dxfName = NULL,
    const ACHAR* appName = NULL);

ACBASE_PORT AcRxClass* newAcRxClass(
    const ACHAR* className,
    const ACHAR* parentClassName,
    int         dwgVer,
    int         maintVer,
    int         proxyFlags = 0,
    AcRxObject* (*pseudoConstructor)() = NULL,
    const ACHAR* dxfName = NULL,
    const ACHAR* appName = NULL,
    AppNameChangeFuncPtr func = NULL);

ACBASE_PORT AcRxClass* newAcRxClass(
    const ACHAR* className,
    const ACHAR* parentClassName,
    int         dwgVer,
    int         maintVer,
    int         proxyFlags ,
    AcRxObject* (*pseudoConstructor)() ,
    const ACHAR* dxfName ,
    const ACHAR* appName ,
    AppNameChangeFuncPtr func,
    AcRxMemberCollectionConstructorPtr makeMembers,
    void* userData = NULL);

ACBASE_PORT void acrxBuildClassHierarchy();

// Destruction:  DELETE AcDbObject-derived CLASSES DURING APPLICATION UNLOAD ONLY !!!

ACBASE_PORT void deleteAcRxClass(AcRxClass* pClassObj);
ACBASE_PORT void acrxInitTypeSystem();
ACBASE_PORT void acrxTerminateTypeSystem();

inline bool AcRxObject::isKindOf(const AcRxClass* pOtherClass) const
{
    const AcRxClass * pMyClass = this->isA();
    return pMyClass == NULL ? false : pMyClass->isDerivedFrom(pOtherClass);

}

#pragma pack (pop)

