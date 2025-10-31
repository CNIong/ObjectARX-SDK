#ifndef ACPLHOSTAPPSERVICES_H
#define ACPLHOSTAPPSERVICES_H
//
//  (C) Copyright 2003-2009 by Autodesk, Inc.  All rights reserved.
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
//  DESCRIPTION:  Interface definition for Host Plot Services.
//

class AcPlPlotLogger;
class AcadPlotInternalServices;



class ADESK_NO_VTABLE AcPlHostAppServices
{
public:
    enum PlotStatus {
        kSheetIdxAndName = -5, kDisableCancelSheet = -4, kDwfFilePlotted = -3, kPlottingMsg = -2,
        kNoPlotYet = -1, kPlotStart = 0, kViewPlotLog = 1, kPlotSuccessful = 2,
        kPlotHadErrors = 3, kPlotHadSystemError = 4, kViewPlottedFile = 5, kViewFileWhenSuccessful = 6
    };

    virtual AcPlPlotLogger * getPlotLogger(void) = 0;
    virtual const AcadPlotInternalServices* acadInternalServices() = 0;

    virtual void updatePlotJobStatus(enum AcPlHostAppServices::PlotStatus nStatus, const ACHAR *szPlotMsg) = 0;
};

ACPL_PORT Acad::ErrorStatus AcPlSetHostAppServices(AcPlHostAppServices *pHostServices);
ACPL_PORT AcPlHostAppServices *AcPlGetHostAppServices();

#endif // ACPLHOSTAPPSERVICES_H
