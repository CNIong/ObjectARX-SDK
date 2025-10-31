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
#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "adscodes.h"
#include "acutads.h"
#include "aced.h"
#include "dbsymtb.h"
#include "dbents.h"
#include "acestext.h"
#include "rxregsvc.h"

#include "actrutil.h"
#include "..\Db\blockorderindex.h"
#include "..\Db\blockorderfilter.h"



//this sample uses the smart pointer class defined
//by actrutil.h located in the samples\tools directory

using namespace AcTrUtil;
#define ARXOK checkErrorT<Acad::ErrorStatus>

//this command lets you select an a block reference (no xrefs supported yet, but I hope to add
//that by FCS) and then an (first level) object within the block reference.
//Then you can decide if you want to move the object to the top or to the bottom in the 
//draworder.
//Note that this command uses the AcDbFilter and AcDbIndex classes. This mechanism is 
//NOT the same that DRAWORDER command uses in model space and layout.
void blockOrder()
{
    resbuf* res = NULL;
	try
	{
		Transaction trans;
		int rt;
		ads_name ename;
		ads_point pt;
        if ((rt=acedEntSel(_T("Select a reference:"),ename,pt))==RTCAN)
			return;
		if (rt!=RTNORM)
			throw Acad::eInvalidInput;
		Ptr<AcDbBlockReference> pBlkRef(ename,AcDb::kForWrite);
        //get block table record
		Ptr<AcDbBlockTableRecord> pBTR(pBlkRef->blockTableRecord(),AcDb::kForWrite);
        Acad::ErrorStatus es;
        //get or add index
		Ptr<AsdkBlockOrderIndex> pIndex;
        es = AcDbIndexFilterManager::getIndex(pBTR,AsdkBlockOrderIndex::desc(),AcDb::kForWrite,(AcDbIndex*&)pIndex);
        if (es==Acad::eKeyNotFound)
        {
            if ((pIndex=AsdkBlockOrderIndex::cast(
                AsdkBlockOrderIndex::desc()->create()))==NULL)
			    throw Acad::eOutOfMemory;
		    ARXOK(AcDbIndexFilterManager::addIndex(pBTR, pIndex));
        } else if (es!=Acad::eOk)
            throw es;
        //get or add filter
		Ptr<AsdkBlockOrderFilter> pFilter;
        es = AcDbIndexFilterManager::getFilter(pBlkRef,AsdkBlockOrderFilter::desc(),AcDb::kForWrite,(AcDbFilter*&)pFilter);
        if (es==Acad::eKeyNotFound)
        {
            if ((pFilter=AsdkBlockOrderFilter::cast(
                AsdkBlockOrderFilter::desc()->create()))==NULL)
			    throw Acad::eOutOfMemory;
		    ARXOK(AcDbIndexFilterManager::addFilter(pBlkRef,pFilter));
        } else if (es!=Acad::eOk)
            throw es;
        //prompt for object to be moved
        ads_point xform[4];
        resbuf *temp,*last,*lastButOne;
        ads_name eobj;
        do
        {
            if (res!=NULL)
                acutRelRb(res);
            res = NULL;temp = NULL;last = NULL; lastButOne=NULL;
            if ((rt=acedNEntSel(_T("\nSelect entity to order:"),eobj,pt,xform,&res))==RTCAN)
                return;
            if (rt!=RTNORM)
			    throw Acad::eInvalidInput;
            temp=res;
            last=temp;
            while (temp!=NULL && temp->rbnext!=NULL){
                lastButOne=temp;
                temp=temp->rbnext;
                last = temp;
            }
        } 
        //prompt until we find an object within the original block reference
        while (res==NULL || last==NULL || (last!=NULL && last->resval.rlname[0]!=ename[0]));
        AcDbObjectId idObj;
        //if the object selected is within a block reference (nested block)
        //then just add the block reference (NOTE that eobj is the inner most object
        //and we only sort objects within the this reference.)
        if (lastButOne!=NULL)
            ARXOK(acdbGetObjectId(idObj,lastButOne->resval.rlname));
        else
            ARXOK(acdbGetObjectId(idObj,eobj));
        acutRelRb(res);
        //find out where to move the object
        if (acedInitGet(0,_T("TOP,T BOTTOM,B"))!=RTNORM)
            throw Acad::eInvalidInput;
        TCHAR result[512];
        if ((rt=acedGetKword(_T("\nMove to [Top/Bottom]:"),result))==RTCAN)
			return;
		if (rt!=RTNORM)
			throw Acad::eInvalidInput;
        if (_tcsicmp(result,_T("TOP"))==0)
            pFilter->moveToTop(idObj);
        else if (_tcsicmp(result,_T("BOTTOM"))==0)
            pFilter->moveToBottom(idObj);
        pIndex->setLastUpdatedAtU(pBTR->database()->tduupdate());
        //make sure that the reference is redrawn
        pBlkRef->assertWriteEnabled();
		trans.commit();
	}
	catch (Acad::ErrorStatus es)
	{
        if (res!=NULL)
            acutRelRb(res);
        acutPrintf(_T("\nError: es==%s"),acadErrorStatusText(es));
	}
}
const TCHAR* cstrCommandGroup = _T("ASDK_BLOCKORDER");

AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt) 
{
    switch(msg) {
        case AcRx::kInitAppMsg:
        {
			//allow unloading
			acrxDynamicLinker->unlockApplication(pkt);
			//we are MDI aware
			acrxDynamicLinker->registerAppMDIAware(pkt);
            //it is no use trying to use the logical app name
            //the dbx is already in the acad process or we never
            //get here
            //Nevertheless, call the following function
            //to do proper reference counting and rx init
            acrxLoadModule(_T("asdkblockorderdb.dbx"),0);

            acedRegCmds->addCommand(cstrCommandGroup,
                            _T("blockorder"),
                            _T("blockorder"),
                            ACRX_CMD_MODAL,
                            &blockOrder);
			
            break;
        }
        case AcRx::kUnloadAppMsg:
            //decrement the reference count on the server
            acrxUnloadModule(_T("asdkblockorderdb.dbx"));
    		acedRegCmds->removeGroup(cstrCommandGroup);
            break;
    }
    return AcRx::kRetOK;
}