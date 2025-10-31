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
// clonenod.cpp
// 
// Example showing one way to deal with objects in the Named Object Dictionary
// during a wblockClone operation.

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "rxregsvc.h"
#include "aced.h"
#include "dbidmap.h"
#include "dbsymtb.h"
#include "dbxrecrd.h"
#include "dbapserv.h"
#include "adscodes.h"
#include "tchar.h"



// Function prototypes
//
void modifyWblock();
void clearReactor();
static Adesk::Boolean getYorN(const TCHAR* pStr);
extern "C" AcRx::AppRetCode
    acrxEntryPoint(AcRx::AppMsgCode, void*);

// Forward class declarations
//
class AsdkNODEdReactor;

// Globals
//
AsdkNODEdReactor *gpEdReac = NULL; // pointer to editor
                                   // reactor


class AsdkNODEdReactor : public AcEditorReactor
//
// Custom AcEditorReactor class for Wblock Clone event
// notification
{
public:
    virtual void beginDeepCloneXlation(AcDbIdMapping& idMap,
        Acad::ErrorStatus* es);
};

// THE FOLLOWING CODE APPEARS IN THE SDK DOCUMENT.

// This example demonstrates a way to handle objects in
// the NamedObjects dictionary for WBLOCK and INSERT. 
// Our object is an AcDbictionary which is called
// "AsdkDictionary" in the NamedObjects dictionary,
// containing our custom objects.

const TCHAR *kpDictionary = _T("AsdkDictionary");

// AsdkNODEdReactor is derived from AcEditorReactor
//
void
AsdkNODEdReactor::beginDeepCloneXlation(
    AcDbIdMapping& idMap,
    Acad::ErrorStatus* pRetStat)
{
    Acad::ErrorStatus es;
    AcDbObjectId dictId;

    if (   idMap.deepCloneContext() != AcDb::kDcWblock
        && idMap.deepCloneContext() != AcDb::kDcInsert)
        return;

    // Get the "from" and "to" databases. 
    //
    AcDbDatabase *pFrom, *pTo;
    idMap.origDb(pFrom);
    idMap.destDb(pTo);

    // See if the "from" database has our dictionary, and
    // open it.  If it doesn't have one, we are done.
    //
    AcDbDictionary *pSrcNamedObjDict;
    pFrom->getNamedObjectsDictionary(pSrcNamedObjDict,
                                     AcDb::kForRead);

    es = pSrcNamedObjDict->getAt(kpDictionary, dictId);
    pSrcNamedObjDict->close();

    if (es == Acad::eKeyNotFound) 
        return;

    AcDbDictionary *pSrcDict;
    acdbOpenObject(pSrcDict, dictId, AcDb::kForRead);

    AcDbObject *pClone;
    switch (idMap.deepCloneContext()) {

    case AcDb::kDcWblock:

        // WBLOCK clones all, or part of a drawing into a
        // newly created drawing.  This means that the
        // NamedObject Dictionary is always cloned, and
        // its AcDbObjectIds are in flux.  Therefore, you
        // cannot use getAt() or setAt() on the dictionary
        // in the new database.  This is because the
        // cloned dictionary references all refer to the 
        // original objects.  During Deep Clone translation,
        // all cloned entries will be translated to the
        // new objects, and entries not cloned will be
        // "removed" by getting "translated" to NULL.
        //
        // The cloning of entries in our own dictionary are
        // not handled here.  If all are to be cloned, then
        // call setTreatElementsAsHard(Adesk::kTrue) on the
        // dictionary.  Otherwise, only those entries which
        // are refered to by hard references in other
        // wblocked objects, will have been cloned via
        // those references.

        // In this example, we will always write out all of
        // the records.  Since TreatElementsAsHard is not
        // currently persistent, we reset it here each time.
        //
        pSrcDict->upgradeOpen();
        pSrcDict->setTreatElementsAsHard(Adesk::kTrue);
		pSrcDict->downgradeOpen();      

        pClone = NULL;
        pSrcDict->wblockClone(pTo, pClone, idMap,
                              Adesk::kFalse);
        if (pClone != NULL) 
            pClone->close();
        break;

    case AcDb::kDcInsert:

        // In INSERT, an entire drawing is cloned, and
        // "merged" into a pre-existing drawing.  This
        // means that the destination drawing may already
        // have our dictionary - in which case we have to
        // merge our entries into the destination
        // dictionary.   So, first we must find out if
        // the destination NamedObjects dictionary has
        // our dictionary.
        //
        AcDbDictionary *pDestNamedDict;
        pTo->getNamedObjectsDictionary(pDestNamedDict,
                                       AcDb::kForWrite);

        // Since INSERT does not clone the destination
        // NamedObjects dictionary, we can use getAt()
        // on it.
        //
        es = pDestNamedDict->getAt(kpDictionary, dictId);

        // If our dictionary does not yet exist in the
        // NamedObjects dictionary, which is not itself
        // cloned, we have to both clone and add our
        // dictionary to it.  Since dictionary entries are
        // ownership references, all of our entries will
        // also be cloned at this point, so we are done.
        //
        if (es == Acad::eKeyNotFound) {

            pClone = NULL;
            pSrcDict->deepClone(pDestNamedDict,
                                pClone, idMap);

            // Unless we have overridden the deepClone
            // of our dictionary, we should expect it to
            // always be cloned here.
            //
            if (pClone == NULL) {
                *pRetStat = Acad::eNullObjectId;
                break;
            }

            pDestNamedDict->setAt(kpDictionary,
                                  pClone, dictId);
            pDestNamedDict->close();
            pClone->close();
            break;
        } 
        pDestNamedDict->close();

        // Our dictionary already exists in the destination
        // database, so now we must "merge" the entries
        // into it.  Since we have not cloned our
        // destination dictionary, its objectIds are not in
        // flux, and we can use getAt() and setAt() on it.
        //
        AcDbDictionary *pDestDict;
        acdbOpenObject(pDestDict, dictId, AcDb::kForWrite);

        AcDbObject *pObj, *pObjClone;
        AcDbDictionaryIterator* pIter;
        pIter = pSrcDict->newIterator();

        for (; !pIter->done(); pIter->next()) {

            const TCHAR *pName = pIter->name();
            pIter->getObject(pObj, AcDb::kForRead);

            // If the dictionary contains any references
            // and/or other objects have references to it,
            // you must either use deepClone() or put the
            // idPairs into the idMap here, so that they
            // will be in the map for translation.
            //
            pObjClone = NULL;
            pObj->deepClone(pDestDict, pObjClone, idMap);

            // INSERT usually uses a method of cloning
            // called CheapClone, where it "moves" objects
            // into the destination database instead of
            // actually cloning them.  When this happens,
            // pObj and pObjClone are pointers to the
            // same object.  We only want to close pObj
            // here if it really is a different object.
            // 
            if (pObj != pObjClone)
                pObj->close();

            if (pObjClone == NULL)
                continue;

            // If the name already exists in our
            // destination dictionary, it must be changed
            // to something unique.  In this example, the
            // name is changed to an annonymous entry. 
            // The setAt() method will automatically append
            // a unique identifier to each name beginning
            // with "*".  It will become something like,
            // "*S04".
            //
            if (   pDestDict->getAt(pName, dictId)
                == Acad::eKeyNotFound) 
                pDestDict->setAt(pName, pObjClone, dictId);
            else 
                pDestDict->setAt(_T("*S"), pObjClone, dictId);

            pObjClone->close();
        }
        delete pIter;
        pDestDict->close();
        break;

    default:
        break;
    }

    pSrcDict->close();
}

// END CODE APPEARING IN SDK DOCUMENT.

// Adds the reactor to the editor to monitor changes.
//
void
setup()
{
    acedEditor->addReactor(gpEdReac);
    acutPrintf(_T("Added new command to Wblock.\n"));

    // Now,  for this sample only,  we need to create a
    // new dictionary,  add it to the named object
    // dictionary using the key string specified by the
    // constant pointer kpDictionary.  Then we'll create
    // a couple of empty xrecords and put them into the
    // new dictionary.  All of this provides the objects
    // that our code will be cloning across.
    //
    AcDbDictionary *pNamedobj;
    acdbHostApplicationServices()->workingDatabase()
        ->getNamedObjectsDictionary(pNamedobj, AcDb::kForRead);

    AcDbDictionary *pDict;
    // Search for the dictionary associated with the key
    // kpDictionary.  If it's not found,  then create it,
    // add it to the namedobjects dictionary,  and then
    // create and add a few xrecords to it.
    //
    // If it is found then do nothing because it's already
    // been done sometime previously.
    //
    if (!pNamedobj->has(kpDictionary))
    {
        if (pNamedobj->upgradeOpen() == Acad::eOk) {
            pDict = new AcDbDictionary;
            AcDbObjectId DictId;
            pNamedobj->setAt(kpDictionary, pDict, DictId);
            pNamedobj->close();

            AcDbXrecord *pObj1 = new AcDbXrecord(),
                        *pObj2 = new AcDbXrecord();

            AcDbObjectId rId1, rId2;
            pDict->setAt(_T("OBJ1"), pObj1, rId1);
            pDict->setAt(_T("OBJ2"), pObj2, rId2);

            pObj1->close();
            pObj2->close();
            pDict->close();
        } else
            pNamedobj->close();
    }
}


// Removes the editor reactor
//
void
clearReactor()
{
    acedEditor->removeReactor(gpEdReac);
}


// Queries the user for Yes/No answer
//
static Adesk::Boolean
getYorN(const TCHAR* pStr)
{
    TCHAR yorn_str[132];

    // specific prompt.
    //
    acutPrintf(_T("\n%s"), pStr);

    acedInitGet(0, _T("No Yes"));

    yorn_str[0] = _T('Y');
    yorn_str[1] = _T('\0');

    switch (acedGetString(Adesk::kFalse, _T(" -- No/<Yes>:  "),
        yorn_str))
    {
    case RTKWORD:
        acedGetInput(yorn_str);
        /* Deliberate fallthrough */
    default:
        break;
    }

    return (!((yorn_str[0] == _T('N'))
        || (yorn_str[0] == _T('n'))));
}

// Arx entry point function
//
AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* appId)
{
    switch (msg) {
    case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(appId);
		acrxDynamicLinker->registerAppMDIAware(appId);
        gpEdReac = new AsdkNODEdReactor();
        acedRegCmds->addCommand(_T("ASDK_CLONENOD_TEST"),
            _T("ASDK_NODSETUP"),
            _T("NODSETUP"),
            ACRX_CMD_TRANSPARENT,
            setup);
        break;
    case AcRx::kUnloadAppMsg:
        clearReactor();
        acedRegCmds->removeGroup(_T("ASDK_CLONENOD_TEST"));
        delete gpEdReac;
    }
    return AcRx::kRetOK;
}
