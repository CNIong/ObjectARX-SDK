//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////


#include "dbents.h"
#include "acgi.h"

#define SIN45  0.7071067811865
#define HALFPI 3.14159265358979323846/2.0

class AsdkSquare : public AcDbCurve
{
public:
    ACRX_DECLARE_MEMBERS(AsdkSquare);
    AsdkSquare();
    virtual ~AsdkSquare();

    // AcDbEntity overrides
    //

    virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const;

    virtual Adesk::Boolean subWorldDraw(AcGiWorldDraw* wd);

    virtual Acad::ErrorStatus subGetOsnapPoints(AcDb::OsnapMode       osnapMode,
                                                Adesk::GsMarker     gsSelectionMark,
                                                const AcGePoint3d&    pickPoint,
                                                const AcGePoint3d&    lastPoint,
                                                const AcGeMatrix3d&   viewXform,
                                                AcGePoint3dArray&     snapPoints,
                                                AcDbIntArray&         geomIds
                                                ) const;

    virtual Acad::ErrorStatus subGetGripPoints(AcGePoint3dArray& gripPoints,
                                            AcDbIntArray& osnapModes,
                                            AcDbIntArray& geomIds) const;

    virtual Acad::ErrorStatus subMoveGripPointsAt(const AcDbIntArray& indices,
                                            const AcGeVector3d& offset);

    virtual Acad::ErrorStatus dwgInFields( AcDbDwgFiler* filer );
    virtual Acad::ErrorStatus dwgOutFields( AcDbDwgFiler* filer ) const;

    virtual Acad::ErrorStatus dxfInFields( AcDbDxfFiler* filer );
    virtual Acad::ErrorStatus dxfOutFields( AcDbDxfFiler* filer ) const;

    virtual void subList() const;

    virtual Acad::ErrorStatus subTransformBy(const AcGeMatrix3d& xform);

    virtual Adesk::Boolean isPlanar() const 
    {
        assertReadEnabled();
        return Adesk::kTrue;
    }

    virtual Acad::ErrorStatus getPlane
        (AcGePlane& plane, AcDb::Planarity&  type) const 
    {
        assertReadEnabled();
        plane.set(mCenter, mNormal);
        type = AcDb::kPlanar;
        return Acad::eOk;
    }
    
    void squareCenter(AcGePoint3d& p) const;
    void setSquareCenter(const AcGePoint3d& p );

    void squareOrient(AcGeVector3d& p) const;
    void setSquareOrient(const AcGeVector3d& p );

    void squareNormal(AcGeVector3d& d) const;
    void setSquareNormal(const AcGeVector3d& d);

    void squareSideLength(double& l) const;
    void setSquareSideLength(const double l);

    void squareId(int& i) const;
    void setSquareId(const int i);

private:

    // Our square is defined by it's center, direction vector (where it
    // also gets it's size), and a normal.
    AcGePoint3d  mCenter;
    AcGeVector3d mOrient;
    AcGeVector3d mNormal;
    int mId;

};

inline void AsdkSquare::squareCenter(AcGePoint3d& p) const
    { assertReadEnabled();
        p = mCenter;} // Square center

inline void AsdkSquare::setSquareCenter( const AcGePoint3d& p ) 
    { assertWriteEnabled();
        mCenter = p; } // Square center

inline void AsdkSquare::squareOrient(AcGeVector3d& p) const
    {assertReadEnabled();
        p = mOrient;} // Square Orientation in 3dspace

inline void AsdkSquare::setSquareOrient( const AcGeVector3d& p ) 
    { assertWriteEnabled();
        mOrient = p; } // Square Orientation in 3dspace

inline void AsdkSquare::squareNormal(AcGeVector3d& d) const
    {assertReadEnabled();
        d = mNormal;} // Square Normal

inline void AsdkSquare::setSquareNormal( const AcGeVector3d& d ) 
    { assertWriteEnabled();
        mNormal = d; } // Square Normal

inline void AsdkSquare::squareSideLength(double& l) const
    {assertReadEnabled();
        l = (mOrient.length() *  SIN45) * 2.0; } // Square side length

inline void AsdkSquare::setSquareSideLength(const double l) 
    { assertWriteEnabled();
    // Calculate the new vector based on the side length.
      mOrient = mOrient.normalize();
      mOrient.x = mOrient.x * ((l / 2.0) / SIN45 );  
      mOrient.y = mOrient.y * ((l / 2.0) / SIN45 );  
      mOrient.z = mOrient.z * ((l / 2.0) / SIN45 ); }

inline void AsdkSquare::squareId(int& i) const
    {assertReadEnabled();
        i = mId; } // Square side length

inline void AsdkSquare::setSquareId(const int i) 
    { assertWriteEnabled();
    // Calculate the new vector based on the side length.
        mId = i;}
