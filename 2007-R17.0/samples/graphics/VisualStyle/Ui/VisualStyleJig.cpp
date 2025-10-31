//
// (C) Copyright 2005-2006 by Autodesk, Inc. 
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

// VisualStyleJig.cpp - editor jig definition for Visual Style entity
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(_FULLDEBUG_)
#define _DEBUG_WAS_DEFINED
#pragma message ("       Compiling MFC /STL /ATL header files in release mode.")
#undef _DEBUG
#endif


#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "geassign.h"
#include "AdskDMgr.h"
#include "..\Db\AsdkVisualStyle.h"
#include "VisualStyleJig.h"

#ifdef _DEBUG_WAS_DEFINED
#define _DEBUG
#undef _DEBUG_WAS_DEFINED
#endif


ACRX_DEFINE_MEMBERS( AsdkVisualStyle );

class JigVariables
{
public:
	JigVariables(){ m_lastWidth = 0.0; };
	double m_lastWidth;
};

AsdkDataManager< JigVariables > jigDataMgr;


VisualStyleJig::VisualStyleJig(
    const AcGePoint3d& center,
    const AcDbObjectId& visualStyleId)
{
    mpVisualStyleEnt = (AsdkVisualStyle*)AsdkVisualStyle::desc()->create();
    mpVisualStyleEnt->setDatabaseDefaults();
    mpVisualStyleEnt->setVisualStyleId(visualStyleId);

    AcGeMatrix3d translateVStyle;
    translateVStyle.setToTranslation(center.asVector());
    mpVisualStyleEnt->setTransform(translateVStyle);
}


// This is the main jig method, which acquires the appropriate information to define the entity
//
void
VisualStyleJig::start()
{
    acutPrintf(ACRX_T("\nWidth <%.4f>: "), jigDataMgr.docData().m_lastWidth);

    AcEdJig::DragStatus stat = drag();

    if (stat == kNormal)
    {
        jigDataMgr.docData().m_lastWidth = mWidth;
        append();
    }
    else
        delete mpVisualStyleEnt;

    mpVisualStyleEnt = NULL;
}

AcEdJig::DragStatus
VisualStyleJig::sampler()
{
    double dist;

    setUserInputControls( ( UserInputControls )
        ( kNullResponseAccepted | kAccept3dCoordinates |
          kGovernedByOrthoMode  | kDontUpdateLastPoint ));

    DragStatus stat = acquireDist( dist, mpVisualStyleEnt->center() );

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
VisualStyleJig::update()
{
    AcGeMatrix3d translateVStyle;
    translateVStyle.setToTranslation(mpVisualStyleEnt->center().asVector());

    double scale = mWidth ? mWidth : 1.0;
    AcGeMatrix3d scaleVStyle;
    AcGeScale3d(scale, scale, 1.0).getMatrix(scaleVStyle);

    mpVisualStyleEnt->setTransform(translateVStyle * scaleVStyle);

    return Adesk::kTrue;
}

AcDbEntity *
VisualStyleJig::entity() const
{
    return mpVisualStyleEnt;
}

