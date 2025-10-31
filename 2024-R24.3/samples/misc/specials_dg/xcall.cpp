//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
// Description:  This is a made up version of what you'd need if not using
//               the ACRX_X_CALL macro in tempapp.cpp
//

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

AcDbEntity *pEnt;
AsdkEntTemperature *pTemp;

pTemp = AsdkEntTemperature::cast(
    pEnt->x(AsdkEntTemperature::desc()));

double eTemp = pTemp->reflectedEnergy(pEnt);

// END CODE APPEARING IN SDK DOCUMENT.
