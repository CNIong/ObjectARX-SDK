//
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
// ACGISAMP.CPP
//
// DESCRIPTION:   This sample application demonstrates how users can
// trap facet data of entities.  The approach to this problem is to
// rely on the AcGi code which creates the facets when an object gets
// shaded.  This application implements several objects.  A high level
// description is given below:

// 1.  AsdkCustomWorldDraw - This is a custom class derived from 
// AcGiWorldDraw.  It has default implementations for all its methods
// and contains a member data called AsdkShellData.

// 2.  AsdkCustomWorldGeometry -  This object will be used when worldDraw
// method of an entity is called.  This class stores a backpointer to the
// AsdkWorldDraw class.  All methods of this object are stubbed
// out except the ::shell method.  The shell method will trap the
// incomming data and assign it to the AsdkShellData class.
// ex.  AsdkCustomWorldGeometry->AsdkCustomWorldDraw->AsdkShellData->storeData.
// The line above indicates that the worldGeometry class has a back pointer
// to the worldDraw class whose member class AsdkShellData is used to
// store the information comming into the AsdkCustomWorldGeometry::shell function

// 3.  AsdkCustomSubEntityTraits -  Object derived off AcGiSubEntityTraits.

// 4.  AsdkShellData -  Class to store the trapped shellData.

// 5.  AsdkCustomDrawEntity -  A custom entity to draw the trapped shellData.

// 6.  The class AsdkPerDocData holds the per document used global variables 
//     colorIndex and deviation 

// 7.  The class AsdkDocGlobals is responsable for setting the correct global
//     variables when a Document-switch occures
//     The actual global variables can be accessed through the global pointer
//     named gpActualData

// COMMANDS:  The application supports the following commands:
// 1.  SetColorIndex:  Command to set the color to be assigned to the
// facets.
// 2.  SetDeviation:   Command to set the facet deviation.  A smaller value
// of deviation will create more facets and a more true representation of
// the surface data.
// 2.  FacetFaces:	Command which allows users to select faces/regions and
// then facets them.  Users can enter the shade command after this and see a
// shaded representation of the selected faces.  The overlay of the parent model
// may obscure the display in some cases, hence it is a good idea to move the
// base model before shading the window.
// An other possibility is to call the SHADE command before calling FacetFaces.

#include <stdio.h>
#include <stdlib.h>
#include "rxobject.h"
#include "rxregsvc.h" 
#include "aced.h"
#include "adslib.h"
#include "dbmain.h"
#include "dbents.h"
#include "dbsymtb.h"
#include "assert.h"
#include "adesk.h"
#include "acdb.h"
#include "custacgi.h"
#include "drawent.h"
#include "dbregion.h"
#include "dbbody.h"
#include "dbapserv.h"

//MDI support
#include "DocReactor.h"

////  SOME SUPPORT FUNCTIONS
Acad::ErrorStatus getSubEntPtr(AcDbObjectId& objId);

Acad::ErrorStatus postToDatabase(AcDbEntity* ent, AcDbObjectId& objId)
{
    //  Given an entity, this function will post it to the database
    //  in MODEL_SPACE and then return the objectId;  returns eOk if
    //  all went well.
    
    Acad::ErrorStatus	  es;
    AcDbBlockTable*		pBlockTable;
    AcDbBlockTableRecord*  pSpaceRecord;
    
    es = acdbHostApplicationServices()->workingDatabase()
        ->getSymbolTable(pBlockTable, AcDb::kForRead);

    assert(es == Acad::eOk);
    
    es = pBlockTable->getAt(ACDB_MODEL_SPACE, pSpaceRecord, AcDb::kForWrite);
    assert(es == Acad::eOk);
    
    es = pBlockTable->close();
    assert(es == Acad::eOk);
    
    es = pSpaceRecord->appendAcDbEntity(objId, ent);
    assert(es == Acad::eOk);
    
    es = ent->close();
    assert(es == Acad::eOk);
    
    es = pSpaceRecord->close();
    assert(es == Acad::eOk);
    
    return es;
}


void setColorIndex()

{
    //  Function will obtain a color index from the user.  Checks
    //  if the index has a valid value.
    
    int colorInd = gpActualData->colorIndex;
    char	prompt[300];
    sprintf(prompt,"\nEnter color index[%d]: ",gpActualData->colorIndex);    
    
    switch (ads_getint(prompt, &colorInd)) {
        
    case RTNORM:
        if (colorInd < 1 || colorInd > 256)
            ads_printf("\nColor index must be between 1-256");
        else
            gpActualData->colorIndex = colorInd;
        break;
        
    default:
        break;
    }
    
    
}

void setFacetDeviation()
{
    //  Function will obtain the desired facet deviation from the user.
    //  Restricts the user to entering a deviation between 0.005 and 0.1
    
    double facetDev = gpActualData->deviation;
    
    char	prompt[300];
    sprintf(prompt,"\nEnter facet deviation[%f]: ",gpActualData->deviation);    
    
    switch (ads_getreal(prompt, &facetDev)) {
        
    case RTNORM:
        if (facetDev < 0.005 || facetDev > 0.1)
            ads_printf("\nUnacceptable value(0.005 <= Facet Deviation <= 0.1)");
        else
            gpActualData->deviation = facetDev;
        break;
        
    default:
        break;
    }
    
}

void shadeface()
{
    //  Function will allow user to select faces of solids or regions.
    //  It will then facet the entity and create a custom entity to
    //  display the facets.
    
    AcDbObjectId	objId;
    
    //  Allows user to select a face of a solid,region or a body.
    //  It will create a region or body and return its objectId.
    while ( getSubEntPtr(objId) == Acad::eOk) 
    {
        AcDbEntity*	pEntity = NULL;
        acdbOpenAcDbEntity(pEntity, objId, AcDb::kForRead);
        
        if(NULL != pEntity)
        {
            if (!pEntity->isKindOf(AcDbRegion::desc())){
                if (!pEntity->isKindOf(AcDbBody::desc()) ){
                    ads_printf("\nNot a region or a body");
                    ads_printf("\nThe entity is %s\n", (pEntity->isA())->name());
                    pEntity->close();
                    return ;
                }
            }
            
            AsdkCustomWorldDraw	*pMyWorldDraw = new AsdkCustomWorldDraw;
            
            // Set the facet deviation value
            pMyWorldDraw->setDeviation(gpActualData->deviation);
            
            //  Call the entity's worldDraw with AsdkCustomWorldDraw
            pEntity->worldDraw(pMyWorldDraw);
            
            //  set the FaceData by entering the colorIndex.  All faces
            //  will get this color.
            pMyWorldDraw->shellData()->setFaceData(gpActualData->colorIndex);
            
            pEntity->upgradeOpen();
            pEntity->erase();		// erase the entity(body or region)
            pEntity->downgradeOpen();
            
            pEntity->close();
          
            AsdkCustomDrawEntity*	pCustEntity = new AsdkCustomDrawEntity;
            //  Obtain pointer to AsdkShellData from pMyWorldDraw and assign
            //  it to the CustomEntity which will draw facets on the screen
            pCustEntity->mpShellData =  pMyWorldDraw->shellData();
            AcDbObjectId	custOID;
            postToDatabase(pCustEntity, custOID);

            delete	 pMyWorldDraw; //  delete the worldDraw object
        }
        
    }
    //	ads_command(RTSTR,"_shade",RTNONE);
}

void initApp()
{
    AsdkCustomDrawEntity::rxInit();
    acedRegCmds->addCommand( "ACGISAMP_COMMANDS", "FACETFACES", "FACETFACES",
        ACRX_CMD_MODAL, &shadeface );
    acedRegCmds->addCommand( "ACGISAMP_COMMANDS", "SETCOLORINDEX", "SETCOLORINDEX",
        ACRX_CMD_MODAL, &setColorIndex );
    acedRegCmds->addCommand( "ACGISAMP_COMMANDS", "SETDEVIATION", "SETDEVIATION",
        ACRX_CMD_MODAL, &setFacetDeviation );
    acrxBuildClassHierarchy();
}

void unloadApp()
{
    acedRegCmds->removeGroup( "ACGISAMP_COMMANDS" );
}

extern "C" AcRx::AppRetCode acrxEntryPoint( AcRx::AppMsgCode msg, void* pkt)
{
    switch( msg ) {
    case AcRx::kInitAppMsg: 
        //An ARX application is locked to memory by default.
        //You must make the following function call to unlock it.
        acrxDynamicLinker->unlockApplication(pkt);
		//support MDI
		acrxDynamicLinker->registerAppMDIAware(pkt);
		// Create the an instance of the class AsdkDocGlobals which
		// cares on setting the right global variables when a document
		// is activated.
		// After this call the per-document global variables can be 
		// accessed through the global pointer  gpActualData
		InitializeMDIManagement();
        initApp(); 
        break;
    case AcRx::kUnloadAppMsg:

		ShutDownMDIManagement();

        deleteAcRxClass(AsdkCustomDrawEntity::desc()); 
        unloadApp(); 
        break;
    default:
        break;
    }
    return AcRx::kRetOK;
}
