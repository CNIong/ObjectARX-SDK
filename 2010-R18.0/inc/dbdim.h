#ifndef AD_DBDIM_H
#define AD_DBDIM_H
//
//
//  Copyright 1993-2009 by Autodesk, Inc.
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
//  DESCRIPTION: Exported dimension classes
//
//  AcRxObject
//    AcDbObject
//      AcDbEntity
//        AcDbDimension
//          AcDbOrdinateDimension
//          AcDbAlignedDimension
//          AcDbRotatedDimension
//          AcDb3PointAngularDimension
//          AcDb2LineAngularDimension
//          AcDbRadialDimension
//          AcDbDiametricDimension
//          AcDbArcDimension
//          AcDbRadialDimensionLarge
//
//  The AcDmUtil dimstyle utility function namespace is also here.
//
#include "dbmain.h"
#include "dbmtext.h"
#include "acgi.h"

// Hidden layer to accommodate dynamic dimensional constraints.
#define DYNAMIC_CONSTRAINT_LAYER_OLD		_T("LayerNameForDynamicConstraint")
#define DYNAMIC_CONSTRAINT_LAYER_HIDDEN_OLD	_T("*LayerNameForDynamicConstraint")

// New names for anonymous layers.
#define DYNAMIC_CONSTRAINT_LAYER			_T("ADSK_CONSTRAINTS")
#define DYNAMIC_CONSTRAINT_LAYER_HIDDEN		_T("*ADSK_CONSTRAINTS")

#pragma pack(push, 8)

//  ----------- Utility functions for dimensioning api: -------------------
//
namespace AcDmUtil
{
    // Return R14 dimvar value given new dimvar values:
    //
    int dimfit  (int dimatfit, int dimtmove);
    int dimunit (int dimlunit, int dimfrac );

    // Return R15 dimvar value, given old dimvar value:
    //
    int dimatfit(int dimfit);
    int dimtmove(int dimfit);
    int dimlunit(int dimunit);
    int dimfrac (int dimunit);


    // -------  Arrowhead management utilities:  ---------

    // All functions will take either local or global name as input.

    // Arrow name utilities:
    // - All four name functions return the same name for user-defined
    //   arrowheads -- the name of the block in the AcDbBlockTable.
    // - All four name functions return NULL if the input is not a valid
    //   arrowhead name or block Id.
    // Caller is responsible for freeing the memory which is passed back.
    //
    // Given the name (or objectId) of an arrowhead, return the
    // globally invariant name:
    const ACHAR * globalArrowName(const ACHAR * pName);
    const ACHAR * globalArrowName(AcDbObjectId blockId);
    //
    // Given the name (or objectId) of an arrowhead, return the
    // local name:
    const ACHAR * arrowName(const ACHAR * pName);
    const ACHAR * arrowName(AcDbObjectId blockId);

    // Is this the local or global name of a built-in (pre-defined) arrowhead?
    bool isBuiltInArrow(const ACHAR * pName);

    // Is this the local or global name of a "no length" arrowhead?
    bool isZeroLengthArrow(const ACHAR * pName);

    // Both of these look up pName in the AcDbBlockTable and return the id 
    //  of the AcDbBlockTableRecord if found.
    //
    // findArrowId() returns eKeyNotFound if the block is not present:
    Acad::ErrorStatus findArrowId(const ACHAR * pName, 
                                  AcDbObjectId& blockId, 
                                  AcDbDatabase* pDb = 0);
    //
    // getArrowId() will create the block if pName is a built-in arrowhead name:
    Acad::ErrorStatus getArrowId(const ACHAR * pName, 
                                 AcDbObjectId& blockId, 
                                 AcDbDatabase* pDb = 0);
};



class ADESK_NO_VTABLE AcDbDimension: public AcDbEntity
{
protected:
    AcDbDimension();
                                     
public:
    ~AcDbDimension();
    ACDB_DECLARE_MEMBERS(AcDbDimension);

    AcGePoint3d         textPosition() const;
    Acad::ErrorStatus   setTextPosition(const AcGePoint3d&);

    Adesk::Boolean      isUsingDefaultTextPosition() const;
    Acad::ErrorStatus   useSetTextPosition();
    Acad::ErrorStatus   useDefaultTextPosition();

    AcGeVector3d        normal() const;
    Acad::ErrorStatus   setNormal(const AcGeVector3d&);

    virtual Adesk::Boolean    isPlanar() const { return true; }
    virtual Acad::ErrorStatus getPlane(AcGePlane&, AcDb::Planarity&) const;

    double              elevation() const;
    Acad::ErrorStatus   setElevation(double);

    ACHAR *             dimensionText() const;
    Acad::ErrorStatus   setDimensionText(const ACHAR *);

    double              textRotation() const;
    Acad::ErrorStatus   setTextRotation(double);

    AcDbObjectId        dimensionStyle() const;
    Acad::ErrorStatus   setDimensionStyle(AcDbObjectId);

    AcDbMText::AttachmentPoint textAttachment() const;
    Acad::ErrorStatus   setTextAttachment(AcDbMText::AttachmentPoint eAtt);

    AcDb::LineSpacingStyle textLineSpacingStyle() const;
    Acad::ErrorStatus   setTextLineSpacingStyle(AcDb::LineSpacingStyle eStyle);

    double              textLineSpacingFactor() const;
    Acad::ErrorStatus   setTextLineSpacingFactor(double dFactor);

    Acad::ErrorStatus   getDimstyleData(AcDbDimStyleTableRecord*& pRecord) const;
    Acad::ErrorStatus   setDimstyleData(AcDbDimStyleTableRecord* pNewData);
    Acad::ErrorStatus   setDimstyleData(AcDbObjectId newDataId);

    // Note: this erased() method doesn't actually get called!  The
    // dbObj arg is not const, so it is not really overriding the
    // reactor's base class method.
    //
    virtual void        erased(AcDbObject* dbObj, Adesk::Boolean bErasing);
    virtual void        objectClosed(const AcDbObjectId dbObj);
    virtual void        dragStatus(const AcDb::DragStat status);

    double              horizontalRotation() const;
    Acad::ErrorStatus   setHorizontalRotation(double newVal);

    // Functions for accessing the Dimension's defining block
    //
    AcDbObjectId        dimBlockId() const;
    Acad::ErrorStatus   setDimBlockId(const AcDbObjectId&);
    AcGePoint3d         dimBlockPosition() const;
    Acad::ErrorStatus   setDimBlockPosition(const AcGePoint3d&);
    Acad::ErrorStatus   recomputeDimBlock(bool forceUpdate = true);
    Acad::ErrorStatus   generateLayout();
    Acad::ErrorStatus   measurement(double &val);
    Acad::ErrorStatus   formatMeasurement(ACHAR *MTextContentBuffer,
                                          double measurement,
                                          ACHAR *dimensionText);

    // Functions for Dynamic Dimensions control
    //
    bool                isDynamicDimension() const;
    Acad::ErrorStatus   setDynamicDimension(bool newVal);

    //new getOsnapPoints API
    Acad::ErrorStatus   getOsnapPointsAtSubentPath(AcDb::OsnapMode osnapMode,
                                     const AcDbFullSubentPath& subentId,
                                     const AcGePoint3d&  pickPoint,
                                     const AcGePoint3d&  lastPoint,
                                     const AcGeMatrix3d& viewXform,
                                     AcGePoint3dArray&   snapPoints,
                                     AcDbIntArray &   geomIds) const;

   
    AcDbObjectId dimLineLinetype() const;
    Acad::ErrorStatus setDimLineLinetype(const AcDbObjectId linetype);
    AcDbObjectId dimExt1Linetype() const;
    Acad::ErrorStatus setDimExt1Linetype(const AcDbObjectId linetype);
    AcDbObjectId dimExt2Linetype() const;
    Acad::ErrorStatus setDimExt2Linetype(const AcDbObjectId linetype);

    Acad::ErrorStatus   removeTextField();
    Acad::ErrorStatus   fieldToMText(AcDbMText* pDimMText);
    Acad::ErrorStatus   fieldFromMText(AcDbMText* pDimMText);

    // Dimension variable api:
    //
    #undef DBDIMVAR_H                   // force the file to get read again
    #include "dbdimvar.h"
    // DEPRECATED METHODS!
    // These are supported but will be removed in future releases:
    //
    int dimfit() const;
    int dimunit() const;

    Acad::ErrorStatus setDimfit (int );
    Acad::ErrorStatus setDimunit(int );
    //
    // end DEPRECATED METHODS!
    
    // Functions for internal use only
    //
    bool                isHorizontalRefTextRotation() const;
    Acad::ErrorStatus   setHorizontalRefTextRotation(bool newVal);

    // Dimension Flip Arrow Support
    bool getArrowFirstIsFlipped() const;
    bool getArrowSecondIsFlipped() const;
    Acad::ErrorStatus setArrowFirstIsFlipped(bool bIsFlipped);
    Acad::ErrorStatus setArrowSecondIsFlipped(bool bIsFlipped);

    AcGeMatrix3d blockTransform() const;

    // Spago inspection dimension enhancement
    enum DimInspect {
        kShapeRemove  = 0,     // Not displayed
        kShapeRound   = 1,     // Rounded end (default)
        kShapeAngular = 2,     // Angular end
        kShapeNone    = 4,     // No bounding shape
        kShapeLabel   = 0x10,  // Label seperator and alpha field displayed
        kShapeRate    = 0x20,  // Shape seperator and alpha field displayed
    };
    bool inspection() const;
    Acad::ErrorStatus setInspection(bool val);

    int inspectionFrame() const;
    Acad::ErrorStatus setInspectionFrame(int frame);

    const ACHAR* inspectionLabel() const;
    Acad::ErrorStatus setInspectionLabel(const ACHAR* label);

    const ACHAR* inspectionRate() const;
    Acad::ErrorStatus setInspectionRate(const ACHAR* label);

    // Dimensional constraint support from dimension objects.
    bool  isConstraintObject() const;
    bool  isConstraintObject(bool &hasExpression,
                             bool &isReferenceConstraint) const;
    bool  isConstraintDynamic(void) const;
    Acad::ErrorStatus  setConstraintDynamic(bool bDynamic);

    bool  shouldParticipateInOPM(void) const;
    void  setShouldParticipateInOPM(bool bShouldParticipate);
};

class AcDbOrdinateDimension: public AcDbDimension
{
public:
    AcDbOrdinateDimension();
    AcDbOrdinateDimension(
        Adesk::Boolean     useXAxis,
        const AcGePoint3d& definingPoint,
        const AcGePoint3d& leaderEndPoint,
        const ACHAR *      dimText = NULL,
        AcDbObjectId       dimStyle  = AcDbObjectId::kNull);
    ~AcDbOrdinateDimension();
    ACDB_DECLARE_MEMBERS(AcDbOrdinateDimension);

    Adesk::Boolean      isUsingXAxis() const;
    Adesk::Boolean      isUsingYAxis() const;
    Acad::ErrorStatus   useXAxis();
    Acad::ErrorStatus   useYAxis();

    AcGePoint3d         origin() const;
    Acad::ErrorStatus   setOrigin(const AcGePoint3d&);

    AcGePoint3d         definingPoint() const;
    Acad::ErrorStatus   setDefiningPoint(const AcGePoint3d&);

    AcGePoint3d         leaderEndPoint() const;
    Acad::ErrorStatus   setLeaderEndPoint(const AcGePoint3d&);

protected:
    // Get corresponding COM wrapper class ID
    //
    virtual Acad::ErrorStatus   subGetClassID(CLSID* pClsid) const;
};

class AcDbAlignedDimension: public AcDbDimension
{
public:
    AcDbAlignedDimension();
    AcDbAlignedDimension(
        const AcGePoint3d& xLine1Point,
        const AcGePoint3d& xLine2Point,
        const AcGePoint3d& dimLinePoint,
        const ACHAR *      dimText = NULL,
        AcDbObjectId       dimStyle = AcDbObjectId::kNull);
    ~AcDbAlignedDimension();
    ACDB_DECLARE_MEMBERS(AcDbAlignedDimension);

    AcGePoint3d         xLine1Point() const;
    Acad::ErrorStatus   setXLine1Point(const AcGePoint3d&);

    AcGePoint3d         xLine2Point() const;
    Acad::ErrorStatus   setXLine2Point(const AcGePoint3d&);

    AcGePoint3d         dimLinePoint() const;
    Acad::ErrorStatus   setDimLinePoint(const AcGePoint3d&);

    double              oblique() const;
    Acad::ErrorStatus   setOblique(double);

    // Aligned dimension Jog symbol
    bool jogSymbolOn() const;
    Acad::ErrorStatus setJogSymbolOn(bool value);

    AcGePoint3d jogSymbolPosition() const;
    Acad::ErrorStatus setJogSymbolPosition(const AcGePoint3d& pt);

protected:
    // Get corresponding COM wrapper class ID
    //
    virtual Acad::ErrorStatus   subGetClassID(CLSID* pClsid) const;
};

class AcDbRotatedDimension: public AcDbDimension
{
public:
    AcDbRotatedDimension();
    AcDbRotatedDimension(
        double             rotation,
        const AcGePoint3d& xLine1Point,
        const AcGePoint3d& xLine2Point,
        const AcGePoint3d& dimLinePoint,
        const ACHAR *      dimText = NULL,
        AcDbObjectId       dimStyle = AcDbObjectId::kNull);
    ~AcDbRotatedDimension();
    ACDB_DECLARE_MEMBERS(AcDbRotatedDimension);

    AcGePoint3d         xLine1Point() const;
    Acad::ErrorStatus   setXLine1Point(const AcGePoint3d&);

    AcGePoint3d         xLine2Point() const;
    Acad::ErrorStatus   setXLine2Point(const AcGePoint3d&);

    AcGePoint3d         dimLinePoint() const;
    Acad::ErrorStatus   setDimLinePoint(const AcGePoint3d&);

    double              oblique() const;
    Acad::ErrorStatus   setOblique(double);

    double              rotation() const;
    Acad::ErrorStatus   setRotation(double);

    // Rotated dimension Jog symbol
    bool jogSymbolOn() const;
    Acad::ErrorStatus setJogSymbolOn(bool value);

    AcGePoint3d jogSymbolPosition() const;
    Acad::ErrorStatus setJogSymbolPosition(const AcGePoint3d& pt);

protected:
    // Get corresponding COM wrapper class ID
    //
    virtual Acad::ErrorStatus   subGetClassID(CLSID* pClsid) const;
};

class AcDb3PointAngularDimension: public AcDbDimension
{
public:
    AcDb3PointAngularDimension();
    AcDb3PointAngularDimension(
        const AcGePoint3d& centerPoint,
        const AcGePoint3d& xLine1Point,
        const AcGePoint3d& xLine2Point,
        const AcGePoint3d& arcPoint,
        const ACHAR *      dimText = NULL,
        AcDbObjectId       dimStyle = AcDbObjectId::kNull);
    ~AcDb3PointAngularDimension();
    ACDB_DECLARE_MEMBERS(AcDb3PointAngularDimension);

    AcGePoint3d         arcPoint() const;
    Acad::ErrorStatus   setArcPoint(const AcGePoint3d&);

    AcGePoint3d         xLine1Point() const;
    Acad::ErrorStatus   setXLine1Point(const AcGePoint3d&);

    AcGePoint3d         xLine2Point() const;
    Acad::ErrorStatus   setXLine2Point(const AcGePoint3d&);

    AcGePoint3d         centerPoint() const;
    Acad::ErrorStatus   setCenterPoint(const AcGePoint3d&);

    // Angular dimension extension arc for quadrant
    bool extArcOn() const;
    Acad::ErrorStatus setExtArcOn(bool value);

protected:
    // Get corresponding COM wrapper class ID
    //
    virtual Acad::ErrorStatus   subGetClassID(CLSID* pClsid) const;
};

class AcDb2LineAngularDimension: public AcDbDimension
{
public:
    AcDb2LineAngularDimension();
    AcDb2LineAngularDimension(
        const AcGePoint3d& xLine1Start,
        const AcGePoint3d& xLine1End,
        const AcGePoint3d& xLine2Start,
        const AcGePoint3d& xLine2End,
        const AcGePoint3d& arcPoint,
        const ACHAR *      dimText = NULL,
        AcDbObjectId       dimStyle = AcDbObjectId::kNull);
    ~AcDb2LineAngularDimension();
    ACDB_DECLARE_MEMBERS(AcDb2LineAngularDimension);

    AcGePoint3d         arcPoint() const;
    Acad::ErrorStatus   setArcPoint(const AcGePoint3d&);

    AcGePoint3d         xLine1Start() const;
    Acad::ErrorStatus   setXLine1Start(const AcGePoint3d&);

    AcGePoint3d         xLine1End() const;
    Acad::ErrorStatus   setXLine1End(const AcGePoint3d&);

    AcGePoint3d         xLine2Start() const;
    Acad::ErrorStatus   setXLine2Start(const AcGePoint3d&);

    AcGePoint3d         xLine2End() const;
    Acad::ErrorStatus   setXLine2End(const AcGePoint3d&);

    // Angular dimension extension arc for quadrant
    bool extArcOn() const;
    Acad::ErrorStatus setExtArcOn(bool value);

protected:
    // Get corresponding COM wrapper class ID
    //
    virtual Acad::ErrorStatus   subGetClassID(CLSID* pClsid) const;
};

class AcDbRadialDimension: public AcDbDimension
{
public:
    AcDbRadialDimension();
    AcDbRadialDimension(
        const AcGePoint3d& center,
        const AcGePoint3d& chordPoint,
        double             leaderLength,
        const ACHAR *      dimText = NULL,
        AcDbObjectId       dimStyle = AcDbObjectId::kNull);
    ~AcDbRadialDimension();
    ACDB_DECLARE_MEMBERS(AcDbRadialDimension);

    double              leaderLength() const;
    Acad::ErrorStatus   setLeaderLength(double);

    AcGePoint3d         center() const;
    Acad::ErrorStatus   setCenter(const AcGePoint3d&);

    AcGePoint3d         chordPoint() const;
    Acad::ErrorStatus   setChordPoint(const AcGePoint3d&);

    // Radial dimension extension arc
    double extArcStartAngle() const;
    Acad::ErrorStatus setExtArcStartAngle(double newAngle);

    double extArcEndAngle() const;
    Acad::ErrorStatus setExtArcEndAngle(double newAngle);

protected:
    // Get corresponding COM wrapper class ID
    //
    virtual Acad::ErrorStatus   subGetClassID(CLSID* pClsid) const;
};

class AcDbDiametricDimension: public AcDbDimension
{
public:
    AcDbDiametricDimension();
    AcDbDiametricDimension(
        const AcGePoint3d& chordPoint,
        const AcGePoint3d& farChordPoint,
        double             leaderLength,
        const ACHAR *      dimText = NULL,
        AcDbObjectId       dimStyle = AcDbObjectId::kNull);
    ~AcDbDiametricDimension();
    ACDB_DECLARE_MEMBERS(AcDbDiametricDimension);

    double              leaderLength() const;
    Acad::ErrorStatus   setLeaderLength(double);

    AcGePoint3d         chordPoint() const;
    Acad::ErrorStatus   setChordPoint(const AcGePoint3d&);

    AcGePoint3d         farChordPoint() const;
    Acad::ErrorStatus   setFarChordPoint(const AcGePoint3d&);

    // Diametric dimension extension arc
    double extArcStartAngle() const;
    Acad::ErrorStatus setExtArcStartAngle(double newAngle);

    double extArcEndAngle() const;
    Acad::ErrorStatus setExtArcEndAngle(double newAngle);

protected:
    // Get corresponding COM wrapper class ID
    //
    virtual Acad::ErrorStatus   subGetClassID(CLSID* pClsid) const;
};

// Arc length dimension class
class AcDbArcDimension: public AcDbDimension
{
public:
    // Default constructor
    AcDbArcDimension();
    // Primary constructor
    AcDbArcDimension(
        const AcGePoint3d& centerPoint,
        const AcGePoint3d& xLine1Point,
        const AcGePoint3d& xLine2Point,
        const AcGePoint3d& arcPoint,
        const ACHAR * dimText = NULL,
        AcDbObjectId dimStyle = AcDbObjectId::kNull);
    // Default destructor
    ~AcDbArcDimension();
    ACDB_DECLARE_MEMBERS(AcDbArcDimension);

    // Query method which returns a point on the arc length dimension's dimension arc.
    AcGePoint3d         arcPoint() const;
    // Set method to set the point which the arc length dimension's dimension arc passes through.
    Acad::ErrorStatus   setArcPoint(const AcGePoint3d & arcPt);

    // Query method which returns the start point for the arc length dimension's first extension line.
    AcGePoint3d         xLine1Point() const;
    // Set method which sets the start point for the arc length dimension's first extension line.        
    Acad::ErrorStatus   setXLine1Point(const AcGePoint3d & xLine1Pt);

    // Query method which returns the start point for the arc length dimension's second extension line.
    AcGePoint3d         xLine2Point() const;
    // Set method which sets the start point for the arc length dimension's second extension line.    
    Acad::ErrorStatus   setXLine2Point(const AcGePoint3d & xLine2Pt);

    // Query method which returns the center point of the arc dimensioned by the arc length dimension.
    AcGePoint3d         centerPoint() const;
    // Set method which sets the center point of the arc dimensioned by the arc length dimension.    
    Acad::ErrorStatus   setCenterPoint(const AcGePoint3d & ctrPt);

    // Query method which returns true if this arc length dimension was specified using two points along the arc, 
    // false if the arc length dimension dimensions the entire arc segment.
    bool                isPartial() const;
    // Set method if passed true, the arc length dimension was specified using the entire arc segment, 
    // if passed false the arc length dimension arc length dimension was specified using two points along the arc.
    Acad::ErrorStatus   setIsPartial(const bool & partial);

    // Query method which returns the parameter of the arc being dimensioned cooresponding to the arc length dimension's first definiton point.
    double              arcStartParam() const;
    // Set method which sets the parameter of the arc being dimensioned cooresponding to the arc length dimension's first definiton point.        
    Acad::ErrorStatus   setArcStartParam(const double & arcParam);

    // Query method which returns the parameter of the arc being dimensioned cooresponding to the arc length dimension's second definiton point.
    double              arcEndParam() const;
    // Set method which sets the parameter of the arc being dimensioned cooresponding to the arc length dimension's second definiton point.    
    Acad::ErrorStatus   setArcEndParam(const double & arcParam);

    // Query method which returns true if this arc length dimension has an extra leader drawn to resolve ambiguity, false if the arc length dimension has no extra leader drawn.
    bool                hasLeader() const;
    // Set method if passed true, the arc length dimension has an extra leader drawn to resolve ambiguity, if passed false the arc length dimension has no extra leader drawn.    
    Acad::ErrorStatus   setHasLeader(const bool & leaderVal);

    // Query method which returns the start point for the arc length dimension's extra leader, if drawn.
    AcGePoint3d         leader1Point() const;
    // Set method which sets the start point for the arc length dimension's extra leader, if drawn.        
    Acad::ErrorStatus   setLeader1Point(const AcGePoint3d & ldr1Pt);

    // Query method which returns the end point for the arc length dimension's extra leader, if drawn.
    AcGePoint3d         leader2Point() const;
    // Set method which sets the end point for the arc length dimension's extra leader, if drawn.    
    Acad::ErrorStatus   setLeader2Point(const AcGePoint3d & ldr2Pt);
    
    // Query method which returns the type of symbol used within the arc length dimension's text string:
    // 0 - Arc symbol precedes text, 1 - Arc symbol is above text, 2 - No arc symbol is used.
    int arcSymbolType() const;
    // Set method which sets the type of symbol to use within the arc length dimension's text string:
    // 0 - Arc symbol precedes text, 1 - Arc symbol is above text, 2 - No arc symbol is used.
    // This overrides the setting of this value in the dimension's style.
    Acad::ErrorStatus setArcSymbolType(const int symbol);

protected:
    // Get corresponding COM wrapper class ID
    virtual Acad::ErrorStatus  subGetClassID(CLSID* pClsid) const;
};

class AcDbRadialDimensionLarge: public AcDbDimension
{
public:
    // Default constructor
    AcDbRadialDimensionLarge();
    // Primary constructor
    AcDbRadialDimensionLarge(
        const AcGePoint3d& center,
        const AcGePoint3d& chordPoint,
        const AcGePoint3d& overrideCenter,
        const AcGePoint3d& jogPoint,
        double             jogAngle,
        const ACHAR *      dimText = NULL,
        AcDbObjectId       dimStyle = AcDbObjectId::kNull);
    // Default destructor
    ~AcDbRadialDimensionLarge();
    ACDB_DECLARE_MEMBERS(AcDbRadialDimensionLarge);


    // Query method which returns the center point of the arc dimensioned by the jogged radius dimension.    
    AcGePoint3d         center() const;
    // Set method which sets the center point of the arc dimensioned by the jogged radius dimension.        
    Acad::ErrorStatus   setCenter(const AcGePoint3d & centerPoint);

    // Query method which returns the chord point on the arc dimensioned by the jogged radius dimension.    
    AcGePoint3d         chordPoint() const;
    // Set method which sets the chord point on the arc dimensioned by the jogged radius dimension.        
    Acad::ErrorStatus   setChordPoint(const AcGePoint3d & chordPoint);

    // Query method which returns the overidden center point used by the jogged radius dimension.    
    AcGePoint3d         overrideCenter() const;
    // Set method which sets the overidden center point to use for the jogged radius dimension.        
    Acad::ErrorStatus   setOverrideCenter(const AcGePoint3d & overrideCenterPoint);

    // Query method which returns the jog point used by the jogged radius dimension.    
    AcGePoint3d         jogPoint() const;
    // Set method which sets the jog point used by the jogged radius dimension.        
    Acad::ErrorStatus   setJogPoint(const AcGePoint3d & jogPoint);

    // Query method which returns the jog angle used by the jogged radius dimension.    
    double              jogAngle() const;
    // Set method which sets the jog angle used by the jogged radius dimension.        
    Acad::ErrorStatus   setJogAngle(double jogAngle);

    // Used exclusively by property palette
    // This function is required because once the jogged radius dimension's defining points are updated, all the other defining points need to be updated too.
    Acad::ErrorStatus   setOverrideCenterPP(const AcGePoint3d & overrideCenterPointPP);
    // Used exclusively by property palette
    // This function is required because once the jogged radius dimension's defining points are updated, all the other defining points need to be updated too.    
    Acad::ErrorStatus   setJogPointPP(const AcGePoint3d & jogPointPP);
    // Used exclusively by property palette
    // This function is required because once the jogged radius dimension's defining points are updated, all the other defining points need to be updated too.    
    Acad::ErrorStatus   setTextPositionPP(const AcGePoint3d & textPointPP);

    // Radial large dimension extension arc
    double extArcStartAngle() const;
    Acad::ErrorStatus setExtArcStartAngle(double newAngle);

    double extArcEndAngle() const;
    Acad::ErrorStatus setExtArcEndAngle(double newAngle);

protected:
    // Get corresponding COM wrapper class ID
    virtual Acad::ErrorStatus   subGetClassID(CLSID * pClsid) const;
};

#pragma pack(pop)

#endif
