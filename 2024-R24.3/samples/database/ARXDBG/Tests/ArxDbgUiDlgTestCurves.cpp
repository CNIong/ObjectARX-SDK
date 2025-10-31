//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxDbgUiDlgTestCurves.h"
#include "ArxDbgUtils.h"
#include "ArxDbgSelSet.h"
#include "ArxDbgUtilsGe.h"
#include "AcadStr.h"
#include "SdSysVar.h"
#include "ArxDbgApp.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**  ArxDbgUiDlgTestCurve::ArxDbgUiDlgTestCurve
**
**  **jma
**
*************************************/

ArxDbgUiDlgTestCurve::ArxDbgUiDlgTestCurve(CWnd* parent)
:	CAcUiDialog(ArxDbgUiDlgTestCurve::IDD, parent, ArxDbgApp::getApp()->dllInstance())
{
    //{{AFX_DATA_INIT(ArxDbgUiDlgTestCurve)
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxDbgUiDlgTestCurve::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgTestCurve::DoDataExchange(CDataExchange* pDX)
{
    CAcUiDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxDbgUiDlgTestCurve)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiDlgTestCurve message map

BEGIN_MESSAGE_MAP(ArxDbgUiDlgTestCurve, CAcUiDialog)
    //{{AFX_MSG_MAP(ArxDbgUiDlgTestCurve)
    ON_BN_CLICKED(ARXDBG_BN_GETPLANE, testGetPlane)
    ON_BN_CLICKED(ARXDBG_BN_STARTPARAM, testGetStartParamEndParam)
    ON_BN_CLICKED(ARXDBG_BN_STARTPT, testGetStartPtEndPt)
    ON_BN_CLICKED(ARXDBG_BN_PTATPARAM, testGetPtAtParam)
    ON_BN_CLICKED(ARXDBG_BN_PARAMATPT, testGetParamAtPt)
    ON_BN_CLICKED(ARXDBG_BN_DISTATPARAM, testGetDistAtParam)
    ON_BN_CLICKED(ARXDBG_BN_PARAMATDIST, testGetParamAtDist)
    ON_BN_CLICKED(ARXDBG_BN_DISTATPT, testGetDistAtPt)
    ON_BN_CLICKED(ARXDBG_BN_PTATDIST, testGetPtAtDist)
    ON_BN_CLICKED(ARXDBG_BN_DERIV, testGetDerivs)
    ON_BN_CLICKED(ARXDBG_BN_DERIV2, testGetDerivs2)
    ON_BN_CLICKED(ARXDBG_BN_CLOSESTPTTO, testGetClosestPtTo)
    ON_BN_CLICKED(ARXDBG_BN_CLOSESTPTTO2, testGetClosestPtTo2)
    ON_BN_CLICKED(ARXDBG_BN_ORTHOPROJECTED, testGetOrthoProjectedCurve)
    ON_BN_CLICKED(ARXDBG_BN_PROJECTED, testGetProjectedCurve)
    ON_BN_CLICKED(ARXDBG_BN_OFFSETCURVES, testGetOffsetCurves)
    ON_BN_CLICKED(ARXDBG_BN_SPLINE, testGetSpline)
    ON_BN_CLICKED(ARXDBG_BN_SPLITCURVES, testGetSplitCurves)
    ON_BN_CLICKED(ARXDBG_BN_SPLITCURVES2, testGetSplitCurves2)
    ON_BN_CLICKED(ARXDBG_BN_EXTEND, testExtend)
    ON_BN_CLICKED(ARXDBG_BN_EXTEND2, testExtend2)
    ON_BN_CLICKED(ARXDBG_BN_AREA, testGetArea)
    ON_BN_CLICKED(ARXDBG_BN_CLOSED, testIsClosedPeriodicPlanar)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiDlgTestCurve message handlers

/****************************************************************************
**
**  ArxDbgUiDlgTestCurve::selectCurve
**
**  **jma
**
*************************************/

AcDbCurve*
ArxDbgUiDlgTestCurve::selectCurve()
{
    AcDbCurve* curve;

    ArxDbgUiPrEntity prEnt(_T("Select AcDbCurve"), nullptr);
	prEnt.addAllowedClass(AcDbCurve::desc());
    prEnt.setAllowNone(true);

    if (prEnt.go() != ArxDbgUiPrBase::kOk)
        return nullptr;
    else {
        Acad::ErrorStatus es = acdbOpenObject(curve, prEnt.objectId(), AcDb::kForRead);
        if (es == Acad::eOk)
            return curve;
        else
            return nullptr;
    }
}

/****************************************************************************
**
**  ArxDbgUiDlgTestCurve::printInfo
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgTestCurve::printInfo(LPCTSTR tagStr, LPCTSTR valStr)
{
    acutPrintf(_T("\n%-20s : %s"), tagStr, valStr);
}

/****************************************************************************
**
**  ArxDbgUiDlgTestCurve::makeRay
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgTestCurve::makeRay(const AcGePoint3d& origin, const AcGeVector3d& dir, int color)
{
    if (dir.isZeroLength()) {
        acutPrintf(_T("\nSkipping zero length vector (color = %d)"), color);
        return;
    }

    AcDbRay* ray = new AcDbRay;
    ray->setBasePoint(origin);
    ray->setUnitDir(dir.normal());
    ray->setColorIndex(color);
    ArxDbgUtils::addToCurrentSpaceAndClose(ray);
}

/****************************************************************************
**
**  ArxDbgUiDlgTestCurve::makePt
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgTestCurve::makePt(const AcGePoint3d& pt, int color)
{
	int mode = 0;
	getSysVar(_T("pdmode"), mode);
	if (mode == 0)
		setSysVar(_T("pdmode"), 99);

    AcDbPoint* ptEnt = new AcDbPoint(pt);
    ptEnt->setColorIndex(color);
    ArxDbgUtils::addToCurrentSpaceAndClose(ptEnt);
}

/****************************************************************************
**
**  ArxDbgUiDlgTestCurve::testGetPlane
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgTestCurve::testGetPlane()
{
	BeginEditorCommand();

    acutPrintf(_T("\nTesting getPlane(AcGePlane& plane, AcDb::Planarity& type)...\n"));

    while (1) {
        AcDbCurve* curve = selectCurve();
        if (curve == NULL) {
			CompleteEditorCommand();
            return;
		}

        AcGePlane plane;
        AcDb::Planarity type;
        Acad::ErrorStatus es = curve->getPlane(plane, type);
        if (es == Acad::eOk) {
            CString planeTypeStr;
            if (type == AcDb::kNonPlanar)
                planeTypeStr = _T("Non Planar");
            else if (type == AcDb::kPlanar)
                planeTypeStr = _T("Planar");
            else if (type == AcDb::kLinear)
                planeTypeStr = _T("Linear");
            else {
                ASSERT(0);
                planeTypeStr = _T("*UNKNOWN*");
            }

            printInfo(_T("PLANE TYPE"), planeTypeStr);

            AcGePoint3d origin;
            AcGeVector3d uVec, vVec;
            plane.get(origin, uVec, vVec);

            CString str;
            printInfo(_T("ORIGIN"), ArxDbgUtils::ptToStr(origin, str));
            printInfo(_T("U VEC"), ArxDbgUtils::vectorToStr(uVec, str));
            printInfo(_T("V VEC"), ArxDbgUtils::vectorToStr(vVec, str));

            makeRay(origin, uVec, 1);
            makeRay(origin, vVec, 2);
        }
        else
            ArxDbgUtils::rxErrorMsg(es);

        curve->close();
    }

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxDbgUiDlgTestCurve::testGetStartParamEndParam
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgTestCurve::testGetStartParamEndParam()
{
	BeginEditorCommand();

    acutPrintf(_T("\nTesting getStartParam(double& param)..."));
    acutPrintf(_T("\nTesting getEndParam(double& param)..."));

    Acad::ErrorStatus es;
    CString str;
    double param;

    while (1) {
        AcDbCurve* curve = selectCurve();
        if (curve == NULL) {
			CompleteEditorCommand();
            return;
		}

        es = curve->getStartParam(param);
        if (es == Acad::eOk) {
            printInfo(_T("START PARAM (DOUBLE)"), ArxDbgUtils::doubleToStr(param, str));
            printInfo(_T("START PARAM (ANGLE)"), ArxDbgUtils::angleToStr(param, str));
        }
        else
            printInfo(_T("START PARAM"), ArxDbgUtils::rxErrorStr(es));

        es = curve->getEndParam(param);
        if (es == Acad::eOk) {
            printInfo(_T("END PARAM (DOUBLE)"), ArxDbgUtils::doubleToStr(param, str));
            printInfo(_T("END PARAM (ANGLE)"), ArxDbgUtils::angleToStr(param, str));
        }
        else
            printInfo(_T("END PARAM"), ArxDbgUtils::rxErrorStr(es));

        curve->close();
    }

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxDbgUiDlgTestCurve::testGetStartPtEndPt
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgTestCurve::testGetStartPtEndPt()
{
	BeginEditorCommand();

    acutPrintf(_T("\nTesting getStartPoint(AcGePoint3d& startPt)..."));
    acutPrintf(_T("\nTesting getEndPoint(AcGePoint3d& endPt)..."));

    while (1) {
        AcDbCurve* curve = selectCurve();
        if (curve == NULL) {
			CompleteEditorCommand();
            return;
		}

        CString str;
        Acad::ErrorStatus es1, es2;
        AcGePoint3d startPt, endPt;
        es1 = curve->getStartPoint(startPt);
        if (es1 == Acad::eOk)
            printInfo(_T("START PT"), ArxDbgUtils::ptToStr(startPt, str));
        else
            printInfo(_T("START PT"), ArxDbgUtils::rxErrorStr(es1));

        es2 = curve->getEndPoint(endPt);
        if (es2 == Acad::eOk)
            printInfo(_T("END PT"), ArxDbgUtils::ptToStr(endPt, str));
        else
            printInfo(_T("END PT"), ArxDbgUtils::rxErrorStr(es2));

            // if both points are the same, put out only one green point
        if ((es1 == Acad::eOk) && (es2 == Acad::eOk) && (startPt == endPt))
            makePt(startPt, 3);
        else {
                // else put out a red point for start and a yellow for end
            if (es1 == Acad::eOk)
                makePt(startPt, 1);
            if (es2 == Acad::eOk)
                makePt(endPt, 2);
        }
        curve->close();
    }

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxDbgUiDlgTestCurve::testGetPtAtParam
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgTestCurve::testGetPtAtParam()
{
	BeginEditorCommand();

    acutPrintf(_T("\nTesting getPointAtParam(double param, AcGePoint3d& point)..."));

    double param;
    Acad::ErrorStatus es;
    AcGePoint3d pt;
    CString str;

    while (1) {
        AcDbCurve* curve = selectCurve();
        if (curve == NULL) {
			CompleteEditorCommand();
            return;
		}

        printParamInterval(curve);

        if (!getCurveParam(param)) {
            curve->close();
			CompleteEditorCommand();
            return;
        }

        es = curve->getPointAtParam(param, pt);
        if (es == Acad::eOk) {
            printInfo(_T("PT"), ArxDbgUtils::ptToStr(pt, str));
            makePt(pt, 4);
        }
        else
            ArxDbgUtils::rxErrorMsg(es);

        curve->close();
    }

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxDbgUiDlgTestCurve::testGetParamAtPt
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgTestCurve::testGetParamAtPt()
{
	BeginEditorCommand();

    acutPrintf(_T("\nTesting getParamAtPoint(const AcGePoint3d& point, double& param)..."));

    ArxDbgUiPrPoint prPt(_T("Point on curve"), NULL);

    CString str;
    Acad::ErrorStatus es;
    double param;

    while (1) {
        AcDbCurve* curve = selectCurve();
        if (curve == NULL) {
			CompleteEditorCommand();
            return;
		}

        if (prPt.go() != ArxDbgUiPrBase::kOk) {
            curve->close();
			CompleteEditorCommand();
            return;
        }

        es = curve->getParamAtPoint(ArxDbgUtils::ucsToWcs(prPt.value()), param);
        if (es == Acad::eOk) {
            printInfo(_T("PARAM (DOUBLE)"), ArxDbgUtils::doubleToStr(param, str));
            printInfo(_T("PARAM (ANGLE)"), ArxDbgUtils::angleToStr(param, str));
        }
        else
            ArxDbgUtils::rxErrorMsg(es);

        curve->close();
    }

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxDbgUiDlgTestCurve::testGetDistAtParam
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgTestCurve::testGetDistAtParam()
{
	BeginEditorCommand();

    acutPrintf(_T("\nTesting getDistAtParam(double param, double& dist)..."));

    double param;
    double dist;
    Acad::ErrorStatus es;
    CString str;

    while (1) {
        AcDbCurve* curve = selectCurve();
        if (curve == NULL) {
			CompleteEditorCommand();
            return;
		}

        printParamInterval(curve);

        if (!getCurveParam(param)) {
            curve->close();
			CompleteEditorCommand();
            return;
        }

        es = curve->getDistAtParam(param, dist);
        if (es == Acad::eOk)
            printInfo(_T("DIST"), ArxDbgUtils::doubleToStr(dist, str));
        else
            ArxDbgUtils::rxErrorMsg(es);

        curve->close();
    }

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxDbgUiDlgTestCurve::testGetParamAtDist
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgTestCurve::testGetParamAtDist()
{
	BeginEditorCommand();

    acutPrintf(_T("\nTesting getParamAtDist(double dist, double& param)..."));

    ArxDbgUiPrDist prDist(_T("Distance"), NULL, ArxDbgUiPrDist::kAny);
    CString str;
    Acad::ErrorStatus es;
    double param;

    while (1) {
        AcDbCurve* curve = selectCurve();
        if (curve == NULL) {
			CompleteEditorCommand();
            return;
		}

        if (prDist.go() != ArxDbgUiPrBase::kOk) {
            curve->close();
			CompleteEditorCommand();
            return;
        }

        es = curve->getParamAtDist(prDist.value(), param);
        if (es == Acad::eOk) {
            printInfo(_T("PARAM (DOUBLE)"), ArxDbgUtils::doubleToStr(param, str));
            printInfo(_T("PARAM (ANGLE)"), ArxDbgUtils::angleToStr(param, str));
        }
        else
            ArxDbgUtils::rxErrorMsg(es);

        curve->close();
    }

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxDbgUiDlgTestCurve::testGetDistAtPt
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgTestCurve::testGetDistAtPt()
{
	BeginEditorCommand();

    acutPrintf(_T("\nTesting getDistAtPoint(const AcGePoint3d& point, double& dist)..."));

    ArxDbgUiPrPoint prPt(_T("Point on curve"), NULL);

    CString str;
    Acad::ErrorStatus es;
    double dist;

    while (1) {
        AcDbCurve* curve = selectCurve();
        if (curve == NULL) {
			CompleteEditorCommand();
            return;
		}

        if (prPt.go() != ArxDbgUiPrBase::kOk) {
            curve->close();
			CompleteEditorCommand();
            return;
        }

        es = curve->getDistAtPoint(ArxDbgUtils::ucsToWcs(prPt.value()), dist);
        if (es == Acad::eOk)
            printInfo(_T("DIST"), ArxDbgUtils::doubleToStr(dist, str));
        else
            ArxDbgUtils::rxErrorMsg(es);

        curve->close();
    }

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxDbgUiDlgTestCurve::testGetPtAtDist
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgTestCurve::testGetPtAtDist()
{
	BeginEditorCommand();

    acutPrintf(_T("\nTesting getPointAtDist(double dist, AcGePoint3d& point)..."));

    ArxDbgUiPrDist prDist(_T("Distance"), NULL, ArxDbgUiPrDist::kAny);
    CString str;
    Acad::ErrorStatus es;
    AcGePoint3d pt;

    while (1) {
        AcDbCurve* curve = selectCurve();
        if (curve == NULL) {
			CompleteEditorCommand();
            return;
		}

        if (prDist.go() != ArxDbgUiPrBase::kOk) {
            curve->close();
			CompleteEditorCommand();
            return;
        }

        es = curve->getPointAtDist(prDist.value(), pt);
        if (es == Acad::eOk) {
            printInfo(_T("PT"), ArxDbgUtils::ptToStr(pt, str));
            makePt(pt, 4);
        }
        else
            ArxDbgUtils::rxErrorMsg(es);

        curve->close();
    }

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxDbgUiDlgTestCurve::testGetDerivs
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgTestCurve::testGetDerivs()
{
	BeginEditorCommand();

    acutPrintf(_T("\nTesting getFirstDeriv(double param, AcGeVector3d& firstDeriv)..."));
    acutPrintf(_T("\nTesting getSecondDeriv(double param, AcGeVector3d& secondDeriv)..."));

    CString str;
    Acad::ErrorStatus es;
    AcGeVector3d deriv1, deriv2;
    double param;
    AcGePoint3d pt;

    while (1) {
        AcDbCurve* curve = selectCurve();
        if (curve == NULL) {
			CompleteEditorCommand();
            return;
		}

        printParamInterval(curve);

        if (!getCurveParam(param)) {
            curve->close();
			CompleteEditorCommand();
            return;
        }

        if (curve->getPointAtParam(param, pt) != Acad::eOk) {
            acutPrintf(_T("\nERROR: getPointAtParam() failed, using origin..."));
            pt = AcGePoint3d::kOrigin;
        }

        es = curve->getFirstDeriv(param, deriv1);
        if (es == Acad::eOk) {
            printInfo(_T("FIRST DERIV"), ArxDbgUtils::vectorToStr(deriv1, str));
            makeRay(pt, deriv1, 1);
        }
        else
            printInfo(_T("FIRST DERIV"), ArxDbgUtils::rxErrorStr(es));

        es = curve->getSecondDeriv(param, deriv2);
        if (es == Acad::eOk) {
            printInfo(_T("SECOND DERIV"), ArxDbgUtils::vectorToStr(deriv2, str));
            makeRay(pt, deriv2, 2);
        }
        else
            printInfo(_T("SECOND DERIV"), ArxDbgUtils::rxErrorStr(es));

        curve->close();
    }

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxDbgUiDlgTestCurve::testGetDerivs2
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgTestCurve::testGetDerivs2()
{
	BeginEditorCommand();

    acutPrintf(_T("\nTesting getFirstDeriv(const AcGePoint3d& point, AcGeVector3d& firstDeriv)..."));
    acutPrintf(_T("\nTesting getSecondDeriv(const AcGePoint3d& point, AcGeVector3d& secondDeriv)..."));

    ArxDbgUiPrPoint prPt(_T("Point on curve"), NULL);

    CString str;
    Acad::ErrorStatus es;
    AcGeVector3d deriv1, deriv2;
    AcGePoint3d wcsPt;

    while (1) {
        AcDbCurve* curve = selectCurve();
        if (curve == NULL) {
			CompleteEditorCommand();
            return;
		}

        if (prPt.go() != ArxDbgUiPrBase::kOk) {
            curve->close();
			CompleteEditorCommand();
            return;
        }

        wcsPt = ArxDbgUtils::ucsToWcs(prPt.value());

        es = curve->getFirstDeriv(wcsPt, deriv1);
        if (es == Acad::eOk) {
            printInfo(_T("FIRST DERIV"), ArxDbgUtils::vectorToStr(deriv1, str));
            makeRay(wcsPt, deriv1, 1);
        }
        else
            printInfo(_T("FIRST DERIV"), ArxDbgUtils::rxErrorStr(es));

        es = curve->getSecondDeriv(wcsPt, deriv2);
        if (es == Acad::eOk) {
            printInfo(_T("SECOND DERIV"), ArxDbgUtils::vectorToStr(deriv2, str));
            makeRay(wcsPt, deriv2, 2);
        }
        else
            printInfo(_T("SECOND DERIV"), ArxDbgUtils::rxErrorStr(es));

        curve->close();
    }

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxDbgUiDlgTestCurve::testGetClosestPtTo
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgTestCurve::testGetClosestPtTo()
{
	BeginEditorCommand();

    acutPrintf(_T("\nTesting getClosestPointTo(const AcGePoint3d& givenPoint, AcGePoint3d& pointOnCurve, Adesk::Boolean extend = Adesk::kFalse)..."));

    ArxDbgUiPrPoint prPt(_T("Point"), NULL);

    CString str;
    Acad::ErrorStatus es;
    AcGePoint3d pt;

    while (1) {
        AcDbCurve* curve = selectCurve();
        if (curve == NULL) {
			CompleteEditorCommand();
            return;
		}

        if (prPt.go() != ArxDbgUiPrBase::kOk) {
            curve->close();
			CompleteEditorCommand();
            return;
        }

        es = curve->getClosestPointTo(ArxDbgUtils::ucsToWcs(prPt.value()), pt);
        if (es == Acad::eOk) {
            printInfo(_T("PT"), ArxDbgUtils::ptToStr(pt, str));
            makePt(pt, 4);
        }
        else
            ArxDbgUtils::rxErrorMsg(es);

        curve->close();
    }

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxDbgUiDlgTestCurve::testGetClosestPtTo2
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgTestCurve::testGetClosestPtTo2()
{
	BeginEditorCommand();

    acutPrintf(_T("\nTesting getClosestPointTo(const AcGePoint3d&  givenPoint,"));
    acutPrintf(_T("\n                const AcGeVector3d& normal, AcGePoint3d& pointOnCurve,"));
    acutPrintf(_T("\n                Adesk::Boolean extend)..."));

    ArxDbgUiPrPoint prPt(_T("Point"), NULL);
    AcGePoint3d tmpPt;
    getSysVar(_T("viewdir"), tmpPt);
    AcGeVector3d viewdir = ArxDbgUtils::ucsToWcs(tmpPt.asVector());

    CString str;
    Acad::ErrorStatus es;
    AcGePoint3d pt;

    while (1) {
        AcDbCurve* curve = selectCurve();
        if (curve == NULL) {
			CompleteEditorCommand();
            return;
		}

        if (prPt.go() != ArxDbgUiPrBase::kOk) {
            curve->close();
			CompleteEditorCommand();
            return;
        }

        es = curve->getClosestPointTo(ArxDbgUtils::ucsToWcs(prPt.value()), viewdir, pt);
        if (es == Acad::eOk) {
            printInfo(_T("PT"), ArxDbgUtils::ptToStr(pt, str));
            makePt(pt, 4);
        }
        else
            ArxDbgUtils::rxErrorMsg(es);

        curve->close();
    }

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxDbgUiDlgTestCurve::testGetOrthoProjectedCurve
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgTestCurve::testGetOrthoProjectedCurve()
{
	BeginEditorCommand();

    acutPrintf(_T("\nTesting getOrthoProjectedCurve()..."));
    acutPrintf(_T("\nProjecting onto current UCS plane..."));

    Acad::ErrorStatus es;

    AcGePlane projPlane = ArxDbgUtils::getUcsPlane(acdbHostApplicationServices()->workingDatabase());

    while (1) {
        AcDbCurve* curve = selectCurve();
        if (curve == NULL) {
			CompleteEditorCommand();
            return;
		}
    
        AcDbCurve* projCurve = NULL;
        es = curve->getOrthoProjectedCurve(projPlane, projCurve);
        if (es == Acad::eOk) {
            projCurve->setColorIndex(1);
            ArxDbgUtils::addToCurrentSpaceAndClose(projCurve);
        }
        else
            ArxDbgUtils::rxErrorMsg(es);

        curve->close();
    }

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxDbgUiDlgTestCurve::testGetProjectedCurve
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgTestCurve::testGetProjectedCurve()
{
	BeginEditorCommand();

    acutPrintf(_T("\nTesting getProjectedCurve()..."));
    acutPrintf(_T("\nProjecting onto current UCS plane with VIEWDIR as projection direction..."));

    Acad::ErrorStatus es;

    AcGePlane projPlane = ArxDbgUtils::getUcsPlane(acdbHostApplicationServices()->workingDatabase());
    AcGePoint3d tmpPt;
    getSysVar(_T("viewdir"), tmpPt);
    AcGeVector3d viewdir = ArxDbgUtils::ucsToWcs(tmpPt.asVector());

    while (1) {
        AcDbCurve* curve = selectCurve();
        if (curve == NULL) {
			CompleteEditorCommand();
            return;
		}
    
        AcDbCurve* projCurve = NULL;
        es = curve->getProjectedCurve(projPlane, viewdir, projCurve);
        if (es == Acad::eOk) {
            projCurve->setColorIndex(1);
            ArxDbgUtils::addToCurrentSpaceAndClose(projCurve);
        }
        else
            ArxDbgUtils::rxErrorMsg(es);

        curve->close();
    }

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxDbgUiDlgTestCurve::testGetOffsetCurves
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgTestCurve::testGetOffsetCurves()
{
	BeginEditorCommand();

    acutPrintf(_T("\nTesting getOffsetCurves(double offsetDist, AcDbVoidPtrArray& offsetCurves)..."));

    ArxDbgUiPrDist prDist(_T("Offset Distance"), NULL, ArxDbgUiPrDist::kAny);
    CString str;
    Acad::ErrorStatus es;
    AcDbVoidPtrArray newEnts;

    while (1) {
        AcDbCurve* curve = selectCurve();
        if (curve == NULL) {
			CompleteEditorCommand();
            return;
		}

        if (prDist.go() != ArxDbgUiPrBase::kOk) {
            curve->close();
			CompleteEditorCommand();
            return;
        }

        newEnts.setLogicalLength(0);    // reset for each loop
        es = curve->getOffsetCurves(prDist.value(), newEnts);
        if (es == Acad::eOk) {
            for (void *pVoid : newEnts) {
                AcDbEntity* ent = static_cast<AcDbEntity*>(pVoid);
                if (ent) {
                    ent->setColorIndex(1);
                    ArxDbgUtils::addToCurrentSpaceAndClose(ent);
                }
            }
        }
        else
            ArxDbgUtils::rxErrorMsg(es);

        curve->close();
    }

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxDbgUiDlgTestCurve::testGetSpline
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgTestCurve::testGetSpline()
{
	BeginEditorCommand();

    acutPrintf(_T("\nTesting getSpline(AcDbSpline*& spline)..."));

    Acad::ErrorStatus es;
    AcDbSpline* spline;

    while (1) {
        AcDbCurve* curve = selectCurve();
        if (curve == NULL) {
			CompleteEditorCommand();
            return;
		}

        es = curve->getSpline(spline);
        if (es == Acad::eOk) {
            spline->setColorIndex(1);
            ArxDbgUtils::addToCurrentSpaceAndClose(spline);
        }
        else
            ArxDbgUtils::rxErrorMsg(es);

        curve->close();
    }

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxDbgUiDlgTestCurve::testGetSplitCurves
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgTestCurve::testGetSplitCurves()
{
	BeginEditorCommand();

    acutPrintf(_T("\nTesting getSplitCurves(const AcGeDoubleArray& params, AcDbVoidPtrArray& curveSegments)..."));

    Acad::ErrorStatus es;
    AcDbVoidPtrArray curveSegs;
    AcDbCurve* tmpCurve;
    AcGeDoubleArray params;

    while (1) {
        AcDbCurve* curve = selectCurve();
        if (curve == NULL) {
			CompleteEditorCommand();
            return;
		}

        printParamInterval(curve);

        params.setLogicalLength(0);    // reset for each loop
        if (!getCurveParams(params)) {
            curve->close();
			CompleteEditorCommand();
            return;
        }

        es = curve->getSplitCurves(params, curveSegs);
        if (es == Acad::eOk) {
                // walk through resultant curves and add them to the database
            int color = 1;
            for (void *pVoid : curveSegs) {
                tmpCurve = static_cast<AcDbCurve*>(pVoid);
                if (tmpCurve) {
                    tmpCurve->setColorIndex(color++);
                    ArxDbgUtils::addToCurrentSpaceAndClose(tmpCurve);
                }
            }
            curveSegs.setLogicalLength(0);
        }
        else {
            ArxDbgUtils::rxErrorMsg(es);

                // even in error condition, some curves may have been allocated
            for (void *pVoid : curveSegs) {
                tmpCurve = static_cast<AcDbCurve*>(pVoid);
                delete tmpCurve;
            }
            curveSegs.setLogicalLength(0);
        }

        curve->close();
    }

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxDbgUiDlgTestCurve::testGetSplitCurves2
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgTestCurve::testGetSplitCurves2()
{
	BeginEditorCommand();

    acutPrintf(_T("\nTesting getSplitCurves(const AcGePoint3dArray& points, AcDbVoidPtrArray& curveSegments)..."));

    Acad::ErrorStatus es;
    AcDbVoidPtrArray curveSegs;
    AcDbCurve* tmpCurve;
    AcGePoint3dArray pts;

    while (1) {
        AcDbCurve* curve = selectCurve();
        if (curve == NULL) {
			CompleteEditorCommand();
            return;
		}

        pts.setLogicalLength(0);    // reset for each loop
        if (!getCurvePts(pts)) {
            curve->close();
			CompleteEditorCommand();
            return;
        }

        es = curve->getSplitCurves(pts, curveSegs);
        if (es == Acad::eOk) {
                // walk through resultant curves and add them to the database
            int color = 1;
            for (void *pVoid : curveSegs) {
                tmpCurve = static_cast<AcDbCurve*>(pVoid);
                if (tmpCurve) {
                    tmpCurve->setColorIndex(color++);
                    ArxDbgUtils::addToCurrentSpaceAndClose(tmpCurve);
                }
            }
            curveSegs.setLogicalLength(0);
        }
        else {
            ArxDbgUtils::rxErrorMsg(es);

                // even in error condition, some curves may have been allocated
            for (void *pVoid : curveSegs) {
                tmpCurve = static_cast<AcDbCurve*>(pVoid);
                delete tmpCurve;
            }
            curveSegs.setLogicalLength(0);
        }

        curve->close();
    }

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxDbgUiDlgTestCurve::testExtend
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgTestCurve::testExtend()
{
	BeginEditorCommand();

    acutPrintf(_T("\nTesting extend(double toNewParam)..."));

    Acad::ErrorStatus es;
    double param;

    while (1) {
        AcDbCurve* curve = selectCurve();
        if (curve == NULL) {
			CompleteEditorCommand();
            return;
		}

        printParamInterval(curve);

        if (!getCurveParam(param)) {
            curve->close();
			CompleteEditorCommand();
            return;
        }

        if (curve->upgradeOpen() == Acad::eOk) {
            es = curve->extend(param);
            if (es != Acad::eOk)
                ArxDbgUtils::rxErrorMsg(es);
        }
        else
            acutPrintf(_T("\nERROR: couldn't open curve for write!"));

        curve->close();
    }

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxDbgUiDlgTestCurve::testExtend2
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgTestCurve::testExtend2()
{
	BeginEditorCommand();

    acutPrintf(_T("\nTesting extend(Adesk::Boolean fromStart, const AcGePoint3d& toPt)..."));

    ArxDbgUiPrPoint prPt(_T("Point to extend to"), NULL);

    Acad::ErrorStatus es;
    bool fromStart;

    while (1) {
        AcDbCurve* curve = selectCurve();
        if (curve == NULL) {
			CompleteEditorCommand();
            return;
		}

        if (ArxDbgUtils::yesNoPromptDef(_T("Extend from start "), fromStart, true) == ArxDbgUiPrBase::kCancel) {
            curve->close();
			CompleteEditorCommand();
            return;
        }

        if (prPt.go() != ArxDbgUiPrBase::kOk) {
            curve->close();
			CompleteEditorCommand();
            return;
        }

        if (curve->upgradeOpen() == Acad::eOk) {
            es = curve->extend(fromStart, ArxDbgUtils::ucsToWcs(prPt.value()));
            if (es != Acad::eOk)
                ArxDbgUtils::rxErrorMsg(es);
        }
        else
            acutPrintf(_T("\nERROR: couldn't open curve for write!"));

        curve->close();
    }

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxDbgUiDlgTestCurve::testGetArea
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgTestCurve::testGetArea()
{
	BeginEditorCommand();

    acutPrintf(_T("\nTesting getArea()..."));

    Acad::ErrorStatus es;
    CString str;
    double area;

    while (1) {
        AcDbCurve* curve = selectCurve();
        if (curve == NULL) {
			CompleteEditorCommand();
            return;
		}

        es = curve->getArea(area);
        if (es == Acad::eOk)
            acutPrintf(_T("\nAREA: %s"), ArxDbgUtils::doubleToStr(area, str));
        else
            ArxDbgUtils::rxErrorMsg(es);

        curve->close();
    }

	CompleteEditorCommand();
}

/****************************************************************************
**
**  ArxDbgUiDlgTestCurve::testIsClosedPeriodicPlanar
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgTestCurve::testIsClosedPeriodicPlanar()
{
	BeginEditorCommand();

    acutPrintf(_T("\nTesting isClosed(), isPeriodic(), isPlanar()..."));

    AcDbCurve* curve = selectCurve();
    if (curve) {
        CString str;
        acutPrintf(_T("\nIS CLOSED:   %s"), ArxDbgUtils::booleanToStr(curve->isClosed(), str));
        acutPrintf(_T("\nIS PERIODIC: %s"), ArxDbgUtils::booleanToStr(curve->isPeriodic(), str));
        acutPrintf(_T("\nIS PLANAR:   %s"), ArxDbgUtils::booleanToStr(curve->isPlanar(), str));

        curve->close();
    }

	CompleteEditorCommand();
}


/****************************************************************************
**
**  ArxDbgUiDlgTestCurve::getCurvePts
**      this function purposely allows no points to be entered just to thest
**  what the API will do if it gets no points
**
**  **jma
**
*************************************/

BOOL
ArxDbgUiDlgTestCurve::getCurvePts(AcGePoint3dArray& pts)
{
    ArxDbgUiPrPoint prPt(_T("Point on curve"), NULL);
    prPt.setAllowNone(TRUE);
    ArxDbgUiPrBase::Status stat;

    while (1) {
        stat = prPt.go();
        if (stat == ArxDbgUiPrBase::kOk)
            pts.append(ArxDbgUtils::ucsToWcs(prPt.value()));
        else if (stat == ArxDbgUiPrBase::kNone)    // done inputting points
            return TRUE;
        else
            return FALSE;
    }
}

/****************************************************************************
**
**  ArxDbgUiDlgTestCurve::getCurveParams
**      this function purposely allows no params to be entered just to thest
**  what the API will do if it gets no params
**
**  **jma
**
*************************************/

BOOL
ArxDbgUiDlgTestCurve::getCurveParams(AcGeDoubleArray& params)
{
    bool asAngles;
    if (ArxDbgUtils::yesNoPromptDef(_T("Input params as angles "), asAngles, true) == ArxDbgUiPrBase::kCancel)
        return FALSE;

    ArxDbgUiPrBase::Status stat;

    if (asAngles) {
        ArxDbgUiPrAngle prParamAng(_T("Params of curve"), NULL, ArxDbgUiPrAngle::kAny);
        prParamAng.setAllowNone(true);

        while (1) {
            stat = prParamAng.go();
            if (stat == ArxDbgUiPrBase::kOk)
                params.append(prParamAng.value());
            else if (stat == ArxDbgUiPrBase::kNone)    // done inputting params
                return TRUE;
            else
                return FALSE;
        }
    }
    else {
        ArxDbgUiPrDist prParam(_T("Params of curve"), NULL, ArxDbgUiPrDist::kAny);
        prParam.setAllowNone(true);

        while (1) {
            stat = prParam.go();
            if (stat == ArxDbgUiPrBase::kOk)
                params.append(prParam.value());
            else if (stat == ArxDbgUiPrBase::kNone)    // done inputting params
                return TRUE;
            else
                return FALSE;
        }
    }
}

/****************************************************************************
**
**  ArxDbgUiDlgTestCurve::getCurveParam
**
**  **jma
**
*************************************/

BOOL
ArxDbgUiDlgTestCurve::getCurveParam(double& param)
{
    bool asAngles;
    if (ArxDbgUtils::yesNoPromptDef(_T("Input param as angle "), asAngles, true) == ArxDbgUiPrBase::kCancel)
        return FALSE;

    if (asAngles) {
        ArxDbgUiPrAngle prParamAng(_T("Param of curve"), NULL, ArxDbgUiPrAngle::kAny);
        if (prParamAng.go() == ArxDbgUiPrBase::kOk) {
            param = prParamAng.value();
            return TRUE;
        }
    }
    else {
        ArxDbgUiPrDist prParam(_T("Param of curve"), NULL, ArxDbgUiPrDist::kAny);
        if (prParam.go() == ArxDbgUiPrBase::kOk) {
            param = prParam.value();
            return TRUE;
        }
    }
    return FALSE;
}

/****************************************************************************
**
**  ArxDbgUiDlgTestCurve::printParamInterval
**
**  **jma
**
*************************************/

void
ArxDbgUiDlgTestCurve::printParamInterval(AcDbCurve* curve)
{
    double startParam, endParam;
    CString str, str2;

    if ((curve->getStartParam(startParam) == Acad::eOk) && (curve->getEndParam(endParam) == Acad::eOk)) {
        acutPrintf(_T("\nParam Interval: (%s --> %s) (DOUBLE)"),
                ArxDbgUtils::doubleToStr(startParam, str),
                ArxDbgUtils::doubleToStr(endParam, str2));
        acutPrintf(_T("\nParam Interval: (%s --> %s) (ANGLE)"),
                ArxDbgUtils::angleToStr(startParam, str),
                ArxDbgUtils::angleToStr(endParam, str2));
    }
    else
        acutPrintf(_T("\nParam Interval: UNSPECIFIED"));
}


