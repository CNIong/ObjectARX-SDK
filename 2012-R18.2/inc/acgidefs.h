#ifndef _ACGI_DEFS_H
#define _ACGI_DEFS_H 1
//
// (C) Copyright 1994-2010 by Autodesk, Inc. 
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
// This is the Graphics Interface for view independent and dependent
// elaboration of AcDb Entities.
//
// The AutoCAD Graphics Interface (AcGi) is a set of objects comprising 
// an API for elaborating the graphics representation of new AutoCAD
// entitites.  These objects support many geometric primitives, 
// transformation matrix querying, and graphical attributes. 

#include "adesk.h"


// These are the current kinds of viewport regeneration modes.
// This mode is not settable by the user, but it can be queried 
// in case you need to take different actions for different
// regeneration modes.
//
typedef enum {
    eAcGiRegenTypeInvalid = 0,
    kAcGiStandardDisplay = 2,
    kAcGiHideOrShadeCommand,
    kAcGiRenderCommand, // deprecated
    kAcGiShadedDisplay = kAcGiRenderCommand,
    kAcGiForExplode,
    kAcGiSaveWorldDrawForProxy
} AcGiRegenType;

// No longer supported and will be removed
//
#define kAcGiSaveWorldDrawForR12 kAcGiForExplode 

// These are the current face filling modes
//
typedef enum {
     kAcGiFillAlways = 1,
     kAcGiFillNever
} AcGiFillType;

// These are the edge visibility types
//
typedef enum {
    kAcGiInvisible = 0,
    kAcGiVisible,
    kAcGiSilhouette
} AcGiVisibility;

// These are the types of arcs
//
typedef enum {
    kAcGiArcSimple = 0,                 // just the arc (not fillable)
    kAcGiArcSector,                     // area bounded by the arc and its center of curvature
    kAcGiArcChord                       // area bounded by the arc and its end points
} AcGiArcType;

// These are the possible types of vertex orientation 
// 
typedef enum {
    kAcGiCounterClockwise = -1,
    kAcGiNoOrientation = 0,
    kAcGiClockwise = 1
} AcGiOrientationType;

// This signifies how to calculate maximum deviation for tesselation
//
typedef enum {
    kAcGiMaxDevForCircle = 0,
    kAcGiMaxDevForCurve,
    kAcGiMaxDevForBoundary,
    kAcGiMaxDevForIsoline,
    kAcGiMaxDevForFacet
} AcGiDeviationType;

// Raster image organization
//
typedef enum {
    kAcGiBitonal,
    kAcGiPalette,
    kAcGiGray,
    kAcGiRGBA,
    kAcGiBGRA,
    kAcGiARGB,
    kAcGiABGR,
    kAcGiBGR,
    kAcGiRGB                              
} AcGiImageOrg;

// Raster image orientation
//
typedef enum {
    kAcGiXLeftToRightTopFirst,
    kAcGiXLeftToRightBottomFirst,
    kAcGiXRightToLeftTopFirst,
    kAcGiXRightToLeftBottomFirst,
    kAcGiYTopToBottomLeftFirst,
    kAcGiYTopToBottomRightFirst,
    kAcGiYBottomToTopLeftFirst,
    kAcGiYBottomToTopRightFirst
} AcGiImageOrient;

// scale filter method to use
typedef enum {
    kDefaultScaleFilter,
    kNearestScaleFilter,
    kBellScaleFilter,
    kMitchellScaleFilter,
    kTriangleScaleFilter,
    kCubicScaleFilter,
    kBsplineScaleFilter,
    kLanczos3ScaleFilter
} AcGiScaleFilterType;

// rotation filter method to use
typedef enum {
    kDefaultRotationFilter,
    kInterpolatedRotationFilter,
    kNearestRotationFilter,
} AcGiRotationFilterType;

// how to interpret nRasterRatio
typedef enum {
    kDefaultScale,                  // classic scaling scheme
    kRelativeScale,                 // relative to original image, do rotation
    kUnTransformedScale             // original pixels, unscaled, unrotated
} AcGiScaleType;

// highlight style
enum AcGiHighlightStyle { 
    kAcGiHighlightNone,
    kAcGiHighlightCustom,
    kAcGiHighlightDashedAndThicken,
    kAcGiHighlightDim,
    kAcGiHighlightThickDim
};

enum AcGiEdgeStyleMaskValues {
    kAcGiNoEdgeStyleMask = 0,
    kAcGiJitterMask      = 1,
    kAcGiOverhangMask    = 2,
    kAcGiEdgeColorMask   = 4
};
typedef unsigned int AcGiEdgeStyleMask;



#endif
