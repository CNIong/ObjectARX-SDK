#ifndef ACPLPLOTREACTOR_H
#define ACPLPLOTREACTOR_H
//
//  (C) Copyright 2003-2006 by Autodesk, Inc.  All rights reserved.
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
//
//  DESCRIPTION:  Header for Document and Document Manager Classes.
//

#include "AdAChar.h"
#include "AcPl.h"
#include "AcPlObject.h"

class AcPlPlotInfo;
class AcPlPlotPageInfo;
class AcPlPlotProgress;

class AcPlPlotReactor : public AcRxObject // API
{
public:

    // Plot Type
    enum PlotType {
        kPlot,
        kPreview,
        kBackgroundPackaging,
        kBackgroundPlot
    };

    // Notification for begin of plot
    ACPL_PORT virtual void beginPlot(AcPlPlotProgress* pPlotProgress, PlotType type);

    // Notification for beginning of an document
    ACPL_PORT virtual void beginDocument(AcPlPlotInfo& plotInfo,
                                         const ACHAR * pDocname,
                               long nCopies = 1, bool bPlotToFile = false,
                               const ACHAR * pFilename = NULL);

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

    // Destructor
    ACPL_PORT virtual ~AcPlPlotReactor();
    
protected:
    ACPL_PORT AcPlPlotReactor();
};

#endif // ACPLPLOTREACTOR_H
