// (C) Copyright 2001 by Autodesk, Inc. 
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
     char*& pAdditionalTooltipString,
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
     const char* pTooltipString)
{
	char mtooltipStr[1024],
		 tempStr[100];
	mtooltipStr[0] = '\0';

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
			if(strlen(mtooltipStr) > 0)
				strcpy(mtooltipStr, "\nEntities under the cursor aperture:");
			else
				strcpy(mtooltipStr, "Entities under the cursor aperture:");

			for (int i = 0; i < apertureEntities.length(); ++i)
			{
				if (Acad::eOk != (es = acdbOpenAcDbEntity(pEnt, apertureEntities[i], AcDb::kForRead)))
					continue;

					sprintf(tempStr, "\n  %s%s%d%s", pEnt->isA()->name(), " <Object ID: ", pEnt->objectId(), ">");
					strcat(mtooltipStr, tempStr);
					pEnt->close();

					// Analyze the nested aperture entities.
					AcDbObjectIdArray nestedIds = nestedApertureEntities[i];
					int length = nestedIds.length();
					if (length > 1)
					{
						// There is a nested entitiy: get it.
						AcDbEntity* pEnt2;
						if (Acad::eOk == (es = acdbOpenAcDbEntity(pEnt2, nestedIds[length - 1], AcDb::kForRead))) {
							sprintf(tempStr, "\n  nested: %s", pEnt2->isA()->name());
							strcat(mtooltipStr, tempStr);
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
			char osnapInfo[500];
			osnapInfo[0] = '\0';

			switch (osnapMask)
			{
			case AcDb::kOsMaskEnd:
				strcpy(osnapInfo, "\nOsnap:\n  end");
				break;
			case AcDb::kOsMaskMid:
				strcpy(osnapInfo, "\nOsnap:\n  mid");
				break;
			case AcDb::kOsMaskCen:
				strcpy(osnapInfo, "\nOsnap:\n  center");
				break;
			case AcDb::kOsMaskNode:
				strcpy(osnapInfo, "\nOsnap:\n  node");
				break;
			case AcDb::kOsMaskQuad:
				strcpy(osnapInfo, "\nOsnap:\n  quadrant");
				break;
			case AcDb::kOsMaskInt:
				strcpy(osnapInfo, "\nOsnap:\n  intersection");
				break;
			case AcDb::kOsMaskIns:
				strcpy(osnapInfo, "\nOsnap:\n  insert");
				break;
			case AcDb::kOsMaskPerp:
				strcpy(osnapInfo, "\nOsnap:\n  perpendicular");
				break;
			case AcDb::kOsMaskTan:
				strcpy(osnapInfo, "\nOsnap:\n  tangent");
				break;
			case AcDb::kOsMaskNear:
				strcpy(osnapInfo, "\nOsnap:\n  near");
				break;
			case AcDb::kOsMaskQuick:
				strcpy(osnapInfo, "\nOsnap:\n  quick");
				break;
			case AcDb::kOsMaskApint:
				strcpy(osnapInfo, "\nOsnap:\n  apint");
				break;
			case AcDb::kOsMaskImmediate:
				strcpy(osnapInfo, "\nOsnap:\n  immediate");
				break;

			case AcDb::kOsMaskAllowTan:
				strcpy(osnapInfo, "\nOsnap:\n  allowTan");
				break;
			case AcDb::kOsMaskDisablePerp:
				strcpy(osnapInfo, "\nOsnap:\n  DisablePerp");
				break;
			case AcDb::kOsMaskRelCartesian:
				strcpy(osnapInfo, "\nOsnap:\n  RelCartesian");
				break;
			case AcDb::kOsMaskRelPolar:
				strcpy(osnapInfo, "\nOsnap:\n  RelPolar");
				break;
			}
			if (strlen(osnapInfo))
			{
				if (keyPointEntities.length())
				{
					strcat(osnapInfo, "\nKey entities:");
					for (int i=0; i<keyPointEntities.length(); ++i)
					{
						if (Acad::eOk != (es = acdbOpenAcDbEntity(pEnt, keyPointEntities[i], AcDb::kForRead)))
							continue;

						sprintf(tempStr, "\n    %s", pEnt->isA()->name());
						strcat(osnapInfo, tempStr);
						pEnt->close();
					}
				}
			}
			strcat(mtooltipStr, osnapInfo);
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
	pAdditionalTooltipString = mtooltipStr;
	return Acad::eOk;
}

