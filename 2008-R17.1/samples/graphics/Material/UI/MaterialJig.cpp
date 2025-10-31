//
// (C) Copyright 2002-2007 by Autodesk, Inc. 
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
//

// MaterialJig.cpp - editor jig definition for Material entity
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif


#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "geassign.h"
#include "AdskDMgr.h"
#include "..\Db\AsdkMaterial.h"
#include "MaterialJig.h"

#pragma warning(disable: 4996) 


ACRX_DEFINE_MEMBERS( AsdkMaterial );

class JigVariables
{
public:
    JigVariables(){ m_lastWidth = 0.0; };
    double m_lastWidth;
};

AsdkDataManager< JigVariables > jigDataMgr;


MaterialJig::MaterialJig(
    const AcGePoint3d& center,
    const AcDbObjectId& materialId)
{
    mpMaterialEnt = (AsdkMaterial*)AsdkMaterial::desc()->create();
    mpMaterialEnt->setDatabaseDefaults();
    mpMaterialEnt->setMaterialId(materialId);

    AcGeMatrix3d translateMat;
    translateMat.setToTranslation(center.asVector());
    mpMaterialEnt->setTransform(translateMat);
}


// This is the main jig method, which acquires the appropriate information to define the entity
//
void
MaterialJig::start()
{
    TCHAR messBuf[80];
    _stprintf(messBuf, _T("\nWidth <%.4f>: "), jigDataMgr.docData().m_lastWidth );
    acutPrintf(messBuf);

    AcEdJig::DragStatus stat = drag();

    if (stat == kNormal)
    {
        jigDataMgr.docData().m_lastWidth = mWidth;
        append();
    }
    else
        delete mpMaterialEnt;

    mpMaterialEnt = NULL;
}

AcEdJig::DragStatus
MaterialJig::sampler()
{
    double dist;

    setUserInputControls( ( UserInputControls )
        ( kNullResponseAccepted | kAccept3dCoordinates |
          kGovernedByOrthoMode  | kDontUpdateLastPoint ));

    DragStatus stat = acquireDist( dist, mpMaterialEnt->center() );

    switch (stat) {

    case kNull:
        mWidth = jigDataMgr.docData().m_lastWidth;
        stat = kNormal;
        break;

    case kNormal:
        if (dist <= 0.0)
            stat = kOther;
        else {
            // save new width for later update of our entity
            if ( dist != mWidth )
                mWidth = dist;
            else
                stat = kNoChange;
        }
        break;
    }

    return stat;
}

Adesk::Boolean
MaterialJig::update()
{
    AcGeMatrix3d translateMat;
    translateMat.setToTranslation(mpMaterialEnt->center().asVector());

    double scale = mWidth ? mWidth : 1.0;
    AcGeMatrix3d scaleMat;
    AcGeScale3d(scale, scale, 1.0).getMatrix(scaleMat);

    mpMaterialEnt->setTransform(translateMat * scaleMat);

    return Adesk::kTrue;
}

AcDbEntity *
MaterialJig::entity() const
{
    return mpMaterialEnt;
}

