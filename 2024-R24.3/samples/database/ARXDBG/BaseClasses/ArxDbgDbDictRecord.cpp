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

#include "ArxDbgDbDictRecord.h"
#include "ArxDbgUtils.h"
#include "ArxDbgUiTdmObjects.h"
#include "ArxDbgOptions.h"



ACRX_DXF_DEFINE_MEMBERS(ArxDbgDbDictRecord, AcDbObject,
						AcDb::kDHL_1015, AcDb::kMRelease0,
						0, ARXDBG_DICT_RECORD, ArxDbg)

/****************************************************************************
**
**  ArxDbgDbDictRecord::ArxDbgDbDictRecord
**
**  **jma
**
*************************************/

ArxDbgDbDictRecord::ArxDbgDbDictRecord()
{
}

/****************************************************************************
**
**  ArxDbgDbDictRecord::~ArxDbgDbDictRecord
**
**  **jma
**
*************************************/

ArxDbgDbDictRecord::~ArxDbgDbDictRecord()
{
}

/****************************************************************************
**
**  ArxDbgDbDictRecord::description
**
**  **jma
**
*************************************/

const TCHAR*
ArxDbgDbDictRecord::description() const
{
    assertReadEnabled();
    return m_description;
}

/****************************************************************************
**
**  ArxDbgDbDictRecord::setDescription
**
**  **jma
**
*************************************/

void
ArxDbgDbDictRecord::setDescription(const TCHAR* val)
{
    if (m_description != val) {
        assertWriteEnabled();    // only trigger UNDO/Reactors if actually changed
        m_description = val;
    }
}

/****************************************************************************
**
**  ArxDbgDbDictRecord::getName
**		we don't store our name directly, but we can get it from the dictionary
**	that we belong to.
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDbDictRecord::getName(CString& name) const
{
    assertReadEnabled();

    AcDbDictionary* dict;
    Acad::ErrorStatus es = acdbOpenObject(dict, ownerId(), AcDb::kForRead);
    if (es == Acad::eOk) {
        TCHAR* tmpStrPtr = NULL;
        es = dict->nameAt(objectId(), tmpStrPtr);
        if (es == Acad::eOk) {
            ASSERT(tmpStrPtr != NULL);
            name = tmpStrPtr;
            acutDelString(tmpStrPtr);
        }
        dict->close();
    }

	return es;
}

/****************************************************************************
**
**  ArxDbgDbDictRecord::dwgInFields
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDbDictRecord::dwgInFields(AcDbDwgFiler* filer)
{
	if (ArxDbgOptions::m_instance.m_showDwgFilerMessages) {
		CString str, str2;
		acutPrintf(_T("\n%s <DwgIn  : %s>"), ArxDbgUtils::objToClassAndHandleStr(this, str),
				ArxDbgUtils::filerTypeToStr(filer->filerType(), str2));
	}

    assertWriteEnabled();
    Acad::ErrorStatus es;

    if ((es = AcDbObject::dwgInFields(filer)) != Acad::eOk)
        return(es);

    TCHAR* tmpStr = NULL;    // must explicitly set to NULL or readItem() crashes!

        // read test value into CString
    filer->readItem(&tmpStr);
    m_description = tmpStr;
    acutDelString(tmpStr);

    return filer->filerStatus();
}

/****************************************************************************
**
**  ArxDbgDbDictRecord::dwgOutFields
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDbDictRecord::dwgOutFields(AcDbDwgFiler* filer) const
{
	if (ArxDbgOptions::m_instance.m_showDwgFilerMessages) {
		CString str, str2;
		acutPrintf(_T("\n%s <DwgOut : %s>"),
				ArxDbgUtils::objToClassAndHandleStr(const_cast<ArxDbgDbDictRecord*>(this), str),
				ArxDbgUtils::filerTypeToStr(filer->filerType(), str2));
	}

    assertReadEnabled();
    Acad::ErrorStatus es;

    if ((es = AcDbObject::dwgOutFields(filer)) != Acad::eOk)
        return es;

    filer->writeItem(static_cast<const TCHAR*>(m_description));

    return filer->filerStatus();
}

/****************************************************************************
**
**  ArxDbgDbDictRecord::dxfInFields
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDbDictRecord::dxfInFields(AcDbDxfFiler* filer)
{
    assertWriteEnabled();
    Acad::ErrorStatus es;

    if (((es = AcDbObject::dxfInFields(filer)) != Acad::eOk) ||
        (filer->atSubclassData(this->desc()->name()) != Adesk::kTrue))
        return filer->filerStatus();

    struct resbuf rb;
    es = Acad::eOk;

    while ((es == Acad::eOk) && ((es = filer->readResBuf(&rb)) == Acad::eOk)) {
        if (rb.restype == kDxfDescription) {
            ASSERT(rb.resval.rstring != NULL);
            m_description = rb.resval.rstring;
        }
        else {
            filer->pushBackItem();
            es = Acad::eEndOfFile;
        }
    }
    if (es != Acad::eEndOfFile)
        return Acad::eInvalidResBuf;

    return filer->filerStatus();
}

/****************************************************************************
**
**  ArxDbgDbDictRecord::dxfOutFields
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDbDictRecord::dxfOutFields(AcDbDxfFiler* filer) const
{
    assertReadEnabled();
    Acad::ErrorStatus es;

    if ((es = AcDbObject::dxfOutFields(filer)) != Acad::eOk)
        return es;

    filer->writeItem(AcDb::kDxfSubclass, this->desc()->name());

    filer->writeItem(kDxfDescription, static_cast<const TCHAR*>(m_description));

    return filer->filerStatus();
}

/****************************************************************************
**
**  ArxDbgDbDictRecord::mangleNameForXref
**
**  **jma
**
*************************************/

bool
ArxDbgDbDictRecord::mangleNameForXref(CString& name, AcDbDatabase* db, AcDbDictionary* pDict) const
{
    AcDbXrefGraph xGraph;
    acedGetCurDwgXrefGraph(xGraph);
    AcDbXrefGraphNode* pNode = xGraph.xrefNode(db);
    if (pNode == NULL) {
        ASSERT(0);
        return false;
    }

	bool useExtNames = false;
	Acad::ErrorStatus es = acdbGetExtnames(useExtNames, db);

    CString boundName;
    CString xrefName = pNode->name();
    long count = 0;
    while (1) {
        boundName.Format(_T("%s$%ld$%s"), xrefName, count, name);

			// TBD: AutoCAD doesn't seem to worry about this... perhaps we shouldn't either?

			// if we can't use extended symbol names, then we have to
			// make sure the length doesn't exceed 31 characters.
		if (useExtNames == false) {
				// if this name would be too long, just use count with the original symbol name
			if (boundName.GetLength() > 31) {
				CString countStr;
				countStr.Format(_T("%ld"), count);

					// this should never happen, but just being extra safe!
				if (countStr.GetLength() > 31) {
					ASSERT(0);
					return false;
				}

					// make sure count will fully fit at the end of the string
				boundName = name;
				if (boundName.GetLength() > 31) {
					CString tmpStr = boundName.Left(30 - countStr.GetLength());    // leave place for $    //MBCS
					boundName.Format(_T("%s$%s"), tmpStr, countStr);
				}
			}

			ASSERT(boundName.GetLength() < 32);
		}

        if (pDict->has(boundName) == false) {
            name = boundName;
            return true;
        }
        count++;
    }
}

/****************************************************************************
**
**  ArxDbgDbDictRecord::mangleNameForRefEdit
**
**  **jma
**
*************************************/

bool
ArxDbgDbDictRecord::mangleNameForRefEdit(CString& name, AcDbDictionary* pDict) const
{
	CString rootName = name;
	int index = 0;

    do {
        name.Format(_T("%c%d%c%s"), _T('$'), index++, _T('$'), rootName);

        ASSERT(index < 1000);	// numbers are getting a little large... why?
    } while (pDict->has(name));

	return true;
}

/****************************************************************************
**
**  ArxDbgDbDictRecord::unMangleNameForRefEdit
**
**  **jma	(lifted from AutoCAD source)
**
*************************************/

bool
ArxDbgDbDictRecord::unMangleNameForRefEdit(CString& name) const
{
    int namePos;
    int nameLen;

    if (name[0] == _T('$')) {
        nameLen = name.GetLength();
        bool bTruncate = false;
        bool bFoundNumber = false;
        for (namePos = 1; namePos < nameLen; namePos++) {
            if ((name[namePos] >= _T('0')) &&
                (name[namePos] <= _T('9'))) {
                bFoundNumber = true;
            }
			else {
                if (bFoundNumber && name[namePos] == _T('$'))
                    bTruncate = true;
                break;
            }
        }

			// Only do it if there is a name to the right 
			// of the $0$.
        if (bTruncate && (++namePos < nameLen)) {
            name = name.Right(nameLen - namePos);
            return true;
        }
    }
    return false;
}

/****************************************************************************
**
**  ArxDbgDbDictRecord::isDictInNOD
**      we only want to special dictionary merging if we are dealing with a
**  dictionary in the main Named Object Dictionary.  Extension dictionaries
**  will not conflict and are cloned as a whole with no merging.  NOTE: we
**  cannot just follow the ownerId() chain up to see where the tree starts
**  because DXFIN severs all the ownerIds for dictionary records (at least that
**	was the case in R14).
**
**  **jma
**
*************************************/

bool
ArxDbgDbDictRecord::isDictInNOD(const AcDbObjectId& dictId, const AcDbObjectId& entryId,
                      AcDbDatabase* db,
                      CString& dictName, CString& entryName) const
{
	ASSERT(db != NULL);

    AcDbDictionary* rootDict;
	Acad::ErrorStatus es;
	es = db->getNamedObjectsDictionary(rootDict, AcDb::kForRead);
    if (es != Acad::eOk) {
        ASSERT(0);
        return false;
    }

    bool isMainDict = false;

    TCHAR* tmpName = NULL;
    es = rootDict->nameAt(dictId, tmpName);
    if (es == Acad::eOk) {
        dictName = tmpName;   // record name of this owner dictionary

        AcDbDictionary* dict;
        es = acdbOpenObject(dict, dictId, AcDb::kForRead);
        if (es == Acad::eOk) {
            TCHAR* tmpName2;
            es = dict->nameAt(entryId, tmpName2);
            if (es == Acad::eOk) {
                isMainDict = true;
                entryName = tmpName2;       // record name of our entry
                acutDelString(tmpName2);
            }
            else {
                ArxDbgUtils::rxErrorMsg(es);
            }
            dict->close();
        }

        acutDelString(tmpName);
    }

    rootDict->close();

    return isMainDict;
}

/****************************************************************************
**
**  ArxDbgDbDictRecord::wblockClone
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDbDictRecord::subWblockClone(AcRxObject* pOwner,
							AcDbObject*& pClonedObject,
							AcDbIdMapping& idMap,
							Adesk::Boolean isPrimary) const
{
		// the standard base class behavior works fine for all but
		// the following contexts.
    Acad::ErrorStatus es;
    AcDb::DeepCloneType dc = idMap.deepCloneContext();
    if ((dc != AcDb::kDcXrefBind) &&
		(dc != AcDb::kDcXrefInsert) &&
        (dc != AcDb::kDcWblkObjects)) {
        return AcDbObject::subWblockClone(pOwner, pClonedObject, idMap, isPrimary);
    }

    pClonedObject = NULL;	// set clone to NULL in case we don't make a copy

		// Make sure we have not already done this one.
    AcDbIdPair idPair(objectId(), AcDbObjectId::kNull, true);
    if (idMap.compute(idPair) && (idPair.value() != AcDbObjectId::kNull))
        return eOk;

		// if we are in an extension dictionary, don't worry about any
		// mangling since we will get cloned in entirety  (I think!)
    CString dictName, entryName;
    if (isDictInNOD(ownerId(), objectId(), database(), dictName, entryName) == false)
        return AcDbObject::subWblockClone(pOwner, pClonedObject, idMap, isPrimary);

    bool isAnonymous = (entryName[0] == _T('*')) ? true : false;

		// Xref Bind will always pass in an AcDbDatabase* for pOwner, but
		// kDcWblkObjects may also pass in the destination dictionary already
		// open.  So, if pDestDb == NULL, we know that we did not open the
		// dictionary here.
    AcDbDictionary* pDestDict = NULL;
    AcDbDatabase* pDestDb = AcDbDatabase::cast(pOwner);
    if (pDestDb) {
		pDestDict = ArxDbgUtils::openDictionaryForWrite(dictName, true, pDestDb);
        if (pDestDict == NULL)
            return Acad::eInvalidInput;
    }
	else 
        pDestDict = AcDbDictionary::cast(pOwner);

    ASSERT(pDestDict != NULL);
    ASSERT(pDestDb != NULL || dc == AcDb::kDcWblkObjects);

    AcDb::DuplicateRecordCloning drc = idMap.duplicateRecordCloning();

    AcDbObjectId existingId;

    if (isAnonymous) {
        entryName = _T("*");
    }
	else {
		if (drc == AcDb::kDrcUnmangleName) {
			unMangleNameForRefEdit(entryName);

				// NOTE: in the usual case for RefEdit, this will be the entry
				// that was originally checkedOut of the set.  All changes will
				// be lost when checking it back in.  See what Layers do as an
				// example that this is "correct" behavior.
			if (pDestDict->getAt(entryName, existingId) == Acad::eOk) {
				if (pDestDb)
					pDestDict->close();

				return idMap.assign(AcDbIdPair(objectId(), existingId, false, false));
			}
		}
		else if (drc == AcDb::kDrcIgnore) {
			if (pDestDict->getAt(entryName, existingId) == Acad::eOk) {
				if (pDestDb)
					pDestDict->close();

				return idMap.assign(AcDbIdPair(objectId(), existingId, false, false));
			}
		}
		else if (drc == AcDb::kDrcMangleName) {			// use $0$name mangling
			if (!mangleNameForRefEdit(entryName, pDestDict))
				entryName = _T("*");  // make anonymous as a last resort!
		}
		else if (drc == AcDb::kDrcXrefMangleName) {		// use xref$0$name mangling
			if (!mangleNameForXref(entryName, database(), pDestDict))
				entryName = _T("*");  // make anonymous as a last resort!
		}
		else {
			// haven't dealt with kDrcReplace yet!
			ASSERT(0);	// TBD: apparently, this won't be implemented in R15 anyway
		}
	}

		// if not cloned okay, or we already cloned, then bail early
    es = AcDbObject::subWblockClone(pDestDict, pClonedObject, idMap, isPrimary);
    if ((es != Acad::eOk) || (pClonedObject == NULL)) {
		if (pDestDb)
			pDestDict->close();
        return es;
    }

        // now add this object to the dictionary
    AcDbObjectId id;
    es = pDestDict->setAt(entryName, pClonedObject, id);

		// close it only if we opened it
    if (pDestDb)
        pDestDict->close();

        // If no errors, leave the clone open, as we are still
        // inside wblockClone().
    if (es != Acad::eOk) {
        delete pClonedObject;
        pClonedObject = NULL;
        return es;
    }

    return es;
}
