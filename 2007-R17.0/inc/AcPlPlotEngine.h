#ifndef   _ACPLPLOTENGINE_H
#define   _ACPLPLOTENGINE_H
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
//
//  AcPlPlotPageInfo      - interface for prescan info
//  AcPlPreviewEngine     - interface with plotting pipeline for previewing
//  AcPlPlotEngine        - interface with plotting pipeline for plotting
//

#include "AdAChar.h"
#include "AcPl.h"
#include "AcPlObject.h"

class AcViewport;
class PlotEnvironment;
class AcPlPlotProgress;
class AcPlPlotInfo;
class AcDbPlotSettings;
class AcPlPlotConfig;

// Status values for ACPL_PREVIEWENDPLOT
enum PreviewStatus {
    kNormal = 0,
    kPlot,
    kCancel,
    kNext,
    kPrevious
};

// Struct ACPL_PREVIEWENDPLOT, in/out parameter modified by AcPlPlotEngine::endPlot()
// if the engine was created with AcPlPlotFactory::createPreviewEngine.
struct ACPL_PREVIEWENDPLOT {
    PreviewStatus nStatus;
};

class AcPlPlotPageInfo : public AcPlObject
{
    ACPL_DECLARE_MEMBERS(AcPlPlotPageInfo);

public:
    ACPL_PORT AcPlPlotPageInfo();
    ACPL_PORT virtual ~AcPlPlotPageInfo();

    ACPL_PORT long entityCount() const;
    ACPL_PORT long rasterCount() const;
    ACPL_PORT long oleObjectCount() const;
    ACPL_PORT long gradientCount() const;
    ACPL_PORT long shadedViewportType() const;
};

class ADESK_NO_VTABLE AcPlPlotEngine {
public:
    virtual Acad::ErrorStatus beginPlot(AcPlPlotProgress* pPlotProgress, void* pParams = NULL);
    virtual Acad::ErrorStatus endPlot(void* pParams = NULL);
    
    // This plotInfo must not be deleted until endDocument().
    virtual Acad::ErrorStatus beginDocument(AcPlPlotInfo& plotInfo, 
                                            const ACHAR * pDocname,
                                            void *pParams = NULL,
                                            long nCopies = 1, 
                                            bool bPlotToFile = false, 
                                            const ACHAR * pFileName = NULL);
    virtual Acad::ErrorStatus endDocument(void* pParams = NULL);
    
    // This plotInfo may be the same as for beginDocument().
    virtual Acad::ErrorStatus beginPage(AcPlPlotPageInfo& pageInfo, 
                                        AcPlPlotInfo& plotInfo, 
                                        bool bLastPage, 
                                        void* pParams = NULL);
    virtual Acad::ErrorStatus endPage(void* pParams = NULL);
    
    virtual Acad::ErrorStatus beginGenerateGraphics(void* pParams = NULL);
    virtual Acad::ErrorStatus beginGenerateGraphics(AcViewport*& pViewport, void* pParams = NULL);
    virtual Acad::ErrorStatus endGenerateGraphics(void* pParams = NULL);
    
    virtual void destroy();
    virtual bool isBackgroundPackaging() const;
};


#endif // _ACPLPLOTENGINE_H
