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

#include "ArxDbgDbEntity.h"
#include "ArxDbgUtils.h"
#include "ArxDbgUiTdmIdMap.h"
#include "ArxDbgOptions.h"



Adesk::Int16     ArxDbgDbEntity::m_version = 0;     // MDI safe

ACRX_DXF_DEFINE_MEMBERS(ArxDbgDbEntity, AcDbEntity,
						AcDb::kDHL_1015, AcDb::kMRelease0,
						0, ARXDBG_ENTITY, ArxDbg)

/****************************************************************************
**
**  ArxDbgDbEntity::ArxDbgDbEntity
**
**  **jma
**
*************************************/

ArxDbgDbEntity::ArxDbgDbEntity()
:   m_xDir(AcGeVector3d::kXAxis),
    m_zDir(AcGeVector3d::kZAxis)
{
}

/****************************************************************************
**
**  ArxDbgDbEntity::~ArxDbgDbEntity
**
**  **jma
**
*************************************/

ArxDbgDbEntity::~ArxDbgDbEntity()
{
}

/****************************************************************************
**
**  ArxDbgDbEntity::location
**
**  **jma
**
*************************************/

AcGePoint3d
ArxDbgDbEntity::location() const
{
    assertReadEnabled();
    return m_origin;
}

/****************************************************************************
**
**  ArxDbgDbEntity::setLocation
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDbEntity::setLocation(const AcGePoint3d& pt)
{
    if (pt != m_origin) {
        assertWriteEnabled();
        m_origin = pt;
    }

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDbEntity::rotation
**
**  **jma
**
*************************************/

double
ArxDbgDbEntity::rotation() const
{
    assertReadEnabled();

    AcGeVector3d xAxis;
    ArxDbgUtils::getEcsXAxis(m_zDir, xAxis);        // get AutoCAD's arbitrary X-Axis
    return xAxis.angleTo(m_xDir, m_zDir);
}

/****************************************************************************
**
**  ArxDbgDbEntity::setRotation
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDbEntity::setRotation(double rot)
{
    assertWriteEnabled();

    AcGeVector3d xAxis;
    ArxDbgUtils::getEcsXAxis(m_zDir, xAxis);	// get AutoCAD's arbitrary X-Axis

    m_xDir = xAxis.rotateBy(rot, m_zDir);		// factor in rotation angle
    m_xDir.normalize();

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDbEntity::normal
**
**  **jma
**
*************************************/

AcGeVector3d
ArxDbgDbEntity::normal() const
{
    assertReadEnabled();
    ASSERT(m_zDir.isUnitLength());

    return m_zDir;
}

/****************************************************************************
**
**  ArxDbgDbEntity::setNormal
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDbEntity::setNormal(const AcGeVector3d& nvec)
{
    if (nvec.isZeroLength()) {
        ASSERT(0);
        return Acad::eInvalidInput;
    }

    if (nvec != m_zDir) {
        assertWriteEnabled();

        AcGeVector3d txdir, tydir;
        AcGeVector3d txdiro, tydiro;

        ArxDbgUtils::getEcsXAxis(nvec, txdir);       // get AutoCAD's arbitrary X-Axis for this normal
        ArxDbgUtils::getEcsXAxis(m_zDir, txdiro);    // get AutoCAD's arbitrary X-Axis for this normal

        tydir = nvec.crossProduct(txdir);
        tydir.normalize();

        tydiro = m_zDir.crossProduct(txdiro);
        tydiro.normalize();

        AcGeMatrix3d mat;
        mat.setToAlignCoordSys(m_origin, txdiro, tydiro, m_zDir,
                               m_origin, txdir,  tydir,  nvec);

        m_xDir.transformBy(mat);
        m_zDir.transformBy(mat);
        m_origin.transformBy(mat);
    }

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDbEntity::dwgInFields
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDbEntity::dwgInFields(AcDbDwgFiler* filer)
{
	if (ArxDbgOptions::m_instance.m_showDwgFilerMessages) {
		CString str, str2;
		acutPrintf(_T("\n%s <DwgIn  : %s>"), ArxDbgUtils::objToClassAndHandleStr(this, str),
				ArxDbgUtils::filerTypeToStr(filer->filerType(), str2));
	}

    Acad::ErrorStatus es;
    if ((es = AcDbEntity::dwgInFields(filer)) != Acad::eOk)
        return es;

    Adesk::Int16 version;
    filer->readItem(&version);
    if (version > m_version)
        return Acad::eMakeMeProxy;

    filer->readItem(&m_origin);
    filer->readItem(&m_xDir);
    filer->readItem(&m_zDir);

    return filer->filerStatus();
}

/****************************************************************************
**
**  ArxDbgDbEntity::dwgOutFields
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDbEntity::dwgOutFields(AcDbDwgFiler* filer) const
{
	if (ArxDbgOptions::m_instance.m_showDwgFilerMessages) {
		CString str, str2;
		acutPrintf(_T("\n%s <DwgOut : %s>"),
				ArxDbgUtils::objToClassAndHandleStr(const_cast<ArxDbgDbEntity*>(this), str),
				ArxDbgUtils::filerTypeToStr(filer->filerType(), str2));
	}

    Acad::ErrorStatus es;
    if ((es = AcDbEntity::dwgOutFields(filer)) != Acad::eOk)
        return es;

    filer->writeItem(m_version);

    filer->writeItem(m_origin);
    filer->writeItem(m_xDir);
    filer->writeItem(m_zDir);

    return filer->filerStatus();
}

/****************************************************************************
**
**  ArxDbgDbEntity::dxfInFields
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDbEntity::dxfInFields(AcDbDxfFiler* filer)
{
    Acad::ErrorStatus es;
    if (((es = AcDbEntity::dxfInFields(filer)) != Acad::eOk) ||
        (filer->atSubclassData(this->desc()->name()) != Adesk::kTrue))
        return filer->filerStatus();

	resbuf rb;
    while ((es == Acad::eOk) && ((es = filer->readResBuf(&rb)) == Acad::eOk)) {
        if (rb.restype == kDxfLocation) {
            m_origin.set(rb.resval.rpoint[X], rb.resval.rpoint[Y], rb.resval.rpoint[Z]);
        }
        else if (rb.restype == kDxfDirection) {
            m_xDir.set(rb.resval.rpoint[X], rb.resval.rpoint[Y], rb.resval.rpoint[Z]);
        }
        else if (rb.restype == kDxfNormal) {
            m_zDir.set(rb.resval.rpoint[X], rb.resval.rpoint[Y], rb.resval.rpoint[Z]);
        }
        else {
            filer->pushBackItem();
            es = Acad::eEndOfFile;
        }
    }

	// TBD: really need to do some orthogonality checking on the vectors since
	// someone could input bad data... but for now we will take it on faith.

    if (es != Acad::eEndOfFile)
        return Acad::eInvalidResBuf;

    return filer->filerStatus();
}

/****************************************************************************
**
**  ArxDbgDbEntity::dxfOutFields
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDbEntity::dxfOutFields(AcDbDxfFiler* filer) const
{
    Acad::ErrorStatus es;
    if ((es = AcDbEntity::dxfOutFields(filer)) != Acad::eOk)
        return es;

    filer->writeItem(AcDb::kDxfSubclass, this->desc()->name());
	
	filer->writeItem(kDxfLocation, m_origin);
	filer->writeItem(kDxfDirection, m_xDir);
	filer->writeItem(kDxfNormal, m_zDir);

    return filer->filerStatus();
}

/****************************************************************************
**
**  ArxDbgDbEntity::getCloneReferences
**
**  **jma
**
*************************************/

void
ArxDbgDbEntity::getCloneReferences(AcDb::DeepCloneType type,
								AcDbObjectIdArray& objIds,
								AcDbIntArray& refTypes) const
{
	// do nothing at this level
}

/****************************************************************************
**
**  ArxDbgDbEntity::verifyReferences
**      this is called after a BLOCK operation to make sure that everything got
**  cloned over successfully.  If not, then any dangling references are removed
**  or set to NULL.
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDbEntity::verifyReferences(int& fixedErrorCount, bool fullCheck)
{
	return Acad::eOk;	// nothing to verify at this level
}

/****************************************************************************
**
**  ArxDbgDbEntity::deepClone
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDbEntity::subDeepClone(AcDbObject* pOwner,
              AcDbObject*& pClonedObject,
              AcDbIdMapping& idMap,
              Adesk::Boolean isPrimary) const
{
        // You should always pass back pClonedObject == NULL
        // if, for any reason, you do not actually clone it
        // during this call.  The caller should pass it in
        // as NULL, but to be safe, we set it here as well.
    pClonedObject = NULL;

	if (ArxDbgOptions::m_instance.m_showDeepCloneDetails) {
		CString titleStr, tmpStr;
		titleStr.Format(_T("Beginning -- deepClone: %s"),
				ArxDbgUtils::objToClassAndHandleStr(const_cast<ArxDbgDbEntity*>(this), tmpStr));
		ArxDbgUiTdmIdMap dbox(&idMap, acedGetAcadDwgView(), titleStr);
		dbox.DoModal();
	}

    AcDb::DeepCloneType type = idMap.deepCloneContext();

        // if we know everything will be cloned for us, just let
		// the base class do everything for us.
    if ((type == AcDb::kDcInsert) ||
		(type == AcDb::kDcInsertCopy) ||
		(type == AcDb::kDcExplode))
        return AcDbEntity::subDeepClone(pOwner, pClonedObject, idMap, isPrimary);

        // following case happens when doing a AcDbDatabase::deepCloneObjects()
        // and the owner happens to be the same... then its really like a
        // kDcCopy, otherwise deepCloneObjects() is like a kDcBlock
    if (type == AcDb::kDcObjects) {
		if (ownerId() == pOwner->objectId())
			type = AcDb::kDcCopy;
		else
			type = AcDb::kDcBlock;
	}

		// now ask derived classes what references they want cloned for them
	AcDbObjectIdArray refEntIds;
	AcDbIntArray refTypes;
	getCloneReferences(type, refEntIds, refTypes);
	ASSERT(refEntIds.length() == refTypes.length());

		// if derived class doesn't have any references to take care of, then
		// we will just let the AcDbEntity::deepClone() take care of things.
	if (refEntIds.isEmpty())
		return AcDbEntity::subDeepClone(pOwner, pClonedObject, idMap, isPrimary);

        // If this object is in the idMap and is already
        // cloned, then return.
	bool tmpIsPrimary = isPrimary ? true : false;	// get around compiler performance warning
    AcDbIdPair idPair(objectId(), AcDbObjectId::kNull, false, tmpIsPrimary);
    if (idMap.compute(idPair) && (idPair.value() != NULL))
        return Acad::eOk;

    // STEP 1:
    // Create the clone
    //
    AcDbObject *pClone = (AcDbObject*)isA()->create();
    if (pClone != NULL)
        pClonedObject = pClone;    // set the return value
    else
        return Acad::eOutOfMemory;

    // STEP 2:
    // Append the clone to its new owner.  In this example,
    // we know that we are derived from AcDbEntity, so we
    // can expect our owner to be an AcDbBlockTableRecord,
    // unless we have set up an ownership relationship with
    // another of our objects.  In that case, we need to
    // establish how we connect to that owner in our own
    // way.  This sample shows a generic method using
    // setOwnerId().
    //
    AcDbBlockTableRecord *pBTR = AcDbBlockTableRecord::cast(pOwner);
    if (pBTR != NULL) {
        AcDbEntity* ent = AcDbEntity::cast(pClone);
        pBTR->appendAcDbEntity(ent);
    }
    else {
        if (isPrimary)
            return Acad::eInvalidOwnerObject;

        // Some form of this code is only necessary if
        // anyone has set up an ownership for our object
        // other than with an AcDbBlockTableRecord.
        //
        pOwner->database()->addAcDbObject(pClone);
        pClone->setOwnerId(pOwner->objectId());
    }

    // STEP 3:
    // Now we copy our contents to the clone.  This is done
    // using an AcDbDeepCloneFiler.  This filer keeps a
    // list of all AcDbHardOwnershipIds and
    // AcDbSoftOwnershipIds we, and any classes we derive
    // from,  have.  This list is then used to know what
    // additional, "owned" objects need to be cloned below.
    //
    AcDbDeepCloneFiler filer;
    dwgOut(&filer);

    // STEP 4:
    // Rewind the filer and read the data into the clone.

    //
    filer.seek(0L, AcDb::kSeekFromStart);
    pClone->dwgIn(&filer);

    // STEP 5:
    // This must be called for all newly created objects
    // in deepClone.  It is turned off by endDeepClone()
    // after it has translated the references to their
    // new values.
    //
    pClone->setAcDbObjectIdsInFlux();

    // STEP 6:
    // Add the new information to the idMap.  We can use
    // the idPair started above.
    //
    idPair.setValue(pClonedObject->objectId());
    idPair.setIsCloned(Adesk::kTrue);
    idMap.assign(idPair);

    // STEP 7:
    // Using the filer list created above, find and clone
    // any owned objects.
    //
    AcDbObject *pSubObject;
    AcDbObject *pClonedSubObject;
    AcDbObjectId id;
    Acad::ErrorStatus es;
    while (filer.getNextOwnedObject(id)) {
            // Open the object and clone it.  Note that we now
            // set "isPrimary" to kFalse here because the object
            // is being cloned, not as part of the primary set,
            // but because it is owned by something in the
            // primary set.
        es = acdbOpenAcDbObject(pSubObject, id, AcDb::kForRead);
        if (es != Acad::eOk)
            continue;   // could have been NULL or erased

        pClonedSubObject = NULL;
        pSubObject->deepClone(pClonedObject, pClonedSubObject, idMap, Adesk::kFalse);

            // If this is a kDcInsert context, the objects
            // may be "cheapCloned".  In this case, they are
            // "moved" instead of cloned.  The result is that
            // pSubObject and pClonedSubObject will point to
            // the same object.  So, we only want to close
            // pSubObject if it really is a different object
            // than its clone.
        if (pSubObject != pClonedSubObject)
            pSubObject->close();

            // The pSubObject may either already have been
            // cloned, or for some reason has chosen not to be
            // cloned.  In that case, the returned pointer will
            // be NULL.  Otherwise, since we have no immediate
            // use for it now, we can close the clone.
        if (pClonedSubObject != NULL)
            pClonedSubObject->close();
    }

        // clone the referenced entities
    AcDbObject* ent;
	int len = refEntIds.length();
	for (int i=0; i<len; i++) {
		if (refTypes[i] == kClone) {
			es = acdbOpenAcDbObject(ent, refEntIds[i], AcDb::kForRead);
			if (es == Acad::eOk) {
				pClonedSubObject = NULL;
				es = ent->deepClone(pOwner, pClonedSubObject, idMap, Adesk::kTrue);
				if (es == Acad::eOk) {
						// see comment above about cheap clone
					if (ent != pClonedSubObject)
						ent->close();

					if (pClonedSubObject != NULL)
						pClonedSubObject->close();
				}
			}
		}
			// this case is needed for RefEdit so we can pass its validation
			// test when editing a blockReference.  We don't actually clone it
			// but we add it to the map so it thinks it got cloned and is therefore
			// a valid "Closed Set" of objects.
		else if (refTypes[i] == kFakeClone) {
            AcDbIdPair idPair(refEntIds[i], refEntIds[i], false, false, true);
            idMap.assign(idPair);
		}
	}

	if (ArxDbgOptions::m_instance.m_showDeepCloneDetails) {
		CString titleStr, tmpStr;
		titleStr.Format(_T("End -- deepClone: %s"),
				ArxDbgUtils::objToClassAndHandleStr(const_cast<ArxDbgDbEntity*>(this), tmpStr));
		ArxDbgUiTdmIdMap dbox(&idMap, acedGetAcadDwgView(), titleStr);
		dbox.DoModal();
	}

        // Leave pClonedObject open for the caller
    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDbEntity::wblockClone
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDbEntity::subWblockClone(AcRxObject* pOwner, AcDbObject*& pClone,
                    AcDbIdMapping& idMap, Adesk::Boolean isPrimary) const
{
	if (ArxDbgOptions::m_instance.m_showWblockCloneDetails) {
		CString titleStr, tmpStr;
		titleStr.Format(_T("Beginning -- wblockClone: %s"),
				ArxDbgUtils::objToClassAndHandleStr(const_cast<ArxDbgDbEntity*>(this), tmpStr));
		ArxDbgUiTdmIdMap dbox(&idMap, acedGetAcadDwgView(), titleStr);
		dbox.DoModal();
	}

    AcDb::DeepCloneType type = idMap.deepCloneContext();

        // if xrefInsert or xrefBind, we know everything will
        // be cloned, so just let normal routine handle this
    if ((type == AcDb::kDcXrefBind) || (type == AcDb::kDcXrefInsert)) {
        return AcDbEntity::subWblockClone(pOwner, pClone, idMap, isPrimary);
    }
		// if we've already been cloned, just return
	AcDbIdPair idPair(objectId(), AcDbObjectId::kNull, true);
    if (idMap.compute(idPair) && (idPair.value() != AcDbObjectId::kNull)) {
        return Acad::eOk;
    }

        // If isPrimary is kTrue, then override the default cloning
        // within our own cloning, which would set it to kFalse,
        // by cloning our referenced entity first.
    if (isPrimary) {
			// now ask derived classes what references they want cloned for them
		AcDbObjectIdArray refEntIds;
		AcDbIntArray refTypes;
		getCloneReferences(type, refEntIds, refTypes);

		ASSERT(refEntIds.length() == refTypes.length());

            // clone each entity we reference first and change the value
            // of isPrimary to fake it out.  Since we clone these first,
            // when the normal wblockClone is called, it will see that
            // they are already in the set of cloned objects and will not
            // try to clone it again.
        AcDbEntity* ent;
        Acad::ErrorStatus es;
		int len = refEntIds.length();
		for (int i=0; i<len; i++) {
			if (refTypes[i] == kClone) {
				es = acdbOpenAcDbEntity(ent, refEntIds[i], AcDb::kForRead);
				if (es == Acad::eOk) {
						// this method only works if they come from the same block
						// (which SHOULD always be the case!)
					if (blockId() == ent->blockId()) {
							// Use the same owner, and pass in the same isPrimary value
						AcDbObject* pSubClone = NULL;
						es = ent->wblockClone(pOwner, pSubClone, idMap, Adesk::kTrue);
						if (pSubClone != NULL)
							pSubClone->close();

						if (es != Acad::eOk) {
							ASSERT(0);
						}
					}
					else {
						ASSERT(0);
					}

					ent->close();
				}
			}
		}
    }
        // Now we can clone ourselves via calling our parent's method.
	Acad::ErrorStatus es =  AcDbEntity::subWblockClone(pOwner, pClone, idMap, isPrimary);

	if (ArxDbgOptions::m_instance.m_showWblockCloneDetails) {
		CString titleStr, tmpStr;
		titleStr.Format(_T("End -- wblockClone: %s"),
				ArxDbgUtils::objToClassAndHandleStr(const_cast<ArxDbgDbEntity*>(this), tmpStr));
		ArxDbgUiTdmIdMap dbox(&idMap, acedGetAcadDwgView(), titleStr);
		dbox.DoModal();
	}

	return es;
}

/****************************************************************************
**
**  ArxDbgDbEntity::transformBy
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDbEntity::subTransformBy(const AcGeMatrix3d& xform)
{
    assertWriteEnabled();
    
    m_origin.transformBy(xform);
    m_xDir.transformBy(xform);
    m_zDir.transformBy(xform);

    m_xDir.normalize();
    m_zDir.normalize();

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDbEntity::getEcs
**
**  **jma
**
*************************************/

void
ArxDbgDbEntity::getEcs(AcGeMatrix3d& retVal) const
{
    AcGeVector3d yDir = m_zDir.crossProduct(m_xDir);

    retVal.setCoordSystem(m_origin, m_xDir, yDir.normal(), m_zDir);
}

/****************************************************************************
**
**  ArxDbgDbEntity::getGripPoints
**      we use the logo's insertion point as the only grip point.
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDbEntity::subGetGripPoints(AcGePoint3dArray& gripPoints,
				               AcDbIntArray& osnapModes,
				               AcDbIntArray& geomIds) const
{
    gripPoints.append(m_origin);

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDbAdeskLogo::moveGripPointsAt
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDbEntity::subMoveGripPointsAt(const AcDbIntArray& indices, const AcGeVector3d& offset)
{
    if (offset.isZeroLength() == Adesk::kTrue)
        return Acad::eInvalidOffset;

    if (indices.length() == 1) {
        if (indices[0] == 0) {
            setLocation(m_origin + offset);
            return Acad::eOk;
        }
    }

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDbEntity::list
**
**  **jma
**
*************************************/

void
ArxDbgDbEntity::subList() const
{
	AcDbEntity::subList();

	CString str;

	printForListCmd(_T("Location"), ArxDbgUtils::ptToStr(location(), str));
	printForListCmd(_T("Rotation"), ArxDbgUtils::angleToStr(rotation(), str));
	printForListCmd(_T("Normal"),   ArxDbgUtils::vectorToStr(normal(), str));
}

/****************************************************************************
**
**  ArxDbgDbEntity::printForListCmd
**
**  **jma
**
*************************************/

void
ArxDbgDbEntity::printForListCmd(LPCTSTR label, LPCTSTR value) const
{
	if (label == NULL)
		acutPrintf(_T("\n%20s"), _T(""));
	else
		acutPrintf(_T("\n%20s"), label);
	
	if (value != NULL)
		acutPrintf(_T(" : %s"), value);
}