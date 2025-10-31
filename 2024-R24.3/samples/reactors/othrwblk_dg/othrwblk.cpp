//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
// othrwblk.cpp
// 
// Example showing correct and incorrect ways to use
// AcEditorReactor::otherWblock to get the destination database's
// Model Space BTR ObjectId


#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "rxregsvc.h"
#include "aced.h"
#include "dbsymtb.h"
#include "dbidmap.h"
#include "adslib.h"
#include "tchar.h"




class AsdkWblockReactor : public AcEditorReactor 
// This reactor implements only the otherWblock notification 
// reaction from AcEditorReactor.
//
{
  public:

    virtual void otherWblock(AcDbDatabase*,
                             AcDbIdMapping&,
                             AcDbDatabase*);
};

#ifdef WRONGWAY

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

void
AsdkWblockReactor::otherWblock(AcDbDatabase*  pDestDb,
                               AcDbIdMapping& idMap,
                               AcDbDatabase*  pSrcDb)
{
    AcDbBlockTable       *pDestBlockTable;
    AcDbBlockTableRecord *pDestBTR;

    pDestDb->getSymbolTable(pDestBlockTable, AcDb::kForRead);
    pDestBlockTable->getAt(ACDB_MODEL_SPACE,
        pDestBTR, AcDb::kForRead);
    pDestBlockTable->close();

    // Now pDestBTR is pointing to pSrcDb database's Model
    // Space not to the destination database's Model Space!
    // The code above is not correct!

// END CODE APPEARING IN SDK DOCUMENT.

    acutPrintf(_T("\nIncorrect destination BTR's ObjectId is \t\t%Ld"),
        pDestBTR->objectId().asOldId());
    pDestBTR->close();

    AcDbBlockTable *pSrcBlockTable;
    AcDbObjectId    srcModelSpaceId;
    pSrcDb->getSymbolTable(pSrcBlockTable, AcDb::kForRead);
    pSrcBlockTable->getAt(ACDB_MODEL_SPACE,
        srcModelSpaceId);
    pSrcBlockTable->close();

    acutPrintf(_T("\nSource Database's Model Space BTR's ObjectId is \t%Ld"),
        srcModelSpaceId.asOldId());
}

#else

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

void
AsdkWblockReactor::otherWblock(AcDbDatabase*  pDestDb,
                               AcDbIdMapping& idMap,
                               AcDbDatabase*  pSrcDb)
{
    // If this is not a fastWblock, then to find the destination Model
    // Space,  you must look it up in the ID map.  If it is a fastWblock,
    // then the source and destination are the same object, but with
    // differnt objectIds and the destination objectId is not yet
    // valid, so it cannot be used to access the object.
    //
    AcDbBlockTable *pSrcBlockTable;
    pSrcDb->getSymbolTable(pSrcBlockTable, AcDb::kForRead);

    AcDbObjectId srcModelSpaceId;
    pSrcBlockTable->getAt(ACDB_MODEL_SPACE,
        srcModelSpaceId);
    pSrcBlockTable->close();

    AcDbObjectId destId;
    if (pDestDb == pSrcDb) {
        // It's a fastWblock, so we use the source objectId.
        //
        destId = srcModelSpaceId;
    } else {
        AcDbIdPair idPair;
        idPair.setKey(srcModelSpaceId);
        idMap.compute(idPair);
        destId = idPair.value();
    }

    AcDbBlockTableRecord *pDestBTR;
    acdbOpenAcDbObject((AcDbObject*&)pDestBTR,
        destId, AcDb::kForRead, Adesk::kTrue);

// END CODE APPEARING IN SDK DOCUMENT.

    AcDbIdPair idPair;
    idPair.setKey(srcModelSpaceId);
    idMap.compute(idPair);

    // idPair.value() is the correct destination objectId for any
    // wblock.  But, for a fastWblock, it cannot be used to access
    // the destination object until the wblock operation is over.

    acutPrintf(_T("\nCorrect destination BTR's ObjectId is:\t\t%Ld"),
        idPair.value().asOldId());
    pDestBTR->close();

    // Incorrect way done here so that the wrong value can be
    // compared to the correct value
    //
    AcDbBlockTable *pDestBlockTable;
    pDestDb->getSymbolTable(pDestBlockTable, AcDb::kForRead);
    pDestBlockTable->getAt(ACDB_MODEL_SPACE,
        pDestBTR, AcDb::kForRead);
    pDestBlockTable->close();

	acutPrintf(_T("\nIncorrect destination BTR's ObjectId is \t\t%Ld"),
        pDestBTR->objectId().asOldId());
    
	pDestBTR->close();

    // source database Model Space BTR's ObjectId is shown to
    // demonstrate that this is what the incorrect method gets
    //
    pSrcDb->getSymbolTable(pSrcBlockTable, AcDb::kForRead);
    pSrcBlockTable->getAt(ACDB_MODEL_SPACE,
        srcModelSpaceId);
    pSrcBlockTable->close();

    acutPrintf(_T("\nSource Database's Model Space BTR's ObjectId is \t%Ld"),
        srcModelSpaceId.asOldId());
}

#endif /* WRONGWAY */

// Arx entry point function
//
extern "C" AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode msg, void* appId)
{
    static AsdkWblockReactor *pEdReac = NULL;

    switch (msg) {
    case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(appId);
		acrxDynamicLinker->registerAppMDIAware(appId);
            
        if (!pEdReac)
            pEdReac = new AsdkWblockReactor();
        acedEditor->addReactor(pEdReac);
        break;
    case AcRx::kUnloadAppMsg:
        acedEditor->removeReactor(pEdReac);
        delete pEdReac;
        pEdReac = NULL;
    }
    return AcRx::kRetOK;
}
