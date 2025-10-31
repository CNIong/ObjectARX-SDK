//
// (C) Copyright 1998-2006 by Autodesk, Inc. 
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

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "acrectjig.h"
#include "geassign.h"
#include "acmain.h"
#include "acrect.h"
#include <math.h>



//////////////////////////////////////////////////////////////////////////
// sets the dynamic dimension properties to the value passed
bool AcDynDimCommon::getDynDimSettings(AcDbDimData *dimdata, enum AcDbDimData::DimDataFlags dynDimSetting)
{
	// reset the data
	dimdata->setDimEditable(false);
	dimdata->setDimInvisible(false);
	dimdata->setDimFocal(false);
	dimdata->setDimHideIfValueIsZero(false);
	dimdata->setDimResultantLength(false);
	dimdata->setDimDeltaLength(false);
	dimdata->setDimResultantAngle(false);
	dimdata->setDimDeltaAngle(false);
	dimdata->setDimRadius(false);

	// check what the setting is for this dimension
	// this is configured using the SETDYNDIMMODES command 
	if (dynDimSetting & AcDbDimData::kDimEditable)
		dimdata->setDimEditable(true);
	if (dynDimSetting & AcDbDimData::kDimInvisible)
		dimdata->setDimInvisible(true);
	if (dynDimSetting & AcDbDimData::kDimFocal)
		dimdata->setDimFocal(true);
	if (dynDimSetting & AcDbDimData::kDimHideIfValueIsZero)
		dimdata->setDimHideIfValueIsZero(true);
	if (dynDimSetting & AcDbDimData::kDimResultantLength)
		dimdata->setDimResultantLength(true);
	if (dynDimSetting & AcDbDimData::kDimDeltaLength)
		dimdata->setDimDeltaLength(true);
	if (dynDimSetting & AcDbDimData::kDimResultantAngle)
		dimdata->setDimResultantAngle(true);
	if (dynDimSetting & AcDbDimData::kDimDeltaAngle)
		dimdata->setDimDeltaAngle(true);
	if (dynDimSetting & AcDbDimData::kDimRadius)
		dimdata->setDimRadius(true);

	return true;
}
