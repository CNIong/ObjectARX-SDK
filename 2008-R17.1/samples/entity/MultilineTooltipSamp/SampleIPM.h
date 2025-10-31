// (C) Copyright 2001-2007 by Autodesk, Inc. 
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
//////////////////////////////////////////////////////////////////////////////
//
// AcEdInputPointMonitor

#if !defined(ARX__ASDKIPM_H__19990505_132529)
#define ARX__ASDKIPM_H__19990505_132529

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "acedinpt.h"


class CSampleIPM : public AcEdInputPointMonitor
{
public:

	// Constructor / Destructor
	CSampleIPM(const bool storeInDocVars = true, AcApDocument* pDoc = curDoc());
	virtual ~CSampleIPM();

	virtual bool excludeFromOsnapCalculation(const AcArray<AcDbObjectId>& nestedEntity,
	                                         INT_PTR gsSelectionMark);
	virtual Acad::ErrorStatus monitorInputPoint(
		bool& bAppendToTooltipStr,
	    TCHAR*& pAdditionalTooltipString,
	    AcGiViewportDraw* pDrawContext,
	    AcApDocument* pDocument,
	    bool pointComputed,
	    int history,
	    const AcGePoint3d& lastPoint,
	    const AcGePoint3d& rawPoint,
	    const AcGePoint3d& grippedPoint,
	    const AcGePoint3d& cartesianSnappedPoint,
	    const AcGePoint3d& osnappedPoint,
	    AcDb::OsnapMask osnapMask,
	    const AcArray<AcDbCustomOsnapMode*>& customOsnapModes,
	    AcDb::OsnapMask osnapOverrides,
	    const AcArray<AcDbCustomOsnapMode*>& customOsnapOverrides,
	    const AcArray<AcDbObjectId>& apertureEntities,
	    const AcArray< AcDbObjectIdArray,
	    AcArrayObjectCopyReallocator< AcDbObjectIdArray > >& nestedApertureEntities,
	    const AcArray<INT_PTR>& gsSelectionMark,
	    const AcArray<AcDbObjectId>& keyPointEntities,
	    const AcArray< AcDbObjectIdArray,
	    AcArrayObjectCopyReallocator< AcDbObjectIdArray > >& nestedKeyPointEntities,
	    const AcArray<INT_PTR>& keyPointGsSelectionMark,
	    const AcArray<AcGeCurve3d*>& alignmentPaths,
	    const AcGePoint3d& computedPoint,
	    const TCHAR* pTooltipString);

private:
	// Pointer to the document this instance belongs to.
	AcApDocument* m_pDoc;
};



#endif // !defined(ARX__ASDKIPM_H__19990505_132529)