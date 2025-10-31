#pragma once
#ifndef DBREVOLVEOPTIONS_H
#define DBREVOLVEOPTIONS_H
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
// DESCRIPTION:
//
// The AcDbRevolveOptions class is used for setting options that are
// passed to createRevolvedSurface() and revolveFace().  

#include "dbmain.h"
#include "gepnt3d.h"
#include "gevec3d.h"
#include "dbbody.h"

#pragma pack(push, 8)


// Utility class for setting options used by createRevolvedSurface().
class AcDbRevolveOptions
{
public:
    AcDbRevolveOptions ();
    AcDbRevolveOptions ( const AcDbRevolveOptions& src );
    ~AcDbRevolveOptions ();

    // Assignment operator.
    AcDbRevolveOptions& operator = ( const AcDbRevolveOptions& src );

    // Get/set draft angle.
    double  draftAngle () const;
    void  setDraftAngle ( double ang );

    // Get/set twist angle.
    double  twistAngle () const;
    void  setTwistAngle ( double ang );

    // Get/set close to axis option.
    bool  closeToAxis () const;
    void  setCloseToAxis ( bool val );

    // Utility functions.
    Acad::ErrorStatus  checkRevolveCurve ( AcDbEntity* pRevEnt,
        const AcGePoint3d& axisPnt, const AcGeVector3d& axisDir,
        bool& closed, bool& endPointsOnAxis, bool& planar,
        bool displayErrorMessages = false );

private:
    void *mpImpRevolveOptions;
    friend class AcDbImpRevolveOptions;
};
#pragma pack(pop)

#endif // DBREVOLVEOPTIONS_H
