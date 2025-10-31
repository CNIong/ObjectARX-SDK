//
// (C) Copyright 1998-1999 by Autodesk, Inc. 
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
#include "DivOsnapMode.h"
#include "DivOsnapInfo.h"

#define ASDK_DEFINE_DIVISOR_OSNAP(DIV,MODEOBJECT,MODESTRING) \
ASDK_DEFINE_DIVISOR_OSNAP_TYPE(DIV,Entity); \
ASDK_DEFINE_DIVISOR_OSNAP_TYPE(DIV,Curve); \
ASDK_DEFINE_DIVISOR_OSNAP_TYPE(DIV,Polyline); \
acdbCustomOsnapManager()->addCustomOsnapMode(&MODEOBJECT); \
acdbCustomOsnapManager()->activateOsnapMode(MODESTRING);

#define ASDK_DEFINE_DIVISOR_OSNAP_TYPE(DIV,ENTITYTYPE) \
AsdkDivOsnap##ENTITYTYPE##Info<DIV> *p##ENTITYTYPE##Info##DIV = new AsdkDivOsnap##ENTITYTYPE##Info<DIV>; \
AcDb##ENTITYTYPE::desc()->addX( AsdkDivOsnapInfo<DIV>::desc(), p##ENTITYTYPE##Info##DIV );

#define ASDK_REMOVE_DIVISOR_OSNAP(DIV,MODEOBJECT) \
acdbCustomOsnapManager()->removeCustomOsnapMode(&MODEOBJECT); \
AcDbEntity::desc()->delX( AsdkDivOsnapInfo<DIV>::desc() ); \
AcDbCurve::desc()->delX( AsdkDivOsnapInfo<DIV>::desc() ); \
AcDbPolyline::desc()->delX( AsdkDivOsnapInfo<DIV>::desc() );

#define ASDK_DIVISOR_SNAP_TO_SEG(DIV) \
AcRxObject *pObj##DIV = AcDbPolyline::desc()->queryX( AsdkDivOsnapInfo<DIV>::desc() ); \
if ( NULL != pObj##DIV ) ((AsdkDivOsnapPolylineInfo<DIV>*)pObj##DIV)->setSnapToSegments( true );

#define ASDK_DIVISOR_SNAP_TO_PLINE(DIV) \
AcRxObject *pObj##DIV = AcDbPolyline::desc()->queryX( AsdkDivOsnapInfo<DIV>::desc() ); \
if ( NULL != pObj##DIV ) ((AsdkDivOsnapPolylineInfo<DIV>*)pObj##DIV)->setSnapToSegments( false );
