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
//  main.cpp

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "acdb.h"             // acdb definitions
#include "adslib.h"           // ads defs
#include "dbents.h"           // "old" entities
#include "aced.h"             // aced stuff
#include "dbdict.h"           // dictionaries
#include "dbsymtb.h"          // symboltables
#include "acgi.h"             // graphical definitions
#include "main.h"             // this project
#include "edreact.h"          // the dynamiclinkerreactor
#include "MkrEnti.h"          // new entity AsdkMkrEntity
#include "MKROBJE.h"          // new entity AsdkMkrObject
#include "rxregsvc.h"         // unlock application
#include "dbapserv.h"
#include "arxutils.h"
#include "tchar.h"



// function prototypes
//
static void initApp   ();
static void unloadApp ();
extern "C" AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode msg, void* ptr);


void
mkraddobjects()
{
    AcGePoint3d pt;
    if (RTNORM != acedGetPoint( NULL, _T("\nEnter position:"), asDblArray (pt) ))
        return;

    AsdkMkrEntity* pEnt = new AsdkMkrEntity;
    if (NULL == pEnt)
        return;

    pEnt->setPos( pt );
    if (!append( pEnt )) {
        delete pEnt;
        return;
    }

    AcDbObjectId objId;
    AsdkMkrObject *pObj = new AsdkMkrObject;
    if (NULL == pObj) {
        pEnt->erase();
        pEnt->close();
        return;
    }

#ifdef DIRECT
    acdbHostApplicationServices()->workingDatabase()
        ->addAcDbObject( objId, pObj );
    pObj->close();
#else
#ifdef NOD
    AcDbDictionary* pMyDict = getDict( _T(/*NOXLATE*/"ASDK_MYDICT"), AcDb::kForWrite );
    if (NULL != pMyDict)
        pMyDict->setMergeStyle(AcDb::kDrcMangleName);
#else
    AcDbDictionary* pMyDict = getExtDict( pEnt, _T(/*NOXLATE*/"ASDK_MYDICT"), AcDb::kForWrite );
#endif  // NOD
    if (NULL == pMyDict) {
        delete pObj;
        pEnt->erase();
        pEnt->close();
        return;
    }

    Acad::ErrorStatus es;
    if (pMyDict->has( _T(/*NOXLATE*/"MYENTRY") ))
        es = pMyDict->setAt( _T("*"), pObj, objId );
    else
        es = pMyDict->setAt( _T(/*NOXLATE*/"MYENTRY"), pObj, objId );
    pMyDict->close();
    if (Acad::eOk == es)
        pObj->close();
    else {
        delete pObj;
        pEnt->erase();
        pEnt->close();
        return;
    }

#endif  // DIRECT
    pEnt->setId( objId );
    pEnt->close();

    acutPrintf( _T("\nEv'rything OK\n") );
}


static void
initApp(void)
{
    // register your own entities
    //
    AsdkMkrEntity::rxInit();
    AsdkMkrObject::rxInit();
    acrxBuildClassHierarchy();

    // register your autocad commands
    //
    acedRegCmds->addCommand( _T(/*NOXLATE*/"ASDK_MKR"), _T(/*NOXLATE*/"ASDK_ADDOBJECTS"), _T("ADDOBJECTS"),
        ACRX_CMD_TRANSPARENT | ACRX_CMD_USEPICKSET, mkraddobjects );
}


static void
unloadApp(void)
{
    // unregister your own entities
    //
    deleteAcRxClass(AsdkMkrEntity::desc());
    deleteAcRxClass(AsdkMkrObject::desc());

    // unregister your autocad commands
    //
    acedRegCmds->removeGroup(_T(/*NOXLATE*/"ASDK_MKR"));
    erase_EditorReactor();
}


// acrxEntryPoint(internal)
// This function is the entry point for your application.
//
AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* ptr)
{
    switch (msg) {
    case AcRx::kInitAppMsg:
        acrxUnlockApplication(ptr);
        acrxRegisterAppMDIAware(ptr);
        initApp();
        break;
    case AcRx::kUnloadAppMsg:
        unloadApp();
        break;
    case AcRx::kLoadDwgMsg:
        create_EditorReactor();
#ifdef DIRECT
        acutPrintf( _T("\nHardOwnership & addAcDbObject\n") );
#else
#ifdef XLATE
        acutPrintf( _T("\nDeepCloneXlation activated.\n") );
#else
        acutPrintf( _T("\nDeepCloneXlation de-activated.\n") );
#endif  // XLATE
#ifdef NOD
        acutPrintf( _T("Custom object will be stored in the")
            _T(" NamedObjectsDictionary.\n") );
#else
        acutPrintf( _T("Custom object will be stored in the")
            _T(" Extension Dictionary.\n") );
#endif  // NOD
#ifdef HARDPOINTER
        acutPrintf( _T("Entity keeps HardPointerId of custom object.\n") );
#else
        acutPrintf( _T("Entity keeps SoftPointerId of custom object.\n") );
#endif  // HARDPOINTER
#endif  // DIRECT
        acutPrintf( _T("Start with 'addobjects'.\n") );
    }
    return AcRx::kRetOK;
}
