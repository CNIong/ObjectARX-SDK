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

#include "stdafx.h"
#include "AsdkPlotApiDialog.h"
#include "casdkplotnotifysink0.h"

class AsdkPlotReactor :
	public AcPlPlotReactor
{
public:
	AsdkPlotReactor(void);
	~AsdkPlotReactor(void);

    // Notification for begin of plot
    ACPL_PORT virtual void beginPlot(AcPlPlotProgress* pPlotProgress, PlotType type);

    // Notification for beginning of an document
    ACPL_PORT virtual void beginDocument(AcPlPlotInfo& plotInfo, const char* pDocname,
                               long nCopies = 1, bool bPlotToFile = false,
                               const char* pFilename = NULL);

    // Notification for begin page
    ACPL_PORT virtual void beginPage(AcPlPlotPageInfo& pageInfo, AcPlPlotInfo& plotInfo,
                           bool bLastPage);
    
    // Notification for end page
    ACPL_PORT virtual void endPage(AcPlPlotProgress::SheetCancelStatus status);

    // Notification for end of an document
    ACPL_PORT virtual void endDocument(AcPlPlotProgress::PlotCancelStatus status);

    // Notification that plot has ended
    ACPL_PORT virtual void endPlot(AcPlPlotProgress::PlotCancelStatus status);

    // Notification that plot was cancelled
    ACPL_PORT virtual void plotCancelled();

    // Notification that page was cancelled
    ACPL_PORT virtual void pageCancelled();

	// The reactor holds a pointer to the client to send notifications to the 
	// IAsdkPlotNotifySink server in the original process (instantiated with the PLOTAPI command)
	CAsdkPlotNotifySinkClient m_PlotClient;
	IDispatch *pDisp;
};
