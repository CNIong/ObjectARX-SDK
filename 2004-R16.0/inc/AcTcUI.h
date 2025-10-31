//////////////////////////////////////////////////////////////////////////////
//
//                 (C) Copyright 1982-2002 by Autodesk, Inc.
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
//////////////////////////////////////////////////////////////////////////////
//
// Name:            AcTcUi.h
//
// Description:     Place for all the exported global functions 
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTCUI_H__
#define __ACTCUI_H__

#include "adui.h"
#include <afxtempl.h>

class CAcTcUiManager;
class CAcTcUiToolPaletteSet;
class CAcTcUiToolPalette;
class CAcTcUiCatalogView;
class AcTcCatalogItem;
class AcTcCatalog;
class AcTcStockTool;


typedef CTypedPtrArray<CPtrArray, AcTcCatalogItem*> AcTcCatalogItemArray;
typedef CTypedPtrArray<CPtrArray, AcTcStockTool*>   AcTcStockToolArray;
typedef CTypedPtrArray<CPtrArray, AcTcCatalog*>     AcTcCatalogArray;
typedef CTypedPtrArray<CPtrArray, CAcTcUiToolPaletteSet*> AcTcUiToolPaletteSetArray;
typedef CTypedPtrArray<CPtrArray, CAcTcUiToolPalette*> AcTcUiToolPaletteArray;
typedef CTypedPtrArray<CPtrArray, CAcTcUiCatalogView*> AcTcUiCatalogViewArray;



// Drag and drop formats
//
#define ACTCUI_DRAGFORMAT_CUSTOM        (0x1 << 0)
#define ACTCUI_DRAGFORMAT_IDROP         (0x1 << 1)
#define ACTCUI_DRAGFORMAT_HDROP         (0x1 << 2)

// For creating a new default palette set
#define ACTCUI_CNPS_NOCREATEWINDOW      (0x1 << 0)
#define ACTCUI_CNPS_NOADD               (0x1 << 1)
#define ACTCUI_CNPS_CREATEHIDDEN        (0x1 << 2)

// Clipboard formats
//
#define CF_ACTCUI_CATALOG_ITEM          "CF_ACTC_CATALOG_ITEM"
#define CF_ACTCUI_CATALOG_ITEM_HEADER   "CF_ACTCUI_CATALOG_ITEM_HEADER"
#define CF_IDROP_ACTCUI_TOOL            "CF_IDROP.XML_ACTCUI_TOOL"
#define CF_IDROP_ACTCUI_PALETTE         "CF_IDROP.XML_ACTCUI_PALETTE"
#define CF_IDROP_ACTCUI_PACKAGE         "CF_IDROP.XML_ACTCUI_PACKAGE"
#define CF_IDROP_ACTCUI_CATEGORY        "CF_IDROP.XML_ACTCUI_CATEGORY"
#define CF_IDROP_ACTCUI_CATALOG         "CF_IDROP.XML_ACTCUI_CATALOG"
#define CF_IDROP_ACTCUI_STOCKTOOL       "CF_IDROP.XML_ACTCUI_STOCKTOOL"
#define CF_ACTCUI_TOOLBAR_ITEM          "CF_ACTCUI_TOOLBAR_ITEM"

// AcTcUiPasteItems flags
//
#define ACTCUI_PI_SHOW_PROGRESS         (0x1 << 0)
#define ACTCUI_PI_USE_NEW_IDS           (0x1 << 1)
#define ACTCUI_PI_BREAK_SOURCE_LINK     (0x1 << 2)      // For internal use
#define ACTCUI_PI_NOTIFY_TOOLS          (0x1 << 3)      // For internal use


// Structure for drag and drop header information
//
typedef struct ACTCUI_DRAG_HEADER
{
    DWORD               mdwDragFormat;      // Dragged object: ACTCUIDRAGFORMATCUSTOM, etc.
    CLIPFORMAT          mcfClipFormat;      // Clipformat: CF_ACTC_CATALOG_ITEM, etc.
    BOOL                mbAutoCADSource;    // TRUE if source is AutoCAD
    DWORD               mdwSourceProcessId; // Source process ID
    GUID                mRootId;            // Root id of the catalog items being dragged
    GUID                mParentId;          // Parent id of the catalog items being dragged
    BOOL                mbReadOnlySource;   // True if source is read-only
    int                 mnCount;            // Number of items being dragged
    int                 mnStockTools;       // Number of stock tool items being dragged
    DWORD               mdwItemTypes;       // Item types being dragged
} ACTCUI_DRAG_HEADER;


__declspec(dllexport) CAcTcUiManager* AcTcUiGetManager(void);
__declspec(dllexport) BOOL AcTcUiCopyItems  (COleDataSource* pDataSource,
                                             const AcTcCatalogItemArray* pItems,
                                             BOOL bAutoCADSource);
__declspec(dllexport) BOOL AcTcUiGetDragInfo(IDataObject* pDataObject,
                                             ACTCUI_DRAG_HEADER* pHeader);
__declspec(dllexport) BOOL AcTcUiPasteItems (IDataObject* pDataObject,
                                             AcTcCatalogItemArray* pItems,
                                             AcTcCatalogItemArray* pStockTools,
                                             DWORD dwFlag = ACTCUI_PI_SHOW_PROGRESS);
__declspec(dllexport) CAcTcUiToolPaletteSet* AcTcUiGetToolPaletteWindow(void);


#endif //__ACTCUI_H__
