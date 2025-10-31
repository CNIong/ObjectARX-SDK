// (C) Copyright 2003-2007 by Autodesk, Inc. 
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

// PlotApiDialog.cpp : implementation file
//
#include "stdafx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "PlotApiDialog.h"
#include "AcPlPlotEngine.h"
#include "acplplotfactory.h"
#include "acplplotinfo.h"
#include "acplplotinfovalidator.h"
#include "axlock.h"
#include "AsdkPlotApiDialog_i.h"



// CPlotApiDialog dialog

IMPLEMENT_DYNAMIC(CPlotApiDialog, CDialog)
CPlotApiDialog::CPlotApiDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CPlotApiDialog::IDD, pParent)
	, m_Scale(0)
	, m_Landscape(FALSE)
	, m_CurrentDevice(_T(""))
	, pPSV(NULL)
	, m_bFit(FALSE)
	, m_Background(FALSE)
	, m_bPlotToFile(FALSE)
	, m_csFilename(_T(""))
	,dwAppCF(0)
	,dwAppObj(0)
	,pPlotSink(NULL)
{
}

CPlotApiDialog::~CPlotApiDialog()
{
}

void CPlotApiDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DEVICES, m_Devices);
	DDX_Control(pDX, IDC_MEDIA, m_Media);
	DDX_Text(pDX, IDC_SCALE, m_Scale);
	DDX_Check(pDX, IDC_LANDSCAPE, m_Landscape);
	DDX_Check(pDX, IDC_FIT, m_bFit);
	DDX_Check(pDX, IDC_BACKGROUND, m_Background);
	DDX_Check(pDX, IDC_PLOTTOFILE, m_bPlotToFile);
	DDX_Text(pDX, IDC_FILENAME, m_csFilename);
}


BEGIN_MESSAGE_MAP(CPlotApiDialog, CDialog)
	ON_CBN_SELCHANGE(IDC_DEVICES, OnCbnSelchangeDevices)
	ON_CBN_SELCHANGE(IDC_MEDIA, OnCbnSelchangeMedia)
	ON_BN_CLICKED(IDC_PLOT, OnBnClickedPlot)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_PREVIEW, OnBnClickedPreview)
	ON_BN_CLICKED(IDC_LANDSCAPE, OnBnClickedLandscape)
	ON_BN_CLICKED(IDC_FIT, OnBnClickedFit)
	ON_BN_CLICKED(IDC_BACKGROUND, OnBnClickedBackground)
	ON_EN_CHANGE(IDC_SCALE, OnEnChangeScale)
	ON_BN_CLICKED(IDC_PLOTTOFILE, OnBnClickedPlottofile)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// CPlotApiDialog message handlers

void CPlotApiDialog::OnCbnSelchangeDevices()
{
	AcAxDocLock lock;

	m_Devices.GetLBText(m_Devices.GetCurSel(),m_CurrentDevice);
		
	Acad::ErrorStatus es=pPSV->setPlotCfgName(pPlotSettings,m_CurrentDevice);
	pPSV->refreshLists(pPlotSettings);
	RefreshMediaNames();
	if(m_bFit)
		CalcExtents();

	// Determine the device capabilities regarding plotting to file.
	// We'll enable or disable the ability to select plot-to-file depending
	// on the devices capability.
	
	AcPlPlotConfig *pPlotConfig =  NULL;
	//const TCHAR *szLocaleName;
	if(Acad::eOk == acplPlotConfigManagerPtr()->setCurrentConfig(pPlotConfig,m_CurrentDevice))
	{
		if(pPlotConfig->plotToFileCapability()!=AcPlPlotConfig::kPlotToFileAllowed)
		{
			if(pPlotConfig->plotToFileCapability()==AcPlPlotConfig::kNoPlotToFile)
			{
				m_bPlotToFile=FALSE;
				CEdit *pEdit=(CEdit*)GetDlgItem(IDC_FILENAME);
				pEdit->EnableWindow(FALSE);
			}
			else
			{		// kMustPlotToFile
					m_bPlotToFile=TRUE;
					CEdit *pEdit=(CEdit*)GetDlgItem(IDC_FILENAME);
					pEdit->EnableWindow(TRUE);
			}
			// Either way, disable the PLOTTOFILE check box.
			CButton *pButton=(CButton*)GetDlgItem(IDC_PLOTTOFILE);
			pButton->EnableWindow(FALSE);
		}
		else
		{
			CEdit *pEdit=(CEdit*)GetDlgItem(IDC_FILENAME);
			pEdit->EnableWindow(TRUE);
			CButton *pButton=(CButton*)GetDlgItem(IDC_PLOTTOFILE);
			pButton->EnableWindow(TRUE);
		}
	}
	UpdateData(FALSE);
}

void CPlotApiDialog::OnCbnSelchangeMedia()
{
	AcAxDocLock lock;

	m_Media.UpdateData();
	m_Media.GetLBText(m_Media.GetCurSel(),m_CurrentMedia);

	Acad::ErrorStatus es=pPSV->setCanonicalMediaName(pPlotSettings,m_CurrentMedia);
	if(m_bFit)
		CalcExtents();
}

void CPlotApiDialog::OnBnClickedPlot()
{
	Acad::ErrorStatus es;
	
	AcAxDocLock lock;
	
	es=pPSV->setPlotType(pPlotSettings,AcDbPlotSettings::kExtents);
	// Set the Scale...
	if (m_bFit)
	{
		es = pPSV->setUseStandardScale(pPlotSettings,Adesk::kTrue);
		es = pPSV->setStdScaleType(pPlotSettings,AcDbPlotSettings::kScaleToFit);
	}
	else // Choose to use this custom scale...
	{
		es=pPSV->setUseStandardScale(pPlotSettings,Adesk::kFalse);
		es=pPSV->setCustomPrintScale(pPlotSettings,m_Scale,1);
	}
	// Specify that we want our plot centered by AutoCAD...
	es=pPSV->setPlotCentered(pPlotSettings,true);
	
    // Create a publish engine, and send the plot through...
	AcPlPlotEngine* pEngine = NULL;
    if(Acad::eOk==AcPlPlotFactory::createPublishEngine(pEngine))
	{
		// Here is the progress dialog for the current plot process...
		AcPlPlotProgressDialog *pPlotProgDlg = acplCreatePlotProgressDialog(acedGetAcadFrame()->m_hWnd,false,1);
	    
		pPlotProgDlg->setPlotMsgString(AcPlPlotProgressDialog::kDialogTitle,_T("Plot API Progress"));
		pPlotProgDlg->setPlotMsgString(AcPlPlotProgressDialog::kCancelJobBtnMsg,_T("Cancel Job"));
		pPlotProgDlg->setPlotMsgString(AcPlPlotProgressDialog::kCancelSheetBtnMsg,_T("Cancel Sheet"));
		pPlotProgDlg->setPlotMsgString(AcPlPlotProgressDialog::kSheetSetProgressCaption,_T("Job Progress"));
		pPlotProgDlg->setPlotMsgString(AcPlPlotProgressDialog::kSheetProgressCaption,_T("Sheet Progress"));
	    
		pPlotProgDlg->setPlotProgressRange(0,100);
		pPlotProgDlg->onBeginPlot();
		pPlotProgDlg->setIsVisible(true);
	    
		es = pEngine->beginPlot(pPlotProgDlg);
		
		AcPlPlotPageInfo pageInfo;
		AcPlPlotInfo plotInfo; // Used to describe how the plot is to be made
	    
		// First, set the layout to the specified layout (which is the current layout in this sample)
		plotInfo.setLayout(layoutId);// This is required.

		// Now, override the layout settings with the plot settings we have been populating
		plotInfo.setOverrideSettings(pPlotSettings);
		
		// We need to validate these settings.
		AcPlPlotInfoValidator validator;
        validator.setMediaMatchingPolicy(AcPlPlotInfoValidator::kMatchEnabled);
		es = validator.validate(plotInfo);

		// Begin document.  The version we call is dependent on the plot-to-file status.
		const TCHAR *szDocName=acDocManager->curDocument()->fileName();
		if(m_bPlotToFile)
			es = pEngine->beginDocument(plotInfo, szDocName, NULL, 1, true, m_csFilename);
		else
			es = pEngine->beginDocument(plotInfo, szDocName);

		// Follow through sending commands to the engine, and notifications to the progress dialog.
		pPlotProgDlg->onBeginSheet();
		pPlotProgDlg->setSheetProgressRange(0, 100);
		pPlotProgDlg->setSheetProgressPos(0);

		es = pEngine->beginPage(pageInfo, plotInfo, true);    	

		es = pEngine->beginGenerateGraphics();
		es = pEngine->endGenerateGraphics();

		es = pEngine->endPage();

		pPlotProgDlg->setSheetProgressPos(100);
		pPlotProgDlg->onEndSheet();
		pPlotProgDlg->setPlotProgressPos(100);
		es = pEngine->endDocument();
		es = pEngine->endPlot();
		
		// Destroy the engine 
		pEngine->destroy();
		pEngine = NULL;
		// and the progress dialog.
		pPlotProgDlg->destroy();
	}
	else
		// Ensure the engine is not already busy...
		AfxMessageBox(_T("Plot Engine is Busy..."));
}

void CPlotApiDialog::RefreshDevices(void)
{
	// Set the list of available devices on the system
	AcArray<const TCHAR*> deviceList;// Temporary device array
	
	m_Devices.ResetContent();// Clear the Combo Box

	pPSV->plotDeviceList(deviceList);// Fill the temporary array,
	// and copy the Combo Box and mirror with the results.
	for(int c=0;c<deviceList.length();c++)
		m_Devices.AddString(deviceList[c]);
	
	// Set the current selection to reflect the current output device.
	const TCHAR* plotCfgchar;
	pPlotSettings->getPlotCfgName(plotCfgchar);
	m_Devices.SetCurSel(m_Devices.SelectString(0,plotCfgchar));
}

BOOL CPlotApiDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	CenterWindow(acedGetAcadDwgView());

	// Setup the ARX pointer...
	pPSV=(AcDbPlotSettingsValidator*)acdbHostApplicationServices()->plotSettingsValidator(); 
	
	AcAxDocLock lock;
	
	// Now get the active layout object.  This will be stored in layoutId.
	AcDbLayoutManager *pLayoutManager = acdbHostApplicationServices()->layoutManager(); 
	AcDbObjectId btrId=pLayoutManager->getActiveLayoutBTRId();
	AcDbBlockTableRecord *pBTR;
	Acad::ErrorStatus es=acdbOpenObject(pBTR,btrId,AcDb::kForRead);
	// We want to instantiate our custom AcDbPlotSettings object, and inherit the 
	// properties from the active layout.
	layoutId=pBTR->getLayoutId();
	AcDbLayout *pLayout=NULL;
	acdbOpenObject(pLayout,layoutId,AcDb::kForRead);

#pragma warning (disable: 4800)

	pPlotSettings=new AcDbPlotSettings(pLayout->modelType());

#pragma warning (default: 4800)

	pPlotSettings->copyFrom(pLayout);
	pLayout->close();
	pBTR->close();

	// Set some initial default values for the controls on the form.
	m_bFit=TRUE;
	CEdit *pEdit=(CEdit*)GetDlgItem(IDC_SCALE);
	pEdit->EnableWindow(FALSE);

    m_csFilename=_T("c:\\temp\\PlotApi.dwf");
	pEdit=(CEdit*)GetDlgItem(IDC_FILENAME);
	pEdit->EnableWindow(FALSE);
	m_bPlotToFile=FALSE;
	
	m_Landscape=FALSE;
	pPSV->setPlotRotation(pPlotSettings,AcDbPlotSettings::k0degrees);
	
	// Determine the current background plot setting.
	struct resbuf res;
	acedGetVar(_T("BACKGROUNDPLOT"),&res);
	if(res.resval.rint)
		m_Background=TRUE;
	else
		m_Background=FALSE;

	// Update the dropdown lists...
	RefreshDevices();
	OnCbnSelchangeDevices();// Called to setup the plot-to-file capabilities for the default device.
	RefreshMediaNames();
	CalcExtents();// Calculate the scale the layout we be plotted to fit the selected page.
	
	
	UpdateData(FALSE);
	
	// Instantiate the IAsdkPlotNotifySink server
	HRESULT hr=InitAutomation();
	    
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CPlotApiDialog::OnDestroy()
{
	CDialog::OnDestroy();
	HRESULT hr=ExitAutomation();
	delete pPlotSettings;
	delete this;
}

void CPlotApiDialog::RefreshMediaNames()
{
	AcArray<const TCHAR*> MediaList;

	m_Media.ResetContent();

	pPSV->canonicalMediaNameList(pPlotSettings,MediaList);

	for(int c=0;c<MediaList.length();c++)
		m_Media.AddString(MediaList[c]);

	const TCHAR *pCurName;
	pPlotSettings->getCanonicalMediaName(pCurName);
	m_Media.SetCurSel(m_Media.SelectString(0,(CString)pCurName));
}

void CPlotApiDialog::OnBnClickedPreview()
{
	Acad::ErrorStatus es;

	AcAxDocLock lock;
        
	es=pPSV->setPlotType(pPlotSettings,AcDbPlotSettings::kExtents);
	// Set the Scale...
	if (m_bFit)
	{
		es = pPSV->setUseStandardScale(pPlotSettings,Adesk::kTrue);
		es = pPSV->setStdScaleType(pPlotSettings,AcDbPlotSettings::kScaleToFit);
	}
	else // Choose to use this custom scale...
	{
		es=pPSV->setUseStandardScale(pPlotSettings,Adesk::kFalse);
		es=pPSV->setCustomPrintScale(pPlotSettings,m_Scale,1);
	}
	es=pPSV->setPlotCentered(pPlotSettings,true);
	
	acedGetAcadFrame()->ShowWindow(SW_SHOW);	
	acedGetAcadFrame()->SetFocus();
	ShowWindow(SW_HIDE);
	if(pPlotSink)
		pPlotSink->put_Visible(FALSE);
	
	AcPlPlotEngine* pEngine = NULL;
	if(Acad::eOk==AcPlPlotFactory::createPreviewEngine(pEngine))
	{
		pEngine->beginPlot(NULL);

		AcPlPlotPageInfo pageInfo;
		AcPlPlotInfo plotInfo;
	    
		plotInfo.setLayout(layoutId);

		plotInfo.setOverrideSettings(pPlotSettings);

		AcPlPlotInfoValidator validator;
		validator.setMediaMatchingPolicy(AcPlPlotInfoValidator::kMatchEnabled);
		es = validator.validate(plotInfo);

		const TCHAR *szDocName=acDocManager->curDocument()->fileName();
	    	
		es = pEngine->beginDocument(plotInfo, szDocName);
		es = pEngine->beginPage(pageInfo, plotInfo, true);    	
		es = pEngine->beginGenerateGraphics();
		es = pEngine->endGenerateGraphics();
		es = pEngine->endPage();
		es = pEngine->endDocument();
		es = pEngine->endPlot();

		pEngine->destroy();
		pEngine = NULL;
	}
	else
		AfxMessageBox(_T("Plot Engine is Busy..."));

	ShowWindow(SW_SHOW);
	if(pPlotSink)
		pPlotSink->put_Visible(TRUE);
}

void CPlotApiDialog::OnBnClickedLandscape()
{
	UpdateData(TRUE);
	AcAxDocLock lock;
	if(m_Landscape)
		Acad::ErrorStatus es=pPSV->setPlotRotation(pPlotSettings,AcDbPlotSettings::k90degrees);
	else
		Acad::ErrorStatus es=pPSV->setPlotRotation(pPlotSettings,AcDbPlotSettings::k0degrees);

	CalcExtents();
}


void CPlotApiDialog::OnBnClickedFit()
{
	UpdateData(TRUE);
	CEdit *pEdit=(CEdit*)GetDlgItem(IDC_SCALE);
	if(m_bFit)
	{
		pEdit->EnableWindow(FALSE);
		CalcExtents();
	}
	else
		pEdit->EnableWindow(TRUE);
}

void CPlotApiDialog::OnBnClickedBackground()
{
	UpdateData(TRUE);
	
	struct resbuf res;
	res.resval.rint=(int)m_Background;
	res.restype=RTSHORT;
	
	acedSetVar(_T("BACKGROUNDPLOT"),&res);
}

void CPlotApiDialog::CalcExtents()
{
	CEdit *pEdit=(CEdit*)GetDlgItem(IDC_SCALE);
	if(m_bFit)
	{
		pEdit->EnableWindow(FALSE);
		Acad::ErrorStatus es = pPSV->setUseStandardScale(pPlotSettings,Adesk::kTrue);
		es = pPSV->setStdScaleType(pPlotSettings,AcDbPlotSettings::kScaleToFit);
		es = pPSV->setPlotType(pPlotSettings,AcDbPlotSettings::kExtents);
		es = pPSV->setPlotCentered(pPlotSettings,true);
		double numerator,denominator;
		es = pPlotSettings->getCustomPrintScale(numerator,denominator);
		m_Scale = numerator/denominator;
		UpdateData(FALSE);
	}
	else
		pEdit->EnableWindow(TRUE);
	UpdateData(FALSE);
}

void CPlotApiDialog::OnEnChangeScale()
{
	UpdateData(TRUE);
}

void CPlotApiDialog::OnBnClickedPlottofile()
{
	UpdateData(TRUE);
	CEdit *pEdit=(CEdit*)GetDlgItem(IDC_FILENAME);
	if(m_bPlotToFile)
		pEdit->EnableWindow(TRUE);
	else
		pEdit->EnableWindow(FALSE);
}

void CPlotApiDialog::OnBnClickedCancel()
{
	CDialog::OnCancel();
	DestroyWindow();
}

HRESULT CPlotApiDialog::InitAutomation(void)
{
	// This will instantiate the IAsdkPlotNotifySink object as the single active instance,
	// assuming it has not already been added to the ROT.
	HRESULT hr = OleInitialize(NULL);
    if (FAILED(hr)) 
		return hr;

	CComPtr <IUnknown> pUnk;
	if(GetActiveObject(CLSID_CPlotNotifySink,NULL,&pUnk)==S_OK)
		return S_OK; // Only one active sink is necessary.

    CComPtr<IClassFactory> pCF;
    hr = DllGetClassObject(CLSID_CPlotNotifySink, IID_IClassFactory, (LPVOID*)&pCF);
    if (FAILED(hr)) 
		return hr;

	hr = pCF->CreateInstance(NULL, IID_IAsdkPlotNotifySink, (LPVOID*)&pPlotSink);
    if (FAILED(hr)) 
		return hr;

	hr=RegisterActiveObject(pPlotSink, CLSID_CPlotNotifySink, ACTIVEOBJECT_WEAK, &dwAppObj);	
    if (FAILED(hr)) 
		return hr;

	return CoLockObjectExternal(pPlotSink, TRUE, TRUE);
}

HRESULT CPlotApiDialog::ExitAutomation(void)
{
	// Remove the active IAsdkPlotNotifySink server from the ROT.
	HRESULT hr;
	hr=CoLockObjectExternal(pPlotSink, FALSE,FALSE);
	if (dwAppObj) 
		hr=RevokeActiveObject(dwAppObj, NULL); 
	OleUninitialize(); 
	return S_OK;
}
