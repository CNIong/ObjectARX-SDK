	//
#ifndef AD_RXOBJECT_H
#define AD_RXOBJECT_H 1
//
// (C) Copyright 1997-2010 by Autodesk, Inc.
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

#include "adesk.h"
#include "rxdefs.h"
#include "rxboiler.h"
#include "acadstrc.h"

#pragma pack (push, 8)

// define GCC_NO_VTABLE to empty for Windows build
#define GCC_NO_VTABLE

#if defined _ADESK_WINDOWS_
#ifdef  ACDB_API
    #  define   ACDB_PORT _declspec(dllexport)
#else
    #  define   ACDB_PORT
#endif
#else // GCC port - Still need to sort out the right ACDB_PORT definition for exporting symbols

#define ACDB_PORT
#if defined(ACDB_API) || defined(ACDB_EXT)
// Why check ACDB_API?
// ACDB_API is defined when compile acdb. But not when compile Gelib.dylib.
// Gelib.dylib would try to link to virtual functions declared by AcRxObject. However,
// there is no implementation Gelib project can see. Unless they are pure virtual function, there would be
// linker error.
// On the other hand, when compiling acdb, these virtual function can't be pure virtual, otherwise,
// they will prevent from instantialize subclass objects. And the implementation of
// the virtual functions are in rxinit.cpp which is compiled into acdb.
// So we will leave GCC_NO_VTABLE to empty when compile acdb.

#else

// Why define GCC_NO_VTABLE to =0?
// define GCC_NO_VTABLE since there isn't equivalence of __declspec(novtable) on GCC
// Given virtual functions in AcRxObject has no implementation, there would be linker error
// if they are not pure virtual function when linking with GCC
#undef GCC_NO_VTABLE
#define GCC_NO_VTABLE =0    

#endif //ACDB_API

#endif //_ADESK_WINDOWS_

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

    virtual AcRxClass*        isA() const GCC_NO_VTABLE;
    
    virtual AcRxObject*       clone() const GCC_NO_VTABLE;
    virtual Acad::ErrorStatus copyFrom(const AcRxObject* other) GCC_NO_VTABLE;
    virtual Adesk::Boolean    isEqualTo(const AcRxObject * other) const GCC_NO_VTABLE;
    virtual AcRx::Ordering    comparedTo(const AcRxObject * other) const GCC_NO_VTABLE;
    
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

