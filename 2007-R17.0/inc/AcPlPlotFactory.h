#ifndef   _ACPLPLOTFACTORY_H
#define   _ACPLPLOTFACTORY_H
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
//
//  AcPlPlotFactory   - makes plot engines
//
#include "AcPl.h"

class AcPlPlotEngine;

class AcPlPlotFactory
{
public:

    enum PreviewEngineFlags {
        kShowPlot            = 0x0001,  // Allow plot from preview state
        kShowNextSheet       = 0x0002,  // Allow "Next Sheet" from preview state
        kShowPreviousSheet   = 0x0004   // Allow "Previous Sheet" from preview state
    };

    static ACPL_PORT Acad::ErrorStatus createPublishEngine(AcPlPlotEngine *& pEngine);
    static ACPL_PORT Acad::ErrorStatus createPreviewEngine(AcPlPlotEngine *& pPreview, 
                                                           long nPreviewFlags = kShowPlot);
};

// Possible plotting system states
enum ProcessPlotState
{
    kNotPlotting = 0,       // No plot in progress
    kForegroundPlotting,    // Plot is in progress in the current process
    kBackgroundPlotting     // Plot is in progress in a background process, 
                            // this process is the foreground process.
};

// Method for determining current state of the plotting subsystem
ACPL_PORT ProcessPlotState __stdcall acplProcessPlotState();

#endif // _ACPLPLOTFACTORY_H
