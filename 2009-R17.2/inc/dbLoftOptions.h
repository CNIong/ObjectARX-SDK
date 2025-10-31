#pragma once
#ifndef DBLOFTOPTIONS_H
#define DBLOFTOPTIONS_H
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
// The AcDbSurface class is the interface class for representing
// ASM surfaces inside AutoCAD.  

#include "dbmain.h"
#include "dbsubeid.h"
#include "gepnt3d.h"
#include "gevec3d.h"
#include "dbbody.h"

#pragma pack(push, 8)


// Utility class for setting options used by createLoftedSurface().
class AcDbLoftOptions
{
public:
    AcDbLoftOptions ();
    AcDbLoftOptions ( const AcDbLoftOptions& src );
    ~AcDbLoftOptions ();

    // Assignment operator.
    AcDbLoftOptions& operator = ( const AcDbLoftOptions& src );

    enum NormalOption {
            kNoNormal,
            kFirstNormal,
            kLastNormal,
            kEndsNormal,
            kAllNormal,
            kUseDraftAngles
    };

    // Get/set start draft angle.
    double  draftStart () const;
    void  setDraftStart ( double ang );

    // Get/set end draft angle.
    double  draftEnd () const;
    void  setDraftEnd ( double ang );

    // Get/set start draft magnitude.
    double  draftStartMag () const;
    void  setDraftStartMag ( double val );

    // Get/set end draft magnitude.
    double  draftEndMag () const;
    void  setDraftEndMag ( double val );

    // Get/set arc-length parameterization.
    bool  arcLengthParam () const;
    void  setArcLengthParam ( bool val );

    // Get/set twist option.
    bool  noTwist () const;
    void  setNoTwist ( bool val );

    // Get/set align option.
    bool  alignDirection () const;
    void  setAlignDirection ( bool val );

    // Get/set simplify option.
    bool  simplify () const;
    void  setSimplify ( bool val );

    // Get/set closed option.
    bool  closed () const;
    void  setClosed ( bool val );

    // Get/set ruled option.
    bool  ruled () const;
    void  setRuled ( bool val );

    // Get/set virtual guide option.
    bool  virtualGuide () const;
    void  setVirtualGuide ( bool val );

    // Get/set plane normal option.
    AcDbLoftOptions::NormalOption  normal () const;
    void  setNormal ( AcDbLoftOptions::NormalOption val );

    // Set loft options from current values of system variables.
    Acad::ErrorStatus  setOptionsFromSysvars ();

    // Set system variables from loft options.
    Acad::ErrorStatus  setSysvarsFromOptions ();

    // Check for valid combinations of options.
    Acad::ErrorStatus  checkOptions ( bool displayErrorMessages = false  );

    // Utility functions.
    Acad::ErrorStatus checkLoftCurves (
        AcArray<AcDbEntity*>& crossSectionCurves,
        AcArray<AcDbEntity*>& guideCurves,
        AcDbEntity* pPathCurve,
        bool& allOpen, bool& allClosed, bool& allPlanar,
        bool displayErrorMessages = false );
    Acad::ErrorStatus checkCrossSectionCurves (
        AcArray<AcDbEntity*>& crossSectionCurves,
        bool& allOpen, bool& allClosed, bool& allPlanar,
        bool displayErrorMessages = false );
    Acad::ErrorStatus checkGuideCurves ( AcArray<AcDbEntity*>& guideCurves,
                                         bool displayErrorMessages = false );
    Acad::ErrorStatus checkPathCurve ( AcDbEntity *pPathCurve,
                                       bool displayErrorMessages = false );

private:
    void *mpImpLoftOptions;
    friend class AcDbImpLoftOptions;
};

#pragma pack(pop)

#endif // DBLOFTOPTIONS_H
