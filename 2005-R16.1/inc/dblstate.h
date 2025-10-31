#ifndef ACDB_LSTATE_H
#define ACDB_LSTATE_H
//
// (C) Copyright 1999-2003 by Autodesk, Inc.
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
// DESCRIPTION: AcDbLayerStateManager class definition.
//
// WRITTEN: 11/99 by Anil Patel

#include "dbmain.h"
#include "acarray.h"

#pragma pack(push, 8)


class AcDbImpLayerStateManager;

class AcDbLayerStateManager: public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbLayerStateManager);
    // Construction/destruction
    AcDbLayerStateManager();
    AcDbLayerStateManager(AcDbDatabase *pHostDb);
    virtual ~AcDbLayerStateManager();

    enum LayerStateMask {
        kNone           = 0x0000,
        kOn             = 0x0001,
        kFrozen         = 0x0002,
        kLocked         = 0x0004,
        kPlot           = 0x0008,
        kNewViewport    = 0x0010,
        kColor          = 0x0020,
        kLineType       = 0x0040,
        kLineWeight     = 0x0080,
        kPlotStyle      = 0x0100,
        kCurrentViewport = 0x0200,
        kAll            = kOn | kFrozen | kLocked | kPlot | kNewViewport |
                          kColor | kLineType | kLineWeight | kPlotStyle |
                          kCurrentViewport,

        kStateIsHidden  = 0x8000        
    };

    enum {
        kUndefDoNothing = 0,
        kUndefTurnOff = 1,
        kUndefFreeze = 2
    };

    // Service methods
    AcDbObjectId        layerStatesDictionaryId(bool bCreateIfNotPresent=false);
    bool                hasLayerState(const char *sName);
    Acad::ErrorStatus   saveLayerState(const char *sName, LayerStateMask mask);
    Acad::ErrorStatus   restoreLayerState(const char *sName);
    Acad::ErrorStatus   setLayerStateMask(const char *sName, 
                                          LayerStateMask mask);
    Acad::ErrorStatus   getLayerStateMask(const char *sName,
                                          LayerStateMask &returnMask);
    Acad::ErrorStatus   deleteLayerState(const char *sName);
    Acad::ErrorStatus   renameLayerState(const char *sName,
                                         const char *sNewName);
    Acad::ErrorStatus   importLayerState(const char *sFilename);
    Acad::ErrorStatus   exportLayerState(const char *sNameToExport,
                                         const char *sFilename);

    Acad::ErrorStatus   saveLayerState(const char *sName, LayerStateMask mask, const AcDbObjectId& idVp);
    Acad::ErrorStatus   restoreLayerState(const char *sName, const AcDbObjectId& idVp, int nUndefOff = 0, const LayerStateMask* pClientMask = NULL);

    Acad::ErrorStatus   setLayerStateDescription(const char* sName, const char* sDesc);
    Acad::ErrorStatus   getLayerStateDescription(const char* sName, char*& sDesc);
    bool                layerStateHasViewportData(const char* sName);

private:
    friend class AcDbImpDatabase;
    AcDbImpLayerStateManager *mpImpLSM;
};

#pragma pack(pop)

#endif
