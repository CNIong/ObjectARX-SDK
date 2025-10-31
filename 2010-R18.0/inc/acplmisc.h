
//////////////////////////////////////////////////////////////////////////////
//
//             (C) Copyright 1994-2009 by Autodesk, Inc.
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

#include "acpldsddata.h"

class AcPlPlotConfig;

/// <summary>
/// This function publishes the data in dsdDataObj to a device or DWF file specified
/// and configured by the data in the PlotConfig object pointed to by pConfig.
///
/// If bShowPlotProgress is true, then a plot progress dialog/meter will be displayed.
/// </summary>
/// <param name="dsdDataObj">Input object containing data to be plotted</param>
/// <param name="pConfig">Input pointer to plotConfig object</param>
/// <param name="bShowPlotProgress">Input bool specifying whether or not to display
/// a plot progress dialog</param>
void acplPublishExecute(AcPlDSDData dsdDataObj, AcPlPlotConfig* pConfig, 
    bool bShowPlotProgress);
