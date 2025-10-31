// (C) Copyright 1996-2006 by Autodesk, Inc. 
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
// Description:
//
// This program demonstrates iterating over a symbol table.
// Specifically the linetype table.

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include <stdlib.h>
#include <rxobject.h>
#include <rxregsvc.h>
#include <aced.h>
#include <dbsymtb.h>
#include <dbapserv.h>
#include <adslib.h>
#include "tchar.h"



void iterateLinetypes();
void initApp();
void unloadApp();
extern "C"
AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode, void*);


// Opens the linetype table and iterates through all the
// entries printing the name of each linetype.
// 
// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.
//
void
iterateLinetypes()
{
    AcDbLinetypeTable *pLinetypeTbl;
    acdbHostApplicationServices()->workingDatabase()
        ->getSymbolTable(pLinetypeTbl, AcDb::kForRead);

    // Create a new iterator that starts at table
    // beginning and skips deleted.
    //
    AcDbLinetypeTableIterator *pLtIterator;
    pLinetypeTbl->newIterator(pLtIterator);

    // Walk the table, getting every table record and
    // printing the linetype name.
    //
    AcDbLinetypeTableRecord *pLtTableRcd;
    const TCHAR *pLtName;
    for (; !pLtIterator->done(); pLtIterator->step()) {
        pLtIterator->getRecord(pLtTableRcd, AcDb::kForRead);
        pLtTableRcd->getName(pLtName);
        pLtTableRcd->close();
        acutPrintf(_T("\nLinetype name is:  %s"), pLtName);
    }
    delete pLtIterator;
    pLinetypeTbl->close();
}

// END CODE APPEARING IN SDK DOCUMENT.


// Initialization function called from acrxEntryPoint during
// kInitAppMsg case.  This function is used to add commands
// to the command stack.
// 
void
initApp()
{
    acedRegCmds->addCommand(_T("ASDK_TABLETEST_COMMANDS"),
        _T("ASDK_ITERATE"), _T("ITERATE"), ACRX_CMD_MODAL,
        iterateLinetypes);
}

// Clean up function called from acrxEntryPoint during the
// kUnloadAppMsg case.  This function removes this apps
// command set from the command stack.
// 
void
unloadApp()
{
    acedRegCmds->removeGroup(_T("ASDK_TABLETEST_COMMANDS"));
}


// ARX entry point
//
AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* appId)
{
    switch (msg) {
    case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(appId);
        acrxDynamicLinker->registerAppMDIAware(appId);
        initApp();
        break;
    case AcRx::kUnloadAppMsg:
        unloadApp();
    }
    return AcRx::kRetOK;
}
