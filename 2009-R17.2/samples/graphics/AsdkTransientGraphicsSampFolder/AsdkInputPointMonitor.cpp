//
// (C) Copyright 2002-2008 by Autodesk, Inc. 
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
//----- AsdkInputPointMonitor.cpp : Implementation of AsdkInputPointMonitor
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "AsdkInputPointMonitor.h"
#include "acgitransient.h"

BOOL GetTooltipDataFromBlockReference(AcDbBlockReference *pRef, CString &strImageName, CString &strImageDescription);

//-----------------------------------------------------------------------------
ACRX_CONS_DEFINE_MEMBERS(AsdkInputPointMonitor, AcEdInputPointMonitor, 1)

//-----------------------------------------------------------------------------
AsdkInputPointMonitor::AsdkInputPointMonitor (AcApDocument *pDoc) : AcEdInputPointMonitor(), mpDocument(pDoc) {
	if ( pDoc )
		pDoc->inputPointManager ()->addPointMonitor (this) ;
}

//-----------------------------------------------------------------------------
AsdkInputPointMonitor::~AsdkInputPointMonitor () {
	Detach () ;
}

//-----------------------------------------------------------------------------
void AsdkInputPointMonitor::Attach (AcApDocument *pDoc) {
	Detach () ;
	if ( mpDocument == NULL ) {
		if ( (mpDocument =pDoc) != NULL )
			pDoc->inputPointManager ()->addPointMonitor (this) ;
	}
}

void AsdkInputPointMonitor::Detach () {
	if ( mpDocument ) {
		mpDocument->inputPointManager ()->removePointMonitor (this) ;
		mpDocument =NULL ;
	}
}

AcApDocument *AsdkInputPointMonitor::Subject () const {
	return (mpDocument) ;
}

bool AsdkInputPointMonitor::IsAttached () const {
	return (mpDocument != NULL) ;
}

//-----------------------------------------------------------------------------
bool AsdkInputPointMonitor::excludeFromOsnapCalculation (
	const AcArray<AcDbObjectId> &nestedEntity,
	int gsSelectionMark
) {
	return (AcEdInputPointMonitor::excludeFromOsnapCalculation (nestedEntity, gsSelectionMark)) ;
}

//-----------------------------------------------------------------------------
Acad::ErrorStatus AsdkInputPointMonitor::monitorInputPoint (
	bool &appendToTooltipStr,
	ACHAR *&additionalTooltipString,
	AcGiViewportDraw *drawContext,
	AcApDocument *document,
	bool pointComputed,
	int history,
	const AcGePoint3d &lastPoint,
	const AcGePoint3d &rawPoint,
	const AcGePoint3d &grippedPoint,
	const AcGePoint3d &cartesianSnappedPoint,
	const AcGePoint3d &osnappedPoint,
	AcDb::OsnapMask osnapMask,
	const AcArray<AcDbCustomOsnapMode *> &customOsnapModes,
	AcDb::OsnapMask osnapOverrides,
	const AcArray<AcDbCustomOsnapMode *> &customOsnapOverrides,
	const AcArray<AcDbObjectId> &apertureEntities,
	const AcArray<AcDbObjectIdArray, AcArrayObjectCopyReallocator<AcDbObjectIdArray> > &nestedApertureEntities,
	const AcArray<Adesk::GsMarker> &gsSelectionMark,
	const AcArray<AcDbObjectId> &keyPointEntities,
	const AcArray<AcDbObjectIdArray, AcArrayObjectCopyReallocator<AcDbObjectIdArray> > &nestedKeyPointEntities,
	const AcArray<Adesk::GsMarker> &keyPointGsSelectionMark,
	const AcArray<AcGeCurve3d *> &alignmentPaths,
	const AcGePoint3d &computedPoint,
	const ACHAR *tooltipString
) {
	appendToTooltipStr =false ;

	int length = apertureEntities.length();
	int nIndex = 0;

	if(length == 0)
	{
		if(DocVars.docData().m_pTransientEntity != NULL)
		{
			if(DocVars.docData().m_pTransientEntity->getPriviewEntityId() == AcDbObjectId::kNull)
			{
			}
			else
			{
				AcArray<int> viewportNumbers;
				DocVars.docData().m_pTransientEntity->getViewportsForTransientGraphics(viewportNumbers);
				DocVars.docData().m_pTransientEntity->setPriviewEntityId(AcDbObjectId::kNull);
				AcGiTransientManager* pTransientManager = acgiGetTransientManager();
				pTransientManager->updateTransient(DocVars.docData().m_pTransientEntity, viewportNumbers);
			}
		}
	}
	// Check mouse aperture over some entity
	while (nIndex < length) 
	{
		AcDbObjectId objId = apertureEntities[nIndex];
		AcDbEntity * pEnt;
		
		if ( Acad::eOk != acdbOpenAcDbEntity( pEnt, objId, AcDb::kForRead))
		{
			acutPrintf( L"\nCannot open entity for read!" );
			return (Acad::eOk);
		}

		::AcDbBlockReference *pRef = AcDbBlockReference::cast(pEnt);

		if(pRef != NULL)
		{
			CString strImageName = _T("");
			CString strImageDescription = _T("");

			if(GetTooltipDataFromBlockReference(pRef, strImageName, strImageDescription) == TRUE)
			{
				if(DocVars.docData().m_pTransientEntity != NULL)
				{
					AcArray<int> viewportNumbers;
					DocVars.docData().m_pTransientEntity->getViewportsForTransientGraphics(viewportNumbers);

					DocVars.docData().m_pTransientEntity->setCurrentMousePoint(computedPoint);
					DocVars.docData().m_pTransientEntity->setPriviewEntityId(objId);
					AcGiTransientManager* pTransientManager = acgiGetTransientManager();
					pTransientManager->updateTransient(DocVars.docData().m_pTransientEntity, viewportNumbers);
				}
			}
		}
		pEnt->close(); 
		nIndex++;
	}

	return (Acad::eOk) ;
}
