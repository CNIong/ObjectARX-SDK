//
#ifndef AD_RXOBJECT_H
#define AD_RXOBJECT_H 1
//
// (C) Copyright 1997-2007 by Autodesk, Inc.
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


#include "rxdefs.h"
#include "rxboiler.h"
#include "acadstrc.h"

#pragma pack (push, 8)

#ifdef  ACDB_API
    #  define   ACDB_PORT _declspec(dllexport)
#else
    #  define   ACDB_PORT
#endif

class AcRxClass;

class ADESK_NO_VTABLE AcRxObject
{
public:
    virtual ~AcRxObject();

    static AcRxClass*         desc();
    static AcRxObject*        cast(const AcRxObject * inPtr);

    inline bool               isKindOf(const AcRxClass * aClass) const;

    AcRxObject*               queryX(const AcRxClass* protocolClass) const;

    // Deprecated: The x() method will be removed in a future release.
    // Please use queryX() instead.
    //
    AcRxObject*               x(const AcRxClass* protocolClass) const;
    virtual AcRxClass*        isA() const;

    virtual AcRxObject*       clone() const;
    virtual Acad::ErrorStatus copyFrom(const AcRxObject* other);
    virtual Adesk::Boolean    isEqualTo(const AcRxObject * other) const;
    virtual AcRx::Ordering    comparedTo(const AcRxObject * other) const;

protected:
    AcRxObject();
};

// Performance note: it might not make sense to make virtual methods
// inline, but dtors are an exception to the rule.  Derived objects'
// dtors will call this dtor explicitly, so inlining works.
//
inline AcRxObject::~AcRxObject()
{
}

#pragma pack (pop)

#include "rxclass.h"

#define ACRX_PE_PTR(RxObj,PEClass) PEClass::cast(RxObj-> \
                                            queryX(PEClass::desc()))

// Deprecated: The ACRX_X_CALL macro will be removed in a future
// release.  Please use ACRX_PE_PTR() instead.
//
#define ACRX_X_CALL(RxObj,PEClass) PEClass::cast(RxObj->x(PEClass::desc()))

#include "rxdict.h"

#endif

