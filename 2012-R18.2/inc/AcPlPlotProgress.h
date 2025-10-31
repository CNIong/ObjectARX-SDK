#ifndef ACPLPLOTPROGRESS_H
#define ACPLPLOTPROGRESS_H
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
//  DESCRIPTION:  Header for AcPlPlotProgress.
//

#include "AdAChar.h"
#include "AcPl.h"

class AcPlPlotProgressDialog;

class ADESK_NO_VTABLE AcPlPlotProgress
{
public:

    enum SheetCancelStatus {
        kSheetContinue,
        kSheetCanceledByCancelButton,
        kSheetCanceledByCancelAllButton,
        kSheetCanceledByCaller,
        kSheetCancelStatusCount
    };

    enum PlotCancelStatus {
        kPlotContinue,
        kPlotCanceledByCaller,
        kPlotCanceledByCancelAllButton,
        kPlotCancelStatusCount
    };

    virtual bool isPlotCancelled() const = 0;
    virtual void setPlotCancelStatus(PlotCancelStatus Cancel) = 0;
    virtual PlotCancelStatus plotCancelStatus() const = 0;

    virtual void setPlotProgressRange(int nLower, int nUpper) = 0;
    virtual void getPlotProgressRange(int &nLower, int &nUpper) const = 0;

    virtual void setPlotProgressPos(int nPos) = 0;
    virtual int  plotProgressPos() const = 0;

    virtual bool isSheetCancelled() const = 0;
    virtual void setSheetCancelStatus(SheetCancelStatus Cancel) = 0;
    virtual SheetCancelStatus sheetCancelStatus() const = 0;

    virtual void setSheetProgressRange(int nLower, int nUpper) = 0;
    virtual void getSheetProgressRange(int &nLower, int &nUpper) const = 0;

    virtual void setSheetProgressPos(int nPos) = 0;
    virtual int  sheetProgressPos() const = 0;

    virtual bool setIsVisible(bool bVisible) = 0;
    virtual bool isVisible() const = 0;

    virtual bool setStatusMsgString(const ACHAR *pMsg) = 0;
    virtual bool getStatusMsgString(ACHAR *& pMsg) const = 0;

    virtual void heartbeat(void) = 0;
};

typedef void (*ACPLPLTPRGHELPPROC)(AcPlPlotProgressDialog *pAcPlPlotProgressDialog);

class AcPlPlotProgressDialog : public AcPlPlotProgress 
{
public:
    enum PlotMSGIndex {
        kDialogTitle,
        kSheetName,
        kSheetNameToolTip,
        kStatus,
        kSheetProgressCaption,
        kSheetSetProgressCaption,
        kMsgCancelling,
        kMsgCancellingCurrent,
        kCancelSheetBtnMsg,
        kCancelJobBtnMsg,
        kMsgCount
    };

    virtual bool onBeginPlot() = 0;
    virtual bool onEndPlot() = 0;

    virtual bool onBeginSheet() = 0;
    virtual bool onEndSheet() = 0;

    virtual bool setPlotMsgString(PlotMSGIndex index, const ACHAR *pMsg) = 0;
    virtual bool getPlotMsgString(PlotMSGIndex index, ACHAR *& pMsg) const = 0;
    
    virtual bool isSingleSheetPlot() const = 0;

    virtual void destroy() = 0;
};

ACPL_PORT AcPlPlotProgressDialog* __stdcall
acplCreatePlotProgressDialog( HWND hParent, 
                          bool bPreview = false, 
                          int nSheets = 1,
                          ACPLPLTPRGHELPPROC hlpProc = NULL,
                          bool bShowCancelSheetButton = true);

#endif // ACPLPLOTPROGRESS_H
