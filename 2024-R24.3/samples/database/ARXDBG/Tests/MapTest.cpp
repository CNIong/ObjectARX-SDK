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

#include "MapTest.h"
#include "ArxDbgUtils.h"


     
MapTestReactor* MapTestReactor::m_instance = NULL;

/****************************************************************************
**
**  MapTestReactor::getInstance
**		make or retrieve the singleton instance of this EditorReactor
**
**  **jma
**
*************************************/

MapTestReactor*
MapTestReactor::getInstance()
{
    if (m_instance)
        return m_instance;

    m_instance = new MapTestReactor;
    acedEditor->addReactor(m_instance);
    return m_instance;
}

/****************************************************************************
**
**  MapTestReactor::destroyInstance
**
**  **jma
**
*************************************/

void
MapTestReactor::destroyInstance()
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

/****************************************************************************
**
**  MapTestReactor::MapTestReactor
**
**  **jma
**
*************************************/

MapTestReactor::MapTestReactor()
:	m_extDatabase(NULL),
	m_cloneState(kNull)
{
}

/****************************************************************************
**
**  MapTestReactor::~MapTestReactor
**
**  **jma
**
*************************************/

MapTestReactor::~MapTestReactor()
{
		// clean up if we left this open before doing the EXPORT
	reset();
}

/****************************************************************************
**
**  MapTestReactor::reset
**
**  **jma
**
*************************************/

void
MapTestReactor::reset()
{
	m_cloneState = kNull;

    m_dwgName.Empty();

	if (m_extDatabase)
		delete m_extDatabase;

	m_extDatabase = NULL;

	ObjIdMapNode* tmpNode;
	int len = m_objIdMap.length();
	for (int i=0; i<len; i++) {
		tmpNode = static_cast<ObjIdMapNode*>(m_objIdMap[i]);
		delete tmpNode;
	}
	m_objIdMap.setLogicalLength(0);
}

/****************************************************************************
**
**  MapTestReactor::findObjIdMapNode
**		look up the objectId associated with the particular operation.
**
**  **jma
**
*************************************/

ObjIdMapNode*
MapTestReactor::findObjIdMapNode(const AcDbObjectId& objId, ObjIdMapNode::IndexType type)
{
	ObjIdMapNode* tmpNode;
	int len = m_objIdMap.length();
	for (int i=0; i<len; i++) {
		tmpNode = static_cast<ObjIdMapNode*>(m_objIdMap[i]);

		if ((type == ObjIdMapNode::kOrigExt) && (objId == tmpNode->m_origExtId))
			return tmpNode;

		if ((type == ObjIdMapNode::kTmpImport) && (objId == tmpNode->m_tmpImportId))
			return tmpNode;

		if ((type == ObjIdMapNode::kNewCur) && (objId == tmpNode->m_newCurId))
			return tmpNode;

		if ((type == ObjIdMapNode::kTmpExport) && (objId == tmpNode->m_tmpExportId))
			return tmpNode;

		if ((type == ObjIdMapNode::kNewExt) && (objId == tmpNode->m_newExtId))
			return tmpNode;
	}

	return NULL;
}

/****************************************************************************
**
**  MapTestReactor::printObj
**
**  **jma
**
*************************************/

void
MapTestReactor::printObj(LPCTSTR event, const AcDbObjectId& objId) const
{
    CString str;
    AcDbObject* obj;
    Acad::ErrorStatus es = acdbOpenAcDbObject(obj, objId, AcDb::kForRead);
    if (es == Acad::eOk) {
        acutPrintf(_T("\n%-15s : [%-18s: %s, %s] "), _T("[MAP REACTOR]"), event,
                ArxDbgUtils::objToClassStr(obj), ArxDbgUtils::objToHandleStr(obj, str));
        obj->close();
    }
}

/****************************************************************************
**
**  MapTestReactor::printObj
**
**  **jma
**
*************************************/

void
MapTestReactor::printObj(LPCTSTR event, const AcDbObject* obj) const
{
    CString str;
    acutPrintf(_T("\n%-15s : [%-18s: %s, %s] "), _T("[MAP REACTOR]"), event,
                ArxDbgUtils::objToClassStr(obj), ArxDbgUtils::objToHandleStr(obj, str));
}

/****************************************************************************
**
**  MapTestReactor::endDeepClone
**		make an entry in the ObjectIdMap as to how the new cloned entry maps
**	back to the original.
**
**  **jma
**
*************************************/

void
MapTestReactor::endDeepClone(AcDbIdMapping& idMap)
{
	if (m_cloneState == kNull)
		return;		// got called from some other context, like a COPY

	ObjIdMapNode* tmpNode;
    AcDbIdPair idPair;

	if (m_cloneState == kImportWblock) {
        AcDbIdMappingIter iter(idMap);
 
        for (iter.start(); !iter.done(); iter.next()) {
            if (iter.getMap(idPair) && idPair.isCloned()) {
				tmpNode = findObjIdMapNode(idPair.key(), ObjIdMapNode::kOrigExt);
				if (tmpNode)
					tmpNode->m_tmpImportId = idPair.value();
			}
		}
	}
	else if (m_cloneState == kImportInsert) {
        AcDbIdMappingIter iter(idMap);
 
        for (iter.start(); !iter.done(); iter.next()) {
            if (iter.getMap(idPair) && idPair.isCloned()) {
				tmpNode = findObjIdMapNode(idPair.key(), ObjIdMapNode::kTmpImport);
				if (tmpNode)
					tmpNode->m_newCurId = idPair.value();
			}
		}
    }
	else if (m_cloneState == kExportWblock) {
        AcDbIdMappingIter iter(idMap);
 
        for (iter.start(); !iter.done(); iter.next()) {
            if (iter.getMap(idPair) && idPair.isCloned()) {
				tmpNode = findObjIdMapNode(idPair.key(), ObjIdMapNode::kNewCur);
				if (tmpNode)
		        	tmpNode->m_tmpExportId = idPair.value();
            }
        }
    }
    else if (m_cloneState == kExportInsert) {
        AcDbIdMappingIter iter(idMap);
 
        for (iter.start(); !iter.done(); iter.next()) {
            if (iter.getMap(idPair) && idPair.isCloned()) {
                tmpNode = findObjIdMapNode(idPair.key(), ObjIdMapNode::kTmpExport);
                if (tmpNode)
                    tmpNode->m_newExtId = idPair.value();
            }
        }
    }
    else {
        ASSERT(0);
    }
}

/****************************************************************************
**
**  MapTestReactor::endInsert
**
**  **jma
**
*************************************/

void         
MapTestReactor::endInsert(AcDbDatabase* pTo) 
{
        // only worried about this when going back to the original
        // database.
    if (m_cloneState != kExportInsert)
        return;

    AcDbObjectIdArray eraseList;
    Acad::ErrorStatus es;
    AcDbEntity* ent;

        // go through the swap list and swapIds with the original
        // entity.  I think it is safe to only worry about Entities 
        // that got cloned and not objects.  In AEC's case, anchors
        // are directly owned by the entity and got cloned, so no
        // swapping should be necessary.  In the case of Dictionary
        // objects, they have already been merged or remapped by
        // the AcDbDatabase::insert() operation.  So, in this loop,
        // only look for objects of type AcDbEntity when doing the
        // swap.
    ObjIdMapNode* tmpNode;
    int len = m_objIdMap.length();
    int i;
    for (i=0 ; i<len; i++) {
        tmpNode = static_cast<ObjIdMapNode*>(m_objIdMap[i]);

        es = acdbOpenAcDbEntity(ent, tmpNode->m_origExtId, AcDb::kForWrite);
        if (es == Acad::eOk) {
            printObj(_T("Swap from"), ent);
            printObj(_T("Swap to"), tmpNode->m_newExtId);

            es = ent->swapIdWith(tmpNode->m_newExtId);
            if (es != Acad::eOk) {
                acutPrintf(_T("\nERROR: could not swap object: (%s)"), ArxDbgUtils::rxErrorStr(es));
            }
            else {
                    // don't erase anything until all the swapping is completed.
                    // In AEC, erasing some entities that "own" another implicitly
                    // cause others to be erased.  That would screw up the swapping
                    // process if done in mid-stream.  So, just add them to a list
                    // and erase them after things have finished.
                eraseList.append(tmpNode->m_newExtId);    // we swapped Ids with orignal, so use newId
            }

            ent->close();
        }

        // else case isn't necessarily an error, because there will be
        // AcDbObjects that were in the clone set because they were referenced
        // by the entities.
    }

        // walk list of objects again, this time erasing them since things have
        // now quieted down and the set of objects is stable.
    len = eraseList.length();
    for (i=0; i<len; i++) {
        es = acdbOpenAcDbEntity(ent, eraseList[i], AcDb::kForWrite);
        if (es == Acad::eOk) {
            ent->erase();
            ent->close();
        }
    }
}


/****************************************************************************
**
**  collectModelSpaceBlkEnts
**
**  **jma
**
*************************************/

Acad::ErrorStatus
collectModelSpaceBlkEnts(AcDbDatabase* db,
                AcDbObjectIdArray& blkEnts, bool skipErased)
{
    Acad::ErrorStatus es;
    AcDbObjectId objId;
    AcDbBlockTableRecordIterator* iter;

    AcDbBlockTableRecord* blkRec;
    es = ArxDbgUtils::openBlockDef(ACDB_MODEL_SPACE, blkRec, AcDb::kForRead, db);
    if (es != Acad::eOk) {
        ASSERT(0);
        return Acad::eInvalidInput;
    }

    es = blkRec->newIterator(iter, true, skipErased);
    if (es != Acad::eOk) {
        ArxDbgUtils::rxErrorAlert(es);
        blkRec->close();
        return es;
    }
    for (; !iter->done(); iter->step(true, skipErased)) {
        es = iter->getEntityId(objId);
        if (es == Acad::eOk)
            blkEnts.append(objId);
    }

    blkRec->close();
    delete iter;

    return Acad::eOk;
}
     

/****************************************************************************
**
**  mapTestImportDwg
**
**  **jma  (based on sample from GIS)
**
*************************************/

void
mapTestImportDwg()
{
    AcDbDatabase* pTempDb;
    AcDbIdMapping idMap;
    AcDbObjectIdArray msEntList;
    AcGeMatrix3d idMatrix;    // identity matrix
     
        // reset import/swap lists
    MapTestReactor* mapReactor = MapTestReactor::getInstance();
    ASSERT(mapReactor);        // should always be here!

    mapReactor->reset();

        // get the drawing name
    Acad::ErrorStatus es;
    es = ArxDbgUtils::getFileNameForRead(_T("Drawing To Import"), NULL, _T("dwg"), mapReactor->m_dwgName, FALSE, FALSE);
    if (es != Acad::eOk)
        return;
 
    if ((mapReactor->m_extDatabase = new AcDbDatabase(Adesk::kFalse)) == NULL) {
        acutPrintf(_T("\nOut of memory"));
        return;
    }

    mapReactor->m_extDatabase->disableUndoRecording(Adesk::kFalse);
 
    es = mapReactor->m_extDatabase->readDwgFile(mapReactor->m_dwgName); 
    if (es != Acad::eOk) {
        mapReactor->reset();    // free up and null out db pointer
        acutPrintf(_T("\nCan't read file: %s"), ArxDbgUtils::rxErrorStr(es));
        return;
    }

    if (collectModelSpaceBlkEnts(mapReactor->m_extDatabase, msEntList, true) != Acad::eOk) {
        mapReactor->reset();    // free up and null out db pointer
        return;
    }

        // fill up the ObjIdMap with the original entries
    ObjIdMapNode* tmpNode;
    int len = msEntList.length();
    for (int i=0; i<len; i++) {
        tmpNode = new ObjIdMapNode;
        tmpNode->m_origExtId = msEntList[i];
        mapReactor->m_objIdMap.append(tmpNode);
    }

    mapReactor->m_cloneState = MapTestReactor::kImportWblock;
    es = mapReactor->m_extDatabase->wblock(pTempDb, msEntList, AcGePoint3d::kOrigin);
	mapReactor->m_cloneState = MapTestReactor::kNull;
	if (es != Acad::eOk) {
		mapReactor->reset();	// free up and null out db pointer
        acutPrintf(_T("\nwblock process failed: %s"), ArxDbgUtils::rxErrorStr(es));
    }
	else {
		mapReactor->m_cloneState = MapTestReactor::kImportInsert;
		es = acdbHostApplicationServices()->workingDatabase()->insert(idMatrix, pTempDb);
		mapReactor->m_cloneState = MapTestReactor::kNull;
		if (es != Acad::eOk) {
			mapReactor->reset();	// free up and null out db pointer
            acutPrintf(_T("\ninsert process failed: %s"), ArxDbgUtils::rxErrorStr(es));
		}
		else
			acutPrintf(_T("\nImport operation was successful!"));
	}
}

/****************************************************************************
**
**  mapTestExportDwg
**
**  **jma  (based on sample from GIS)
**
*************************************/

void
mapTestExportDwg()
{
    Acad::ErrorStatus es;
    AcDbDatabase* pTempDb;
    AcDbIdMapping idMap;
    AcDbObjectIdArray list;
    AcGeMatrix3d idMatrix;	// identity matrix

	MapTestReactor* mapReactor = MapTestReactor::getInstance();
	ASSERT(mapReactor);		// should always be here!
          
    if (mapReactor->m_extDatabase == NULL) {
        acutPrintf(_T("\nExecute IMPORTDWG before running this test!")) ; 
        return;
    }

		// here we are taking all entities in the current model space,
		// not just the originals.  That will suffice for our test but
		// only makes sense when importing into clean drawings.
	if (collectModelSpaceBlkEnts(acdbHostApplicationServices()->workingDatabase(), list, Adesk::kTrue) != Acad::eOk)
		return;

	pTempDb = new AcDbDatabase(Adesk::kFalse);
	mapReactor->m_cloneState = MapTestReactor::kExportWblock;
    es = acdbHostApplicationServices()->workingDatabase()->wblock(pTempDb, list, AcGePoint3d::kOrigin);
	mapReactor->m_cloneState = MapTestReactor::kNull;
	if (es != Acad::eOk) {
        acutPrintf(_T("\nwblock process failed %s"), ArxDbgUtils::rxErrorStr(es));
    }
	else {
		mapReactor->m_cloneState = MapTestReactor::kExportInsert;
		es = mapReactor->m_extDatabase->insert(idMatrix, pTempDb);
		mapReactor->m_cloneState = MapTestReactor::kNull;
		if (es != Acad::eOk) {
			acutPrintf(_T("\ninsert process failed %s"), ArxDbgUtils::rxErrorStr(es)); 
		}
		else {
		    mapReactor->m_extDatabase->saveAs(mapReactor->m_dwgName);
		}
	}
     
    delete pTempDb;
	mapReactor->reset();	// clean up for next usage
}
