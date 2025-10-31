//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
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
    //----- body was created from (important for blocks)
    virtual Acad::ErrorStatus prepare (AcDbEntity *pEnt, AcDbVoidPtrArray &bodies, int control, const AcDbViewport *pVp) ;
    virtual Acad::ErrorStatus getBody (void *pBodyData, int control) ;

    static Acad::ErrorStatus saveData (AcDbEntity *pEnt, void *pBodyData) ;
    static Adesk::Boolean retrieveData (AcDbEntity *pEnt, AcDbVoidPtrArray &bodies, const AcDbViewport *pVp =NULL) ;
	
    static void clear () ;
    static void clear (AcDbEntity *pEnt) ;
    static void clear (AcDbEntity *pEnt, AcDbViewport *pVp) ;

    // Utility function, creating AcDbBody entities for input pEnt, using this PE
    // ents array contains resulting entities. Caller needs to delete them
    //
    static Acad::ErrorStatus getBodyEntities (AcDbEntity *pEnt, AcDbVoidPtrArray &ents, int control, const AcDbViewport *pVp);
} ;
