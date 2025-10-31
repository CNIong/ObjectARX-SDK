//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// Function prototype definitions for brreport.cpp.

#ifndef AC_BRREPORT_H
#define AC_BRREPORT_H 1

#include "adesk.h"
#include "gegbl.h"
#include "brgbl.h"
#include "brprops.h"


// forward class declarations
class AcGePoint3d;
class AcBrEntity;


void                errorReport		(AcBr::ErrorStatus errorCode);

void                entityAssociatedReport(AcBrEntity* entityAssociated);

void                ptContainmentReport(AcGe::PointContainment containment,
									    AcBrEntity*			   container);
 
void                lnContainmentReport(Adesk::UInt32& hitIndex,
										AcGePoint3d&   hitPoint,
									    AcBrEntity*    entityHit,
										AcBrEntity*    entityEntered);

void				propsReport		(AcBrMassProps& massProps,
									 double         area, 
									 double         length);

void				bblockReport	(AcGePoint3d& min, AcGePoint3d& max);

void				shellTypeReport	(AcBr::ShellType shellType);

void				loopTypeReport	(AcBr::LoopType loopType);
 

#endif
