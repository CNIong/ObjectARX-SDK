//
// (C) Copyright 1998-2002,2004 by Autodesk, Inc. 
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


//Implements AcLine 
# include "AcLine.h"
#include <tchar.h>

//MAKE_ACDBOPENOBJECT_FUNCTION(AcLine);
ACRX_DXF_DEFINE_MEMBERS(AcLine, AcDbEntity, 15, 0, AcDbProxyEntity::kColorChangeAllowed, \
												ASDKACLINE, ASDKACLINE);

//Static Declaration
appDataType		AcLine::msAppData; //AppData


appDataType::iterator 
AcLine::putAppData()
{
	if(msAppData.empty())
	{
		msAppData.reserve(GripCount);
		std::string sAppData[GripCount]=
		{
			_T("First"),_T("Second"),
			_T("Center")
		};

		for(int i=0;i<GripCount;i++)
		{
			msAppData.push_back(sAppData[i]);
		}
	}
	return msAppData.begin();
	
}

AcLine::AcLine()
{}
	
AcLine::AcLine(const AcGePoint3d &sp,const AcGePoint3d &ep)
:msp(sp),mep(ep)
{
	mcp[0] = (msp[0]+mep[0])/2;
	mcp[1] = (msp[1]+mep[1])/2;
	mcp[2] = 0;
}

AcLine::~AcLine()
{}

Acad::ErrorStatus 
AcLine::dwgInFields(AcDbDwgFiler *pFiler)
{
	Acad::ErrorStatus es;
	es =AcDbEntity::dwgInFields(pFiler);

	pFiler->readItem(&msp);
	pFiler->readItem(&mep);
    return pFiler->filerStatus();

}

Acad::ErrorStatus 
AcLine::dwgOutFields(AcDbDwgFiler*pFiler) const
{
    assertReadEnabled();
    AcDbEntity::dwgOutFields(pFiler);
    pFiler->writeItem(msp);
	pFiler->writeItem(mep);
 
	return pFiler->filerStatus();
}



Acad::ErrorStatus 
AcLine::dxfInFields(AcDbDxfFiler *pFiler)
{
	assertWriteEnabled();
	Acad::ErrorStatus es;
    struct resbuf     rb;
    
	es=AcDbEntity::dxfInFields(pFiler);
    if (es != Acad::eOk) 
	{
        return es;
    }

    if (!pFiler->atSubclassData(_T("AcLine"))) 
	{
        return Acad::eBadDxfSequence;
    }
    while (es == Acad::eOk) 
	{
        if ((es = pFiler->readItem(&rb)) == Acad::eOk) 
		{
            switch(rb.restype) 
			{
				case AcDb::kDxfXCoord:
					msp.set(rb.resval.rpoint[X], rb.resval.rpoint[Y],rb.resval.rpoint[Z]);
	                break;
				case AcDb::kDxfXCoord+1:
					mep.set(rb.resval.rpoint[X], rb.resval.rpoint[Y],rb.resval.rpoint[Z]);
	                break;
		        default:
					pFiler->pushBackItem();
					es = Acad::eEndOfFile;
					break;
            }
        }
    }

    if (es != Acad::eEndOfFile)
        return Acad::eInvalidResBuf;

	
    return pFiler->filerStatus();
}

Acad::ErrorStatus 
AcLine::dxfOutFields(AcDbDxfFiler*pFiler) const
{
	 assertReadEnabled();
	
    AcDbEntity::dxfOutFields(pFiler);

	pFiler->writeItem(AcDb::kDxfSubclass, _T("AcLine"));
    pFiler->writeItem(AcDb::kDxfXCoord, msp);
	pFiler->writeItem(AcDb::kDxfXCoord, mep);
	return Acad::eOk;
}
	
Adesk:: Boolean 
AcLine::worldDraw(AcGiWorldDraw* pWd)
{
	AcGePoint3d pVertex[2];
	pVertex[0] = msp;
	pVertex[1] = mep;
	
	pWd->geometry().polyline((Adesk::UInt32) 2, pVertex);
	return Adesk::kTrue;


}

Acad::ErrorStatus 
AcLine::getGripPoints(AcGePoint3dArray&,AcDbIntArray&,
					  			    AcDbIntArray&) const
{
	return Acad::eNotImplementedYet;
}

Acad::ErrorStatus 
AcLine::moveGripPointsAt(const AcDbIntArray&,
								   const AcGeVector3d&)
{
	return Acad::eNotImplementedYet;
}

//New overloaded grip methods that need to be implemented 
//to use the Grip Enhancement
Acad::ErrorStatus  
AcLine::getGripPoints(AcDbGripDataPtrArray& gripPoints,
                      const double			viewSize,
                      const	AcGeVector3d&   offset, 
                      const int				bitflags) const
{
	AcDbGripData  *pStartGripData   = new AcDbGripData();
	AcDbGripData  *pEndGripData	    = new AcDbGripData();
	AcDbGripData  *pCenterGripData  = new AcDbGripData();

	//AcGePoint3d	  *pAltBaseStartGrip = new AcGePoint3d(msp[0]+0.25,mep[0]+0.25,0);

	if(bitflags)
	{
		//Then the grip points are just for the display purpose and so 
		//we just set the 3d point
	
		pStartGripData->setGripPoint(msp);
		gripPoints.append(pStartGripData);

		pEndGripData->setGripPoint(mep);
		gripPoints.append(pEndGripData);

		pCenterGripData->setGripPoint(mcp);
		gripPoints.append(pCenterGripData);

	}
	else 
	{
		appDataType::iterator appIter = putAppData();

		pStartGripData->setGripPoint(msp);
		pStartGripData->setAppData((void*)&appIter);
		gripPoints.append(pStartGripData);
		appIter++;

		pEndGripData->setGripPoint(mep);
		pEndGripData->setAppData((void*)&appIter);
		gripPoints.append(pEndGripData);
		appIter++;

		pCenterGripData->setGripPoint(mcp);
		pCenterGripData->setAppData((void*)&appIter);
		gripPoints.append(pCenterGripData);
		appIter++;

		/*
		pStartGripData->setGripPoint(msp);
		pStartGripData->setAppData(msAppData1);
		pStartGripData->disableModeKeywords(true);
		pStartGripData->setHoverFunc(GripCbackFuncs::GripOperationfunc);
		pStartGripData->setWorldDraw(GripCbackFuncs::GripWorldDrawfunc);
		pStartGripData->setRtClk(GripCbackFuncs::GripRtClkHandlerfunc);
		pStartGripData->setToolTipFunc(GripCbackFuncs::GripToolTipfunc);
		pStartGripData->setSkipWhenShared(true);
		//Commented by Suresh Kumar on 01/23/02 for testing offline base
		//point
		//pStartGripData->disableRubberBandLine(true);
		//pStartGripData->setAlternateBasePoint(pAltBaseStartGrip);
		bool bSkipSharedStatus = pStartGripData->skipWhenShared();
		if(bSkipSharedSta-*tus)
			acutPrintf("\nSkip When shared returned true\n");
		else acutPrintf("\nSkip when shared failed\n");
		

		gripPoints.append(pStartGripData);

		pEndGripData->setGripPoint(mep);
		pEndGripData->setAppData(msAppdata2);
		pEndGripData->disableModeKeywords(true);
		pEndGripData->setWorldDraw(NULL);
		pEndGripData->setViewportDraw(GripCbackFuncs::GripViewportDrawfunc);
		//m_pgripPoints[1].setWorldDraw(GripCbackFuncs::GripWorldDrawfunc);
		pEndGripData->setToolTipFunc(GripCbackFuncs::GripToolTipfunc);
		pEndGripData->setGripOpStatFunc(GripCbackFuncs::gripOpStatusCbackfunc);
		pEndGripData->setHoverFunc(GripCbackFuncs::GripOperationfunc);
		
		gripPoints.append(pEndGripData);
		*/
	}

	return Acad::eOk;
}

	
Acad::ErrorStatus  AcLine::moveGripPointsAt(const AcDbVoidPtrArray&gripAppData,
										const AcGeVector3d &offset,
                                        const int bitflags)
{
	std::string *pshotGrip = 0;
	AcGePoint3d point;
	
	for(int i=0;i<gripAppData.length(); i++)
	{
		pshotGrip = static_cast<std::string*>(gripAppData[i]);
		if(*pshotGrip == _T("First"))
		{
			msp += offset;
			continue;
		}
		else if(*pshotGrip ==_T("Second"))
		{
			mep += offset;
			continue;
		}
		else if(*pshotGrip == _T("Center"))
		{
			mcp += offset;
			continue;

		}
	}
	return Acad::eOk;
}
	
Acad::ErrorStatus AcLine::transformBy(const AcGeMatrix3d& xform)
{
	assertWriteEnabled();
	msp.transformBy(xform);
	mep.transformBy(xform);
	return Acad::eOk;
}

void AcLine::dragStatus(const AcDb::DragStat status)
{}

void AcLine::gripStatus(const AcDb::GripStat status)
{}

