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

#include "ArxDbgUiTdcDatabase.h"
#include "ArxDbgUtils.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**  ArxDbgUiTdcDatabase::ArxDbgUiTdcDatabase
**
**  **jma
**
*************************************/

ArxDbgUiTdcDatabase::ArxDbgUiTdcDatabase(AcDbDatabase* db)
:   m_db(db)
{
    //{{AFX_DATA_INIT(ArxDbgUiTdcDatabase)
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxDbgUiTdcDatabase::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDatabase::DoDataExchange(CDataExchange* pDX)
{
    ArxDbgUiTdcRxObjectBase::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxDbgUiTdcDatabase)
    DDX_Control(pDX, ARXDBG_FR_PREVIEW, m_frPreview);
    DDX_Control(pDX, ARXDBG_LC_DBMISC_VALUES, m_dataList);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdcDatabase message map

BEGIN_MESSAGE_MAP(ArxDbgUiTdcDatabase, ArxDbgUiTdcRxObjectBase)
    //{{AFX_MSG_MAP(ArxDbgUiTdcDatabase)
    ON_WM_PAINT()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdcDatabase message handlers


/****************************************************************************
**
**  ArxDbgUiTdcDatabase::OnPaint
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDatabase::OnPaint() 
{
    CPaintDC dc(this); // device context for painting

	const TCHAR* fname;
	Acad::ErrorStatus es = m_db->getFilename(fname);
	if (es == Acad::eOk) {
        m_frPreview.EnableWindow(TRUE);
        if (!acdbDisplayPreviewFromDwg(fname, m_frPreview.m_hWnd))
            ArxDbgUtils::stopAlertBox(_T("ERROR: Could not display preview image!"));
    }
    else {
        m_frPreview.EnableWindow(FALSE);
    }
}

/****************************************************************************
**
**	ArxDbgUiTdcDatabase::OnInitDialog
**
**	**jma
**
*************************************/

BOOL
ArxDbgUiTdcDatabase::OnInitDialog() 
{
    ArxDbgUiTdcRxObjectBase::OnInitDialog();

	buildColumns(m_dataList);
	display();

    return TRUE;
}

/****************************************************************************
**
**  ArxDbgUiTdcDatabase::display
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcDatabase::display()
{
		// remove any existing data
    m_fieldStrList.RemoveAll();
    m_valueStrList.RemoveAll();

    CString str;
	Acad::ErrorStatus es;

    addToDataList(_T("Approx. Number of Objects"), ArxDbgUtils::intToStr(m_db->approxNumObjects(), str));
    addToDataList(_T("Number of Saves"), ArxDbgUtils::intToStr(m_db->numberOfSaves(), str));
    addToDataList(_T("Maintenance Release Version"), ArxDbgUtils::intToStr(m_db->maintenanceReleaseVersion(), str));
    addToDataList(_T("Last Saved As Version"), ArxDbgUtils::dwgVersionToStr(m_db->lastSavedAsVersion(), str));
    addToDataList(_T("Last Saved As Maintenance Version"), ArxDbgUtils::intToStr(m_db->lastSavedAsMaintenanceVersion(), str));
    addToDataList(_T("Original File Name"), m_db->originalFileName(), true);
    addToDataList(_T("Original File Version"), ArxDbgUtils::dwgVersionToStr(m_db->originalFileVersion(), str));
    addToDataList(_T("Original File Maintenance Version"), ArxDbgUtils::intToStr(m_db->originalFileMaintenanceVersion(), str));
    addToDataList(_T("Original File Saved By Version"), ArxDbgUtils::dwgVersionToStr(m_db->originalFileSavedByVersion(), str));
    addToDataList(_T("Original File Saved By Manintenance Version"), ArxDbgUtils::intToStr(m_db->originalFileSavedByMaintenanceVersion(), str));
    addToDataList(_T("DWG Saved By Autodesk Software"), ArxDbgUtils::booleanToStr(m_db->dwgFileWasSavedByAutodeskSoftware(), str));

	TCHAR* name = NULL;

		// get projectName
    es = m_db->getProjectName(name);
	if (es == Acad::eOk) {
		addToDataList(_T("Project Name"), name, true);
		acutDelString(name);
	}
	else
		addToDataList(_T("Project Name"), ArxDbgUtils::rxErrorStr(es));

		// get hyperlinkBase
    es = m_db->getHyperlinkBase(name);
	if (es == Acad::eOk) {
		addToDataList(_T("Hyperlink Base"), name, true);
		acutDelString(name);
	}
	else
		addToDataList(_T("Hyperlink Base"), ArxDbgUtils::rxErrorStr(es));

		// get styleSheet
    es = m_db->getStyleSheet(name);
	if (es == Acad::eOk) {
		addToDataList(_T("Style Sheet"), name, true);
		acutDelString(name);
	}
	else
		addToDataList(_T("Style Sheet"), ArxDbgUtils::rxErrorStr(es));

		// get fileName
	const TCHAR* fname;
    es = m_db->getFilename(fname);
	if (es == Acad::eOk)
		addToDataList(_T("File Name"), fname, true);
	else
		addToDataList(_T("File Name"), ArxDbgUtils::rxErrorStr(es));

		// get fingerprintGuid
    es = m_db->getFingerprintGuid(name);
	if (es == Acad::eOk) {
		addToDataList(_T("Fingerprint Guid"), name);
		acutDelString(name);
	}
	else
		addToDataList(_T("Fingerprint Guid"), ArxDbgUtils::rxErrorStr(es));

		// get versionGuid
    es = m_db->getVersionGuid(name);
	if (es == Acad::eOk) {
		addToDataList(_T("Version Guid"), name);
		acutDelString(name);
	}
	else
		addToDataList(_T("Version Guid"), ArxDbgUtils::rxErrorStr(es));


    addToDataList(_T("Is Partially Opened"), ArxDbgUtils::booleanToStr(m_db->isPartiallyOpened(), str));
    addToDataList(_T("Retain Original Thumbnail"), ArxDbgUtils::booleanToStr(m_db->retainOriginalThumbnailBitmap(), str));
	addToDataList(_T("Xref Block"), ArxDbgUtils::objToClassAndHandleStr(m_db->xrefBlockId(), str));
	addToDataList(_T("Transaction Manager"), ArxDbgUtils::ptrToStr(m_db->transactionManager(), str));

	addSeperatorLine(_T("Header Variables"));

	addToDataList(_T("Angbase"), ArxDbgUtils::doubleToStr(m_db->angbase(), str));
	addToDataList(_T("Angdir"), ArxDbgUtils::booleanToStr(m_db->angdir(), str));
	addToDataList(_T("Attdia"), ArxDbgUtils::booleanToStr(m_db->attdia(), str));
	addToDataList(_T("Attmode"), ArxDbgUtils::intToStr(m_db->attmode(), str));
	addToDataList(_T("Attreq"), ArxDbgUtils::booleanToStr(m_db->attreq(), str));
	addToDataList(_T("Aunits"), ArxDbgUtils::intToStr(m_db->aunits(), str));
	addToDataList(_T("Auprec"), ArxDbgUtils::intToStr(m_db->auprec(), str));
	addToDataList(_T("Blipmode"), ArxDbgUtils::booleanToStr(m_db->blipmode(), str));
	addToDataList(_T("Cecolor"), ArxDbgUtils::colorToStr(m_db->cecolor().colorIndex(), str));
	addToDataList(_T("Celweight"), ArxDbgUtils::lineWeightTypeToStr(m_db->celweight(), str));

	es = ArxDbgUtils::symbolIdToName(m_db->clayer(), str);
	addToDataList(_T("Celayer"), str);

	es = ArxDbgUtils::symbolIdToName(m_db->celtype(), str);
	addToDataList(_T("Celtype"), str);
	addToDataList(_T("Celtscale"), ArxDbgUtils::doubleToStr(m_db->celtscale(), str));

	addToDataList(_T("Chamfera"), ArxDbgUtils::doubleToStr(m_db->chamfera(), str));
	addToDataList(_T("Chamferb"), ArxDbgUtils::doubleToStr(m_db->chamferb(), str));
	addToDataList(_T("Chamferc"), ArxDbgUtils::doubleToStr(m_db->chamferc(), str));
	addToDataList(_T("Chamferd"), ArxDbgUtils::doubleToStr(m_db->chamferd(), str));

	es = ArxDbgUtils::mlineStyleIdToName(m_db->cmlstyleID(), str);
	addToDataList(_T("Cmlstyleid"), str);

	addToDataList(_T("Cmljust"), ArxDbgUtils::intToStr(m_db->cmljust(), str));
	addToDataList(_T("Cmlscale"), ArxDbgUtils::doubleToStr(m_db->cmlscale(), str));

	addToDataList(_T("Coords"), ArxDbgUtils::intToStr(m_db->coords(), str));
	addToDataList(_T("Dimaso"), ArxDbgUtils::booleanToStr(m_db->dimaso(), str));
	addToDataList(_T("Dimsho"), ArxDbgUtils::booleanToStr(m_db->dimsho(), str));

	es = ArxDbgUtils::symbolIdToName(m_db->dimstyle(), str);
	addToDataList(_T("Dimstyle"), str);

	addToDataList(_T("Dispsilh"), ArxDbgUtils::booleanToStr(m_db->dispSilh(), str));
	addToDataList(_T("Delete Used Obj"), ArxDbgUtils::booleanToStr(!!m_db->delUsedObj(), str));
	addToDataList(_T("Dragmode"), ArxDbgUtils::intToStr(m_db->dragmode(), str));
	addToDataList(_T("Elevation"), ArxDbgUtils::doubleToStr(m_db->elevation(), str));
	addToDataList(_T("Endcaps"), ArxDbgUtils::intToStr(m_db->endCaps(), str));
	addToDataList(_T("Extmin"), ArxDbgUtils::ptToStr(m_db->extmin(), str));
	addToDataList(_T("Extmax"), ArxDbgUtils::ptToStr(m_db->extmax(), str));
	addToDataList(_T("Facetres"), ArxDbgUtils::doubleToStr(m_db->facetres(), str));
	addToDataList(_T("Fillmode"), ArxDbgUtils::booleanToStr(m_db->fillmode(), str));
	addToDataList(_T("Filletrad"), ArxDbgUtils::doubleToStr(m_db->filletrad(), str));

	TCHAR tmpStr[256];
    m_db->handseed().getIntoAsciiBuffer(tmpStr);
	addToDataList(_T("Handseed"), tmpStr);

	addToDataList(_T("Insbase"), ArxDbgUtils::ptToStr(m_db->insbase(), str));
	addToDataList(_T("Insunits"), ArxDbgUtils::intToStr(m_db->insunits(), str));
	addToDataList(_T("Isolines"), ArxDbgUtils::intToStr(m_db->isolines(), str));
	addToDataList(_T("Joinstyle"), ArxDbgUtils::intToStr(m_db->joinStyle(), str));
	addToDataList(_T("Ltscale"), ArxDbgUtils::doubleToStr(m_db->ltscale(), str));
	addToDataList(_T("Limcheck"), ArxDbgUtils::booleanToStr(m_db->limcheck(), str));
	addToDataList(_T("Limmin"), ArxDbgUtils::ptToStr(m_db->limmin(), str));
	addToDataList(_T("Limmax"), ArxDbgUtils::ptToStr(m_db->limmax(), str));
	addToDataList(_T("Lineweight Display"), ArxDbgUtils::booleanToStr(m_db->lineWeightDisplay(), str));
	addToDataList(_T("Lunits"), ArxDbgUtils::intToStr(m_db->lunits(), str));
	addToDataList(_T("Luprec"), ArxDbgUtils::intToStr(m_db->luprec(), str));
	addToDataList(_T("Maxactvp"), ArxDbgUtils::intToStr(m_db->maxactvp(), str));
	addToDataList(_T("Measurement"), ArxDbgUtils::measurementTypeToStr(m_db->measurement(), str));

	TCHAR* menuName;
	es = m_db->getMenu(menuName);
	if (es == Acad::eOk) {
		addToDataList(_T("Menu"), menuName, true);
		acutDelString(menuName);
	}
	else
		addToDataList(_T("Menu"), ArxDbgUtils::rxErrorStr(es));

	addToDataList(_T("Mirrtext"), ArxDbgUtils::booleanToStr(m_db->mirrtext(), str));
	addToDataList(_T("OLE Startup"), ArxDbgUtils::booleanToStr(m_db->oleStartUp(), str));
	addToDataList(_T("Orthomode"), ArxDbgUtils::booleanToStr(m_db->orthomode(), str));
	addToDataList(_T("Pdmode"), ArxDbgUtils::intToStr(m_db->pdmode(), str));
	addToDataList(_T("Pdsize"), ArxDbgUtils::doubleToStr(m_db->pdsize(), str));
	addToDataList(_T("Pextmin"), ArxDbgUtils::ptToStr(m_db->pextmin(), str));
	addToDataList(_T("Pextmax"), ArxDbgUtils::ptToStr(m_db->pextmax(), str));
	addToDataList(_T("Pelevation"), ArxDbgUtils::doubleToStr(m_db->pelevation(), str));
	addToDataList(_T("Pickstyle"), ArxDbgUtils::intToStr(m_db->pickstyle(), str));
	addToDataList(_T("Pinsbase"), ArxDbgUtils::ptToStr(m_db->pinsbase(), str));
	addToDataList(_T("Plimcheck"), ArxDbgUtils::booleanToStr(m_db->plimcheck(), str));
	addToDataList(_T("Plimmin"), ArxDbgUtils::ptToStr(m_db->plimmin(), str));
	addToDataList(_T("Plimmax"), ArxDbgUtils::ptToStr(m_db->plimmax(), str));
	addToDataList(_T("PlineEllipse"), ArxDbgUtils::booleanToStr(m_db->plineEllipse(), str));
	addToDataList(_T("PlineGen"), ArxDbgUtils::booleanToStr(m_db->plinegen(), str));
	addToDataList(_T("Plinewid"), ArxDbgUtils::doubleToStr(m_db->plinewid(), str));
	addToDataList(_T("Plot Style Mode"), ArxDbgUtils::booleanToStr(m_db->plotStyleMode(), str));
	addToDataList(_T("PsltScale"), ArxDbgUtils::booleanToStr(m_db->psltscale(), str));
	addToDataList(_T("Pucsorg"), ArxDbgUtils::ptToStr(m_db->pucsorg(), str));
	addToDataList(_T("Pucsxdir"), ArxDbgUtils::vectorToStr(m_db->pucsxdir(), str));
	addToDataList(_T("Pucsydir"), ArxDbgUtils::vectorToStr(m_db->pucsydir(), str));

	es = ArxDbgUtils::symbolIdToName(m_db->pucsname(), str);
	addToDataList(_T("Pucsname"), str);

	addToDataList(_T("Pucsbase"), ArxDbgUtils::objToClassAndHandleStr(m_db->pucsBase(), str));

	AcDb::OrthographicView orthoView;
	addToDataList(_T("Pucs Is Orthographic"), ArxDbgUtils::booleanToStr(m_db->isPucsOrthographic(orthoView), str));

	addToDataList(_T("Qtextmode"), ArxDbgUtils::booleanToStr(m_db->qtextmode(), str));
	addToDataList(_T("Regenmode"), ArxDbgUtils::booleanToStr(m_db->regenmode(), str));
	addToDataList(_T("Save Proxy Graphics"), ArxDbgUtils::intToStr(m_db->saveproxygraphics(), str));
	addToDataList(_T("Shadedge"), ArxDbgUtils::intToStr(m_db->shadedge(), str));
	addToDataList(_T("Shadedif"), ArxDbgUtils::intToStr(m_db->shadedif(), str));
	addToDataList(_T("Skpoly"), ArxDbgUtils::booleanToStr(m_db->skpoly(), str));
	addToDataList(_T("Sketchinc"), ArxDbgUtils::doubleToStr(m_db->sketchinc(), str));
	addToDataList(_T("Splframe"), ArxDbgUtils::booleanToStr(m_db->splframe(), str));
	addToDataList(_T("Splinetype"), ArxDbgUtils::intToStr(m_db->splinetype(), str));
	addToDataList(_T("Splinesegs"), ArxDbgUtils::intToStr(m_db->splinesegs(), str));
	addToDataList(_T("Surfu"), ArxDbgUtils::intToStr(m_db->surfu(), str));
	addToDataList(_T("Surfv"), ArxDbgUtils::intToStr(m_db->surfv(), str));
	addToDataList(_T("Surftype"), ArxDbgUtils::intToStr(m_db->surftype(), str));
	addToDataList(_T("Surftab1"), ArxDbgUtils::intToStr(m_db->surftab1(), str));
	addToDataList(_T("Surftab2"), ArxDbgUtils::intToStr(m_db->surftab2(), str));
	addToDataList(_T("Tdcreate"), ArxDbgUtils::dateToStr(m_db->tdcreate(), str));
	addToDataList(_T("Tdupdate"), ArxDbgUtils::dateToStr(m_db->tdupdate(), str));
	addToDataList(_T("Tducreate"), ArxDbgUtils::dateToStr(m_db->tducreate(), str));
	addToDataList(_T("Tduupdate"), ArxDbgUtils::dateToStr(m_db->tduupdate(), str));
	addToDataList(_T("Tdindwg"), ArxDbgUtils::dateToStr(m_db->tdindwg(), str));
	addToDataList(_T("Tdusrtimer"), ArxDbgUtils::dateToStr(m_db->tdusrtimer(), str));
	addToDataList(_T("Textsize"), ArxDbgUtils::doubleToStr(m_db->textsize(), str));
	addToDataList(_T("Thickness"), ArxDbgUtils::doubleToStr(m_db->thickness(), str));
	addToDataList(_T("Tilemode"), ArxDbgUtils::booleanToStr(m_db->tilemode(), str));
	addToDataList(_T("Treedepth"), ArxDbgUtils::intToStr(m_db->treedepth(), str));
	addToDataList(_T("Tracewidth"), ArxDbgUtils::doubleToStr(m_db->tracewid(), str));
	addToDataList(_T("Tstackalign"), ArxDbgUtils::intToStr(m_db->tstackalign(), str));
	addToDataList(_T("Tstacksize"), ArxDbgUtils::intToStr(m_db->tstacksize(), str));
	addToDataList(_T("Ucsorg"), ArxDbgUtils::ptToStr(m_db->ucsorg(), str));
	addToDataList(_T("Ucsxdir"), ArxDbgUtils::vectorToStr(m_db->ucsxdir(), str));
	addToDataList(_T("Ucsydir"), ArxDbgUtils::vectorToStr(m_db->ucsydir(), str));

	es = ArxDbgUtils::symbolIdToName(m_db->ucsname(), str);
	addToDataList(_T("Ucsname"), str);

	addToDataList(_T("Ucsbase"), ArxDbgUtils::objToClassAndHandleStr(m_db->ucsBase(), str));
	addToDataList(_T("Ucs Is Orthographic"), ArxDbgUtils::booleanToStr(m_db->isUcsOrthographic(orthoView), str));

	addToDataList(_T("Useri1"), ArxDbgUtils::intToStr(m_db->useri1(), str));
	addToDataList(_T("Useri2"), ArxDbgUtils::intToStr(m_db->useri2(), str));
	addToDataList(_T("Useri3"), ArxDbgUtils::intToStr(m_db->useri3(), str));
	addToDataList(_T("Useri4"), ArxDbgUtils::intToStr(m_db->useri4(), str));
	addToDataList(_T("Useri5"), ArxDbgUtils::intToStr(m_db->useri5(), str));
	addToDataList(_T("Userr1"), ArxDbgUtils::doubleToStr(m_db->userr1(), str));
	addToDataList(_T("Userr2"), ArxDbgUtils::doubleToStr(m_db->userr2(), str));
	addToDataList(_T("Userr3"), ArxDbgUtils::doubleToStr(m_db->userr3(), str));
	addToDataList(_T("Userr4"), ArxDbgUtils::doubleToStr(m_db->userr4(), str));
	addToDataList(_T("Userr5"), ArxDbgUtils::doubleToStr(m_db->userr5(), str));
	addToDataList(_T("Usrtimer"), ArxDbgUtils::booleanToStr(m_db->usrtimer(), str));
	addToDataList(_T("Visretain"), ArxDbgUtils::booleanToStr(m_db->visretain(), str));
	addToDataList(_T("Viewport Scale Default"), ArxDbgUtils::doubleToStr(m_db->viewportScaleDefault(), str));
	addToDataList(_T("WorldView"), ArxDbgUtils::booleanToStr(m_db->worldview(), str));
	addToDataList(_T("Xref Edit Enabled"), ArxDbgUtils::booleanToStr(m_db->xrefEditEnabled(), str));

// TBD: getCePlotStyleNameId()

	drawPropsList(m_dataList);
}

