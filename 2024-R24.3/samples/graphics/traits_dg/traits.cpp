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
// traits.cpp
//
// This sample demonstrates using many of the AcGiSubEntityTraits
// class functions for controlling the properties of the graphics
// primitives drawn during entity elaboration.

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "aced.h"
#include "dbsymtb.h"
#include "dbapserv.h"
#include "acgi.h"
#include "tchar.h"



// function prototypes
//
// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

static Acad::ErrorStatus
getLinetypeIdFromString(const TCHAR* str, AcDbObjectId& id);
static Acad::ErrorStatus
getLayerIdFromString(const TCHAR* str, AcDbObjectId& id);

// END CODE APPEARING IN SDK DOCUMENT.

// Helpful constants for setting attributes:
// COLOR
//
static const Adesk::UInt16 kColorByBlock   = 0;
static const Adesk::UInt16 kRed            = 1;
static const Adesk::UInt16 kYellow         = 2;
static const Adesk::UInt16 kGreen          = 3;
static const Adesk::UInt16 kCyan           = 4;
static const Adesk::UInt16 kBlue           = 5;
static const Adesk::UInt16 kMagenta        = 6;
static const Adesk::UInt16 kWhite          = 7;
static const Adesk::UInt16 kColorByLayer   = 256;


class AsdkTraitsSamp: public AcDbEntity
{
public:

    ACRX_DECLARE_MEMBERS(AsdkTraitsSamp);
protected:
    virtual Adesk::Boolean subWorldDraw(AcGiWorldDraw *);
    Acad::ErrorStatus subTransformBy(const AcGeMatrix3d &);
};


ACRX_DXF_DEFINE_MEMBERS(AsdkTraitsSamp,AcDbEntity,
AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent, 0,\
    ASDKTRAITSSAMP,AsdkTraits Sample);

Acad::ErrorStatus AsdkTraitsSamp::subTransformBy(
    const AcGeMatrix3d &xfm)
{
    return Acad::eOk;
}
 
// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

Adesk::Boolean
AsdkTraitsSamp::subWorldDraw(AcGiWorldDraw* pW)
{
    // At this point, the current property traits are
    // the entity's property traits.  If the current
    // property traits are changed and you want to
    // reapply the entity's property traits, this is
    // the place to save them.
    // 
    Adesk::UInt16 entity_color
        = pW->subEntityTraits().color();
    AcDbObjectId  entity_linetype
        = pW->subEntityTraits().lineTypeId();
    AcDbObjectId  entity_layer
        = pW->subEntityTraits().layerId();

    // Override the current color and make it blue.
    //
    pW->subEntityTraits().setColor(kBlue);

    // Draw a blue 3-point polyline.
    //
    int num_pts = 3;
    AcGePoint3d *pVerts = new AcGePoint3d[num_pts];
    pVerts[0] = AcGePoint3d(0.0, 0.0, 0);
    pVerts[1] = AcGePoint3d(1.0, 0.0, 0);
    pVerts[2] = AcGePoint3d(1.0, 1.0, 0);
    
    pW->geometry().polyline(num_pts, pVerts);

    // Force the current color to use current layer's color.
    //
    pW->subEntityTraits().setColor(kColorByLayer);

    // Force current line type to "DASHDOT".  If
    // "DASHDOT" is not loaded, the current line
    // type will still be in effect.
    //
    AcDbObjectId dashdotId;
    if (getLinetypeIdFromString(_T("DASHDOT"), dashdotId)
        == Acad::eOk)
    {
        pW->subEntityTraits().setLineType(dashdotId);
    }

    // Force current layer to "MY_LAYER".  If
    // "MY_LAYER" is not loaded, the current layer
    // will still be in effect.
    //
    AcDbObjectId layerId;
    if (getLayerIdFromString(_T("MY_LAYER"), layerId)
        == Acad::eOk)
    {
        pW->subEntityTraits().setLayer(layerId);
    }

    // Draw a dashdot'd xline in "MY_LAYER"'s color.
    //
    pW->geometry().xline(pVerts[0], pVerts[2]);

    delete [] pVerts;

    return Adesk::kTrue;
}


// A useful function that gets the linetype ID from the
// linetype's name -- must be in upper case.
// 
static Acad::ErrorStatus
getLinetypeIdFromString(const TCHAR* str, AcDbObjectId& id)
{
    Acad::ErrorStatus err;
 
    // Get the table of currently loaded linetypes.
    //
    AcDbLinetypeTable *pLinetypeTable;
    err = acdbHostApplicationServices()->workingDatabase()
        ->getSymbolTable(pLinetypeTable, AcDb::kForRead);
    if (err != Acad::eOk)
        return err;
 
    // Get the id of the linetype with the name that
    // 'str' contains.
    //
    err = pLinetypeTable->getAt(str, id, Adesk::kTrue);
 
    pLinetypeTable->close();
 
    return err;
}
 
 
// A useful function that gets the layer ID from the
// layer's name -- must be in upper case.
// 
static Acad::ErrorStatus
getLayerIdFromString(const TCHAR* str, AcDbObjectId& id)
{
    Acad::ErrorStatus err;
 
    // Get the table of currently loaded layers.
    //
    AcDbLayerTable *pLayerTable;
    err = acdbHostApplicationServices()->workingDatabase()
        ->getSymbolTable(pLayerTable, AcDb::kForRead);
    if (err != Acad::eOk)
        return err;
 
    // Get the ID of the layer with the name that 'str'
    // contains.
    //
    err = pLayerTable->getAt(str, id, Adesk::kTrue);
 
    pLayerTable->close();
 
    return err;
}

// END CODE APPEARING IN SDK DOCUMENT.

void
addAsdkTraitsSampObject()
{
    AsdkTraitsSamp *pNewObj = new AsdkTraitsSamp;

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

static void initAsdkTraitsSamp()
{
    AsdkTraitsSamp::rxInit();
    acrxBuildClassHierarchy();

    acedRegCmds->addCommand(_T("ASDK_TRAITS_SAMP"),
                            _T("ASDKTRAITSSAMP"),
                            _T("TRAITSSAMP"),
                            ACRX_CMD_TRANSPARENT,
                            addAsdkTraitsSampObject);
}

extern "C" AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* appId) 
{
    switch(msg) {
	case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(appId);
		acrxDynamicLinker->registerAppMDIAware(appId);
	    initAsdkTraitsSamp();
	    break;
	case AcRx::kUnloadAppMsg:
	    acedRegCmds->removeGroup(_T("ASDK_TRAITS_SAMP"));
            deleteAcRxClass(AsdkTraitsSamp::desc());
    }
    return AcRx::kRetOK;
}
