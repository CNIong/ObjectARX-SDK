//  Copyright 2004 by Autodesk, Inc.
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
#include "acpublishreactors.h"
#include "acdmmapi.h"

//clients who desire notifications of the key publish events will derive
//from AcPublishReactor and instantiate this class. These reactors are called 
//only during Publish to DWF operations.
//Clients are responsible for obtaining configuration data for their
//metadata publication from the AcPublishReactor

class AcTestPublishReactor : public AcPublishReactor
{
 public:
	
    void OnAboutToBeginPublishing(AcPublishBeginJobInfo *pInfo);
    void OnBeginPublishingSheet(AcPublishSheetInfo *pInfo);
	void OnAboutToEndPublishing(AcPublishReactorInfo *pInfo);
	void OnEndPublish(AcPublishReactorInfo *pInfo);
	void OnCancelledOrFailedPublishing(AcPublishReactorInfo *pInfo);
	void OnBeginAggregation(AcPublishAggregationInfo *pInfo);
	void OnEndAggregation(AcPublishAggregationInfo *pInfo);
	virtual ~AcTestPublishReactor() {};

	AcTestPublishReactor() {};
}; 



