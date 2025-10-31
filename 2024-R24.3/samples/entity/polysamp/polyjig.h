//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
// POLYJIG.H
//
// DESCRIPTION: 
//
// AsdkPolyJig class, derived from AcEdJig class,
// provides dragging capablity for a custom entity
// AsdkPoly

#ifndef _ASDK_POLYJIG_H
#define _ASDK_POLYJIG_H

#include "dbjig.h"
#include "dbmain.h"
#include "tchar.h"

class AcGePoint3d;
class AsdkPoly;


class AsdkPolyJig : public  AcEdJig
{
 public:
    AsdkPolyJig();
    virtual ~AsdkPolyJig();

    void               initializePoly(AcGePoint2d  cen,
                                      AcGeVector3d norm,
                                      int          numSides,
                                      double elev);

    void               acquire(AcGePoint2d  cen,
                               AcGeVector3d norm,
                               TCHAR*       name,
                               AcDbObjectId tsId,
                               double elev);

    Adesk::Boolean     dragAcquire(TCHAR* promptString,
                                   TCHAR* name,
                                   AcDbObjectId tsId);

    // overridden methods from AcEdJig class
    //
    AcDbEntity*        entity() const;
    DragStatus	       sampler();
    Adesk::Boolean     update();


 private:
    AsdkPoly*	       mPoly;
};

#endif
