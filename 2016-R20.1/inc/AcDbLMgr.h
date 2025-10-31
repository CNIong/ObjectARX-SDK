//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2015 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
//  AcDbLMgr.h - Exported Interface class for Database specific 
//               routines that manipulate and access AcDbLayout 
//               objects.
//

#ifndef   _ACDBLMGR_H
#define   _ACDBLMGR_H

#include "adesk.h"
#include "dbid.h"
#include "dblayout.h"
#include "dblaymgrrctr.h"
#pragma pack (push, 8)

// The maximum number of layouts in a single drawing.
#define  MAX_PSPACE_LAYOUTS     256

class AcDbObjectId;

class AcDbLayoutManager: public AcRxObject  {
  public:

    virtual Acad::ErrorStatus 
        setCurrentLayout        (const ACHAR * newname,
                                 AcDbDatabase* pDb = NULL) = 0;
    virtual Acad::ErrorStatus 
        setCurrentLayoutId      (AcDbObjectId layoutId) = 0;
    virtual const ACHAR *      
        findActiveLayout        (bool allowModel,
                                 const AcDbDatabase* pDb = NULL) = 0;

    virtual AcDbObjectId      
        getActiveLayoutBTRId    (const AcDbDatabase* pDb = NULL) = 0;

    virtual AcDbLayout *      
        findLayoutNamed         (const ACHAR * name, 
                                 bool leaveRecordOpen = false,
                                 const AcDbDatabase* pDb = NULL) = 0;
    virtual Acad::ErrorStatus 
        copyLayout              (const ACHAR * copyname, 
                                 const ACHAR * newname,
                                 AcDbDatabase* pDb = NULL) = 0;

    virtual Acad::ErrorStatus 
        deleteLayout            (const ACHAR * delname,
                                 AcDbDatabase* pDb = NULL) = 0;

    virtual Acad::ErrorStatus 
        createLayout            (const ACHAR *newname,
                                 AcDbObjectId& layoutId, 
                                 AcDbObjectId& blockTableRecId, 
                                 AcDbDatabase* pDb = NULL) = 0;
    virtual Acad::ErrorStatus 
        renameLayout            (const ACHAR * oldname, 
                                 const ACHAR * newname,
                                 AcDbDatabase* pDb = NULL) = 0;

    virtual Acad::ErrorStatus 
        cloneLayout             (AcDbLayout* pLBTR, 
                                 const ACHAR * newname, 
                                 int newTabOrder = 0,
                                 AcDbDatabase* pDb = NULL) = 0;

    virtual AcDbObjectId  
        getNonRectVPIdFromClipId (AcDbObjectId clipId) = 0;

    virtual bool              
        isVpnumClipped          (int index, const AcDbDatabase* pDb = NULL) = 0;

    virtual int               
        countLayouts            (AcDbDatabase *pDb = NULL) = 0;

    virtual void 
        addReactor              (AcDbLayoutManagerReactor * newObj) = 0;

    virtual void 
        removeReactor           (AcDbLayoutManagerReactor * delObj) = 0;
};

Acad::ErrorStatus acdbDoSetupForLayouts(AcDbDatabase* pDatabase,
                                        Adesk::ULongPtr& contextHandle);

Acad::ErrorStatus acdbClearSetupForLayouts(Adesk::ULongPtr contextHandle);

#pragma pack (pop)
#endif // _ACDBLMGR_H
