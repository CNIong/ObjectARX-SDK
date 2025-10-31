#ifndef AD_DBDICTUTIL_H
#define AD_DBDICTUTIL_H 1
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
//  DESCRIPTION:
//
//   The following are some dictionary utility functions similar 
//   to those defined for symbol tables in dbsymutl.h
//   NOTE: These utils have the same usage guidelines as the symbol 
//   table versions. That is; These functions are very handy for 
//   quick one-time access to the name or id of a dictionary entry.
//   On the other hand; if you need to make multiple accesses to 
//   a given dictionary, then avoid the overhead of these functions
//   and open the dictionary directly.
//
// -----------------------
// Get the ID of an item 
// -----------------------
//  General purpose:
//    Acad::ErrorStatus 
//      AcDbDictUtil::dictionaryGetAt(AcDbObjectId& id, const ACHAR* name, AcDbObjectId ownerDictId);
//
//  Specific:
//    Acad::ErrorStatus 
//      AcDbDictUtil::getGroupId(AcDbObjectId& id, const ACHAR* name, AcDbDatabase* pDb);
//     also...
//       getLayoutId
//       getPlotSettingsId
//       getPlotStyleNameId
//       getMaterialId
//       getColorId
//       getTableStyleId
//
// -----------------------
// Get the NAME/KEY of an item:
// -----------------------
//  General purpose:
//    Acad::ErrorStatus 
//      AcDbDictUtil::dictionaryNameAt(ACHAR*& pName, AcDbObjectId itemId, AcDbObjectId ownerDictId);
//  or...
//    Acad::ErrorStatus 
//      AcDbDictUtil::dictionaryNameAt(ACHAR*& pName, AcDbObjectId itemId);
//
//  Specific:
//    Acad::ErrorStatus 
//      AcDbDictUtil::getGroupName(ACHAR*& name, AcDbObjectId id);
//       also...
//        getLayoutName
//        getPlotSettingsName
//        getPlotStyleNameName
//        getMaterialName
//        getColorName
//        getTableStyleName
//
//  NOTE: The "get name" functions allocate the returned string.
//        The calling application is responsible for deallocating the memory 
//        used by the returned string.
//
// -----------------------
// Check for existence
// -----------------------
//  
//        bool hasGroup(const ACHAR* name, AcDbDatabase* pDb);
//       also...
//        hasLayout
//        hasPlotSettings
//        hasPlotStyleName
//        hasMaterial
//        hasColor
//        hasTableStyle
//

#include <assert.h>
#include <stddef.h>
#include "dbdict.h"
#include "AcString.h"

namespace AcDbDictUtil
{

inline Acad::ErrorStatus 
dictionaryNameAt(ACHAR*& pName, AcDbObjectId itemId, AcDbObjectId ownerDictId)
{
    assert(!itemId.isNull() && !ownerDictId.isNull());
    AcDbDictionary* pDict;
    Acad::ErrorStatus es = acdbOpenObject(pDict, ownerDictId, AcDb::kForRead);
    if (es == Acad::eOk) {
        es = pDict->nameAt(itemId, pName);
        pDict->close();
    }
    return es;
}

inline Acad::ErrorStatus 
dictionaryNameAt(AcString& name, AcDbObjectId itemId, AcDbObjectId ownerDictId)
{
    assert(!itemId.isNull() && !ownerDictId.isNull());
    AcDbDictionary* pDict;
    Acad::ErrorStatus es = acdbOpenObject(pDict, ownerDictId, AcDb::kForRead);
    if (es == Acad::eOk) {
        es = pDict->nameAt(itemId, name);
        pDict->close();
    }
    return es;
}

//Note: If you already know the owner of itemId, then call the overloaded 
//      version above to avoid an extra call to acdbOpenObject.
inline Acad::ErrorStatus 
dictionaryNameAt(ACHAR*& pName, AcDbObjectId itemId)
{
    assert(!itemId.isNull());
    AcDbObject* pObject;
    Acad::ErrorStatus es = acdbOpenObject(pObject, itemId, AcDb::kForRead);
    if (es != Acad::eOk)
        return es;
    AcDbObjectId dictId = pObject->ownerId(); //get the owner id
    es = pObject->close();
    assert(es == Acad::eOk);
    return dictionaryNameAt(pName, itemId, dictId);
}

//Note: If you already know the owner of itemId, then call the overloaded 
//      version above to avoid an extra call to acdbOpenObject.
inline Acad::ErrorStatus 
dictionaryNameAt(AcString& name, AcDbObjectId itemId)
{
    assert(!itemId.isNull());
    AcDbObject* pObject;
    Acad::ErrorStatus es = acdbOpenObject(pObject, itemId, AcDb::kForRead);
    if (es != Acad::eOk)
        return es;
    AcDbObjectId dictId = pObject->ownerId(); //get the owner id
    es = pObject->close();
    assert(es == Acad::eOk);
    return dictionaryNameAt(name, itemId, dictId);
}

// Given a dictionary and a key name, retrieve the id for that entry.
inline Acad::ErrorStatus
dictionaryGetAt(AcDbObjectId& id, const ACHAR* name, AcDbObjectId ownerDictId)
{
    assert(!ownerDictId.isNull());
    AcDbDictionary* pDict;
    Acad::ErrorStatus es = acdbOpenObject(pDict, ownerDictId, AcDb::kForRead);
    assert(es == Acad::eOk);
    if (es == Acad::eOk) {
        es = pDict->getAt(name, id);
        pDict->close();
    }
    return es;
}

#define DBDICTUTIL_MAKE_DICTIONARY_UTILS(LOWERNAME, UPPERNAME) \
inline Acad::ErrorStatus \
get##UPPERNAME##Id(AcDbObjectId& id, const ACHAR* name, AcDbDatabase* pDb) \
{ \
    assert(pDb != NULL); \
    return (pDb != NULL) \
        ? dictionaryGetAt(id, name, pDb->LOWERNAME##DictionaryId()) \
        : Acad::eInvalidInput; \
} \
inline Acad::ErrorStatus \
get##UPPERNAME##Name(ACHAR*& name, AcDbObjectId itemId) \
{ \
    AcDbDatabase* pDb = itemId.database(); \
    return (pDb != NULL) \
        ? dictionaryNameAt(name, itemId, pDb->LOWERNAME##DictionaryId()) \
        : Acad::eInvalidInput; \
} \
inline Acad::ErrorStatus \
get##UPPERNAME##Name(AcString& name, AcDbObjectId itemId) \
{ \
    AcDbDatabase* pDb = itemId.database(); \
    return (pDb != NULL) \
        ? dictionaryNameAt(name, itemId, pDb->LOWERNAME##DictionaryId()) \
        : Acad::eInvalidInput; \
} \
inline bool \
has##UPPERNAME(const ACHAR* name, AcDbDatabase* pDb) \
{ \
    AcDbObjectId id; \
    return (get##UPPERNAME##Id(id, name, pDb) == Acad::eOk); \
}

DBDICTUTIL_MAKE_DICTIONARY_UTILS( mLStyle,       MLStyle)
DBDICTUTIL_MAKE_DICTIONARY_UTILS( group,         Group)
DBDICTUTIL_MAKE_DICTIONARY_UTILS( layout,        Layout)
DBDICTUTIL_MAKE_DICTIONARY_UTILS( plotSettings,  PlotSettings)
DBDICTUTIL_MAKE_DICTIONARY_UTILS( plotStyleName, PlotStyleName)
DBDICTUTIL_MAKE_DICTIONARY_UTILS( material,      Material)
DBDICTUTIL_MAKE_DICTIONARY_UTILS( color,         Color)
DBDICTUTIL_MAKE_DICTIONARY_UTILS( tableStyle,    TableStyle)
DBDICTUTIL_MAKE_DICTIONARY_UTILS( visualStyle,    VisualStyle)

#undef DBDICTUTIL_MAKE_DICTIONARY_UTILS

} // end AcDbDictUtil namespace

#endif // !AD_DBDICTUTIL_H
