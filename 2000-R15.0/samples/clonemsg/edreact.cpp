// (C) Copyright 1996,1998 by Autodesk, Inc. 
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
//  edreact.cpp


#include "acdb.h"             // acdb definitions
#include "adslib.h"           // ads defs
#include "dbents.h"           // "old" entities
#include "aced.h"             // aced stuff
#include "dbdict.h"           // dictionaries
#include "dbsymtb.h"          // symboltables
#include "acgi.h"             // graphical definitions
#include "dbidmap.h"          // id mapping
#include "edreact.h"
#include "mkrenti.h"
#include "arxutils.h"


Adesk::Boolean
isCloned( const AcDbObjectId&  refId,
          const AcDbIdMapping& idMap )
{
    AcDbIdPair pair;
    pair.setKey( refId );
    return idMap.compute( pair ) && pair.value() != 0;
}


// editor reactor EditorReactor
//
static AsdkEditorReactor* pEditorReactor = NULL; // MDI Safe

// call this function to
// create the reactor EditorReactor
//
void
create_EditorReactor()
{
  if (NULL == pEditorReactor)
      pEditorReactor = new AsdkEditorReactor();
  acedEditor->addReactor( pEditorReactor );
}

// call this function to
// erase the reactor EditorReactor
//
void
erase_EditorReactor()
{
  acedEditor->removeReactor(pEditorReactor);
  delete pEditorReactor;
}

void
AsdkEditorReactor::beginDeepCloneXlation(AcDbIdMapping&     idMap,
                                     Acad::ErrorStatus* pRetStatus)
{
#if defined( XLATE ) && !defined( DIRECT )
    AcDbDatabase *pOrigDb, *pDestDb;
    idMap.origDb( pOrigDb );
    idMap.destDb( pDestDb );

    AcDbIdMappingIter iter(idMap);
    AcDbIdPair idPair;
    int isDictCloned = 0;

    for (iter.start(); !iter.done(); iter.next()) {
	    if (!iter.getMap(idPair))
	        continue;
	    if (!idPair.isCloned())
            continue;

        AsdkMkrEntity *pMkrEnt;
        if (Acad::eOk != acdbOpenObject( pMkrEnt, idPair.key(), AcDb::kForRead ))
            continue;
        AcDbObjectId refId = pMkrEnt->id();

#ifdef NOD
        // is the dictionary cloned?
        //
        pMkrEnt->close();

        // no action required when using hard pointer id's
#ifndef HARDPOINTER
        if (!isDictCloned && AcDb::kDcWblock == idMap.deepCloneContext())
        {
            AcDbObjectId srcId = getDictId( /*NOXLATE*/"ASDK_MYDICT", pOrigDb );
            AcDbObjectId dstId;
            AcDbObject* pDestDict = cloneFromId( srcId );
            if (NULL == pDestDict)
                continue;
            pDestDb->addAcDbObject( dstId, pDestDict );
            pDestDict->close();
            idMap.assign( AcDbIdPair( srcId, dstId, Adesk::kTrue ) );
            isDictCloned = 1;
        }
#endif  // !HARDPOINTER

#else
        AcDbObjectId srcId = getExtDictId( pMkrEnt, /*NOXLATE*/"ASDK_MYDICT" );
        pMkrEnt->close();
        AcDbObjectId dstId;
        AcDbObject* pDestDict = cloneFromId( srcId );
        if (NULL == pDestDict)
            continue;
        pDestDb->addAcDbObject( dstId, pDestDict );
        pDestDict->close();
        idMap.assign( AcDbIdPair( srcId, dstId, Adesk::kTrue ) );
#endif  // NOD

        // is the custom object cloned?
        //
        if (!isCloned( refId, idMap )) {
            // for soft pointer id's.
            //
            AcDbObject *pClone = cloneFromId( refId );
            if (NULL == pClone)
                continue;
            
            AcDbObjectId newId;
            if (AcDb::kDcWblock == idMap.deepCloneContext()) {
                // no action required when using hard pointer id's
#ifndef HARDPOINTER
                pDestDb->addAcDbObject( newId, pClone );
                pClone->close();
#endif  // !HARDPOINTER
            }
            else {
                AcDbDictionary *pDestDict =
                    getDict( /*NOXLATE*/"ASDK_MYDICT", AcDb::kForWrite, pDestDb );
                if (NULL == pDestDict)
                    continue;
                if (pDestDict->has( /*NOXLATE*/"MYENTRY" ))
                    pDestDict->setAt( "*", pClone, newId );
                else
                    pDestDict->setAt( /*NOXLATE*/"MYENTRY", pClone, newId );
                pDestDict->close();
                pClone->close();
            }
            idMap.assign( AcDbIdPair( refId, newId, Adesk::kTrue ) );
        }
    }
#endif  // XLATE
}
