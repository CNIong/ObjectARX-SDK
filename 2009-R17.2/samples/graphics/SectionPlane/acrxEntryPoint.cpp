// (C) Copyright 2006-2007 by Autodesk, Inc. 
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
#include "SectionPlaneUtility.h"

//-----------------------------------------------------------------------------
#define szRDS _RXST("Asdk")

//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
class CSectionPlaneApp : public AcRxArxApp {

public:
	CSectionPlaneApp () : AcRxArxApp () {}

	virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt) {
		// TODO: Load dependencies here

		// You *must* call On_kInitAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kInitAppMsg (pkt) ;
		
		// TODO: Add your initialization code here

		return (retCode) ;
	}

	virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt) {
		// TODO: Add your code here

		// You *must* call On_kUnloadAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kUnloadAppMsg (pkt) ;

		// TODO: Unload dependencies here

		return (retCode) ;
	}

	virtual void RegisterServerComponents () {
	}

	// - AsdkSectionPlane._GetSection command (do not rename)
	static void AsdkSectionPlane_GetSection(void)
	{
		CSectionPlaneUtility::GetSection();
	}

	// - AsdkSectionPlane._IterSections command (do not rename)
	static void AsdkSectionPlane_IterSections(void)
	{
		CSectionPlaneUtility::IterSections();
	}

public:

	// - AsdkSectionPlane._DynamicSection command (do not rename)
	static void AsdkSectionPlane_DynamicSection(void)
	{
		int iTest = RTNORM;
		AcGeMatrix3d ucsMat;
		if(Acad::eOk != (acedGetCurrentUCS(ucsMat)))
			return;
		
		AcGePoint3dArray sectVertices;
		
		// Get two points in the plane
		ads_point pnt;
		iTest = acedGetPoint(NULL,_T("\nSelect first point of the line in the plane: "),pnt);
		if(iTest != RTNORM)
			return;

		AcGePoint3d startPnt(pnt[X],pnt[Y],pnt[Z]);
		// transform the selected point to wcs
		startPnt.transformBy(ucsMat);
		sectVertices.append(startPnt);
		AcGePoint3d endPnt;
		iTest = acedGetPoint(pnt,_T("\nSelect second point of the line in the plane: "),asDblArray(endPnt));
		if(iTest != RTNORM)
			return;
		// transform the selected point to wcs
		endPnt.transformBy(ucsMat);
		sectVertices.append(endPnt);
		AcDbSection* pSection = new AcDbSection(sectVertices, AcGeVector3d::kZAxis);
		if(pSection==NULL)
			return;
		if(Acad::eOk != (pSection->setState(AcDbSection::kPlane)))
			return;
		AcDbObjectId sectionId = AcDbObjectId::kNull;
		sectionId = CSectionPlaneUtility::AddEntityToDatabase(pSection);
		if(sectionId == AcDbObjectId::kNull)
			return;
		//AcDbObjectId sectionId = pSection->objectId();
		AcString sectName = _T("FirstSection");
		if(Acad::eOk != (pSection->setName(sectName)))
			return;
		if(Acad::eOk != (pSection->setIndicatorTransparency(90)))
			return;
		if(Acad::eOk != (pSection->setHeight(AcDbSection::kHeightAboveSectionLine, 3.0)))
			return;
		if(Acad::eOk != (pSection->setHeight(AcDbSection::kHeightBelowSectionLine, 1.0)))
			return;
		if(Acad::eOk != (pSection->enableLiveSection(true)))
			return;

		pSection->close();
				
		ads_real * dist = new ads_real(10.00);
		ads_real * rotateAngle = new ads_real(30.00);
		
		TCHAR translateOrRotate2[12] = _T("Translate");
		TCHAR translateOrRotate[12];
		
		while(iTest != RTCAN)
		{
			acedInitGet(0,_T("Translate Rotate Snapshot"));
			AcString promtForT_R_S; 
			promtForT_R_S.format(_T("\n[Translate/Rotate/Snapshot] <%s>"), translateOrRotate2);
			iTest = acedGetKword(promtForT_R_S, translateOrRotate);
			
			// If the user hits enter translateOrRotate is incorrect
			// Make translateOrRotate the value in translateOrRotate2
			if(iTest == RTNONE)
				_tcscpy(translateOrRotate, translateOrRotate2);
			
			// Keep translateOrRotate2 current
			_tcscpy(translateOrRotate2, translateOrRotate);
			if(iTest == RTCAN)
				break;
						
			if (!_tcscmp(translateOrRotate,_T("Translate")))
			{
				int iMoveOrRotate = 1;
				CSectionPlaneUtility::MoveOrRotateSection(iMoveOrRotate, sectionId, sectVertices, dist, rotateAngle); 
			
			}
			else if (!_tcscmp(translateOrRotate,_T("Rotate")))
			{
				int iMoveOrRotate = 2;
				CSectionPlaneUtility::MoveOrRotateSection(iMoveOrRotate, sectionId, sectVertices,dist, rotateAngle); 
			}
			else 
			{
				ads_name eName;
				ads_point pnt;
				iTest = acedEntSel(_T("\nSelect the solid to create block ref from: "),eName,pnt);
				if(iTest!= RTNORM)
					break;
				
				ACHAR blkName[133];
				iTest = acedGetString(0,_T("\nEnter block name: "), blkName);
				if(iTest != RTNORM)
					break;

				AcDbObjectId solId;
				acdbGetObjectId(solId, eName);

				// Call code to create a block from the selection
				if(Acad::eOk != (acdbOpenObject(pSection, sectionId, AcDb::kForWrite)))
				{
					acutPrintf(_T("\nUnable to open section for write"));
					break;
				}
				
				AcGePoint3d blkRefPnt(0,0,0);
						
				int iForLayerColor = 2;
				CSectionPlaneUtility::Generate3dBlock(pSection, solId, blkName, blkRefPnt, iForLayerColor);
			}
		}
		
		if(Acad::eOk == (acdbOpenObject(pSection,sectionId,AcDb::kForWrite)))
		{
			pSection->erase();
			pSection->close();
		}
		delete dist;
		delete rotateAngle;
	}
} ;

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CSectionPlaneApp)

ACED_ARXCOMMAND_ENTRY_AUTO(CSectionPlaneApp, AsdkSectionPlane, _GetSection, GetSection, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CSectionPlaneApp, AsdkSectionPlane, _IterSections, IterSections, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CSectionPlaneApp, AsdkSectionPlane, _DynamicSection, DynamicSection, ACRX_CMD_TRANSPARENT, NULL)
