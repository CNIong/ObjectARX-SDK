//  Copyright 2004-2006 by Autodesk, Inc.
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

#include "acpublishreactors.h"
#include "DWFReactors.h"
#include "DWFEntReactor.h"



extern HINSTANCE ghInst1;
extern AcTestDMMEntReactor  gClientDMMReactor;


/// In the case of foreground publish jobs, this is the first notification 
/// clients will receive; it allows them to examine and modify DSD their data.
/// 
/// The AcDMMReactorManager, which is required to support these reactors,
/// only exists when AcPublish is running. The recommended practice is
/// to call this function in an AcPublishReactor OnAboutToBeginPublishing
/// and remove your DMM reactors in both OnEndPublish and in
/// OnCancelledOrFailedPublishing. Note that AcEPlotX must also be loaded
/// since that is where the AcDMMReactorManager is implemented.
/// 

void
AcTestPublishReactor ::OnAboutToBeginPublishing(AcPublishBeginJobInfo *pInfo)
{

	if (pInfo->GetDSDData()->sheetType() != AcPlDSDEntry::kOriginalDevice)
	{
#ifdef DMM_API
		acutPrintf(_T("OnAboutToBeginPublishing\n"));
		CString str = pInfo->GetDSDData()->destinationName();
		CString strLogFilepath = pInfo->GetDSDData()->logFilePath();
		acutPrintf (_T("DWF File Name = %s\n"), pInfo->GetDSDData()->destinationName());
#endif
		if (ghInst1)
		{				
			ACGLOBADDDMMREACTOR pAcGlobalAddDMMReactor =
			(ACGLOBADDDMMREACTOR)GetProcAddress(ghInst1, "AcGlobAddDMMReactor");
			if (NULL != pAcGlobalAddDMMReactor)
			{
				pAcGlobalAddDMMReactor(&gClientDMMReactor);
			}
		}
	}
	else
	{
		acutPrintf (_T("Not a publishing job\n"));
		return;
	}
}

void
AcTestPublishReactor ::OnBeginPublishingSheet(AcPublishSheetInfo *pInfo)
{
#ifdef DMM_API
	acutPrintf(_T("OnBeginPublishingSheet\n"));
	CString strUniqueId =  pInfo->GetUniqueId();
	const AcPlDSDEntry *dsdDataEntry =  pInfo->GetDSDEntry();
	CString strLayoutName = dsdDataEntry->layout();
	acutPrintf (_T("Layout = %s and UniqueId = %s\n"), strLayoutName, strUniqueId);
	pInfo->GetPlotLogger()->logMessage(_T("OnBeginPublishingSheet using DWF Metadata API"));
#endif

}

/// No changes are made in this notifier
void 
AcTestPublishReactor ::OnAboutToEndPublishing(AcPublishReactorInfo *pInfo)
{
#ifdef DMM_API
	acutPrintf(_T("OnAboutToEndPublishing\n"));
#endif
}

///Just a bookmark for end of job. No changes are made in this notifier.
void 
AcTestPublishReactor ::OnEndPublish(AcPublishReactorInfo *pInfo)
{

#ifdef DMM_API
	acutPrintf(_T("OnEndPublish\n"));
#endif
	if (ghInst1)
	{	
		ACGLOBREMOVEDMMREACTOR pAcGlobalRemoveDMMReactor =
		(ACGLOBREMOVEDMMREACTOR)GetProcAddress(ghInst1, "AcGlobRemoveDMMReactor");
		if (NULL != pAcGlobalRemoveDMMReactor)
		{
			pAcGlobalRemoveDMMReactor(&gClientDMMReactor);
		}
	}
}

/// No changes are made in this notifier.
void 
AcTestPublishReactor ::OnCancelledOrFailedPublishing(AcPublishReactorInfo *pInfo)
{
#ifdef DMM_API
	acutPrintf(_T("OnCancelledOrFailedPublishing\n"));
#endif
	if (ghInst1)
	{	
		ACGLOBREMOVEDMMREACTOR pAcGlobalRemoveDMMReactor =
		(ACGLOBREMOVEDMMREACTOR)GetProcAddress(ghInst1, "AcGlobRemoveDMMReactor");
		if (NULL != pAcGlobalRemoveDMMReactor)
		{
			pAcGlobalRemoveDMMReactor(&gClientDMMReactor);
		}
	}
}
///
/// For adding global properties we need to wait just after 
/// OnBeginAggregation(). This notification is sent after all of the 
/// temporary DWF files for the job have been plotted and 
/// aggregation into a single multisheet DWF is about to begin.
/// 
/// AcPublishAggregationInfo is context data, it allows clients to add 
/// ePlot global properties and resources to the DWF
///

void 
AcTestPublishReactor ::OnBeginAggregation(AcPublishAggregationInfo *pAggreGationInfo)
{	
#ifdef DMM_API
	acutPrintf(_T("OnBeginAggregation\n"));		
#endif
	//appropriate location to add sheet level metadata
	AcDMMEPlotProperty testprop1(L"Description", L"Description through API");	
	testprop1.SetCategory(L"DMMAPI");
	AcDMMEPlotProperty testprop2(L"Sheet Number", L"Sheet Number through API");
	testprop2.SetCategory(L"DMMAPI");
	AcDMMEPlotProperty testprop3(L"Name", L"Value");
	testprop3.SetCategory(L"DMMAPI");
	AcDMMEPlotPropertyVec vec;
	vec.clear();
	vec.push_back(testprop1);
	vec.push_back(testprop2);
	vec.push_back(testprop3);
	pAggreGationInfo->AddGlobalProperties(vec);
}

void 
AcTestPublishReactor ::OnEndAggregation(AcPublishAggregationInfo *pAggreGationInfo)
{
#ifdef DMM_API
	acutPrintf(_T("OnEndAggregation\n"));
#endif
}

