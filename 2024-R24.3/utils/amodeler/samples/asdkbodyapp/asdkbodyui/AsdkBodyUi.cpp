//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////


#if defined(_DEBUG) && !defined(_FULLDEBUG_)
#define _DEBUG_WAS_DEFINED
#pragma message ("       Compiling MFC /STL /ATL header files in release mode.")
#undef _DEBUG
#endif

#include <Windows.h>
#include "dbmain.h"
#include "accmd.h"
#include "rxregsvc.h"                   // For acrxRegisterService 
#include "adslib.h"
#include "actrans.h"
#include "assert.h"
#include "dbsymtb.h"
#include "dbents.h"
#include "dbpl.h"
#include "geassign.h"


#include "AsdkBodyUi.h"
#include "..\AsdkBodyObj\Asdkbody.h"
#include "errormsg.h"
#include "dbxutil.h"
#include "string.h"
#include "tchar.h"
#include "acedCmdNF.h"

#ifdef _DEBUG_WAS_DEFINED
#define _DEBUG
#undef _DEBUG_WAS_DEFINED
#endif

// 
// Function prototypes
// 
void printHelp();
void createBox();
void createSphere();
void createCylinder();
void createCone();
void createPipe();
void createPipeConic();
void createTetrahedron();
void createTorus();
void createReducingElbow();
void createRectToCircleReducer();
void createConvexHull();
void createFace();
void createPyramid();
void createExtrusion();
void createAxisRevolution();
void createExtrusionAlongPath();
void aUnion();
void aSubtract();
void aIntersect();
void doArray();

//
// Static function prototypes
//
static AcDbEntity* selectEntity(AcDb::OpenMode openMode);
static bool getYesNo(bool defaultIsYes = TRUE);
static void cleanupEntity(AcDbEntity *pEnt);
static void handleADSError(int adsrc);
static AsdkBody* getFace();
static AsdkBody* getExistingFace();
static AsdkBody* getNewFace(ACHAR* kw);
static void getVertices(AcGePoint3d* &vertices, int &iVertices, int iMaxVertices = 64);
static void getFilletVertexData(const int iVertices, PolygonVertexData** &vertexData);
static AcDb2dPolyline* getPolyline();
static AcGeVector3d getVector();
static void getTwoPoints(AcGePoint3d& p1, AcGePoint3d &p2);
static AcGePoint3d getPoint(ACHAR* prompt = ACRX_T(""));
static double getDistance(AcGePoint3d fromPt, ACHAR *prompt = ACRX_T(""), double defaultDist = 0.0);
static int getInt(ACHAR *prompt = ACRX_T(""), int defaultValue = 0);
static double getReal(ACHAR *prompt = ACRX_T(""), double defaultValue = 0.0);
static void getPolylineVertices(AcGePoint3d* &vertices, 
    PolygonVertexData** &vertexData, int &iVertices, AcGeVector3d &normal);
static void getPath(AcGePoint3d* &vertices, PolygonVertexData** &vertexData, 
    int &iVertices);
static MorphingMap getMorphingMap(const Body& startProfile, const Body& endProfile);
static MorphingMap* queryMorphingMap(AsdkBody* pBody1, AsdkBody* pBody2);



// -------------------------------------------------
// -------------------------------------------------
//    Initialization
// -------------------------------------------------
// -------------------------------------------------
//  This data structure holds info about commands to be
//  registered and to be listed by the ifcHelp command
//
CommandInfo commandInfo[] =
{
    // 
    // commands
    // 
    ACRX_T("AHELP"),                &printHelp,                 ACRX_T("Display this command table"),
    ACRX_T("ABOX"),                 &createBox,                 ACRX_T("Create a Box"), 
    ACRX_T("ASPHERE"),              &createSphere,              ACRX_T("Create a Sphere"), 
    ACRX_T("ACYLINDER"),            &createCylinder,            ACRX_T("Create a Cylinder"),
    ACRX_T("ACONE"),                &createCone,                ACRX_T("Create a Cone"),
    ACRX_T("APIPE"),		        &createPipe,                ACRX_T("Create a Pipe"),
	ACRX_T("APIPECONIC"),           &createPipeConic,           ACRX_T("Create a Pipe Conic"),
	ACRX_T("ATETRAHEDRON"),         &createTetrahedron,         ACRX_T("Create a Tetrahedron"),
	ACRX_T("ATORUS"),               &createTorus,               ACRX_T("Create a Torus"),
	ACRX_T("AREDUCINGELBOW"),       &createReducingElbow,       ACRX_T("Create a Reducing Elbow"),
	ACRX_T("ARECTTOCIRCLEREDUCER"), &createRectToCircleReducer, ACRX_T("Create a Circle Reducer"),
	ACRX_T("ACONVEXHULL"),          &createConvexHull,          ACRX_T("Create a Convex Hull"),
    ACRX_T("AFACE"),		        &createFace,	            ACRX_T("Create a Face"),
	ACRX_T("APYRAMID"),             &createPyramid,             ACRX_T("Create a Pyramid"),
	ACRX_T("AEXTRUDE"),             &createExtrusion,           ACRX_T("Sweep along a straight line"),
    ACRX_T("AAXISREVOLVE"),         &createAxisRevolution,      ACRX_T("Sweep around an axis"),
    ACRX_T("APATHEXTRUDE"),         &createExtrusionAlongPath,  ACRX_T("Sweep along a path"),
    ACRX_T("AUNION"),               &aUnion,                    ACRX_T("Unite Two AsdkBodys"), 
    ACRX_T("ASUBTRACT"),            &aSubtract,                 ACRX_T("Subtract Two AsdkBodys"),
    ACRX_T("AINTERSECT"),           &aIntersect,                ACRX_T("Intersects AsdkBodys"),
    ACRX_T("DOARRAY"),              &doArray,                   ACRX_T("Do an Array operation"),
    0,                      0,                          0
};

//utility function that appends an entity to the model space
Adesk::Boolean append( AcDbEntity* pEnt )
{
    AcDbBlockTable *pBt;
	AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase();
    if (Acad::eOk != pDb->getBlockTable( pBt, AcDb::kForRead ))
        return Adesk::kFalse;

    AcDbBlockTableRecord *pMs;
    Acad::ErrorStatus es = pBt->getAt( ACDB_MODEL_SPACE, pMs,
        AcDb::kForWrite );
    pBt->close();
    if (Acad::eOk != es)
        return Adesk::kFalse;
    es = pMs->appendAcDbEntity( pEnt );
    pMs->close();
    return Acad::eOk == es;
}


const ACHAR* gstrCmdGrpName = ACRX_T("ASDKBODYUI_COMMANDS");

extern "C" AcRx::AppRetCode
acrxEntryPoint( AcRx::AppMsgCode msg, void *pkt )
{

    switch(msg)
    {
    case AcRx::kInitAppMsg:
		{
		//Initialize the server app
        acrxLoadModule(ACRX_T("AsdkBodyObj.dbx"),1);
		for (CommandInfo * pInfo = commandInfo;  pInfo->commandName != NULL; pInfo++)
		{
			if (acedRegCmds->addCommand(gstrCmdGrpName, pInfo->commandName,
				pInfo->commandName, ACRX_CMD_MODAL, pInfo->fn ) 
				!= Acad::eOk )
			{
				ads_printf ( ACRX_T("There was a problem with addCommand().") );
				break;
			}
		}
        // 
        // Try to allow unloading
        // 
        acrxUnlockApplication(pkt);
		//register as being MDI aware
		acrxRegisterAppMDIAware(pkt);
        printHelp();
        break;
		}
    case AcRx::kUnloadAppMsg:
        // 
		// Clean up the commands that were registered with the editor.
		//
		acedRegCmds->removeGroup ( gstrCmdGrpName );
		acrxUnloadModule(ACRX_T("AsdkBodyObj.dbx"));
        break;
    }

    return AcRx::kRetOK;
}


//
//  ArxAppHelp()
//
//  Print out the short descriptions of all application commands.
//
void 
printHelp()
{
    ads_printf(ACRX_T("\n\n%-20s%s\n"), ACRX_T("Commands"), ACRX_T("Descriptions"));
    ads_printf(ACRX_T("--------------------------------------------------------\n"));

    for (CommandInfo * pInfo = commandInfo; pInfo->commandName != NULL;  pInfo++)
        ads_printf ( ACRX_T("%-20s%s\n"), pInfo->commandName, pInfo->desc );
}



////////////////////////////////////////////////////////////////////////////////
//
// AsdkBody primitve creation functions
//


void 
createBox()
{
    AsdkBody *pBody = NULL;

    try
    {
        AcGePoint3d corner1 = getPoint(ACRX_T("\nCorner of box: "));
        AcGePoint3d corner2 = getPoint(ACRX_T("\nOther corner: "));
        ads_printf( ACRX_T("\n") );
    
        pBody = new AsdkBody;

        AcGeVector3d vec = corner2 - corner1;
        if (vec[X] == 0.0)
            vec[X] = getDistance(corner2, ACRX_T("\nWidth: "));
        if (vec[Y] == 0.0)
            vec[Y] = getDistance(corner2, ACRX_T("\nDepth: "));
        if (vec[Z] == 0.0)
            vec[Z] = getDistance(corner2, ACRX_T("\nHeight: "));

        pBody->createBox(corner1, vec);
    }
    catch (int caught_adsrc)
    //
    // User probably cancelled.  Clean up and bail out.
    {
        handleADSError(caught_adsrc);
        return;
    }
    catch (ErrorCode err) 
    {
        if (err == eFail)
        {
            ads_printf( ACRX_T("\nBody is not valid.  Continue?"));
            if(! getYesNo())
            {
                delete pBody;
                return;
            }
        }
        else
        {
            ads_printf( ACRX_T("\nERROR: %s\n"), getErrorMsg(err));
            delete pBody;
            return;
        }
    }
    if (append( pBody ))
        pBody->close();
    else {
        delete pBody;
        ads_printf( ACRX_T("\nCould not add AsdkBody to ACAD Database.  *Bailing out*\n") );
    }
}


void 
createSphere()
{
    AsdkBody *pBody = NULL;

    try
    {
        AcGePoint3d center = getPoint(ACRX_T("\nCenter of sphere: "));
        double dist = getDistance(center, ACRX_T("\nRadius of sphere: "));
        int approx = getInt(ACRX_T("\nEnter # of lines to approximate a circle <32>:"), 32);
    
        pBody = new AsdkBody;
    
        pBody->createSphere(center, dist, approx);
    }
    catch (int caught_adsrc)
    //
    // User probably cancelled.  Clean up and bail out.
    {
        handleADSError(caught_adsrc);
        return;
    }
    catch (ErrorCode err) 
    {
        if (err == eFail)
        {
            ads_printf( ACRX_T("\nBody is not valid.  Continue?"));
            if(! getYesNo())
            {
                delete pBody;
                return;
            }
        }
        else
        {
            ads_printf( ACRX_T("\nERROR: %s\n"), getErrorMsg(err));
            delete pBody;
            return;
        }
    }

    if (append( pBody ))
        pBody->close();
    else {
        delete pBody;
        ads_printf( ACRX_T("\nCould not add AsdkBody to ACAD Database.  *Bailing out*\n") );
    }
}


void 
createCylinder()
{
    AsdkBody *pBody = NULL;

    try
    {
        AcGePoint3d axisStart, axisEnd;
        ads_printf(ACRX_T("\nCylinder axis: "));
        getTwoPoints(axisStart, axisEnd);

        AcGeVector3d baseNormal;
        try
        {
            baseNormal = getPoint(ACRX_T("\nBase normal vector <None>:")) - axisStart;
        }
        catch (int caught_adsrc)
        {
            if (caught_adsrc == RTNONE)
                baseNormal = AcGeVector3d(0, 0, 0);
            else
                throw caught_adsrc;
        }
        double radius = getDistance(axisStart, ACRX_T("\nRadius: "));
        int approx = getInt(ACRX_T("\nEnter # of lines to approximate a circle <32>:"), 32);

        pBody = new AsdkBody;
    
        pBody->createCylinder(axisStart, axisEnd, baseNormal, radius, approx);
    }
    catch (int caught_adsrc)
    //
    // User probably cancelled.  Clean up and bail out.
    {
        handleADSError(caught_adsrc);
        return;
    }
    catch (ErrorCode err) 
    {
        if (err == eFail)
        {
            ads_printf( ACRX_T("\nBody is not valid.  Continue?"));
            if(! getYesNo())
            {
                delete pBody;
                return;
            }
        }
        else
        {
            ads_printf( ACRX_T("\nERROR: %s\n"), getErrorMsg(err));
            delete pBody;
            return;
        }
    }

    if (append( pBody ))
        pBody->close();
    else {
        delete pBody;
        ads_printf( ACRX_T("\nCould not add AsdkBody to ACAD Database.  *Bailing out*\n") );
    }
}


void 
createCone()
{
    AsdkBody *pBody = NULL;

    try
    {
        AcGePoint3d axisStart, axisEnd;
        ads_printf(ACRX_T("\nCone axis: "));
        getTwoPoints(axisStart, axisEnd);

        AcGeVector3d baseNormal;
        try
        {
            baseNormal = getPoint(ACRX_T("\nBase normal vector <None>: ")) - axisStart;
        }
        catch (int caught_adsrc)
        {
            if (caught_adsrc == RTNONE)
                baseNormal = AcGeVector3d(0, 0, 0);
            else
                throw caught_adsrc;
        }
        double radius1 = getDistance(axisStart, ACRX_T("\nStart radius: "));
        double radius2 = getDistance(axisEnd, ACRX_T("\nEnd radius: "));
        int approx = getInt(ACRX_T("\nEnter # of lines to approximate a circle <32>:"), 32);

        pBody = new AsdkBody;
    
        pBody->createCone(axisStart, axisEnd, baseNormal, 
            radius1, radius2, approx);
    }
    catch (int caught_adsrc)
    //
    // User probably cancelled.  Clean up and bail out.
    {
        handleADSError(caught_adsrc);
        return;
    }
    catch (ErrorCode err) 
    {
        if (err == eFail)
        {
            ads_printf( ACRX_T("\nBody is not valid.  Continue?"));
            if(! getYesNo())
            {
                delete pBody;
                return;
            }
        }
        else
        {
            ads_printf( ACRX_T("\nERROR: %s\n"), getErrorMsg(err));
            delete pBody;
            return;
        }
    }

    if (append( pBody ))
        pBody->close();
    else {
        delete pBody;
        ads_printf( ACRX_T("\nCould not add AsdkBody to ACAD Database.  *Bailing out*\n") );
    }
}


void 
createPipe()
{
    AsdkBody *pBody = NULL;

    try
    {
        AcGePoint3d axisStart, axisEnd;
        ads_printf(ACRX_T("\nPipe axis: "));
        getTwoPoints(axisStart, axisEnd);

        AcGeVector3d baseNormal;
        try
        {
            baseNormal = getPoint(ACRX_T("\nBase normal vector <None>:")) - axisStart;
        }
        catch (int caught_adsrc)
        {
            if (caught_adsrc == RTNONE)
                baseNormal = AcGeVector3d(0, 0, 0);
            else
                throw caught_adsrc;
        }
        double outerRadius = getDistance(axisStart, ACRX_T("\nOuter radius: "));
        double innerRadius = getDistance(axisStart, ACRX_T("\nInner radius: "));
        int approx = getInt(ACRX_T("\nEnter # of lines to approximate a circle <32>:"), 32);
    
        pBody = new AsdkBody;
    
        pBody->createPipe(axisStart, axisEnd, baseNormal, 
            outerRadius, innerRadius, approx);
    }
    catch (int caught_adsrc)
    //
    // User probably cancelled.  Clean up and bail out.
    {
        handleADSError(caught_adsrc);
        return;
    }
    catch (ErrorCode err) 
    {
        if (err == eFail)
        {
            ads_printf( ACRX_T("\nBody is not valid.  Continue?"));
            if(! getYesNo())
            {
                delete pBody;
                return;
            }
        }
        else
        {
            ads_printf( ACRX_T("\nERROR: %s\n"), getErrorMsg(err));
            delete pBody;
            return;
        }
    }

    if (append( pBody ))
        pBody->close();
    else {
        delete pBody;
        ads_printf( ACRX_T("\nCould not add AsdkBody to ACAD Database.  *Bailing out*\n") );
    }
}


void 
createPipeConic()
{
    AsdkBody *pBody = NULL;

    try
    {
        AcGePoint3d axisStart, axisEnd;
        ads_printf(ACRX_T("\nConic pipe axis: "));
        getTwoPoints(axisStart, axisEnd);

        AcGeVector3d baseNormal;
        try
        {
            baseNormal = getPoint(ACRX_T("\nBase normal vector <None>:")) - axisStart;
        }
        catch (int caught_adsrc)
        {
            if (caught_adsrc == RTNONE)
                baseNormal = AcGeVector3d(0, 0, 0);
            else
                throw caught_adsrc;
        }
        double outerRadius1 = getDistance(axisStart, ACRX_T("\nFirst outer radius: "));
        double innerRadius1 = getDistance(axisStart, ACRX_T("\nFirst inner radius: "));
        double outerRadius2 = getDistance(axisEnd, ACRX_T("\nSecond outer radius: "));
        double innerRadius2 = getDistance(axisEnd, ACRX_T("\nSecond inner radius: "));
        int approx = getInt(ACRX_T("\nEnter # of lines to approximate a circle <32>:"), 32);
    
        pBody = new AsdkBody;
    
         pBody->createPipeConic(axisStart, axisEnd, baseNormal,
            outerRadius1, innerRadius1, outerRadius2, innerRadius2, 
            approx);
    }
    catch (int caught_adsrc)
    //
    // User probably cancelled.  Clean up and bail out.
    {
        handleADSError(caught_adsrc);
        return;
    }
    catch (ErrorCode err) 
    {
        if (err == eFail)
        {
            ads_printf( ACRX_T("\nBody is not valid.  Continue?"));
            if(! getYesNo())
            {
                delete pBody;
                return;
            }
        }
        else
        {
            ads_printf( ACRX_T("\nERROR: %s\n"), getErrorMsg(err));
            delete pBody;
            return;
        }
    }

    if (append( pBody ))
        pBody->close();
    else {
        delete pBody;
        ads_printf( ACRX_T("\nCould not add AsdkBody to ACAD Database.  *Bailing out*\n") );
    }
}


void 
createTetrahedron()
{
    AsdkBody *pBody = NULL;

    try
    {
        AcGePoint3d corner1 = getPoint(ACRX_T("\nCorner one: "));
        AcGePoint3d corner2 = getPoint(ACRX_T("\nCorner two: "));
        AcGePoint3d corner3 = getPoint(ACRX_T("\nCorner three: "));
        AcGePoint3d corner4 = getPoint(ACRX_T("\nCorner four: "));
        ads_printf( ACRX_T("\n") );
    
        pBody = new AsdkBody;

        pBody->createTetrahedron(corner1, corner2, corner3, corner4);
    }
    catch (int caught_adsrc)
    //
    // User probably cancelled.  Clean up and bail out.
    {
        handleADSError(caught_adsrc);
        return;
    }
    catch (ErrorCode err) 
    {
        if (err == eFail)
        {
            ads_printf( ACRX_T("\nBody is not valid.  Continue?"));
            if(! getYesNo())
            {
                delete pBody;
                return;
            }
        }
        else
        {
            ads_printf( ACRX_T("\nERROR: %s\n"), getErrorMsg(err));
            delete pBody;
            return;
        }
    }

    if (append( pBody ))
        pBody->close();
    else {
        delete pBody;
        ads_printf( ACRX_T("\nCould not add AsdkBody to ACAD Database.  *Bailing out*\n") );
    }
}


void 
createTorus()
{
    AsdkBody *pBody = NULL;

    try
    {
        AcGePoint3d axisStart, axisEnd;
        ads_printf(ACRX_T("\nTorus axis: "));
        getTwoPoints(axisStart, axisEnd);

        double majorRadius = getDistance(axisStart, ACRX_T("\nMajor radius: "));
        double minorRadius = getDistance(axisStart, ACRX_T("\nMinor radius: "));
        int majorApprox = getInt(ACRX_T("\nEnter # of lines to approximate major radius <32>:"), 32);
        int minorApprox = getInt(ACRX_T("\nEnter # of lines to approximate minor radius <32>:"), 32);
    
        pBody = new AsdkBody;
    
        pBody->createTorus(axisStart, axisEnd, majorRadius, minorRadius, 
            majorApprox, minorApprox );
    }
    catch (int caught_adsrc)
    //
    // User probably cancelled.  Clean up and bail out.
    {
        handleADSError(caught_adsrc);
        return;
    }
    catch (ErrorCode err) 
    {
        if (err == eFail)
        {
            ads_printf( ACRX_T("\nBody is not valid.  Continue?"));
            if(! getYesNo())
            {
                delete pBody;
                return;
            }
        }
        else
        {
            ads_printf( ACRX_T("\nERROR: %s\n"), getErrorMsg(err));
            delete pBody;
            return;
        }
    }

    if (append( pBody ))
        pBody->close();
    else {
        delete pBody;
        ads_printf( ACRX_T("\nCould not add AsdkBody to ACAD Database.  *Bailing out*\n") );
    }
}


void 
createReducingElbow()
{
    AsdkBody *pBody = NULL;

    try
    {
        AcGePoint3d elbowCenter = getPoint(ACRX_T("\nElbow center: "));
        AcGePoint3d endCenter1 = getPoint(ACRX_T("\nEnd one center: "));
        double endRadius1 = getDistance(endCenter1, ACRX_T("\nEnd one radius: "));
        AcGePoint3d endCenter2 = getPoint(ACRX_T("\nEnd two center: "));
        double endRadius2 = getDistance(endCenter2, ACRX_T("\nEnd two radius: "));
        int majorApprox = getInt(ACRX_T("\nEnter # of lines to approximate major radius <32>:"), 32);
        int minorApprox = getInt(ACRX_T("\nEnter # of lines to approximate minor radius <32>:"), 32);
    
        pBody = new AsdkBody;
    
        pBody->createReducingElbow(elbowCenter, endCenter1, endCenter2, 
            endRadius1, endRadius2, majorApprox, minorApprox);
    }
    catch (int caught_adsrc)
    //
    // User probably cancelled.  Clean up and bail out.
    {
        handleADSError(caught_adsrc);
        return;
    }
    catch (ErrorCode err) 
    {
        if (err == eFail)
        {
            ads_printf( ACRX_T("\nBody is not valid.  Continue?"));
            if(! getYesNo())
            {
                delete pBody;
                return;
            }
        }
        else
        {
            ads_printf( ACRX_T("\nERROR: %s\n"), getErrorMsg(err));
            delete pBody;
            return;
        }
    }

    if (append( pBody ))
        pBody->close();
    else {
        delete pBody;
        ads_printf( ACRX_T("\nCould not add AsdkBody to ACAD Database.  *Bailing out*\n") );
    }
}


void 
createRectToCircleReducer()
{
    AsdkBody *pBody = NULL;

    try
    {
        AcGePoint3d baseCorner = getPoint(ACRX_T("\nBase corner: "));
        AcGeVector3d baseSizes3d = getPoint(ACRX_T("\nBase sizes: ")) - baseCorner;
        AcGeVector2d baseSizes(baseSizes3d.x, baseSizes3d.y);
        AcGePoint3d circleCenter = getPoint(ACRX_T("\nCircle center: "));
        double circleRadius = getDistance(circleCenter, ACRX_T("\nCircle radius: "));
        AcGeVector3d circleNormal;

        // Get circle normal.  Jiri changed it so that it always uses the
        // Z axis, so this really does nothing.  -vm
        //
        try
        {
            circleNormal 
                = getPoint(ACRX_T("\nCircle normal vector <Z-Axis>: ")) - AcGePoint3d(0, 0, 0);
        }
        catch (int caught_adsrc)
        {
            if (caught_adsrc == RTNONE)
                circleNormal = AcGeVector3d::kZAxis;
            else
                throw caught_adsrc;
        }

        int approx = getInt(ACRX_T("\nEnter # of lines to approximate a circle <32>:"), 32);
    
        pBody = new AsdkBody;
    
        pBody->createRectToCircleReducer( baseCorner, baseSizes,
	        circleCenter, circleNormal, circleRadius, approx);
    }
    catch (int caught_adsrc)
    //
    // User probably cancelled.  Clean up and bail out.
    {
        handleADSError(caught_adsrc);
        return;
    }
    catch (ErrorCode err) 
    {
        if (err == eFail)
        {
            ads_printf( ACRX_T("\nBody is not valid.  Continue?"));
            if(! getYesNo())
            {
                delete pBody;
                return;
            }
        }
        else
        {
            ads_printf( ACRX_T("\nERROR: %s\n"), getErrorMsg(err));
            delete pBody;
            return;
        }
    }

    if (append( pBody ))
        pBody->close();
    else {
        delete pBody;
        ads_printf( ACRX_T("\nCould not add AsdkBody to ACAD Database.  *Bailing out*\n") );
    }
}

void 
createConvexHull()
{
    AsdkBody *pBody = NULL;
    AcGePoint3d *vertices = NULL;
    int iVertices;

    try
    {
        getVertices(vertices, iVertices);

		pBody = new AsdkBody;

//		pBody->createFace(vertices, iVertices);
		pBody->createConvexHull(vertices, iVertices);
    }
    catch(int caught_adsrc)
    //
    // User probably cancelled.  Clean up and bail out.
    {
        handleADSError(caught_adsrc);
        goto cleanup;
    }
	catch (ErrorCode err) 
    {
        if (err == eFail)
        {
            ads_printf( ACRX_T("\nBody is not valid.  Continue?"));
            if(! getYesNo())
            {
                delete pBody;
                goto cleanup;
            }
        }
        else
        {
            ads_printf( ACRX_T("\nERROR: %s\n"), getErrorMsg(err));
            delete pBody;
            goto cleanup;
        }
    }

	if (append( pBody ))
        pBody->close();
    else {
        delete pBody;
        ads_printf( ACRX_T("\nCould not add AsdkBody to ACAD Database.  *Bailing out*\n") );
    }

cleanup:

    delete [] vertices;
}


//
// createFace
//
// Gets a single-face AsdkBody object, then closes it.
//
// (If the user chooses to get an existing face, the
// net effect of this function is nada -- I think...)
//
void 
createFace()
{
	AsdkBody* pBody = NULL;
    
    try
    {
        pBody = getFace();
    }
    catch (int caught_adsrc)
    {
        handleADSError(caught_adsrc);
        return;
    }
    catch (ErrorCode err) 
    {
        ads_printf( ACRX_T("\nERROR: %s\n"), getErrorMsg(err));
        delete pBody;
        return;
    }

	if (pBody != NULL)
    {
		pBody->close();
    }
}


void 
createPyramid()
{
    AsdkBody *pBody = NULL;
    AcGePoint3d *vertices = NULL;
	PolygonVertexData** vertexData = NULL;
	int iVertices;
    AcGeVector3d normal;
    AcGePoint3d apex(0,0,1);
    
    try 
    {
        ads_printf(ACRX_T("\nProfile to extrude: "));
        while (vertices == NULL)
            getPolylineVertices(vertices, vertexData, iVertices, normal);
        
        apex = getPoint(ACRX_T("\nApex point: "));
	    
        pBody = new AsdkBody;
    
		pBody->createPyramid(vertices, vertexData, iVertices, normal, apex);
	}
    catch (int caught_adsrc)
    //
    // User probably cancelled.  Clean up and bail out.
    {
        handleADSError(caught_adsrc);
        goto cleanup;
    }
    catch (ErrorCode err) 
    {
        if (err == eFail)
        {
            ads_printf( ACRX_T("\nBody is not valid.  Continue?"));
            if(! getYesNo())
            {
                delete pBody;
                goto cleanup;
            }
        }
        else
        {
            ads_printf( ACRX_T("\nERROR: %s\n"), getErrorMsg(err));
            delete pBody;
            goto cleanup;
        }
    }
    if (append( pBody ))
        pBody->close();
    else {
        delete pBody;
        ads_printf( ACRX_T("\nCould not add AsdkBody to ACAD Database.  *Bailing out*\n") );
    }

cleanup:
    
    delete [] vertices;
    delete [] vertexData;
}


void 
createExtrusion()
{
    AsdkBody *pBody = NULL;
    AcGePoint3d *vertices = NULL;
	PolygonVertexData** vertexData = NULL;
	int iVertices;
    AcGeVector3d normal;
    AcGeVector3d extrusion;
    double scaleFactor, twistAngle;
    Point3d fixedPt = Point3d::kNull;
    
    try 
    {
        ads_printf(ACRX_T("\nProfile to extrude: "));
        while (vertices == NULL)
            getPolylineVertices(vertices, vertexData, iVertices, normal);

        ads_printf(ACRX_T("\nExtrusion vector: "));
        extrusion = getVector();

        // Get scale factor and twist angle
        //
        scaleFactor = getReal(ACRX_T("\nScale factor <1.0>: "), 1.0);
        twistAngle = getReal(ACRX_T("\nTwist angle <0.0>: "), 0.0);
        if (scaleFactor != 1.0 || twistAngle != 0.0)
        {
            try {
                fixedPt = getPoint(ACRX_T("Select fixed point for scale/twist <0,0,0>: "));
            }
            catch (int caught_adsrc)
            {
                if (caught_adsrc)
                    fixedPt = Point3d::kNull;
                else
                    throw caught_adsrc;
            }
        }
		else
			fixedPt = vertices[0];
        pBody = new AsdkBody;
    
		pBody->createExtrusion(vertices, vertexData, iVertices, normal, 
            extrusion, fixedPt, scaleFactor, twistAngle);
	}
    catch (int caught_adsrc)
    //
    // User probably cancelled.  Clean up and bail out.
    {
        handleADSError(caught_adsrc);
        goto cleanup;
    }
    catch (ErrorCode err) 
    {
        if (err == eFail)
        {
            ads_printf( ACRX_T("\nBody is not valid.  Continue?"));
            if(! getYesNo())
            {
                delete pBody;
                goto cleanup;
            }
        }
        else
        {
            ads_printf( ACRX_T("\nERROR: %s\n"), getErrorMsg(err));
            delete pBody;
            goto cleanup;
        }
    }
    if (append( pBody ))
        pBody->close();
    else {
        delete pBody;
        ads_printf( ACRX_T("\nCould not add AsdkBody to ACAD Database.  *Bailing out*\n") );
    }

cleanup:
    
    delete [] vertices;
    delete [] vertexData;
}


void 
createAxisRevolution()
{
    AsdkBody *pBody = NULL;
    AcGePoint3d *vertices = NULL;
	PolygonVertexData** vertexData = NULL;
	int iVertices;
    AcGeVector3d normal;
    AcGePoint3d axisStart(0,0,0);
    AcGePoint3d axisEnd(1,1,0);
    ads_real revolutionAngle;
    int approx;
    Point3d fixedPt = Point3d::kNull;
    double scaleFactor;
    double twistAngle;
    
    try 
    {
        ads_printf(ACRX_T("\nProfile to revolve: "));
        while (vertices == NULL)
            getPolylineVertices(vertices, vertexData, iVertices, normal);

        ads_printf(ACRX_T("\nRotation axis: "));
        getTwoPoints(axisStart, axisEnd);

        revolutionAngle = getReal(ACRX_T("\nRevolution angle <360>: "), 360.0);

        approx = getInt(ACRX_T("\nEnter # of lines to approximate a circle <32>:"), 32);

        // Get scale factor and twist angle
        //
        scaleFactor = getReal(ACRX_T("\nScale factor <1.0>: "), 1.0);
        twistAngle = getReal(ACRX_T("\nTwist angle <0.0>: "), 0.0);
        if (scaleFactor != 1.0 || twistAngle != 0.0)
        {
            try {
                fixedPt = getPoint(ACRX_T("Select fixed point for scale/twist <0,0,0>: "));
            }
            catch (int caught_adsrc)
            {
                if (caught_adsrc)
                    fixedPt = Point3d::kNull;
                else
                    throw caught_adsrc;
            }
        }

        pBody = new AsdkBody;
    
		pBody->createAxisRevolution(vertices, vertexData, iVertices, 
            normal, axisStart, axisEnd, (double)revolutionAngle, approx,
            fixedPt, (double)scaleFactor, (double)twistAngle);
	}
    catch (int caught_adsrc)
    //
    // User probably cancelled.  Clean up and bail out.
    {
        handleADSError(caught_adsrc);
        goto cleanup;
    }
    catch (ErrorCode err) 
    {
        if (err == eFail)
        {
            ads_printf( ACRX_T("\nBody is not valid.  Continue?"));
            if(! getYesNo())
            {
                delete pBody;
                goto cleanup;
            }
        }
        else
        {
            ads_printf( ACRX_T("\nERROR: %s\n"), getErrorMsg(err));
            delete pBody;
            goto cleanup;
        }
    }
    if (append( pBody ))
        pBody->close();
    else {
        delete pBody;
        ads_printf( ACRX_T("\nCould not add AsdkBody to ACAD Database.  *Bailing out*\n") );
    }

cleanup:
    
    delete [] vertices;
    delete [] vertexData;
}


//
// createExtrusionPath()
//
// Creates a CBody object from one or two profile faces
// (single-face AsdkBody objects) and an extrusion path.
//
void 
createExtrusionAlongPath()
{
    AsdkBody *pBody = NULL;
    AsdkBody *pStartFace = NULL, *pEndFace = NULL;
    MorphingMap *pMorphMap = NULL;
    AcGePoint3d *vertices = NULL;
    PolygonVertexData** vertexData = NULL;
    int iVertices;
    bool bClosePath;
    bool bCheckValidity;
    double scaleFactor, twistAngle;
    Point3d fixedPt = Point3d::kNull;

    try
    {
        ads_printf( ACRX_T("\nStart profile: ") );
        pStartFace = getFace();

        ads_printf( ACRX_T("\nEnd profile: ") );
        pEndFace = getFace();

        if( pEndFace == NULL ) {
            pEndFace = new AsdkBody;  // empty body
            ads_printf(ACRX_T("\nNull end profile will be used."));
        }

        // Get morphing map if there is an end face
        //
        // The const_cast is necessary. We need to make it a const,
        // so it calls the right verson of body() which calls assertReadEnabled().
        // pEndFace is currently open for read.
        //
        if (!const_cast<const AsdkBody*>(pEndFace)->body().isNull())
            pMorphMap = queryMorphingMap(pStartFace, pEndFace);
        if (pMorphMap == NULL)
            pMorphMap = new MorphingMap(MorphingMap::kNull);

        // Get extrusion path
        //
        ads_printf(ACRX_T("\nExtrusion path: "));
        getPath(vertices, vertexData, iVertices);
        if (vertices == NULL)
        {
            ads_printf(ACRX_T("\nBad extrusion path.  *Bailing out*\n"));
            goto cleanup;
        }

        ads_printf(ACRX_T("\nClose Path? "));
        bClosePath = getYesNo(FALSE);

        // Get scale factor and twist angle
        //
        scaleFactor = getReal(ACRX_T("\nScale factor <1.0>: "), 1.0);
        twistAngle = getReal(ACRX_T("\nTwist angle <0.0>: "), 0.0);
        if (scaleFactor != 1.0 || twistAngle != 0.0)
        {
            try {
                fixedPt = getPoint(ACRX_T("Select fixed point for scale/twist <0,0,0>: "));
            }
            catch (int caught_adsrc)
            {
                if (caught_adsrc)
                    fixedPt = Point3d::kNull;
                else
                    throw caught_adsrc;
            }
        }

        ads_printf(ACRX_T("\nCheck validity of result? "));
        bCheckValidity = getYesNo();

        pBody = new AsdkBody;

        // The two const_casts are necessary. We need to make them const,
        // so we call the right verson of body() which calls assertReadEnabled().
        // pStartFace and pEndFace are currently open for read.
        //
        pBody->createExtrusionAlongPath(
            const_cast<const AsdkBody*>(pStartFace)->body(),
            const_cast<const AsdkBody*>(pEndFace)->body(),
            vertices, 
            vertexData, 
            iVertices, 
            bClosePath,
            bCheckValidity,
            fixedPt,
            (double)scaleFactor, 
            (double)twistAngle, 
            *pMorphMap);
    }
    catch (int caught_adsrc)
    //
    // User probably cancelled.  Clean up and bail out.
    {
        handleADSError(caught_adsrc);
        goto cleanup;
    }
	catch (ErrorCode err) 
    {
        if (err == eFail)
        {
            ads_printf( ACRX_T("\nBody is not valid.  Continue?"));
            if(! getYesNo())
            {
                delete pBody;
                goto cleanup;
            }
        }
        else
        {
            ads_printf( ACRX_T("\nERROR: %s\n"), getErrorMsg(err));
            delete pBody;
            goto cleanup;
        }
    }
    
    if (append(pBody))
        pBody->close();
    else {
        delete pBody;
        ads_printf(ACRX_T("\nCould not add AsdkBody to ACAD Database.  *Bailing out*\n"));
    }

cleanup:

    cleanupEntity(pStartFace);
    cleanupEntity(pEndFace);
    delete [] vertices;
    delete [] vertexData;
}


void 
aUnion()
{
    ads_name s;
    if (RTNORM != ads_ssget( NULL, NULL, NULL, NULL, s ))
        return;

    ads_printf( ACRX_T("\n") );

    int len = 0;
    ads_sslength( s, &len );
    if (len < 2) {
        ads_printf( ACRX_T("Nothing to do.\n") );
        ads_ssfree( s );
        return;
    }

    AsdkBody *pFirst = NULL;
    ads_name first_ent;
    for (long i = 0; i < len; i++)
    {
        ads_name ent;
        AcDbObjectId id;

        if (RTNORM != ads_ssname( s, i, ent ))
            continue;
        if (Acad::eOk != acdbGetObjectId( id, ent ))
            continue;

        AsdkBody *p;
        if (Acad::eOk != acdbOpenObject( p, id, AcDb::kForWrite ))
            continue;

        if (NULL == pFirst)
        {
            pFirst = p;
            ads_name_set(ent, first_ent);
            //
            // Not sure if this is the right way to copy an ads_name -vm
        }
        else 
        {
            try 
            {
                pFirst->body() += p->body();
                p->erase();
            }
            catch (...) 
            {
                ads_printf( ACRX_T("*Invalid*\n") );
            }
            p->close();
        }
    }
    
    ads_ssfree( s );
    if (NULL != pFirst)
    {
        pFirst->close();
        ads_entupd(first_ent);
    }
}


void 
aSubtract()
{
    ads_name ent1, ent2;
    ads_point p1, p2;

    if (RTNORM != ads_entsel( ACRX_T("\nSelect AsdkBody to subtract from: "), ent1, p1 ))
    {
        ads_printf( ACRX_T("*Cancel*\n") );
        return;
    }
    if (RTNORM != ads_entsel( ACRX_T("\nSelect AsdkBody to subtract: "), ent2, p2 ))
    {
        ads_printf( ACRX_T("*Cancel*\n") );
        return;
    }
    ads_printf( ACRX_T("\n") );

    AcDbObjectId id1, id2;
    if (Acad::eOk != acdbGetObjectId( id1, ent1 ))
    {
        ads_printf( ACRX_T("*Cancel*\n") );
        return;
    }
    if (Acad::eOk != acdbGetObjectId( id2, ent2 ))
    {
        ads_printf( ACRX_T("*Cancel*\n") );
        return;
    }

    AsdkBody *pb1, *pb2;
    if (Acad::eOk != acdbOpenObject( pb1, id1, AcDb::kForWrite ))
    {
        ads_printf( ACRX_T("*Cancel*\n") );
        return;
    }
    if (Acad::eOk != acdbOpenObject( pb2, id2, AcDb::kForWrite ))
    {
        pb1->close();
        ads_printf( ACRX_T("*Cancel*\n") );
        return;
    }

    try {
        pb1->body() -= pb2->body();
        pb2->erase();
    }
    catch (...) {
        ads_printf( ACRX_T("*Invalid*\n") );
    }
    pb1->close();
    pb2->close();

    ads_entupd(ent1);
}


void 
aIntersect()
{
    ads_name s;
    if (RTNORM != ads_ssget( NULL, NULL, NULL, NULL, s ))
        return;

    ads_printf( ACRX_T("\n") );

    int len = 0;
    ads_sslength( s, &len );
    if (len < 2) 
    {
        ads_printf( ACRX_T("Nothing to do.\n") );
        ads_ssfree( s );
        return;
    }

    AsdkBody *pFirst = NULL;
    ads_name first_ent;
    for (long i = 0; i < len; i++)
    {
        ads_name ent;
        AcDbObjectId id;
        if (RTNORM != ads_ssname( s, i, ent ))
            continue;
        if (Acad::eOk != acdbGetObjectId( id, ent ))
            continue;

        AsdkBody *p;
        if (Acad::eOk != acdbOpenObject( p, id, AcDb::kForWrite ))
            continue;

        if (NULL == pFirst)
        {
            pFirst = p;
            ads_name_set(ent, first_ent);
        }
        else 
        {
            try 
            {
                pFirst->body() *= p->body();
                p->erase();
            }
            catch (...) 
            {
                ads_printf( ACRX_T("*Invalid*\n") );
            }
            p->close();
        }
    }
    ads_ssfree( s );
    if (NULL != pFirst) 
    {
        if (pFirst->body().isNull()) 
        {
            ads_printf( ACRX_T("Null AsdkBody created - deleted\n") );
            pFirst->erase();
        }
        pFirst->close();
        ads_entupd(first_ent);
    }
}


//
// Only for profiling purposes.
//
void
doArray()
{
    acedCommandS(
        RTSTR, ACRX_T("_array"),
        RTSTR, ACRX_T("_l"),
        RTSTR, ACRX_T(""),
        RTSTR, ACRX_T("_r"),
        RTSTR, ACRX_T("30"),
        RTSTR, ACRX_T("30"),
        RTSTR, ACRX_T("0,0"),
        RTSTR, ACRX_T("15,15"),
        NULL );
}


////////////////////////////////////////////////////////////////////////////////
//
// Face and morphing map creation functions.
//
// These functions are specific to Facet Modeler objects.
//
// Each throws an ADS return code if the user cancels out of an operation,
// or there is an unanticipated error.
//

#define STREQ(s,t) (_tcscmp((s),(t))==0)

//
// getFace()
//
// Prompts the user to specify a face in one of three ways:
// 1) Select an existing AsdkBody that consists of one face,
// 2) Select a polyline to be used as a pattern for the face
//    vertices (the default), or
// 3) Enter the face vertices one-by-one.
//
// A AsdkBody object, opened for reading, is returned.
//
static AsdkBody* 
getFace()
{
	int adsrc;
    ACHAR kw[20];

    // Limit the choices for the time being -vm
    //
    // ads_initget(0, "Points polyLine Face");
	// adsrc = ads_getkword("Points/<polyLine>/Face: ", kw);

    ads_initget(0, ACRX_T("Points polyLine"));
	adsrc = ads_getkword(ACRX_T("Points/<polyLine>: "), kw);
    if (adsrc <= RTERROR) 
		throw adsrc;
    
    if (adsrc == RTNONE) 
    {
        _tcscpy_s(kw, ACRX_T("polyLine"));
		adsrc = RTNORM;
    }

	if (STREQ(kw, ACRX_T("Face")))
        return getExistingFace();
    else
        return getNewFace(kw);
}


//
// getNewFace()
//
// If kw == "polyLine", create a single-face AsdkBody based on an existing polyline.
// If kw == "Points", creat a single-face AsdkBody based on points entered by the user.
// A pointer to the AsdkBody, opened for reading, is returned.
//
static AsdkBody*
getNewFace(ACHAR* kw)
{
    AsdkBody* pBody = NULL;
    AcGePoint3d *vertices = NULL;
    int iVertices;
    AcGeVector3d normal;

    if (STREQ(kw, ACRX_T("polyLine")))
    // Create a new one-face AsdkBody from an exisiting polyline
    //
    {
		PolygonVertexData** vertexData = NULL;
		int iVertices;

		getPolylineVertices(vertices, vertexData, iVertices, normal);

        if (vertices == NULL)
            return NULL;
            
        pBody = new AsdkBody;

        try 
        {
		    pBody->createFace(vertices, vertexData, iVertices, normal);
		}
		catch (ErrorCode err) 
        {
			ads_printf( ACRX_T("\nERROR: %s\n"), getErrorMsg(err));
			delete pBody;
            delete [] vertices;
            delete [] vertexData;
			return NULL;
		}
        delete [] vertexData;
    }
    else if (STREQ(kw, ACRX_T("Points")))
    {
        getVertices(vertices, iVertices);

        if (vertices == NULL)
            return NULL;

		pBody = new AsdkBody;

        try
        {
		    pBody->createFace(vertices, iVertices);
		}
		catch (ErrorCode err) 
        {
		    ads_printf( ACRX_T("\nERROR: %s\n"), getErrorMsg(err));
			delete pBody;
            delete [] vertices;
		    return NULL;
	    }

    }
    else // should never happen
        return NULL;
	
    delete [] vertices;

	if (! append(pBody)) 
    {
		ads_printf( ACRX_T("\nCould not add AsdkBody to ACAD Database.  *Bailing out*\n") );
        delete pBody;
	    return NULL;
	}

	ads_printf(ACRX_T("\nCreated %d edge face."), pBody->body().edgeCount());
	pBody->downgradeOpen();

	return pBody;
}


//
// getExistingFace()
// 
// Prompts the user to select an entity.  If it is a single-face AsdkBody, a
// pointer to the AsdkBody, opened for reading, is returned, otherwise, NULL.
//
static AsdkBody*
getExistingFace()
{
    AsdkBody* pBody = NULL;
	AcDbEntity* pEnt = NULL;
    
    ads_printf(ACRX_T("\nSelect a single-face AsdkBody :"));
    pEnt = selectEntity(AcDb::kForRead);

	if (pEnt == NULL) 
    {
		ads_printf( ACRX_T("No entity selected.\n") );
		ads_printf( ACRX_T("*Cancel*\n") );
		return NULL;
	}

	pBody = AsdkBody::cast(pEnt);

	if (pBody == NULL) 
    {
		ads_printf(ACRX_T("\nEntity is not a AsdkBody object.  *Bailing out*\n"));
		pEnt->close();
		return NULL;
	}
    if (pBody->body().faceCount() != 1)
    {
        ads_printf(ACRX_T("\nAsdkBody object must have exactly one face. *Bailing out*\n"));
        pBody->close();
        return NULL;
    }
 
    ads_printf(ACRX_T("\nGot a %d edge face."), pBody->body().edgeCount());

    return pBody;
}


//
// getMorphingMap
//
// Prompts the user to enter all of the vertex connections necessary
// to create a morphing map, based on the start and end profile faces
// passed to it.
// 
// The function will iterate on the vertices of the face which has
// the most vertices, assuring completeness.
//
static MorphingMap
getMorphingMap(const Body& startProfile, const Body& endProfile)
{
	int startCount = startProfile.edgeCount();
	int endCount = endProfile.edgeCount();
	
	int vertex;
	MorphingMap morphMap; // returned

    // The defaultVertex is equal to the same index on the opposite
    // face, unless it is greater than the max index on that face,
    // in which case it equals the max index.
    //
    int defaultVertex;
 
    // Not documented what this does, or if I need to do it.
    //
	morphMap.init();

	if (endCount > startCount)
	{
		ads_printf(ACRX_T("\nMorph from end profile to start profile.\n"));
		for(int i = 0; i < endCount; i++) {
			defaultVertex = i > startCount - 1 ? startCount - 1 : i;
			ads_printf(ACRX_T("Map vertex %d to vertex [0-%d] <%d> :"), 
					i, startCount - 1, defaultVertex);
            vertex = getInt(ACRX_T(""), defaultVertex);

			morphMap.add(vertex, i);
		}
	}
	else // startCount >= endCount
	{
		ads_printf(ACRX_T("\nMorph from start profile to end profile.\n"));
		for(int i = 0; i < startCount; i++) {
			defaultVertex = i > endCount - 1 ? endCount - 1 : i;
			ads_printf(ACRX_T("Map vertex %d to vertex [0-%d] <%d> :"), 
					i, endCount - 1, defaultVertex);
			vertex = getInt(ACRX_T(""), defaultVertex);

			morphMap.add(i, vertex);
		}
	}
	return morphMap;
}


//
// queryMorphingMap()
//
// Encapsulates getMorphingMap, performing all the necessary
// user interaction.
//
static MorphingMap*
queryMorphingMap(AsdkBody* pBody1, AsdkBody* pBody2)
{
    bool bGetMorphingMap;
	pBody1->upgradeOpen();
	pBody2->upgradeOpen();
	
    if (pBody1->body().edgeCount() == pBody2->body().edgeCount())
	{
		pBody1->downgradeOpen();
		pBody2->downgradeOpen();
		ads_printf(ACRX_T("\nSpecify Morphing Map? "));
		bGetMorphingMap = getYesNo(FALSE);
	}
	else
	{
		bGetMorphingMap = TRUE;
	}
	
	
	if (bGetMorphingMap)
	{
		pBody1->upgradeOpen();
		pBody2->upgradeOpen();
		MorphingMap* map;
        map = new MorphingMap(getMorphingMap(pBody1->body(), pBody2->body()));
		pBody1->downgradeOpen();
		pBody2->downgradeOpen();
		return map;
	}
    else
        return NULL;
}


////////////////////////////////////////////////////////////////////////////////
//
// ADS utility functions
//
// Each of these encapsulates one or more ADS functions and performs conversion
// to AcGe class objects.
//
// The ADS return code is thrown if the user cancels, or there is an unforseen
// error.
//

//
// getPolyline()
//
// Prompts the user to select an entity, then attempts to cast it
// to a AcDb2dPolyline.  Returns NULL if this doesn't work.
//
static AcDb2dPolyline*
getPolyline()
{
	AcDb2dPolyline* pPLine = NULL;
	AcDbEntity* pEnt = NULL;
    
    while (1)
    {
        ads_printf(ACRX_T("Select polyline :"));
        pEnt = selectEntity(AcDb::kForRead);

        if (pEnt == NULL)
            return NULL;


	    pPLine = AcDb2dPolyline::cast(pEnt);

		if (pPLine == NULL) 
        {
			AcDbPolyline* pLwPline = NULL;

			if (pEnt->isA() != AcDbPolyline::desc())
			{
				ads_printf(ACRX_T("\nEntity must be a polyline.\n"));
				pEnt->close();
				continue;
			}
			else // LWPolyline found, convert
			{
				pEnt->upgradeOpen();
				pLwPline = AcDbPolyline::cast(pEnt);
				Acad::ErrorStatus es;
				pLwPline->upgradeOpen();
				es = pLwPline->convertTo(pPLine);
				if (es == Acad::eObjectToBeDeleted)
				{
					delete(pLwPline);
					pPLine->downgradeOpen();
				}
				else
					return NULL;
				break;
			}
		}
        else
            break;
    }

	return pPLine;
}


static AcGeVector3d
getVector()
{
    AcGePoint3d p1(0,0,0), p2(0,0,0);

    getTwoPoints(p1, p2);
    return p2 - p1;
}


//
// getTwoPoints()
//
// Used to get a line.  When I figure out how to
// convert an AcGeLine3d, I'll would pass back one of
// those, instead.
//
static void
getTwoPoints(AcGePoint3d& p1, AcGePoint3d &p2)
{
    AcGePoint3d *vertices = NULL;
    int iVertices;

    getVertices(vertices, iVertices, 2);
        
    if (iVertices == 2)
    {
       p1 = vertices[0];
       p2 = vertices[1];
    }
    if (iVertices == 1)
    {
       p1 = acdbHostApplicationServices()->workingDatabase()->ucsorg();
       p2 = vertices[0];
    }

    delete [] vertices;
}


//
// circleRadiusFromBulge()
//
// ARX expresses arcs in terms of their "bulges", while the Facet Modeler
// uses circle radii.  The function gets the radius from the bulge.
//
double 
circleRadiusFromBulge(const AcGePoint3d& p1, const AcGePoint3d& p2, double bulge)
{
	return 0.25 * p1.distanceTo(p2) * (bulge + 1 / bulge);  
} 


//
// getPolylineVertices()
//
// Gets a polyline entity from the user, and converts it into an array of
// vertices, vertex data, and a normal, which are passed back through the
// parameters.  If something goes wrong, vertices is set to NULL.
//
// Note that PolygonVertexData is an AModeler class.
//
static void 
getPolylineVertices(AcGePoint3d* &vertices, PolygonVertexData** &vertexData, 
	int &iVertices, AcGeVector3d &normal)
{
	int i;
    int approx = -1;
    double filletRadius;
	AcDb2dPolyline* pPLine = getPolyline();

	if (pPLine == NULL) 
    {
		vertices = NULL;
		vertexData = NULL;
		iVertices = 0;
		return;
	}

	AcDbObjectIterator* pIterator = pPLine->vertexIterator();

	AcDb2dVertex* pVertex;
	AcDbObjectId vId;

    // Loop 1:
    // Count the vertices.
    //
	for (iVertices = 0; ! pIterator->done(); pIterator->step(), iVertices++) 
        {;}

    if (iVertices == 0)  // something is fishy
    {
        vertices = NULL;
        vertexData = NULL;
        return;
    }

	vertices = new AcGePoint3d[iVertices];
	vertexData = new PolygonVertexData*[iVertices];
	double *bulge = new double[iVertices];

    normal = pPLine->normal();

    // Loop 2:
    // Get the coordinates and bulge of each vertex
    //
	for (pIterator->start(), i=0; ! pIterator->done(); pIterator->step(), i++) 
    {
		vId = pIterator->objectId();
		pPLine->openVertex(pVertex, vId, AcDb::kForRead);

		vertices[i] = pPLine->vertexPosition(*pVertex);
		bulge[i] = pVertex->bulge();
	
		pVertex->close();
	}

    // Loop 3:
    // Create the vertexData for the polyline.
    // This is in its own loop because we need to peek at the next vertex each time.
    // 
    filletRadius = getReal(ACRX_T("\nFillet radius <0.0>: "), 0.0);

	for (i = 0; i < iVertices; i++)
	{
		if (bulge[i] != 0.0 && (pPLine->isClosed() || i + 1 < iVertices))
        // i.e., vertex is beginning of an arc
        // AND this is not the last vertex of an open polyline
        {
			if (approx < 0)
			{
                approx = getInt(ACRX_T("\nEnter # of lines to approximate a circle <32>:"), 32);
                //
                // I'm deliberately allowing invalid values here,
                // i.e., numbers below 4
			}
			AcGePoint3d nextVertex = i + 1 < iVertices ? vertices[i + 1] : vertices[0];
            // nextVertex might be the first vertex

			double radius = circleRadiusFromBulge(vertices[i], nextVertex, bulge[i]);
			
            bool leftOfCenter;

			if (bulge[i] > 0 && bulge[i] < 1) 
				leftOfCenter = TRUE;
			else if (bulge[i] < -1)
				leftOfCenter = TRUE;
			else
				leftOfCenter = FALSE;

			Circle3d circle(
                (Point3d)vertices[i], 
                (Point3d)nextVertex, 
                (Vector3d)normal, 
                radius, 
                leftOfCenter);

			vertexData[i] = new PolygonVertexData(PolygonVertexData::kArc3d,
                circle, approx);
        }
        else // vertex is the first of a staight line segment
        {
            if (filletRadius != 0.0)
            {
                if (approx < 0)
                    approx = getInt(ACRX_T("\nEnter # of lines to approximate a circle <32>:"), 32);

                vertexData[i] = new PolygonVertexData(
                    PolygonVertexData::kFilletByRadius,
                    filletRadius,
                    approx);
            }
            else
            {
                vertexData[i] = NULL;
            }
        }
	}

	delete pIterator;
	delete [] bulge;

	// pPLine->upgradeOpen();
	// pPLine->erase();
    //
    // Maybe better for testing if we don't erase this polyline

	pPLine->close();
}


//
// getVertices()
//
// Prompt the user for a series of points to be returned as
// an array of vertices.  vertices gets set to NULL if something
// went wrong.
//
// Sorry, no arcs or fillets allowed yet.
//
static void 
getVertices(AcGePoint3d* &vertices, int &iVertices, int iMaxVertices)
{
	int i;
    AcGePoint3d* p = new AcGePoint3d[iMaxVertices];

    ads_initget(0, NULL);

    // Loop 1:
    // Get points from the user, and assign them to the p array.
    //
	for (i=0; i < iMaxVertices; i++) 
    {
        try
        {
            p[i] = getPoint(ACRX_T("Select point: "));
        }
        catch (int caught_adsrc)
        {
            if (caught_adsrc == RTNONE)
                break;
            else
                throw caught_adsrc;
        }
        ads_printf(ACRX_T("\n"));
	}

	iVertices = i;

	vertices = new AcGePoint3d[iVertices];
	
    // Loop 2:
    // Copy vertices into returned array
    //
	for (i = 0; i < iVertices; i++) 
    {
		vertices[i] = p[i];
	}
    delete [] p;
}


//
// getPath()
//
// Prompts the user to make a path either from an existing polyline, or by
// specifying individual points.
//
// Throws the ADS return code if there is an error, or the user
// cancels.
//
static void 
getPath(AcGePoint3d* &vertices, PolygonVertexData** &vertexData, int &iVertices)
{
	AcGeVector3d normal; // unused
    ACHAR kw[20];
    int adsrc;

    ads_initget(0, ACRX_T("Points polyLine"));
	adsrc = ads_getkword(ACRX_T("Points/<polyLine>: "), kw);
    if (adsrc <= RTERROR) 
		throw adsrc;
    if (adsrc == RTNONE) 
    {
		_tcscpy_s(kw, ACRX_T("polyLine"));
        adsrc = RTNORM;
    }

	if (STREQ(kw, ACRX_T("Points")))
        getVertices(vertices, iVertices);
    else
        getPolylineVertices(vertices, vertexData, iVertices, normal);
}

//
// selectEntity()
//
// Prompt the user to select an entity.  Returns NULL if nothing is selected.
//
static AcDbEntity*
selectEntity(AcDb::OpenMode openMode)
{
    ads_name en = { 0, 0 };
    ads_point pt = { 0.0, 0.0, 0.0 };  // Initialization experiment  -vm
    int adsrc;
    AcDbObjectId eId;

	ads_initget(0, NULL);

    adsrc = ads_entsel(ACRX_T(""), en, pt);

    if (adsrc == RTERROR)
    {
        adsrc = RTNONE;
    }

    if (adsrc <= RTERROR)
    {
        throw adsrc;
    }

	if (adsrc == RTNONE) 
	{
		ads_printf(ACRX_T("\nNothing Selected."));
        return NULL;
	}

    // Now, exchange the old-fangled ads_name for the new-fangled
    // object id.
    Acad::ErrorStatus retStat = acdbGetObjectId(eId, en);
    if (retStat != Acad::eOk) 
	{
        ads_printf(ACRX_T("\nacdbGetObjectId failed"));
        ads_printf(ACRX_T("\nen==(%lx,%lx), retStat==%d\n"), en[0], en[1], eId);
        return NULL;
    }

    AcDbEntity *pEntObj = NULL;

    if ((retStat = acdbOpenObject(pEntObj, eId, openMode)) != Acad::eOk) 
	{
        ads_printf(
            ACRX_T("\nacdbOpenObject failed: ename=(%lx,%lx), mode==%d retStat==%d\n"),
            en[0], en[1], openMode, retStat);
        return NULL;
    }
    return pEntObj;
}


//
// getYesNo
//
// Prompts the user to enter Yes or No.  The default is determined
// by the argument "defaultIsYes".
//
static bool 
getYesNo(bool defaultIsYes)
{
	int adsrc;
    ACHAR kw[20];
    ads_initget(0, ACRX_T("Yes No"));

	if(defaultIsYes)
		adsrc = ads_getkword(ACRX_T("<Yes>/No: "), kw);
	else
		adsrc = ads_getkword(ACRX_T("Yes/<No>: "), kw);

    if (adsrc <= RTERROR)
    {
        throw adsrc;
    }

    if (adsrc == RTNONE) {
		if(defaultIsYes)
			_tcscpy_s(kw, ACRX_T("Yes"));
		else
			_tcscpy_s(kw, ACRX_T("No"));
        adsrc = RTNORM;
    }

	if (STREQ(kw, ACRX_T("Yes")))
		return TRUE;
	else
		return FALSE;
}


//
// getPoint()
//
// Note that this throws RTNONE!
//
static AcGePoint3d
getPoint(ACHAR *prompt)
{
    int adsrc;
    ads_point p;

    ads_initget( 0, NULL );
    adsrc = ads_getpoint(NULL, prompt, p);
    if (adsrc <= RTERROR)
        throw adsrc;
    if (adsrc == RTNONE)
        throw adsrc; // catch this!
    if (adsrc == RTNORM)
    {
        acdbUcs2Wcs(p, p, Adesk::kFalse);
        return asPnt3d(p);
    }
    
    // if we get this far, "throw" our hands up...
    // OH, HA HA HA! GET IT?!?!
    throw adsrc;

    // To shut up the compiler...
    return AcGePoint3d(0,0,0);  // WILL NEVER DO THIS
}


static double
getDistance(AcGePoint3d fromPt, ACHAR *prompt, double defaultDist)
{
    int adsrc;
    ads_point p;
    ads_real dist = (ads_real)defaultDist;

    ads_initget( 0, NULL );
    acdbWcs2Ucs(asDblArray(fromPt), p, Adesk::kFalse);  
    adsrc = ads_getdist(p, prompt, &dist);
    if (adsrc <= RTERROR)
       throw adsrc;
    
    return (double)dist;
}

static int
getInt(ACHAR *prompt, int defaultValue)
{
    int i;

    ads_initget( 0, NULL );
    int adsrc = ads_getint(prompt, &i);
    if (adsrc <= RTERROR)
        throw adsrc;
	if (adsrc == RTNONE)
        i = defaultValue;

    return i;
}


static double
getReal(ACHAR *prompt, double defaultValue)
{
    double dbl;

    ads_initget( 0, NULL );
    int adsrc = ads_getreal(prompt, &dbl);
    if (adsrc <= RTERROR)
        throw adsrc;
    if (adsrc == RTNONE)
	    dbl = defaultValue;

    return dbl;
}

//
// cleanupEntity()
//
// Erase and close the entity passed.  I'm not sure what else to
// do to eliminate the enitity from the database.  -vm
//
static void
cleanupEntity(AcDbEntity *pEnt)
{
    if (pEnt != NULL)
    {
        if (! pEnt->isWriteEnabled())
            pEnt->upgradeOpen();

        pEnt->erase();
        pEnt->close();
    }
}

static void
handleADSError(int adsrc)
{
    if (adsrc == RTNONE)
        ads_printf(ACRX_T("\nNothing selected.  *Bailing out*\n"));
    else if (adsrc != RTCAN)
        ads_printf(ACRX_T("\nADS error %d. *Bailing out*\n"), adsrc);
}
