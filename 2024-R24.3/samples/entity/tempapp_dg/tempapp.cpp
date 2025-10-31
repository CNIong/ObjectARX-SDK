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
// Description:
//
// Test App for ARx Usage of Protocol Extension in
// conjunction with the AcDb library.
// 
// Defines the AsdkEntTemperature "property" extension
// protocol class for AcDbEntity, a default implementation,
// and specific implementations for Circles and Regions.

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include <stdlib.h>
#include "rxobject.h"
#include "rxregsvc.h"
#include "rxdlinkr.h"
#include "rxditer.h"
#include "aced.h"
#include "adslib.h"
#include "dbents.h"
#include "dbregion.h"
#include "dbdict.h"
#include "dbsymtb.h"
#include "tchar.h"



void initApp();
void unloadApp();
extern "C"
AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode, void*);

class AsdkEntTemperature : public AcRxObject
// 
// AsdkEntTemperature Protocol extension abstract base
// class.  Notice that this is the lowest level that uses
// the ACRX macros.
// 
{
public:
    ACRX_DECLARE_MEMBERS(AsdkEntTemperature);
    virtual double reflectedEnergy(AcDbEntity*) const = 0;
};
ACRX_NO_CONS_DEFINE_MEMBERS(AsdkEntTemperature, AcRxObject);


class AsdkDefaultTemperature : public AsdkEntTemperature
// 
// Default implementation to be attached to AcDbEntity as a
// catch-all.  This guarantees that this protocol extension
// will be found for any entity so the search up the
// AcRxClass tree will not fail and abort AutoCAD.
//
{
public:

    virtual double reflectedEnergy(AcDbEntity* pEnt) const;
};


double
AsdkDefaultTemperature::reflectedEnergy(
    AcDbEntity* pEnt) const
{
    acutPrintf(
        _T("\nThis entity has no area, and no reflection.\n"));
    return -1.0;
}

class AsdkRegionTemperature : public AsdkEntTemperature
//
// AsdkEntTemperature implementation for Regions.
//
{
public:
    virtual double reflectedEnergy(AcDbEntity* pEnt) const;
};

double
AsdkRegionTemperature::reflectedEnergy(
    AcDbEntity* pEnt) const
{
    AcDbRegion *pRegion = AcDbRegion::cast(pEnt);

    if (pRegion == NULL)
        acutPrintf(_T("\nThe impossible has happened!"));

    // Compute reflected energy as region area multiplied
    // by a dummy constant.
    //
    double retVal;
    if (pRegion->getArea(retVal) != Acad::eOk)
        return -1.0;

    return retVal * 42.0;
}


class AsdkCircleTemperature : public AsdkEntTemperature
//
// AsdkEntTemperature implementation for circles.
{
public:

    virtual double reflectedEnergy(AcDbEntity* pEnt) const;
};


double
AsdkCircleTemperature::reflectedEnergy(
    AcDbEntity* pEnt) const
{
    AcDbCircle *pCircle = AcDbCircle::cast(pEnt);

    // Compute reflected energy in manner distinctly
    // different than for AcDbRegion.
    // 
    return pCircle->radius() * 6.21 * 42.0;
}


// This function has the user select an entity and then
// calls the reflectedEnergy() function in the protocol
// extension class attached to that entity's class.
// 
void
energy()
{
    AcDbEntity *pEnt;
    AcDbObjectId pEntId;
    ads_name en;
    ads_point pt;

    if (acedEntSel(_T("\nSelect an Entity:  "), en, pt)
        != RTNORM)
    {
        acutPrintf(_T("Nothing Selected\n"));
        return;
    }
    acdbGetObjectId(pEntId, en);
    acdbOpenObject(pEnt, pEntId, AcDb::kForRead);

    // call the protocol extension class's method
    //
    double eTemp = ACRX_X_CALL(pEnt,
        AsdkEntTemperature)->reflectedEnergy(pEnt);

    acutPrintf(_T("\nEnergy == %f\n"), eTemp);
    pEnt->close();
}


// Pointers for Protocol Extension Objects.  These pointers
// are global so that they can be accessed during
// initialization *and* cleanup
// 
AsdkDefaultTemperature *pDefaultTemp;
AsdkRegionTemperature *pRegionTemp;
AsdkCircleTemperature *pCircleTemp;

// Initialization function called from acrxEntryPoint during
// kInitAppMsg case.  This function is used to add commands
// to the command stack as well as adding protocol extension
// objects to classes in and custom classes to the ACRX
// runtime class hierarchy.
// 
void
initApp()
{
    acrxRegisterService(_T("AsdkTemperature"));

    AsdkEntTemperature::rxInit();
    acrxBuildClassHierarchy();

    pDefaultTemp = new AsdkDefaultTemperature();
    pRegionTemp = new AsdkRegionTemperature();
    pCircleTemp = new AsdkCircleTemperature();

    // Add the protocol extension objects to the appropriate
    // AcRxClass objects
    //
    AcDbEntity::desc()->addX(AsdkEntTemperature::desc(),
        pDefaultTemp);
    AcDbRegion::desc()->addX(AsdkEntTemperature::desc(),
        pRegionTemp);
    AcDbCircle::desc()->addX(AsdkEntTemperature::desc(),
        pCircleTemp);

    acedRegCmds->addCommand(_T("ASDK_TEMPERATURE_APP"),
        _T("ASDK_ENERGY"), _T("ENERGY"), ACRX_CMD_TRANSPARENT,
        energy);
}

void
unloadApp()
{
    delete acrxServiceDictionary->remove(_T("AsdkTemperature"));
    acedRegCmds->removeGroup(_T("ASDK_TEMPERATURE_APP"));

    // Remove protocol extension objects from the AcRxClass
    // object tree.  This *must* be done before removing the
    // AsdkEntTemperature class from the ACRX runtime class
    // hierarchy so that the AsdkEntTemperature::desc()
    // still exists.
    // 
    AcDbEntity::desc()->delX(AsdkEntTemperature::desc());
    delete pDefaultTemp;
    AcDbRegion::desc()->delX(AsdkEntTemperature::desc());
    delete pRegionTemp;
    AcDbCircle::desc()->delX(AsdkEntTemperature::desc());
    delete pCircleTemp;

    // Remove the AsdkEntTemperature class from the ARX
    // runtime class hierarchy.
    //
    deleteAcRxClass(AsdkEntTemperature::desc());
}

static const TCHAR acGeomentObjDbxFile[] = _T("AcGeomentObj.dbx");

AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* appId)
{
    switch (msg) {
    case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(appId);
		acrxDynamicLinker->registerAppMDIAware(appId);
        acrxLoadModule(acGeomentObjDbxFile, 0);
        initApp();
        break;
    case AcRx::kUnloadAppMsg:
        unloadApp();
        acrxUnloadModule(acGeomentObjDbxFile);
    }
    return AcRx::kRetOK;
}
