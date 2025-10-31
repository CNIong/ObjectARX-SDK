//
//
// (C) Copyright 2003 by Autodesk, Inc. 
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

#pragma once
#include "resource.h"
#include "afxwin.h"
#include "asdkplotreactor.h"
#include "AcPlPlotConfigMgr.h"
#include "AcPlPlotConfig.h"


// CPlotApiDialog dialog

class CPlotApiDialog : public CDialog
{
	DECLARE_DYNAMIC(CPlotApiDialog)

public:
	CPlotApiDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPlotApiDialog();

// Dialog Data
	enum { IDD = IDD_APIPLOTDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeDevices();
	afx_msg void OnCbnSelchangeMedia();
	afx_msg void OnBnClickedPlot();
	void RefreshDevices(void);
	CComboBox m_Devices;
	CComboBox m_Media;
	double m_Scale;
	AcDbObjectId layoutId;
	BOOL m_Landscape;
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	void RefreshMediaNames();
	CString m_CurrentDevice;
	CString m_CurrentMedia;
	AcDbPlotSettingsValidator* pPSV;
	AcDbPlotSettings *pPlotSettings;
	afx_msg void OnBnClickedPreview();
	afx_msg void OnBnClickedLandscape();
	afx_msg void OnBnClickedFit();
	afx_msg void OnBnClickedBackground();
	void CalcExtents(void);
	afx_msg void OnEnChangeScale();
	BOOL m_bFit;
	BOOL m_Background;
	BOOL m_bPlotToFile;
	CString m_csFilename;
	DWORD dwAppCF;
	DWORD dwAppObj;
	CComPtr<IAsdkPlotNotifySink> pPlotSink;

	afx_msg void OnBnClickedPlottofile();
	afx_msg void OnBnClickedCancel();
	HRESULT InitAutomation(void);
	HRESULT ExitAutomation(void);
};
