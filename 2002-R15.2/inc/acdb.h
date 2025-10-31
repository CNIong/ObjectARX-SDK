#ifndef AD_ACDB_H
#define AD_ACDB_H 1
// 
// (C) Copyright 1993-2001 by Autodesk, Inc. 
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
// acdb.h:   Definitions for AutoCAD Database Library which are
//           shared between Internal and 3rd party Developers

#include "adesk.h"
#include "rxobject.h"
#include "gepnt3d.h"

#ifdef ACAD_OBJID_INLINE_INTERNAL
#    include "dbidinln.h"
#else
#    include "dbidapps.h"
#endif

#include "dbboiler.h"

// String Constants
//
#define ACDB_SERVICES                  /*MSG0*/"AcDbServices"
#define ACDB_MODEL_SPACE               /*MSG0*/"*Model_Space"
#define ACDB_PAPER_SPACE               /*MSG0*/"*Paper_Space"
#define ACDB_NULL_HANDLE               /*MSG0*/"\0\0\0\0\0\0\0"
#define ACDB_BROKEN_HANDLE             /*MSG0*/"FFFFFFFF"
#define ACDB_OPEN_BRACE_STR            /*MSG0*/"{"
#define ACDB_OPEN_BRACE_CHAR           /*MSG0*/'{'
#define ACDB_CLOSE_BRACE_STR           /*MSG0*/"}"
#define ACDB_CLOSE_BRACE_CHAR          /*MSG0*/'}'
#define ACDB_GROUP_DICTIONARY          /*MSG0*/"ACAD_GROUP"
#define ACDB_MLINESTYLE_DICTIONARY     /*MSG0*/"ACAD_MLINESTYLE"
#define ACDB_LAYOUT_DICTIONARY         /*MSG0*/"ACAD_LAYOUT"
#define ACDB_PLOTSETTINGS_DICTIONARY   /*MSG0*/"ACAD_PLOTSETTINGS"
#define ACDB_PLOTSTYLENAME_DICTIONARY  /*MSG0*/"ACAD_PLOTSTYLENAME"
#define ACDB_EMBEDDED_OBJECT_STR       /*MSG0*/"Embedded Object"
#define ACDB_LAYERSTATES_DICTIONARY    /*MSG0*/"ACAD_LAYERSTATES"

// struct Acad has been moved to the new header file acadstrc.h
//
#include "acadstrc.h"

#pragma pack(push, 8)

struct AcDb
{
    enum OpenMode          { kForRead           = 0,
                             kForWrite          = 1,
                             kForNotify         = 2 };

    enum FileVersion       { kR12               = 0,
                             kR13               = 1,
                             kR13Custom         = 2,
                             kMaxVersion        = 500 }; 

    enum CoordAxis         { kX                 = 0,
                             kY                 = 1,
                             kZ                 = 2 };

    enum CoordSystem       { kWorldCS           = 0,
                             kUserCS            = 1,
                             kCurDisplayCS      = 2,
                             kPaperDisplayCS    = 3,
                             kEntityCS          = 4 };

    enum Intersect         { kOnBothOperands    = 0,
                             kExtendThis        = 1,
                             kExtendArg         = 2,
                             kExtendBoth        = 3 };

    enum Visibility        { kInvisible         = 1,
                             kVisible           = 0 };

    typedef Adesk::Int16 DxfCode;
    enum                   { kDxfInvalid        = -9999,
                             kDxfXDictionary     = -6,
                             kDxfPReactors       = -5,
                             kDxfUndo            = -4,
                             kDxfXDataStart      = -3,
                             kDxfHeaderId        = -2,
                             kDxfFirstEntId      = -2,
                             kDxfEnd             = -1,
                             kDxfStart           = 0,
                             kDxfText            = 1,
                             kDxfXRefPath        = 1,
                             kDxfShapeName       = 2,
                             kDxfBlockName       = 2,
                             kDxfAttributeTag    = 2,
                             kDxfSymbolTableName = 2,
                             kDxfMstyleName      = 2,
                             kDxfSymTableRecName = 2,
                             kDxfAttributePrompt = 3,
                             kDxfDimStyleName    = 3,
                             kDxfLinetypeProse   = 3,
                             kDxfTextFontFile    = 3,
                             kDxfDescription     = 3,
                             kDxfDimPostStr      = 3,
                             kDxfTextBigFontFile = 4,
                             kDxfDimAPostStr     = 4,
                             kDxfCLShapeName     = 4,
                             kDxfSymTableRecComments = 4,
                             kDxfHandle          = 5,
                             kDxfDimBlk          = 5,
                             kDxfDimBlk1         = 6,
                             kDxfLinetypeName    = 6,
                             kDxfDimBlk2         = 7,
                             kDxfTextStyleName   = 7,
                             kDxfLayerName       = 8,
                             kDxfCLShapeText     = 9,

                             kDxfXCoord         = 10,
    
                             kDxfYCoord         = 20,
    
                             kDxfZCoord         = 30,

                             kDxfElevation      = 38,
                             kDxfThickness      = 39,

                             kDxfReal           = 40,
                             kDxfViewportHeight = 40,
                             kDxfTxtSize        = 40,
                             kDxfTxtStyleXScale = 41,
                             kDxfViewWidth      = 41,
                             kDxfViewportAspect = 41,
                             kDxfTxtStylePSize  = 42,
                             kDxfViewLensLength = 42,
                             kDxfViewFrontClip  = 43,
                             kDxfViewBackClip   = 44,
                             kDxfShapeXOffset   = 44,
                             kDxfShapeYOffset   = 45,
                             kDxfViewHeight     = 45,
                             kDxfShapeScale     = 46,
                             kDxfPixelScale     = 47,

                             kDxfLinetypeScale  = 48,

                             kDxfDashLength     = 49,
                             kDxfMlineOffset    = 49,
                             kDxfLinetypeElement = 49,

                             kDxfAngle          = 50,
                             kDxfViewportSnapAngle = 50,
                             kDxfViewportTwist  = 51,

                             kDxfVisibility     = 60,
                             kDxfLayerLinetype  = 61,
                             kDxfColor          = 62,
                             // Removed codes intended
                             // only for internal
                             // use:  63-65
                             kDxfHasSubentities = 66,
                             kDxfViewportVisibility = 67,
                             kDxfViewportActive = 68,
                             kDxfViewportNumber = 69,

                             kDxfInt16          = 70,
                             kDxfViewMode       = 71,
                             kDxfCircleSides    = 72,
                             kDxfViewportZoom   = 73,
                             kDxfViewportIcon   = 74,
                             kDxfViewportSnap   = 75,
                             kDxfViewportGrid   = 76,
                             kDxfViewportSnapStyle= 77,
                             kDxfViewportSnapPair= 78,

                             kDxfRegAppFlags    = 71,

                             kDxfTxtStyleFlags  = 71,
                             kDxfLinetypeAlign  = 72,
                             kDxfLinetypePDC    = 73,

                             kDxfInt32          = 90,

                             // Subclass Section Marker
                             //
                             // to be followed by subclass name.
                             //
                             kDxfSubclass            = 100,
                             kDxfEmbeddedObjectStart = 101,
                             kDxfControlString       = 102,

                             // DimVarTableRecords have been using 5 for a
                             // string value.  With R13, they get a handle
                             // value as well.  Since 5 is already in use,
                             // we use 105 for this special case.
                             //
                             kDxfDimVarHandle = 105,

                             kDxfUCSOrg         = 110,
                             kDxfUCSOriX        = 111,
                             kDxfUCSOriY        = 112,

                             kDxfXReal          = 140,

                             kDxfXInt16         = 170,

                             kDxfNormalX        = 210,
                             kDxfNormalY        = 220,
                             kDxfNormalZ        = 230,

                             kDxfXXInt16        = 270,

                             kDxfInt8           = 280,
                             kDxfRenderMode     = 281,

                             kDxfBool           = 290,

                             //  More string values 300-309
                             kDxfXTextString    = 300,

                             //  Arbitrary Binary Chunks 310-319
                             kDxfBinaryChunk   = 310,
                 
                             //  Arbitrary Object Handles 320-329
                             kDxfArbHandle  = 320,

                             kDxfSoftPointerId   = 330,  // 330-339
                             kDxfHardPointerId   = 340,  // 340-349
                             kDxfSoftOwnershipId = 350,  // 350-359
                             kDxfHardOwnershipId = 360,  // 360-369

                             // New base entity properties
                             // Lineweight is either an integer
                             // or "BYLAYER" or "BYBLOCK"
                             kDxfLineWeight        = 370,
                             kDxfPlotStyleNameType = 380,
                             kDxfPlotStyleNameId   = 390,
                             kDxfXXXInt16          = 400,

                             kDxfLayoutName     = 410,

                             kDxfComment        = 999,

                             kDxfXdAsciiString  = 1000,
                             kDxfRegAppName     = 1001,
                             kDxfXdControlString = 1002,
                             kDxfXdLayerName    = 1003,
                             kDxfXdBinaryChunk  = 1004,
                             kDxfXdHandle       = 1005,

                             kDxfXdXCoord       = 1010,
                             kDxfXdYCoord       = 1020,
                             kDxfXdZCoord       = 1030,

                             kDxfXdWorldXCoord  = 1011,
                             kDxfXdWorldYCoord  = 1021,
                             kDxfXdWorldZCoord  = 1031,

                             kDxfXdWorldXDisp   = 1012,
                             kDxfXdWorldYDisp   = 1022,
                             kDxfXdWorldZDisp   = 1032,

                             kDxfXdWorldXDir    = 1013,
                             kDxfXdWorldYDir    = 1023,
                             kDxfXdWorldZDir    = 1033,

                             kDxfXdReal         = 1040,
                             kDxfXdDist         = 1041,
                             kDxfXdScale        = 1042,

                             kDxfXdInteger16    = 1070,
                             kDxfXdInteger32    = 1071 };

    // Primitives.
    //
    enum DwgDataType       { kDwgNull            = 0,
                             kDwgReal            = 1,
                             kDwgInt32           = 2,
                             kDwgInt16           = 3,
                             kDwgInt8            = 4,
                             kDwgText            = 5,
                             kDwgBChunk          = 6,
                             kDwgHandle          = 7,
                             kDwgHardOwnershipId = 8,
                             kDwgSoftOwnershipId = 9,
                             kDwgHardPointerId   = 10,
                             kDwgSoftPointerId   = 11,
                             kDwg3Real           = 12,
                             kDwgNotRecognized   = 19 };

    // OsnapMask:  Specifies Osnap Operation.
    //
    enum OsnapMask         { kOsMaskEnd          = 1,
                             kOsMaskMid          = 2,
                             kOsMaskCen          = 4,
                             kOsMaskNode         = 8,
                             kOsMaskQuad         = 0x10,
                             kOsMaskInt          = 0x20,
                             kOsMaskIns          = 0x40,
                             kOsMaskPerp         = 0x80,
                             kOsMaskTan          = 0x100,
                             kOsMaskNear         = 0x200,
                             kOsMaskQuick        = 0x400,
                             kOsMaskApint        = 0x800,
                             kOsMaskImmediate    = 0x10000,
                             kOsMaskAllowTan     = 0x20000,
                             kOsMaskDisablePerp  = 0x40000,
                             kOsMaskRelCartesian = 0x80000,
                             kOsMaskRelPolar     = 0x100000,
                             kOsMaskNoneOverride = 0x200000 };

    // OsnapMode:  Specifies Object query.
    //             Binary and Virtual Operations not represented.
    //
    enum OsnapMode         { kOsModeEnd          = 1,
                             kOsModeMid          = 2,
                             kOsModeCen          = 3,
                             kOsModeNode         = 4,
                             kOsModeQuad         = 5, 
                             kOsModeIns          = 7,
                             kOsModePerp         = 8,
                             kOsModeTan          = 9,
                             kOsModeNear         = 10 };

    enum ShowImagesMode    { kNeverShow     = 0,
                                                 kAlwaysShow      = 1,
                             kBoundingBoxShow = 2 };

    enum SaveImagesMode    { kNeverSave     = 0,
                                                 kAlwaysSave      = 1 };

    enum TextHorzMode      { kTextLeft    = 0,   // TH_LEFT,
                             kTextCenter  = 1,   // TH_CENT,
                             kTextRight   = 2,   // TH_RIGHT,
                             kTextAlign   = 3,   // THV_ALIGN,
                             kTextMid     = 4,   // THV_MID,
                             kTextFit     = 5 }; // THV_FIT
 
    enum TextVertMode      { kTextBase    = 0,   // TV_BASE,
                             kTextBottom  = 1,   // TV_BOT,
                             kTextVertMid = 2,   // TV_MID,
                             kTextTop     = 3 }; // TV_TOP

    enum LineSpacingStyle  { kAtLeast = 1,
                             kExactly = 2 };

    enum Planarity         { kNonPlanar = 0,
                             kPlanar    = 1,
                             kLinear    = 2 };

    enum PointIndex        { kMPoint1    = 0,
                             kMPoint2    = 1,
                             kMPoint3    = 2,
                             kMPoint4    = 3 };

    enum EdgeIndex         { kMEdge1    = 0,
                             kMEdge2    = 1,
                             kMEdge3    = 2,
                             kMEdge4    = 3 };

    enum Poly2dType        { k2dSimplePoly      = 0,
                             k2dFitCurvePoly    = 1,
                             k2dQuadSplinePoly  = 2,
                             k2dCubicSplinePoly = 3 };

    enum Poly3dType        { k3dSimplePoly      = 0,
                             k3dQuadSplinePoly  = 1,
                             k3dCubicSplinePoly = 2 };

    enum PolyMeshType      { kSimpleMesh        = 0,
                             kQuadSurfaceMesh   = 5,
                             kCubicSurfaceMesh  = 6,
                             kBezierSurfaceMesh = 8 };

    enum Vertex2dType      { k2dVertex          = 0,
                             k2dSplineCtlVertex = 1,
                             k2dSplineFitVertex = 2,
                             k2dCurveFitVertex =  3 };

    enum Vertex3dType      { k3dSimpleVertex    = 0,
                             k3dControlVertex   = 1,
                             k3dFitVertex       = 2 };

    enum SpaceValueType    { kUndefined,
                             kStubPtr,
                             kEndOfFile,
                             kBackwardBranch,
                             kForwardBranch,
                             kDetour };

    enum BoolOperType      { kBoolUnite      = 0, 
                             kBoolIntersect  = 1, 
                             kBoolSubtract   = 2 };

    typedef Adesk::UInt32    SubentType;
    enum                   { kNullSubentType   = 0,
                             kFaceSubentType   = 1,
                             kEdgeSubentType   = 2,
                             kVertexSubentType = 3, 

////////////////////////////////////////////////////////////
                                                          //
                   // Mline specific type                 //
                                                          //
                             kMlineSubentCache = 4        //  Beauty is in the eye
                                                          //   of the beholder.
                                                          //
////////////////////////////////////////////////////////////
    
};

    typedef Adesk::UInt32    GeomId;
    enum                   { kNoGeom = 0 };

    enum GeomType          { kInvalidGeom = 0,
                             kPointGeom,
                             kLineGeom,
                             kCircleGeom,
                             kPlaneGeom };

    enum FilerType         { kFileFiler     = 0,
                             kCopyFiler     = 1,
                             kUndoFiler     = 2,
                             kBagFiler      = 3,
                             kIdXlateFiler      = 4,
                             kPageFiler         = 5,
                             kDeepCloneFiler    = 6,
                             kIdFiler           = 7,
                             kPurgeFiler        = 8,
                             kWblockCloneFiler  = 9 };

    enum FilerSeekType     { kSeekFromStart   = 0,
                             kSeekFromCurrent = 1,
                             kSeekFromEnd     = 2 };

    enum AcDbDwgVersion    { kDHL_MC0_0   = 0,
                             kDHL_AC1_2   = 1,
                             kDHL_AC1_40  = 2,
                             kDHL_AC1_50  = 3,
                             kDHL_AC2_20  = 4,
                             kDHL_AC2_10  = 5,
                             kDHL_AC2_21  = 6,
                             kDHL_AC2_22  = 7,
                             kDHL_1001    = 8,
                             kDHL_1002    = 9,      // AutoCAD 2.5
                             kDHL_1003    = 10,     // AutoCAD 2.6
                             kDHL_1004    = 11,     // Release 9
                             kDHL_1005    = 12,
                             kDHL_1006    = 13,     // Release 10
                             kDHL_1007    = 14,
                             kDHL_1008    = 15,
                             kDHL_1009    = 16,     // R11 and R12
                             kDHL_1010    = 17,
                             kDHL_1011    = 18,
                             kDHL_1012    = 19,     // R13
                             kDHL_1013    = 20,     // R14 mid version.
                             kDHL_1014    = 21,     // R14 final version.
                             kDHL_1500    = 22,     // R15 development (Tahoe)
                             kDHL_1015    = 23,     // R15 final version.
                             kDHL_CURRENT = kDHL_1015,
                             kDHL_Unknown = 32766,
                             kDHL_Max     = 32767 };

    // kDHL_1012, kMRelease0 = R13c0-3
    // kDHL_1012, kMRelease1 = R13c0-3
    // kDHL_1012, kMRelease4 = R13c4
    // kDHL_1012, kMRelease5 = R13c4_m
    // kDHL_1012, kMRelease6 = R13c4a

    // kDHL_1013, kMRelease0 = Sedona s000..s045
    // kDHL_1013, kMRelease1 = Sedona s046..s050
    // kDHL_1013, kMRelease2 = Sedona s051..s052
    // kDHL_1013, kMRelease3 = Sedona s053..s054
    // kDHL_1013, kMRelease4 = Sedona s055..s059
    // kDHL_1013, kMRelease5 = Sedona s060..s063
    // kDHL_1013, kMRelease6 = Sedona s064..
    // kDHL_1014, kMRelease0 = R14.0

    // kDHL_1500, kMRelease0  = Tahoe t010..t016
    // kDHL_1500, kMRelease1  = Tahoe t017
    // kDHL_1500, kMRelease2  = Tahoe t018, t019
    // kDHL_1500, kMRelease3  = Tahoe t020
    // kDHL_1500, kMRelease4  = Tahoe t021..t023
    // kDHL_1500, kMRelease5  = Tahoe t024
    // kDHL_1500, kMRelease6  = Tahoe t025..t027
    // kDHL_1500, kMRelease7  = Tahoe t028
    // kDHL_1500, kMRelease8  = Tahoe t029
    // kDHL_1500, kMRelease9  = Tahoe t030
    // kDHL_1500, kMRelease10 = Tahoe t031..t033
    // kDHL_1500, kMRelease11 = Tahoe t034
    // kDHL_1500, kMRelease12 = Tahoe t035..t036
    // kDHL_1500, kMRelease13 = Tahoe t037..t038
    // kDHL_1500, kMRelease14 = Tahoe t039
    // kDHL_1500, kMRelease15 = Tahoe t040..t041
    // kDHL_1500, kMRelease17 = Tahoe t042
    // kDHL_1500, kMRelease20 = Tahoe t047
    // kDHL_1500, kMRelease21 = Tahoe t048
    // kDHL_1500, kMRelease22 = Tahoe t049..t050
    // kDHL_1500, kMRelease23 = Tahoe t051
    // kDHL_1500, kMRelease24 = Tahoe t052..t053
    // kDHL_1500, kMRelease25 = Tahoe t054
    // kDHL_1500, kMRelease26 = Tahoe t055
    // kDHL_1500, kMRelease27 = Tahoe t056
    // kDHL_1500, kMRelease28 = not used
    // kDHL_1500, kMRelease29 = Tahoe t057
    // kDHL_1500, kMRelease30 = Tahoe t058
    // kDHL_1500, kMRelease31 = Tahoe t059
    // kDHL_1500, kMRelease32 = Tahoe t060
    // kDHL_1500, kMRelease33 = Tahoe t061
    // kDHL_1500, kMRelease34 = Tahoe t062..t063
    // kDHL_1500, kMRelease35 = Tahoe t064
    // kDHL_1500, kMRelease36 = Tahoe t065
    // kDHL_1500, kMRelease37 = Tahoe t066
    // kDHL_1500, kMRelease38 = Tahoe t067
    // kDHL_1500, kMRelease39 = Tahoe t068
    // kDHL_1500, kMRelease40 = Tahoe t069..t070 (fmt changed, tho this didn't)
    // kDHL_1500, kMRelease41 = Tahoe t071
    // kDHL_1500, kMRelease42 = Tahoe t072
    // kDHL_1500, kMRelease43 = Tahoe t073
    // kDHL_1500, kMRelease44 = Tahoe t074
    // kDHL_1500, kMRelease45 = Tahoe t075..t077
    // kDHL_1500, kMRelease46 = Tahoe t078
    // kDHL_1015, kMRelease0  = Tahoe t079..t080
    // kDHL_1015, kMRelease1  = Tahoe t081..t083
    // kDHL_1015, kMRelease2  = Tahoe t084..t086
    // kDHL_1015, kMRelease3  = Tahoe t087..t088
    // kDHL_1015, kMRelease4  = Tahoe t089..t091
    // kDHL_1015, kMRelease5  = Tahoe t092..t094
    // kDHL_1015, kMRelease6  = Tahoe t095..
    // kDHL_1015, kMRelease7  = Banff u002..
    // kDHL_1015, kMRelease8  = Banff u016..
    // kDHL_1015, kMRelease9  = Banff u028..
    // kDHL_1015, kMRelease10 = Banff u070..
    // kDHL_1015, kMRelease11 = Banff SP3...
    // kDHL_1015, kMRelease12 = Kirkland K001...
    // kDHL_1015, kMRelease13 = Kirkland K009 (Banff SP3 merge)

    enum MaintenanceReleaseVersion
                           { kMRelease0         = 0,
                             kMRelease1         = 1,
                             kMRelease2         = 2,
                             kMRelease3         = 3,
                             kMRelease4         = 4,
                             kMRelease5         = 5,
                             kMRelease6         = 6,
                             kMRelease7         = 7,
                             kMRelease8         = 8,
                             kMRelease9         = 9,
                             kMRelease10        = 10,
                             kMRelease11        = 11,
                             kMRelease12        = 12,
                             kMRelease13        = 13,
                             kMRelease14        = 14,
                             kMRelease15        = 15,
                             kMRelease16        = 16,
                             kMRelease17        = 17,
                             kMRelease18        = 18,
                             kMRelease19        = 19,
                             kMRelease20        = 20,
                             kMRelease21        = 21,
                             kMRelease22        = 22, 
                             kMRelease23        = 23,
                             kMRelease24        = 24,
                             kMRelease25        = 25,
                             kMRelease26        = 26,
                             kMRelease27        = 27,
                             kMRelease28        = 28,
                             kMRelease29        = 29,
                             kMRelease30        = 30,
                             kMRelease31        = 31,
                             kMRelease32        = 32,
                             kMRelease33        = 33,
                             kMRelease34        = 34,
                             kMRelease35        = 35,
                             kMRelease36        = 36,
                             kMRelease37        = 37,
                             kMRelease38        = 38,
                             kMRelease39        = 39,
                             kMRelease40        = 40,
                             kMRelease41        = 41,
                             kMReleaseFirstValid1500 = kMRelease41,
                             kMRelease42        = 42,
                             kMRelease43        = 43,
                             kMRelease44        = 44,
                             kMRelease45        = 45,
                             kMRelease46        = 46,
                             kMRelease47        = 47,
                             kMRelease48        = 48,
                             kMRelease49        = 49,
                             kMReleaseCurrent   = kMRelease13,
                             kMReleaseUnknown   = 126,
                             kMReleaseMax       = 127 };

    enum SaveType          { kNoSave = 0,
                             kR12Save,
                             kR13Save,
                             kR14Save };

    enum GroupOperType     { kNoOp           = 0,
                             kAdd            = 1,
                             kRemove         = 2,
                             kRename         = 3,
                             kOrdered        = 4,       // Members reordered
                             kGrpDesc        = 5,       // Description Modified
                             kSelect         = 6,       // Selectibility flag
                             kCreate         = 7,       // New group creation
                             kPrepend        = 8,
                             kInsert         = 9,
                             kGrpFlags       = 10 };     

    // kDcInsert     => Database INSERT in which entities from the source
    //                  database could be moved into the destination database.
    // kDcInsertCopy => Database INSERT in which the source database is left
    //                  intact. Objects are copied to the destination database.
    //
    enum DeepCloneType     { kDcCopy           = 0,
                             kDcExplode        = 1,
                             kDcBlock          = 2,
                             kDcXrefBind       = 3,
                             kDcSymTableMerge  = 4,
                             kDcInsert         = 6,
                             kDcWblock         = 7,
                             kDcObjects        = 8,
                             kDcXrefInsert     = 9,
                             kDcInsertCopy     = 10,
                             kDcWblkObjects    = 11 };

    // Handling for duplicate Symbol and Dictionary records
    //
    enum DuplicateRecordCloning { 
                             kDrcNotApplicable  = 0,
                             kDrcIgnore         = 1,   // Keep existing
                             kDrcReplace        = 2,   // Use clone
                             kDrcXrefMangleName = 3,   // <xref>$0$<name>
                             kDrcMangleName     = 4,   // $0$<name>
                             kDrcUnmangleName   = 5 };

    enum XrefStatus        { kXrfNotAnXref     = 0,
                             kXrfResolved      = 1,
                             kXrfUnloaded      = 2,
                             kXrfUnreferenced  = 3,
                             kXrfFileNotFound  = 4,
                             kXrfUnresolved    = 5 };

    enum MeasurementValue {
                kEnglish = 0,
                kMetric  = 1,
    };

    enum UnitsValue {
        kUnitsUndefined     = 0,
        kUnitsInches        = 1,
        kUnitsFeet          = 2,
        kUnitsMiles         = 3,
        kUnitsMillimeters   = 4,
        kUnitsCentimeters   = 5,
        kUnitsMeters        = 6,
        kUnitsKilometers    = 7,
        kUnitsMicroinches   = 8,
        kUnitsMils          = 9,
        kUnitsYards         = 10,
        kUnitsAngstroms     = 11,
        kUnitsNanometers    = 12,
        kUnitsMicrons       = 13,
        kUnitsDecimeters    = 14,
        kUnitsDekameters    = 15,
        kUnitsHectometers   = 16,
        kUnitsGigameters    = 17,
        kUnitsAstronomical  = 18,
        kUnitsLightYears    = 19,
        kUnitsParsecs       = 20,
        kUnitsMax           = kUnitsParsecs,
    };

    // lineweights are in 100ths of a millimeter

    enum LineWeight        { kLnWt000          =   0,
                             kLnWt005          =   5,
                             kLnWt009          =   9,
                             kLnWt013          =  13,
                             kLnWt015          =  15,
                             kLnWt018          =  18,
                             kLnWt020          =  20,
                             kLnWt025          =  25,
                             kLnWt030          =  30,
                             kLnWt035          =  35,
                             kLnWt040          =  40,
                             kLnWt050          =  50,
                             kLnWt053          =  53,
                             kLnWt060          =  60,
                             kLnWt070          =  70,
                             kLnWt080          =  80,
                             kLnWt090          =  90,
                             kLnWt100          = 100,
                             kLnWt106          = 106,
                             kLnWt120          = 120,
                             kLnWt140          = 140,
                             kLnWt158          = 158,
                             kLnWt200          = 200,
                             kLnWt211          = 211,
                             kLnWtByLayer      = -1,
                             kLnWtByBlock      = -2,
                             kLnWtByLwDefault  = -3 };


    enum EndCaps           { kEndCapNone       =  0,
                             kEndCapRound      =  1,
                             kEndCapAngle      =  2,
                             kEndCapSquare     =  3 };

    enum JoinStyle         { kJnStylNone       =  0,
                             kJnStylRound      =  1,
                             kJnStylAngle      =  2,
                             kJnStylFlat       =  3 };

    enum PlotStyleNameType { kPlotStyleNameByLayer       = 0,
                             kPlotStyleNameByBlock       = 1,
                             kPlotStyleNameIsDictDefault = 2,
                             kPlotStyleNameById          = 3 };

    enum DimArrowFlags     { kFirstArrow  = 0x00,
                             kSecondArrow = 0x01 };

    enum DimblkFlags       { kDimblk = 0,
                             kDimblk1,
                             kDimblk2,
                             kDimLdrBlk };

    enum OrthographicView  { kNonOrthoView = 0,
                             kTopView      = 1,
                             kBottomView   = 2,
                             kFrontView    = 3,
                             kBackView     = 4,
                             kLeftView     = 5,
                             kRightView    = 6 };

    enum VpFreezeOps       { kFreeze = 0,
                             kThaw,
                             kReset };

    // If adding to the following enum you must change the array
    // in constant.cpp and the initialization string in constant.xmf.
    enum reservedStringEnumType { kByLayer = 0,
                             kByBlock      = 1,
                             kNone         = 2,
                             kContinuous   = 3,
                             kStandard     = 4, 
                             kNormal       = 5,
                             kDefPoints    = 6,
                             kDefault      = 7,
                             kMissing      = 8,
                             kByColor      = 9,
                             kModel        = 10,
                             kReservedStringCount };

    // SortEntsFlags:  Specifies when entity traversals are in sorted order
    //
    enum SortEntsFlags     { kSortEntsSelection  = 0x01,
                             kSortEntsOsnap      = 0x02,
                             kSortEntsRedraw     = 0x04,
                             kSortEntsSlide      = 0x08, // (obsolete)
                             kSortEntsRegen      = 0x10, 
                             kSortEntsPlot       = 0x20,
                             kSortEntsPsout      = 0x40 };

}; // struct AcDb

#pragma pack(pop)

#endif
