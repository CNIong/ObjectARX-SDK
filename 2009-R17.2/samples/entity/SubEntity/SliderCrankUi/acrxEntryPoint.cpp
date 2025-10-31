// (C) Copyright 2002-2006 by Autodesk, Inc. 
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

//-----------------------------------------------------------------------------
//----- acrxEntryPoint.h
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "resource.h"

//-----------------------------------------------------------------------------
#define szRDS _RXST("Asdk")

#include "../SliderCrankDb/AsdkSliderCrank.h"
#include "AsdkUIContext.h"

int acedSSSubentLength(const ads_name sname, long index, long* length);
int acedSSSubentName(const ads_name ss, long entIndex, long subentIndex, AcDbFullSubentPath& subentity);

//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
class CSliderCrankUiApp : public AcRxArxApp {
private:
        AsdkUIContext *m_puicontext;
public:
    CSliderCrankUiApp () : AcRxArxApp () {}

    virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt) {
        // TODO: Load dependencies here

        // You *must* call On_kInitAppMsg here
        AcRx::AppRetCode retCode =AcRxArxApp::On_kInitAppMsg (pkt) ;
        
        m_puicontext = new AsdkUIContext();
        acedAddObjectContextMenu(AsdkSliderCrank::desc(), m_puicontext, pkt);

        return (retCode) ;
    }

    virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt) {
        // TODO: Add your code here

        // You *must* call On_kUnloadAppMsg here
        AcRx::AppRetCode retCode =AcRxArxApp::On_kUnloadAppMsg (pkt) ;

        acedRemoveObjectContextMenu(AsdkSliderCrank::desc(), m_puicontext);
        delete m_puicontext;

        return (retCode) ;
    }

    virtual void RegisterServerComponents () {
    }


    // - AsdkSliderCrankUi._AddSliderCrank command (do not rename)
    static void AsdkSliderCrankUi_AddSliderCrank(void)
    {
        // Add your code for command AsdkSliderCrankUi._AddSliderCrank here
        AsdkSliderCrank *pSliderCrank = new AsdkSliderCrank();

        pSliderCrank->setLocation(AcGePoint3d(0.0,0.0,0.0));
        pSliderCrank->setSliderDirection(AcGeVector3d(1.0,0.0,0.0));
        pSliderCrank->setCrankRadius(10.0);
        pSliderCrank->setCrankPinAngle(45.0);
        pSliderCrank->setConnectingLinkLength(30.0);
        pSliderCrank->setPistonSize(5);
        pSliderCrank->setPistonSkirtLength(5);

        //Set color]
        AcCmEntityColor col;
        col.setColorIndex(1);
        pSliderCrank->setConnectingLinkColor(col);

        col.setColorIndex(2);
        pSliderCrank->setCrankColor(col);

        col.setColorIndex(3);
        pSliderCrank->setPistonColor(col);


        AcDbBlockTableRecordPointer pMS (ACDB_MODEL_SPACE, acdbHostApplicationServices()->workingDatabase(), AcDb::kForWrite) ;
        pMS->appendAcDbEntity(pSliderCrank);
        pSliderCrank->close();
    }

    // - AsdkSliderCrankUi._MoveSliderCrank command (do not rename)
    static void AsdkSliderCrankUi_MoveSliderCrank(void)
    {
        // Add your code for command AsdkSliderCrankUi._MoveSliderCrank here

        ads_name ss;
        acedSSGet(_T("_:U"),NULL,NULL,NULL,ss);

        //ads name of the entity
        int idx = 0;
        ads_name ename;
        acedSSName(ss, idx, ename);

        //Check how many sub entities were selected
        long len = 0;
        acedSSSubentLength(ss, idx, &len);		
        acutPrintf(_T("Number of subents selected: %d"),len);


        AcDbFullSubentPath subentity;
        acedSSSubentName(ss,idx,idx,subentity);

        //Open the sub entity to move it by 10 points
        AcDbObjectId id;
        acdbGetObjectId(id,ename);
        AcDbEntityPointer pEnt(id, AcDb::kForWrite);

        if(Acad::eOk == pEnt.openStatus())
        {
            AcDbFullSubentPathArray paths;
            paths.append(subentity);

            AcGeMatrix3d xform;
            xform.setToTranslation(AcGeVector3d(10,0,0));
            pEnt->transformSubentPathsBy(paths,xform);
        }
    }
} ;

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CSliderCrankUiApp)

ACED_ARXCOMMAND_ENTRY_AUTO(CSliderCrankUiApp, AsdkSliderCrankUi, _AddSliderCrank, AddSliderCrank, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CSliderCrankUiApp, AsdkSliderCrankUi, _MoveSliderCrank, MoveSliderCrank, ACRX_CMD_MODAL, NULL)