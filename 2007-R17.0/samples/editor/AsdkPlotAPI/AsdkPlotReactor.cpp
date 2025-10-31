//
//
// (C) Copyright 2003-2006 by Autodesk, Inc. 
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

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include ".\asdkplotreactor.h"
#include "asdkplotreactor.h"



AsdkPlotReactor::AsdkPlotReactor(void)
{
	// When this reactor is created upon demand load of the module,
	// it tries to find the (singleton) active IAsdkPlotNotifySink object in the ROT
	// and connects with it here.
	CComPtr<IUnknown> pUnk;
	m_PlotClient.m_lpDispatch=NULL;
	m_PlotClient.m_bAutoRelease=TRUE;
	if(GetActiveObject(CLSID_CPlotNotifySink,NULL,&pUnk)==S_OK)
		if(pUnk->QueryInterface(IID_IDispatch,(void**) &pDisp)==S_OK)
		{
			m_PlotClient.AttachDispatch(pDisp);
			if(m_PlotClient.m_lpDispatch)
				m_PlotClient.SendPlotEvent(_T("Reactor Instantiated"));
		}
}

AsdkPlotReactor::~AsdkPlotReactor(void)
{
	// detach from the client
	if(m_PlotClient.m_lpDispatch)
		m_PlotClient.SendPlotEvent(_T("Reactor Destroyed"));
	m_PlotClient.ReleaseDispatch();
}

ACPL_PORT void AsdkPlotReactor::beginPlot(AcPlPlotProgress* pPlotProgress, PlotType type)
{
	if(m_PlotClient.m_lpDispatch)
		m_PlotClient.SendPlotEvent(_T("Begin Plot"));
}

ACPL_PORT void AsdkPlotReactor::beginDocument(AcPlPlotInfo& plotInfo, const TCHAR* pDocname,
                            long nCopies, bool bPlotToFile,
                            const TCHAR* pFilename)
{
	if(m_PlotClient.m_lpDispatch)
		m_PlotClient.SendPlotEvent(_T("Begin Document"));
}

ACPL_PORT void AsdkPlotReactor::beginPage(AcPlPlotPageInfo& pageInfo, AcPlPlotInfo& plotInfo,
                        bool bLastPage)
{
	if(m_PlotClient.m_lpDispatch)
		m_PlotClient.SendPlotEvent(_T("Begin Page"));
}

ACPL_PORT void AsdkPlotReactor::endPage(AcPlPlotProgress::SheetCancelStatus status)
{
	if(m_PlotClient.m_lpDispatch)	
		m_PlotClient.SendPlotEvent(_T("End Page"));
}

ACPL_PORT void AsdkPlotReactor::endDocument(AcPlPlotProgress::PlotCancelStatus status)
{
	if(m_PlotClient.m_lpDispatch)
		m_PlotClient.SendPlotEvent(_T("End Document"));
}

ACPL_PORT void AsdkPlotReactor::endPlot(AcPlPlotProgress::PlotCancelStatus status)
{
	if(m_PlotClient.m_lpDispatch)
		m_PlotClient.SendPlotEvent(_T("End Plot"));
}

ACPL_PORT void AsdkPlotReactor::plotCancelled()
{
	if(m_PlotClient.m_lpDispatch)
		m_PlotClient.SendPlotEvent(_T("Plot Cancelled"));
}

ACPL_PORT void AsdkPlotReactor::pageCancelled()
{
	if(m_PlotClient.m_lpDispatch)
		m_PlotClient.SendPlotEvent(_T("Page Cancelled"));
}