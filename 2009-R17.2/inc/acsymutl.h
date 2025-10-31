#ifndef _ACSYMUTL_H
#define _ACSYMUTL_H
//
// (C) Copyright 1998-2006 by Autodesk, Inc. 
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
//  DESCRIPTION:
//
//  Namespace AcEdSymbolUtilities contains various AutoCAD-specific
//  utilities for working with symbol names, symbol records, and symbol
//  tables.  The main access to the utility functions is through
//  "acedSymUtil()", which you dereference to call the member
//  functions of AcEdSymbolUtilities::Services.
//

#include <assert.h>
#include "acadstrc.h"
#include "dbsymutl.h"
#pragma pack (push, 8)

#define ACEDSYMUTIL_SERVICES_CURRENT_VERSION 100

class AcDbDatabase;

namespace AcEdSymbolUtilities
{

enum CrSpMode {
    kCrEndsInput = true
  , kCrSpEndsInput = false
};

enum NameCaseMode {
    kPreserveCase = true
  , kForceToUpper = false
};

class Services
{
public:
    enum { kCurrentVersion = ACEDSYMUTIL_SERVICES_CURRENT_VERSION };
    virtual unsigned version() const = 0;

    virtual Acad::PromptStatus getCompatibleSymbolString(
                                      ACHAR*&        pResponse,
                                      const ACHAR*   prompt,
                                      AcDbDatabase * pDb) const = 0;

    virtual Acad::PromptStatus getSymbolString(
                                      ACHAR*&      pResponse,
                                      const ACHAR* prompt,
                                      bool         onlyCrEndsInput,
                                      bool         preserveCase) const = 0;

}; // End Services

// For use by AcEdSymbolUtilities only!
#define ACEDSYMUTIL_SERVICESNAME_WITH_VERSION_1(n,v) n ## v
#define ACEDSYMUTIL_SERVICESNAME_WITH_VERSION(n,v) \
        ACEDSYMUTIL_SERVICESNAME_WITH_VERSION_1(n,v)
#define ACEDSYMUTIL_SERVICES_NAME \
        ACEDSYMUTIL_SERVICESNAME_WITH_VERSION( \
            servicesPtr, \
            ACEDSYMUTIL_SERVICES_CURRENT_VERSION)
extern const Services * ACEDSYMUTIL_SERVICES_NAME();

// --------- Inline definitions ---------

inline const Services *
servicesPtr()
{
    const Services * pSymUtil = ACEDSYMUTIL_SERVICES_NAME();
    assert(pSymUtil != 0);
    assert(pSymUtil->version() == Services::kCurrentVersion);
    return pSymUtil;
}

} // End AcEdSymbolUtilities

namespace AcEdSymUtil = AcEdSymbolUtilities;

typedef AcEdSymbolUtilities::Services AcEdSymUtilServices;

inline const AcEdSymUtilServices *
acedSymUtil()
{
    return AcEdSymbolUtilities::servicesPtr();
}

#pragma pack (pop)
#endif // _ACSYMUTL_H
