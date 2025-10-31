// (C) Copyright 2001-2006 by Autodesk, Inc. 
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

#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "tchar.h"



CSampleIPM::CSampleIPM(const bool storeInDocVars, AcApDocument* pDoc)
{
	if (storeInDocVars) {

		assert(gDocVars.docData(pDoc).m_pIPM == NULL);

		m_pDoc = pDoc;
		m_pDoc->inputPointManager()->addPointMonitor(this);
		gDocVars.docData().m_pIPM = this;

	} else
		m_pDoc = NULL;
}

CSampleIPM::~CSampleIPM()
{
	if (m_pDoc)
		if (gDocVars.docData(m_pDoc).m_pIPM) {
			m_pDoc->inputPointManager()->removePointMonitor(this);
			gDocVars.docData(m_pDoc).m_pIPM = NULL;
		}
}

bool
CSampleIPM::excludeFromOsnapCalculation(const AcArray<AcDbObjectId>& nestedEntity,
	                                   int gsSelectionMark)
{
  return false;
}
//
// This is where we take advantage of quite a bit of information
// provide by this big function to display multiline tooltip
// (new feature in Acad 2002) under the cursor aperture.
//
// It gets even more interesting when you mix it with OSNAP info.
//
// Have fun!
//
Acad::ErrorStatus 
CSampleIPM::monitorInputPoint(
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
     const AcArray<int>& gsSelectionMark,
     const AcArray<AcDbObjectId>& keyPointEntities,
     const AcArray< AcDbObjectIdArray,
     AcArrayObjectCopyReallocator< AcDbObjectIdArray > >& nestedKeyPointEntities,
     const AcArray<int>& keyPointGsSelectionMark,
     const AcArray<AcGeCurve3d*>& alignmentPaths,
     const AcGePoint3d& computedPoint,
     const TCHAR* pTooltipString)
{
	TCHAR mtooltipStr[1024],
		 tempStr[100];
	mtooltipStr[0] = _T('\0');

	Acad::ErrorStatus es;
	AcDbEntity* pEnt;
	AcDbObjectId highlightId = AcDbObjectId::kNull;

	if (pointComputed)
	{
		//
		// Analyze the aperture entities.
		//
		if (apertureEntities.length() > 0)
		{
			if(_tcslen(mtooltipStr) > 0)
                _tcscpy(mtooltipStr, _T("\nEntities under the cursor aperture:"));
			else
                _tcscpy(mtooltipStr, _T("Entities under the cursor aperture:"));

			for (int i = 0; i < apertureEntities.length(); ++i)
			{
				if (Acad::eOk != (es = acdbOpenAcDbEntity(pEnt, apertureEntities[i], AcDb::kForRead)))
					continue;

                _stprintf(tempStr, _T("\n  %s%s%d%s"), pEnt->isA()->name(), _T(" <Object ID: "), pEnt->objectId(), _T(">"));
					_tcscat(mtooltipStr, tempStr);
					pEnt->close();

					// Analyze the nested aperture entities.
					AcDbObjectIdArray nestedIds = nestedApertureEntities[i];
					int length = nestedIds.length();
					if (length > 1)
					{
						// There is a nested entitiy: get it.
						AcDbEntity* pEnt2;
						if (Acad::eOk == (es = acdbOpenAcDbEntity(pEnt2, nestedIds[length - 1], AcDb::kForRead))) {
                            _stprintf(tempStr, _T("\n  nested: %s"), pEnt2->isA()->name());
							_tcscat(mtooltipStr, tempStr);
							pEnt2->close();
						}
					}
			}
			highlightId = apertureEntities[0];
		}

		//
		// Analyze OSNAP.
		//

		if (history && Acad::eOsnapped)
		{
			TCHAR osnapInfo[500];
			osnapInfo[0] = _T('\0');

			switch (osnapMask)
			{
			case AcDb::kOsMaskEnd:
                _tcscpy(osnapInfo, _T("\nOsnap:\n  end"));
				break;
			case AcDb::kOsMaskMid:
                _tcscpy(osnapInfo, _T("\nOsnap:\n  mid"));
				break;
			case AcDb::kOsMaskCen:
                _tcscpy(osnapInfo, _T("\nOsnap:\n  center"));
				break;
			case AcDb::kOsMaskNode:
                _tcscpy(osnapInfo, _T("\nOsnap:\n  node"));
				break;
			case AcDb::kOsMaskQuad:
                _tcscpy(osnapInfo, _T("\nOsnap:\n  quadrant"));
				break;
			case AcDb::kOsMaskInt:
                _tcscpy(osnapInfo, _T("\nOsnap:\n  intersection"));
				break;
			case AcDb::kOsMaskIns:
                _tcscpy(osnapInfo, _T("\nOsnap:\n  insert"));
				break;
			case AcDb::kOsMaskPerp:
                _tcscpy(osnapInfo, _T("\nOsnap:\n  perpendicular"));
				break;
			case AcDb::kOsMaskTan:
                _tcscpy(osnapInfo, _T("\nOsnap:\n  tangent"));
				break;
			case AcDb::kOsMaskNear:
                _tcscpy(osnapInfo, _T("\nOsnap:\n  near"));
				break;
			case AcDb::kOsMaskQuick:
                _tcscpy(osnapInfo, _T("\nOsnap:\n  quick"));
				break;
			case AcDb::kOsMaskApint:
                _tcscpy(osnapInfo, _T("\nOsnap:\n  apint"));
				break;
			case AcDb::kOsMaskImmediate:
                _tcscpy(osnapInfo, _T("\nOsnap:\n  immediate"));
				break;

			case AcDb::kOsMaskAllowTan:
                _tcscpy(osnapInfo, _T("\nOsnap:\n  allowTan"));
				break;
			case AcDb::kOsMaskDisablePerp:
                _tcscpy(osnapInfo, _T("\nOsnap:\n  DisablePerp"));
				break;
			case AcDb::kOsMaskRelCartesian:
                _tcscpy(osnapInfo, _T("\nOsnap:\n  RelCartesian"));
				break;
			case AcDb::kOsMaskRelPolar:
                _tcscpy(osnapInfo, _T("\nOsnap:\n  RelPolar"));
				break;
			}
			if (_tcslen(osnapInfo))
			{
				if (keyPointEntities.length())
				{
                    _tcscat(osnapInfo, _T("\nKey entities:"));
					for (int i=0; i<keyPointEntities.length(); ++i)
					{
						if (Acad::eOk != (es = acdbOpenAcDbEntity(pEnt, keyPointEntities[i], AcDb::kForRead)))
							continue;

						_stprintf(tempStr, _T("\n    %s"), pEnt->isA()->name());
						_tcscat(osnapInfo, tempStr);
						pEnt->close();
					}
				}
			}
			_tcscat(mtooltipStr, osnapInfo);
		}
	}

	//
	// Do highlighting, only the top level entity is highlighted.
	//
	static AcDbObjectId oldHighlightId = AcDbObjectId::kNull;
	if(highlightId != oldHighlightId)
	{
		if (AcDbObjectId::kNull != oldHighlightId)
		{
			es = acdbOpenAcDbEntity(pEnt, oldHighlightId, AcDb::kForRead);
			if (es == Acad::eOk)
			{
				es = pEnt->unhighlight();
				pEnt->close();
				oldHighlightId = AcDbObjectId::kNull;
			}
		}
		es = acdbOpenAcDbEntity(pEnt, highlightId, AcDb::kForRead);
		if (es == Acad::eOk)
		{
			es = pEnt->highlight();
			pEnt->close();
			oldHighlightId = highlightId;
		}
	}

	// Turn on additional tooltip.
	bAppendToTooltipStr = true;
	pAdditionalTooltipString = _tcsdup(mtooltipStr);
	return Acad::eOk;
}

