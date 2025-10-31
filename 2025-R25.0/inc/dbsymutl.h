//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2024 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
//  DESCRIPTION:
//
//  Namespace AcDbSymbolUtilities contains various utilities for
//  working with symbol names, symbol records, and symbol tables.
//  The main access to the utility functions is through
//  "acdbSymUtil()", which you dereference to call the member
//  functions of AcDbSymbolUtilities::Services.

#ifndef AD_DBSYMUTL_H
#define AD_DBSYMUTL_H 1

#include "dbmain.h"     // for AcDbDatabase::getSymbolTable
#include "dbsymtb.h"
#define DbSymUtil_Deprecated_ACHAR_Methods
#ifdef DbSymUtil_Deprecated_ACHAR_Methods
#include "acutmem.h"    // acutDelString(), acutNewString()
#endif

#pragma pack (push, 8)

#define ACDBSYMUTIL_SERVICES_CURRENT_VERSION 106

namespace AcDbSymbolUtilities
{

enum CompatibilityMode {
    kExtendedNames    = true,
    kPreExtendedNames = false
};

enum NameCaseMode {
    kPreserveCase     = true,
    kForceToUpper     = false
};

enum NewNameMode {
    kAsNewName        = true,
    kAsExistingName   = false
};

enum VerticalBarMode {
    kAllowVerticalBar = true,
    kNoVerticalBar    = false
};

class Services
{
public:
    enum { kCurrentVersion = ACDBSYMUTIL_SERVICES_CURRENT_VERSION };
    virtual int version() const = 0;

    // --------- Pre-defined symbols ---------

    virtual bool isBlockLayoutName        (const ACHAR * name) const = 0;
    virtual bool isBlockModelSpaceName    (const ACHAR * name) const = 0;
    virtual bool isBlockPaperSpaceName    (const ACHAR * name) const = 0;
    virtual bool isLayerDefpointsName     (const ACHAR * name) const = 0;
    virtual bool isLayerZeroName          (const ACHAR * name) const = 0;
    virtual bool isLinetypeByBlockName    (const ACHAR * name) const = 0;
    virtual bool isLinetypeByLayerName    (const ACHAR * name) const = 0;
    virtual bool isLinetypeContinuousName (const ACHAR * name) const = 0;
    virtual bool isRegAppAcadName         (const ACHAR * name) const = 0;
    virtual bool isTextStyleStandardName  (const ACHAR * name) const = 0;
    virtual bool isViewportActiveName     (const ACHAR * name) const = 0;

    virtual AcDbObjectId blockModelSpaceId    (AcDbDatabase * pDb) const = 0;
    virtual AcDbObjectId blockPaperSpaceId    (AcDbDatabase * pDb) const = 0;
    virtual AcDbObjectId layerDefpointsId     (AcDbDatabase * pDb) const = 0;
    virtual AcDbObjectId layerZeroId          (AcDbDatabase * pDb) const = 0;
    virtual AcDbObjectId linetypeByBlockId    (AcDbDatabase * pDb) const = 0;
    virtual AcDbObjectId linetypeByLayerId    (AcDbDatabase * pDb) const = 0;
    virtual AcDbObjectId linetypeContinuousId (AcDbDatabase * pDb) const = 0;
    virtual AcDbObjectId regAppAcadId         (AcDbDatabase * pDb) const = 0;
    virtual AcDbObjectId textStyleStandardId  (AcDbDatabase * pDb) const = 0;

    virtual const ACHAR * blockModelSpaceName    () const = 0;
    virtual const ACHAR * blockPaperSpaceName    () const = 0;
    virtual const ACHAR * layerDefpointsName     () const = 0;
    virtual const ACHAR * layerZeroName          () const = 0;
    virtual const ACHAR * linetypeByBlockName    () const = 0;
    virtual const ACHAR * linetypeByLayerName    () const = 0;
    virtual const ACHAR * linetypeContinuousName () const = 0;
    virtual const ACHAR * regAppAcadName         () const = 0;
    virtual const ACHAR * textStyleStandardName  () const = 0;
    virtual const ACHAR * viewportActiveName     () const = 0;

    // --------- Symbol names ---------

    virtual int               compareSymbolName(
                                      const ACHAR * thisName,
                                      const ACHAR * otherName) const = 0;
    virtual bool              hasVerticalBar(
                                      const ACHAR * name) const = 0;
    virtual Acad::ErrorStatus makeDependentName(
                                      AcString &    sNewName,           // out
                                      const ACHAR * dwgName,
                                      const ACHAR * symbolName) const = 0;
    // Returns sNewName == empty if invalid input or if no repairs were done
    virtual Acad::ErrorStatus repairPreExtendedSymbolName(
                                      AcString &    sNewName,           // out
                                      const ACHAR * oldName,
                                      bool         allowVerticalBar) const = 0;
#ifdef DbSymUtil_Deprecated_ACHAR_Methods
            // frees pNewName input ptr if not null
            // returns pNewName == nullptr if invalid input or if no repairs were done
            // else points pNewName to a newly allocated buffer
            Acad::ErrorStatus repairPreExtendedSymbolName(
                                      ACHAR *&      pNewName,           // in-out
                                      const ACHAR * oldName,
                                      bool         allowVerticalBar) const;     // deprecated
#endif
    // Returns sNewName == empty if invalid input or if no repairs were done
    virtual Acad::ErrorStatus repairSymbolName(
                                      AcString &    sNewName,           // out
                                      const ACHAR * oldName,
                                      bool         allowVerticalBar) const = 0;
#ifdef DbSymUtil_Deprecated_ACHAR_Methods
            // frees pNewName input ptr if not null
            // returns pNewName == nullptr if invalid input or if no repairs were done
            // else points pNewName to a newly allocated buffer
            Acad::ErrorStatus repairSymbolName(
                                      ACHAR *&      pNewName,           // in-out
                                      const ACHAR * oldName,
                                      bool         allowVerticalBar) const;     // deprecated
#endif
    virtual bool              splitDependentName(
                                      size_t &      numLeftBytes,
                                      const ACHAR *& pRight,
                                      const ACHAR *  symbolName) const = 0;
    virtual Acad::ErrorStatus validatePreExtendedSymbolName(
                                      const ACHAR * name,
                                      bool         allowVerticalBar) const = 0;
    virtual Acad::ErrorStatus validateSymbolName(
                                      const ACHAR * name,
                                      bool         allowVerticalBar) const = 0;

    // --------- Compatibility ---------

    virtual bool              compatibilityMode(
                                      AcDbDatabase * pDb) const = 0;
    virtual Acad::ErrorStatus getBlockNameFromInsertPathName(
                                      AcString &    sBlockName,         // out
                                      const ACHAR * pathName) const = 0;
#ifdef DbSymUtil_Deprecated_ACHAR_Methods
            // Frees input pBlockName ptr if it's non-null
            // Always sets pBlockName to an allocated new buffer
            Acad::ErrorStatus getBlockNameFromInsertPathName(
                                      ACHAR *&      pBlockName,         // in-out
                                      const ACHAR * pathName) const;    // deprecated
#endif
    virtual Acad::ErrorStatus getInsertPathNameFromBlockName(
                                      AcString &    sPathName,          // out
                                      const ACHAR * blockName) const = 0;
    virtual bool              getMaxSymbolNameLength(
                                      size_t &     maxLength,
                                      size_t &     maxSize,
                                      bool         isNewName,
                                      bool         compatibilityMode) const = 0;
    virtual Acad::ErrorStatus getPathNameFromSymbolName(
                                      AcString &    sPathName,          // out
                                      const ACHAR * symbolName,
                                      const ACHAR * extensions) const = 0;
#ifdef DbSymUtil_Deprecated_ACHAR_Methods
            // Frees input pPathName ptr if it's non-null
            // Always sets pPathName to an allocated new buffer
            Acad::ErrorStatus getPathNameFromSymbolName(
                                      ACHAR *&      pPathName,          // in-out
                                      const ACHAR * symbolName,
                                      const ACHAR * extensions) const;  // deprecated
#endif
    virtual Acad::ErrorStatus getSymbolNameFromPathName(
                                      AcString &    sSymbolName,        // out
                                      const ACHAR * pathName,
                                      const ACHAR * extensions) const = 0;
#ifdef DbSymUtil_Deprecated_ACHAR_Methods
            // Frees input pSymbolName ptr if it's non-null
            // Always sets pSymbolName to an allocated new buffer
            Acad::ErrorStatus getSymbolNameFromPathName(
                                      ACHAR *&      pSymbolName,        // in-out
                                      const ACHAR * pathName,
                                      const ACHAR * extensions) const;  // deprecated
#endif
    virtual Acad::ErrorStatus preValidateSymbolName(
                                      AcString &    sSymbolName,        // in-out
                                      bool         preserveCase) const = 0;
#ifdef DbSymUtil_Deprecated_ACHAR_Methods
            // if pSymbolName input is null, returns eInvalidInput
            // else frees pSymbolName input and sets it to a newly allocated buffer
            // Returns eOk if input pSymbolName points to empty string
            Acad::ErrorStatus preValidateSymbolName(
                                      ACHAR *&      pSymbolName,        // in-out
                                      bool         preserveCase) const; // deprecated
#endif
    virtual Acad::ErrorStatus validateCompatibleSymbolName(
                                      const ACHAR * name,
                                      bool         isNewName,
                                      bool         allowVerticalBar,
                                      bool         compatibilityMode) const = 0;

}; // end Services

inline Acad::ErrorStatus getSymbolName(AcString & sName, AcDbObjectId objId)
{
    sName.setEmpty();
    AcDbSymbolTableRecord *pRec = NULL;
    Acad::ErrorStatus es = ::acdbOpenObject(pRec, objId, AcDb::kForRead);
    if (es == Acad::eOk) {
        es = pRec->getName(sName);
        pRec->close();
    }
    return es;
}

#ifdef DbSymUtil_Deprecated_ACHAR_Methods
// This overload which allocates an ACHAR buffer is deprecated and will be removed.
// Please use the above overload which takes an AcString & arg.
// pName arg is out-only
inline Acad::ErrorStatus getSymbolName(ACHAR *&pName, AcDbObjectId objId)
{
    AcString sName;
    const Acad::ErrorStatus es = AcDbSymbolUtilities::getSymbolName(sName, objId);
    ::acutNewString(sName.constPtr(), pName);
    return es;
}

inline Acad::ErrorStatus Services::repairPreExtendedSymbolName(ACHAR *& pNewName,
                                      const ACHAR * oldName,
                                      bool         allowVerticalBar) const
{
    ::acutDelString(pNewName);
    AcString sName;
    const Acad::ErrorStatus es = repairPreExtendedSymbolName(sName, oldName,
                                                allowVerticalBar);
    if (es == Acad::eOk && !sName.isEmpty())
        ::acutNewString(sName.constPtr(), pNewName);
    return es;
}

inline Acad::ErrorStatus Services::repairSymbolName(ACHAR *& pNewName,
                                      const ACHAR * oldName,
                                      bool         allowVerticalBar) const
{
    ::acutDelString(pNewName);
    AcString sName;
    const Acad::ErrorStatus es = repairSymbolName(sName, oldName, allowVerticalBar);
    if (es == Acad::eOk && !sName.isEmpty())
        ::acutNewString(sName.constPtr(), pNewName);
    return es;
}

inline Acad::ErrorStatus Services::getBlockNameFromInsertPathName(ACHAR *& pBlockName,
                                                        const ACHAR * pathName) const
{
    ::acutDelString(pBlockName);
    AcString sName;
    const Acad::ErrorStatus es = getBlockNameFromInsertPathName(sName, pathName);
    ::acutNewString(sName.constPtr(), pBlockName);
    return es;
}

inline Acad::ErrorStatus Services::getPathNameFromSymbolName(
                                      ACHAR *&      pPathName,
                                      const ACHAR * symbolName,
                                      const ACHAR * extensions) const
{
    ::acutDelString(pPathName);
    AcString sName;
    const Acad::ErrorStatus es = getPathNameFromSymbolName(sName, symbolName, extensions);
    ::acutNewString(sName.constPtr(), pPathName);
    return es;
}

inline Acad::ErrorStatus Services::getSymbolNameFromPathName(
                                      ACHAR *&      pSymbolName,
                                      const ACHAR * pathName,
                                      const ACHAR * extensions) const
{
    ::acutDelString(pSymbolName);
    AcString sName;
    const Acad::ErrorStatus es = getSymbolNameFromPathName(sName, pathName, extensions);
    ::acutNewString(sName.constPtr(), pSymbolName);
    return es;
}

inline Acad::ErrorStatus Services::preValidateSymbolName(ACHAR *& pSymbolName,
                                                        bool preserveCase) const
{
    if (pSymbolName == nullptr)
        return Acad::eInvalidInput;
    AcString sName = pSymbolName;
    ::acutDelString(pSymbolName);
    const Acad::ErrorStatus es = preValidateSymbolName(sName, preserveCase);
    ::acutNewString(sName.constPtr(), pSymbolName);
    return es;
}
#endif

// For use by AcDbSymbolUtilities only!
#define ACDBSYMUTIL_SERVICESNAME_WITH_VERSION_1(n,v) n ## v
#define ACDBSYMUTIL_SERVICESNAME_WITH_VERSION(n,v) \
        ACDBSYMUTIL_SERVICESNAME_WITH_VERSION_1(n,v)
#define ACDBSYMUTIL_SERVICES_NAME \
        ACDBSYMUTIL_SERVICESNAME_WITH_VERSION( \
            servicesPtr, \
            ACDBSYMUTIL_SERVICES_CURRENT_VERSION)

ACDBCORE2D_PORT const Services * ACDBSYMUTIL_SERVICES_NAME();

// --------- Inline definitions ---------

inline const Services *
servicesPtr()
{
    const Services * pSymUtil = ACDBSYMUTIL_SERVICES_NAME();
    // We could do this assert if an assert macro is available
    // assert(pSymUtil->version() == Services::kCurrentVersion);
    return pSymUtil;
}

// The get<TABLE>Id() functions retrieve the AcDbObjectId for a symbol
// record given the name of the symbol (parameter "name") and a pointer
// to the database (parameter pDb) that contains the specified table.
// If the function succeeds, it returns the AcDbObjectId in parameter "rId"
// and returns Acad::eOk.
//
// We provide a get<TABLE>Id() function for all the basic symbol tables
// except for the viewport table, which may have duplicate records.
// The following inlined functions are available.
//
// getBlockId
// getDimStyleId
// getLayerId
// getLinetypeId
// getRegAppId
// getTextStyleId
// getUCSId
// getViewId
//
// These functions open up the table and look for the specified record.
// If you need to make successive calls for a particular table, you should
// open the table yourself instead of invcurring the overhead of
// repeatedly opening and closing the tables using these functions.

#define DBSYMUTL_MAKE_GETSYMBOLID_FUNCTION(T_TABLE) \
inline Acad::ErrorStatus \
get ## T_TABLE ## Id( \
    AcDbObjectId &objId, \
    const ACHAR  *name, \
    AcDbDatabase *pDb) \
{ \
    if (pDb == NULL) \
        return Acad::eNullObjectPointer; \
    AcDb ## T_TABLE ## Table *pTable = NULL; \
    Acad::ErrorStatus es = pDb->getSymbolTable(pTable, AcDb::kForRead); \
    if (es == Acad::eOk) { \
        es = pTable->getAt(name, objId); \
        pTable->close(); \
    } \
    return es; \
}
DBSYMUTL_MAKE_GETSYMBOLID_FUNCTION(Block)
DBSYMUTL_MAKE_GETSYMBOLID_FUNCTION(DimStyle)
DBSYMUTL_MAKE_GETSYMBOLID_FUNCTION(Layer)
DBSYMUTL_MAKE_GETSYMBOLID_FUNCTION(Linetype)
DBSYMUTL_MAKE_GETSYMBOLID_FUNCTION(RegApp)

inline Acad::ErrorStatus
getTextStyleId(
    AcDbObjectId &objId,
    const ACHAR  *name,
    AcDbDatabase *pDb)
{
    if (pDb == NULL)
        return Acad::eNullObjectPointer;
    AcDbTextStyleTable *pTable = NULL;
    Acad::ErrorStatus es = pDb->getSymbolTable(pTable, AcDb::kForRead);
    if (es == Acad::eOk) {
        AcDbTextStyleTableRecord *pRec = NULL;
        es = pTable->getAt(name, pRec, AcDb::kForRead);
        if (es == Acad::eOk) {
            if (pRec->isShapeFile())
                es = Acad::eKeyNotFound;
            else
                objId = pRec->objectId();
            pRec->close();
        }
        pTable->close();
    }
    return es;
}

DBSYMUTL_MAKE_GETSYMBOLID_FUNCTION(UCS)
DBSYMUTL_MAKE_GETSYMBOLID_FUNCTION(View)
#undef DBSYMUTL_MAKE_GETSYMBOLID_FUNCTION

// The has<TABLE>() functions return a boolean value indicating
// whether a symbol record with the given name (parameter "name") or
// AcDbObjectId (parameter objId) in a particular database's symbol table
// exists.  Parameter pDb points to the database to use for accessing
// the symbol table.  The functions return Adesk::kTrue if it finds
// the record.  Otherwise, it returns Adesk::kFalse.
// 
// We provide a has<TABLE>() function for all the basic symbol tables.
// The functions overload on the type of the first parameter.  If it is
// an AcDbObjectId, we look for the AcDbObjectId in the table.  If it is a
// string, we look for the specified name in the table.
// The following inlined functions are available.
//
// hasBlock
// hasDimStyle
// hasLayer
// hasLinetype
// hasRegApp
// hasTextStyle
// hasUCS
// hasView
// hasViewport
//
// These functions open up the table and looks for the specified record.
// IF you need to make successive calls for a particular table, you should
// open the table yourself instead of invcurring the overhead of
// repeatedly opening and closing the tables using these functions.

#define DBSYMUTL_MAKE_HASSYMBOLID_FUNCTION(T_TABLE) \
inline bool \
has ## T_TABLE( \
    AcDbObjectId  objId, \
    AcDbDatabase *pDb) \
{ \
    if (pDb == NULL) \
        return false; \
    bool hasSymbol = false; \
    AcDb ## T_TABLE ## Table *pTable = NULL; \
    Acad::ErrorStatus es = pDb->getSymbolTable(pTable, AcDb::kForRead); \
    if (es == Acad::eOk) { \
        hasSymbol = !!pTable->has(objId); \
        pTable->close(); \
    } \
    return hasSymbol; \
}
DBSYMUTL_MAKE_HASSYMBOLID_FUNCTION(Block)
DBSYMUTL_MAKE_HASSYMBOLID_FUNCTION(DimStyle)
DBSYMUTL_MAKE_HASSYMBOLID_FUNCTION(Layer)
DBSYMUTL_MAKE_HASSYMBOLID_FUNCTION(Linetype)
DBSYMUTL_MAKE_HASSYMBOLID_FUNCTION(RegApp)
DBSYMUTL_MAKE_HASSYMBOLID_FUNCTION(TextStyle)
DBSYMUTL_MAKE_HASSYMBOLID_FUNCTION(UCS)
DBSYMUTL_MAKE_HASSYMBOLID_FUNCTION(View)
DBSYMUTL_MAKE_HASSYMBOLID_FUNCTION(Viewport)
#undef DBSYMUTL_MAKE_HASSYMBOLID_FUNCTION

#define DBSYMUTL_MAKE_HASSYMBOLNAME_FUNCTION(T_TABLE) \
inline bool \
has ## T_TABLE( \
    const ACHAR  *name, \
    AcDbDatabase *pDb) \
{ \
    if (pDb == NULL) \
        return false; \
    bool hasSymbol = false; \
    AcDb ## T_TABLE ## Table *pTable = NULL; \
    Acad::ErrorStatus es = pDb->getSymbolTable(pTable, AcDb::kForRead); \
    if (es == Acad::eOk) { \
        hasSymbol = !!pTable->has(name); \
        pTable->close(); \
    } \
    return hasSymbol; \
}
DBSYMUTL_MAKE_HASSYMBOLNAME_FUNCTION(Block)
DBSYMUTL_MAKE_HASSYMBOLNAME_FUNCTION(DimStyle)
DBSYMUTL_MAKE_HASSYMBOLNAME_FUNCTION(Layer)
DBSYMUTL_MAKE_HASSYMBOLNAME_FUNCTION(Linetype)
DBSYMUTL_MAKE_HASSYMBOLNAME_FUNCTION(RegApp)
DBSYMUTL_MAKE_HASSYMBOLNAME_FUNCTION(TextStyle)
DBSYMUTL_MAKE_HASSYMBOLNAME_FUNCTION(UCS)
DBSYMUTL_MAKE_HASSYMBOLNAME_FUNCTION(View)
DBSYMUTL_MAKE_HASSYMBOLNAME_FUNCTION(Viewport)
#undef DBSYMUTL_MAKE_HASSYMBOLNAME_FUNCTION

} // end AcDbSymboUtilities

namespace AcDbSymUtil = AcDbSymbolUtilities;

ACDBCORE2D_PORT
Acad::ErrorStatus  getTableStyleNameFromDbById(const AcDbObjectId& objId, AcString & sName);

typedef AcDbSymbolUtilities::Services AcDbSymUtilServices;

inline const AcDbSymUtilServices *
acdbSymUtil()
{
    return AcDbSymbolUtilities::servicesPtr();
}

#pragma pack (pop)
#endif // !AD_DBSYMUTL_H
