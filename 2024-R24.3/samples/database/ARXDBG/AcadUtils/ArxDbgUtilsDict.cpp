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



/****************************************************************************
**
**	ArxDbgUtils::getRegularDictionaryId
**		get the id of a dictionary considered to be "regular" (one which is
**	underneath the RootNamedObjectDictionary.
**
**	**jma
**
*************************************/

AcDbObjectId
ArxDbgUtils::getRegularDictionaryId(LPCTSTR dictName, bool createIfNotFound, AcDbDatabase* db)
{
	ASSERT(db != NULL);

    AcDbObjectId dictId  = AcDbObjectId::kNull;

        // get the root dict for this database
    AcDbDictionary* rootDict;
	Acad::ErrorStatus es = db->getNamedObjectsDictionary(rootDict, AcDb::kForRead);
	if (es != Acad::eOk) {
		ArxDbgUtils::rxErrorMsg(es);
		return AcDbObjectId::kNull;
	}

        // try to first open for read and see if it is already there
    AcDbDictionary* dict;
    dict = openDictionaryForRead(dictName, rootDict);
    if (dict) {
        dictId = dict->objectId();
        dict->close();
    }
    else {    // the dictionary has not yet been created
        if (createIfNotFound) {
            es = rootDict->upgradeOpen();
            if ((es == Acad::eOk) || (es == Acad::eWasOpenForWrite)) {
                dict = openDictionaryForWrite(dictName, true, rootDict);
                if (dict) {
                    dictId = dict->objectId();
                    dict->close();
                }
            }
        }
    }
    rootDict->close();    // don't need it anymore!
    return dictId;
}

/****************************************************************************
**
**  ArxDbgUtils::getSubDictionaryId
**
**  **jma
**
*************************************/

AcDbObjectId
ArxDbgUtils::getSubDictionaryId(LPCTSTR dictName, bool createIfNotFound,
                                AcDbDictionary* parentDict)
{
    ASSERT(parentDict != NULL);

    AcDbObjectId dictId;

        // try to first see if it is already there
    Acad::ErrorStatus es = parentDict->getAt(dictName, dictId);
    if (es == Acad::eOk) {
        return dictId;
    }
    else if (es == Acad::eKeyNotFound) {
        if (createIfNotFound) {
                // upgrade parentDict to write if not already
            if (parentDict->isWriteEnabled() == Adesk::kFalse) {
                es = parentDict->upgradeOpen();
                if ((es != Acad::eOk) && (es != Acad::eWasOpenForWrite)) {
                    ArxDbgUtils::rxErrorAlert(es);
                    ASSERT(0);
                    return AcDbObjectId::kNull;
                }
            }
                // create this new dict
            AcDbDictionary* newDict = new AcDbDictionary;
            es = parentDict->setAt(dictName, newDict, dictId);
            if (es == Acad::eOk) {
                newDict->close();
                return dictId;
            }
            else {
                delete newDict;
                return AcDbObjectId::kNull;
            }
        }
        else
            return AcDbObjectId::kNull;
    }
    else {
        ArxDbgUtils::rxErrorAlert(es);
        ASSERT(0);
        return AcDbObjectId::kNull;
    }
}

/****************************************************************************
**
**	ArxDbgUtils::openDictionaryForRead
**		use this when you expect the dictionary to be there and you
**	are just retrieving values out of it. This is a wrapper for finding
**	this dictionary underneath the root dictionary of the current drawing.
**
**	**jma
**
*************************************/

AcDbDictionary*
ArxDbgUtils::openDictionaryForRead(LPCTSTR dictName, AcDbDatabase* db)
{
	ASSERT(db != NULL);

        // get the root dict for this database
    AcDbDictionary* dict = NULL;
    AcDbDictionary* rootDict;
	Acad::ErrorStatus es = db->getNamedObjectsDictionary(rootDict, AcDb::kForRead);
	if (es == Acad::eOk) {
			// now get the sub-dict
        dict = openDictionaryForRead(dictName, rootDict);
        rootDict->close();
	}
	else {
		ArxDbgUtils::rxErrorMsg(es);
    }

    return dict;
}

/****************************************************************************
**
**	ArxDbgUtils::openDictionaryForRead
**		use this when you expect the dictionary to be there and you
**	are just retrieving values out of it. The parentDict is the
**	dictionary that contians the one you are looking for
**
**	**jma
**
*************************************/

AcDbDictionary*
ArxDbgUtils::openDictionaryForRead(LPCTSTR dictName, const AcDbObjectId& parentDictId)
{
    ASSERT(dictName != NULL);
    if (parentDictId == AcDbObjectId::kNull)
        return NULL;

        // figure out what parent directory they want
    AcDbDictionary* parentDict;
    Acad::ErrorStatus es = acdbOpenObject(parentDict, parentDictId, AcDb::kForRead);
    if (es != Acad::eOk) {
        ArxDbgUtils::rxErrorMsg(es);
        return NULL;
    }

    AcDbDictionary* dict = openDictionaryForRead(dictName, parentDict);
    parentDict->close();
    return dict;
}

/****************************************************************************
**
**	ArxDbgUtils::openDictionaryForRead
**		use this when you expect the dictionary to be there and you
**	are just retrieving values out of it. The parentDict is the
**	dictionary that contians the one you are looking for
**
**	**jma
**
*************************************/

AcDbDictionary*
ArxDbgUtils::openDictionaryForRead(LPCTSTR dictName, AcDbDictionary* parentDict)
{
    ASSERT(dictName != NULL);
    ASSERT(parentDict != NULL);

        // get the dictionary that we are looking for
    AcDbObject* obj;
    Acad::ErrorStatus es = parentDict->getAt(dictName, obj, AcDb::kForRead);

    if (es == Acad::eOk)
        return AcDbDictionary::cast(obj);
    else
        return NULL;
}

/****************************************************************************
**
**	ArxDbgUtils::openDictionaryForWrite
**		wrapper for opening a dictionary stored off of the root dictionary
**	of the current directory.
**
**	**jma
**
*************************************/

AcDbDictionary*
ArxDbgUtils::openDictionaryForWrite(LPCTSTR dictName, bool createIfNotFound, AcDbDatabase* db)
{
	ASSERT(db != NULL);

        // get the root dict for this database
    AcDbDictionary* dict = NULL;
    AcDbDictionary* rootDict;
	Acad::ErrorStatus es = db->getNamedObjectsDictionary(rootDict, AcDb::kForWrite);
	if (es == Acad::eOk) {
			// now get the sub-dict
        dict = openDictionaryForWrite(dictName, createIfNotFound, rootDict);
        rootDict->close();
	}
	else {
		ArxDbgUtils::rxErrorMsg(es);
    }

    return dict;
}

/****************************************************************************
**
**	ArxDbgUtils::openDictionaryForWrite
**
**	**jma
**
*************************************/

AcDbDictionary*
ArxDbgUtils::openDictionaryForWrite(LPCTSTR dictName, bool createIfNotFound, const AcDbObjectId& parentDictId)
{
    ASSERT(dictName != NULL);
    if (parentDictId == AcDbObjectId::kNull)
        return NULL;

        // figure out what parent directory they want
    AcDbDictionary* parentDict;
    Acad::ErrorStatus es = acdbOpenObject(parentDict, parentDictId, AcDb::kForWrite);
    if (es != Acad::eOk) {
        ArxDbgUtils::rxErrorMsg(es);
        return NULL;
    }

    AcDbDictionary* dict = openDictionaryForWrite(dictName, createIfNotFound, parentDict);
    parentDict->close();
    return dict;
}

/****************************************************************************
**
**	ArxDbgUtils::openDictionaryForWrite
**
**	**jma
**
*************************************/

AcDbDictionary*
ArxDbgUtils::openDictionaryForWrite(LPCTSTR dictName, bool createIfNotFound,
                                            AcDbDictionary* parentDict)
{
    ASSERT(dictName != NULL);
    ASSERT(parentDict != NULL);
    ASSERT(parentDict->isWriteEnabled());    // make sure parent is open for write

    AcDbDictionary* dict = NULL;
    AcDbObject* obj;
    Acad::ErrorStatus es;

        // get the dictionary that we are looking for
    es = parentDict->getAt(dictName, obj, AcDb::kForWrite);
    if (es == Acad::eOk) {
        dict = AcDbDictionary::cast(obj);
    }
    else if (es == Acad::eKeyNotFound) {
        if (createIfNotFound) {
            dict = new AcDbDictionary;
            AcDbObjectId dictId;
            es = parentDict->setAt(dictName, dict, dictId);
            if (es != Acad::eOk) {
                acutPrintf(_T("\nERROR: could not create dictionary \"%s\" (%s)"), dictName, ArxDbgUtils::rxErrorStr(es));
                delete dict;
                dict = NULL;
            }
        }
    }
    else {
        ArxDbgUtils::rxErrorMsg(es);
    }

    return dict;
}

/****************************************************************************
**
**	ArxDbgUtils::collectDictionaryEntryNames
**		iterate over the dictionary and collect all the names contained
**	within it.
**
**	**jma
**
*************************************/

Acad::ErrorStatus
ArxDbgUtils::collectDictionaryEntryNames(const AcDbObjectId& dictId, SdStrObjIdList& list, AcRxClass* classType)
{
    Acad::ErrorStatus ret = Acad::eInvalidInput;

    AcDbDictionary* dict;
	ret = acdbOpenObject(dict, dictId, AcDb::kForRead);
    if (ret == Acad::eOk) {
        Acad::ErrorStatus es;
        AcDbObject* obj;
        AcDbDictionaryIterator* dictIter = dict->newIterator();
        ASSERT(dictIter != NULL);
        if (dictIter != NULL) {
            for (; !dictIter->done(); dictIter->next()) {
                es = dictIter->getObject(obj, AcDb::kForRead);
                if (es == Acad::eOk) {
                    if (classType == NULL)
						list.AddAlpha(dictIter->name(), dictIter->objectId());
					else if (obj->isKindOf(classType))
                        list.AddAlpha(dictIter->name(), dictIter->objectId());
                    obj->close();
                }
            }
            delete dictIter;
            ret = Acad::eOk;
        }
        else
            ret = Acad::eInvalidInput;

        dict->close();
    }
    return ret;
}

/****************************************************************************
**
**	ArxDbgUtils::lookUpDictEntryName
**		given an entry Id in a dictionary, look up its parent dictionary
**	and then find out what the key value is for this entry in the dictionary.
**
**	**jma
**
*************************************/

bool
ArxDbgUtils::lookUpDictEntryName(const AcDbObjectId& objId, CString& entryName)
{
    bool retCode = FALSE;
    AcDbObject* obj;

    Acad::ErrorStatus es = acdbOpenAcDbObject(obj, objId, AcDb::kForRead);
    if (es == Acad::eOk) {
        AcDbDictionary* dict;
        es = acdbOpenObject(dict, obj->ownerId(), AcDb::kForRead);
        if (es == Acad::eOk) {
            TCHAR* name = NULL;
            if (dict->nameAt(objId, name) == Acad::eOk) {
                entryName = name;
                retCode = true;
                acutDelString(name);
            }
            dict->close();
        }
        obj->close();        
    }
    return retCode;
}

/****************************************************************************
**
**	ArxDbgUtils::openExtDictForRead
**
**	**jma
**
*************************************/

AcDbDictionary*
ArxDbgUtils::openExtDictForRead(const AcDbObject* obj)
{
    ASSERT(obj != NULL);

        // Get extension dicitonary object Id
    Acad::ErrorStatus es;
    AcDbObjectId extDictId = obj->extensionDictionary();
    if (extDictId == AcDbObjectId::kNull)
        return NULL;

        // Open the dictionary
    AcDbDictionary* extDict;
    es = acdbOpenObject(extDict, extDictId, AcDb::kForRead);
    if (es != Acad::eOk) {
        ASSERT(0);
        return NULL;
    }

    return extDict;
}

/****************************************************************************
**
**	ArxDbgUtils::openExtDictForWrite
**		open an object's extension dictionary
**
**	**jma
**
*************************************/

AcDbDictionary*
ArxDbgUtils::openExtDictForWrite(AcDbObject* obj, bool createIfNotFound)
{
    ASSERT(obj != NULL);
    ASSERT(obj->isWriteEnabled());

        // Get extension dicitonary object Id, if it doesn't
        // exist yet, make it if asked for
    Acad::ErrorStatus es;
    AcDbObjectId extDictId = obj->extensionDictionary();
    if (extDictId == AcDbObjectId::kNull) {
        if (createIfNotFound) {
            es = obj->createExtensionDictionary();
            ASSERT(es == Acad::eOk);
            if (es != Acad::eOk) {
                ArxDbgUtils::rxErrorMsg(es);
                return NULL;
            }
            if ((extDictId = obj->extensionDictionary()) == AcDbObjectId::kNull) {
                acutPrintf(_T("\nERROR: Could not create an extension dictionary."));
                return NULL;
            }
        }
        else
            return NULL;
    }
        // Open the dictionary
    AcDbDictionary* extDict;
    es = acdbOpenObject(extDict, extDictId, AcDb::kForWrite);
    if (es != Acad::eOk) {
        ASSERT(0);
        return NULL;
    }

    return extDict;
}
