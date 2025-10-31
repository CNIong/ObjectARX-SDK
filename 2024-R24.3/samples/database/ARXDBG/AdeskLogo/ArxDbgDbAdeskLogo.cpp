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

#include "ArxDbgDbAdeskLogo.h"
#include "ArxDbgDbAdeskLogoStyle.h"
#include "ArxDbgUtils.h"
#include "SdSysVar.h"



Adesk::Int16     ArxDbgDbAdeskLogo::m_version = 0;     // MDI safe

ACRX_DXF_DEFINE_MEMBERS(ArxDbgDbAdeskLogo, ArxDbgDbEntity,
						AcDb::kDHL_1015, AcDb::kMRelease0,
						0, ARXDBG_ADESK_LOGO, ArxDbg)

/****************************************************************************
**
**  ArxDbgArxDbgDbArxDbgDbAdeskLogo::ArxDbgDbAdeskLogo
**
**  **jma
**
*************************************/

ArxDbgDbAdeskLogo::ArxDbgDbAdeskLogo()
{
    m_tmpMtext = NULL;
	// logoStyleId and scale already initialized correctly by their constructors
}

/****************************************************************************
**
**  ArxDbgDbAdeskLogo::~ArxDbgDbAdeskLogo
**
**  **jma
**
*************************************/

ArxDbgDbAdeskLogo::~ArxDbgDbAdeskLogo()
{
	if(NULL != m_tmpMtext)
		delete m_tmpMtext;
}

/****************************************************************************
**
**  ArxDbgDbAdeskLogo::scale
**      just return the current scale of the logo.
**
**  **jma
**
*************************************/

AcGeScale3d
ArxDbgDbAdeskLogo::scale() const
{
    assertReadEnabled();
    return m_scale;
}

/****************************************************************************
**
**  ArxDbgDbAdeskLogo::setScale
**      Set the new scale of the object.
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDbAdeskLogo::setScale(const AcGeScale3d& newScale)
{
    if (newScale != m_scale) {  // don't force notifications if nothing has changed
        assertWriteEnabled();
        m_scale = newScale;
    }

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDbAdeskLogo::logoStyleId
**      Returns the object id for the style that we reference
**
**  **jma
**
*************************************/

AcDbObjectId
ArxDbgDbAdeskLogo::logoStyleId() const
{
    assertReadEnabled();
    return m_logoStyleId;
}

/****************************************************************************
**
**  ArxDbgDbAdeskLogo::setLogoStyleId
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDbAdeskLogo::setLogoStyleId(const AcDbObjectId& styleId)
{
    if (styleId == AcDbObjectId::kNull)
        return Acad::eNullObjectId;

    if (styleId != m_logoStyleId) {  // don't force notifications if nothing has changed
        assertWriteEnabled();
        m_logoStyleId = styleId;
    }

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDbAdeskLogo::arbitraryReferenceId
**
**  **jma
**
*************************************/

AcDbObjectId
ArxDbgDbAdeskLogo::arbitraryReferenceId() const
{
    assertReadEnabled();
    return m_arbitraryRefEnt;
}

/****************************************************************************
**
**  ArxDbgDbAdeskLogo::setArbitraryReferenceId
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDbAdeskLogo::setArbitraryReferenceId(const AcDbObjectId& refEntId)
{
    if (refEntId == AcDbObjectId::kNull)
        return Acad::eNullObjectId;

    if (refEntId != m_arbitraryRefEnt) {  // don't force notifications if nothing has changed
        assertWriteEnabled();
        m_arbitraryRefEnt = refEntId;
    }

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDbAdeskLogo::getCloneReferences
**		implementing this function allows our base class to handle all deepClone
**	and wblockClone requests for us.  All we have to do here is tell it what
**	kind of behavior we want and it will do the rest.  Since we have only a few
**	derived classes, we could have easily just overridden these functions ourselves,
**	but in a much larger system with lots of custom objects, it becomes unmaintainable
**	to do it that way.
**
**  **jma
**
*************************************/

void
ArxDbgDbAdeskLogo::getCloneReferences(AcDb::DeepCloneType type,
								AcDbObjectIdArray& refIds,
								AcDbIntArray& refTypes) const
{
		// these types should have been filtered out.  NOTE that kDcObjects
		// is usually ambiguous and has been mapped to kDcBlock or kDcCopy.
	ASSERT((type != AcDb::kDcExplode) &&
		   (type != AcDb::kDcInsert) &&
		   (type != AcDb::kDcInsertCopy) &&
		   (type != AcDb::kDcSymTableMerge) &&
		   (type != AcDb::kDcXrefBind) &&
		   (type != AcDb::kDcXrefInsert) &&
		   (type != AcDb::kDcObjects));

	if (type == AcDb::kDcCopy) {
		refIds.append(m_arbitraryRefEnt);
		refTypes.append(kClone);	// you could set this to kNoClone and both would point to the same one.
	}
	else if (type == AcDb::kDcBlock) {
		refIds.append(m_arbitraryRefEnt);
		refTypes.append(kClone);

			// LongTransactions (RefEdit) will not allow our object to be checked
			// out from a block definition unless its accompanying style def is
			// also in the check out set (which it won't be by default).  So, we
			// have to tell ::deepClone() to fake like it cloned the style definition
			// so it will pass LongTransaction's checkOut validation.
		refIds.append(m_logoStyleId);
		refTypes.append(kFakeClone);
	}
	else if (type == AcDb::kDcWblock) {
		refIds.append(m_arbitraryRefEnt);
		refTypes.append(kClone);
	}
	else if (type == AcDb::kDcWblkObjects) {
		refIds.append(m_arbitraryRefEnt);
		refTypes.append(kClone);
	}
	else {
		ASSERT(0);	// which context did we not account for?
	}
}

/****************************************************************************
**
**  ArxDbgDbAdeskLogo::verifyReferences
**      this is called after a BLOCK operation to make sure that everything got
**  cloned over successfully.  If not, then any dangling references are removed
**  or set to NULL.
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDbAdeskLogo::verifyReferences(int& fixedErrorCount, bool fullCheck)
{
    Acad::ErrorStatus es = ArxDbgDbEntity::verifyReferences(fixedErrorCount, fullCheck);
    if (es != Acad::eOk)
        return es;

        // if not doing a full check we only check for Null Ids.  Since NULL
        // is OK for us, just return because there is nothing that we can verify
    if (fullCheck == false)
        return Acad::eOk;

        // set to NULL if this didn't get verified
    es = ArxDbgUtils::verifyEntityReference(this, m_arbitraryRefEnt, NULL, true, false);
    if (es != Acad::eOk) {
			// print this out just for educational purposes.
		acutPrintf(_T("\nArxDbgDbAdeskLogo: severed stale reference"));

        if (setArbitraryReferenceId(AcDbObjectId::kNull) == Acad::eOk)
            fixedErrorCount++;
    }

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDbAdeskLogo::dwgInFields
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDbAdeskLogo::dwgInFields(AcDbDwgFiler* filer)
{
    Acad::ErrorStatus es;
    if ((es = ArxDbgDbEntity::dwgInFields(filer)) != Acad::eOk)
        return es;

    Adesk::Int16 version;
    filer->readItem(&version);
    if (version > m_version)
        return Acad::eMakeMeProxy;

    filer->readItem(&m_logoStyleId);
    filer->readItem(&m_scale);
    filer->readItem(&m_arbitraryRefEnt);

    return filer->filerStatus();
}

/****************************************************************************
**
**  ArxDbgDbAdeskLogo::dwgOutFields
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDbAdeskLogo::dwgOutFields(AcDbDwgFiler* filer) const
{
    Acad::ErrorStatus es;
    if ((es = ArxDbgDbEntity::dwgOutFields(filer)) != Acad::eOk)
        return es;

    filer->writeItem(m_version);

    filer->writeItem(m_logoStyleId);
    filer->writeItem(m_scale);

		// if the thing we were referencing is erased, don't
		// allow that to propagate to new copies of the entity.
	if (filer->filerType() == AcDb::kDeepCloneFiler) {
			// TBD: can't call isErased() on null object (actually, I think this
			// has been fixed now)
		if ((m_arbitraryRefEnt.isNull() == false) && m_arbitraryRefEnt.isErased())
			filer->writeHardPointerId(AcDbObjectId::kNull);
		else
			filer->writeItem(m_arbitraryRefEnt);
	}
	else
		filer->writeItem(m_arbitraryRefEnt);

    return filer->filerStatus();
}

/****************************************************************************
**
**  ArxDbgDbAdeskLogo::dxfInFields
**      The general strategy for DXF is to scan for the matching dxf code and
**  then call the regular API "set" function to perform the necessary error
**  checking since DXF is just a text file and could contain out of range data.
**  Currently, we don't do any error reporting, we just skip the value and move
**  on using whatever default value we had.
**
**  NOTE: during DXFIN, you will be passed objectIds (as is the case with the
**  hardPointerId to the logoStyle), that are not yet valid Ids, so there is
**  no way to verify that it is an object of the correct type.  You just have
**  to take it on blind faith that it will be a good Id after a second pass is
**  made to fix up the references.  If its not a good Id, the only way to catch
**  it is on an AUDIT operation.
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDbAdeskLogo::dxfInFields(AcDbDxfFiler* filer)
{
    Acad::ErrorStatus es;
    if (((es = ArxDbgDbEntity::dxfInFields(filer)) != Acad::eOk) ||
        (filer->atSubclassData(this->desc()->name()) != Adesk::kTrue))
        return filer->filerStatus();

    resbuf rb;

    while ((es == Acad::eOk) && ((es = filer->readResBuf(&rb)) == Acad::eOk)) {
        if (rb.restype == kDxfLogoStyleId) {
            AcDbObjectId id;
            id.setFromOldId(rb.resval.mnLongPtr);
            setLogoStyleId(id);
        }
        else if (rb.restype == kDxfArbitraryRefId) {
            AcDbObjectId id;
            id.setFromOldId(rb.resval.mnLongPtr);
            setArbitraryReferenceId(id);
        }
        else if (rb.restype == kDxfScale) {
            AcGeScale3d tmpScale(rb.resval.rpoint[X], rb.resval.rpoint[Y], rb.resval.rpoint[Z]);
            setScale(tmpScale);
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
**  ArxDbgDbAdeskLogo::dxfOutFields
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDbAdeskLogo::dxfOutFields(AcDbDxfFiler* filer) const
{
    Acad::ErrorStatus es;
    if ((es = ArxDbgDbEntity::dxfOutFields(filer)) != Acad::eOk)
        return es;

    filer->writeItem(AcDb::kDxfSubclass, this->desc()->name());

    filer->writeItem(kDxfLogoStyleId, m_logoStyleId);
    filer->writeItem(kDxfArbitraryRefId, m_arbitraryRefEnt);
    filer->writeItem(kDxfScale, m_scale);

    return filer->filerStatus();
}

/****************************************************************************
**
**  ArxDbgDbAdeskLogo::subWorldDraw
**
**  **jma
**
*************************************/

Adesk::Boolean
ArxDbgDbAdeskLogo::subWorldDraw(AcGiWorldDraw* worldDraw)
{
    if (worldDraw->regenAbort())
        return Adesk::kTrue;

    if (worldDraw->regenType() == kAcGiSaveWorldDrawForProxy) {
		commonDraw(worldDraw);
        return Adesk::kTrue;
	}

    return Adesk::kFalse;   // force viewportDraw() to be called always
}

/****************************************************************************
**
**  ArxDbgDbAdeskLogo::subViewportDraw
**
**  **jma
**
*************************************/

void
ArxDbgDbAdeskLogo::subViewportDraw(AcGiViewportDraw* vportDraw)
{
	commonDraw(vportDraw);
}

/****************************************************************************
**
**  ArxDbgDbAdeskLogo::commonDraw
**
**  **jma
**
*************************************/

void
ArxDbgDbAdeskLogo::commonDraw(AcGiCommonDraw* drawContext)
{
    if (drawContext->regenAbort())
        return;

    AcGeMatrix3d scaleMat;
    m_scale.getMatrix(scaleMat);

    AcGeMatrix3d mat;
    getEcs(mat);   // push ECS of this Logo
    mat *= scaleMat;

    drawContext->rawGeometry()->pushModelTransform(mat);

    ArxDbgDbAdeskLogoStyle* lStyle = NULL;
    Acad::ErrorStatus es = acdbOpenObject(lStyle, m_logoStyleId, AcDb::kForRead);

    drawLogo(drawContext, lStyle);
    drawLabel(drawContext, lStyle);
    drawBorder(drawContext, lStyle);

    if (es == Acad::eOk)
        lStyle->close();

    drawContext->rawGeometry()->popModelTransform();

	drawRefLine(drawContext);
}

/****************************************************************************
**
**  ArxDbgDbAdeskLogo::drawSingleCaliper
**      the Autodesk logo has 3 calipers of various size.  Given an array
**  of 5 points, draw them as 2D polyline here in the base class.  Derived
**  classes can choose to override and draw however they want.
**
**  **jma
**
*************************************/

void
ArxDbgDbAdeskLogo::drawSingleCaliper(AcGiCommonDraw* drawContext, AcGePoint3d* pts,
                                   ArxDbgDbAdeskLogoStyle* lStyle)
{
	AcGeVector3d viewDir;
	AcGiViewportDraw* vportDraw = AcGiViewportDraw::cast(drawContext);
	if (vportDraw)
		viewDir = vportDraw->viewport().viewDir();
	else {
			// cheat and get viewdir for current viewport from the system variable
		AcGePoint3d tmpPt;
		getSysVar(_T("viewdir"), tmpPt);
		viewDir = tmpPt.asVector();
	}

    if (viewDir == AcGeVector3d::kZAxis) {
            // if solid fill is on we have to save the current state
            // first and then restore it.  If we don't, then if we 
            // are drawn as part of some other entity, we'll mess it up
            // for them.
        if (lStyle && (lStyle->isSolidFill()) && (drawContext->isDragging() == Adesk::kFalse)) {
            AcGiFillType savedFillType = drawContext->subEntityTraits().fillType();
            drawContext->subEntityTraits().setFillType(kAcGiFillAlways);
            drawContext->rawGeometry()->polygon(5, pts);
            drawContext->subEntityTraits().setFillType(savedFillType);
        }
        else {
            drawContext->rawGeometry()->polygon(5, pts);
        }
    }
    else {
        AcGePoint3d allPts[10];
        allPts[0] = pts[0];
        allPts[1] = pts[1];
        allPts[2] = pts[2];
        allPts[3] = pts[3];
        allPts[4] = pts[4];

        allPts[5].set(pts[0].x, pts[0].y, 1.0);
        allPts[6].set(pts[1].x, pts[1].y, 1.0);
        allPts[7].set(pts[2].x, pts[2].y, 1.0);
        allPts[8].set(pts[3].x, pts[3].y, 1.0);
        allPts[9].set(pts[4].x, pts[4].y, 1.0);

        Adesk::Int32 faceList[37];

            // bottom face
        faceList[0]  = 5;   // number of vertices
        faceList[1]  = 0;
        faceList[2]  = 1;
        faceList[3]  = 2;
        faceList[4]  = 3;
        faceList[5]  = 4;

            // top face
        faceList[6]  = 5;   // number of vertices
        faceList[7]  = 5;
        faceList[8]  = 6;
        faceList[9]  = 7;
        faceList[10] = 8;
        faceList[11] = 9;

            // inside left face
        faceList[12] = 4;   // number of vertices
        faceList[13] = 0;
        faceList[14] = 1;
        faceList[15] = 6;
        faceList[16] = 5;

            // inside right face
        faceList[17] = 4;   // number of vertices
        faceList[18] = 1;
        faceList[19] = 2;
        faceList[20] = 7;
        faceList[21] = 6;

            // outside right face
        faceList[22] = 4;   // number of vertices
        faceList[23] = 2;
        faceList[24] = 3;
        faceList[25] = 8;
        faceList[26] = 7;

            // outside top face
        faceList[27] = 4;   // number of vertices
        faceList[28] = 3;
        faceList[29] = 4;
        faceList[30] = 9;
        faceList[31] = 8;

            // outside left face
        faceList[32] = 4;   // number of vertices
        faceList[33] = 4;
        faceList[34] = 0;
        faceList[35] = 5;
        faceList[36] = 9;

        drawContext->rawGeometry()->shell(10, allPts, 37, faceList);
    }
}

/****************************************************************************
**
**  ArxDbgDbAdeskLogo::drawLogo
**
**  **jma
**
*************************************/

void
ArxDbgDbAdeskLogo::drawLogo(AcGiCommonDraw* drawContext, ArxDbgDbAdeskLogoStyle* lStyle)
{
    AcGePoint3d pts[5];

        // NOTE: we can just hardwire these points around the origin in
        // a 1 x 1 unit block scheme because our ECS data from the ArxDbgDbEntity
        // class takes care of our actual position in space.  That matrix,
        // along with the scale of the Logo has already been pushed into
        // the stream.  All subsequent data we push in will be transformed
        // to the correct location and size.

        // draw first caliper
    pts[0].set(0.1194, 0.0,    0.0);
    pts[1].set(0.5,    0.4057, 0.0);
    pts[2].set(0.8806, 0.0,    0.0);
    pts[3].set(0.5391, 0.4958, 0.0);
    pts[4].set(0.4609, 0.4958, 0.0);
    drawSingleCaliper(drawContext, pts, lStyle);

        // draw second caliper
    pts[0].set(0.0582, 0.0,    0.0);
    pts[1].set(0.5,    0.6299, 0.0);
    pts[2].set(0.9418, 0.0,    0.0);
    pts[3].set(0.5391, 0.7267, 0.0);
    pts[4].set(0.4609, 0.7267, 0.0);
    drawSingleCaliper(drawContext, pts, lStyle);

        // draw third caliper
    pts[0].set(0.0,    0.0,    0.0);
    pts[1].set(0.5,    0.8779, 0.0);
    pts[2].set(1.0,    0.0,    0.0);
    pts[3].set(0.5391, 1.0,    0.0);
    pts[4].set(0.4609, 1.0,    0.0);
    drawSingleCaliper(drawContext, pts, lStyle);
}

/****************************************************************************
**
**  ArxDbgDbAdeskLogo::drawLabel
**
**  **jma
**
*************************************/

void
ArxDbgDbAdeskLogo::drawLabel(AcGiCommonDraw* drawContext, ArxDbgDbAdeskLogoStyle* lStyle)
{
    if (drawContext->isDragging())	// don't draw text when dragging, slow proformance
        return;

    CString labelStr;
    if (lStyle)
        labelStr = lStyle->label();

        // short circut if label is Nullstr
    if (labelStr.IsEmpty())
        return;

    // we use an in-memory Mtext object to do the dirty work of writing out
    // the text since it is extremely hard to write text with the AcGi::text()
    // signatures.  This in-memory Mtext object is kept as a member of the class
	// and destroyed either here, since the context is recreated or at the
	// destructor of the class.

	if(NULL != m_tmpMtext)// prevent the memory leak...
		delete m_tmpMtext;

	m_tmpMtext = new AcDbMText;
    m_tmpMtext->setLocation(AcGePoint3d(1.25, 0.0, 0.0)); // set to be just to the right of the logo
    m_tmpMtext->setTextHeight(1.0);                       // unit-block concept where scaling will adjust height
    m_tmpMtext->setWidth(0.0);
    m_tmpMtext->setContents(labelStr);
    m_tmpMtext->setAttachment(AcDbMText::kBottomLeft);

    AcDbDatabase* db = database();
    if (db == NULL)
        db = acdbHostApplicationServices()->workingDatabase();

    m_tmpMtext->setDatabaseDefaults(db);

    if (lStyle && (lStyle->textStyleId() != AcDbObjectId::kNull))
        m_tmpMtext->setTextStyle(lStyle->textStyleId());

    drawContext->rawGeometry()->draw(m_tmpMtext);
}

/****************************************************************************
**
**  ArxDbgDbAdeskLogo::drawBorder
**
**  **jma
**
*************************************/

void
ArxDbgDbAdeskLogo::drawBorder(AcGiCommonDraw* drawContext, ArxDbgDbAdeskLogoStyle* lStyle)
{
    AcGePoint3d pts[5];

        // stream out the border around the logo
    pts[0].set(0.0, 0.0, 0.0);
    pts[1].set(1.0, 0.0, 0.0);
    pts[2].set(1.0, 1.0, 0.0);
    pts[3].set(0.0, 1.0, 0.0);
    pts[4].set(0.0, 0.0, 0.0);

    drawContext->rawGeometry()->polyline(5, pts);
}

/****************************************************************************
**
**  ArxDbgDbAdeskLogo::drawRefLine
**
**  **jma
**
*************************************/

void
ArxDbgDbAdeskLogo::drawRefLine(AcGiCommonDraw* drawContext)
{
	AcDbEntity* ent;
	Acad::ErrorStatus es = acdbOpenAcDbEntity(ent, m_arbitraryRefEnt, AcDb::kForRead);
	if (es == Acad::eOk) {
		AcGePoint3d toPt;
		getReferenceAttachmentPoint(ent, toPt);
		ent->close();

		AcGePoint3d pts[2];
		pts[0] = location();
		pts[1] = toPt;

		Adesk::UInt16 curColor = drawContext->subEntityTraits().color();
		drawContext->subEntityTraits().setColor(1);
		drawContext->rawGeometry()->polyline(2, pts);
		drawContext->subEntityTraits().setColor(curColor);
	}
}

/****************************************************************************
**
**  ArxDbgDbAdeskLogo::getReferenceAttachmentPoint
**		get a place on the reference entity to draw to.  It only works well
**	for entities that correctly fill in getEcs(), or for the few built in
**	AutoCAD entities I have specifically looked for here.
**
**  **jma
**
*************************************/

void
ArxDbgDbAdeskLogo::getReferenceAttachmentPoint(AcDbEntity* ent, AcGePoint3d& toPt)
{
	AcDbCircle* circ;
	AcDbArc* arc;
	AcDbLine* line;
	AcDbPoint* point;
	AcDbBlockReference* blkRef;
	
	if ((circ = AcDbCircle::cast(ent)) != NULL)
		toPt = circ->center();
	else if ((arc = AcDbArc::cast(ent)) != NULL)
		toPt = arc->center();
	else if ((line = AcDbLine::cast(ent)) != NULL)
		toPt = line->startPoint();
	else if ((point = AcDbPoint::cast(ent)) != NULL)
		toPt = point->position();
	else if ((blkRef = AcDbBlockReference::cast(ent)) != NULL)
		toPt = blkRef->position();
	else {
			// can't get anything better so just rely on the ECS.  If the
			// raw AutoCAD entities would do this, we wouldn't need the above
			// switch statement.
		AcGeMatrix3d mat;
		ent->getEcs(mat);

		AcGeVector3d v1, v2, v3;
		mat.getCoordSystem(toPt, v1, v2, v3);
	}
}

/****************************************************************************
**
**  ArxDbgDbAdeskLogo::subSetDatabaseDefaults
**      if logo style id hasn't yet been initialized, then set it to be
**  whatever the standard logo style is for this database.  This function
**  will be called when there is a new instance that is about to be added
**  to the database (or if someone calls AcDbEntity::setDatabaseDefaults()
**  directly).  It is your chance to fill in any unititialized data.  Note,
**  that you cannot set this data in the constructor because you don't know
**  which database you will be added to and you don't want an objectId from
**  a different database than your own!
**
**  **jma
**
*************************************/

void
ArxDbgDbAdeskLogo::subSetDatabaseDefaults(AcDbDatabase* pDb)
{
    ASSERT(pDb != NULL);

		// NOTE: the following note was true in R14... don't know
		// for sure whether it is still true in R15

        // get past AutoCAD bug of calling this on Undo/Redo
        // without opening for Write!  Under the following
        // condition, AutoCAD will call this function without
        // opening us for write.  Since we may call functions that
        // call assertWriteEnabled(), we will crash if we don't
        // trap for this oddball case.
        // CONDITION:  you add a new object to the database, then
        // do an UNDO/REDO.  AutoCAD tries to get tricky with this
        // case for speed improvements.  It is really just marking
        // some state flag to say "unappended" or "reappended"
        // without invoking any UNDO filers and such.  Only problem
        // is that it calls setDatabaseDefaults() again for no
        // apparent reason (at this level of the hierarchy) since our
        // data hasn't changed.  So, either bail early as we do here,
        // or make sure assertWriteEnabled() does not get called anywhere
        // from inside this function or indirectly from this function.
    if (isWriteEnabled() == Adesk::kFalse)
        return;

    ArxDbgDbEntity::subSetDatabaseDefaults(pDb);      // let parent class do its thing

        // if style is still NULL, set it to the standard style from
        // this database.
    if (m_logoStyleId == AcDbObjectId::kNull) {
        assertWriteEnabled();
		m_logoStyleId = ArxDbgDbAdeskLogoStyle::getStandardStyle(pDb, true);
    }
}

/****************************************************************************
**
**  ArxDbgDbAdeskLogo::audit
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDbAdeskLogo::audit(AcDbAuditInfo* pAuditInfo)
{
    Acad::ErrorStatus es = ArxDbgDbEntity::audit(pAuditInfo);

	// TBD: need to fill out Audit info to make sure references are ok.

    return es;
}

/****************************************************************************
**
**  ArxDbgDbAdeskLogo::list
**
**  **jma
**
*************************************/

void
ArxDbgDbAdeskLogo::subList() const
{
	ArxDbgDbEntity::subList();

	CString str;

	AcGeScale3d sc = scale();
	printForListCmd(_T("Scale X"), ArxDbgUtils::doubleToStr(sc.sx, str));
	printForListCmd(_T("Scale Y"), ArxDbgUtils::doubleToStr(sc.sy, str));
	printForListCmd(_T("Scale Z"), ArxDbgUtils::doubleToStr(sc.sz, str));

	ArxDbgDbAdeskLogoStyle* style;
	Acad::ErrorStatus es = acdbOpenObject(style, logoStyleId(), AcDb::kForRead);
	if (es == Acad::eOk) {
		es = style->getName(str);
		if (es != Acad::eOk)
			str = ArxDbgUtils::rxErrorStr(es);

		style->close();
	}
	else
		str = ArxDbgUtils::rxErrorStr(es);

	printForListCmd(_T("Style"), str);

	printForListCmd(_T("Arbitrary Reference"), ArxDbgUtils::objToClassAndHandleStr(m_arbitraryRefEnt, str));
}

/****************************************************************************
**
**  ArxDbgDbAdeskLogo::transformBy
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDbAdeskLogo::subTransformBy(const AcGeMatrix3d& xform)
{
    assertWriteEnabled();
    
		// handle scale part of matrix here and
		// let base class handle the rest.
    if (xform.isScaledOrtho() && (xform.scale() != 1.0))
        setScale(xform.scale());

	return ArxDbgDbEntity::subTransformBy(xform);
}



