//
#ifndef AD_DBHATCH_H
#define AD_DBHATCH_H 1
//
// (C) Copyright 1996-2009 by Autodesk, Inc.
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
// DBHATCH.H
//
// DESCRIPTION: API class declaration for AcDbHatch.
//

#include "acdb.h"
#include "dbmain.h"
#include "gelnsg2d.h"
#include "gelnsg3d.h"
#include "gearc2d.h"
#include "gearc3d.h"
#include "gept2dar.h"
#include "gevptar.h"
#include "geintarr.h"

#pragma pack(push, 8)

// A size of 32 is not sufficient: the pattern name itself can already be 31 characters
// long (plus one char for EOS), but it can have an appendix in the form of
// ",_O", making it a total of 35 characters max.
//
#define HATCH_PATTERN_NAME_LENGTH   35

// I think we should change the 32 below to 35 as well, but we can't do this
// in Spago (a compatibility release), because it would change the size of the
// AcDbGlobals struct.
// (See 'ACHAR m_szGradientName[GRADIENT_PATTERN_NAME_LENGTH]' in dbglobal.h.)
//
#define GRADIENT_PATTERN_NAME_LENGTH    32

class AcDbRegion;

class AcDbHatch: public AcDbEntity
{
public:

    // Enum Definition
    //

    enum HatchObjectType {
        kHatchObject      = 0,
        kGradientObject   = 1
    };

    enum HatchLoopType {
        kDefault             = 0,
        kExternal            = 1,
        kPolyline            = 2,
        kDerived             = 4,
        kTextbox             = 8,
        kOutermost           = 0x10,
        kNotClosed           = 0x20,
        kSelfIntersecting    = 0x40,
        kTextIsland          = 0x80,
        kDuplicate           = 0x100,
        kIsAnnotative        = 0x200,
        kDoesNotSupportScale = 0x400,
        kForceAnnoAllVisible = 0x800,
        kOrientToPaper       = 0x1000,
        kIsAnnotativeBlock   = 0x2000
    };

    enum HatchEdgeType {
        kLine             = 1,
        kCirArc           = 2,
        kEllArc           = 3,
        kSpline           = 4 
    };

    enum HatchPatternType {
        kUserDefined      = 0,
        kPreDefined       = 1,
        kCustomDefined    = 2 
    };

    enum HatchStyle {
        kNormal           = 0,
        kOuter            = 1,
        kIgnore           = 2 
    };

    enum GradientPatternType {
        kPreDefinedGradient     = 0,
        kUserDefinedGradient    = 1
    };

    // Constructors and Destructors
    //
    AcDbHatch ();

    virtual ~AcDbHatch();

    ACDB_DECLARE_MEMBERS(AcDbHatch);

    // Hatch Plane Methods
    //
    double elevation() const;
    Acad::ErrorStatus setElevation(double elevation);

    AcGeVector3d normal() const;
    Acad::ErrorStatus setNormal(const AcGeVector3d& normal);

    virtual Adesk::Boolean isPlanar() const { return true; }
    virtual Acad::ErrorStatus getPlane(AcGePlane&, AcDb::Planarity&) const;

    // Hatch Boundary Methods
    //
    int numLoops() const;

    Adesk::Int32 loopTypeAt(int loopIndex) const;

    Acad::ErrorStatus getLoopAt(int loopIndex,
                                Adesk::Int32& loopType,
                                AcGeVoidPointerArray& edgePtrs,
                                AcGeIntArray&  edgeTypes) const;

    Acad::ErrorStatus getLoopAt(int loopIndex,
                                Adesk::Int32& loopType,
                                AcGePoint2dArray& vertices,
                                AcGeDoubleArray& bulges) const;

    Acad::ErrorStatus appendLoop(Adesk::Int32 loopType,
                                 const AcGeVoidPointerArray& edgePtrs,
                                 const AcGeIntArray&  edgeTypes);

    Acad::ErrorStatus appendLoop(Adesk::Int32 loopType,
                                 const AcGePoint2dArray& vertices,
                                 const AcGeDoubleArray& bulges);

    Acad::ErrorStatus insertLoopAt(int loopIndex,
                                   Adesk::Int32 loopType,
                                   const AcGeVoidPointerArray& edgePtrs,
                                   const AcGeIntArray&  edgeTypes);

    Acad::ErrorStatus insertLoopAt(int loopIndex,
                                   Adesk::Int32 loopType,
                                   const AcGePoint2dArray& vertices,
                                   const AcGeDoubleArray& bulges);

    Acad::ErrorStatus removeLoopAt(int loopIndex);


    // Hatch Association Methods 
    //
    bool associative() const;
    Acad::ErrorStatus setAssociative(bool isAssociative);

    Acad::ErrorStatus appendLoop(Adesk::Int32 loopType,
                                 const AcDbObjectIdArray& dbObjIds);

    Acad::ErrorStatus insertLoopAt(int loopIndex,
                                   Adesk::Int32 loopType,
                                   const AcDbObjectIdArray& dbObjIds);

    Acad::ErrorStatus getAssocObjIdsAt(int loopIndex,
                                       AcDbObjectIdArray& dbObjIds) const;

    Acad::ErrorStatus getAssocObjIds(AcDbObjectIdArray& dbObjIds) const;

    Acad::ErrorStatus removeAssocObjIds();


    // determines Hatch or Gradient object type
    //
    AcDbHatch::HatchObjectType hatchObjectType() const;
    Acad::ErrorStatus setHatchObjectType(AcDbHatch::HatchObjectType type);

    virtual Adesk::Boolean isGradient() const;
    virtual Adesk::Boolean isHatch() const;

    // Gradient Style Methods
    //
    AcDbHatch::GradientPatternType gradientType() const;

    const ACHAR* gradientName() const;

    Acad::ErrorStatus setGradient(AcDbHatch::GradientPatternType gradType,
        const ACHAR* gradName);

    double gradientAngle() const;
    Acad::ErrorStatus setGradientAngle(double angle);

    Acad::ErrorStatus getGradientColors( unsigned int& count, 
                                            AcCmColor*& colors,
                                            float*& values );
    
    Acad::ErrorStatus setGradientColors( unsigned int count, 
                                            AcCmColor* colors,
                                            float* values );

    Adesk::Boolean getGradientOneColorMode() const;
    Acad::ErrorStatus setGradientOneColorMode( Adesk::Boolean oneColorMode );

    float getShadeTintValue() const;
    Acad::ErrorStatus setShadeTintValue( float value );
    Acad::ErrorStatus setShadeTintValueAndColor2( float value );

    float gradientShift() const;
    Acad::ErrorStatus setGradientShift( float shiftValue );

    Acad::ErrorStatus evaluateGradientColorAt( float value,
                                                AcCmColor& color );

    // Hatch Pattern Methods
    //
    AcDbHatch::HatchPatternType patternType() const;

    const ACHAR* patternName() const;

    Acad::ErrorStatus  setPattern(AcDbHatch::HatchPatternType patType,
                                  const ACHAR* patName);

    double patternAngle() const;
    Acad::ErrorStatus setPatternAngle(double angle);

    double patternSpace() const;
    Acad::ErrorStatus setPatternSpace(double space);

    double patternScale() const;
    Acad::ErrorStatus setPatternScale(double scale);

    bool patternDouble() const;
    Acad::ErrorStatus setPatternDouble(bool isDouble);

    int numPatternDefinitions() const;
    Acad::ErrorStatus  getPatternDefinitionAt(int index, 
                                              double& angle,
                                              double& baseX,
                                              double& baseY,
                                              double& offsetX,
                                              double& offsetY,
                                              AcGeDoubleArray& dashes)
                                              const;


    // Hatch Style Methods
    //
    AcDbHatch::HatchStyle hatchStyle() const;
    Acad::ErrorStatus setHatchStyle(AcDbHatch::HatchStyle hstyle);

    // Hatch Graphics Display Control Methods
    //
    Acad::ErrorStatus  evaluateHatch(bool bUnderestimateNumLines = false);
    bool               lineGenerationEnabled() const;
    bool               setLineGenerationEnabled(bool bEnable);

    int numHatchLines() const;

    bool isSolidFill() const;
    
    Acad::ErrorStatus  getHatchLineDataAt(int index, 
                                          AcGePoint2d& startPt,
                                          AcGePoint2d& endPt) const;

    Acad::ErrorStatus  getHatchLinesData(AcGePoint2dArray& startPts,
                                         AcGePoint2dArray& endPts) const;

    // Reactor Methods
    //

    virtual void modifiedGraphics(const AcDbEntity* pObj);


    // Overridden AcDbObject Methods
    //
    virtual Acad::ErrorStatus subSwapIdWith(AcDbObjectId otherId,
                 Adesk::Boolean swapXdata = false,
                 Adesk::Boolean swapExtDict = false);


    // Used in conjunction with swapIdWith to swap reference definitions
    // as well.
    //
    virtual Acad::ErrorStatus  swapReferences(const AcDbIdMapping& idMap);

    Acad::ErrorStatus getArea(double& a) const;

    Acad::ErrorStatus setOriginPoint(const AcGePoint2d& pt);
    AcGePoint2d originPoint() const;

    AcDbRegion* getRegionArea() const;

    void removeHatchLines();

protected:
    virtual Acad::ErrorStatus  subGetClassID(CLSID* pClsid) const;

}; // END_ACDB_CLASS(AcDbHatch)

#pragma pack(pop)

#endif /* AD_DBHATCH_H */
