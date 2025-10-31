#ifndef AD_DBDIM_H
#define AD_DBDIM_H
//
//
//  Copyright 1993-1999 by Autodesk, Inc.
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
//
//  The AcDmUtil dimstyle utility function namespace is also here.
//
#include "dbmain.h"
#include "dbmtext.h"

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
    const char* globalArrowName(const char* pName);
    const char* globalArrowName(AcDbObjectId blockId);
    //
    // Given the name (or objectId) of an arrowhead, return the
    // local name:
    const char* arrowName(const char* pName);
    const char* arrowName(AcDbObjectId blockId);

    // Is this the local or global name of a built-in (pre-defined) arrowhead?
    bool isBuiltInArrow(const char* pName);

    // Is this the local or global name of a "no length" arrowhead?
    bool isZeroLengthArrow(const char* pName);

    // Both of these look up pName in the AcDbBlockTable and return the id 
    //  of the AcDbBlockTableRecord if found.
    //
    // findArrowId() returns eKeyNotFound if the block is not present:
    Acad::ErrorStatus findArrowId(const char* pName, 
                                        AcDbObjectId& blockId, 
                                        AcDbDatabase* pDb = 0);
    //
    // getArrowId() will create the block if pName is a built-in arrowhead name:
    Acad::ErrorStatus getArrowId(const char* pName, 
                                        AcDbObjectId& blockId, 
                                        AcDbDatabase* pDb = 0);
};



class AcDbDimension: public AcDbEntity
{
public:
    AcDbDimension();
    ~AcDbDimension();
    ACDB_DECLARE_MEMBERS(AcDbDimension);

    AcGePoint3d      	textPosition() const;
    Acad::ErrorStatus	setTextPosition(const AcGePoint3d&);

    Adesk::Boolean	isUsingDefaultTextPosition() const;
    Acad::ErrorStatus	useSetTextPosition();
    Acad::ErrorStatus	useDefaultTextPosition();

    AcGeVector3d	normal() const;
    Acad::ErrorStatus	setNormal(const AcGeVector3d&);

    virtual Adesk::Boolean    isPlanar() const { return Adesk::kTrue; }
    virtual Acad::ErrorStatus getPlane(AcGePlane&, AcDb::Planarity&) const;

    double              elevation() const;
    Acad::ErrorStatus   setElevation(double);

    char*		dimensionText() const;
    Acad::ErrorStatus	setDimensionText(const char*);

    double		textRotation() const;
    Acad::ErrorStatus	setTextRotation(double);

    AcDbObjectId	dimensionStyle() const;
    Acad::ErrorStatus	setDimensionStyle(AcDbObjectId);

    AcDbMText::AttachmentPoint textAttachment() const;
    Acad::ErrorStatus   setTextAttachment(AcDbMText::AttachmentPoint eAtt);

    AcDb::LineSpacingStyle textLineSpacingStyle() const;
    Acad::ErrorStatus   setTextLineSpacingStyle(AcDb::LineSpacingStyle eStyle);

    double              textLineSpacingFactor() const;
    Acad::ErrorStatus   setTextLineSpacingFactor(double dFactor);

    Acad::ErrorStatus   getDimstyleData(AcDbDimStyleTableRecord*& pRecord) const;
    Acad::ErrorStatus   setDimstyleData(AcDbDimStyleTableRecord* pNewData);
    Acad::ErrorStatus   setDimstyleData(AcDbObjectId newDataId);

    virtual void	erased(AcDbObject* dbObj, Adesk::Boolean bErasing);
    virtual void        objectClosed(const AcDbObjectId dbObj);

    double              horizontalRotation() const;
    Acad::ErrorStatus	setHorizontalRotation(double newVal);

    // Functions for accessing the Dimension's defining block
    //
    AcDbObjectId     	dimBlockId() const;
    Acad::ErrorStatus	setDimBlockId(const AcDbObjectId&);
    AcGePoint3d      	dimBlockPosition() const;
    Acad::ErrorStatus	setDimBlockPosition(const AcGePoint3d&);
    Acad::ErrorStatus	recomputeDimBlock(bool forceUpdate = true);
    Acad::ErrorStatus	generateLayout();
    Acad::ErrorStatus   measurement(double &val);
    Acad::ErrorStatus   formatMeasurement(char *MTextContentBuffer,
                                          double measurement,
                                          char *dimensionText);


    //new getOsnapPoints API
    Acad::ErrorStatus getOsnapPoints(AcDb::OsnapMode osnapMode,
                                     const AcDbFullSubentPath& subentId,
                                     const AcGePoint3d&  pickPoint,
                                     const AcGePoint3d&  lastPoint,
                                     const AcGeMatrix3d& viewXform,
                                     AcGePoint3dArray&   snapPoints,
                                     AcDbIntArray&   geomIds) const;
                                     
    // Old OSNAP API, for dimensions it is unavailable.
    Acad::ErrorStatus   getOsnapPoints(AcDb::OsnapMode     osnapMode,
                                       int                 gsSelectionMark,
        				               const AcGePoint3d&  pickPoint,
                     				   const AcGePoint3d&  lastPoint,
                         			   const AcGeMatrix3d& viewXform,
                        			   AcGePoint3dArray&   snapPoints,
                        			   AcDbIntArray&       geomIds) const;                                     

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
};

class AcDbOrdinateDimension: public AcDbDimension
{
public:
    AcDbOrdinateDimension();
    AcDbOrdinateDimension(
        Adesk::Boolean     useXAxis,
        const AcGePoint3d& definingPoint,
        const AcGePoint3d& leaderEndPoint,
        const char*        dimText = NULL,
        AcDbObjectId       dimStyle  = AcDbObjectId::kNull);
    ~AcDbOrdinateDimension();
    ACDB_DECLARE_MEMBERS(AcDbOrdinateDimension);

    Adesk::Boolean	isUsingXAxis() const;
    Adesk::Boolean	isUsingYAxis() const;
    Acad::ErrorStatus	useXAxis();
    Acad::ErrorStatus	useYAxis();

    AcGePoint3d		origin() const;
    Acad::ErrorStatus	setOrigin(const AcGePoint3d&);

    AcGePoint3d		definingPoint() const;
    Acad::ErrorStatus	setDefiningPoint(const AcGePoint3d&);

    AcGePoint3d		leaderEndPoint() const;
    Acad::ErrorStatus	setLeaderEndPoint(const AcGePoint3d&);

    // Get corresponding COM wrapper class ID
    //
    virtual Acad::ErrorStatus   getClassID(CLSID* pClsid) const;
};

class AcDbAlignedDimension: public AcDbDimension
{
public:
    AcDbAlignedDimension();
    AcDbAlignedDimension(
        const AcGePoint3d& xLine1Point,
        const AcGePoint3d& xLine2Point,
        const AcGePoint3d& dimLinePoint,
        const char*        dimText = NULL,
        AcDbObjectId       dimStyle = AcDbObjectId::kNull);
    ~AcDbAlignedDimension();
    ACDB_DECLARE_MEMBERS(AcDbAlignedDimension);

    AcGePoint3d		xLine1Point() const;
    Acad::ErrorStatus	setXLine1Point(const AcGePoint3d&);

    AcGePoint3d		xLine2Point() const;
    Acad::ErrorStatus	setXLine2Point(const AcGePoint3d&);

    AcGePoint3d		dimLinePoint() const;
    Acad::ErrorStatus	setDimLinePoint(const AcGePoint3d&);

    double		oblique() const;
    Acad::ErrorStatus	setOblique(double);

    // Get corresponding COM wrapper class ID
    //
    virtual Acad::ErrorStatus   getClassID(CLSID* pClsid) const;
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
        const char*        dimText = NULL,
        AcDbObjectId       dimStyle = AcDbObjectId::kNull);
    ~AcDbRotatedDimension();
    ACDB_DECLARE_MEMBERS(AcDbRotatedDimension);

    AcGePoint3d		xLine1Point() const;
    Acad::ErrorStatus	setXLine1Point(const AcGePoint3d&);

    AcGePoint3d		xLine2Point() const;
    Acad::ErrorStatus	setXLine2Point(const AcGePoint3d&);

    AcGePoint3d		dimLinePoint() const;
    Acad::ErrorStatus	setDimLinePoint(const AcGePoint3d&);

    double		oblique() const;
    Acad::ErrorStatus	setOblique(double);

    double		rotation() const;
    Acad::ErrorStatus	setRotation(double);

    // Get corresponding COM wrapper class ID
    //
    virtual Acad::ErrorStatus   getClassID(CLSID* pClsid) const;
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
        const char*        dimText = NULL,
        AcDbObjectId       dimStyle = AcDbObjectId::kNull);
    ~AcDb3PointAngularDimension();
    ACDB_DECLARE_MEMBERS(AcDb3PointAngularDimension);

    AcGePoint3d		    arcPoint() const;
    Acad::ErrorStatus	setArcPoint(const AcGePoint3d&);

    AcGePoint3d         xLine1Point() const;
    Acad::ErrorStatus	setXLine1Point(const AcGePoint3d&);

    AcGePoint3d         xLine2Point() const;
    Acad::ErrorStatus	setXLine2Point(const AcGePoint3d&);

    AcGePoint3d         centerPoint() const;
    Acad::ErrorStatus	setCenterPoint(const AcGePoint3d&);

    // Get corresponding COM wrapper class ID
    //
    virtual Acad::ErrorStatus   getClassID(CLSID* pClsid) const;
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
        const char*        dimText = NULL,
        AcDbObjectId       dimStyle = AcDbObjectId::kNull);
    ~AcDb2LineAngularDimension();
    ACDB_DECLARE_MEMBERS(AcDb2LineAngularDimension);

    AcGePoint3d		arcPoint() const;
    Acad::ErrorStatus	setArcPoint(const AcGePoint3d&);

    AcGePoint3d		xLine1Start() const;
    Acad::ErrorStatus	setXLine1Start(const AcGePoint3d&);

    AcGePoint3d		xLine1End() const;
    Acad::ErrorStatus	setXLine1End(const AcGePoint3d&);

    AcGePoint3d		xLine2Start() const;
    Acad::ErrorStatus	setXLine2Start(const AcGePoint3d&);

    AcGePoint3d		xLine2End() const;
    Acad::ErrorStatus	setXLine2End(const AcGePoint3d&);

    // Get corresponding COM wrapper class ID
    //
    virtual Acad::ErrorStatus   getClassID(CLSID* pClsid) const;
};

class AcDbRadialDimension: public AcDbDimension
{
public:
    AcDbRadialDimension();
    AcDbRadialDimension(
        const AcGePoint3d& center,
        const AcGePoint3d& chordPoint,
        double             leaderLength,
        const char*        dimText = NULL,
        AcDbObjectId       dimStyle = AcDbObjectId::kNull);
    ~AcDbRadialDimension();
    ACDB_DECLARE_MEMBERS(AcDbRadialDimension);

    double		leaderLength() const;
    Acad::ErrorStatus	setLeaderLength(double);

    AcGePoint3d		center() const;
    Acad::ErrorStatus	setCenter(const AcGePoint3d&);

    AcGePoint3d		chordPoint() const;
    Acad::ErrorStatus	setChordPoint(const AcGePoint3d&);

    // Get corresponding COM wrapper class ID
    //
    virtual Acad::ErrorStatus   getClassID(CLSID* pClsid) const;
};

class AcDbDiametricDimension: public AcDbDimension
{
public:
    AcDbDiametricDimension();
    AcDbDiametricDimension(
        const AcGePoint3d& chordPoint,
        const AcGePoint3d& farChordPoint,
        double             leaderLength,
        const char*        dimText = NULL,
        AcDbObjectId       dimStyle = AcDbObjectId::kNull);
    ~AcDbDiametricDimension();
    ACDB_DECLARE_MEMBERS(AcDbDiametricDimension);

    double		leaderLength() const;
    Acad::ErrorStatus	setLeaderLength(double);

    AcGePoint3d		chordPoint() const;
    Acad::ErrorStatus	setChordPoint(const AcGePoint3d&);

    AcGePoint3d		farChordPoint() const;
    Acad::ErrorStatus	setFarChordPoint(const AcGePoint3d&);

    // Get corresponding COM wrapper class ID
    //
    virtual Acad::ErrorStatus   getClassID(CLSID* pClsid) const;
};

#pragma pack(pop)

#endif
