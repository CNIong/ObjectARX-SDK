//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////


#include "dbmain.h"
#include "acgi.h"
#include "dbxutil.h"
#include "rxregsvc.h"
#include "asdkbody.h"



ACRX_DXF_DEFINE_MEMBERS (AsdkBody, AcDbEntity, 
                         AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent, 
                         0, ASDKBODY, ASDKBODYAPP);

class DwgFilerCallBack : public SaveRestoreCallback
{
public:
    DwgFilerCallBack (AcDbDwgFiler*);

    virtual void saveBytes   (const void* buffer, int requiredLength);
    virtual void restoreBytes(void*       buffer, int requiredLength);

private:
    AcDbDwgFiler *m_filer;
};


class AsdkBodyAModelerCallBack : public OutputTriangleCallback
{
public:
    AsdkBodyAModelerCallBack(AcGiWorldDraw* pCurWorldDraw) {m_pCurWorldDraw = pCurWorldDraw;}
    virtual ~AsdkBodyAModelerCallBack(){;}

    // 
    // Body::triangulate() callback function
    // 
    void outputTriangle(Edge* edges[], int numSides);
    void outputTriStrip(Edge* edgeArray[], int arrayLength,
                        bool firstTriangleIsCcw);

private:
    AcGiWorldDraw* m_pCurWorldDraw;
};


static void 
drawAllEdges(const Body& b, AcGiWorldDraw *pWorldDraw)
{
#ifndef NDEBUG
    Adesk::UInt16 currentColor = pWorldDraw->subEntityTraits().color();
    Adesk::UInt16 color = currentColor, lastColorSet = currentColor;
    const Adesk::UInt16 approxColor = 1;
    const Adesk::UInt16 bridgeColor = 2;
    const Adesk::UInt16 firstEdgeColor = 3;
    const Adesk::UInt16 secondEdgeColor = 4;
    int iEdge = 0, iFaces = b.faceCount();
#endif

    for (Face* f = b.faceList(); f != NULL; f = f->next())
    {
        if (f->edgeLoop() == NULL)
            continue;
        
        Edge* e = f->edgeLoop();
        do 
        {
            if (e->isEulerEdge()) 
            {
#ifndef NDEBUG
                if (e->isApprox())
                    color = approxColor;
                else if (iFaces == 1 && iEdge == 0)
                    color = firstEdgeColor;
                else if (iFaces == 1 && iEdge == 1)
                    color = secondEdgeColor;
                else if (e->isBridge())
                    color = bridgeColor;
                else
                    color = currentColor;

                if (color != lastColorSet)
                {
                    pWorldDraw->subEntityTraits().setColor(color);
                    lastColorSet = color;
                }
                iEdge++;
#else
                if (e->isBridge())
                    continue;
#endif
                Point3d p[2];
                p[0] = e->point();
                p[1] = e->next()->point();
                pWorldDraw->geometry().polyline(2, (AcGePoint3d*)p);
            }
        } while ((e = e->next()) != f->edgeLoop());
    }
}


////////////////////////////////////////////////////////////////////////////////
//
// Constructors and destructors 
//

AsdkBody::AsdkBody()
{

}


AsdkBody::~AsdkBody()
{
}


////////////////////////////////////////////////////////////////////////////////
//
// Pseudo constructors
//
// Each of these envelopes a Facet Modeler member function that creates
// a solid (except for createFace, which creates a body with one face).
// Each should call Body::isValid after creation, unless NDEBUG is defined.
//

void 
AsdkBody::createBox(const AcGePoint3d& p, const AcGeVector3d& vec)
{
	assertWriteEnabled();
    m_3dGeom = Body::box(*(Point3d*)&p, *(Vector3d*)&vec);
    if (debugMode())
        if (! m_3dGeom.isValid())
            throw eFail;
}


void 
AsdkBody::createSphere(const AcGePoint3d& p, double radius, int approx)
{
	assertWriteEnabled();
    m_3dGeom = Body::sphere( *(Point3d*)&p, radius, approx);
    if (debugMode())
	    if (! m_3dGeom.isValid())
            throw eFail;
}


void 
AsdkBody::createCylinder(const AcGePoint3d& axisStart, const AcGePoint3d& axisEnd, 
    const AcGeVector3d& baseNormal, double radius, int approx)
{
	assertWriteEnabled();
    m_3dGeom = Body::cylinder(
        Line3d(*(Point3d*)&axisStart, *(Point3d*)&axisEnd), 
        *(Vector3d*)&baseNormal, 
        radius, 
        approx);
    if (debugMode())
	    if (! m_3dGeom.isValid())
            throw eFail;
}


void 
AsdkBody::createCone(const AcGePoint3d& axisStart, const AcGePoint3d& axisEnd, 
    const AcGeVector3d& baseNormal, double radius1, double radius2, int approx)
{
	assertWriteEnabled();
    m_3dGeom = Body::cone(
        Line3d(*(Point3d*)&axisStart, *(Point3d*)&axisEnd), 
        *(Vector3d*)&baseNormal, 
        radius1, 
        radius2,
        approx);
    if (debugMode())
	    if (! m_3dGeom.isValid())
            throw eFail;
}


void 
AsdkBody::createPipe(const AcGePoint3d& axisStart, const AcGePoint3d& axisEnd, 
    const AcGeVector3d& baseNormal, double dblOuterRadius, double dblInnerRadius, 
    int approx)
{
	assertWriteEnabled();
	m_3dGeom = Body::pipe(
        Line3d(*(Point3d*)&axisStart, *(Point3d*)&axisEnd),
        *(Vector3d*)&baseNormal,
        dblOuterRadius, 
        dblInnerRadius, 
        approx);
    if (debugMode())
	    if (! m_3dGeom.isValid())
            throw eFail;
}


void 
AsdkBody::createPipeConic(
    const AcGePoint3d& axisStart, 
    const AcGePoint3d& axisEnd,
    const AcGeVector3d& baseNormal,
    double outerRadius1, 
    double innerRadius1, 
    double outerRadius2, 
    double innerRadius2,
    int approx)
{
	assertWriteEnabled();
	m_3dGeom = Body::pipeConic(
        Line3d(*(Point3d*)&axisStart, *(Point3d*)&axisEnd),
        *(Vector3d*)&baseNormal,
	    outerRadius1, 
        innerRadius1, 
        outerRadius2, 
        innerRadius2, 
        approx);
    if (debugMode())
	    if (! m_3dGeom.isValid())
            throw eFail;
}


void 
AsdkBody::createTetrahedron(const AcGePoint3d& p1, const AcGePoint3d& p2,
    const AcGePoint3d& p3, const AcGePoint3d& p4)
{
	assertWriteEnabled();
    m_3dGeom = Body::tetrahedron(*(Point3d*)&p1, *(Point3d*)&p2,
	    *(Point3d*)&p3, *(Point3d*)&p4);
    if (debugMode())
	    if (! m_3dGeom.isValid())
            throw eFail;
}


void 
AsdkBody::createTorus(const AcGePoint3d& axisStart, const AcGePoint3d& axisEnd,
    double majorRadius, double minorRadius, int majorApprox, int minorApprox)
{
	assertWriteEnabled();
    m_3dGeom = Body::torus(
        Line3d(*(Point3d*)&axisStart, *(Point3d*)&axisEnd),
        majorRadius, 
        minorRadius, 
        majorApprox, 
        minorApprox);

    if (debugMode())
	    if (! m_3dGeom.isValid())
            throw eFail;
}

                                                                                    
void 
AsdkBody::createReducingElbow(
    const AcGePoint3d& elbowCenter, 
    const AcGePoint3d& endCenter1,
    const AcGePoint3d& endCenter2, 
    double endRadius1, 
    double endRadius2,
    int majorApprox,
    int minorApprox)
{
    assertWriteEnabled();                                                   
	m_3dGeom = Body::reducingElbow(*(Point3d*)&elbowCenter, *(Point3d*)&endCenter1, 
        *(Point3d*)&endCenter2, endRadius1, endRadius2, majorApprox, minorApprox);
    if (debugMode())
	    if (! m_3dGeom.isValid())
            throw eFail;
}


void 
AsdkBody::createRectToCircleReducer(
    const AcGePoint3d& baseCorner, 
    const AcGeVector2d& baseSizes,
	const AcGePoint3d& circleCenter, 
    const AcGeVector3d& circleNormal, 
    double circleRadius,
    int approx)
{
	assertWriteEnabled();
	m_3dGeom = 
    Body::rectangleToCircleReducer(
        *(Point3d*)&baseCorner, 
        *(Vector2d*)&baseSizes,
		Circle3d(
            Line3d(
                *(Point3d*)&circleCenter, 
                *(Vector3d*)&circleNormal), 
            circleRadius), 
        approx);
    if (debugMode())
	    if (! m_3dGeom.isValid())
            throw eFail;
}


void 
AsdkBody::createConvexHull(const AcGePoint3d vertices[], int numVertices)
{
	assertWriteEnabled();
	m_3dGeom = Body::convexHull((Point3d*)vertices, numVertices);
    if (debugMode())
	    if (! m_3dGeom.isValid())
            throw eFail;
}


void 
AsdkBody::createFace(const AcGePoint3d vertices[], PolygonVertexData* vertexData[], 
    int numVertices, const AcGeVector3d &normal)
{
	assertWriteEnabled();
    Face* pFace = new Face((Point3d*)vertices, vertexData, numVertices, 
        *(Vector3d*)&normal, 0, TRUE, &m_3dGeom);
                                                                                 
    // I would call m_3dGeom.isValid, but it only works for solids, i.e., 
    // at least three faces -vm
}


void 
AsdkBody::createFace(const AcGePoint3d vertices[], int numVertices)
{
	assertWriteEnabled();
    Face* pFace = new Face((Point3d*)vertices, numVertices, 0, TRUE, &m_3dGeom);
                                                                                 
    // I would call m_3dGeom.isValid, but it only works for solids, i.e., 
    // at least three faces -vm
}


void 
AsdkBody::createPyramid(
    const AcGePoint3d vertices[], 
    PolygonVertexData *vertexData[],
    int numVertices, 
    const AcGeVector3d &plgNormal, 
    const AcGePoint3d &apex)
{
	assertWriteEnabled();
	m_3dGeom = Body::pyramid((Point3d*)vertices, vertexData, numVertices, 
        *(Vector3d*)&plgNormal, *(Point3d*)&apex);
    if (debugMode())
	    if (! m_3dGeom.isValid())
            throw eFail;
}


void 
AsdkBody::createExtrusion(
    const AcGePoint3d vertices[], 
    PolygonVertexData* vertexData[],
	int numVertices, 
    const AcGeVector3d &plgNormal, 
    const AcGeVector3d &extrusionVector, 
    const AcGePoint3d &fixedPt,
	double scaleFactor, 
    double twistAngle)
{
	assertWriteEnabled();
	m_3dGeom = Body::extrusion((Point3d*)vertices, vertexData, numVertices, 
        *(Vector3d*)&plgNormal, *(Vector3d*)&extrusionVector, *(Point3d*)&fixedPt, 
        scaleFactor, twistAngle * (kPi/180));
    if (debugMode())
	    if (! m_3dGeom.isValid())
            throw eFail;
}

void
AsdkBody::createAxisRevolution(
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
    double twistAngle)
{
	assertWriteEnabled();
    m_3dGeom = Body::axisRevolution(
        (Point3d*)vertices,
        vertexData,
        numVertices,
        *(Vector3d*)&normal,
        Line3d(axisStart, axisEnd),
        revolutionAngle * (kPi/180),
        approx,
        *(Point3d*)&fixedPt,
        scaleFactor,
        twistAngle * (kPi/180));
    if (debugMode())
	    if (! m_3dGeom.isValid())
            throw eFail;
}


void
AsdkBody::createEndpointRevolution(
    const AcGePoint3d vertices[],
    PolygonVertexData* vertexData[],
    int numVertices,
    const AcGeVector3d &normal,
    double revolutionAngle,
    int approx)
{
	assertWriteEnabled();
    m_3dGeom = Body::endpointRevolution(
        (Point3d*)vertices,
        vertexData,
        numVertices,
        *(Vector3d*)&normal,
        revolutionAngle * (kPi/180),
        approx);
    if (debugMode())
	    if (! m_3dGeom.isValid())
            throw eFail;
}


void
AsdkBody::createSkin(
    AsdkBody* profiles[],
    int numProfiles,
    bool isClosed,
    MorphingMap* morphingMaps[])
{
	assertWriteEnabled();
    bool checkPlanarity = debugMode() ? TRUE : FALSE;
    Body **profileBodies = new Body*[numProfiles];
    
    for (int i = 0; i < numProfiles; i++)
        profileBodies[i] = &(profiles[i]->body());

    m_3dGeom = Body::skin(
        profileBodies,
        numProfiles,
        isClosed,
        checkPlanarity,
        morphingMaps);
    if (debugMode())
	    if (! m_3dGeom.isValid())
            throw eFail;
}
        

void 
AsdkBody::createExtrusionAlongPath(
    const Body &startProfile, 
    const Body &endProfile,
	const AcGePoint3d vertices[], 
    PolygonVertexData* vertexData[], 
    int numVertices, 
    bool pathIsClosed,
    bool bCheckValidity,
    const AcGePoint3d &scaleTwistFixedPt,
    double scaleFactor, 
    double twistAngle, 
    const MorphingMap &morphingMap)
{
	assertWriteEnabled();
	m_3dGeom = Body::extrusionAlongPath(
        startProfile, 
        endProfile, 
        (Point3d*)vertices, 
        vertexData, 
        numVertices, 
        pathIsClosed, 
        bCheckValidity, 
        *(Point3d*)&scaleTwistFixedPt, 
        scaleFactor, 
        twistAngle * (kPi/180), 
        morphingMap);
    if (debugMode())
    {
        m_3dGeom.mergeCoplanarEntities();
	    if (! m_3dGeom.isValid())
            throw eFail;
    }
}


Body& 
AsdkBody::body()
{
    assertWriteEnabled();
    return m_3dGeom;
}

const Body& 
AsdkBody::body() const
{
    assertReadEnabled();
    return m_3dGeom;
}

////////////////////////////////////////////////////////////////////////////////
//
// ARX related member functions
//


Adesk::Boolean 
AsdkBody::subWorldDraw(AcGiWorldDraw* worldDraw)
{
    assertReadEnabled();

    if (worldDraw->regenAbort()) {
        return Adesk::kTrue;
    }

    // 
    // Evaluate the graphics
    // 
    //graphRep.evaluateWorldDraw(body, worldDraw, defaultColor);

    switch (worldDraw->regenType()) {

    case kAcGiHideOrShadeCommand:
    case kAcGiShadedDisplay:
        
        // 
        // Draw shells
        // 
        {
        AsdkBodyAModelerCallBack AModelerCallBack( worldDraw );
        m_3dGeom.triangulate( &AModelerCallBack );
        }

        break;

    case kAcGiStandardDisplay:
    case kAcGiSaveWorldDrawForR12:

        // 
        // Draw wireframe with visible hidden lines
        // 
        drawAllEdges( m_3dGeom, worldDraw );

        break;

    default:
        // 
        // Unknown regenType
        // 
        //ASSERT(0);
        break;
    } /*switch*/
    
    return Adesk::kTrue;   // Don't call viewportDraw().
}


Acad::ErrorStatus
AsdkBody::dwgInFields(AcDbDwgFiler* filer)
{
    assertWriteEnabled();
    Acad::ErrorStatus es;

    if ((es = AcDbEntity::dwgInFields(filer)) != Acad::eOk)
        return es;

    switch (filer->filerType()) 
    {
    case AcDb::kCopyFiler:    
    case AcDb::kDeepCloneFiler:
    case AcDb::kWblockCloneFiler:
        {
        void *i, *j;
        
        filer->readAddress(&i);
        filer->readAddress(&j);
        
        AcDbStub*   stub = (AcDbStub*)i;
        AcDbEntity* ent  = (AsdkBody*)j;
        
        if (NULL != stub) 
            acdbOpenAcDbEntity(ent, AcDbObjectId(stub), AcDb::kForRead, Adesk::kTrue);
        m_3dGeom = ((AsdkBody*)ent)->m_3dGeom.copy();
        if (NULL != stub)
            ent->close();
        }
        break;
        
    case AcDb::kFileFiler:     
    case AcDb::kUndoFiler:
    case AcDb::kPageFiler:

        m_3dGeom = Body::restore( &DwgFilerCallBack( filer ) );
        break;
        
    default:
        break;
    }
    return filer->filerStatus();
}


Acad::ErrorStatus
AsdkBody::dwgOutFields(AcDbDwgFiler* filer) const
{
    assertReadEnabled();
    Acad::ErrorStatus es;

    if ((es = AcDbEntity::dwgOutFields(filer)) != Acad::eOk)
        return es;

    switch (filer->filerType()) 
    {
    case AcDb::kCopyFiler:     
    case AcDb::kDeepCloneFiler:
    case AcDb::kWblockCloneFiler:
        
        filer->writeAddress( objectId() );
        filer->writeAddress( this );
        break;
        
    case AcDb::kFileFiler:     
    case AcDb::kUndoFiler:
    case AcDb::kPageFiler:
        
        m_3dGeom.save( &DwgFilerCallBack( filer ) );
        break;
        
    default:
        break;
    }
    return filer->filerStatus();
}


Acad::ErrorStatus 
AsdkBody::subTransformBy(const AcGeMatrix3d& xform)
{
    AcDbDwgFiler *filer;

    assertWriteEnabled( Adesk::kFalse );
    if (NULL != (filer = undoFiler()))
    {
        filer->writeAddress(AsdkBody::desc() );
        filer->writeItem( (Adesk::Int16)555 );

        //filer->writeBytes( &xform, sizeof AcGeMatrix3d );
        
        AcGePoint3d  o;
        AcGeVector3d x, y, z;
        xform.getCoordSystem( o, x, y, z );
        filer->writeItem( o );
        filer->writeItem( x );
        filer->writeItem( y );
        filer->writeItem( z );
    }

    m_3dGeom.transform( *(Transf3d*)&xform );
    return Acad::eOk;
}


Acad::ErrorStatus 
AsdkBody::applyPartialUndo(AcDbDwgFiler* filer, AcRxClass* classObj)
{
    if (AsdkBody::desc() != classObj)
        return AcDbEntity::applyPartialUndo( filer, classObj );

    Adesk::Int16 opCode;
    filer->readItem( &opCode );

    switch (opCode) 
    {
    case 555:  // It is a transformBy() operation
        {
        // filer->readBytes( &mat, sizeof AcGeMatrix3d );

        AcGeMatrix3d mat;
        AcGeVector3d x, y, z;
        AcGePoint3d  o;
    
        filer->readItem( &o );
        filer->readItem( &x );
        filer->readItem( &y );
        filer->readItem( &z );
    
        mat.setCoordSystem( o, x, y, z );
        mat.invert();
        transformBy( mat );
        }
        break;
    default:
        break;
    }
    return Acad::eOk;
}


void 
AsdkBodyAModelerCallBack::outputTriangle(Edge* edges[], int numSides)
{
    if (!m_pCurWorldDraw)
        return;

    // 
    // assume, the numSide must be < 5
    // 
    if (numSides < 3 || numSides > 4)   
        return;

    AcGePoint3d points[4];
    Adesk::UInt32 face_list_size = 1 + numSides;
    Adesk::Int32* face_list = new Adesk::Int32[face_list_size];
    AcGiEdgeData edge_data;
    Adesk::UInt8* edge_vis_array = new Adesk::UInt8[numSides];
    face_list[0] = numSides;
    for (int i = 0; i < numSides; i++)
    {
        points[i] = AcGePoint3d(edges[i]->point().x, 
            edges[i]->point().y, edges[i]->point().z);
                                                                                
        face_list[i+1] = i;
        if (edges[i]->next() != edges[(i+1)%numSides] 
            || edges[i]->isFlagOn(BEF)) 
        {
            // 
            // triangle edge 
            // 
            edge_vis_array[i] = kAcGiInvisible;
        }
        else if (edges[i]->isFlagOn(AEF))
        {
            edge_vis_array[i] = kAcGiSilhouette;
        }
        else
        {
            edge_vis_array[i] = kAcGiVisible;
        }
    }
    edge_data.setVisibility(edge_vis_array);

    // 
    // set color
    // Need to figure out wall side to assign correct color
    // 
    m_pCurWorldDraw->geometry().shell(numSides, points, face_list_size, 
        face_list, &edge_data);

    delete [] face_list;
    delete [] edge_vis_array;
}


void 
AsdkBodyAModelerCallBack::outputTriStrip(Edge* /*edgeArray*/[], 
    int /*arrayLength*/, bool /* firstTriangleIsCcw */)
{
    assert(0);
}


DwgFilerCallBack::DwgFilerCallBack( AcDbDwgFiler *f ) : m_filer( f )
{
}


void 
DwgFilerCallBack::saveBytes( const void* buffer, int requiredLength )
{
    m_filer->writeBytes( buffer, requiredLength );
}


void 
DwgFilerCallBack::restoreBytes( void* buffer, int requiredLength )
{
    m_filer->readBytes( buffer, requiredLength );
}

extern "C" AcRx::AppRetCode
acrxEntryPoint( AcRx::AppMsgCode msg, void *pkt )
{
    switch(msg)
    {
    case AcRx::kInitAppMsg:
		//intialize AsdkAmodeler
		//
        acrxLoadModule(_T("aecmodeler70.dbx"),0);
        // Try to allow unloading
        // 
        acrxUnlockApplication(pkt);
		//register as being MDI aware
		//
		acrxRegisterAppMDIAware(pkt);
		//initialize our custom class
		AsdkBody::rxInit();
		acrxBuildClassHierarchy();
        break;

    case AcRx::kUnloadAppMsg:
		deleteAcRxClass(AsdkBody::desc());
		//unload AsdkAModeler if we have been the
		//only one using it. (RX does reference counting)
		acrxUnloadModule(_T("aecmodeler70.dbx"));
        break;
    }
    return AcRx::kRetOK;
}
