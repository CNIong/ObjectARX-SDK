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

#include "ArxDbgUtils.h"
#include "AcadStr.h"



/****************************************************************************
**
**	ArxDbgUtils::symbolIdToName
**		given an objectId for a symbol table record, retrieve the name
**	associated with this symbol.
**
**	**jma
**
*************************************/

Acad::ErrorStatus
ArxDbgUtils::symbolIdToName(const AcDbObjectId& symbolId, CString& name)
{
        // shouldn't happen usually, but some debugging routines
        // want to print out this info
    if (symbolId == AcDbObjectId::kNull) {
        name = _T("AcDbObjectId::kNull");
        return Acad::eNullObjectId;
    }
        // get symbol name from symbol table record
    AcDbSymbolTableRecord* tblRec;
    Acad::ErrorStatus es;
    es = acdbOpenObject(tblRec, symbolId, AcDb::kForRead);
    if (es == Acad::eOk) {
        const TCHAR* locName;
        tblRec->getName(locName);
        name = locName;
        tblRec->close();
    }
    else {
        ArxDbgUtils::rxErrorMsg(es);
        es = Acad::eInvalidInput;
    }

    return es;
}

/****************************************************************************
**
**	ArxDbgUtils::mlineStyleIdToName
**		similar to symbolIdToName() but since MLINE Styles are not
**	derived from AcDbSymbolTableRecord, we need a special function.
**
**	**jma
**
*************************************/

Acad::ErrorStatus
ArxDbgUtils::mlineStyleIdToName(const AcDbObjectId& mlineStyleId, CString& name)
{
        // get symbol name from symbol table record
    AcDbMlineStyle* mlineStyle;
    Acad::ErrorStatus es;
    es = acdbOpenObject(mlineStyle, mlineStyleId, AcDb::kForRead);
    if (es == Acad::eOk) {
        name = mlineStyle->name();
        mlineStyle->close();
    }
    else {
        ArxDbgUtils::rxErrorMsg(es);
        es = Acad::eInvalidInput;
    }

    return es;
}

/****************************************************************************
**
**	ArxDbgUtils::nameToSymbolId
**
**	**jma
**
*************************************/

Acad::ErrorStatus
ArxDbgUtils::nameToSymbolId(AcRxClass* symTblClass, LPCTSTR name,
                        AcDbObjectId& recordId, AcDbDatabase* db)
{
	ASSERT(symTblClass != NULL);
	ASSERT(db != NULL);

    AcDbSymbolTable* symTbl;
    if ((symTbl = openSymbolTable(symTblClass, AcDb::kForRead, db)) == NULL)
        return Acad::eInvalidInput;

    Acad::ErrorStatus es;
    es = symTbl->getAt(name, recordId);
    symTbl->close();
    return es;
}

/****************************************************************************
**
**	ArxDbgUtils::symbolExists
**		use this if you don't have an object ID for the symbol table
**	and you want to know if the symbol already exists.
**
**	**jma
**
*************************************/

bool
ArxDbgUtils::symbolExists(AcRxClass* symTblClass, LPCTSTR name, AcDbDatabase* db)
{
	ASSERT(symTblClass != NULL);
	ASSERT(db != NULL);

    AcDbSymbolTable* symTbl;
    if ((symTbl = openSymbolTable(symTblClass, AcDb::kForRead, db)) == NULL)
        return false;

    bool symExists = symTbl->has(name);
    symTbl->close();
    return symExists;
}

/****************************************************************************
**
**	ArxDbgUtils::openSymbolTable
**		get a generic symbol table pointer from a specific symbol
**	table.
**
**	**jma
**
*************************************/

AcDbSymbolTable*
ArxDbgUtils::openSymbolTable(AcRxClass* symTblClass,
                                AcDb::OpenMode mode, AcDbDatabase* db)
{
	ASSERT(symTblClass != NULL);
	ASSERT(db != NULL);

    AcDbSymbolTable* symTbl = NULL;
    Acad::ErrorStatus es;

    if (symTblClass == AcDbBlockTableRecord::desc()) {
        AcDbBlockTable* blkTbl;
        es = db->getBlockTable(blkTbl, mode);
        symTbl = blkTbl;
    }
    else if (symTblClass == AcDbDimStyleTableRecord::desc()) {
        AcDbDimStyleTable* dimTbl;
        es = db->getDimStyleTable(dimTbl, mode);
        symTbl = dimTbl;
    }
    else if (symTblClass == AcDbLayerTableRecord::desc()) {
        AcDbLayerTable* layerTbl;
        es = db->getLayerTable(layerTbl, mode);
        symTbl = layerTbl;
    }
    else if (symTblClass == AcDbLinetypeTableRecord::desc()) {
        AcDbLinetypeTable* ltypeTbl;
        es = db->getLinetypeTable(ltypeTbl, mode);
        symTbl = ltypeTbl;
    }
    else if (symTblClass == AcDbTextStyleTableRecord::desc()) {
        AcDbTextStyleTable* textTbl;
        es = db->getTextStyleTable(textTbl, mode);
        symTbl = textTbl;
    }
    else if (symTblClass == AcDbRegAppTableRecord::desc()) {
        AcDbRegAppTable* appTbl;
        es = db->getRegAppTable(appTbl, mode);
        symTbl = appTbl;
    }
    else if (symTblClass == AcDbUCSTableRecord::desc()) {
        AcDbUCSTable* ucsTbl;
        es = db->getUCSTable(ucsTbl, mode);
        symTbl = ucsTbl;
    }
    else if (symTblClass == AcDbViewTableRecord::desc()) {
        AcDbViewTable* viewTbl;
        es = db->getViewTable(viewTbl, mode);
        symTbl = viewTbl;
    }
    else if (symTblClass == AcDbViewportTableRecord::desc()) {
        AcDbViewportTable* vportTbl;
        es = db->getViewportTable(vportTbl, mode);
        symTbl = vportTbl;
    }
    else
        es = Acad::eInvalidInput;    // passed in a class type that is illegal

    ASSERT(es == Acad::eOk);    // should never fail!
    if (es != Acad::eOk) {
        ArxDbgUtils::rxErrorMsg(es);
        return NULL;
    }
    else
        return symTbl;
}

/****************************************************************************
**
**	ArxDbgUtils::collectSymbolIds:
**		iterate through a symbol table and get all of the object Ids
**
**	**jma
**
*************************************/

Acad::ErrorStatus
ArxDbgUtils::collectSymbolIds(AcRxClass* symTblClass,
                            AcDbObjectIdArray& objIds, AcDbDatabase* db)
{
	ASSERT(symTblClass != NULL);
	ASSERT(db != NULL);

    Acad::ErrorStatus retCode = Acad::eInvalidInput;

    AcDbSymbolTable* symTbl = openSymbolTable(symTblClass, AcDb::kForRead, db);
    if (symTbl != NULL) {
            // get an iterator over this symbol Table
        AcDbSymbolTableIterator* tblIter;
        if (symTbl->newIterator(tblIter) == Acad::eOk) {
                // walk table and just collect all the objIds
                // of the entries
            if (symTbl->isKindOf(AcDbLayerTable::desc()))
                static_cast<AcDbLayerTableIterator*>(tblIter)->setSkipHidden(false);
            Acad::ErrorStatus es;
            AcDbObjectId tblRecId;
            for (; !tblIter->done(); tblIter->step()) {
                es = tblIter->getRecordId(tblRecId);
                if (es == Acad::eOk)
                    objIds.append(tblRecId);
            }
            delete tblIter;
            retCode = Acad::eOk;
        }
        symTbl->close();
    }
    return retCode;
}

/****************************************************************************
**
**  ArxDbgUtils::collectBlockIds
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgUtils::collectBlockIds(SdStrObjIdList& list, bool excludeMsPs,
                            bool excludeXref, bool excludeAnonymous, AcDbDatabase* db)
{
	ASSERT(db != NULL);

    Acad::ErrorStatus retCode = Acad::eInvalidInput;

    AcDbBlockTable* blkTbl;
	Acad::ErrorStatus es = db->getSymbolTable(blkTbl, AcDb::kForRead);
	if (es == Acad::eOk) {
            // get an iterator over this symbol Table
        AcDbBlockTableIterator* tblIter;
        es = blkTbl->newIterator(tblIter);
        ASSERT(tblIter != NULL);
        if (es == Acad::eOk) {
                // walk table and just collect all the objIds
                // of the entries
            AcDbObjectId tblRecId;
            for (; !tblIter->done(); tblIter->step()) {
                AcDbBlockTableRecord* blkRec;
                es = tblIter->getRecord(blkRec, AcDb::kForRead);
                if (es == Acad::eOk) {
                    if (excludeMsPs && blkRec->isLayout()) {
                        ;    // do nothing
					}
                    else if ((excludeXref) &&
                             ((blkRec->isFromExternalReference()) ||
                              (blkRec->isFromOverlayReference()))) {
                        ;    // do nothing
                    }
                    else if (excludeAnonymous && blkRec->isAnonymous()) {
                        ;    // do nothing
					}
                    else {
						const TCHAR* name;
						blkRec->getName(name);
                        list.AddAlpha(name, blkRec->objectId());
					}

                    blkRec->close();
                }
            }
            delete tblIter;
            retCode = Acad::eOk;
        }
        blkTbl->close();
    }
    return retCode;
}

/****************************************************************************
**
**	ArxDbgUtils::addNewSymbolAndClose
**		add a new symbol record to the given symbol table and then close
**	the record on success or delete the record on failure.
**
**	**jma
**
*************************************/

Acad::ErrorStatus
ArxDbgUtils::addNewSymbolAndClose(AcDbSymbolTable* symTbl,
                                        AcDbSymbolTableRecord* newRecord)
{
    Acad::ErrorStatus es;

    es = symTbl->add(newRecord);
    if (es == Acad::eOk)
        newRecord->close();
    else
        delete newRecord;
    
    return es;
}

/****************************************************************************
**
**	ArxDbgUtils::addNewLayer
**		add a new layer with the given name, and with all the default settings
**	If the layer already exists, this func will just return Acad::eOk
**
**	**jma
**
*************************************/

Acad::ErrorStatus
ArxDbgUtils::addNewLayer(LPCTSTR layerName, AcDbDatabase* db)
{
	ASSERT(db != NULL);

        // if layer already exists, then just return
    AcDbLayerTable* layTbl;
	Acad::ErrorStatus es = db->getSymbolTable(layTbl, AcDb::kForRead);
	if (es != Acad::eOk)
		return es;

    if (layTbl->has(layerName)) {
        layTbl->close();
        return Acad::eOk;
    }
        // upgrade to write
    es = layTbl->upgradeOpen();
    if (es != Acad::eOk) {
        ASSERT(0);
        layTbl->close();
        return es;
    }
        // make sure the name gets set ok
    AcDbLayerTableRecord* newRec = new AcDbLayerTableRecord;
    es = newRec->setName(layerName);
    if (es != Acad::eOk) {
        delete newRec;
        layTbl->close();
        return Acad::eInvalidInput;
    }
        // look up value for default linetype CONTINUOUS,
        // AcDbLayerTableRecord doesn't set this automatically (at least it didn't in Sedona)
    newRec->setLinetypeObjectId(db->continuousLinetype());

    es = layTbl->add(newRec);
    if (es != Acad::eOk)
        delete newRec;
    else
        newRec->close();

    layTbl->close();
    return es;
}

/****************************************************************************
**
**	ArxDbgUtils::defineNewBlock
**		Use when you are trying to define or re-define a block.  If
**	re-defining, this function will delete the current contents of the block
**	for you first.  If defining for the first time, it will add a new
**	record to the blockTable for you and return an openedForWrite blockRec.
**
**	**jma
**
*************************************/

Acad::ErrorStatus
ArxDbgUtils::defineNewBlock(LPCTSTR blkName, AcDbBlockTableRecord*& newBlkRec,
                            AcDbObjectId& newBlkRecId, AcDbDatabase* db)
{
	ASSERT(db != NULL);

    AcDbBlockTable* blkTbl;
	Acad::ErrorStatus es = db->getSymbolTable(blkTbl, AcDb::kForWrite);
    if (es != Acad::eOk)
        return es;

        // if this block already exists, erase its contents first
    if (blkTbl->getAt(blkName, newBlkRec, AcDb::kForWrite) == Acad::eOk) {
        newBlkRecId = newBlkRec->objectId();
        AcDbBlockTableRecordIterator* iter;
        es = newBlkRec->newIterator(iter);
        if (es != Acad::eOk) {
            ArxDbgUtils::rxErrorMsg(es);
            newBlkRec->close();
        }
        else {
            AcDbEntity* ent;
            for (; !iter->done(); iter->step()) {
                if (iter->getEntity(ent, AcDb::kForWrite) == Acad::eOk) {
                    ent->erase();
                    ent->close();
                }
            }
            delete iter;
        }
    }
    else {    // create a new block table record and add it to the block table
        newBlkRec = new AcDbBlockTableRecord;
        newBlkRec->setPathName(AcadString::nullStr);    // constructor doesn't do it properly

        es = newBlkRec->setName(blkName);
        if (es == Acad::eOk)
            es = blkTbl->add(newBlkRecId, newBlkRec);

        if (es != Acad::eOk) {
            ArxDbgUtils::rxErrorMsg(es);
            delete newBlkRec;
        }
    }

    blkTbl->close();    // doesn't need to be open anymore
    return es;
}

/****************************************************************************
**
**	ArxDbgUtils::defineNewBlock
**		streamlined version when you don't care about new record Id.
**
**	**jma
**
*************************************/

Acad::ErrorStatus
ArxDbgUtils::defineNewBlock(LPCTSTR blkName, AcDbBlockTableRecord*& newBlkRec,
                            AcDbDatabase* db)
{
    AcDbObjectId newBlkRecId;
    return defineNewBlock(blkName, newBlkRec, newBlkRecId, db);
}

/****************************************************************************
**
**	ArxDbgUtils::defineNewBlock
**		streamlined version when you don't care about new record Pointer.
**
**	**jma
**
*************************************/

Acad::ErrorStatus
ArxDbgUtils::defineNewBlock(LPCTSTR blkName, AcDbObjectId& newBlkRecId, AcDbDatabase* db)
{
    AcDbBlockTableRecord* newBlkRec;
    Acad::ErrorStatus es = defineNewBlock(blkName, newBlkRec, newBlkRecId, db);
    if (es == Acad::eOk)
        newBlkRec->close();
    return es;
}

/****************************************************************************
**
**	ArxDbgUtils::defineNewAnonymousBlock
**
**	**jma
**
*************************************/

Acad::ErrorStatus
ArxDbgUtils::defineNewAnonymousBlock(AcDbBlockTableRecord*& newBlkRec,
                                AcDbObjectId& newBlkRecId, AcDbDatabase* db)
{
	ASSERT(db != NULL);

    AcDbBlockTable* blkTbl;
	Acad::ErrorStatus es = db->getSymbolTable(blkTbl, AcDb::kForWrite);
    if (es != Acad::eOk)
        return es;

    newBlkRec = new AcDbBlockTableRecord;
    newBlkRec->setPathName(AcadString::nullStr);    // constructor doesn't do it properly

    es = newBlkRec->setName(_T("*U"));
    if (es == Acad::eOk)
        es = blkTbl->add(newBlkRecId, newBlkRec);

    if (es != Acad::eOk) {    // make sure everything went ok
        ArxDbgUtils::rxErrorMsg(es);
        delete newBlkRec;
        newBlkRec = NULL;    // don't let caller get bad value
    }

    blkTbl->close();    // doesn't need to be open anymore
    return es;
}

/****************************************************************************
**
**	ArxDbgUtils::defineNewAnonymousBlock
**		streamlined version when you don't care about new record Id.
**
**	**jma
**
*************************************/

Acad::ErrorStatus
ArxDbgUtils::defineNewAnonymousBlock(AcDbBlockTableRecord*& newBlkRec, AcDbDatabase* db)
{
    AcDbObjectId newBlkRecId;
    return defineNewAnonymousBlock(newBlkRec, newBlkRecId, db);
}

/****************************************************************************
**
**	ArxDbgUtils::defineNewAnonymousBlock
**		streamlined version when you don't care about new record Pointer.
**
**	**jma
**
*************************************/

Acad::ErrorStatus
ArxDbgUtils::defineNewAnonymousBlock(AcDbObjectId& newBlkRecId, AcDbDatabase* db)
{
    AcDbBlockTableRecord* newBlkRec;
    Acad::ErrorStatus es = defineNewAnonymousBlock(newBlkRec, newBlkRecId, db);
    if (es == Acad::eOk)
        newBlkRec->close();
    return es;
}

/****************************************************************************
**
**	ArxDbgUtils::openBlockDef
**		open a named block definition from the block table.  Only print
**	an error message if it was actually there and couldn't be opened.
**
**	**jma
**
*************************************/

Acad::ErrorStatus
ArxDbgUtils::openBlockDef(LPCTSTR blkName, AcDbBlockTableRecord*& blkRec,
                                    AcDb::OpenMode mode, AcDbDatabase* db)
{
    ASSERT(blkName != NULL);
	ASSERT(db != NULL);

    AcDbBlockTable* blkTbl;
	Acad::ErrorStatus es = db->getSymbolTable(blkTbl, AcDb::kForRead);
    if (es != Acad::eOk)
        return es;

        // open named block
    es = blkTbl->getAt(blkName, blkRec, mode);
    if (es != Acad::eKeyNotFound)
        ArxDbgUtils::rxErrorMsg(es);        // print error message if its an unexpected error

    blkTbl->close();    // doesn't need to be open anymore
    return es;
}

/****************************************************************************
**
**	ArxDbgUtils::openCurrentSpaceBlock
**
**	**jma
**
*************************************/

AcDbBlockTableRecord*
ArxDbgUtils::openCurrentSpaceBlock(AcDb::OpenMode mode, AcDbDatabase* db)
{
	ASSERT(db != NULL);

    AcDbBlockTableRecord* blkRec;

    Acad::ErrorStatus es = acdbOpenObject(blkRec, db->currentSpaceId(), mode);
    if (es != Acad::eOk)
        return NULL;
    else
        return blkRec;
}

/****************************************************************************
**
**  ArxDbgUtils::addToCurrentSpace
**		for convienence sake since this is usually called with the current db
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgUtils::addToCurrentSpace(AcDbEntity* newEnt)
{
	return addToCurrentSpace(newEnt, acdbHostApplicationServices()->workingDatabase());
}

/****************************************************************************
**
**  ArxDbgUtils::addToCurrentSpace
**      add a new entity to the current space block record.
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgUtils::addToCurrentSpace(AcDbEntity* newEnt, AcDbDatabase* db)
{
    ASSERT(newEnt != NULL);
	ASSERT(db != NULL);

    AcDbBlockTableRecord* blkRec = openCurrentSpaceBlock(AcDb::kForWrite, db);

    ASSERT(blkRec != NULL);

    if (blkRec == NULL)
        return Acad::eInvalidInput;

        // append new entity to current space block
    Acad::ErrorStatus es = blkRec->appendAcDbEntity(newEnt);
    if (es != Acad::eOk) {
        acutPrintf(_T("\nERROR: could not add entity to current space (%s)"), ArxDbgUtils::rxErrorStr(es));
    }

    blkRec->close();
    return es;
}

/****************************************************************************
**
**  ArxDbgUtils::addToCurrentSpaceAndClose
**      add a new entity to the current space block record.
**
**  NOTE:  this function accepts responsibility for the new entity.
**  If appending to the blkRec fails, it will delete it and if successful
**  it will close it.
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgUtils::addToCurrentSpaceAndClose(AcDbEntity* newEnt, AcDbDatabase* db)
{
    Acad::ErrorStatus es;

    es = addToCurrentSpace(newEnt, db);
    if (es == Acad::eOk)
        newEnt->close();
    else
        delete newEnt;

    return es;
}

/****************************************************************************
**
**  ArxDbgUtils::addToCurrentSpaceAndClose
**		for convienence sake since this is usually called with the current db
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgUtils::addToCurrentSpaceAndClose(AcDbEntity* newEnt)
{
	return addToCurrentSpaceAndClose(newEnt, acdbHostApplicationServices()->workingDatabase());
}

/****************************************************************************
**
**  ArxDbgUtils::isOnLockedLayer
**
**  **jma
**
*************************************/

bool
ArxDbgUtils::isOnLockedLayer(AcDbObjectId& id, bool printMsg)
{
    AcDbEntity* ent;
	Acad::ErrorStatus es = acdbOpenAcDbEntity(ent, id, AcDb::kForRead);
    if (es == Acad::eOk) {
        bool result = isOnLockedLayer(ent, printMsg);
        ent->close();
        return result;
    }

    return true;  // by default we "lock" data
}

/****************************************************************************
**
**  ArxDbgUtils::isOnLockedLayer
**
**  **jma
**
*************************************/

bool
ArxDbgUtils::isOnLockedLayer(AcDbEntity* ent, bool printMsg)
{
    AcDbObject* obj;
    AcDbLayerTableRecord* layer;
    bool isLocked = false;
    Acad::ErrorStatus es;

    es = acdbOpenAcDbObject(obj, ent->layerId(), AcDb::kForRead);
    if (es == Acad::eOk) {
        layer = AcDbLayerTableRecord::cast(obj);
        if (layer)
            isLocked = layer->isLocked();
        else {
            ASSERT(0);
        }
        obj->close();
    }
    else {
        ASSERT(0);
        ArxDbgUtils::rxErrorMsg(es);
    }

    if (isLocked && printMsg) {
        acutPrintf(_T("\nSelected entity is on a locked layer."));
    }

    return isLocked;
}



