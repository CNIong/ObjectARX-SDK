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
#include "StdAfx.h"

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "ArxDbgAppEditorReactor.h"
#include "ArxDbgUtils.h"
#include "ArxDbgUiTdcSysReactors.h"
#include "ArxDbgDbEntity.h"
#include "ArxDbgDbDictRecord.h"
#include "ArxDbgOptions.h"



ACRX_NO_CONS_DEFINE_MEMBERS(ArxDbgAppEditorReactor, AcEditorReactor);

/////////////////////////////////////////////////////////////////////////////
//////////// STATIC CONSTRUCTOR/DESTRUCTOR FOR THIS SINGLETON CLASS /////////
/////////////////////////////////////////////////////////////////////////////

ArxDbgAppEditorReactor* ArxDbgAppEditorReactor::m_instance = NULL;

/****************************************************************************
**
**  ArxDbgAppEditorReactor::getInstance
**
**  **jma
**
*************************************/

ArxDbgAppEditorReactor*
ArxDbgAppEditorReactor::getInstance()
{
    if (m_instance)
        return m_instance;

    m_instance = new ArxDbgAppEditorReactor;
    acedEditor->addReactor(m_instance);
    return m_instance;
}

/****************************************************************************
**
**  ArxDbgAppEditorReactor::destroyInstance
**
**  **jma
**
*************************************/

void
ArxDbgAppEditorReactor::destroyInstance()
{
    if (m_instance) {
        acedEditor->removeReactor(m_instance);
        delete m_instance;
        m_instance = NULL;
    }
    else {
        ASSERT(0);
    }
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/****************************************************************************
**
**  ArxDbgAppEditorReactor::ArxDbgAppEditorReactor
**
**  **jma
**
*************************************/

ArxDbgAppEditorReactor::ArxDbgAppEditorReactor()
{
}

/****************************************************************************
**
**  ArxDbgAppEditorReactor::~ArxDbgAppEditorReactor
**
**  **jma
**
*************************************/

ArxDbgAppEditorReactor::~ArxDbgAppEditorReactor()
{
}

/****************************************************************************
**
**  ArxDbgAppEditorReactor::databaseConstructed
**
**  **jma
**
*************************************/

void
ArxDbgAppEditorReactor::databaseConstructed(AcDbDatabase* db)
{
    ArxDbgUiTdcSysReactors::databaseConstructed(db);

	m_cloneSet.databaseConstructed(db);
}

/****************************************************************************
**
**  ArxDbgAppEditorReactor::databaseToBeDestroyed
**
**  **jma
**
*************************************/

void
ArxDbgAppEditorReactor::databaseToBeDestroyed(AcDbDatabase* db)
{
    ArxDbgUiTdcSysReactors::databaseDestroyed(db);

	m_cloneSet.databaseDestroyed(db);
}

/****************************************************************************
**
**  ArxDbgAppEditorReactor::endDeepClone
**
**  **jma
**
*************************************/

void
ArxDbgAppEditorReactor::endDeepClone(AcDbIdMapping& idMap)
{
    if ((idMap.deepCloneContext() == AcDb::kDcBlock) ||
        (idMap.deepCloneContext() == AcDb::kDcObjects)) {
        verifyClonedReferences(idMap);
    }
}

/****************************************************************************
**
**  ArxDbgAppEditorReactor::verifyClonedReferences
**      when being cloned to another block in the same drawing, it is possible
**  that not all of the entities that you referenced were cloned as well, and
**  you may now have references to entities that are owned by another block.
**  This is not good!. Therefore, walk through the set of cloned objects and
**  verify all their references.
**
**  **jma
**
*************************************/

void
ArxDbgAppEditorReactor::verifyClonedReferences(AcDbIdMapping& idMap)
{
    ArxDbgDbEntity* ent;
    AcDbObject* obj;
    Acad::ErrorStatus es;
    int numErrorsFixed;

    AcDbIdPair idPair;
    AcDbIdMappingIter mapIter(idMap);
    for (mapIter.start(); !mapIter.done(); mapIter.next()) {
        if (mapIter.getMap(idPair)) {
            es = acdbOpenObject(obj, idPair.value(), AcDb::kForWrite);
            if (es == Acad::eOk) {
                ent = ArxDbgDbEntity::cast(obj);
				if (ent != NULL) {
					es = ent->verifyReferences(numErrorsFixed, true);
					if (es != Acad::eOk) {
						ASSERT(0);
						ArxDbgUtils::rxErrorMsg(es);
						obj->erase();   // don't know what else to do but erase screwed up entity
					}
				}
                obj->close();
            }
            else {
                ASSERT(0);
                ArxDbgUtils::rxErrorMsg(es);
            }
        }
        else {
            ASSERT(0);
        }
    }
}

/****************************************************************************
**
**	ArxDbgAppEditorReactor::beginDeepCloneXlation
**
**  **jma
**
*************************************/

void
ArxDbgAppEditorReactor::beginDeepCloneXlation(
                            AcDbIdMapping& idMap, Acad::ErrorStatus* es)
{
    m_didTheseDicts.setLogicalLength(0);    // reset the dictionaries we have processed

    AcDbDatabase* origDb;
    AcDbDatabase* destDb;
    idMap.origDb(origDb);
    idMap.destDb(destDb);

    AcDbObject* clonedObj;
    AcDbObject* objToClone;

		// we catch this event so that we can wblock objects that are not entities.
		// This happens from the class ArxDbgUiTdcWblockClone where you are allowed
		// to pick non-entities to wblock to a new/existing drawing.  AcDbDatabase::wblock()
		// only allows entities to be in the set of objects passed to it, but you
		// can manually wblockClone them yourself here.
    if (idMap.deepCloneContext() == AcDb::kDcWblock) {
			// see what non-entity objects we have to clone by hand.
		AcDbObjectIdArray handCloneObjects;
		m_cloneSet.getObjectsForDatabase(origDb, handCloneObjects);
        if (handCloneObjects.isEmpty())
            return;

            // walk through the clone set and try to clone
            // everything.  If something is already cloned,
            // its ok, it won't be cloned again or return an
            // error, it will just set clonedObj to NULL.
        CString str;
        int len = handCloneObjects.length();
        for (int i=0; i<len; i++) {
            clonedObj = NULL;
            if (acdbOpenAcDbObject(objToClone, handCloneObjects[i], AcDb::kForRead) == Acad::eOk) {
                objToClone->wblockClone(destDb, clonedObj, idMap, Adesk::kFalse);
                if (clonedObj != NULL) {
                    acutPrintf(_T("\nArxDbgAppEditorReactor: cloned additional object [%s, %s]"),
                                ArxDbgUtils::objToClassStr(clonedObj),
                                ArxDbgUtils::objToHandleStr(objToClone, str));
                    clonedObj->close();
                }
                objToClone->close();
            }
        }
    }
		// catching this event allows us to correctly bring in our Dictionary Records.
		// If we don't do this, then they will be orphaned.  AutoCAD will not hook up
		// the cloned dictionary records automatically.
    else if ((ArxDbgOptions::m_instance.m_doDictRecordInsertByHand) &&
			 ((idMap.deepCloneContext() == AcDb::kDcInsert) ||
			  (idMap.deepCloneContext() == AcDb::kDcInsertCopy))) {
            // have to manually find all things we are interested in inserting.
            // So, look for all ArxDbgDictRecords, if its a dict record,
            // make sure owner dict is cloned in new database
        AcDbObjectIdArray objIds;
        collectAllDictRecords(origDb, objIds);
        int len = objIds.length();
        for (int i=0; i<len; i++) {
                // find out if object is a dict record
            Acad::ErrorStatus es;
            es = acdbOpenObject(objToClone, objIds[i], AcDb::kForRead);
            if (es == Acad::eOk) {
                acutPrintf(_T("\nArxDbgAppEditorReactor: hand inserting [%s]"), ArxDbgUtils::objToClassStr(objToClone));

                    // clone the owner dictionary if one of our dictionary records
                if (objToClone->isKindOf(ArxDbgDbDictRecord::desc()))
                    insertCloneOwnerDict(objToClone->ownerId(), destDb, idMap);

                objToClone->close();
            }
        }
    }
}

/****************************************************************************
**
**	ArxDbgAppEditorReactor::collectAllDictRecords
**
**  **jma
**
*************************************/

void
ArxDbgAppEditorReactor::collectAllDictRecords(AcDbDatabase* db, AcDbObjectIdArray& objIds)
{
    AcDbDictionary* dict;
	Acad::ErrorStatus es;
	es = db->getNamedObjectsDictionary(dict, AcDb::kForRead);
    if (es == Acad::eOk) {
        searchOneDictionary(dict, objIds);
        dict->close();
    }
}

/****************************************************************************
**
**	ArxDbgAppEditorReactor::searchOneDictionary
**		iterate over the dictionary and collect all the relevant entries contained
**	within it.  This is a recursive function
**
**  **jma
**
*************************************/

void
ArxDbgAppEditorReactor::searchOneDictionary(AcDbDictionary* dict, AcDbObjectIdArray& objIds)
{
        // get an iterator over this dictionary
    AcDbDictionaryIterator* dictIter = dict->newIterator();
    ASSERT(dictIter != NULL);

        // walk dictionary and just collect all the entries that are of the
        // given type
    AcDbObject* obj;
    for (; !dictIter->done(); dictIter->next()) {
        if (acdbOpenAcDbObject(obj, dictIter->objectId(), AcDb::kForRead) == Acad::eOk) {
            if (obj->isKindOf(ArxDbgDbDictRecord::desc())) {
                objIds.append(obj->objectId());
            }
            else if (obj->isKindOf(AcDbDictionary::desc())) {
                searchOneDictionary(AcDbDictionary::cast(obj), objIds);
            }

            obj->close();
        }
    }
    delete dictIter;
    dict->close();
}

/****************************************************************************
**
**	ArxDbgAppEditorReactor::insertCloneOwnerDict
**
**  **jma
**
*************************************/

void
ArxDbgAppEditorReactor::insertCloneOwnerDict(const AcDbObjectId& dictId,
                            AcDbDatabase* destDb, AcDbIdMapping& idMap)
{
        // the dictionaries are dealt with as a whole when encountering the
        // first entry within them. Skip processing if we have already 
        // encountered this one before.
    if (m_didTheseDicts.contains(dictId))
        return;
    else
        m_didTheseDicts.append(dictId);

        // get the name of the dictionary to recreate
    CString dictName;
    if (!ArxDbgUtils::lookUpDictEntryName(dictId, dictName)) {
        ArxDbgUtils::stopAlertBox(_T("ERROR: Couldn't find old dictionary name during Insert!"));
        return;
    }
        // open the source dictionary to be inserted
    AcDbDictionary* srcDict;
    if (acdbOpenObject(srcDict, dictId, AcDb::kForRead) != Acad::eOk) {
        ASSERT(0);
        return;
    }
        // try to open the destiniation dictionary.  Since INSERT does
        // not clone the destination NamedObjects dictionary, we can
        // use getAt() on it since IDs are not inFlux
    Acad::ErrorStatus es;
    AcDbDictionary* destDict = ArxDbgUtils::openDictionaryForRead(dictName, destDb);
    if (destDict) {
        es = destDict->upgradeOpen();
        if (es == Acad::eOk)
            insertCloneMergeDicts(srcDict, destDict, idMap);
        else {
            ASSERT(0);
        }
        destDict->close();
    }
    else {
            // our dictionary doesn't yet exist in destination database.
            // Use deepClone to clone it and all of its contents to the 
            // root dictionary of the destination database.
        AcDbDictionary* rootDictDest;
		es = destDb->getNamedObjectsDictionary(rootDictDest, AcDb::kForWrite);
        if (es == Acad::eOk) {
            AcDbObject* pClone = NULL;
            srcDict->deepClone(rootDictDest, pClone, idMap);
            if (pClone != NULL) {
                AcDbObjectId tmpObjId;
                es = rootDictDest->setAt(dictName, pClone, tmpObjId);
                if (es != Acad::eOk) {
                    ArxDbgUtils::stopAlertBox(_T("ERROR: Could not clone destination dictionary!"));
                    ArxDbgUtils::rxErrorAlert(es);
                }
                pClone->close();
            }
            rootDictDest->close();
        }
    }
    srcDict->close();
}

/****************************************************************************
**
**	ArxDbgAppEditorReactor::insertCloneMergeDicts
**		our dictionary already exists in the destination drawing, so we must
**	merge the two together.  Since the destination dictionary was not cloned
**	we can do normal getAt() since its IDs are not inFlux.
**
**  **jma
**
*************************************/

void
ArxDbgAppEditorReactor::insertCloneMergeDicts(AcDbDictionary* srcDict,
                AcDbDictionary* destDict, AcDbIdMapping& idMap)
{
    AcDbObjectId tmpObjId;
    AcDbObject* objToClone;
    AcDbObject* clonedObj;
    AcDbDictionaryIterator* iter;
    iter = srcDict->newIterator();

    for (; !iter->done(); iter->next()) {
        iter->getObject(objToClone, AcDb::kForRead);
        
            // if an entry with this name is found already, don't clone
            // it, add to the idMap to say that this one got translated
            // to one that already exists
        const TCHAR *pName = iter->name();
        if (destDict->getAt(pName, tmpObjId) == Acad::eOk) {
            AcDbIdPair idPair(objToClone->objectId(), tmpObjId, true, false, true);
            idMap.assign(idPair);
            objToClone->close();
        }
        else {
                // doesn't exist yet in the destination dict, so clone and
                // place it there.
            clonedObj = NULL;
            objToClone->deepClone(destDict, clonedObj, idMap);

                // INSERT usually uses a method of cloning
                // called CheapClone, where it "moves" objects
                // into the destination database instead of
                // actually cloning them.  When this happens,
                // objToClone and clonedObj are pointers to the
                // same object.  We only want to close pObj
                // here if it really is a different object.
            if (objToClone != clonedObj)
                objToClone->close();

            if (clonedObj) {
                destDict->setAt(pName, clonedObj, tmpObjId);
                clonedObj->close();
            }
        }
    }
    delete iter;
}


