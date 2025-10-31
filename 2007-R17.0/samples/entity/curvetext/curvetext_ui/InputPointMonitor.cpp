// (C) Copyright 1993-2006 by Autodesk, Inc.
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
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "InputPointMonitor.h"
#include "utils.h"



AsdkPointMonitor::AsdkPointMonitor()
{
	pCurveText = NULL;
	m_dist = 0.0;
}


Acad::ErrorStatus
AsdkPointMonitor::monitorInputPoint(
          // Output
          // If changedTooltipStr is kTrue
          // then newTooltipString has the new tooltip string in it.
          //
          bool&                             appendToTooltipStr,
          TCHAR*&                            additionalTooltipString,

          // Input/Output
          //
          AcGiViewportDraw*                   drawContext,

          // Input parameters:
          //
          AcApDocument*                       document,
          bool                                pointComputed,
          int                                 history,
          const AcGePoint3d&                  lastPoint,
          const AcGePoint3d&                  rawPoint,
          const AcGePoint3d&                  grippedPoint,
          const AcGePoint3d&                  cartesianSnappedPoint,
          const AcGePoint3d&                  osnappedPoint,
          AcDb::OsnapMask                     osnapMask,
          const AcArray<AcDbCustomOsnapMode*>& customOsnapModes,
          AcDb::OsnapMask                     osnapOverrides,
          const AcArray<AcDbCustomOsnapMode*>& customOsnapOverrides,
          const AcArray<AcDbObjectId>&        apertureEntities,
          const AcArray< AcDbObjectIdArray, AcArrayObjectCopyReallocator< AcDbObjectIdArray > >& 
                                              nestedApertureEntities,
          const AcArray<int>&                 gsSelectionMark,
          const AcArray<AcDbObjectId>&        keyPointEntities,
          const AcArray< AcDbObjectIdArray, AcArrayObjectCopyReallocator< AcDbObjectIdArray > >&
                                              nestedKeyPointEntities,
          const AcArray<int>&                 keyPointGsSelectionMark,
          const AcArray<AcGeCurve3d*>&        alignmentPaths,
          const AcGePoint3d&                  computedPoint,
          const TCHAR*                         tooltipString)
{
	if(!pointComputed)
		return Acad::eOk;

	m_curvePerp[0] = computedPoint;
	
	pCurveText->getClosestPointTo(computedPoint, m_curvePerp[1]);
	pCurveText->getDistAtPoint(m_curvePerp[1], m_dist);

    if (NULL != drawContext)
		drawContext->geometry().polyline(2, m_curvePerp);

	return Acad::eOk;
}
