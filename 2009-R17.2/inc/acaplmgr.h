#ifndef   _ACAPLMGR_H
#define   _ACAPLMGR_H
// 
// (C) Copyright 1993-2006 by Autodesk, Inc. 
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
//  AcApLMgr.h - Interface class for Applicaton specific routines
//               that manipulate and access AcDbLayout objects.
//
#include "AcDbLMgr.h"
#pragma pack (push, 8)

class AcDbObjectId;
class AcGePoint2d;
class AcGePoint3d;

// All this just to forward declare AcGePoint2dArray.
template <class T> class AcArrayMemCopyReallocator;
template <class T, class R = AcArrayMemCopyReallocator<T> > class AcArray;
typedef AcArray<AcGePoint2d> AcGePoint2dArray;


class AcApLayoutManager : public AcDbLayoutManager {
  public:
    // application methods
    //
    virtual int               
    pageSetup                 (AcDbObjectId layoutBTRId = AcDbObjectId::kNull, 
                               void* pParent = NULL, 
                               Adesk::Boolean isPageSetupDlg = TRUE) = 0;
    virtual void              
    updateCurrentPaper        (Adesk::Boolean zoomToPaper = FALSE  ) = 0;

    virtual void              
    updateLayoutTabs          () = 0;

    virtual const ACHAR *      
    findActiveTab             () = 0;
                              
    virtual Adesk::Boolean    
    showTabs                  () = 0;

    virtual void              
    setShowTabs               (Adesk::Boolean showTabs           ) = 0;

    virtual Adesk::Boolean    
    showPageSetup             () = 0;

    virtual void              
    setShowPageSetup          (Adesk::Boolean showPageSetupDlg   ) = 0;

    virtual Adesk::Boolean    
    createViewports           () = 0;

    virtual void              
    setCreateViewports        (Adesk::Boolean createViewports    ) = 0;

    virtual Adesk::Boolean    
    showPaperBackground       () = 0;

    virtual void              
    setShowPaperBackground    (Adesk::Boolean showPaperBackground) = 0;

    virtual Adesk::Boolean    
    showPaperMargins          () = 0; 

    virtual void              
    setShowPaperMargins       (Adesk::Boolean showPaperMargins   ) = 0;

    virtual Adesk::Boolean    
    showPrintBorder           () = 0;

    virtual void              
    setShowPrintBorder        (Adesk::Boolean showPrintBorder    ) = 0;

    virtual ACHAR *            
    getNextNewLayoutName      (AcDbDatabase* useDb = NULL) = 0;

    virtual void 
    setDefaultPlotConfig      (AcDbObjectId layoutBTRId) = 0;

    virtual Acad::ErrorStatus   
    getClipBoundaryElaboration(AcDbObjectId clipId,
                               AcGePoint2dArray *&clipBoundary) = 0;

    virtual Acad::ErrorStatus 
    pointInViewports          (const AcGePoint3d &pickPt, 
                               AcDbObjectIdArray &viewports) = 0;
};
#pragma pack (pop)
#endif // _ACAPLMGR_H

