#ifndef AC_DBBOILER_H
#define AC_DBBOILER_H
//
//
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
// DESCRIPTION: Main Exported Database Library Definitions.
//     Macros primarily used in the api headers
#include "rxboiler.h"
#include "AcDbCore2dDefs.h"

class AcDbSystemInternals;

#define ACDB_DECLARE_HEAP_OPERATORS_COMMON(CLASSNAME, EXPIMP) \
EXPIMP static void* operator new(std::size_t size); \
EXPIMP static void  operator delete(void* ptr);

//if we target C++ 17 or later in debug builds we must define these exta operators
#if defined(_DEBUG) && __cplusplus > 201402
#define ACDB_DECLARE_HEAP_OPERATORS(CLASSNAME, EXPIMP) \
ACDB_DECLARE_HEAP_OPERATORS_COMMON(CLASSNAME, EXPIMP) \
static void* operator new(std::size_t size, std::align_val_t, const char*, int) \
{ \
return CLASSNAME::operator new(size); \
} \
static void operator delete(void* p, std::align_val_t, const char*, int) \
{ \
    CLASSNAME::operator delete(p); \
}

#else
#define ACDB_DECLARE_HEAP_OPERATORS(CLASSNAME, EXPIMP) \
ACDB_DECLARE_HEAP_OPERATORS_COMMON(CLASSNAME, EXPIMP)
#endif

// Macro for common declarations of classes derived from
// AcDbObject which are built into AutoCAD.
//
// This macro is NOT intended for application-defined classes derived
// from AcDbObject when declaring their class header.  This macro declares
// an internally used form of constructor, which takes the
// AcDbSystemInternals* argument.  Rx applications should not define
// such constructors for their database object classes, but they should
// be ignored by the system anyway.
//
// Application-defined classes are advised to use the ACRX_DECLARE_MEMBERS
// macro instead, and to consult the documentation for related definitions.
//
#define ACDB_DECLARE_MEMBERS_ABSTRACT_EXPIMP(CLASSNAME, EXPIMP) \
private: \
    friend class AcDbSystemInternals; \
protected: \
    CLASSNAME(AcDbSystemInternals*); \
public: \
    ACRX_DECLARE_MEMBERS_EXPIMP(CLASSNAME, EXPIMP)

#define ACDB_DECLARE_MEMBERS_EXPIMP(CLASSNAME, EXPIMP) \
    ACDB_DECLARE_MEMBERS_ABSTRACT_EXPIMP(CLASSNAME, EXPIMP) \
    ACDB_DECLARE_HEAP_OPERATORS(CLASSNAME, EXPIMP)

#define ACDB_DECLARE_MEMBERS(CLASSNAME) ACDB_DECLARE_MEMBERS_EXPIMP(CLASSNAME, ACDBCORE2D_PORT)
#define ACDB_DECLARE_MEMBERS_ABSTRACT(CLASSNAME) ACDB_DECLARE_MEMBERS_ABSTRACT_EXPIMP(CLASSNAME, ACDBCORE2D_PORT)
#define ACDBCORE2D_DECLARE_MEMBERS(CLASSNAME) ACDB_DECLARE_MEMBERS_EXPIMP(CLASSNAME, ACDBCORE2D_PORT)


#if defined(_ADESK_IOS_) || defined(_ADESK_WEB_) || defined(_ADESK_ANDROID_)
#define GEOMENT_DECLARE_MEMBERS(CLASSNAME) \
ACDBCORE2D_DECLARE_MEMBERS(CLASSNAME); 
#else
//to export isA and desc via acdb_x64.ddf or acdb_x86.ddf
#define GEOMENT_DECLARE_MEMBERS(CLASSNAME) \
ACDB_DECLARE_MEMBERS_EXPIMP(CLASSNAME, ACDB_PORT);
#endif


#endif
