//
//
// (C) Copyright 1990-2003 by Autodesk, Inc. 
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
//----- AsdkRings.cpp : Implementation of AsdkRings
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "AsdkRings.h"

//-----------------------------------------------------------------------------
Adesk::UInt32 AsdkRings::kCurrentVersionNumber =1 ;

//-----------------------------------------------------------------------------
ACRX_DXF_DEFINE_MEMBERS (
	AsdkRings, AcDbEntity,
	AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent, 
	AcDbProxyEntity::kAllAllowedBits, ASDKRINGS,
	"ASDKSELECTIONFILTERDBAPP"
	"|Product Desc:     A description for your object"
	"|Company:          Your company name"
	"|WEB Address:      Your company WEB site address"
)

AsdkRings::AsdkRings(AcGePoint3d center, double radius)
{
	     setCenter(center);
		 setRadii(radius);
		 m_subselectstate = 0;

}
AsdkRings::AsdkRings (){}

//-----------------------------------------------------------------------------
//----- AcDbObject protocols
//- Dwg Filing protocol
Acad::ErrorStatus AsdkRings::dwgOutFields (AcDbDwgFiler *pFiler) const {
	
	assertReadEnabled () ;
	//----- Save parent class information first.
	Acad::ErrorStatus es =AcDbEntity::dwgOutFields (pFiler) ;
	if ( es != Acad::eOk )
		return (es) ;

	//----- Object version number needs to be saved first
	if ( (es =pFiler ->writeInt16 (AsdkRings::kCurrentVersionNumber)) != Acad::eOk )
		return (es) ;
	
     pFiler->writeItem( getCenter() );
    pFiler->writeItem( getRadius());

 	return (pFiler->filerStatus ()) ;
}

Acad::ErrorStatus AsdkRings::dwgInFields (AcDbDwgFiler *pFiler) {
	assertWriteEnabled () ;

	//----- Read parent class information first.
	Acad::ErrorStatus es =AcDbEntity::dwgInFields (pFiler) ;
	if ( es != Acad::eOk )
		return (es) ;

	//----- Object version number needs to be read first
	Adesk::Int16 version =0 ;
	if ( (es =pFiler->readInt16(&version)) != Acad::eOk )
		return (es) ;
	if ( version > AsdkRings::kCurrentVersionNumber ){
		acutPrintf( "\nNew version of AsdkRings object found (version %.1f found, version %.1f supported): upgrade your Smiley.dbx to enable these objects.", version, kCurrentVersionNumber );
	   return (Acad::eMakeMeProxy) ;
	}

    AcGePoint3d center;
    double radius;
    pFiler->readItem( &center );
    pFiler->readItem( &radius );
    setCenter( center );
    setRadii( radius );
	
	return (pFiler->filerStatus ()) ;
}

//-----------------------------------------------------------------------------
//----- AcDbEntity protocols
Adesk::Boolean AsdkRings::worldDraw (AcGiWorldDraw *mode) {
	assertReadEnabled () ;

    AcGeVector3d offset(0,0,0);
    AcGeCircArc3d circle1 = Circle_1;
	AcGeCircArc3d circle2 = Circle_2;
	AcGeCircArc3d circle3 = Circle_3;

    
	   Adesk::UInt16 color;
	   color = 1;  //Red color for circle 1
       mode->subEntityTraits().setColor(color);

    // Give the  circle 1 a GS marker of 1
    mode->subEntityTraits().setSelectionMarker( 1 );
    mode->geometry().circle( /*circle1.center()*/getCenter(), circle1.radius(), AcGeVector3d (0,0,1) );
	
	color = 3;  //Green color for circle 2
	mode->subEntityTraits().setColor(color);
	    // Give  circle 2 GS marker of 2
    mode->subEntityTraits().setSelectionMarker( 2 );
    mode->geometry().circle( /*circle2.center()*/getCenter(), circle2.radius(), AcGeVector3d (0,0,1) );

	color = 5;  //Blue color for circle 3
	mode->subEntityTraits().setColor(color);
	// Give  circle 3 GS marker of 3
	mode->subEntityTraits().setSelectionMarker( 3 );
	mode->geometry().circle( /*circle3.center()*/getCenter(), circle3.radius(), AcGeVector3d (0,0,1) );

	return (AcDbEntity::worldDraw (mode)) ;
}



Acad::ErrorStatus
AsdkRings::dxfInFields(AcDbDxfFiler *filer)
{
    assertWriteEnabled();

    struct resbuf rb;
    AcGePoint3d center;//
    double radius;

    Acad::ErrorStatus es = AcDbEntity::dxfInFields( filer );

    if( Acad::eOk != es ) {
        return es;
    }

    // Check that we are at the correct subclass data
    //
    if( !filer->atSubclassData( "AsdkRings" )) {
        return Acad::eBadDxfSequence;
    }

    // First piece of data MUST be the version number
    if( Acad::eOk != ( es = filer->readItem( &rb ))) {
        return es;
    }

    if ( AcDb::kDxfXInt16 != rb.restype ){
        acutPrintf( "\nNo version information found in object definition." );
        return filer ->filerStatus();
    }

    // Check version first
    if ( rb.resval.rint > 1 ){
        acutPrintf( "\nNew version of AsdkRings object found (version %ld): upgrade your dbx project to enable these objects.", rb.resval.rint );
        return Acad::eMakeMeProxy;
    }


    while( Acad::eOk == es ) {
        if( Acad::eOk == ( es = filer->readItem( &rb ))) {
            switch( rb.restype ) {
            case AcDb::kDxfXCoord:
                center.set( rb.resval.rpoint[X],
                            rb.resval.rpoint[Y],
                            rb.resval.rpoint[Z]);
                setCenter( center );
                break;
         
            case AcDb::kDxfReal:
                radius = rb.resval.rreal;
                setRadii( radius );
                break;
            }
        }
    }

    return filer->filerStatus();
}

Acad::ErrorStatus
AsdkRings::dxfOutFields(AcDbDxfFiler *filer) const
{
    assertReadEnabled();

    AcDbEntity::dxfOutFields( filer );
    filer->writeItem( AcDb::kDxfSubclass, "AsdkRings" );
   
	// Write version number
	filer->writeItem (AcDb::kDxfXInt16, kCurrentVersionNumber );
    filer->writeItem( AcDb::kDxfXCoord, getCenter() );
    filer->writeItem( AcDb::kDxfReal, getRadius() );
    return filer->filerStatus();
}

//- Grip points protocol
Acad::ErrorStatus AsdkRings::getGripPoints (
	AcGePoint3dArray &gripPoints, AcDbIntArray &osnapModes, AcDbIntArray &geomIds
) const 
{
	assertReadEnabled () ;
	AcGePoint3d center;
	AcGeVector3d xoff, yoff;
	double  radius_1,radius_2,radius_3;
    int subselstate = m_subselectstate;
	center.set(getCenter().x, getCenter().y,getCenter().z);
	gripPoints.append( center );

 	switch (subselstate)
	{

	case 0:  // all selected 
		radius_1 = getRadius();
		radius_2 = radius_1 * 1.5;
		radius_3 = radius_1 * 2.0;

		xoff.set( radius_1, 0, 0 );
		yoff.set( 0, radius_1, 0 );
		gripPoints.append( center + xoff );
		gripPoints.append( center + yoff );
		gripPoints.append( center - xoff );
		gripPoints.append( center - yoff );

		xoff.set( radius_2, 0, 0);
		yoff.set(0, radius_2, 0);
		gripPoints.append( center + xoff );
		gripPoints.append( center + yoff );
		gripPoints.append( center - xoff );
		gripPoints.append( center - yoff );

		xoff.set( radius_3, 0, 0);
		yoff.set(0, radius_3, 0);
		gripPoints.append( center + xoff );
		gripPoints.append( center + yoff );
		gripPoints.append( center - xoff );
		gripPoints.append( center - yoff );

	break;
	case 1:  // Selecting innermost circle only - selection point is within innermost circle only
		
	radius_1 = getRadius();

	 xoff.set( radius_1, 0, 0 );
     yoff.set( 0, radius_1, 0 );
    gripPoints.append( center + xoff );
    gripPoints.append( center + yoff );
    gripPoints.append( center - xoff );
    gripPoints.append( center - yoff );

   break;
   case 2:
	 // Selecting within second circle only
    center.set(getCenter().x, getCenter().y,getCenter().z);
	radius_1 = getRadius();
	radius_2 = radius_1 * 1.5;

	 xoff.set( radius_2, 0, 0 );
     yoff.set( 0, radius_2, 0 );
    gripPoints.append( center + xoff );
    gripPoints.append( center + yoff );
    gripPoints.append( center - xoff );
    gripPoints.append( center - yoff );
   break;
   case 3:

	 // Selecting within outermost circle only
	   center.set(getCenter().x, getCenter().y,getCenter().z);
	
	   radius_1 = getRadius();
	   radius_2 = radius_1*1.5;
	   radius_3 = radius_1 * 2.0;


	   xoff.set( radius_3, 0, 0 );
	   yoff.set( 0, radius_3, 0 );
	   gripPoints.append( center + xoff );
	   gripPoints.append( center + yoff );
	   gripPoints.append( center - xoff );
	   gripPoints.append( center - yoff );

	   break;

  
	}
	return Acad::eOk;
}

void AsdkRings::setSubSelState(const int subselstate){
	m_subselectstate = subselstate;
}

Acad::ErrorStatus AsdkRings::moveGripPointsAt (const AcDbIntArray &indices, const AcGeVector3d &offset) {
	assertWriteEnabled () ;
   AcGePoint3d oldgp, newgp;
   int subselstate = m_subselectstate;
	for (int i = 0; i<indices.length(); i++)
	{
		int index = indices[i];
	 double  radius_1,radius_2,radius_3;

	     radius_1 = getRadius();
         radius_2 = radius_1 * 1.5;
		 radius_3 = radius_1 * 2.0;

		 //mid_radius = 0.5 *( outer_radius + inner_radius);

		switch (index){
			case 0: // centre of circle
				setCenter(getCenter() + offset);
				continue;

            case 1:  //point on inner circle

					oldgp = getCenter() + AcGeVector3d( radius_1 , 0, 0 );  
					newgp = oldgp + offset;
				    radius_1 = newgp.distanceTo(getCenter());	
           break;
        case 2:
                   //point on  circle2
					 oldgp = getCenter() + AcGeVector3d( 0, radius_1,  0 ); 
					newgp = oldgp + offset;
				   radius_1 = newgp.distanceTo(getCenter());	
            break;
        case 3:

					oldgp = getCenter() - AcGeVector3d( radius_1, 0,   0 );  //point on inner circle
					newgp = oldgp + offset;
				    radius_1 = newgp.distanceTo(getCenter());	
            break;
        case 4:

				    oldgp = getCenter() - AcGeVector3d(  0, radius_1,  0 );  //point on inner circle
					newgp = oldgp + offset;
				    radius_1 = newgp.distanceTo(getCenter());	
            break;
        case 5:			
				oldgp = getCenter() + AcGeVector3d(  radius_1, 0, 0 );  //point on inner circle
				newgp = oldgp + offset;
				radius_1 = newgp.distanceTo(getCenter());	
	    break;
        case 6:			
				oldgp = getCenter() + AcGeVector3d( 0, radius_1,  0 );  //point on inner circle
				newgp = oldgp + offset;
				radius_1 = newgp.distanceTo(getCenter());	
	    break;
        case 7:			
				oldgp = getCenter() - AcGeVector3d( radius_1, 0, 0 );  //point on inner circle
				newgp = oldgp + offset;
				radius_1 = newgp.distanceTo(getCenter());	
	    break;
        case 8:			
				oldgp = getCenter() - AcGeVector3d(0,  radius_1, 0 );  //point on inner circle
				newgp = oldgp + offset;
				radius_1 = newgp.distanceTo(getCenter());	

				break;
		case 9:			
			oldgp = getCenter() + AcGeVector3d(radius_1,0, 0 );  //point on inner circle
			newgp = oldgp + offset;
			radius_1 = newgp.distanceTo(getCenter());	
			break;
		case 10:			
			oldgp = getCenter() + AcGeVector3d(0,  radius_1, 0 );  //point on inner circle
			newgp = oldgp + offset;
			radius_1 = newgp.distanceTo(getCenter());	
			break;
		case 11:			
			oldgp = getCenter() - AcGeVector3d(radius_1,0,  0 );  //point on inner circle
			newgp = oldgp + offset;
			radius_1 = newgp.distanceTo(getCenter());	
	    break;
        case 12:			
				oldgp = getCenter() - AcGeVector3d(0,  radius_1, 0 );  //point on inner circle
				newgp = oldgp + offset;
				radius_1 = newgp.distanceTo(getCenter());	

		} //end switch

		   setRadii(radius_1);
		 
	}
	//----- This method is never called unless you return eNotImplemented 
	//----- from the new moveGripPointsAt() method below (which is the default implementation)

	return Acad::eOk;
}

void AsdkRings::setCenter(AcGePoint3d center)
{
	   assertWriteEnabled();
	   m_center.set(center.x,center.y,center.z);
     recordGraphicsModified();
}

void AsdkRings::setRadii(const double radius)
{
	    assertWriteEnabled();
	   Circle_1.setRadius(radius );    
	   Circle_2.setRadius(radius * 1.5);   
	   Circle_3.setRadius(radius * 2.0);   
	   recordGraphicsModified();

}

void AsdkRings::setColor(AcCmEntityColor color)
{
}

    double AsdkRings::getRadius() const
	{
		 assertReadEnabled();
		 return Circle_1.radius();
	}

    AcGePoint3d AsdkRings::getCenter() const
	{
		 assertReadEnabled();
		 return m_center;//Circle_1.center();
	}

bool AsdkRings::hitTest(const AcGePoint3d&  wvpt,  	const AcGeVector3d& wvwdir)
{
	
  // Check if the point lies on or within the entire entity, i.e. 
  // on or within circle 3 (the outermost circle)

	AcGePlane pln;
	int marker =0;
	AcGeLine3d line;

	pln.set(getCenter(),AcGeVector3d(0,0,1));
	AcGePoint3d projPt = wvpt.project(pln,wvwdir);

	AcGeCircArc3d *pGeArc = new AcGeCircArc3d();
	pGeArc->setCenter(getCenter());
	pGeArc->setRadius(getRadius()* 2.0);  //radius of outermost circle fixed at 2.0 * the innermost circle radius
 
	if (pGeArc ->isInside(projPt) == Adesk::kTrue){
		delete pGeArc;
	  return true;
	}
	else{
	 delete pGeArc;
	 return false;
	}
}

void AsdkRings::setSubSelection(const AcGePoint3d&  wvpt, const AcGeVector3d& wvwdir, int &marker)
{

	AcGePlane pln;

	AcGeMatrix3d xform;
	AcDbFullSubentPath *subentIds;
	AcGeLine3d line;

	AcDb::SubentType type = kEdgeSubentType; //2
	int numPaths;

	pln.set(getCenter(),AcGeVector3d(0,0,1));

	AcGePoint3d projPt = wvpt.project(pln,wvwdir);

	AcGeCircArc3d *pGeArc = new AcGeCircArc3d();
	pGeArc->setCenter(getCenter());
	pGeArc->setRadius(getRadius());

// First check if the point lies within innermost circle
	if (pGeArc ->isInside(projPt) == Adesk::kTrue){
		    setSubSelState(1);   
			marker = 1;
		return ;
	}
		
		//Point lies outside circle1 (but inside circle 2 only)
	  pGeArc->setRadius(getRadius()*1.5);
	  if (pGeArc ->isInside(projPt) == Adesk::kTrue){

            	marker = 2;
			setSubSelState(2);  
			return ;
		}

	
	//Point lies outside circle2 (but inside circle 3)
	   pGeArc->setRadius(getRadius()*2.0);
	   if (pGeArc ->isInside(projPt) == Adesk::kTrue){
           	marker = 3;
		   setSubSelState(3);  
		   return ;
	   }

}


void AsdkRings::clearSubSelection(void)
{
	setSubSelState(0);//No subselection
}

Acad::ErrorStatus 
AsdkRings::getSubentPathsAtGsMarker(AcDb::SubentType     type, 
                                   int                  gsMark,
                             const AcGePoint3d&         pickPoint,
                             const AcGeMatrix3d&        viewXform,
                                   int&                 numPaths, 
                                   AcDbFullSubentPath*& subentPaths,
                                   int                  numInserts,
                                   AcDbObjectId*        entAndInsertStack) const
{
    assertReadEnabled();

    assert(numInserts == 0);
    assert(entAndInsertStack == NULL);



    numPaths    = 0;
    subentPaths = NULL;
    
    if (gsMark == 0)
        return Acad::eInvalidInput;
	if (type != AcDb::kEdgeSubentType)
		assert(Adesk::kFalse);
	
        if (gsMark < 1 || gsMark > 3)
        return Acad::eInvalidInput;

        
         numPaths       = 1;
         subentPaths    = new AcDbFullSubentPath[1];
         subentPaths[0] = AcDbFullSubentPath(objectId(), type, gsMark);

  
    return Acad::eOk;
}

Acad::ErrorStatus 
AsdkRings::getGsMarkersAtSubentPath(const AcDbFullSubentPath& path, 
								   AcDbIntArray&       gsMarkers) const
{
	Acad::ErrorStatus es;

	
	AcDbSubentId subEntId = path.subentId();

	if (subEntId.type() != AcDb::kEdgeSubentType)
	  return( Acad::eWrongSubentityType );
	
	gsMarkers.append(subEntId.index());

	return Acad::eOk;
}