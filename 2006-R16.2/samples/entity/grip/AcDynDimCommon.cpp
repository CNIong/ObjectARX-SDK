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
	if (dynDimSetting & AcDbDimData::DimDataFlags::kDimEditable)
		dimdata->setDimEditable(true);
	if (dynDimSetting & AcDbDimData::DimDataFlags::kDimInvisible)
		dimdata->setDimInvisible(true);
	if (dynDimSetting & AcDbDimData::DimDataFlags::kDimFocal)
		dimdata->setDimFocal(true);
	if (dynDimSetting & AcDbDimData::DimDataFlags::kDimHideIfValueIsZero)
		dimdata->setDimHideIfValueIsZero(true);
	if (dynDimSetting & AcDbDimData::DimDataFlags::kDimResultantLength)
		dimdata->setDimResultantLength(true);
	if (dynDimSetting & AcDbDimData::DimDataFlags::kDimDeltaLength)
		dimdata->setDimDeltaLength(true);
	if (dynDimSetting & AcDbDimData::DimDataFlags::kDimResultantAngle)
		dimdata->setDimResultantAngle(true);
	if (dynDimSetting & AcDbDimData::DimDataFlags::kDimDeltaAngle)
		dimdata->setDimDeltaAngle(true);
	if (dynDimSetting & AcDbDimData::DimDataFlags::kDimRadius)
		dimdata->setDimRadius(true);

	return true;
}
