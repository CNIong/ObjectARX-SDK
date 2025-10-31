#pragma once
//
// (C) Copyright 1990-2009 by Autodesk, Inc.
//
//
//
// By using this code, you are agreeing to the terms
// and conditions of the License Agreement that appeared
// and was accepted upon download or installation
// (or in connection with the download or installation)
// of the Autodesk software in which this code is included.
// All permissions on use of this code are as set forth
// in such License Agreement provided that the above copyright
// notice appears in all authorized copies and that both that
// copyright notice and the limited warranty and
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

#undef ACAD_OBJID_INLINE_INTERNAL
#include "dbhatch.h"
#include <tchar.h>

class AcDbCircle;
class AcDb2dPolyline;
class AcDbPolyline;
class AcDbMPolygonCrossingArray;
class AcDbMPolygonNode;

const double AcDbMPolygonCrossingFuzz = 1E-6;

class AcDbMPolygon : public AcDbEntity {
public:

    enum loopDir {
        kExterior     = 0,            // counter clockwise
        kInterior,                    // clockwise
        kAnnotation                   // text
    };

    // Constructors and Destructors
    //
    AcDbMPolygon();
    virtual ~AcDbMPolygon();

    ACDB_DECLARE_MEMBERS(AcDbMPolygon);


    //*************************************************************************
    // Methods specific to AcDbMPolygon 
    //*************************************************************************

    // Mpolygon hatch member access methods.
    //
    virtual AcDbHatch * hatch();

    // Hatch Plane Methods
    //
    virtual double elevation() const;
    virtual Acad::ErrorStatus setElevation(double elevation);

    virtual AcGeVector3d normal() const;
    virtual Acad::ErrorStatus setNormal(const AcGeVector3d& normal);

    // Hatch Graphics Display Control Methods
    //
    virtual Acad::ErrorStatus  evaluateHatch(bool bUnderestimateNumLines = false);

    // Hatch Pattern Methods
    //
    virtual AcDbHatch::HatchPatternType patternType() const;

    virtual const TCHAR* patternName() const;

    virtual Acad::ErrorStatus  setPattern(AcDbHatch::HatchPatternType patType,
                                  const TCHAR* patName);

    virtual double patternAngle() const;
    virtual Acad::ErrorStatus setPatternAngle(double angle);

    virtual double patternSpace() const;
    virtual Acad::ErrorStatus setPatternSpace(double space);

    virtual double patternScale() const;
    virtual Acad::ErrorStatus setPatternScale(double scale);

    virtual bool patternDouble() const;
    virtual Acad::ErrorStatus setPatternDouble(bool isDouble);

    virtual int numPatternDefinitions() const;
    virtual Acad::ErrorStatus  getPatternDefinitionAt(int index, 
                                              double& angle,
                                              double& baseX,
                                              double& baseY,
                                              double& offsetX,
                                              double& offsetY,
                                              AcGeDoubleArray& dashes)
                                              const;

    // Hatch Gradient support

    Acad::ErrorStatus setGradientAngle(double angle);
    Acad::ErrorStatus setGradientShift( float shiftValue );
	Acad::ErrorStatus setGradientOneColorMode( Adesk::Boolean oneColorMode );
    Acad::ErrorStatus setGradientColors( unsigned int count, 
                                            AcCmColor* colors,
                                            float* values );
    Acad::ErrorStatus setGradient(AcDbHatch::GradientPatternType gradType,
                                   const TCHAR* gradName);


    // Mpolygon access methods.
    //
    virtual AcCmColor patternColor() const;
    virtual Acad::ErrorStatus setPatternColor(const AcCmColor& pc);

    virtual double getArea() const;
    virtual double getPerimeter() const;

    virtual bool isBalanced() const;

    virtual AcGeVector2d getOffsetVector() const;

    virtual Acad::ErrorStatus getMPolygonTree(AcDbMPolygonNode*& loopNode) const;
    virtual void deleteMPolygonTree(AcDbMPolygonNode* loopNode) const;

    // Mpolygon loop quiry and manipulation methods.
    //
    virtual Acad::ErrorStatus appendLoopFromBoundary(const AcDbCircle* pCircle,
        bool excludeCrossing = true, double tol = AcDbMPolygonCrossingFuzz);
    virtual Acad::ErrorStatus appendLoopFromBoundary(const AcDbPolyline* pPoly,
        bool excludeCrossing = true, double tol = AcDbMPolygonCrossingFuzz);
    virtual Acad::ErrorStatus appendLoopFromBoundary(const AcDb2dPolyline* pPoly,
        bool excludeCrossing = true, double tol = AcDbMPolygonCrossingFuzz);

    virtual int numMPolygonLoops() const;
    virtual Acad::ErrorStatus getMPolygonLoopAt(int loopIndex, AcGePoint2dArray& vertices,
                                        AcGeDoubleArray& bulges) const;

    virtual Acad::ErrorStatus insertMPolygonLoopAt(int loopIndex, 
        const AcGePoint2dArray& vertices, const AcGeDoubleArray& bulges, 
        bool excludeCrossing = true, double tol = AcDbMPolygonCrossingFuzz);

    virtual Acad::ErrorStatus appendMPolygonLoop(const AcGePoint2dArray& vertices, 
        const AcGeDoubleArray& bulges, bool excludeCrossing = true,
        double tol = AcDbMPolygonCrossingFuzz);
    virtual Acad::ErrorStatus removeMPolygonLoopAt(int loopIndex);

    virtual Acad::ErrorStatus balanceTree();
    virtual Acad::ErrorStatus balanceDisplay();

    virtual Acad::ErrorStatus getLoopDirection(int lindex, AcDbMPolygon::loopDir& dir) const;
    virtual Acad::ErrorStatus setLoopDirection(int lindex, AcDbMPolygon::loopDir dir);

    virtual Acad::ErrorStatus getLoopAtGsMarker(int gsMark, int &loop) const;
    virtual void getChildLoops(int curLoop, AcGeIntArray& selectedLoopIndexes) const;
    virtual int getParentLoop(int curLoop) const;
    virtual int getClosestLoopTo(const AcGePoint3d& worldPt) const;

    // Mpolyon loop crossing and inside methods.
    //
    virtual int isPointInsideMPolygon(const AcGePoint3d& worldPt, AcGeIntArray& loopsArray,
                                      double tol = AcDbMPolygonCrossingFuzz) const;
    virtual bool isPointOnLoopBoundary(const AcGePoint3d& worldPt, int loop, 
                                       double tol = AcDbMPolygonCrossingFuzz) const;

    virtual Acad::ErrorStatus loopCrossesItself(bool& crosses, bool findAll,
                                        AcDbMPolygonCrossingArray& crossingsArray,
                                        const AcGePoint2dArray& vertexPts, 
                                        const AcGeDoubleArray& vertexBulges, 
                                        double tol = AcDbMPolygonCrossingFuzz) const;

    virtual bool loopCrossesItself(const AcGePoint2dArray& vertexPts, 
                           const AcGeDoubleArray& vertexBulges, 
                           double tol = AcDbMPolygonCrossingFuzz) const;

    virtual Acad::ErrorStatus loopCrossesMPolygon(bool& crosses, bool findAll,
                                          AcDbMPolygonCrossingArray& crossingsArray,
                                          const AcGePoint2dArray& testVertexPts, 
                                          const AcGeDoubleArray& testVertexBulges, 
                                          double tol = AcDbMPolygonCrossingFuzz) const;

    virtual bool selfCrosses(const AcGePoint2dArray& vertexPts, 
                     const AcGeDoubleArray& vertexBulges,
                     double tol = AcDbMPolygonCrossingFuzz) const;

    virtual bool includesTouchingLoops(double tol = AcDbMPolygonCrossingFuzz) const;

    //*************************************************************************
    // Overridden methods from AcDbEntity
    //*************************************************************************
    virtual Acad::ErrorStatus subGetClassID( CLSID* pClsid) const;

    virtual Adesk::Boolean    subWorldDraw(AcGiWorldDraw*  mode);
    virtual void              saveAs(AcGiWorldDraw* mode, AcDb::SaveType st);

    virtual Acad::ErrorStatus subGetSubentPathsAtGsMarker(
        AcDb::SubentType      type,
		Adesk::GsMarker       gsMark,
        const AcGePoint3d&    pickPoint,
        const AcGeMatrix3d&   viewXform,
        int&                  numPaths,
        AcDbFullSubentPath*&  subentPaths,
        int                   numInserts = 0,
        AcDbObjectId*         entAndInsertStack 
        = NULL) const;
    
    virtual Acad::ErrorStatus subGetGsMarkersAtSubentPath(
        const AcDbFullSubentPath& subPath, 
		AcArray<Adesk::GsMarker>&         gsMarkers) const;

    virtual AcDbEntity*       subSubentPtr(const AcDbFullSubentPath& id) const;

    virtual Acad::ErrorStatus   subIntersectWith(
        const AcDbEntity*   ent,
        AcDb::Intersect     intType,
        AcGePoint3dArray&   points,
        Adesk::GsMarker     thisGsMarker  = 0,
        Adesk::GsMarker     otherGsMarker = 0)
        const;
    
    virtual Acad::ErrorStatus   subIntersectWith(
        const AcDbEntity*   ent,
        AcDb::Intersect     intType,
        const AcGePlane&    projPlane,
        AcGePoint3dArray&   points,
        Adesk::GsMarker     thisGsMarker  = 0,
        Adesk::GsMarker     otherGsMarker = 0)
        const;

    virtual Acad::ErrorStatus   subGetOsnapPoints(
        AcDb::OsnapMode       osnapMode,
        Adesk::GsMarker       gsSelectionMark,
        const AcGePoint3d&    pickPoint,
        const AcGePoint3d&    lastPoint,
        const AcGeMatrix3d&   viewXform,
        AcGePoint3dArray&        snapPoints,
        AcDbIntArray&     geomIds) const;

    virtual Acad::ErrorStatus subGetGripPoints(AcGePoint3dArray&     gripPoints,
        AcDbIntArray&  osnapModes,
        AcDbIntArray&  geomIds) const;

    virtual Acad::ErrorStatus subMoveGripPointsAt(const AcDbIntArray& indices,
        const AcGeVector3d& offset);

    virtual Acad::ErrorStatus subGetStretchPoints(AcGePoint3dArray& stretchPoints) const;

    virtual Acad::ErrorStatus subMoveStretchPointsAt( const AcDbIntArray& indices,
        const AcGeVector3d& offset);

    virtual Acad::ErrorStatus   subTransformBy(const AcGeMatrix3d& xform);
    virtual Acad::ErrorStatus	subGetGeomExtents(AcDbExtents& extents) const;
    virtual void              subList() const;
    
    virtual Acad::ErrorStatus   subExplode( AcDbVoidPtrArray& entitySet) const;

    //*************************************************************************
    // Overridden methods from AcDbObject
    //*************************************************************************
    
    virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* filer);
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* filer) const;
    virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* filer);
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* filer) const;
    virtual Acad::ErrorStatus audit(AcDbAuditInfo* );
    virtual Acad::ErrorStatus decomposeForSave(AcDb::AcDbDwgVersion ver,
        AcDbObject*& replaceObj, AcDbObjectId& replaceId, 
        Adesk::Boolean& exchangeXData);
    
    // Batch Mpolygon creation (it should have no loops)
	//
    virtual Acad::ErrorStatus createLoopsFromBoundaries (const AcDbObjectIdArray &ids,
        AcDbIntArray &rejectedObjs,
        bool excludeCrossing = true, double tol = AcDbMPolygonCrossingFuzz);
    virtual Acad::ErrorStatus createLoops (const AcArray<AcGePoint2dArray,AcArrayObjectCopyReallocator<AcGePoint2dArray> > &vertices,
        const AcArray<AcGeDoubleArray,AcArrayObjectCopyReallocator<AcGeDoubleArray> > &bulges, AcDbIntArray &rejectedObjs,
        bool excludeCrossing = true, double tol = AcDbMPolygonCrossingFuzz);

private:
    friend class AcDbImpMPolygon;
    void* pImp;
};

// This class is used during loop editing to store loops.
// The MpolygonUI.arx application uses this during dragging
// while in the MPEDT Move command.
class AcDbMpolygonLoops {
public:
    AcDbMpolygonLoops(int lindex, int gindex = 0, int gcnt = 0);

    int mLoopIndex;                   // AcDbHatch loop index.
    bool mIsText;                     // Annotation Loop?
    int mGripIndex;                   // Base grip index for this loop (grip editing only.)
    int mGripCount;                   // Number of hot grips in the loop (grip editing only.)
    AcGePoint2dArray mVertexPoints;    
    AcGeDoubleArray mVertexBulges;
};

inline
AcDbMpolygonLoops::AcDbMpolygonLoops(int lindex, int gindex, int gcnt)
{
    mLoopIndex = lindex;
    mGripIndex = gindex;
    mGripCount = gcnt;
}

// This class is used to store one mpolygon loop crossing point.
class AcDbMPolygonCrossing {
public:
    AcDbMPolygonCrossing();
    ~AcDbMPolygonCrossing();

    int getLoopIndex() const;         // Crossing loop index
    void setLoopIndex(int index);
    
    int getEdgeIndex() const;         // Starting vertex index of loop edge 
    void setEdgeIndex(int index);

    AcGePoint2d getCrossingPoint() const; // Loop crossing point
    void setCrossingPoint(const AcGePoint2d& pt);

private:
    void* pImp;
};

// An Array of class AcDbMPolygonCrossing (loop crossing points).
class AcDbMPolygonCrossingArray {
public:
    ~AcDbMPolygonCrossingArray();

    AcArray<AcDbMPolygonCrossing *> mCrossingArray;
};


inline
AcDbMPolygonCrossingArray::~AcDbMPolygonCrossingArray()
{
    AcDbMPolygonCrossing* pCrossing;
    int numCross = mCrossingArray.length();
    for (int i = numCross - 1; i >= 0; i--) {
        pCrossing = mCrossingArray[i];
        mCrossingArray.removeAt(i);
        if (pCrossing != NULL)
            delete pCrossing;
    }
}

// The following class is used by the getMPolygonTree API to
//  return the internal tree ordered loops.

class AcDbMPolygonNode {
public:
    // Constructor
    AcDbMPolygonNode();

public:
    AcDbMPolygonNode * mParent;
    AcArray<AcDbMPolygonNode*> mChildren;
    int mLoopIndex;                   // MPolygon loop index.
};

inline
AcDbMPolygonNode::AcDbMPolygonNode()
    : mLoopIndex(-1), mParent(NULL)
{
}



