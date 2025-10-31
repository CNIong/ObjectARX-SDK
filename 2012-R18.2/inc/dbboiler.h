#ifndef AC_DBBOILER_H
#define AC_DBBOILER_H
//
// (C) Copyright 1993-2006 by Autodesk, Inc. 
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
//
// DESCRIPTION: Main Exported Database Library Definitions.
//     Macros primarily used in the api headers

#include "rxboiler.h"

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
#define ACDB_DECLARE_MEMBERS(CLASSNAME) \
private: \
    friend class AcDbSystemInternals; \
protected: \
    CLASSNAME(AcDbSystemInternals*); \
public: \
    ACRX_DECLARE_MEMBERS(CLASSNAME)

// The acdbOpenObject() function is a template function defined in
// dbmain.h where the first parameter is of type (CLASSNAME *&).
// The following macro exists for backwards compatibility with prior
// source which required use of this macro to define a type-specific
// version acdbOpenObject().
#define MAKE_ACDBOPENOBJECT_FUNCTION(CLASSNAME)

#endif
