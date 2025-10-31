#ifndef _ASDK_POLYJIG_H
#define _ASDK_POLYJIG_H
//
// (C) Copyright 1996-2006 by Autodesk, Inc. 
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
// POLYJIG.H
//
// DESCRIPTION: 
//
// AsdkPolyJig class, derived from AcEdJig class,
// provides dragging capablity for a custom entity
// AsdkPoly


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
