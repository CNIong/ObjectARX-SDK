//
//
// (C) Copyright 2002 by Autodesk, Inc. 
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
//

#include "boltjig.h"
#include "..\boltObject\asdkBolt.h"

AsdkBoltJig::AsdkBoltJig()
{
	HRESULT hr = S_OK;
    // Get an instance of a wrapper for a non-db-resident bolt
    if (FAILED(hr = mBolt.CoCreateInstance(CLSID_Bolt))) {
        acutPrintf("\nUnable to load asdkBolt");
        throw hr;
    }
	    
    m_pBaseObj = mBolt;
    m_pBaseObj->CreateObject();

     // Get an instance of a listner so we know when input has been
     // entered in OPM
     if (FAILED(hr = CComObject<CComBoltCmd>::CreateInstance(&m_pBoltCmd)))
         throw hr;
    
     m_pBoltCmd->SetDocument(curDoc());
     hr = m_pBoltCmd->QueryInterface(IID_IUnknown,(LPVOID *)&m_pUnkCmd);
     if (FAILED(hr))
         throw hr;

     // Attach the listener to the bolt wrapper
     CComQIPtr<IConnectionPointContainer> pPtContainer;
     pPtContainer = mBolt;
     hr = pPtContainer->FindConnectionPoint(
         IID_IPropertyNotifySink,&m_pConPt);
     if (FAILED(hr))
         throw hr;

     if (FAILED(hr = m_pConPt->Advise(m_pUnkCmd,&m_dConnectionID)))
         throw hr;

     acedSetIUnknownForCurrentCommand(mBolt);

     m_pDb = curDoc()->database();
	 m_pBolt=NULL;

}

AsdkBoltJig::~AsdkBoltJig()
{
	release();
    if (m_pConPt) m_pConPt->Unadvise(m_dConnectionID);
}

void AsdkBoltJig::inputInitialValues()
{
	AcEdJig::DragStatus stat=kNormal;
	int retval=RTNORM;
	
	while (true) 
	{
		bool done=true;
		if(!m_pBoltCmd->GotHeadSides())
		{
			done=false;
			int headSides;
			retval=acedGetInt("\nHead Sides <6>: ",&headSides);
            if (retval == RTCAN)
                break;
            // CPH RTMODELESS workaround...and all below (just the !m_pBoltCmd->...)
			if(retval == RTNONE && !m_pBoltCmd->bModelessInterrupt)
				headSides=6;
			else if (retval != RTNORM)
                continue;
			mBolt->put_headSides(headSides);
		}
		// CPH RTMODELESS workaround...and all below
		m_pBoltCmd->bModelessInterrupt = false;
		if(!m_pBoltCmd->GotHeadHeight())
		{
			done=false;
			double headHeight;
			retval=acedGetDist(NULL,"\nHead Height <2.0>: ",&headHeight);
            if (retval == RTCAN)
                break;
            if(retval == RTNONE && !m_pBoltCmd->bModelessInterrupt)
				headHeight=2.0f;
            else if (retval != RTNORM)
                continue;
			mBolt->put_headHeight(headHeight);
		}
		m_pBoltCmd->bModelessInterrupt = false;
		if(!m_pBoltCmd->GotShaftLength())
		{
			done=false;
			double shaftLength;
			retval=acedGetDist(NULL,"\nShaft Length <10.0>: ",&shaftLength);
            if (retval == RTCAN)
                break;
            if(retval == RTNONE && !m_pBoltCmd->bModelessInterrupt)
				shaftLength=10.0f;
            else if (retval != RTNORM)
                continue;
			mBolt->put_shaftLength(shaftLength);
		}
		m_pBoltCmd->bModelessInterrupt = false;
		if(!m_pBoltCmd->GotThreadLength())
		{
			done=false;
			double threadLength;
			retval=acedGetDist(NULL,"\nThread Length <3.0>: ",&threadLength);
            if (retval == RTCAN)
                break;
            if(retval == RTNONE && !m_pBoltCmd->bModelessInterrupt)
				threadLength=3.0f;
            else if (retval != RTNORM)
                continue;
			mBolt->put_threadLength(threadLength);
		}
		m_pBoltCmd->bModelessInterrupt = false;
		if(!m_pBoltCmd->GotThreadWidth())
		{
			done=false;
			double threadWidth;
			retval=acedGetDist(NULL,"\nThread Width <0.2>: ",&threadWidth);
            if (retval == RTCAN)
                break;
            if(retval == RTNONE && !m_pBoltCmd->bModelessInterrupt)
				threadWidth=0.2f;
            else if (retval != RTNORM)
                continue;
			mBolt->put_threadWidth(threadWidth);
		}
		m_pBoltCmd->bModelessInterrupt = false;
		if(done)
			break;
	}

	if(retval==RTCAN)
		return;

	// Now we enter the JIG Phase of the command:

	 // Initialize prop bools
	 GotPosition=m_pBoltCmd->GotPosition();
	 GotHeadDiameter=m_pBoltCmd->GotHeadDiameter();
	 GotShaftDiameter=m_pBoltCmd->GotShaftDiameter();

	while((!m_pBoltCmd->GotPosition() || !m_pBoltCmd->GotHeadDiameter() || !m_pBoltCmd->GotShaftDiameter()) && stat!=kCancel)
	{
		if(!GotPosition)
		{
			acutPrintf("\nSpecify Insertion Point:\n");
			stat = drag(); // Go get it
			if (stat==kNormal) // Picked by the cursor only.
			{
				AcAxPoint3d pos(cursorPos);
				mBolt->put_position(*(pos.asVariantPtr()));
				GotPosition = true;
			}
			else
				continue;
		}
		if(!GotHeadDiameter)
		{
			acutPrintf("\nSpecify Bolt Head Diameter:\n");
			stat = drag();// Go get it
			if (stat == kNormal) 
			{
				mBolt->put_headDiameter(headDia);
				GotHeadDiameter = true;
			}
			else
				continue;
		}
		if(!GotShaftDiameter)
		{
			acutPrintf("\nSpecify Bolt Shaft Diameter:\n");
			stat = drag();// Go get it
			if (stat == kNormal) 
			{
				mBolt->put_shaftDiameter(shaftDia);
				GotShaftDiameter = true;
			}
			else
				continue;
		}
	}

	AcDbObjectId obj(NULL);
	if(stat!=kCancel)
		append();// Instead of : m_pBaseObj->AddToDb(obj,m_pDb->currentSpaceId(),"asdkBolt");
}

void AsdkBoltJig::release()
{
    if (m_pBolt != NULL) {
        m_pBaseObj->SetObject((AcDbObject *&)m_pBolt);
        m_pBolt=NULL;
    }
}

void AsdkBoltJig::getPointer()
{
    if (m_pBolt == NULL)
        m_pBaseObj->GetObject((AcDbObject *&)m_pBolt);
}


AcDbEntity* AsdkBoltJig::entity() const
{
    if (m_pBolt == NULL)
        m_pBaseObj->GetObject((AcDbObject *&)m_pBolt);
    return (AcDbEntity *)m_pBolt;
}

AcEdJig::DragStatus	 
AsdkBoltJig::sampler()
{
    setSpecialCursorType(AcEdJig::kCrosshair);

    setUserInputControls((UserInputControls)
	                 (kNullResponseAccepted|kAccept3dCoordinates |
	                  kDontUpdateLastPoint));
	
	DragStatus stat = kCancel;
	
	AcGePoint3d pos;
	double hD, sD;

	double headHeight;
	mBolt->get_headHeight(&headHeight);
	
	if(!m_pBoltCmd->GotPosition())
	{
		stat=acquirePoint(pos);		
		if(cursorPos == pos)
			return kNoChange;
		else 
		{
			cursorPos = pos;
			return stat;
		}
	}

	if(!m_pBoltCmd->GotHeadDiameter())
	{	
		stat=acquireDist(hD,cursorPos);
		hD*=2;
		
		if (hD == headDia) 
			return kNoChange;
		else 
		{
			headDia = hD;
			return stat;
		}
	}

	if(!GotShaftDiameter)
	{
		AcGePoint3d shaftJigPt=cursorPos;
		shaftJigPt.x+=headHeight;
		stat=acquireDist(sD,shaftJigPt);
		sD*=2;
		if (sD == shaftDia) 
			return kNoChange;
		else 
		{
			shaftDia = sD;
			return stat;
		}
	}
    return stat;
}

Adesk::Boolean	
AsdkBoltJig::update()
{
	if(!m_pBoltCmd->GotPosition()) {
		getPointer();
		m_pBolt->setPosition(cursorPos);
		release();
	}
	else if(!m_pBoltCmd->GotHeadDiameter()) {
		getPointer();
		m_pBolt->setHeadDiameter(headDia);
		release();
	}
	else if(!m_pBoltCmd->GotShaftDiameter()) {
		getPointer();
		m_pBolt->setShaftDiameter(shaftDia);
		release();
	}
	return Adesk::kTrue;
}

// This is command 'BOLTJIG'
void AsDkBoltJig()
{
	AsdkBoltJig jig;
	jig.inputInitialValues();
}

