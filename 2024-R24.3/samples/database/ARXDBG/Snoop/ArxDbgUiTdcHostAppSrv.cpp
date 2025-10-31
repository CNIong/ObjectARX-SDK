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

#include "ArxDbgUiTdcHostAppSrv.h"
#include "ArxDbgUtils.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
**
**  ArxDbgUiTdcHostAppSrv::ArxDbgUiTdcHostAppSrv
**
**  **jma
**
*************************************/

ArxDbgUiTdcHostAppSrv::ArxDbgUiTdcHostAppSrv()
{
    //{{AFX_DATA_INIT(ArxDbgUiTdcHostAppSrv)
    //}}AFX_DATA_INIT
}

/****************************************************************************
**
**  ArxDbgUiTdcHostAppSrv::~ArxDbgUiTdcHostAppSrv
**
**  **jma
**
*************************************/

ArxDbgUiTdcHostAppSrv::~ArxDbgUiTdcHostAppSrv()
{
}

/****************************************************************************
**
**  ArxDbgUiTdcHostAppSrv::DoDataExchange
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcHostAppSrv::DoDataExchange(CDataExchange* pDX)
{
    ArxDbgUiTdcRxObjectBase::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ArxDbgUiTdcHostAppSrv)
    DDX_Control(pDX, ARXDBG_LC_DATA, m_dataList);
    //}}AFX_DATA_MAP
}


/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdcHostAppSrv message map

BEGIN_MESSAGE_MAP(ArxDbgUiTdcHostAppSrv, ArxDbgUiTdcRxObjectBase)
    //{{AFX_MSG_MAP(ArxDbgUiTdcHostAppSrv)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ArxDbgUiTdcHostAppSrv message handlers

/****************************************************************************
**
**  ArxDbgUiTdcHostAppSrv::OnInitDialog
**
**  **jma
**
*************************************/

BOOL
ArxDbgUiTdcHostAppSrv::OnInitDialog() 
{
    ArxDbgUiTdcRxObjectBase::OnInitDialog();

	buildColumns(m_dataList);
    displayCurrent();

    return TRUE;
}

/****************************************************************************
**
**  ArxDbgUiTdcHostAppSrv::displayCurrent
**
**  **jma
**
*************************************/

void
ArxDbgUiTdcHostAppSrv::displayCurrent()
{
		// remove any previous entries
    m_fieldStrList.RemoveAll();
    m_valueStrList.RemoveAll();

	CString str;

	AcDbHostApplicationServices* appSrv = acdbHostApplicationServices();
	ASSERT(appSrv != NULL);

	addToDataList(_T("Ready To Display Messages"), ArxDbgUtils::booleanToStr(appSrv->readyToDisplayMessages(), str));
	addToDataList(_T("Do Full CRC Check"), ArxDbgUtils::booleanToStr(appSrv->doFullCRCCheck(), str));

	TCHAR tempPath[1024];
	Adesk::UInt32 bufSize = appSrv->getTempPath(1024, tempPath);
	addToDataList(_T("Temp Path"), tempPath);

	addToDataList(_T("Working Database"), ArxDbgUtils::dbToStr(appSrv->workingDatabase(), str));
	addToDataList(_T("Default Undo Controller"), ArxDbgUtils::ptrToStr(appSrv->defaultUndoController(), str));
	addToDataList(_T("Working Transaction Manager"), ArxDbgUtils::ptrToStr(appSrv->workingTransactionManager(), str));

	addToDataList(_T("Program"), appSrv->program());
	addToDataList(_T("Product"), appSrv->product());
	addToDataList(_T("Company Name"), appSrv->companyName());

	ProdIdCode idCode = appSrv->prodcode();
	if (idCode == kProd_ACAD)
		str = _T("Prod_ACAD");
	else if (idCode == kProd_OEM)
		str = _T("Prod_OEM");
	else if (idCode == kProd_AcDb)
		str = _T("Prod_AcDb");
	else {
		ASSERT(0);
		str = _T("*Unknown*");
	}

	addToDataList(_T("Product ID Code"), str);
	addToDataList(_T("Release Major Minor String"), appSrv->releaseMajorMinorString());
	addToDataList(_T("Release Major Version"), ArxDbgUtils::intToStr(appSrv->releaseMajorVersion(), str));
	addToDataList(_T("Release Minor Version"), ArxDbgUtils::intToStr(appSrv->releaseMinorVersion(), str));
	addToDataList(_T("Version String"), appSrv->versionString());
	addToDataList(_T("Registry Machine Product Root Key"), appSrv->getMachineRegistryProductRootKey());
    addToDataList(_T("Registry User Product Root Key"), appSrv->getUserRegistryProductRootKey());
	addToDataList(_T("Registry Product LCID"), ArxDbgUtils::intToStr(appSrv->getProductLocale(), str));
	addToDataList(_T("Code Page Id"), ArxDbgUtils::intToStr(static_cast<int>(appSrv->getSystemCodePage()), str));

	addToDataList(_T("Alternate Font Name"), appSrv->getAlternateFontName());
	addToDataList(_T("Font Map File Name"), appSrv->getFontMapFileName());
	addToDataList(_T("Cache Symbol Indices"), ArxDbgUtils::booleanToStr(appSrv->cacheSymbolIndices(), str));

	drawPropsList(m_dataList);
}
