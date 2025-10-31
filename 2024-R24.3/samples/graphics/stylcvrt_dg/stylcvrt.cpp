//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
// stylcvrt.cpp
//

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include <string.h>
#include <stdio.h>
#include "aced.h"
#include "dbsymtb.h"
#include "dbapserv.h"
#include "acgi.h"
#include "tchar.h"
#include "Ac64BitHelpers.h"



// globals
//
static AcGiTextStyle AsdkStyle;


class AsdkTxtStyleSamp: public AcDbEntity
{
public:

    ACRX_DECLARE_MEMBERS(AsdkTxtStyleSamp);
protected:
    virtual Adesk::Boolean subWorldDraw(AcGiWorldDraw *);
    Acad::ErrorStatus subTransformBy(const AcGeMatrix3d &);
};


ACRX_DXF_DEFINE_MEMBERS(AsdkTxtStyleSamp,AcDbEntity,
AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent, 0,\
    AsdkTxtStyleSamp,AsdkTextStyle Sample);

Acad::ErrorStatus AsdkTxtStyleSamp::subTransformBy(
    const AcGeMatrix3d &xfm)
{
    return Acad::eOk;
}
 

Adesk::Boolean
AsdkTxtStyleSamp::subWorldDraw(AcGiWorldDraw* pW)
{
    AcGePoint3d pos(0.0, 0.0, 0.0);
    AcGeVector3d norm(0.0, 0.0, 1.0);
    AcGeVector3d dir(1.0, 0.2, 0.0);
    TCHAR *pStr = _T("Test string");
    int len = _tcslen(pStr);
    
    pW->geometry().text(pos, norm, dir, pStr, len,
        Adesk::kFalse, AsdkStyle);

    return Adesk::kTrue;
}


// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

// Get an AcGiTextStyle from an acDbTextStyleTableRecord.
// Try to map as many characteristics as possible.
//
void
getTextStyle(AcGiTextStyle& newStyle, AcDbObjectId styleId)
{
    AcDbTextStyleTableRecord *pOldStyle;
    acdbOpenObject(pOldStyle, styleId,
        AcDb::kForRead);
    const TCHAR *pTmpStr;
    pOldStyle->fileName(pTmpStr);
    newStyle.setFileName(pTmpStr);

    pOldStyle->bigFontFileName(pTmpStr);
    newStyle.setBigFontFileName(pTmpStr);

    newStyle.setTextSize(pOldStyle->textSize());
    newStyle.setXScale(pOldStyle->xScale());
    newStyle.setObliquingAngle(pOldStyle->obliquingAngle());

    pOldStyle->close();
    newStyle.loadStyleRec();
}

// END CODE APPEARING IN SDK DOCUMENT.

void
addAsdkTxtStyleSampObject()
{
    // First set up the styleId global with a valid
    // ObjectId for an AcDbTextStyleTableRecord.
    //
    AcDbTextStyleTable *pStyleTable;
    acdbHostApplicationServices()->workingDatabase()
        ->getSymbolTable(pStyleTable, AcDb::kForRead);
   
    AcDbTextStyleTableIterator *pIterator;
    pStyleTable->newIterator(pIterator);

    // get ObjectId of first record in table
    //
    AcDbObjectId styleId;
    pIterator->getRecordId(styleId);

    delete pIterator;
    pStyleTable->close();
    
    // convert the AcDbTextStyleTableRecord to an
    // AcGiTextStyle using the global AsdkStyle
    // AcGiTextStyle object as the recipient.
    //
    getTextStyle(AsdkStyle, styleId);


    // Ok,  now make one of our AsdkTxtStyleSamp entities
    // and add it to Model Space.
    
    AsdkTxtStyleSamp *pNewObj = new AsdkTxtStyleSamp;

    AcDbBlockTable *pBlockTable;
    acdbHostApplicationServices()->workingDatabase()
        ->getSymbolTable(pBlockTable, AcDb::kForRead);

    AcDbBlockTableRecord *pBlock;
    pBlockTable->getAt(ACDB_MODEL_SPACE, pBlock,
        AcDb::kForWrite);

    AcDbObjectId objId;
    pBlock->appendAcDbEntity(objId, pNewObj);

    pBlockTable->close();
    pBlock->close();
    pNewObj->close();
}

static void initAsdkTxtStyleSamp()
{
    AsdkTxtStyleSamp::rxInit();
    acrxBuildClassHierarchy();

    acedRegCmds->addCommand(_T("ASDK_STYLE_CONVERT_SAMP"),
                            _T("ASDKSTYLECVRT"),
                            _T("STYLECVRT"),
                            ACRX_CMD_TRANSPARENT,
                            addAsdkTxtStyleSampObject);
}

extern "C" AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* appId) 
{
    switch(msg) {
    case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(appId);
        acrxDynamicLinker->registerAppMDIAware(appId);
        initAsdkTxtStyleSamp();
        break;
    case AcRx::kUnloadAppMsg:
        acedRegCmds->removeGroup(_T("ASDK_STYLE_CONVERT_SAMP"));
            deleteAcRxClass(AsdkTxtStyleSamp::desc());
    }
    return AcRx::kRetOK;
}
