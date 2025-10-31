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

// AsdkSmiley custom object.

#include "StdAfx.h"
#include "StdArx.h"
#include "dbproxy.h"
#include "geassign.h"
#include "acgi.h"
#include "dbcolor.h"


#include <objbase.h>

#define VERSION_ASDKSMILEY 1


//{{AFX_ARX_MACRO
ACRX_DXF_DEFINE_MEMBERS(AsdkSmiley, AcDbEntity,
                        AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent,
                        AcDbProxyEntity::kTransformAllowed ||
                        AcDbProxyEntity::kColorChangeAllowed ||
                        AcDbProxyEntity::kLayerChangeAllowed,
                        ASDKSMILEY, AsdkSmileyDb|Product: ObjectDBX Enabler for Smiley Entity|Company: Autodesk Developer Consulting Group|Website: www.autodesk.com/adn/devhelp
);
//}}AFX_ARX_MACRO


bool AsdkSmiley::s_bHasClsid;
CLSID AsdkSmiley::s_clsid;

const double kPi = 3.14159;

const char kClassName[] = "AsdkSmiley";

const double kCurrentVersionNumber = 1.0;

MAKE_ACDBOPENOBJECT_FUNCTION( AsdkSmiley );

AsdkSmiley::AsdkSmiley()
{
    setNormal( AcGeVector3d( 0,0,1 ));
    setCenter( AcGePoint3d( 0,0,0 ));
    
    setRadius( 1.0 );

    double h = 0.4,
           d = 0.9,
           s = 0.15,
           xstart = 0.9 * sin( 1.25 * kPi ),
           ystart = 0.9 * cos( 1.25 * kPi ),
           xend = 0.9 * cos( 1.75 * kPi ),
           yend = 0.9 * sin( 1.75 * kPi );
    setEyesApart( d );
    setEyesHeight( h );
    setEyeSize( s );

    AcGeVector3d vecstart( xstart, ystart, 0 ),
                 vecend( xend, yend, 0 ),
                 vecbottom( 0, -1.0, 0 );
    AcGePoint3d mouthcen( center() );
    mouthcen[Y] += 0.4;

    setMouth( mouthcen + vecstart, mouthcen + vecbottom, mouthcen + vecend );
	
	// Set the default fill color to True Color Yellow.
	AcCmEntityColor fillcolor;
	fillcolor.setRGB(255,255,0);
	setColor(fillcolor);

	// Set the default background color to True Color black.
	mbackcolor.setRGB(0,0,0);
}

AsdkSmiley::~AsdkSmiley()
{
}

// initialise the static member corresponding to the CLSID
void
AsdkSmiley::initCLSID()
{
	s_bHasClsid = SUCCEEDED(CLSIDFromProgID(L"SmileyDb.Entity",&s_clsid));
}

// return the CLSID for OPM usage
Acad::ErrorStatus
AsdkSmiley::getClassID(CLSID* pClsid) const
{
    assertReadEnabled();
	if ( s_bHasClsid )
	{
		*pClsid = s_clsid;
		return Acad::eOk;
	}
	else
		return Acad::eNotImplementedYet;
}

AcCmEntityColor AsdkSmiley::backColor()
{
	assertReadEnabled();
	return mbackcolor;
}


Acad::ErrorStatus AsdkSmiley::setBackColor( const AcCmEntityColor& color)
{
	assertWriteEnabled();
	mbackcolor=color;
	return Acad::eOk;
}


Acad::ErrorStatus AsdkSmiley::setColor( const AcCmEntityColor& color, Adesk::Boolean doSubents )
{
	assertWriteEnabled();
	AcCmColor tcolor;
	tcolor.setRGB(color.red(),color.green(),color.blue());
	tcolor.setColorMethod(AcCmEntityColor::kByColor);
	return AcDbEntity::setColor(tcolor, doSubents);
}

void AsdkSmiley::ensureRadius()
{
    AcGeVector2d vec( meyesapart / 2, meyesheight );
    if (( vec.length() + 1.2 * meyesize ) > radius() )
        setRadius( vec.length() + 1.2 * meyesize);

    AcGePoint3d center( center() ),
                smilecen( mouthCenter() ),
                startpt( mouthLeft() ),
				endpt( mouthRight() ),
				botpt( mouthBottom() );

    AcGeVector3d vecstart = startpt - smilecen;

    if ( center.distanceTo( startpt ) > radius() / 1.1 )
        setRadius( 1.1 * center.distanceTo( startpt ));
    
	if ( center.distanceTo( endpt ) > radius() / 1.1 )
        setRadius( 1.1 * center.distanceTo( endpt ));

	if ( center.distanceTo( botpt ) > radius() / 1.1 )
        setRadius( 1.1 * center.distanceTo( botpt ));
}

Adesk::Boolean
AsdkSmiley::worldDraw(AcGiWorldDraw *wd)
{
    assertReadEnabled();

    AcGeVector3d offset(0,0,0);
    AcGeCircArc3d face = mfacecircle;

    // If dragging, don't fill the smiley
    //
    if( wd->isDragging() ){
		wd->subEntityTraits().setTrueColor(entityColor()); // Returns a 'True' true color.
        wd->subEntityTraits().setFillType( kAcGiFillNever );
    }
    else
        wd->subEntityTraits().setFillType( kAcGiFillAlways );

    // Give the circle a GS marker of 1
    //
    wd->subEntityTraits().setSelectionMarker( 1 );
    wd->geometry().circle( face.center(), face.radius(), mnormal );

    if( !wd->isDragging() )
		wd->subEntityTraits().setTrueColor(mbackcolor);// Set the background true color.

    // Give the eyes GS markers of 2 etc.
    //
    AcGePoint3dArray eyearray;

    eyes( eyearray );
    for( int i = 0; i < eyearray.length(); i++ ){
        wd->subEntityTraits().setSelectionMarker( i + 2 );
        wd->geometry().circle( eyearray.at(i) + offset, meyesize, mnormal );
    }

    AcGePoint3d smilecen( mouthCenter() + offset ),
                startpt( mouthLeft() + offset ),
                endpt( mouthRight() + offset );
    AcGeVector3d startvec = startpt - smilecen,
                 endvec = endpt - smilecen;
    double mouthangle = startvec.angleTo( endvec );

    wd->subEntityTraits().setSelectionMarker( eyearray.length() + 2 );
    wd->geometry().circularArc( smilecen, mouthRadius(), mnormal, startvec, mouthangle, kAcGiArcChord );
    return Adesk::kTrue;
}

Acad::ErrorStatus
AsdkSmiley::dwgInFields(AcDbDwgFiler *filer)
{
    assertWriteEnabled();

    AcDbEntity::dwgInFields( filer );

    // Read version number
    double version;
    filer->readItem( &version );

    if ( version > kCurrentVersionNumber ){
        ads_printf( "\nNew version of AsdkSmiley object found (version %.1f found, version %.1f supported): upgrade your Smiley.dbx to enable these objects.", version, kCurrentVersionNumber );
        return Acad::eMakeMeProxy;
    }

    AcGePoint3d center, mouthleftpt, mouthbottompt, mouthrightpt;
    double radius;
    filer->readItem( &center );
    filer->readItem( &radius );
    setCenter( center );
    setRadius( radius );
    filer->readItem( &mnormal );
    filer->readItem( &meyesapart );
    filer->readItem( &meyesheight );
    filer->readItem( &meyesize );
    filer->readItem( &mouthleftpt );
    filer->readItem( &mouthbottompt );
    filer->readItem( &mouthrightpt );
	
	setMouth( mouthleftpt, mouthbottompt, mouthrightpt );
	
	// Read in the background color.
	Adesk::UInt32 backColor;
	filer->readUInt32(&backColor);
	mbackcolor.setColor(backColor);
    	
    return filer->filerStatus();
}

Acad::ErrorStatus
AsdkSmiley::dwgOutFields(AcDbDwgFiler *filer) const
{
    assertReadEnabled();

    AcDbEntity::dwgOutFields( filer );

    // Write version number
    filer->writeItem( kCurrentVersionNumber );
    filer->writeItem( center() );
    filer->writeItem( radius() );
    filer->writeItem( mnormal );
    filer->writeItem( meyesapart );
    filer->writeItem( meyesheight );
    filer->writeItem( meyesize );
    filer->writeItem( mouthLeft() );
    filer->writeItem( mouthBottom() );
    filer->writeItem( mouthRight() );

	// Write the background color
	filer->writeUInt32(mbackcolor.trueColor());
	
    return filer->filerStatus();
}

Acad::ErrorStatus
AsdkSmiley::dxfInFields(AcDbDxfFiler *filer)
{
    assertWriteEnabled();

    struct resbuf rb;
    AcGePoint3d center, mouthleftpt, mouthbottompt, mouthrightpt;
    double radius;

    Acad::ErrorStatus es = AcDbEntity::dxfInFields( filer );

    if( Acad::eOk != es ) {
        return es;
    }

    // Check that we are at the correct subclass data
    //
    if( !filer->atSubclassData( kClassName )) {
        return Acad::eBadDxfSequence;
    }

    // First piece of data MUST be the version number
    if( Acad::eOk != ( es = filer->readItem( &rb ))) {
        return es;
    }

    if ( AcDb::kDxfReal != rb.restype ){
        ads_printf( "\nNo version information found in object definition." );
        return Acad::eMakeMeProxy;
    }

    // Check version first
    if ( rb.resval.rreal > 1.0 ){
        ads_printf( "\nNew version of AsdkSmiley object found (version %.1f): upgrade your Smiley.dbx to enable these objects.", rb.resval.rreal );
        return Acad::eMakeMeProxy;
    }

    // Set the normal's default value in case it's not in the
    // DXF information coming in
    //
    mnormal = AcGeVector3d( 0, 0, 1 ); // set default value:

    while( Acad::eOk == es ) {
        if( Acad::eOk == ( es = filer->readItem( &rb ))) {
            switch( rb.restype ) {
            case AcDb::kDxfXCoord:
                center.set( rb.resval.rpoint[X],
                            rb.resval.rpoint[Y],
                            rb.resval.rpoint[Z]);
                setCenter( center );
                break;
            case AcDb::kDxfReal+1:
                radius = rb.resval.rreal;
                setRadius( radius );
                break;
            case AcDb::kDxfNormalX:
                mnormal.set( rb.resval.rpoint[X],
                             rb.resval.rpoint[Y],
                             rb.resval.rpoint[Z]);
            case AcDb::kDxfReal+2:
                meyesapart = rb.resval.rreal;
                break;
            case AcDb::kDxfReal+3:
                meyesheight = rb.resval.rreal;
                break;
            case AcDb::kDxfReal+4:
                meyesize = rb.resval.rreal;
                break;
            case AcDb::kDxfXCoord+1:
                mouthleftpt.set( rb.resval.rpoint[X],
                                 rb.resval.rpoint[Y],
                                 rb.resval.rpoint[Z]);
                setMouthLeft( mouthleftpt );
                break;
            case AcDb::kDxfXCoord+2:
                mouthbottompt.set( rb.resval.rpoint[X],
                                   rb.resval.rpoint[Y],
                                   rb.resval.rpoint[Z]);
                setMouthBottom( mouthbottompt );
                break;
            case AcDb::kDxfXCoord+3:
                mouthrightpt.set( rb.resval.rpoint[X],
                                  rb.resval.rpoint[Y],
                                  rb.resval.rpoint[Z]);
                setMouthRight( mouthrightpt );
                break;
            }
        }
    }

    return filer->filerStatus();
}

Acad::ErrorStatus
AsdkSmiley::dxfOutFields(AcDbDxfFiler *filer) const
{
    assertReadEnabled();

    AcDbEntity::dxfOutFields( filer );

    filer->writeItem( AcDb::kDxfSubclass, kClassName );
    // Write version number
    filer->writeItem( AcDb::kDxfReal, kCurrentVersionNumber );
    filer->writeItem( AcDb::kDxfXCoord, center() );
    filer->writeItem( AcDb::kDxfReal+1, radius() );
    if( filer->includesDefaultValues()
        || mnormal != AcGeVector3d( 0, 0, 1 ))
    {
        filer->writeItem( AcDb::kDxfNormalX, mnormal );
    }
    filer->writeItem( AcDb::kDxfReal+2, meyesapart );
    filer->writeItem( AcDb::kDxfReal+3, meyesheight );
    filer->writeItem( AcDb::kDxfReal+4, meyesize );
    filer->writeItem( AcDb::kDxfXCoord+1, mouthLeft() );
    filer->writeItem( AcDb::kDxfXCoord+2, mouthBottom() );
    filer->writeItem( AcDb::kDxfXCoord+3, mouthRight() );

    return filer->filerStatus();
}

Acad::ErrorStatus
AsdkSmiley::explode(AcDbVoidPtrArray& entities) const
{
    assertReadEnabled();

    AcDbCircle *pCircle = new AcDbCircle( center(), mnormal, radius() );
    entities.append( pCircle );

    // Create eyes
    //
    AcGePoint3dArray eyearray;
    eyes( eyearray );
    for( int i = 0; i < eyearray.length(); i++ ){
        AcDbCircle *pCircle = new AcDbCircle( eyearray.at(i), mnormal, meyesize );
        entities.append( pCircle );
    }

    // Create smile arc
    //
    AcGePoint3d smilecen( mouthCenter() ),
                startpt( mouthLeft() ),
                endpt( mouthRight() );
    AcGeVector3d normvec( 1, 0, 0 ),
                 startvec = startpt - smilecen,
                 endvec = endpt - smilecen;
    double startang = 2 * kPi - startvec.angleTo( normvec ),
           endang = 2 * kPi - endvec.angleTo( normvec );
    AcDbArc *pArc = new AcDbArc( smilecen, mnormal, mouthRadius(), startang, endang );
    entities.append( pArc );

    // Create smile arc chord
    //
    AcDbLine *pLine = new AcDbLine( startpt, endpt );
    entities.append( pLine );

    return Acad::eOk;
}

void
AsdkSmiley::list() const
{
    assertReadEnabled();

    AcGePoint3d cen( center() );
    double rad = radius();

    AcDbEntity::list();
    acutPrintf(
        "%12scenter point, X=%9.16q0  Y=%9.16q0  Z=%9.16q0\n"
        "%11s radius %9.16q0\n"
        "%7s eye radius %9.16q0\n"
        "%7s eye height %9.16q0\n"
        "%7s eyes apart %9.16q0\n",
        "", cen[X], cen[Y], cen[Z], "",
        rad, "", meyesize, "",
        meyesheight, "", meyesapart
    );
}

Acad::ErrorStatus
AsdkSmiley::getOsnapPoints(
    AcDb::OsnapMode     osnapMode,
    int                 gsSelectionMark,
    const AcGePoint3d&  pickPoint,
    const AcGePoint3d&  lastPoint,
    const AcGeMatrix3d& viewXform,
    AcGePoint3dArray&   snapPoints,
    AcDbIntArray&       geomIds) const
{
    assertReadEnabled();

    switch( osnapMode ) {

    case AcDb::kOsModeNear:
        return osnapNear( pickPoint, snapPoints );
    case AcDb::kOsModeCen:
        return osnapCen( pickPoint, snapPoints );
    case AcDb::kOsModeQuad:
        return osnapQuad( pickPoint, snapPoints );
    case AcDb::kOsModeMid:
    case AcDb::kOsModeEnd:
    case AcDb::kOsModeNode:
    case AcDb::kOsModeIns:
    case AcDb::kOsModePerp:
    case AcDb::kOsModeTan:
    default:
        break;
    }

    return Acad::eInvalidInput;
}

Acad::ErrorStatus
AsdkSmiley::getGripPoints(
    AcGePoint3dArray& gripPoints,
    AcDbIntArray& osnapMasks,
    AcDbIntArray& geomIds) const
{
    assertReadEnabled();

    // Grip points to face
    //
    AcGePoint3d center( center() );
    gripPoints.append( center );
    AcGeVector3d xoff( radius(), 0, 0 ),
                 yoff( 0, radius(), 0 );
    gripPoints.append( center + xoff );
    gripPoints.append( center + yoff );
    gripPoints.append( center - xoff );
    gripPoints.append( center - yoff );

    // Grip points to mouth
    //
    AcGeLineSeg3d chord( mouthLeft(), mouthRight() );

    gripPoints.append( mouthLeft() );
    gripPoints.append( mouthRight() );
    gripPoints.append( chord.midPoint() );
    gripPoints.append( mouthBottom() );

    // Grip points to eyes
    //
    AcGePoint3dArray eyearray;
    AcGePoint3d eyecen;
    eyes( eyearray );
    for( int i = 0; i < eyearray.length(); i++ ){
        eyecen = eyearray.at( i );
        gripPoints.append( eyecen );
        AcGeVector3d xoff( meyesize, 0, 0 ),
                     yoff( 0, meyesize, 0 );
        gripPoints.append( eyecen + xoff );
        gripPoints.append( eyecen + yoff );
        gripPoints.append( eyecen - xoff );
        gripPoints.append( eyecen - yoff );
    }

    return Acad::eOk;
}

Acad::ErrorStatus
AsdkSmiley::moveGripPointsAt(
    const AcDbIntArray& indices,
    const AcGeVector3d& offset)
{
    assertWriteEnabled();

    AcGePoint3dArray eyearray;
    AcGePoint3d oldquad, newquad, newmouthcenter, newmouthbottom,
                smilecen, startpt, endpt, midpt, newpt;
    AcGeVector3d vecstart(0,0,0), vecend(0,0,0), newvec(0,0,0);

    eyes( eyearray );
    for( int i = 0; i < indices.length(); i++ ) {
        int idx = indices[i];
        switch( idx ) {

        // Stretch smiley center
        //
        case 0:
            setCenter( center() + offset );
            continue;

        // Stretch smiley radius
        //
        case 1:
            oldquad = center() + AcGeVector3d( radius(), 0, 0 );
            break;
        case 2:
            oldquad = center() + AcGeVector3d( 0, radius(), 0 );
            break;
        case 3:
            oldquad = center() - AcGeVector3d( radius(), 0, 0 );
            break;
        case 4:
            oldquad = center() - AcGeVector3d( 0, radius(), 0 );
            break;

        // Stretch smiley mouth
        //
        case 5:
            // Left hand edge of mouth
            //
            setMouthLeft( mouthLeft() + offset );
            ensureRadius();

            continue;

        case 6:
            // Right hand edge of mouth
            //
            setMouthRight( mouthRight() + offset );
            ensureRadius();

            continue;

        case 7:
            // Middle mouth chord
            //
            setMouth( mouthLeft() + offset, mouthBottom() + offset, mouthRight() + offset );
            ensureRadius();

            continue;

        case 8:
            // Bottom of mouth arc
            //
            setMouthBottom( mouthBottom() + offset );
            ensureRadius();

            continue;

        // Stretch smiley eyes
        //
        default:
            if(( eyearray.length() * 5 ) + 9 > idx ){
                
                // Get eye number, extracting it from the array
                //
                int eyepos = (int)(( idx - 9 ) / 5 );
                AcGePoint3d eyecen = eyearray.at( eyepos );
                
                // Handle the grip for the eye
                //
                int subidx = idx - 9;
                while ( subidx >= 5 ){ subidx -= 5; }
                switch( subidx ){

                // Stretch eye center
                //
                case 0:
                    // Keep the minimum eye height at zero
                    //
                    if( meyesheight+offset[Y] < 0 )
                        setEyesHeight( 0 );
                    else
                        setEyesHeight( meyesheight + offset[Y] );

                    // Keep the eyes from overlapping
                    //
                    if( eyecen[X] < center()[X] ){    // left eye
                        if( meyesapart - ( offset[X] * 2 ) < meyesize * 2 )
                            setEyesApart( meyesize * 2 );
                        else
                            setEyesApart( meyesapart - ( offset[X] * 2 ));
                    }
                    else {                          // right eye
                        if( meyesapart + ( offset[X] * 2 ) < meyesize * 2 )
                            setEyesApart( meyesize * 2 );
                        else
                            setEyesApart( meyesapart + ( offset[X] * 2));
                    }
                    ensureRadius();
                    continue;

                // Stretch eye radius
                //
                case 1:
                    oldquad = eyecen + AcGeVector3d( meyesize, 0, 0 );
                    break;
                case 2:
                    oldquad = eyecen + AcGeVector3d( 0, meyesize, 0 );
                    break;
                case 3:
                    oldquad = eyecen - AcGeVector3d( meyesize, 0, 0 );
                    break;
                case 4:
                    oldquad = eyecen - AcGeVector3d( 0, meyesize, 0 );
                    break;
                }
                newquad = oldquad + offset;
                
                // Keep eyes from touching
                //
                if( newquad.distanceTo( eyecen ) > meyesapart / 2 )
                    setEyeSize( meyesapart / 2 );
                else
                    setEyeSize( newquad.distanceTo( eyecen ));
                ensureRadius();
            }
            continue;
        }
        newquad = oldquad + offset;
        scaleRadius( newquad.distanceTo( center() ));
    }

    return Acad::eOk;
}

Acad::ErrorStatus
AsdkSmiley::getStretchPoints(AcGePoint3dArray& stretchPoints) const
{
    assertReadEnabled();

    //  getStretchPoints == getGripPoints
    //
    AcDbIntArray osnapModes;
    AcDbIntArray geomIds;
    return getGripPoints( stretchPoints, osnapModes, geomIds );
}

Acad::ErrorStatus
AsdkSmiley::moveStretchPointsAt(
    const AcDbIntArray& indices,
    const AcGeVector3d& offset)
{
    assertWriteEnabled();

    //  moveStretchPointsAt == moveGripPointsAt
    //
    return moveGripPointsAt( indices, offset );
}

Acad::ErrorStatus
AsdkSmiley::transformBy(const AcGeMatrix3d& xform)
{
    assertWriteEnabled();

    // Transform the center point and get the translation vector
    AcGePoint3d oldCenter( center() ),
                newCenter( center() );
    newCenter.transformBy( xform );
    AcGeVector3d transVec = newCenter - center();

    // Get the equivalent transformation
    AcGeMatrix3d newXform;
    newXform.setToTranslation( transVec );

    // Only translate the face and mouth - do not transform!
    mfacecircle.transformBy( newXform );
    mmoutharc.transformBy( newXform );

    // Get the point at a quadrant, transform it..
    AcGePoint3d oldXquad = center() + AcGeVector3d( radius(), 0, 0 ),
                newXquad( oldXquad );
    newXquad.transformBy( xform );

    // ... then scale the Smiley accordingly
    if ( Adesk::kFalse == xform.isEqualTo( AcGeMatrix3d::kIdentity ))
        scaleRadius( radius() * newCenter.distanceTo( newXquad ) / oldCenter.distanceTo( oldXquad ));

    return Acad::eOk;
}

void
AsdkSmiley::saveAs(AcGiWorldDraw *wd, AcDb::SaveType saveType)
{

    // saveType == AcDb::kR12Save for saveasr12
    // saveType == AcDb::kR13Save for proxy graphics save
    //
    AcGiRegenType rtype = wd->regenType();

    if( AcDb::kR12Save == saveType )
        wd->subEntityTraits().setFillType( kAcGiFillNever );
    else if( AcDb::kR13Save == saveType )
        wd->subEntityTraits().setFillType( kAcGiFillAlways );

    // Draw face
    //
    wd->geometry().circle( center(), radius(), mnormal );

    if( AcDb::kR13Save == saveType )
        wd->subEntityTraits().setColor( 250 );

    // Draw eyes
    //
    AcGePoint3dArray eyearray;
    eyes( eyearray );
    AcGeVector3d eyevec( -1, 0, 0 );
    double eyeang = kPi;
    for( int i = 0; i < eyearray.length(); i++ ){
        wd->geometry().circularArc( eyearray.at( i ), meyesize, mnormal, eyevec, eyeang );
    }

    // Draw frown
    //
    AcGePoint3d smilecen = center();
    smilecen[Y] -= radius() * 1.1;
    double smilerad = radius() * 0.8;
    AcGeVector3d smilevec( 1, 1, 0 );
    double smileang = kPi / 2;
    wd->geometry().circularArc( smilecen, smilerad, mnormal, smilevec, smileang, kAcGiArcChord );
}

Acad::ErrorStatus
AsdkSmiley::osnapNear(
    const AcGePoint3d& pickPoint,
    AcGePoint3dArray& snapPoints) const
{
    // For osnap near, define the same points as the grip points.
    // This definitely not the proper implementation,  but it is
    // adequate for this simple sample.
    //

    AcGeVector3d xoff( radius(), 0, 0 );
    AcGeVector3d yoff( 0, radius(), 0 );
    AcGePoint3d center( center() );
    snapPoints.append( center + xoff );
    snapPoints.append( center + yoff );
    snapPoints.append( center - xoff );
    snapPoints.append( center - yoff );

    return Acad::eOk;
}

Acad::ErrorStatus
AsdkSmiley::osnapCen(
    const AcGePoint3d& pickPoint,
    AcGePoint3dArray& snapPoints) const
{
    // Osnap center to the face's center
    //
    snapPoints.append( center() );

    // Osnap center to the eyes' center
    //
    AcGePoint3dArray eyearray;
    eyes( eyearray );
    for( int i = 0; i < eyearray.length(); i++ ){
        snapPoints.append( eyearray.at( i ));
    }

    return Acad::eOk;
}

Acad::ErrorStatus
AsdkSmiley::osnapQuad(
    const AcGePoint3d& pickPoint,
    AcGePoint3dArray& snapPoints) const
{
    AcGeVector3d xoff(0,0,0);
    AcGeVector3d yoff(0,0,0);

    // Osnap quad to the face's quad points
    //
    xoff.x = yoff.y = radius();
    AcGePoint3d center( center() );
    snapPoints.append( center + xoff );
    snapPoints.append( center + yoff );
    snapPoints.append( center - xoff );
    snapPoints.append( center - yoff );
    
    // Osnap quad to the eyes' quad points
    //
    AcGePoint3dArray eyearray;
    AcGePoint3d eyecen;
    eyes( eyearray );
    for( int i = 0; i < eyearray.length(); i++ ){
        eyecen = eyearray.at( i );
        xoff.x = meyesize;
        yoff.y = meyesize;
        snapPoints.append( eyecen + xoff );
        snapPoints.append( eyecen + yoff );
        snapPoints.append( eyecen - xoff );
        snapPoints.append( eyecen - yoff );
    }

    return Acad::eOk;
}

AcGePoint3d
AsdkSmiley::center() const
{
    assertReadEnabled();
    return mfacecircle.center();
}

void
AsdkSmiley::setCenter(const AcGePoint3d c) 
{
    assertWriteEnabled();
    mmoutharc.translateBy( c - center() );
    mfacecircle.setCenter( c );
    recordGraphicsModified();
} // smiley center

double
AsdkSmiley::radius() const
{
    assertReadEnabled();
    return mfacecircle.radius();
}

void
AsdkSmiley::setRadius(const double r)       
{
    assertWriteEnabled();
    mfacecircle.setRadius( r );
} // smiley radius

void
AsdkSmiley::scaleRadius(const double r)       
{
    assertWriteEnabled();
    AcGePoint3d center( center() );
    double rad = radius(),
           factor = r / rad;
    setEyesApart( factor * meyesapart );
    setEyesHeight( factor * meyesheight );
    setEyeSize( factor * meyesize );
    AcGePoint3d left( mouthLeft() ),
                bottom( mouthBottom() ),
                right( mouthRight() );
    setMouth( left.scaleBy( factor, center ), bottom.scaleBy( factor, center ), right.scaleBy( factor, center ) );
    setRadius( r );
    recordGraphicsModified();
} // smiley radius

AcGeVector3d
AsdkSmiley::normal() const
{
    assertReadEnabled();
    return mnormal;
}

void
AsdkSmiley::setNormal(const AcGeVector3d v)
{
    assertWriteEnabled();
    mnormal = v;
    recordGraphicsModified();
} // smiley normal

double
AsdkSmiley::eyesApart() const
{
    assertReadEnabled();
    return meyesapart;
}

void
AsdkSmiley::setEyesApart(const double d)       
{
    assertWriteEnabled();
    meyesapart = d;
    recordGraphicsModified();
} // smiley eyes apart

double
AsdkSmiley::eyesHeight() const
{
    assertReadEnabled();
    return meyesheight;
}

void
AsdkSmiley::setEyesHeight(const double h)       
{
    assertWriteEnabled();
    meyesheight = h;
    recordGraphicsModified();
} // smiley eyes height

double
AsdkSmiley::eyeSize() const
{
    assertReadEnabled();
    return meyesize;
}

void
AsdkSmiley::setEyeSize(const double s)       
{
    assertWriteEnabled();
    meyesize = s;
    recordGraphicsModified();
} // smiley eyes size

void
AsdkSmiley::eyes(AcGePoint3dArray& array) const
{
    assertReadEnabled();
    // left eye
    AcGePoint3d eye = center();
    eye[X] -= meyesapart / 2;
    eye[Y] += meyesheight;
    array.append(eye);
    // right eye
    eye[X] += meyesapart;
    array.append(eye);
} // smiley eyes

AcGePoint3d
AsdkSmiley::mouthCenter() const
{
    assertReadEnabled();
    return mmoutharc.center();
}

double
AsdkSmiley::mouthRadius() const
{
    assertReadEnabled();
    return mmoutharc.radius();
}

AcGePoint3d
AsdkSmiley::mouthLeft() const
{
    assertReadEnabled();
    return mmoutharc.startPoint();
}

void
AsdkSmiley::setMouthLeft(const AcGePoint3d& p)       
{
    assertWriteEnabled();
    mmoutharc.set( p, mouthBottom(), mouthRight() );
    recordGraphicsModified();
} // left point of mouth arc (smile)

AcGePoint3d
AsdkSmiley::mouthRight() const
{
    assertReadEnabled();
    return mmoutharc.endPoint();
}

void
AsdkSmiley::setMouthRight(const AcGePoint3d& p)       
{
    assertWriteEnabled();
    mmoutharc.set( mouthLeft(), mouthBottom(), p );
    recordGraphicsModified();
} // right point of mouth arc (smile)

AcGePoint3d
AsdkSmiley::mouthBottom() const
{
    assertReadEnabled();
    AcGeVector3d yoff( 0, radius(), 0 );
    AcGePoint3d center( center() );
    AcGePoint3d faceBottom( center - yoff );
    AcGePointOnCurve3d pntCurve;
    
    mmoutharc.getClosestPointTo( faceBottom, pntCurve );
    return pntCurve.point();
}

void
AsdkSmiley::setMouthBottom(const AcGePoint3d& p)       
{
    assertWriteEnabled();
    mmoutharc.set( mouthLeft(), p, mouthRight() );
    recordGraphicsModified();
} // bottom point of mouth arc (smile)

void
AsdkSmiley::setMouth( const AcGePoint3d& left, const AcGePoint3d& bottom, const AcGePoint3d& right )
{
    assertWriteEnabled();
    AcGePoint3d realLeft( left ), realBottom( bottom ), realRight( right );

    double topY = center()[Y] + eyesHeight() - eyeSize();
    double diff = 0.0;

    if (( left[Y] - topY ) > diff ){
        diff = left[Y] - topY;
    }
    if (( bottom[Y] - topY ) > diff ){
        diff = bottom[Y] - topY;
    }
    if (( right[Y] - topY ) > diff ){
        diff = right[Y] - topY;
    }
    
    AcGeVector3d vec( 0, diff, 0 );
    mmoutharc.set( realLeft - vec, realBottom - vec, realRight - vec );
    recordGraphicsModified();
}
