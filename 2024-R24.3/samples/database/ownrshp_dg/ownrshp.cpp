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
// This program demonstrates establishing ownership trees.
//
// In order to show all aspects of this mechanism, a custom
// object class is used that has two data members one to
// store an integer (simulating real data) and the other
// stores a hard ownership objectId.
//
// Ownership consists of two parts:
//
// 1) The owner object stores the owned object's objectId
// and files it out/in to DWG and DXF
//
// 2) The owned object has its setOwnerId() member called
// with the owned object's objectId as the parameter.  This
// sets up the backpointer link so that the owned object
// knows who its owner is.  This is used by such things as
// WBLOCK to walk "up" the ownership tree.
//
// Setting backpointers is taken care of by AutoCAD during
// operations that use the dwg and dxf filers, so a custom
// object/entity class doesn't need to worry about this for
// its dwgInFields and dxfInFields members.  But, any class
// member functions that set any ownership Id data members
// in the class should take care of setting the owned
// object's backpointers by opening the owned objects and
// calling their setOwnerId() member functions using the
// owner object's objectId as the parameter for the calls.

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include <rxobject.h>
#include <rxregsvc.h>
#include <aced.h>
#include <dbsymtb.h>
#include <dbapserv.h>
#include <adslib.h>
#include <actrans.h>
#include "tchar.h"



void createObjs();
void listTree();
void printOut(AcDbObjectId id);
void initApp();
void unloadApp();
extern "C"
AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode, void*);

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

// Class declarations
//
class AsdkOwnerDemo : public AcDbObject

// This is a custom object class to demonstrate what is
// necessary to create ownership trees.
//
// To keep it simple, this class has two data members: a
// simple integer to represent normal data, and a hard
// ownership ID data member to hold the object ID of an owned
// object.
//
// Get and set functions are provided for both data members.
//
{
public:
    ACRX_DECLARE_MEMBERS(AsdkOwnerDemo);
    AsdkOwnerDemo(): mIntval(0) {};
    AsdkOwnerDemo(const Adesk::Int16& val): mIntval(val) {};

    Adesk::Int16 intData();
    Acad::ErrorStatus setIntData(const Adesk::Int16&);

    AcDbHardOwnershipId idData();
    Acad::ErrorStatus setIdData(const AcDbHardOwnershipId&);

    Acad::ErrorStatus dwgInFields (AcDbDwgFiler*);
    Acad::ErrorStatus dwgOutFields(AcDbDwgFiler*) const;
    Acad::ErrorStatus dxfInFields (AcDbDxfFiler*);
    Acad::ErrorStatus dxfOutFields(AcDbDxfFiler*) const;
private:
    Adesk::Int16 mIntval;
    AcDbHardOwnershipId mObjId;
};

ACRX_DXF_DEFINE_MEMBERS(AsdkOwnerDemo, AcDbObject,
AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent, 0,
    ASDKOWNERDEMO, OWNERSHIP);

// Gets the value of the integer data member.
//
Adesk::Int16
AsdkOwnerDemo::intData()
{
    assertReadEnabled();
    return mIntval;
}

// Sets the value of the integer data member.
//
Acad::ErrorStatus
AsdkOwnerDemo::setIntData(const Adesk::Int16& val)
{
    assertWriteEnabled();
    mIntval = val;
    return Acad::eOk;
}

// Returns a copy of the ownership ID data member.
//
AcDbHardOwnershipId
AsdkOwnerDemo::idData()
{
    assertReadEnabled();
    return mObjId;
}

// Sets the value of the ownership ID data member.
//
Acad::ErrorStatus
AsdkOwnerDemo::setIdData(const AcDbHardOwnershipId& ownedId)
{
    if (ownedId.asOldId() == 0L) {
        return Acad::eInvalidInput;
    }
    assertWriteEnabled();

    mObjId = ownedId;

    // Now set the backpointer.  A transaction is used for
    // opening the object, so if the object is already
    // open it won't prevent this setting from taking place.
    //
    AcDbObject *pObj;
    AcTransaction *pTrans
        = actrTransactionManager->startTransaction();
    pTrans->getObject(pObj, ownedId, AcDb::kForWrite);
    pObj->setOwnerId(objectId());
    actrTransactionManager->endTransaction();

    return Acad::eOk;
}

// Files data in from a DWG file.
//
Acad::ErrorStatus
AsdkOwnerDemo::dwgInFields(AcDbDwgFiler* filer)
{
    assertWriteEnabled();
    AcDbObject::dwgInFields(filer);
    // For wblock filing we wrote out our owner as a hard
    // pointer Id so now we need to read it in to keep things
    // in sync.
    //
    if (filer->filerType() == AcDb::kWblockCloneFiler) {
        AcDbHardPointerId id;
        filer->readItem(&id);
    }
    filer->readItem(&mIntval);
    filer->readItem(&mObjId);
    return filer->filerStatus();
}

// Files data out to a DWG file.
//
Acad::ErrorStatus
AsdkOwnerDemo::dwgOutFields(AcDbDwgFiler* filer) const
{
    assertReadEnabled();
    AcDbObject::dwgOutFields(filer);
    // Since objects of this class will be in the Named
    // Objects Dictionary tree and may be hard referenced
    // by some other object, to support wblock we need to
    // file out our owner as a hard pointer Id so that it
    // will be added to the list of objects to be wblocked
    //
    if (filer->filerType() == AcDb::kWblockCloneFiler)
        filer->writeHardPointerId((AcDbHardPointerId)ownerId());
    filer->writeItem(mIntval);
    filer->writeItem(mObjId);
    return filer->filerStatus();
}

// Files data in from a DXF file.
//
Acad::ErrorStatus
AsdkOwnerDemo::dxfInFields(AcDbDxfFiler* filer)
{
    assertWriteEnabled();

    Acad::ErrorStatus es;
    if ((es = AcDbObject::dxfInFields(filer))
        != Acad::eOk)
    {
        return es;
    }

    // Check if we're at the right subclass data marker.
    //
    if (!filer->atSubclassData(_T("AsdkOwnerDemo"))) {
        return Acad::eBadDxfSequence;
    }

    struct resbuf inbuf;
    while (es == Acad::eOk) {
        if ((es = filer->readItem(&inbuf)) == Acad::eOk) {
            if (inbuf.restype == AcDb::kDxfInt16) {
                mIntval = inbuf.resval.rint;
            } else if (inbuf.restype
                == AcDb::kDxfHardOwnershipId)
            {
                acdbGetObjectId(mObjId,
                    inbuf.resval.rlname);
            }
        }
    }
    return filer->filerStatus();
}

// Files data out to a DXF file.
//
Acad::ErrorStatus
AsdkOwnerDemo::dxfOutFields(AcDbDxfFiler* filer) const
{
    assertReadEnabled();

    AcDbObject::dxfOutFields(filer);
    filer->writeItem(AcDb::kDxfSubclass, _T("AsdkOwnerDemo"));
    filer->writeItem(AcDb::kDxfInt16, mIntval);

    // Null object IDs are invalid: don't write them out.
    //
    if (mObjId.asOldId() != 0L) {
        filer->writeItem(AcDb::kDxfHardOwnershipId, mObjId);
    }
    return filer->filerStatus();
}

// Creates an AsdkOwnerDemo object (pObjC) and adds data to
// it.  Then, AsdkOwnerDemo pObjB is created and set to be
// the owner of pObjC.  Next, AsdkOwnerDemo pObjA is created
// and added to a dictionary in the named object dictionary.
// Finally, pObjA is set to own pObjB. Technically, we could
// just add pObjA to the named object dictionary itself, but
// that's not appropriate because it would clutter up the
// named object dictionary.
//

void
createObjs()
{
    AcDbObjectId objIdA, objIdB, objIdC;
    AcDbDictionary *pNamedobj;
    AcDbDictionary *pDict = NULL;
    AcDbDatabase *pCurDwg = acdbHostApplicationServices()->workingDatabase();

    // Create object C with a dummy integer data value of 3.
    //
    AsdkOwnerDemo *pObjC = new AsdkOwnerDemo(3);

    // Append object C to database without setting an owner.
    //
    pCurDwg->addAcDbObject(objIdC, pObjC);

    pObjC->close();

    // Create object B with a dummy integer data value of 2.
    //
    AsdkOwnerDemo *pObjB = new AsdkOwnerDemo(2);

    // Append object B to the database without setting an owner.
    //
    pCurDwg->addAcDbObject(objIdB, pObjB);

    // Now set up ownership for object C.  The
    // AsdkOwnerDemo::setIdData() function takes the
    // objectId parameter and copies it into the
    // AcDbHardOwnershipId data member.  This places the
    // object ID in a position to be filed out/in via the
    // dwgInFields/dwgOutFields/dxfInFields/dxfOutFields
    // member functions.  This constitutes primary
    // "ownership."  The AsdkOwnerDemo::setIdData() function
    // also calls each owned object's setOwnerId() member
    // function to set the backpointer and establish the
    // full two-way ownership link.
    //
    pObjB->setIdData(objIdC);

    pObjB->close();

    // Create object A with a dummy integer data value of 1.
    //
    AsdkOwnerDemo *pObjA = new AsdkOwnerDemo(1);

    // Next, add objA to a dictionary in the named object
    // dictionary.  This will establish ownership for objA,
    // set the ownership backlink, and add it to the
    // database.
    //
    pCurDwg->getNamedObjectsDictionary(pNamedobj,
        AcDb::kForWrite);

    // Get a pointer to the ASDK_DICT dictionary.  If it
    // doesn't exist, then create it and add it to the
    // named object dictionary.
    //
    if (pNamedobj->getAt(_T("ASDK_DICT"), (AcDbObject*&) pDict,
        AcDb::kForWrite) == Acad::eKeyNotFound)
    {
        pDict = new AcDbDictionary;
        AcDbObjectId DictId;
        pNamedobj->setAt(_T("ASDK_DICT"), pDict, DictId);
    }
    pNamedobj->close();

    // add object A to the ASDK_DICT dictionary
    //
    pDict->setAt(_T("OBJA"), pObjA, objIdA);
    pDict->close();

    // Now set up ownership for object B.
    //
    pObjA->setIdData(objIdB);

    pObjA->close();
}

// The list tree function runs through all objects in the ASDK_DICT dictionary,
// follows their ownership trees, and lists out information
// on all objects in the tree.
//
void
listTree()
{
    AcDbDictionary *pNamedobj;
    AcDbDictionary *pDict;
    acdbHostApplicationServices()->workingDatabase()
        ->getNamedObjectsDictionary(pNamedobj, AcDb::kForWrite);

    // Get a pointer to the ASDK_DICT dictionary.
    //
    if (pNamedobj->getAt(_T("ASDK_DICT"), (AcDbObject*&) pDict,
        AcDb::kForRead) == Acad::eKeyNotFound)
	{
		pNamedobj->close();
		return ;
	}

    pNamedobj->close();

    // Run through the entries and list their backpointers.
    //
    AcDbDictionaryIterator *pDictItr = pDict->newIterator();
    for (; !pDictItr->done(); pDictItr->next()) {
        printOut(pDictItr->objectId());
    }
    delete pDictItr;

    pDict->close();
}


// Recursively walks down an ownership tree of AsdkOwnerDemo
// class objects, printing out information on each one.
//
void
printOut(AcDbObjectId id)
{
    AsdkOwnerDemo *pDemo;
    acdbOpenObject(pDemo, id, AcDb::kForRead);
    acutPrintf(_T("\nIntdata: %d  ObjId: %ld  Backpointer:")
        _T(" %ld OwnedObj: %ld"), pDemo->intData(),
        (pDemo->objectId()).asOldId(),
        (pDemo->ownerId()).asOldId(),
        (pDemo->idData()).asOldId());

    // Recursive tree walk
    //
    if ((pDemo->idData()).asOldId() != 0L) {
        printOut(pDemo->idData());
    }
    pDemo->close();
}

// The initialization function is called from acrxEntryPoint() during
// kInitAppMsg case.  This function is used to add commands
// to the command stack and to add classes to the ACRX class
// hierarchy.
//
void
initApp()
{
    acedRegCmds->addCommand(_T("ASDK_OWNERSHIP_COMMANDS"),
        _T("ASDK_CREATE"), _T("CREATE"),ACRX_CMD_MODAL, createObjs);
    acedRegCmds->addCommand(_T("ASDK_OWNERSHIP_COMMANDS"),
        _T("ASDK_LISTREE"), _T("LISTREE"),ACRX_CMD_MODAL, listTree);

    AsdkOwnerDemo::rxInit();
    acrxBuildClassHierarchy();
}


// The clean up function is called from acrxEntryPoint() during the
// kUnloadAppMsg case.  This function removes this application's
// command set from the command stack and the
// AsdkOwnerDemo class from the ARX runtime class tree.
//
void
unloadApp()
{
    acedRegCmds->removeGroup(_T("ASDK_OWNERSHIP_COMMANDS"));

    // Remove the AsdkOwnerDemo class from the ACRX runtime
    // class hierarchy.  If this is done while the database is
    // still active, it should cause all objects of class
    // AsdkOwnerDemo to be turned into proxies.
    //
    deleteAcRxClass(AsdkOwnerDemo::desc());
}


// ARX entry point
//
AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* appId)
{
    switch (msg) {
    case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(appId);
		acrxDynamicLinker->registerAppMDIAware(appId);
		initApp();
        break;
    case AcRx::kUnloadAppMsg:
        unloadApp();
    }
    return AcRx::kRetOK;
}

// END CODE APPEARING IN SDK DOCUMENT.
