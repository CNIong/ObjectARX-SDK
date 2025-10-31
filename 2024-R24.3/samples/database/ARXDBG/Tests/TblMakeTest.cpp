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

#include "TblMakeTest.h"
#include "ArxDbgUtils.h"
#include "ArxDbgSelSet.h"
#include "ArxDbgUtilsGe.h"
#include "AcadStr.h"
#include "acedCmdNF.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/****************************************************************************
**
**    cmdTestTblMake:
**
**    **jma
**
*************************************/

void
cmdTestTblMake()
{
    TblMakeDbox dbox(acedGetAcadDwgView());
    dbox.DoModal();
}

/****************************************************************************
**
**    TblMakeDbox::TblMakeDbox    (constructor)
**
**    **jma
**
*************************************/

TblMakeDbox::TblMakeDbox(CWnd* pParent)
:    CDialog(_T("ARXDBG_DLG_TBLMAKE"), pParent)
{
    //{{AFX_DATA_INIT(TblMakeDbox)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**    TblMakeDbox::DoModal
**
**    **jma
**
*************************************/

INT_PTR
TblMakeDbox::DoModal()
{
    INT_PTR retCode;

    while (1) {
        retCode = CDialog::DoModal();
        if (retCode == ARXDBG_BN_ANONBLOCK)
            makeAnonymousBlock();
        else if (retCode == ARXDBG_BN_APPID)
            makeAppid();
        else if (retCode == ARXDBG_BN_BLOCK)
            makeNamedBlock();
        else if (retCode == ARXDBG_BN_DIMSTYLE)
            makeDimstyle();
        else if (retCode == ARXDBG_BN_LAYER)
            makeLayer();
        else if (retCode == ARXDBG_BN_LINETYPE)
            makeLinetype();
        else if (retCode == ARXDBG_BN_TEXTSTYLE)
            makeTextstyle();
        else if (retCode == ARXDBG_BN_UCS)
            makeUcs();
        else if (retCode == ARXDBG_BN_VIEW)
            makeView();
        else if (retCode == ARXDBG_BN_VIEWPORT)
            makeViewport();
        else
            return(IDOK);

        ArxDbgUtils::debugPause(NULL);    // allow graphics to update and user to see entity
    }
}

/****************************************************************************
**
**    TblMakeDbox::OnCmdMsg
**
**    **jma
**
*************************************/

BOOL
TblMakeDbox::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
    m_buttonId = nID;
    return(CDialog::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo));
}


/****************************************************************************
**
**    TblMakeDbox::DoDataExchange
**
**    **jma
**
*************************************/

void
TblMakeDbox::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(TblMakeDbox)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// TblMakeDbox message map

BEGIN_MESSAGE_MAP(TblMakeDbox, CDialog)
    //{{AFX_MSG_MAP(TblMakeDbox)
    ON_BN_CLICKED(ARXDBG_BN_ANONBLOCK, OnButtonClicked)
    ON_BN_CLICKED(ARXDBG_BN_APPID, OnButtonClicked)
    ON_BN_CLICKED(ARXDBG_BN_BLOCK, OnButtonClicked)
    ON_BN_CLICKED(ARXDBG_BN_DIMSTYLE, OnButtonClicked)
    ON_BN_CLICKED(ARXDBG_BN_LAYER, OnButtonClicked)
    ON_BN_CLICKED(ARXDBG_BN_LINETYPE, OnButtonClicked)
    ON_BN_CLICKED(ARXDBG_BN_TEXTSTYLE, OnButtonClicked)
    ON_BN_CLICKED(ARXDBG_BN_UCS, OnButtonClicked)
    ON_BN_CLICKED(ARXDBG_BN_VIEW, OnButtonClicked)
    ON_BN_CLICKED(ARXDBG_BN_VIEWPORT, OnButtonClicked)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// TblMakeDbox message handlers

/****************************************************************************
**
**    TblMakeDbox::OnButtonClicked
**
**    **jma
**
*************************************/

void
TblMakeDbox::OnButtonClicked() 
{
    EndDialog(m_buttonId);
}

/****************************************************************************
**
**    TblMakeDbox::makeNamedBlock
**
**    **jma
**
*************************************/

void
TblMakeDbox::makeNamedBlock()
{
        // get block name and make sure they don't redefine it
        // without specifically asking to
    ArxDbgUiPrString prBlkname(_T("Block name"), FALSE);
    while (1) {
        if (prBlkname.go() == ArxDbgUiPrBase::kCancel)
            return;
        if (ArxDbgUtils::symbolExists(AcDbBlockTableRecord::desc(), prBlkname.value(),
						acdbHostApplicationServices()->workingDatabase())) {
            bool redefine;
            acutPrintf(_T("\nBlock \"%s\" already exists."), prBlkname.value());
            if (ArxDbgUtils::yesNoPromptDef(_T("Redefine it? "), redefine, false) == ArxDbgUiPrBase::kCancel)
                return;
            if (redefine == true)
                break;
        }
        else
            break;
    }
        // get the base point that defines insertion point for block
    ArxDbgUiPrPoint prBasePt(_T("Base point"), NULL);
    if (prBasePt.go() != ArxDbgUiPrBase::kOk)
        return;
    
        // now get the entities to include in the block
    ArxDbgSelSet ss;
    if (ss.userSelect() != ArxDbgSelSet::kSelected) {
        acutPrintf(_T("\nNothing selected."));
        return;
    }

    AcDbObjectId newBlkRecId;
    if (ArxDbgUtils::defineNewBlock(prBlkname.value(), newBlkRecId,
			acdbHostApplicationServices()->workingDatabase()) != Acad::eOk)
        return;

        // must transform entities to WCS origin to be correct block def
    AcGeMatrix3d xformMat;
    ArxDbgUtils::getUcsToWcsOriginMatrix(xformMat,
                            ArxDbgUtils::ucsToWcs(prBasePt.value()), acdbHostApplicationServices()->workingDatabase());

    AcDbObjectIdArray entsToClone;
    ss.asArray(entsToClone);
    if (ArxDbgUtils::cloneAndXformObjects(acdbHostApplicationServices()->workingDatabase(),
						entsToClone, newBlkRecId, xformMat, true) != Acad::eOk)
        ArxDbgUtils::stopAlertBox(_T("ERROR: Could not clone entities into block def!"));

    acutPrintf(_T("\nCreated Block \"%s\"."), prBlkname.value());
}

/****************************************************************************
**
**    TblMakeDbox::makeAnonymousBlock
**
**    **jma
**
*************************************/

void
TblMakeDbox::makeAnonymousBlock()
{
    ArxDbgUiPrPoint prBasePt(_T("Base point"), NULL);
    if (prBasePt.go() != ArxDbgUiPrBase::kOk)
        return;

        // now get the entities to select
    ArxDbgSelSet ss;
    if (ss.userSelect() != ArxDbgSelSet::kSelected) {
        acutPrintf(_T("\nNothing selected."));
        return;
    }

    TCHAR* blkName;
    AcDbObjectId newBlkRecId;
    AcDbBlockTableRecord* newBlkRec;
    if (ArxDbgUtils::defineNewAnonymousBlock(newBlkRec, newBlkRecId, acdbHostApplicationServices()->workingDatabase()) != Acad::eOk)
        return;

    newBlkRec->getName(blkName);
    newBlkRec->close();    // don't need block rec open for clone

    AcGeMatrix3d xformMat;
    ArxDbgUtils::getUcsToWcsOriginMatrix(xformMat,
                            ArxDbgUtils::ucsToWcs(prBasePt.value()), acdbHostApplicationServices()->workingDatabase());

    AcDbObjectIdArray entsToClone;
    ss.asArray(entsToClone);
    if (ArxDbgUtils::cloneAndXformObjects(acdbHostApplicationServices()->workingDatabase(), entsToClone,
                            newBlkRecId, xformMat, true) != Acad::eOk)
        ArxDbgUtils::stopAlertBox(_T("ERROR: Could not clone entities into block def!"));

    acutPrintf(_T("\nCreated Block \"%s\"."), blkName);
    acutDelString(blkName);
}

/****************************************************************************
**
**    TblMakeDbox::makeDimstyle
**
**    **jma
**
*************************************/

void
TblMakeDbox::makeDimstyle()
{
    CString symName;

    if (ArxDbgUtils::getNewSymbolName(_T("Dimstyle name"), AcDbDimStyleTableRecord::desc(), symName) != ArxDbgUiPrBase::kOk)
        return;

    AcDbDimStyleTableRecord* newRec = new AcDbDimStyleTableRecord;
    if (setSymbolName(newRec, symName) != Acad::eOk) {
        delete newRec;
        return;
    }

        // set some colors just for the fun of it
    AcCmColor color;
    color.setColorIndex(1);
    newRec->setDimclrd(color);
    color.setColorIndex(2);
    newRec->setDimclre(color);
    color.setColorIndex(3);
    newRec->setDimclrt(color);

    if (addToSymbolTableAndClose(newRec))
        acutPrintf(_T("\nCreated dimstyle: \"%s\""), symName);
    else
        acutPrintf(_T("\nERROR: Could not create dimstyle: \"%s\""), symName);
}

/****************************************************************************
**
**    TblMakeDbox::makeLayer
**
**    **jma
**
*************************************/

void
TblMakeDbox::makeLayer()
{
    CString symName;

    if (ArxDbgUtils::getNewSymbolName(_T("Layer name"), AcDbLayerTableRecord::desc(), symName) != ArxDbgUiPrBase::kOk)
        return;

        // get color in range 1 - 255, and on/off/freeze/etc.
    bool isFrozen, isOff, isLocked, isVPDFLT;
    ArxDbgUiPrIntDef prColor(_T("Color number "), NULL, ArxDbgUiPrInt::kRange, 7);
    prColor.setRange(1, 255);

    if ((prColor.go() != ArxDbgUiPrBase::kOk) ||
        (ArxDbgUtils::yesNoPromptDef(_T("Frozen "), isFrozen, false) != ArxDbgUiPrBase::kOk) ||
        (ArxDbgUtils::yesNoPromptDef(_T("Off "), isOff, false) != ArxDbgUiPrBase::kOk) ||
        (ArxDbgUtils::yesNoPromptDef(_T("Locked "), isLocked, false) != ArxDbgUiPrBase::kOk) ||
        (ArxDbgUtils::yesNoPromptDef(_T("VP default "), isVPDFLT, false) != ArxDbgUiPrBase::kOk))
        return;

    AcDbLayerTableRecord* newRec = new AcDbLayerTableRecord;
    if (setSymbolName(newRec, symName) != Acad::eOk) {
        delete newRec;
        return;
    }

    AcCmColor cmColor;
    cmColor.setColorIndex(prColor.value());
    newRec->setColor(cmColor);

    newRec->setIsFrozen(isFrozen);
    newRec->setIsOff(isOff);
    newRec->setVPDFLT(isLocked);
    newRec->setIsLocked(isVPDFLT);

    if (addToSymbolTableAndClose(newRec))
        acutPrintf(_T("\nCreated layer: \"%s\""), symName);
    else
        acutPrintf(_T("\nERROR: Could not create layer: \"%s\""), symName);
}

/****************************************************************************
**
**    TblMakeDbox::makeLinetype
**
**    **jma
**
*************************************/

void
TblMakeDbox::makeLinetype()
{
    CString symName;

    if (ArxDbgUtils::getNewSymbolName(_T("Linetype name"), AcDbLinetypeTableRecord::desc(), symName) != ArxDbgUiPrBase::kOk)
        return;

    AcDbLinetypeTableRecord* newRec = new AcDbLinetypeTableRecord;
    if (setSymbolName(newRec, symName) != Acad::eOk) {
        delete newRec;
        return;
    }

    ArxDbgUiPrString prDesc(_T("ASCII description"), TRUE);
    ArxDbgUiPrDist prPatLength(_T("Pattern length"), NULL, ArxDbgUiPrDist::kNoNegNoZero);
    ArxDbgUiPrInt prDashCount(_T("Dash count"), NULL, ArxDbgUiPrInt::kNoNegNoZero);
    if ((prDesc.go() != ArxDbgUiPrBase::kOk) ||
        (prPatLength.go() != ArxDbgUiPrBase::kOk) ||
        (prDashCount.go() != ArxDbgUiPrBase::kOk)) {
            delete newRec;
        return;
    }

    newRec->setAsciiDescription(prDesc.value());
    newRec->setPatternLength(prPatLength.value());
    newRec->setNumDashes(prDashCount.value());
    
    ArxDbgUiPrDist prDashLength(_T("Dash length"), NULL, ArxDbgUiPrDist::kAny);
    for (int i=0; i < prDashCount.value(); i++) {
        if (prDashLength.go() != ArxDbgUiPrBase::kOk) {
            delete newRec;
            return;
        }
        newRec->setDashLengthAt(i, prDashLength.value());
    }

    if (addToSymbolTableAndClose(newRec))
        acutPrintf(_T("\nAdded linetype \"%s\"."), symName);
    else
        acutPrintf(_T("\nERROR: could not add linetype \"%s\"."), symName);
}

/****************************************************************************
**
**    TblMakeDbox::makeTextstyle
**
**    **jma
**
*************************************/

void
TblMakeDbox::makeTextstyle()
{
    CString symName;

    if (ArxDbgUtils::getNewSymbolName(_T("Textstyle name"), AcDbTextStyleTableRecord::desc(), symName) != ArxDbgUiPrBase::kOk)
        return;

    AcDbTextStyleTableRecord* newRec = new AcDbTextStyleTableRecord;
    if (setSymbolName(newRec, symName) != Acad::eOk) {
        delete newRec;
        return;
    }

    CString fname;
    if (ArxDbgUtils::getFileNameForRead(_T("Font file to use"),
                _T(""), _T("shx;ttf"), fname) != Acad::eOk) {
        delete newRec;
        return;
    }
    Acad::ErrorStatus es = newRec->setFileName(fname);
    if (es != Acad::eOk) {
        ArxDbgUtils::rxErrorMsg(es);
        delete newRec;
        return;
    }
    newRec->setBigFontFileName(_T(""));    // must explicitly set to ""

    ArxDbgUiPrDistDef    prTextSize(_T("Text size "), NULL, ArxDbgUiPrDist::kNoNeg, 0.0);
    ArxDbgUiPrAngleDef prOblique(_T("Oblique angle "), NULL, ArxDbgUiPrAngle::kAny, 0.0);
    ArxDbgUiPrDistDef    prScale(_T("X scale "), NULL, ArxDbgUiPrDist::kNoNegNoZero, 1.0);
    prScale.setUnit(ArxDbgUtils::kDecimal);
    
    if ((prTextSize.go() != ArxDbgUiPrBase::kOk) ||
        (prOblique.go() != ArxDbgUiPrBase::kOk) ||
        (prScale.go() != ArxDbgUiPrBase::kOk)) {
        delete newRec;
        return;
    }
    newRec->setTextSize(prTextSize.value());
    newRec->setObliquingAngle(prOblique.value());
    newRec->setXScale(prScale.value());

    if (addToSymbolTableAndClose(newRec))
        acutPrintf(_T("\nAdded textstyle \"%s\"."), symName);
    else
        acutPrintf(_T("\nERROR: could not add textstyle \"%s\"."), symName);
}

/****************************************************************************
**
**    TblMakeDbox::makeAppid
**
**    **jma
**
*************************************/

void
TblMakeDbox::makeAppid()
{
    CString symName;

    if (ArxDbgUtils::getNewSymbolName(_T("Application name"), AcDbRegAppTableRecord::desc(), symName) != ArxDbgUiPrBase::kOk)
        return;

    AcDbRegAppTableRecord* newRec = new AcDbRegAppTableRecord;
    if (setSymbolName(newRec, symName) != Acad::eOk) {
        delete newRec;
        return;
    }
    if (addToSymbolTableAndClose(newRec))
        acutPrintf(_T("\nAdded application \"%s\"."), symName);
    else
        acutPrintf(_T("\nERROR: could not add application \"%s\"."), symName);
}

/****************************************************************************
**
**    TblMakeDbox::makeUcs
**
**    **jma
**
*************************************/

void
TblMakeDbox::makeUcs()
{
    CString symName;

    if (ArxDbgUtils::getNewSymbolName(_T("UCS name"), AcDbUCSTableRecord::desc(), symName) != ArxDbgUiPrBase::kOk)
        return;

        // mimic the UCS command's 3point option
    ArxDbgUiPrPoint prOrigin(_T("Origin"), NULL);
    if (prOrigin.go() != ArxDbgUiPrBase::kOk)
        return;

    ArxDbgUiPrPoint prXAxis(_T("Point on positive portion of the X-axis"), NULL, prOrigin.value());
    ArxDbgUiPrPoint prYAxis(_T("Point on positive-Y portion of the UCS XY plane"), NULL, prOrigin.value());

    if ((prXAxis.go() != ArxDbgUiPrBase::kOk) ||
        (prYAxis.go() != ArxDbgUiPrBase::kOk))
        return;

    AcDbUCSTableRecord* newRec = new AcDbUCSTableRecord;
    if (setSymbolName(newRec, symName) != Acad::eOk) {
        delete newRec;
        return;
    }

    AcGePoint3d originPt = ArxDbgUtils::ucsToWcs(prOrigin.value());
    newRec->setOrigin(originPt);
    AcGeVector3d xAxis = ArxDbgUtils::ucsToWcs(prXAxis.value()) - originPt;
        // calculate pseudo Y axis since it isn't necessarily perpendicular
    AcGeVector3d yAxis = ArxDbgUtils::ucsToWcs(prYAxis.value()) - originPt;
    AcGeVector3d zAxis = xAxis.crossProduct(yAxis);
        // calculate true prependicular Y axis
    yAxis = zAxis.crossProduct(xAxis);

    newRec->setXAxis(xAxis.normalize());
    newRec->setYAxis(yAxis.normalize());

    if (addToSymbolTableAndClose(newRec))
        acutPrintf(_T("\nAdded UCS \"%s\"."), symName);
    else
        acutPrintf(_T("\nERROR: could not add UCS \"%s\"."), symName);
}

/****************************************************************************
**
**    TblMakeDbox::makeView
**        Sample routine to test direct make of a View Table Record.
**    Trying to center the view around the bounding-box extents of a 
**    selected object, with the center of the bounding box in center of
**    the screen (similar to ZOOM,Center).  Doesn't really work yet!
**
**    **jma
**
*************************************/

void
TblMakeDbox::makeView()
{
    AcDbEntity* obj;
    AcDbExtents extents;
    Acad::ErrorStatus es;

    if ((obj = ArxDbgUtils::selectEntity(_T("\nSelect entity to center view around: "), AcDb::kForRead)) == NULL)
        return;

    if ((es = obj->getGeomExtents(extents)) != Acad::eOk) {
        ArxDbgUtils::rxErrorMsg(es);
        obj->close();
        return;
    }
    obj->close();

    AcGePoint3d centerPt = ArxDbgUtilsGe::midpoint(extents.minPoint(), extents.maxPoint());

    double deltaX = fabs(extents.maxPoint().x - extents.minPoint().x);
    double deltaY = fabs(extents.maxPoint().y - extents.minPoint().y);
    double deltaZ = fabs(extents.maxPoint().z - extents.minPoint().z);

    CString symName;
    if (ArxDbgUtils::getNewSymbolName(_T("View name"), AcDbViewTableRecord::desc(), symName) != ArxDbgUiPrBase::kOk)
        return;

    ArxDbgUiPrKeyWordDef prViewDir(_T("\nView direction [Top/BOttom/Front/BAck/Left/Right]"),
                    _T("Top BOttom Front BAck Left Right"), _T("Top"));
    if (prViewDir.go() != ArxDbgUiPrBase::kOk)
        return;

    AcDbViewTableRecord* newRec = new AcDbViewTableRecord;
    if (setSymbolName(newRec, symName) != Acad::eOk) {
        delete newRec;
        return;
    }
    newRec->setIsPaperspaceView(Adesk::kFalse);
    newRec->setCenterPoint(ArxDbgUtils::ucsToDcs(centerPt));    // how to get correct point?
    newRec->setTarget(centerPt);
    newRec->setHeight(deltaZ);
    newRec->setWidth(max(deltaX, deltaY));

        // get desired view direction
    AcGeVector3d viewDir;
    if (prViewDir.isKeyWordPicked(_T("Top")))
        viewDir = AcGeVector3d::kZAxis;
    else if (prViewDir.isKeyWordPicked(_T("BOttom")))
        viewDir = -AcGeVector3d::kZAxis;
    else if (prViewDir.isKeyWordPicked(_T("BAck")))
        viewDir = AcGeVector3d::kYAxis;
    else if (prViewDir.isKeyWordPicked(_T("Front")))
        viewDir = -AcGeVector3d::kYAxis;
    else if (prViewDir.isKeyWordPicked(_T("Right")))
        viewDir = AcGeVector3d::kXAxis;
    else if (prViewDir.isKeyWordPicked(_T("Left")))
        viewDir = -AcGeVector3d::kXAxis;
    else {
        ASSERT(0);
    }
    newRec->setViewDirection(viewDir);

    if (addToSymbolTableAndClose(newRec)) {
        acutPrintf(_T("\nAdded View \"%s\"."), symName);
        acedCommandS(RTSTR, _T("._-VIEW"), RTSTR, _T("_R"), RTSTR, symName, 0);
    }
    else
        acutPrintf(_T("\nERROR: could not add View \"%s\"."), symName);
}

/****************************************************************************
**
**    TblMakeDbox::makeViewport
**
**    **jma
**
*************************************/

void
TblMakeDbox::makeViewport()
{
    ArxDbgUtils::stopAlertBox(_T("STUB: viewport"));
}

/****************************************************************************
**
**    TblMakeDbox::addToSymbolTableAndClose
**
**    **jma
**
*************************************/

BOOL
TblMakeDbox::addToSymbolTableAndClose(AcDbSymbolTableRecord* symRec)
{
    BOOL stat = FALSE;

    AcDbSymbolTable* symTbl = ArxDbgUtils::openSymbolTable(symRec->isA(),
									AcDb::kForWrite, acdbHostApplicationServices()->workingDatabase());
    if (symTbl) {
        Acad::ErrorStatus es = symTbl->add(symRec);
        if (es == Acad::eOk) {
            stat = TRUE;
            symRec->close();
        }
        else {
            ArxDbgUtils::rxErrorAlert(es);
            delete symRec;
        }

        symTbl->close();
    }
    return(stat);
}

/****************************************************************************
**
**    TblMakeDbox::setSymbolName
**
**    **jma
**
*************************************/

BOOL
TblMakeDbox::setSymbolName(AcDbSymbolTableRecord* newRec, LPCTSTR newName)
{
    Acad::ErrorStatus es;
    CString str;

    es = newRec->setName(newName);
    if (es != Acad::eOk) {
        ArxDbgUtils::rxErrorAlert(es);
        newRec->close();
        str.Format(_T("Invalid Symbol Name: \"%s\""), newName);
        ArxDbgUtils::alertBox(str);
    }
    return(es);
}


