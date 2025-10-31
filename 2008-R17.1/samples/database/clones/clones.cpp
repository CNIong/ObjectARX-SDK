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
//  clones.cpp

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "acdb.h"             // acdb definitions
#include "adslib.h"           // ads defs
#include "dbents.h"           // "old" entities
#include "aced.h"             // aced stuff
#include "dbsymtb.h"          // symboltables
#include "clones.h"           // this project
#include "rxregsvc.h"         // unlock application
#include "dbidmap.h"
#include "dbapserv.h"
#include "gemat3d.h"
#include <stdlib.h>
#include "tchar.h"



// function prototypes
//
Adesk::Boolean append     (AcDbEntity* pEntity, AcDbObjectId& objId);
Adesk::Boolean append     (AcDbEntity* pEntity);
AcDbObjectId   getBlockId (const TCHAR* pBlockName);
int            getFile    (const TCHAR* pCmdAsk, const TCHAR* pDiaAsk,
                           const TCHAR* pExt, TCHAR* pResult);
static void unloadApp(void);
static void initApp  (void);
extern "C" AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode msg, void* ptr);


// Copies the entire current space (either model- or paper space)
// using AcDbObject::clone(). The cloned entities are inserted
// into model space. You might notice that calling clone() doesn't
// work for "complex entities" like Polylines or Blocks.
//
void
clone1()
{
    ads_name ss;
    if (RTNORM != acedSSGet( _T("_x"), NULL, NULL, NULL, ss ))
    {
        acutPrintf( _T("acedSSGet cancelled\n") );
        return;
    }

    long length;
    if (RTNORM != acedSSLength( ss, &length ) || 0 == length)
    {
        acutPrintf( _T("empty selection set\n") );
        acedSSFree( ss );
        return;
    }

    ads_name     ent;
    AcDbObjectId id;

    for (long i = 0; i < length; i++) {
        if (RTNORM != acedSSName( ss, i, ent ))
            continue;
        if (Acad::eOk != acdbGetObjectId( id, ent ))
            continue;
        AcDbEntity* pObj;
        if (Acad::eOk != acdbOpenAcDbEntity( pObj, id, AcDb::kForRead ))
            continue;

        AcDbEntity* pClone = AcDbEntity::cast( pObj->clone() );
        if (NULL != pClone) {
            if (append( pClone ))
                pClone->close();
            else
                delete pClone;
        }
        pObj->close();
    }
    acedSSFree( ss );
}


// Copies the entire current space (either model- or paper space)
// using AcDbDatabase::deepCloneObjects(). The cloned entities are
// inserted into model space. This version works well with
// Polylines and Blocks.
//
void
clone2()
{
    ads_name ss;
    if (RTNORM != acedSSGet( _T("_x"), NULL, NULL, NULL, ss ))
    {
        acutPrintf( _T("acedSSGet cancelled\n") );
        return;
    }

    long length;
    if (RTNORM != acedSSLength( ss, &length ) || 0 == length)
    {
        acutPrintf( _T("empty selection set\n") );
        acedSSFree( ss );
        return;
    }

    ads_name          ent;
    AcDbObjectId      id;
    AcDbObjectIdArray list;
    AcDbIdMapping     pIdMap;

    for (long i = 0; i < length; i++) {
        if (RTNORM != acedSSName( ss, i, ent ))
            continue;
        if (Acad::eOk != acdbGetObjectId( id, ent ))
            continue;

        list.append( id );
    }
    acedSSFree( ss );

    AcDbObjectId blockId = getBlockId( ACDB_MODEL_SPACE );
    if (blockId != 0) {
        if (Acad::eOk != acdbHostApplicationServices()->workingDatabase()
            ->deepCloneObjects( list, blockId, pIdMap ))
            acutPrintf( _T("Error on deepCloneObjects\n") );
    }
    else
        acutPrintf( _T("Error in getting ModelSpace ID\n") );
}

// Copies an external drawing into the current model space.
// This is the supported way: a combination of
// AcDbDatabase::insert and AcDbDatabase::wblock.
// First, we wblock the external database into a temporary
// in-memory database. We can't wblock directly into the
// current drawing, because wblock is destructive on the
// target database.
// Then we use insert to insert the temporary database into
// the current drawing. We can't use insert to insert the
// external drawing directly, because insert uses
// cheapClone, which moves the objects from the source to
// the target database.
//
// Using this approach, all the symbol table gets merged
// correctly into the current drawing database.
//
void
clone3()
{
    AcDbObjectId id;
    AcDbObjectIdArray list;
    AcDbDatabase extDatabase( Adesk::kFalse );
    TCHAR dwgName[_MAX_PATH];

    if (RTNORM != getFile( _T("Enter DWG name"), _T("Select Drawing"), _T("dwg"),
                           dwgName ))
    {
        return;
    }
    if (Acad::eOk != extDatabase.readDwgFile( dwgName ))
    {
        acedAlert( _T("Error reading DWG!") );
        return;
    }
    AcDbBlockTable* pBT;
    if (Acad::eOk != extDatabase.getSymbolTable( pBT, AcDb::kForRead ))
    {
        acedAlert( _T("Error getting BlockTable of DWG") );
        return;
    }
    AcDbBlockTableRecord* pBTR;
    Acad::ErrorStatus es = pBT->getAt( ACDB_MODEL_SPACE, pBTR, AcDb::kForRead );
    pBT->close();
    if (Acad::eOk != es) {
        acedAlert( _T("Error getting model space of DWG") );
        return;
    }

    AcDbBlockTableRecordIterator* pIT;
    if (Acad::eOk != pBTR->newIterator( pIT )) {
        acedAlert( _T("Error iterating model space of DWG") );
        pBTR->close();
        return;
    }

    for ( ; !pIT->done(); pIT->step()) {
        if (Acad::eOk == pIT->getEntityId( id )) {
            list.append( id );

            // There is a bug in ARX that causes extension dictionaries
            // to appear to be soft owners of their contents.  This causes
	    // the contents to be skipped during wblock.  To fix this we
	    // must explicitly tell the extension dictionary to be a hard
	    // owner of it's entries.
            //
            AcDbEntity *pEnt;
            if ( Acad::eOk == pIT->getEntity(pEnt, AcDb::kForRead)) {
                AcDbObjectId obj;
                if ((obj = pEnt->extensionDictionary())
                    != AcDbObjectId::kNull)
                {
                    AcDbDictionary *pDict = NULL;
                    acdbOpenObject(pDict, obj, AcDb::kForWrite);
                    if (pDict) {
                        pDict->setTreatElementsAsHard(Adesk::kTrue);
                        pDict->close();
                    }
                }
                pEnt->close();
            }
        }
    }

    delete pIT;
    pBTR->close();

    if (list.isEmpty()) {
        acedAlert( _T("No entities found in model space of DWG") );
        return;
    }

    AcDbDatabase *pTempDb;

    if (Acad::eOk != extDatabase.wblock( pTempDb, list, AcGePoint3d::kOrigin ))
    {
        acedAlert( _T("wblock failed!") );
        return;
    }
    if (Acad::eOk != acdbHostApplicationServices()->workingDatabase()
        ->insert( AcGeMatrix3d::kIdentity, pTempDb ))
        acedAlert( _T("insert failed!") );

    delete pTempDb;
}


// append - append an opened entity to model space in the database:
//
Adesk::Boolean
append( AcDbEntity* pEntity, AcDbObjectId& objId )
{
	AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase();
	AcDbBlockTable* pBlockTable = NULL;
	AcDbBlockTableRecord* pBlockRec = NULL;

	if( pDb == NULL ) {
		acedAlert( _T("No database!") );
		return Adesk::kFalse;
	}
	if( pDb->getSymbolTable( pBlockTable, AcDb::kForRead ) != Acad::eOk ) {
		acedAlert( _T("Failed to get block table!") );
		return Adesk::kFalse;
	}
	if( pBlockTable->getAt( ACDB_MODEL_SPACE, pBlockRec, AcDb::kForWrite )
		!= Acad::eOk )
	{
		acedAlert( _T("Failed to get block table record!") );
		pBlockTable->close();
		return Adesk::kFalse;
	}
	if( pBlockRec->appendAcDbEntity( objId, pEntity ) != Acad::eOk ) {
		acedAlert( _T("Failed to append entity!") );
		pBlockTable->close();
		pBlockRec->close();
		return Adesk::kFalse;
	}
	pBlockRec->close();
	pBlockTable->close();
	return Adesk::kTrue;
}

// append - append an opened entity to model space in the database:
//
Adesk::Boolean
append( AcDbEntity* pEntity )
{
	AcDbObjectId objId;
	return append( pEntity, objId );
}


AcDbObjectId
getBlockId( const TCHAR* pBlockName )
{
    AcDbDatabase* pCurDwg = acdbHostApplicationServices()->workingDatabase();
    if (NULL == pCurDwg)
        return AcDbObjectId( 0 );
    AcDbBlockTable* pBlockTable;
    if (Acad::eOk != pCurDwg->getSymbolTable( pBlockTable, AcDb::kForRead ))
        return AcDbObjectId( 0 );
    AcDbObjectId returnId;
    pBlockTable->getAt( pBlockName, returnId );
    pBlockTable->close();
    return returnId;
}

// getFile
//
// Returns: RTNORM if sucessfully
//          RTERROR if failure
//          The selected file in pResult
//
int
getFile(
    // input:
    const TCHAR* pCmdAsk,  // prompt for command line mode
    const TCHAR* pDiaAsk,  // prompt for dialog box mode
    const TCHAR* pExt,     // file extension
    // output:
    TCHAR* pResult)        // selected file returned to the caller.
                          // must be an allocated buffer!
{
    TCHAR tmpResult[134];
    struct resbuf *pRb = NULL;
    int res = RTERROR;
    TCHAR drive[_MAX_DRIVE], dir[_MAX_DIR];
    TCHAR fname[_MAX_FNAME], ext[_MAX_EXT];

    // command line argument?
    //
    if ( NULL != (pRb = acedGetArgs()) && RTSTR == pRb->restype) {
        // yes!
        //
        _tcscpy( tmpResult, pRb->resval.rstring );
        // continue later: look if acedFindFile finds the file!
        //
        res = RTNORM;
    }
    else {
        // no command line argument
        //
        struct resbuf fileDia;

        // is "filedia" set to 1?
        //
        acedGetVar( _T("filedia"), &fileDia );
        if (1 == fileDia.resval.rint) {
            // yes, display dialog box
            //
            struct resbuf fileRes;

            res = acedGetFileD( pDiaAsk, NULL, pExt, 0, &fileRes );
            if (RTNORM != res) return res;
            if (RTSTR == fileRes.restype) {
                // user selected valid file
                //
                _tcscpy( pResult, fileRes.resval.rstring );
                free( fileRes.resval.rstring );
                return RTNORM;
            }
        }
        // Prompt at command line required. Either
        // filedia = 0, or "type it" button in dialog was pressed.
        //
        res = acedGetString( 0, pCmdAsk, tmpResult );
        if (RTNORM != res) return res;
    }
    // look if there's already the file extension attached
    //
    _tsplitpath( tmpResult, drive, dir, fname, ext );
    // if not, append file extension
    //
    if (_tcsicmp( ext, pExt ) != 0)
        _tmakepath( tmpResult, drive, dir, fname, pExt );

    // look if file exists (only if not in dialog mode)
    //
    res = acedFindFile( tmpResult, pResult );
    if (RTNORM != res)
        acutPrintf( _T("\nUnable to open %s.\n"), tmpResult );
    return res;
}

const TCHAR* cstrCommandGroup = _T("ASDKCLONES_COMMANDS");

static void
initApp(void)
{
  acedRegCmds->addCommand(cstrCommandGroup, _T("CLONE1"), _T("CLONE1"), ACRX_CMD_MODAL, clone1);
  acedRegCmds->addCommand(cstrCommandGroup, _T("CLONE2"), _T("CLONE2"), ACRX_CMD_MODAL, clone2);
  acedRegCmds->addCommand(cstrCommandGroup, _T("CLONE3"), _T("CLONE3"), ACRX_CMD_MODAL, clone3);
}

static void
unloadApp(void)
{
  acedRegCmds->removeGroup(cstrCommandGroup);
}


// acrxEntryPoint
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
  }
  return AcRx::kRetOK;
}
