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

#include "XformTest.h"
#include "ArxDbgUtils.h"
#include "ArxDbgUtilsGe.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**    XformDbox::XformDbox    (constructor)
**
**    **jma
**
*************************************/

XformDbox::XformDbox(CWnd* pParent)
:    CDialog(_T("ARXDBG_DLG_XFORM"), pParent)
{
    //{{AFX_DATA_INIT(XformDbox)
    m_rotateType = kRbUcsZAxis;
    m_transType = kRbFromTo;
    m_xformCopy = FALSE;
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**    XformDbox::DoModal
**
**    **jma
**
*************************************/

INT_PTR
XformDbox::DoModal()
{
    INT_PTR retCode;

    while (1) {
        retCode = CDialog::DoModal();
        if (retCode == ARXDBG_BN_ROTATE)
            rotate();
        else if (retCode == ARXDBG_BN_MOVE)
            move();
        else if (retCode == ARXDBG_BN_SCALE)
            scale();
        else if (retCode == ARXDBG_BN_MIRROR)
            mirror();
        else if (retCode == ARXDBG_BN_WCS_ORIGIN)
            wcsOrigin();
        else
            return(IDOK);

        ArxDbgUtils::debugPause(NULL);    // allow user to see changes before returning dialog
    }
}

/****************************************************************************
**
**    XformDbox::OnCmdMsg
**
**    **jma
**
*************************************/

BOOL
XformDbox::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
    m_buttonId = nID;
    return(CDialog::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo));
}

/****************************************************************************
**
**    XformDbox::DoDataExchange
**
**    **jma
**
*************************************/

void
XformDbox::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(XformDbox)
    DDX_Radio(pDX, ARXDBG_RB_UCS_X, m_rotateType);
    DDX_Radio(pDX, ARXDBG_RB_FROM_TO, m_transType);
    DDX_Check(pDX, ARXDBG_CB_XFORM_COPY, m_xformCopy);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// XformDbox message map

BEGIN_MESSAGE_MAP(XformDbox, CDialog)
    //{{AFX_MSG_MAP(XformDbox)
    ON_BN_CLICKED(ARXDBG_BN_MIRROR, OnButtonClicked)
    ON_BN_CLICKED(ARXDBG_BN_MOVE, OnButtonClicked)
    ON_BN_CLICKED(ARXDBG_BN_ROTATE, OnButtonClicked)
    ON_BN_CLICKED(ARXDBG_BN_SCALE, OnButtonClicked)
    ON_BN_CLICKED(ARXDBG_BN_WCS_ORIGIN, OnButtonClicked)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// XformDbox message handlers


/****************************************************************************
**
**    XformDbox::OnButtonClicked
**
**    **jma
**
*************************************/

void
XformDbox::OnButtonClicked() 
{
    UpdateData(TRUE);
    EndDialog(m_buttonId);
}

/****************************************************************************
**
**    XformDbox::rotate
**
**    **jma
**
*************************************/

void
XformDbox::rotate()
{
    AcGeMatrix3d xform;
    AcDbEntity* obj;
    AcGeVector3d axis;

    if ((obj = ArxDbgUtils::selectEntity(NULL, AcDb::kForRead)) == NULL)
        return;

    if (m_rotateType == kRbUcsXAxis)
        axis = ArxDbgUtils::getUcsXAxis(acdbHostApplicationServices()->workingDatabase());
    else if (m_rotateType == kRbUcsYAxis)
        axis = ArxDbgUtils::getUcsYAxis(acdbHostApplicationServices()->workingDatabase());
    else if (m_rotateType == kRbUcsZAxis)
        axis = ArxDbgUtils::getUcsZAxis(acdbHostApplicationServices()->workingDatabase());
    else if (m_rotateType == kRbEcsZAxis) {
        AcGeMatrix3d ecsMat;
        obj->getEcs(ecsMat);
        AcGePoint3d origin;
        AcGeVector3d xAxis;
        AcGeVector3d yAxis;
        ecsMat.getCoordSystem(origin, xAxis, yAxis, axis);

            // temporarily print out normal vector for debugging
        ArxDbgUtils::stopAlertBox(_T("Doesn't work correctly yet...\nWaiting on AcDbEntity::ecs()"));
        CString str;
        acutPrintf(_T("\nECS X-AXIS: %s"), ArxDbgUtils::vectorToStr(xAxis, str));
        acutPrintf(_T("\nECS Y-AXIS: %s"), ArxDbgUtils::vectorToStr(yAxis, str));
        acutPrintf(_T("\nECS Z-AXIS: %s"), ArxDbgUtils::vectorToStr(axis, str));
    }
    else {
        ASSERT(0);
    }

    ArxDbgUiPrPoint prBasePt(_T("Base point"), NULL);
    ArxDbgUiPrAngleDef prRotAng(_T("Rotation angle "), NULL, ArxDbgUiPrAngle::kAny, ArxDbgUtilsGe::kRad45);

    if ((prBasePt.go() == ArxDbgUiPrBase::kOk) &&
        (prRotAng.go() == ArxDbgUiPrBase::kOk)) {
        xform.setToRotation(prRotAng.value(), axis,
                        ArxDbgUtils::ucsToWcs(prBasePt.value()));
        doXform(obj, xform);
    }
    obj->close();
}

/****************************************************************************
**
**    XformDbox::scale
**
**    **jma
**
*************************************/

void
XformDbox::scale()
{
    AcGeMatrix3d xform;
    AcDbEntity* obj;

    if ((obj = ArxDbgUtils::selectEntity(NULL, AcDb::kForRead)) == NULL)
        return;

    ArxDbgUiPrPoint prBasePt(_T("Base point"), NULL);
    ArxDbgUiPrDist prScale(_T("Scale multiplier"), NULL, ArxDbgUiPrDist::kNoNegNoZero);

    if ((prBasePt.go() == ArxDbgUiPrBase::kOk) &&
        (prScale.go() == ArxDbgUiPrBase::kOk)) {
        xform.setToScaling(prScale.value(),
                        ArxDbgUtils::ucsToWcs(prBasePt.value()));
        doXform(obj, xform);
    }
    obj->close();
}

/****************************************************************************
**
**    XformDbox::move
**
**    **jma
**
*************************************/

void
XformDbox::move()
{
    AcGeMatrix3d xform;
    AcDbEntity* obj;
    AcGeVector3d transVec;

    if ((obj = ArxDbgUtils::selectEntity(NULL, AcDb::kForRead)) == NULL)
        return;

    if (m_transType == kRbFromTo) {
        ArxDbgUiPrPoint prBasePt(_T("Base point"), NULL);
        if (prBasePt.go() != ArxDbgUiPrBase::kOk) {
            obj->close();
            return;
        }
        ArxDbgUiPrPoint prToPt(_T("To point"), NULL, prBasePt.value());
        if (prToPt.go() != ArxDbgUiPrBase::kOk) {
            obj->close();
            return;
        }
        transVec = (ArxDbgUtils::ucsToWcs(prToPt.value()) -
                            ArxDbgUtils::ucsToWcs(prBasePt.value()));
    }
    else {
        ArxDbgUiPrPoint prDisp(_T("Displacement"), NULL);
        if (prDisp.go() != ArxDbgUiPrBase::kOk) {
            obj->close();
            return;
        }
        transVec = ArxDbgUtils::ucsToWcs(prDisp.value().asVector());
    }

    xform.setToTranslation(transVec);
    doXform(obj, xform);
    obj->close();
}

/****************************************************************************
**
**    XformDbox::mirror
**
**    **jma
**
*************************************/

void
XformDbox::mirror()
{
    AcGeMatrix3d xform;
    AcDbEntity* obj;

    if ((obj = ArxDbgUtils::selectEntity(NULL, AcDb::kForRead)) == NULL)
        return;

    ArxDbgUiPrPoint prPt1(_T("First point on mirror line"), NULL);
    if (prPt1.go() != ArxDbgUiPrBase::kOk) {
        obj->close();
        return;
    }
    ArxDbgUiPrPoint prPt2(_T("Second point on mirror line"), NULL, prPt1.value());
    if (prPt2.go() != ArxDbgUiPrBase::kOk) {
        obj->close();
        return;
    }

    AcGeLine3d mirrorLine(ArxDbgUtils::ucsToWcs(prPt1.value()),
                            ArxDbgUtils::ucsToWcs(prPt2.value()));

    xform.setToMirroring(mirrorLine);
    doXform(obj, xform);
    obj->close();
}

/****************************************************************************
**
**    XformDbox::wcsOrigin
**        this is what you have to do before making a block definition
**    from existing entities.
**
**    **jma
**
*************************************/

void
XformDbox::wcsOrigin()
{
    AcGeMatrix3d xform;
    AcDbEntity* obj;

    if ((obj = ArxDbgUtils::selectEntity(NULL, AcDb::kForRead)) == NULL)
        return;

    ArxDbgUiPrPoint prBasePt(_T("Base point"), NULL);
    if (prBasePt.go() != ArxDbgUiPrBase::kOk) {
        obj->close();
        return;
    }

    ArxDbgUtils::getUcsToWcsOriginMatrix(xform,
                        ArxDbgUtils::ucsToWcs(prBasePt.value()), acdbHostApplicationServices()->workingDatabase());
    doXform(obj, xform);
    obj->close();
}

/****************************************************************************
**
**    XformDbox::doXform
**
**    **jma
**
*************************************/

void
XformDbox::doXform(AcDbEntity* ent, const AcGeMatrix3d& m)
{
    if (m_xformCopy == FALSE) {
        Acad::ErrorStatus es = ent->upgradeOpen();
        if (es == Acad::eOk) {
            es = ent->transformBy(m);
            if (es != Acad::eOk)
                ArxDbgUtils::rxErrorAlert(es);
        }
        else
            ArxDbgUtils::rxErrorAlert(es);
    }
    else {
        AcDbObjectId ownerBlockId = ent->blockId();    // compiler complains!
        if (ArxDbgUtils::cloneAndXformObjects(acdbHostApplicationServices()->workingDatabase(), ent->objectId(),
                            ownerBlockId, m, true) != Acad::eOk)
            ArxDbgUtils::stopAlertBox(_T("ERROR: Couldn't clone entity!"));
    }
}

