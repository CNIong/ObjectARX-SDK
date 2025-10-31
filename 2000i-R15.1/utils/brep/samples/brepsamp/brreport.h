#ifndef AC_BRREPORT_H
#define AC_BRREPORT_H 1
// (C) Copyright 1996-1999 by Autodesk, Inc. 
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
// DESCRIPTION:
//
// Function prototype definitions for brreport.cpp.


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
