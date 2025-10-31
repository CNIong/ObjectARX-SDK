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
//
#pragma warning( disable : 4101 )  // Disable warning message for unreferenced local variables

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include <acutads.h>
#include <aced.h>
#include <dbmain.h>
#include <dbents.h>
#include <dbpl.h>
#include <dbosnap.h>
#include <rxregsvc.h>
#include "tchar.h"

#include "DivOsnap.h"



void initApp();
void unloadApp();

AsdkDivOsnapMode<3> thirdMode( _T("THIrd"),_T("_THIrd"),_T("Third of length"), _T("1/3") );
AsdkDivOsnapMode<4> fourthMode( _T("FOUrth"),_T("_FOUrth"),_T("Quarter of length"), _T("1/4") );
AsdkDivOsnapMode<5> fifthMode( _T("FIFth"),_T("_FIFth"),_T("Fifth of length"), _T("1/5") );

void
snapToPolylineSegments()
{
    acutPrintf(_T("\nDivisor object snap will snap to polyline segments."));
    ASDK_DIVISOR_SNAP_TO_SEG(3);
    ASDK_DIVISOR_SNAP_TO_SEG(4);
    ASDK_DIVISOR_SNAP_TO_SEG(5);
}

void
snapToWholePolyline()
{
    acutPrintf(_T("\nDivisor object snap will snap to whole polyline."));
    ASDK_DIVISOR_SNAP_TO_PLINE(3);
    ASDK_DIVISOR_SNAP_TO_PLINE(4);
    ASDK_DIVISOR_SNAP_TO_PLINE(5);
}

// Put the boilerplate calls here, rather than in DivOsnapInfo.cpp/.h
// as we want to make one per actual class (i.e. one per template instance)
// The following throws compile error C2906 with the VC7.1/8.0 
// 'AcRxClass *AsdkDivOsnapInfo<i>::desc(void)' : 
// explicit specialization requires 'template <>'
//

//ACRX_NO_CONS_DEFINE_MEMBERS( AsdkDivOsnapInfo<3>, AcDbCustomOsnapInfo );
//ACRX_NO_CONS_DEFINE_MEMBERS( AsdkDivOsnapInfo<4>, AcDbCustomOsnapInfo );
//ACRX_NO_CONS_DEFINE_MEMBERS( AsdkDivOsnapInfo<5>, AcDbCustomOsnapInfo );

// We will redefine ACRX_NO_CONS_DEFINE_MEMBERS with a new macro that accepts 
// a template argument with explicit specialization
//

// notice template<> before declaration of the functions
#define ACRX_DEFINE_MEMBERS_TEMPLARG(CLASS_NAME) \
	template<>	AcRxClass* CLASS_NAME::desc() \
{ \
	if (CLASS_NAME::gpDesc != NULL) \
	return CLASS_NAME::gpDesc; \
	return CLASS_NAME::gpDesc \
	= (AcRxClass*)((AcRxDictionary*)acrxSysRegistry() \
	->at(ACRX_CLASS_DICTIONARY))->at(ACRX_T(#CLASS_NAME)); \
} \
	template<>	AcRxClass* CLASS_NAME::isA() const \
{ \
	if (CLASS_NAME::gpDesc != NULL) \
	return CLASS_NAME::gpDesc; \
	return CLASS_NAME::gpDesc \
	= (AcRxClass*)((AcRxDictionary*)acrxSysRegistry() \
	->at(ACRX_CLASS_DICTIONARY))->at(ACRX_T(#CLASS_NAME)); \
} \
	AcRxClass* CLASS_NAME::gpDesc = NULL

#define ACRX_NO_CONS_DEFINE_MEMBERS_TEMPLARG(CLASS_NAME,PARENT_CLASS) \
	ACRX_DEFINE_MEMBERS_TEMPLARG(CLASS_NAME); \
	void CLASS_NAME::rxInit() { \
	ACRX_STATIC_CHECK(CLASS_NAME); \
	CLASS_NAME::gpDesc = newAcRxClass(ACRX_T(#CLASS_NAME), ACRX_T(#PARENT_CLASS)); \
	}
ACRX_NO_CONS_DEFINE_MEMBERS_TEMPLARG( AsdkDivOsnapInfo<3>, AcDbCustomOsnapInfo );
ACRX_NO_CONS_DEFINE_MEMBERS_TEMPLARG( AsdkDivOsnapInfo<4>, AcDbCustomOsnapInfo );
ACRX_NO_CONS_DEFINE_MEMBERS_TEMPLARG( AsdkDivOsnapInfo<5>, AcDbCustomOsnapInfo );

void
initApp()
{
    acedRegCmds->addCommand( _T("ASDK_DIVISOR"), _T("ASDK_SNAP2PLINE"),    _T("SNAP2PLINE"),   ACRX_CMD_TRANSPARENT, snapToWholePolyline );
    acedRegCmds->addCommand( _T("ASDK_DIVISOR"), _T("ASDK_SNAP2SEG"),      _T("SNAP2SEG"),     ACRX_CMD_TRANSPARENT, snapToPolylineSegments );

    // Add parent protocol extension class to hierarchy
    AsdkDivOsnapInfo<3>::rxInit();
    AsdkDivOsnapInfo<4>::rxInit();
    AsdkDivOsnapInfo<5>::rxInit();
    acrxBuildClassHierarchy();

    ASDK_DEFINE_DIVISOR_OSNAP(3,thirdMode,_T("_third"));
    ASDK_DEFINE_DIVISOR_OSNAP(4,fourthMode,_T("_fourth"));
    ASDK_DEFINE_DIVISOR_OSNAP(5,fifthMode,_T("_fifth"));

    snapToWholePolyline();
}

void
unloadApp()
{
    acedRegCmds->removeGroup( _T("ASDK_DIVISOR") );

    ASDK_REMOVE_DIVISOR_OSNAP(3,thirdMode);
    ASDK_REMOVE_DIVISOR_OSNAP(4,fourthMode);
    ASDK_REMOVE_DIVISOR_OSNAP(5,fifthMode);

    deleteAcRxClass( AsdkDivOsnapInfo<3>::desc() );
    deleteAcRxClass( AsdkDivOsnapInfo<4>::desc() );
    deleteAcRxClass( AsdkDivOsnapInfo<5>::desc() );
}

extern "C" __declspec(dllexport) AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void *p)
{
    switch (msg)
    {
    case AcRx::kInitAppMsg:
        acrxRegisterAppMDIAware(p);
        acrxUnlockApplication(p);
        initApp();
        break;
    case AcRx::kUnloadAppMsg:
        unloadApp();
        break;
    }
    return AcRx::kRetOK;
}
