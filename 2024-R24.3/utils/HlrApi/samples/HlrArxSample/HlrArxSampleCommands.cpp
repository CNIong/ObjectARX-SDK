//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "StdArx.h"
#include "resource.h"
#include "geassign.h"
#include "dbxutil.h"
#include "ControlsDlg.h"
#include "../../Inc/Hlr.h"



Acad::ErrorStatus postToDatabase (/*[in]*/AcDbDatabase *pDb /*=NULL*/, AcDbEntity *pEnt, AcDbObjectId &idObj) {
    //----- Purpose:
    //----- Adds an entity to the MODEL_SPACE of the database given in argument.
    //-----   * pDb:   pointer to the databse where to add the entity,
    //-----            if NULL, then the curretn database is used.
    //-----   * pEnt:  pointer to an entity instance.
    //-----   * idObj: it will contain the assign ID to the object if successfully added to the database.
    //----- Note:
    //-----   The entity object is closed while we return from that function. Only the idObj can be used after.
    assert ( pEnt != NULL ) ;

    if ( pDb == NULL )
        pDb =acdbHostApplicationServices ()->workingDatabase () ;
    //----- Get a pointer to the current drawing
    //----- and get the drawing's block table. Open it for read.
    Acad::ErrorStatus es ;
    AcDbBlockTable *pBlockTable ;
    if ( (es =pDb->getBlockTable (pBlockTable, AcDb::kForRead)) == Acad::eOk ) {
        //----- Get the Model Space record and open it for write. This will be the owner of the new line.
        AcDbBlockTableRecord *pSpaceRecord ;
        if ( (es =pBlockTable->getAt (ACDB_MODEL_SPACE, pSpaceRecord, AcDb::kForWrite)) == Acad::eOk ) {
            //----- Append pEnt to Model Space, then close it and the Model Space record.
            if ( (es =pSpaceRecord->appendAcDbEntity (idObj, pEnt)) == Acad::eOk )
                pEnt->close () ;
            pSpaceRecord->close () ;
        }
        pBlockTable->close () ;
    }
    //----- It is good programming practice to return an error status
    return (es) ;
}

// This is command 'TEST1'

// Command TEST1 ask you to select entities on the AutoCAD DWG file, and use the current
// viewport settings to hide lines. All visible resulting entities will be produced
// in Red color, and if ask for all non-visible resulting entities will be produced in Blue.
void progress1 (int percent_completed) {
    // ASM runs threaded, and this callback function gets called from a worker thread.
    // It is not possible to call aced functions such as acedSetStatusBarProgressMeterPos()
    // from a non-main thread.
}

void progress2 (int percent_completed) {
    // ASM runs threaded, and this callback function gets called from a worker thread.
    // It is not possible to call aced functions such as acedSetStatusBarProgressMeterPos()
    // from a non-main thread.
}

void progress3 (int percent_completed) {
    // ASM runs threaded, and this callback function gets called from a worker thread.
    // It is not possible to call aced functions such as acedSetStatusBarProgressMeterPos()
    // from a non-main thread.
}

void asdktest1 () {
    //----- Select the entities
    ads_name ss, en ;
    if ( acedSSGet (NULL, NULL, NULL, NULL, ss) != RTNORM )
        return ;

    //----- Append entity IDs to the collector
    int n ;
    AcDbObjectId id ;
    AsdkHlrCollector collector ;
    collector.setDeleteState (true) ;
    acedSSLength (ss, &n) ;
    for ( int i =0 ; i < n ; i++ ) {
        acedSSName (ss, i, en) ;
        acdbGetObjectId (id, en) ;
        collector.addEntity (id) ;
    }
    acedSSFree (ss) ;

    //----- Get current viewport settings
    struct resbuf rb;
    acedGetVar(ACRX_T(/*NOXLATE*/"viewdir"), &rb);
    ads_point dirPt;
    acdbUcs2Wcs (rb.resval.rpoint, dirPt, Adesk::kTrue) ;
    acedGetVar(ACRX_T(/*NOXLATE*/"target"), &rb);
    ads_point tarPt;
    acdbUcs2Wcs (rb.resval.rpoint, tarPt, Adesk::kFalse) ;

    //----- Ask if non-visible edges should be created
    int hidLines =AfxMessageBox (ACRX_T("Would you like to see hidden lines?"), MB_YESNO) ;
    int honorInt =AfxMessageBox (ACRX_T("Would you like to honor internal visibility of polyface meshes or ACIS objects?"), MB_YESNO) ;
    int meshSils =AfxMessageBox (ACRX_T("Would you like to calculate silhouettes of polyface meshes?"), MB_YESNO) ;
    int unit =AfxMessageBox (ACRX_T("Would you like to unit solid before processing?"), MB_YESNO) ;

    //----- Process hidden line removal
    AsdkHlrEngine hlr (
        asPnt3d (tarPt), asVec3d (dirPt),
        kEntity | kBlock | kSubentity | kProgress
        | (honorInt == IDYES ? kHonorInternals : 0)
        | (hidLines == IDYES ? kShowAll : 0)
        | (meshSils == IDYES ? kMeshSilhouettes : 0)
        | (unit == IDYES ? kUnite : 0)
    ) ;
    hlr.setAcisConversionProgressCallBack (progress1) ;
    hlr.setAhlProgressCallBack (progress2) ;
    hlr.setAcadConversionProgressCallBack (progress3) ;

    acedSetStatusBarProgressMeter (ACRX_T("HLR running: "), 0, 300) ;
    hlr.run (collector) ;
    acedRestoreStatusBar () ;

    //----- Assign color to the resulting entities
    //----- red for visible edges
    //----- blue for non-visible edges
    //----- yellow for internal edges
    n =collector.mOutputData.logicalLength () ;
    for (int i =0 ; i < n ; i++ ) {
        AsdkHlrData *p =collector.mOutputData [i] ;

        AcDbEntity *pEnt =p->getResultEntity () ;
        AsdkHlrData::Visibility vis =p->getVisibility () ;
        if ( vis == AsdkHlrData::kVisible ) {
            pEnt->setColorIndex (1) ; //----- Read
        } else if ( vis == AsdkHlrData::kInternallyHidden ) {
            if ( p->getHlrVisibility () == AsdkHlrData::kVisible )
                pEnt->setColorIndex (2) ; //----- Yellow
            else
                pEnt->setColorIndex (3) ; //----- Green
        } else {
            pEnt->setColorIndex (5) ; //----- Blue
        }

        if ( postToDatabase (NULL, pEnt, id) != Acad::eOk ) {
            acutPrintf (_T("Failed to add entity to current space.\n")) ;
            break ;
        }
        if ( acdbOpenAcDbEntity (pEnt, id, AcDb::kForRead) != Acad::eOk ) {
            acutPrintf (_T("Failed to open last added outputed curve.\n")) ;
            break ;
        }

        //----- Entity originator path for block reference entities
        AcDbObjectIdArray ids =p->getObjectIds () ;
        if ( ids.logicalLength () > 0 ) {
            acutPrintf (ACRX_T("\n%lx, "), pEnt->objectId ().asOldId ()) ;
            if ( p->getSubentId ().type () != AcDb::kNullSubentType )
                acutPrintf (ACRX_T("[%ld, %ld], "), p->getSubentId ().type (), p->getSubentId ().index ()) ;
            for ( int j =0 ; j < ids.logicalLength () ; j++ )
                acutPrintf (ACRX_T("%lx, "), ids.at (j).asOldId ()) ;
            AcDbObjectId id =ids.last () ;
            if ( !id.isNull () ) {
                AcDbEntity *ent =NULL ;
                acdbOpenAcDbEntity (ent, id, AcDb::kForRead) ;
                id =ent->linetypeId () ;
                ent->close () ;
                if ( pEnt->upgradeOpen () == Acad::eOk )
                pEnt->setLinetype (id) ;
            }
        }

        pEnt->close () ;
    }
}

Adesk::Boolean pickViewport (AcDbViewport *&pVp) {
    ads_point p1, p2 ;
    
    if ( acedGetPoint (NULL, ACRX_T("\nPlease enter point 1: "), p1) != RTNORM )
        return (Adesk::kFalse) ;
    if ( acedGetPoint (p1, ACRX_T("\nPlease enter point 2: "), p2) != RTNORM )
        return (Adesk::kFalse) ;
    acdbUcs2Wcs (p1, p1, Adesk::kFalse ) ;
    acdbUcs2Wcs (p2, p2, Adesk::kFalse ) ;

    int frontClip =AfxMessageBox (ACRX_T("Would you like to clip at the front?"), MB_YESNO) ;
    int backClip =AfxMessageBox (ACRX_T("Would you like to clip at the back?"), MB_YESNO) ;
    
    pVp =new AcDbViewport ;
    pVp->setViewTarget (asPnt3d (p2)) ;
    pVp->setViewDirection (asPnt3d (p1) - asPnt3d (p2)) ;

    pVp->setFrontClipDistance (asPnt3d (p1).distanceTo (asPnt3d (p2))) ;
    pVp->setBackClipDistance (0) ;
    
    acutPrintf (ACRX_T("\nFront Clipping is %d"), pVp->isFrontClipOn ()) ;
    if ( frontClip == IDYES )
        pVp->setFrontClipOn () ;
    acutPrintf (ACRX_T("\nFront Clipping is %d"), pVp->isFrontClipOn ()) ;
    
    acutPrintf (ACRX_T("\nBack Clipping is %d"), pVp->isBackClipOn ()) ;
    if ( backClip == IDYES )
        pVp->setBackClipOn () ;
    acutPrintf(ACRX_T("\nBack Clipping is %d"), pVp->isBackClipOn ()) ;
    
    return (Adesk::kTrue) ;
}

// This is command 'TEST2'

// Command TEST2 ask you to select entities on the AutoCAD DWG file, for a virtual viewport,
// and for HLR controls you want to apply to the HLR engine. Then the color of each resulting
// entities will depend of the originator entity. The function is going throw block definition
// to find the original entity which produced the edges, and assign its color to the edges.

void asdktest2 () {
    //----- Select the entities
    ads_name ss, en ;
    if ( acedSSGet (NULL, NULL, NULL, NULL, ss) != RTNORM )
        return ;

    //----- Append entity IDs to the collector
    int n ;
    AcDbObjectId id ;
    AsdkHlrCollector collector ;
    acedSSLength (ss, &n) ;
    for ( int i =0 ; i < n ; i++ ) {
        acedSSName (ss, i, en) ;
        acdbGetObjectId (id, en) ;
        collector.addEntity (id) ;
    }
    acedSSFree (ss) ;

    //----- Display a dialog box to select HLR controls, the user wants to apply to the HLR engine
    AfxSetResourceHandle (_hdllInstance) ;
    CControlsDlg dlg ;
    dlg.mnControls =kProject | kEntity | kBlock | kHonorInternals ;
    if ( dlg.DoModal () != IDOK ) {
        AfxSetResourceHandle (acedGetAcadResourceInstance ()) ;
        return ;
    }
    AfxSetResourceHandle (acedGetAcadResourceInstance ()) ;

    int control =dlg.mnControls ;
    acutPrintf (ACRX_T("\nAbout to call hidden Line calculation")) ;
    acutPrintf (ACRX_T("\nCalling with %d Entities"), collector.getInputEntityIds ().logicalLength ()) ;
    acutPrintf (ACRX_T("\nkProject %s "), control & kProject ? ACRX_T("On") : ACRX_T("Off")) ;
    acutPrintf (ACRX_T("\nkShowAll %s "), control & kShowAll ? ACRX_T("On") : ACRX_T("Off")) ;
    acutPrintf (ACRX_T("\nkEntity %s "), control & kEntity  ? ACRX_T("On") : ACRX_T("Off")) ;
    acutPrintf (ACRX_T("\nkBlock %s "), control & kBlock  ? ACRX_T("On") : ACRX_T("Off")) ;
    acutPrintf (ACRX_T("\nkSubentity %s "), control & kSubentity  ? ACRX_T("On") : ACRX_T("Off")) ;
    acutPrintf (ACRX_T("\nkHideTangents %s "), control & kHideTangents  ? ACRX_T("On") : ACRX_T("Off")) ;
    acutPrintf (ACRX_T("\nkCleanup %s "), control & kCleanup  ? ACRX_T("On") : ACRX_T("Off")) ;
    acutPrintf (ACRX_T("\nkIsolines %s "), control & kIsolines  ? ACRX_T("On") : ACRX_T("Off")) ;
    acutPrintf (ACRX_T("\nkUnite %s "), control & kUnite  ? ACRX_T("On") : ACRX_T("Off")) ;
    acutPrintf (ACRX_T("\nkReuse %s "), control & kReuse  ? ACRX_T("On") : ACRX_T("Off")) ;
    acutPrintf (ACRX_T("\nkProgress %s "), control & kProgress  ? ACRX_T("On") : ACRX_T("Off")) ;
    acutPrintf (ACRX_T("\nkHandlePoints %s "), control & kHandlePoints  ? ACRX_T("On") : ACRX_T("Off")) ;
    acutPrintf (ACRX_T("\nkHonorInternals %s "), control & kHonorInternals ? ACRX_T("On") : ACRX_T("Off")) ;
    acutPrintf (ACRX_T("\nkMeshSilhouettes %s "), control & kMeshSilhouettes ? ACRX_T("On") : ACRX_T("Off")) ;
    
    //----- Ask for virtual viewport settings
    AcDbViewport *pVp =NULL ;
    if ( !pickViewport (pVp) )
        return ;

    //----- Process hidden line removal
    AsdkHlrEngine hlr (pVp, control) ;
    hlr.run (collector) ;
    delete pVp ;

    //----- The following code will collect the color of the originator entity of an edge
    //----- and will assign it to the resulting entity.
    actrTransactionManager->startTransaction () ;

    int nOutput =collector.mOutputData.logicalLength () ;
    acutPrintf (ACRX_T("\nHlr returned %d curves"), nOutput) ;
    for ( int j =0 ; j < nOutput ; j++ ) {
        AsdkHlrData *pResult =collector.mOutputData [j] ;

        AcDbEntity *pResultEntity =pResult->getResultEntity () ;
        AcDbObjectId id ;
        if ( postToDatabase (NULL, pResultEntity, id) != Acad::eOk ) {
            acutPrintf (_T("Failed to add entity to current space.\n")) ;
            break ;
        }
        actrTransactionManager->getObject ((AcDbObject *&)pResultEntity, id, AcDb::kForWrite) ;

        AcDbObjectIdArray ids =pResult->getObjectIds () ;
        int last =ids.logicalLength () - 1 ;
        AcCmColor color ;
        AcDbObjectId layerId ;
        color.setColorIndex (0) ;
        while ( last >= 0 && color.colorIndex () == 0 ) {
            AcDbObjectId innerId =ids.at (last) ;
            AcDbObject *pObj ;
            actrTransactionManager->getObject (pObj, innerId, AcDb::kForRead) ;
            AcDbEntity *pEnt =AcDbEntity::cast (pObj) ;

            color =pEnt->color () ;
            layerId =pEnt->layerId () ;
            last-- ;
        }
        if ( layerId != AcDbObjectId::kNull ) {
            pResultEntity->setColor (color) ;
            pResultEntity->setLayer (layerId) ;
        } else {
            AcDbEntity *pEnt =pResult->getEntity () ;
            if ( pEnt != NULL ) {
                pResultEntity->setColor (pEnt->color ()) ;
                pResultEntity->setLayer (pEnt->layer ()) ;
            }
        }
        pResultEntity->close () ;
    }

    actrTransactionManager->endTransaction();
}

// This is command 'TEST3'

// This command demonstrates the thing as command 'TEST1' except that it works on
// memory only entities. Memory only entities, and database resident entity can be mixed
// together in the collector object.

void asdktest3 () {
    //----- Create a line and a circle (memory only)
    AcDbLine *pLine =new AcDbLine (AcGePoint3d (), AcGePoint3d (100, 100, -100)) ;
    AcDbCircle *pCircle =new AcDbCircle (AcGePoint3d (50, 50, 0), AcGeVector3d (0, 0, 1) , 25.0) ;

    //----- Create a region from the circle
    AcDbVoidPtrArray arr1, arr2 ;
    arr1.append (pCircle) ;
    AcDbRegion::createFromCurves (arr1, arr2) ;
    AcDbRegion *pRegion =(AcDbRegion *)arr2.at (0) ;
    delete pCircle ;

    //----- Add the line and the region objects to the collector
    //----- NB: Remember those object are memory objects only
    AsdkHlrCollector collector ;
    collector.setDeleteState (true) ;
    collector.addEntity (pLine) ;
    collector.addEntity (pRegion) ;

    //----- Process hidden line removal
    AsdkHlrEngine hlr (AcGePoint3d (50, 50,0), AcGeVector3d (0, 0, 1), kEntity | kBlock | kShowAll | kProject | kHonorInternals) ;
    hlr.run (collector) ;

    //----- To easily see the result, we do append resulting entities to the current database
    //----- and use the color convention used in command 'TEST1'
    int n =collector.mOutputData.logicalLength () ;
    for ( int i =0 ; i < n ; i++ ) {
        AsdkHlrData *p =collector.mOutputData [i] ;

        AcDbEntity *pEnt =p->getResultEntity () ;
        AsdkHlrData::Visibility vis =p->getVisibility () ;
        if ( vis == AsdkHlrData::kVisible )
            pEnt->setColorIndex (1) ;
        else
            pEnt->setColorIndex (5) ;
        AcDbObjectId id ;
        if ( postToDatabase (NULL, pEnt, id) != Acad::eOk ) {
            acutPrintf (_T("Failed to add entity to current space.\n")) ;
            break ;
        }

        //----- Entity originator path
        AcDbObjectIdArray ids =p->getObjectIds () ;
        if ( ids.logicalLength () > 0 ) {
            acutPrintf (ACRX_T("\n%ld, "), pEnt->objectId ().asOldId ()) ;
            for ( int j =0 ; j < ids.logicalLength () ; j++ ) {
                acutPrintf (ACRX_T("%ld, "), ids.at (j).asOldId ()) ;
            }
        }

        pEnt->close () ;
    }
}

// This is command 'TEST4'

// This command demonstrates the use of kCleanup / kReuse flags
void AddEntityToLayer (AsdkHlrCollector &collector, ACHAR *layerName) {
    //----- Check layer
    if ( layerName != NULL && *layerName != ACRX_T('\0') ) {
        AcDbDatabase *pDb =acdbHostApplicationServices ()->workingDatabase () ;
        AcDbLayerTable *pLayerTable ;
        pDb->getLayerTable (pLayerTable, AcDb::kForRead) ;
        if ( !pLayerTable->has (layerName) ) {
            AcDbLayerTableRecord *pLayerRecord =new AcDbLayerTableRecord ;
            pLayerRecord->setName (layerName) ;
            pLayerTable->upgradeOpen () ;
            pLayerTable->add (pLayerRecord) ;
            pLayerTable->downgradeOpen () ;
            pLayerRecord->close () ;
            pLayerTable->close () ;
            applyCurDwgLayerTableChanges () ;
        } else {
            pLayerTable->close () ;
        }
    } else {
        layerName =NULL ;
    }
    //----- Assign color to the resulting entities
    //----- red for visible edges
    //----- blue for non-visible edges
    //----- yellow for internal edges
    int n =collector.mOutputData.logicalLength () ;
    for ( int i =0 ; i < n ; i++ ) {
        AsdkHlrData *p =collector.mOutputData [i] ;

        AcDbEntity *pEnt =p->getResultEntity () ;
        AsdkHlrData::Visibility vis =p->getVisibility () ;
        if ( vis == AsdkHlrData::kVisible ) {
            pEnt->setColorIndex (1) ; //----- Read
        } else if ( vis == AsdkHlrData::kInternallyHidden ) {
            if ( p->getHlrVisibility () == AsdkHlrData::kVisible )
                pEnt->setColorIndex (2) ; //----- Yellow
            else
                pEnt->setColorIndex (3) ; //----- Green
        } else {
            pEnt->setColorIndex (5) ; //----- Blue
        }
        if ( layerName != NULL )
            pEnt->setLayer (layerName) ;
        AcDbObjectId id ;
        if ( postToDatabase (NULL, pEnt, id) != Acad::eOk ) {
            acutPrintf (_T("Failed to add entity to current space.\n")) ;
            break ;
        }

        //----- Entity originator path for block reference entities
        AcDbObjectIdArray ids =p->getObjectIds () ;
        if ( ids.logicalLength () > 0 ) {
            acutPrintf (ACRX_T("\n%ld, "), pEnt->objectId ().asOldId ()) ;
            for ( int j =0 ; j < ids.logicalLength () ; j++ ) {
                acutPrintf (ACRX_T("%ld, "), ids.at (j).asOldId ()) ;
            }
        }

        pEnt->close () ;
    }
}

void asdktest4 () {
    //----- Select the entities
    ads_name ss, en ;
    if ( acedSSGet (NULL, NULL, NULL, NULL, ss) != RTNORM )
        return ;

    //----- Append entity IDs to the collector
    int n ;
    AcDbObjectId id ;
    AsdkHlrCollector collector ;
    acedSSLength (ss, &n) ;
    for ( int i =0 ; i < n ; i++ ) {
        acedSSName (ss, i, en) ;
        acdbGetObjectId (id, en) ;
        collector.addEntity (id) ;
    }
    acedSSFree (ss) ;

    //----- Get current viewport settings
    struct resbuf rb;
    acedGetVar(ACRX_T(/*NOXLATE*/"target"), &rb);
    ads_point tarPt;
    acdbUcs2Wcs (rb.resval.rpoint, tarPt, Adesk::kFalse) ;

    //----- Ask if non-visible edges should be created
    int hidLines =AfxMessageBox (ACRX_T("Would you like to see hidden lines?"), MB_YESNO) ;
    int honorInt =AfxMessageBox (ACRX_T("Would you like to honor internal visibility of polyface meshes or ACIS objects?"), MB_YESNO) ;
    int meshSils =AfxMessageBox (ACRX_T("Would you like to calculate silhouettes of polyface meshes?"), MB_YESNO) ;
    int unit =AfxMessageBox (ACRX_T("Would you like to unit solid before processing?"), MB_YESNO) ;

    //----- *** First view will be front view ***

    //----- Process hidden line removal
    AsdkHlrEngine hlrFront (
        asPnt3d (tarPt), AcGeVector3d (0, -1, 0),//AcGeVector3d (0, 0, -1),
        kProject| kEntity | kBlock | kReuse //----- Do not use 'kCleanup'
        | (honorInt == IDYES ? kHonorInternals : 0)
        | (hidLines == IDYES ? kShowAll : 0)
        | (meshSils == IDYES ? kMeshSilhouettes : 0)
        | (unit == IDYES ? kUnite : 0)
    ) ;
    hlrFront.run (collector) ;
    AddEntityToLayer (collector, ACRX_T("FontView")) ;

    //----- *** Second view will be left view ***

    //----- Process hidden line removal

    AsdkHlrEngine hlrLeft (
        asPnt3d (tarPt), AcGeVector3d (1, 0, 0),//, AcGeVector3d (1, 0, 0),
        kProject| kEntity | kBlock | kReuse //----- Do not use 'kCleanup'
        | (honorInt == IDYES ? kHonorInternals : 0)
        | (hidLines == IDYES ? kShowAll : 0)
        | (meshSils == IDYES ? kMeshSilhouettes : 0)
        | (unit == IDYES ? kUnite : 0)
    ) ;
    hlrLeft.run (collector) ;
    AddEntityToLayer (collector, ACRX_T("LeftView")) ;

    //----- *** Third view will be top view ***

    //----- Process hidden line removal

    AsdkHlrEngine hlrTop (
        asPnt3d (tarPt), AcGeVector3d (0, 0, 1),//, AcGeVector3d (0, -1, 0),
        kProject| kEntity | kBlock | kReuse //----- Do not use 'kCleanup'
        | (honorInt == IDYES ? kHonorInternals : 0)
        | (hidLines == IDYES ? kShowAll : 0)
        | (meshSils == IDYES ? kMeshSilhouettes : 0)
        | (unit == IDYES ? kUnite : 0)
    ) ;
    hlrTop.run (collector) ;
    AddEntityToLayer (collector, ACRX_T("TopView")) ;
}

// This is command 'TEST5'

// Command TEST5 ask you to select entities on the AutoCAD DWG file, for a virtual viewport,
// and for HLR controls you want to apply to the HLR engine. Then the color of each resulting
// entities will depend of the originator entity. The function is going throw block definition
// to find the original entity which produced the edges, and assign its color to the edges.
// Its like test2, but works with clipping

void asdktest5 () {
    //----- Select the entities
    ads_name ss, en ;
    if ( acedSSGet (NULL, NULL, NULL, NULL, ss) != RTNORM )
        return ;

    //----- Append entity IDs to the collector
    int n ;
    AcDbObjectId id ;
    AsdkHlrCollector collector ;
    acedSSLength (ss, &n) ;
    for ( int i =0 ; i < n ; i++ ) {
        acedSSName (ss, i, en) ;
        acdbGetObjectId (id, en) ;
        collector.addEntity (id) ;
    }
    acedSSFree (ss) ;

    //----- Display a dialog box to select HLR controls, the user wants to apply to the HLR engine
    AfxSetResourceHandle (_hdllInstance) ;
    CControlsDlg dlg ;
    dlg.mnControls =kProject | kEntity | kBlock | kHonorInternals ;
    if ( dlg.DoModal () != IDOK ) {
        AfxSetResourceHandle (acedGetAcadResourceInstance ()) ;
        return ;
    }
    AfxSetResourceHandle (acedGetAcadResourceInstance ()) ;

    int control =dlg.mnControls ;
    acutPrintf (ACRX_T("\nAbout to call hidden Line calculation")) ;
    acutPrintf (ACRX_T("\nCalling with %d Entities"), collector.getInputEntityIds ().logicalLength ()) ;
    acutPrintf (ACRX_T("\nkProject %s "), control & kProject ? ACRX_T("On") : ACRX_T("Off")) ;
    acutPrintf (ACRX_T("\nkShowAll %s "), control & kShowAll ? ACRX_T("On") : ACRX_T("Off")) ;
    acutPrintf (ACRX_T("\nkEntity %s "), control & kEntity  ? ACRX_T("On") : ACRX_T("Off")) ;
    acutPrintf (ACRX_T("\nkBlock %s "), control & kBlock  ? ACRX_T("On") : ACRX_T("Off")) ;
    acutPrintf (ACRX_T("\nkSubentity %s "), control & kSubentity  ? ACRX_T("On") : ACRX_T("Off")) ;
    acutPrintf (ACRX_T("\nkHideTangents %s "), control & kHideTangents  ? ACRX_T("On") : ACRX_T("Off")) ;
    acutPrintf (ACRX_T("\nkCleanup %s "), control & kCleanup  ? ACRX_T("On") : ACRX_T("Off")) ;
    acutPrintf (ACRX_T("\nkIsolines %s "), control & kIsolines  ? ACRX_T("On") : ACRX_T("Off")) ;
    acutPrintf (ACRX_T("\nkUnite %s "), control & kUnite  ? ACRX_T("On") : ACRX_T("Off")) ;
    acutPrintf (ACRX_T("\nkReuse %s "), control & kReuse  ? ACRX_T("On") : ACRX_T("Off")) ;
    acutPrintf (ACRX_T("\nkProgress %s "), control & kProgress  ? ACRX_T("On") : ACRX_T("Off")) ;
    acutPrintf (ACRX_T("\nkHandlePoints %s "), control & kHandlePoints  ? ACRX_T("On") : ACRX_T("Off")) ;
    acutPrintf (ACRX_T("\nkHonorInternals %s "), control & kHonorInternals ? ACRX_T("On") : ACRX_T("Off")) ;
    acutPrintf (ACRX_T("\nkMeshSilhouettes %s "), control & kMeshSilhouettes ? ACRX_T("On") : ACRX_T("Off")) ;
    
    //----- Ask for virtual viewport settings
    AcDbViewport *pVp =NULL ;
    if ( !pickViewport (pVp) )
        return ;

    //----- Process hidden line removal
    AsdkHlrEngine hlr (pVp, control) ;
    hlr.run (collector) ;
    delete pVp ;

    //----- The following code will collect the color of the originator entity of an edge
    //----- and will assign it to the resulting entity.
    actrTransactionManager->startTransaction () ;

    int nOutput =collector.mOutputData.logicalLength () ;
    acutPrintf (ACRX_T("\nHlr returned %d curves"), nOutput) ;
    for ( int j =0 ; j < nOutput ; j++ ) {
        AsdkHlrData *pResult =collector.mOutputData [j] ;

        AcDbEntity *pResultEntity =pResult->getResultEntity () ;
        AcDbObjectId id ;
        if ( postToDatabase (NULL, pResultEntity, id) != Acad::eOk ) {
            acutPrintf (_T("Failed to add entity to current space.\n")) ;
            break ;
        }

        actrTransactionManager->getObject ((AcDbObject *&)pResultEntity, id, AcDb::kForWrite) ;

        AcDbObjectIdArray ids =pResult->getObjectIds () ;
        int last =ids.logicalLength () - 1 ;
        AcCmColor color ;
        AcDbObjectId layerId ;
        color.setColorIndex (0) ;
        while ( last >= 0 && color.colorIndex () == 0 ) {
            AcDbObjectId innerId =ids.at (last) ;
            AcDbObject *pObj ;
            actrTransactionManager->getObject (pObj, innerId, AcDb::kForRead) ;
            AcDbEntity *pEnt =AcDbEntity::cast (pObj) ;

            color =pEnt->color () ;
            layerId =pEnt->layerId () ;
            last-- ;
        }
        if ( layerId != AcDbObjectId::kNull ) {
            pResultEntity->setColor (color) ;
            pResultEntity->setLayer (layerId) ;
        } else {
            AcDbEntity *pEnt =pResult->getEntity () ;
            if ( pEnt != NULL ) {
                pResultEntity->setColor (pEnt->color ()) ;
                pResultEntity->setLayer (pEnt->layer ()) ;
            }
        }
        pResultEntity->close () ;
    }

    actrTransactionManager->endTransaction();
}

// This is command 'TEST6'

// This command is a test command for create an ACIS BODY from triangles

void asdktest6 () {
    int nPoints =8 ;
    int nTriangles =12 ;
    int nIndices =3 * nTriangles ;

    double p [] ={
        0, 0, 0,
        1, 0, 0,
        1, 1, 0,
        0, 1, 0,
        0, 0, 1,
        1, 0, 1,
        1, 1, 1,
        0, 1, 1
    } ;

    int i [] ={
        0, 1, 5,    0, 5, 4,
        1, 6, 5,    1, 2, 6,
        4, 5, 6,    4, 6, 7,
        7, 0, 4,    7, 3, 0,
        2, 0, 3,    2, 1, 0,
        7, 6, 3,    6, 2, 3
    } ;

    AcGeIntArray indices (nIndices) ;
    indices.setLogicalLength (nIndices) ;
    indices.setPhysicalLength (nIndices) ;
    memcpy (indices.asArrayPtr (), i, nIndices * sizeof (int)) ;

    AcGePoint3dArray gePts (nPoints) ;
    gePts.setLogicalLength (nPoints) ;
    gePts.setPhysicalLength (nPoints) ;
    memcpy (gePts.asArrayPtr (), p, nPoints * sizeof (AcGePoint3d)) ;

    void *acisBody =createBodyFromTriangles (gePts, indices) ;
    AcDb3dSolid *b =new AcDb3dSolid ;
    b->setASMBody(acisBody);
        
    AcDbObjectId id ;
    postToDatabase (NULL, b, id) ;
}
