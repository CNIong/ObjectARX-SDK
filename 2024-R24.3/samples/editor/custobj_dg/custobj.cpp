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
// This program demonstrates what it takes to create a
// custom object class.  Essentially, this means deriving a
// class from AcDbObject and providing your own
// implementations of dwgInFields, dwgOutFields,
// dxfInFields, and dxfOutFields.

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include <rxobject.h>
#include <rxregsvc.h>
#include <aced.h>
#include <dbsymtb.h>
#include <dbapserv.h>
#include <adslib.h>
#include "tchar.h"
#include <dbobjptr.h>



void createDictionary();
void iterateDictionary();
void initApp();
void unloadApp();
extern "C"
AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode, void*);

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

class AsdkMyClass : public AcDbObject
//
// This class demonstrates custom objects.
//
// To keep it simple, this class has a single integer data
// member.  Get and set functions are provided for this
// data member.
//
{
public:
    ACRX_DECLARE_MEMBERS(AsdkMyClass);
    AsdkMyClass(): mIntval(0) {};
    AsdkMyClass(const Adesk::Int16& val): mIntval(val) {};

    Acad::ErrorStatus         getData     (Adesk::Int16&);
    Acad::ErrorStatus         setData     (Adesk::Int16);

    virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler*);
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler*)
        const;
    virtual Acad::ErrorStatus dxfInFields (AcDbDxfFiler*);
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler*)
        const;
private:
    Adesk::Int16 mIntval;
};

ACRX_DXF_DEFINE_MEMBERS(AsdkMyClass, AcDbObject, 
AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent, 
0,
    ASDKMYCLASS, SAMP2);

// Gets the value of the integer data member.
//
Acad::ErrorStatus
AsdkMyClass::getData(Adesk::Int16& val)
{
    // Tells AutoCAD a read operation is taking place.
    //
    assertReadEnabled();
    val = mIntval;
    return Acad::eOk;
}

// Sets the value of the integer data member.
//
Acad::ErrorStatus
AsdkMyClass::setData(Adesk::Int16 val)
{
    // Triggers openedForModify notification.
    //
    assertWriteEnabled();
    mIntval = val;
    return Acad::eOk;
}

// Files data in from a DWG file.
//
Acad::ErrorStatus
AsdkMyClass::dwgInFields(AcDbDwgFiler* pFiler)
{
    assertWriteEnabled();

    AcDbObject::dwgInFields(pFiler);
    // For wblock filing we wrote out our owner as a hard
    // pointer ID so now we need to read it in to keep things
    // in sync.
    //
    if (pFiler->filerType() == AcDb::kWblockCloneFiler) {
        AcDbHardPointerId id;
        pFiler->readItem(&id);
    }
    pFiler->readItem(&mIntval);
    return pFiler->filerStatus();
}

// Files data out to a DWG file.
//
Acad::ErrorStatus
AsdkMyClass::dwgOutFields(AcDbDwgFiler* pFiler) const
{
    assertReadEnabled();

    AcDbObject::dwgOutFields(pFiler);
    // Since objects of this class will be in the Named
    // Objects Dictionary tree and may be hard referenced
    // by some other object, to support wblock we need to
    // file out our owner as a hard pointer ID so that it
    // will be added to the list of objects to be wblocked.
    //
    if (pFiler->filerType() == AcDb::kWblockCloneFiler)
        pFiler->writeHardPointerId((AcDbHardPointerId)ownerId());
    pFiler->writeItem(mIntval);
    return pFiler->filerStatus();
}

// Files data in from a DXF file.
//
Acad::ErrorStatus
AsdkMyClass::dxfInFields(AcDbDxfFiler* pFiler)
{
    assertWriteEnabled();

    Acad::ErrorStatus es;
    if ((es = AcDbObject::dxfInFields(pFiler))
        != Acad::eOk)
    {
        return es;
    }

    // Check if we're at the right subclass getData marker.
    //
    if (!pFiler->atSubclassData(_T("AsdkMyClass"))) {
        return Acad::eBadDxfSequence;
    }

    struct resbuf inbuf;
    while (es == Acad::eOk) {
        if ((es = pFiler->readItem(&inbuf)) == Acad::eOk) {
            if (inbuf.restype == AcDb::kDxfInt16) {
                mIntval = inbuf.resval.rint;
            }
        }
    }
    return pFiler->filerStatus();
}

// Files data out to a DXF file.
//
Acad::ErrorStatus
AsdkMyClass::dxfOutFields(AcDbDxfFiler* pFiler) const
{
    assertReadEnabled();

    AcDbObject::dxfOutFields(pFiler);
    pFiler->writeItem(AcDb::kDxfSubclass, _T("AsdkMyClass"));
    pFiler->writeItem(AcDb::kDxfInt16, mIntval);
    return pFiler->filerStatus();
}

// This function creates two objects of class AsdkMyClass. It fills them in
// with the integers 1 and 2, and then adds them to the
// dictionary associated with the key ASDK_DICT.  If this
// dictionary doesn't exist, it is created and added
// to the named object dictionary.
//
void
createDictionary()
{
    AcDbDictionary *pNamedobj;
    acdbHostApplicationServices()->workingDatabase()->
        getNamedObjectsDictionary(pNamedobj, AcDb::kForWrite);

    // Check to see if the dictionary we want to create is
    // already present. If not, create it and add
    // it to the named object dictionary.
    //
    AcDbDictionary *pDict;
    if (pNamedobj->getAt(_T("ASDK_DICT"), (AcDbObject*&) pDict,
        AcDb::kForWrite) == Acad::eKeyNotFound)
    {
        pDict = new AcDbDictionary;
        AcDbObjectId DictId;
        pNamedobj->setAt(_T("ASDK_DICT"), pDict, DictId);
    }
    pNamedobj->close();

    if (pDict) {
        // Create new objects to add to the new dictionary,
        // add them, then close them.
        //
        AsdkMyClass *pObj1 = new AsdkMyClass(1);
        AsdkMyClass *pObj2 = new AsdkMyClass(2);

        AcDbObjectId rId1, rId2;
        pDict->setAt(_T("OBJ1"), pObj1, rId1);
        pDict->setAt(_T("OBJ2"), pObj2, rId2);

        pObj1->close();
        pObj2->close();
        pDict->close();
    }
}


// Opens the dictionary associated with the key ASDK_DICT
// and iterates through all its entries, printing out the
// integer data value in each entry.
//
void
iterateDictionary()
{
		AcDbDictionaryPointer pNamedobj;
		// use a smart pointer to access the objects, the destructor will close them automatically
		pNamedobj.open(acdbHostApplicationServices()->workingDatabase()->namedObjectsDictionaryId(), AcDb::kForRead);
		// if ok
		if (pNamedobj.openStatus() == Acad::eOk)
		{
			AcDbObjectId dictId;
			// get at the dictionary entry itself
			Acad::ErrorStatus es = pNamedobj->getAt(_T("ASDK_DICT"), dictId);
			// if ok
			if (es == Acad::eOk)
			{
				// now open it for read
				AcDbDictionaryPointer pDict(dictId, AcDb::kForRead);
				// if ok
				if (pDict.openStatus() == Acad::eOk)
				{
					// Get an iterator for the ASDK_DICT dictionary.
					AcDbDictionaryIterator* pDictIter= pDict->newIterator();

					Adesk::Int16 val;
					AsdkMyClass *pMyCl = NULL;
					for (; !pDictIter->done(); pDictIter->next()) 
					{
						// Get the current record, open it for read, and
						es = pDictIter->getObject((AcDbObject*&)pMyCl, AcDb::kForRead);
						// if ok
						if (es == Acad::eOk)
						{
							pMyCl->getData(val);
							pMyCl->close();
							// print its data.
							acutPrintf(_T("\nintval is:  %d"), val);
						}
					}
					delete pDictIter;
				}

				// no need to close the dicts as we used smart pointers
			}
		}
}

// The initialization function called from the acrxEntryPoint() function during the
// kInitAppMsg case is used to add commands
// to the command stack and to add classes to the ACRX class
// hierarchy.
//
void
initApp()
{
    acedRegCmds->addCommand(_T("ASDK_DICTIONARY_COMMANDS"),
        _T("ASDK_CREATE"), _T("CREATE"), ACRX_CMD_MODAL,
        createDictionary);

    acedRegCmds->addCommand(_T("ASDK_DICTIONARY_COMMANDS"),
        _T("ASDK_ITERATE"), _T("ITERATE"), ACRX_CMD_MODAL,
        iterateDictionary);

    AsdkMyClass::rxInit();
    acrxBuildClassHierarchy();
}


// The clean up function called from the acrxEntryPoint() function during the
// kUnloadAppMsg case removes this application's
// command set from the command stack and removes this application's
// custom classes from the ACRX runtime class hierarchy.
//
void
unloadApp()
{
    acedRegCmds->removeGroup(_T("ASDK_DICTIONARY_COMMANDS"));

    // Remove the AsdkMyClass class from the ACRX runtime
    // class hierarchy.  If this is done while the database is
    // still active, it should cause all objects of class
    // AsdkMyClass to be turned into proxies.
    //
    deleteAcRxClass(AsdkMyClass::desc());
}

// END CODE APPEARING IN SDK DOCUMENT.


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
