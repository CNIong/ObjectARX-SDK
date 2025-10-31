//
// (C) Copyright 2000-2002 by Autodesk, Inc. 
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

// SmileJig.cpp - editor jig definition for Smiley entity

#include "StdAfx.h"
#include "StdArx.h"

#include <aced.h>
#include <geassign.h>
#include <stdio.h>
#include <adslib.h>
#include <dbapserv.h>

#include "AdskDMgr.h"

#include "..\SmileyDb\AsdkSmiley.h"
#include "SmileJig.h"

ACRX_DEFINE_MEMBERS( AsdkSmiley );

class JigVariables
{
public:
	JigVariables(){ m_lastRadius = 0.0; };
	double m_lastRadius;
};

AsdkDataManager< JigVariables > jigDataMgr;

SmileyJig::SmileyJig(
    const AcGePoint3d& p,
    const AcGeVector3d& n)
{
    mpSmiley = (AsdkSmiley*)AsdkSmiley::desc()->create();
    mpSmiley->setDatabaseDefaults();
    mpSmiley->setCenter( p );
    mpSmiley->setNormal( n );

	// Set the Smiley background to AutoCAD's Client workspace color.
	AcColorSettings pAcadColors;
	acedGetCurrentColors(&pAcadColors);
	DWORD backcolorDW= pAcadColors.dwGfxModelBkColor;
	
	AcCmEntityColor backcolor;
	backcolor.setColorMethod(AcCmEntityColor::kByColor);
	backcolor.setRGB( GetRValue(backcolorDW),GetGValue(backcolorDW),GetBValue(backcolorDW) );	
	mpSmiley->setBackColor(backcolor);
}


// This is the main jig method, which acquires the appropriate information to define the smiley
//
void
SmileyJig::start()
{
    char messBuf[80];

    if ( jigDataMgr.docData().m_lastRadius > 0.0 )
        sprintf( messBuf, "\nRadius <%.4f>: ", jigDataMgr.docData().m_lastRadius );
    else
        sprintf( messBuf, "\nRadius: ", jigDataMgr.docData().m_lastRadius );

    setDispPrompt( messBuf );
    AcEdJig::DragStatus stat = drag();

    if ( kNormal == stat ){
        jigDataMgr.docData().m_lastRadius = mradius;
        append();
    }
    else {
        delete mpSmiley;
    }
    mpSmiley = NULL;
}

AcEdJig::DragStatus
SmileyJig::sampler()
{
    double dist;

    setUserInputControls( ( UserInputControls )
        ( kNullResponseAccepted | kAccept3dCoordinates |
          kGovernedByOrthoMode  | kDontUpdateLastPoint ));

    DragStatus stat = acquireDist( dist, mpSmiley->center() );
    if ( kNull == stat ){
        mradius = jigDataMgr.docData().m_lastRadius;
        stat = kNormal;
    }
    else if ( kNormal == stat ) {
        if (0.0 >= dist)
            stat = kOther;
        else {
            // save new radius for later update of our entity
            if ( dist != mradius )
                mradius = dist;
            else
                stat = kNoChange;
        }
    }
    return stat;
}

Adesk::Boolean
SmileyJig::update()
{
    mpSmiley->scaleRadius( mradius );
	return Adesk::kTrue;
}

AcDbEntity *
SmileyJig::entity() const
{
    return mpSmiley;
}

void
createSmiley()
{
    AcGePoint3d cen;
    struct resbuf rbFrom, rbTo;

    ads_getpoint( NULL, "\nCenter point: ", asDblArray( cen ));

    rbFrom.restype = RTSHORT;
    rbFrom.resval.rint = 1; // from UCS
    rbTo.restype = RTSHORT;
    rbTo.resval.rint = 0; // to WCS

    ads_trans( asDblArray( cen ), &rbFrom, &rbTo, Adesk::kFalse, asDblArray( cen ));

    AcGeVector3d x = acdbHostApplicationServices()->workingDatabase()->ucsxdir();
    AcGeVector3d y = acdbHostApplicationServices()->workingDatabase()->ucsydir();

    AcGeVector3d normalVec = x.crossProduct( y );
    normalVec.normalize();

    SmileyJig jig( cen, normalVec );

    jig.start();
}
