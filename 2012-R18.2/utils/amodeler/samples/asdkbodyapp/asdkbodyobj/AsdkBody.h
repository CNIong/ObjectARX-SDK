#ifndef __ASDKBODY_H__
#define __ASDKBODY_H__


///////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright 1996-2007 by Autodesk, Inc.
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
///////////////////////////////////////////////////////////////////////////////

#include "amodeler.h"

using namespace AModeler;

#pragma warning(push)
#pragma warning(disable:4275)

class 
#ifdef EXPORT_ASDKBODY
_declspec(dllexport)
#else
//nothing
#endif
AsdkBody: public AcDbEntity
{
public:
    ACRX_DECLARE_MEMBERS(AsdkBody);

    ///////////////////////////////////////////////////////////////////////////
    //
    // Constructors and destructor
    //

    AsdkBody();
    virtual ~AsdkBody();

    Body& body();
	const Body& body() const;
    ///////////////////////////////////////////////////////////////////////////
    //
    // Pseudo Constructors
    //
    // Each envelopes a Facet Modeler Body class member function (and that's
    // pretty much all they do).
    //
    void createBox(const AcGePoint3d& p, const AcGeVector3d& vec);
    void createSphere(const AcGePoint3d& p, double radius, int approx);
    void createCylinder(const AcGePoint3d& axisStart, const AcGePoint3d& axisEnd, 
        const AcGeVector3d& baseNormal, double radius, int approx);
    void createCone(const AcGePoint3d& axisStart, const AcGePoint3d& axisEnd, 
        const AcGeVector3d& baseNormal, double radius1, double radius2, int approx);
    void createPipe(const AcGePoint3d& axisStart, const AcGePoint3d& axisEnd, 
        const AcGeVector3d& baseNormal,
        double dblOuterRadius, double dblInnerRadius, 
        int approx);
	void createPipeConic(const AcGePoint3d& axisStart, const AcGePoint3d& axisEnd,
        const AcGeVector3d& baseNormal,
		double outterRadius1, double innerRadius1,
		double outterRadius2, double innerRadius2, 
        int approx);
	void createTetrahedron(const AcGePoint3d& p1, const AcGePoint3d& p2,
		const AcGePoint3d& p3, const AcGePoint3d& p4);
	void createTorus(const AcGePoint3d& axisStart, const AcGePoint3d& axisEnd,
		double majorRadius, double minorRadius, int majorApprox, int minorApprox);
	void createReducingElbow(const AcGePoint3d& elbowCenter, const AcGePoint3d& endCenter1,
        const AcGePoint3d& endCenter2, double endRadius1, double endRadius2,
        int majorApprox, int minorApprox);
	void createRectToCircleReducer(
        const AcGePoint3d& baseCorner,
        const AcGeVector2d& baseSizes, 
        const AcGePoint3d& circleCenter,
        const AcGeVector3d& circleNormal, 
        double circleRadius, 
        int approx);
    void createConvexHull(const AcGePoint3d vertices[], int numVertices);

    // Create a body consisting of one face
    //
    void createFace(const AcGePoint3d vertices[], PolygonVertexData* vertexData[], 
        int numVertices, const AcGeVector3d &normal);
    void createFace(const AcGePoint3d vertices[], int numVertices);

    // Sweeps
    //
	void createPyramid(
        const AcGePoint3d vertices[], 
        PolygonVertexData* vertexData[],
	    int numVertices, 
        const AcGeVector3d &plgNormal, 
        const AcGePoint3d &apex);

	void createExtrusion(
        const AcGePoint3d vertices[], 
        PolygonVertexData* vertexData[],
		int numVertices, 
        const AcGeVector3d &plgNormal, 
        const AcGeVector3d &extusionVector, 
        const AcGePoint3d &fixedPt, 
        double scaleFactor, 
        double twistAngle);

    void createAxisRevolution(
        const AcGePoint3d vertices[],
        PolygonVertexData* vertexData[],
        int numVertices,
        const AcGeVector3d &normal,
        const AcGePoint3d &axisStart,
        const AcGePoint3d &axisEnd,
        double revolutionAngle,
        int approx,
        const AcGePoint3d &fixedPt,
        double scaleFactor,
        double twistAngle);

    void createEndpointRevolution(
        const AcGePoint3d vertices[],
        PolygonVertexData* vertexData[],
        int numVertices,
        const AcGeVector3d &normal,
        double revolutionAngle,
        int approx);

    void createSkin(
        AsdkBody* profiles[],
        int numProfiles,
        bool isClosed,
        MorphingMap* morphingMaps[]);

	void createExtrusionAlongPath(
        const Body &startProfile, 
        const Body &endProfile,
		const AcGePoint3d vertices[], 
        PolygonVertexData* vertexData[], 
        int numVerticesm, 
        bool pathIsClosed, 
        bool bCheckValidity,
        const AcGePoint3d &scaleTwistFixedPt, 
        double scaleFactor, 
        double twistAngle, 
        const MorphingMap &morphingMap);

    virtual Adesk::Boolean saveImagesByDefault() const;

    virtual Adesk::Boolean debugMode() const;
    //
    // debugMode is used for two thing: 1) if true, Body::isValid() is called
    // in all pseudo constructors on the new solid.  Also, checkValidity and
    // checkPlanarity arguments turned on.

    ///////////////////////////////////////////////////////////////////////////
    // 
    // Persist
    // 
    virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* filer);
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* filer) const;

    virtual Acad::ErrorStatus subTransformBy(const AcGeMatrix3d& xform);

    virtual Acad::ErrorStatus applyPartialUndo(AcDbDwgFiler* undoFiler, AcRxClass* classObj);

protected:
    ///////////////////////////////////////////////////////////////////////////
    // 
    // display
    // 
    virtual Adesk::Boolean subWorldDraw(AcGiWorldDraw* mode);
private:
	// These are here because otherwise dllexport tries to export the
    // private methods of AcDbObject.  They're private in AcDbObject
    // because vc5 and vc6 do not properly support array new and delete.
    // The "vector deleting dtor" gets optimized into a scalar deleting
    // dtor by the linker if the server dll does not call vector delete.
    // The linker shouldn't do that, because it doesn't know that the
    // object won't be passed to some other dll which *does* do vector
    // delete.
    //
    void *operator new[](size_t nSize) { return 0;}
    void operator delete[](void *p) {};
    void *operator new[](size_t nSize, const char *file, int line) { return 0;}

    Body m_3dGeom;
};

MAKE_ACDBOPENOBJECT_FUNCTION( AsdkBody );

inline Adesk::Boolean
AsdkBody::saveImagesByDefault() const
{  return Adesk::kFalse;  }


inline Adesk::Boolean
AsdkBody::debugMode() const
{
#ifndef NDEBUG
    return Adesk::kTrue;
#else
    return Adesk::kFalse;
#endif
}
#pragma warning(pop)
#endif
