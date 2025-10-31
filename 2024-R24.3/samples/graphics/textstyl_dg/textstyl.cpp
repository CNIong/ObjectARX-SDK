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
// textstyl.cpp
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


class AsdkTextStyleSamp: public AcDbEntity
{
public:

    ACRX_DECLARE_MEMBERS(AsdkTextStyleSamp);
protected:
    virtual Adesk::Boolean subWorldDraw(AcGiWorldDraw *);
    Acad::ErrorStatus subTransformBy(const AcGeMatrix3d &);
};


ACRX_DXF_DEFINE_MEMBERS(AsdkTextStyleSamp,AcDbEntity,
AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent, 0,\
    ASDKTEXTSTYLESAMP,AsdkTextStyle Sample);

Acad::ErrorStatus AsdkTextStyleSamp::subTransformBy(
    const AcGeMatrix3d &xfm)
{
    return Acad::eOk;
}
 
// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

Adesk::Boolean
AsdkTextStyleSamp::subWorldDraw(AcGiWorldDraw* pW)
{
    AcGePoint3d pos(4.0, 4.0, 0.0);
    AcGeVector3d norm(0.0, 0.0, 1.0);
    AcGeVector3d dir(-1.0, -0.2, 0.0);
    TCHAR *pStr = _T("This is a percent, '%%%'.");
    int len = _tcslen(pStr);
    AcGiTextStyle style;

    AcGeVector3d vec = norm;
    vec = vec.crossProduct(dir);
    dir = vec.crossProduct(norm);

    style.setFileName(_T("txt.shx"));
    style.setBigFontFileName(_T(""));
    int status;
    if (!((status = style.loadStyleRec()) & 1))
        pStr = _T("Font not found.");

    pW->geometry().text(pos, norm, dir, pStr, len,
        Adesk::kFalse, style);

    pos.y += 2.0;

    style.setTrackingPercent(0.8); 
	style.setObliquingAngle(0.5);

	// You must call loadStyleRec() again after changing 
	// the style's properties in order for the current style 
	// settings to be loaded into the graphics system. 
	// Otherwise, the extents calculation may be incorrect.
	//
	style.loadStyleRec(); 
    AcGePoint2d ext = style.extents(pStr, Adesk::kFalse,
        _tcslen(pStr), Adesk::kFalse);

    pW->geometry().text(pos, norm, dir, pStr, len,
        Adesk::kFalse, style);

    // Draw a rectangle around the last text drawn.
    // First you have to create a polyline the size of the
    // bounding box, then you have to transform it to the
    // correct orientation, and then to the location of the
    // text.
    
    // Compute the matrix that orients the box.
    //
    AcGeMatrix3d textMat;
    norm.normalize();
    dir.normalize();
    AcGeVector3d yAxis = norm;
    yAxis = yAxis.crossProduct(dir);
    yAxis.normalize();
    textMat.setCoordSystem(AcGePoint3d(0.0, 0.0, 0.0), dir,
        yAxis, norm);

    // Create the bounding box and enlarge it somewhat.
    //
    double offset = ext.y / 2.0;
    AcGePoint3d verts[5];
    verts[0] = verts[4] = AcGePoint3d(-offset, -offset, 0.0);
    verts[1] = AcGePoint3d(ext.x + offset, -offset, 0.0);
    verts[2] = AcGePoint3d(ext.x + offset, ext.y + offset, 0.0);
    verts[3] = AcGePoint3d(-offset, ext.y + offset, 0.0);

    // Orient and then translate each point in the
    // bounding box.
    //
    for (int i = 0; i < 5; i++) {
        verts[i].transformBy(textMat);
        verts[i].x += pos.x;
        verts[i].y += pos.y;
        verts[i].z += pos.z;
    }
    pW->geometry().polyline(5, verts);

    return Adesk::kTrue;
}

// END CODE APPEARING IN SDK DOCUMENT.

void
addAsdkTextStyleSampObject()
{
    AsdkTextStyleSamp *pNewObj = new AsdkTextStyleSamp;

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

static void initAsdkTextStyleSamp()
{
    AsdkTextStyleSamp::rxInit();
    acrxBuildClassHierarchy();

    acedRegCmds->addCommand(_T("ASDK_TEXTSTYLE_SAMP"),
                            _T("ASDKSTYLESAMP"),
                            _T("STYLESAMP"),
                            ACRX_CMD_TRANSPARENT,
                            addAsdkTextStyleSampObject);
}

extern "C" AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* appId) 
{
    switch(msg) {
	case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(appId);
		acrxDynamicLinker->registerAppMDIAware(appId);
	    initAsdkTextStyleSamp();
	    break;
	case AcRx::kUnloadAppMsg:
	    acedRegCmds->removeGroup(_T("ASDK_TEXTSTYLE_SAMP"));
            deleteAcRxClass(AsdkTextStyleSamp::desc());
    }
    return AcRx::kRetOK;
}
