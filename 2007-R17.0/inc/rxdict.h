#ifndef _rxdict_h
#define _rxdict_h 1
//
// Copyright (C) 1992-2006 by Autodesk, Inc.
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

#include "rxobject.h"
#include "AdAChar.h"

#pragma pack (push, 8)

class AcRxDictionaryIterator;

class AcRxDictionary: public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcRxDictionary);

    virtual AcRxObject*    at      (const ACHAR* key) const = 0;
    virtual AcRxObject*    at      (Adesk::UInt32 id) const = 0;

    AcRxObject*            atPut   (const ACHAR* key, AcRxObject* pObject);
    virtual AcRxObject*    atPut   (const ACHAR* key, AcRxObject* pObject,
        Adesk::UInt32& retId) = 0;
    virtual AcRxObject*    atPut   (Adesk::UInt32 id, AcRxObject* pObject) = 0;

    virtual Adesk::Boolean resetKey(const ACHAR* oldKey, const ACHAR* newKey) = 0;
    virtual Adesk::Boolean resetKey(Adesk::UInt32 id, const ACHAR* newKey) = 0;

    virtual Adesk::Boolean atKeyAndIdPut(const ACHAR* newKey, Adesk::UInt32 id,
        AcRxObject* pObject) = 0;

    virtual AcRxObject*    remove  (const ACHAR* key) = 0;
    virtual AcRxObject*    remove  (Adesk::UInt32 id) = 0;

    virtual Adesk::Boolean has     (const ACHAR* entryName) const = 0;
    virtual Adesk::Boolean has     (Adesk::UInt32 id) const = 0;

    virtual Adesk::UInt32  idAt    (const ACHAR* key) const = 0;

    virtual const ACHAR*    keyAt   (Adesk::UInt32 id) const = 0;

    virtual Adesk::UInt32  numEntries() const = 0;

    virtual AcRxDictionaryIterator* newIterator(
        AcRx::DictIterType type = AcRx::kDictSorted) = 0;

    virtual Adesk::Boolean deletesObjects() const = 0;
    virtual Adesk::Boolean isCaseSensitive() const = 0;
    virtual Adesk::Boolean isSorted() const = 0;
};

extern "C" AcRxDictionary* acrxSysRegistry();

inline AcRxObject* AcRxDictionary::atPut(const ACHAR* key, AcRxObject* pObj)
{ Adesk::UInt32 temp; return atPut(key, pObj, temp); }

#define acrxClassDictionary \
AcRxDictionary::cast(acrxSysRegistry()->at(ACRX_CLASS_DICTIONARY))

#define acrxServiceDictionary \
AcRxDictionary::cast(acrxSysRegistry()->at(ACRX_SERVICE_DICTIONARY))

#pragma pack (pop)
#endif
