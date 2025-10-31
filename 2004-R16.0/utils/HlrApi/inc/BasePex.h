//
// (C) Copyright 1998-2002 by Autodesk, Inc.
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


//-----------------------------------------------------------------------------
//----- Hidden Line Removal API
//----- by Cyrille Fauvel & Phil Holcombe
//----- Autodesk Developer Consulting Group
//----- June 10th, 1999
//-----------------------------------------------------------------------------
#pragma once

#include "Hlr.h"

#pragma warning (disable: 4275)

//-----------------------------------------------------------------------------
//----- AsdkHiddenLine Protocol extension abstract base
//----- class.  Notice that this is the lowest level that uses
//----- the ACRX macros.
class EXP_IMP AsdkHiddenLineBase: public AcRxObject {

protected:
	std::map<AcDbEntity *, AcDbVoidPtrArray *> m_entityBodies ;

public:
	ACRX_DECLARE_MEMBERS (AsdkHiddenLineBase) ;

	//----- Function to append BODY objects to the list
	//----- If required, then it also indicates which objects the
	//----- body was created from ( important for blocks )
	virtual Acad::ErrorStatus prepare (AcDbEntity *pEnt, AcDbVoidPtrArray &bodies, int control, const AcDbViewport *pVp) ;
	virtual Acad::ErrorStatus getBody (void *pBodyData, int control) ;

	static Acad::ErrorStatus saveData (AcDbEntity *pEnt, void *pBodyData) ;
	static Adesk::Boolean retrieveData (AcDbEntity *pEnt, AcDbVoidPtrArray &bodies, const AcDbViewport *pVp =NULL) ;
	
	static void clear () ;
	static void clear (AcDbEntity *pEnt) ;
	static void clear (AcDbEntity *pEnt, AcDbViewport *pVp) ;
} ;
