//
// (C) Copyright 1998-1999 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//
//

#include "stdafx.h"
#include "ArxDbgDbGraphicsContainer.h"
#include "ArxDbgUtils.h"
#include "SdSysVar.h"

extern Acad::ErrorStatus
collectModelSpaceBlkEnts(AcDbDatabase* db,
                AcDbObjectIdArray& blkEnts, bool skipErased);


Adesk::Int16     ArxDbgDbGraphicsContainer::m_version = 0;     // MDI safe

ACRX_DXF_DEFINE_MEMBERS(ArxDbgDbGraphicsContainer, ArxDbgDbEntity,
						AcDb::kDHL_1015, AcDb::kMRelease0,
						0, ARXDBG_GRAPHICS_CONTAINER, ArxDbg);

/****************************************************************************
**
**  ArxDbgDbGraphicsContainer::ArxDbgDbGraphicsContainer
**
**  **jma
**
*************************************/

ArxDbgDbGraphicsContainer::ArxDbgDbGraphicsContainer()
:	m_db(NULL),
	m_objIds(100)
{
}

/****************************************************************************
**
**  ArxDbgDbGraphicsContainer::~ArxDbgDbGraphicsContainer
**
**  **jma
**
*************************************/

ArxDbgDbGraphicsContainer::~ArxDbgDbGraphicsContainer()
{
	if (m_db)
		delete m_db;
}

/****************************************************************************
**
**  ArxDbgDbGraphicsContainer::blockId
**      Returns the object id for the style that we reference
**
**  **jma
**
*************************************/

AcDbObjectId
ArxDbgDbGraphicsContainer::blockId() const
{
    assertReadEnabled();
    return m_blockId;
}

/****************************************************************************
**
**  ArxDbgDbGraphicsContainer::setBlockId
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDbGraphicsContainer::setBlockId(const AcDbObjectId& blkId)
{
    if (blkId != m_blockId) {  // don't force notifications if nothing has changed
        assertWriteEnabled();
        m_blockId = blkId;
    }

    return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDbGraphicsContainer::extDwg
**
**  **jma
**
*************************************/

const char*
ArxDbgDbGraphicsContainer::extDwg() const
{
	assertReadEnabled();
	return m_dwgName;
}

/****************************************************************************
**
**  ArxDbgDbGraphicsContainer::setExtDwg
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDbGraphicsContainer::setExtDwg(const char* fullPath)
{
	if (m_dwgName.Compare(fullPath) != 0) {  // don't force notifications if nothing has changed
		assertWriteEnabled();
		m_dwgName = fullPath;
		return loadDwgFile();
	}

	return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDbGraphicsContainer::loadDwgFile
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDbGraphicsContainer::loadDwgFile()
{
	if (m_db)
		delete m_db;

	if (m_dwgName.IsEmpty())
		return Acad::eOk;

    if ((m_db = new AcDbDatabase(false, true)) == NULL) {
        acutPrintf("\nERROR: could not construct new database.");
		m_db = NULL;
        return Acad::eInvalidInput;
	}

	Acad::ErrorStatus es = m_db->readDwgFile(m_dwgName, _SH_DENYNO);	// don't deny anyone else from using the file.
	if (es != Acad::eOk) {
		acutPrintf("\nERROR: could not read drawing database %s", ArxDbgUtils::rxErrorStr(es)) ;
	   	delete m_db;
		m_db = NULL;
    }

	AcDbObjectIdArray blkEnts;
	m_objIds.setLogicalLength(0);

	es = collectModelSpaceBlkEnts(m_db, m_objIds, true);
	if (es != Acad::eOk)
		return es;
	
	return Acad::eOk;
}

/****************************************************************************
**
**  ArxDbgDbGraphicsContainer::drawMarker
**		draw a Green and Yellow (in honor of the U of O Ducks!) node marker
**
**  **jma
**
*************************************/

void
ArxDbgDbGraphicsContainer::drawMarker(AcGiWorldDraw* mode)
{
        // calculate size of a marker by using PDSIZE variable
        // which is how AcDbPoint entities draw in AutoCAD.
	AcDbDatabase* db = NULL;
	AcGiContext* context = mode->context();
	if (context)
		db = context->database();
	if (db == NULL)
		db = acdbHostApplicationServices()->workingDatabase();

    double pdsize = db->pdsize();

    if (pdsize <= 0.0) {			// values greater than 0.0 are already in absolute size
        double viewsize = 100.0;	// arbitrary hard default

        getSysVar("viewsize", viewsize);
        viewsize /= 2.0;     // ?? doesn't match AutoCAD docs, but is correct value
        if (pdsize < 0.0)    // percentage of viewsize
            pdsize  = viewsize * (fabs(pdsize) / 100.0);
        else
            pdsize = viewsize * 0.05;        // 5% of viewsize
    }

    double halfSize = pdsize / 2.0;

    AcGePoint3d pts[5];
    pts[0].set(-halfSize, -halfSize, 0.0);
    pts[1].set( halfSize, -halfSize, 0.0);
    pts[2].set( halfSize,  halfSize, 0.0);
    pts[3].set(-halfSize,  halfSize, 0.0);
    pts[4].set(-halfSize, -halfSize, 0.0);

	Adesk::UInt16 curColor = mode->subEntityTraits().color();
	AcDbObjectId curLtype  = mode->subEntityTraits().lineTypeId();

	mode->subEntityTraits().setColor(3);
	mode->subEntityTraits().setLineType(db->continuousLinetype());

    mode->geometry().polyline(5, pts);			// draw box

	AcGePoint3d slashPts[2];

	mode->subEntityTraits().setColor(2);

	slashPts[0] = pts[0];
	slashPts[1] = pts[2];
    mode->geometry().polyline(2, slashPts);		// draw slash

	slashPts[0] = pts[1];
	slashPts[1] = pts[3];
    mode->geometry().polyline(2, slashPts);		// draw slash the other way to make an 'X'

	mode->subEntityTraits().setColor(curColor);
	mode->subEntityTraits().setLineType(curLtype);
}

/****************************************************************************
**
**  ArxDbgDbGraphicsContainer::worldDraw
**
**  **jma
**
*************************************/

Adesk::Boolean
ArxDbgDbGraphicsContainer::worldDraw(AcGiWorldDraw* mode)
{
    if (mode->regenAbort())
        return Adesk::kTrue;

    AcGeMatrix3d mat;
    getEcs(mat);   // push ECS of this graphicsContainer

    mode->geometry().pushModelTransform(mat);

	drawMarker(mode);	// ensure that there is some kind of graphics to select

    if (m_db != NULL) {
	    AcDbEntity* ent;
		Acad::ErrorStatus es;

		int len = m_objIds.length();
        for (int i=0; i<len; i++) {
			es = acdbOpenAcDbEntity(ent, m_objIds[i], AcDb::kForRead);
			if (es == Acad::eOk) {
				mode->geometry().draw(ent);
				ent->close();
			}
			else
				ArxDbgUtils::rxErrorMsg(es);
        }
    }

	AcDbBlockTableRecord* blkRec;
	Acad::ErrorStatus es = acdbOpenObject(blkRec, m_blockId, AcDb::kForRead);
	if (es == Acad::eOk) {
		mode->geometry().draw(blkRec);
		blkRec->close();
	}

    mode->geometry().popModelTransform();

	return Adesk::kTrue;
}

/****************************************************************************
**
**  ArxDbgDbGraphicsContainer::setAttributes
**
**  **jma
**
*************************************/

Adesk::UInt32
ArxDbgDbGraphicsContainer::setAttributes(AcGiDrawableTraits* pTraits)
{
    Adesk::UInt32 nResult;

// TBD: at this point, these settings seems to be mutually exclusive and a little unreliable.
// maybe I am doing something wrong???
	
	//nResult = AcGiDrawable::kDrawableIsAnEntity | AcGiDrawable::kDrawableUsesNesting;
	//nResult = AcGiDrawable::kDrawableIsAnEntity | AcGiDrawable::kDrawableIsCompoundObject;
	nResult = AcGiDrawable::kDrawableIsDimension;

    pTraits->setupForEntity(this);

    return nResult;
}

/****************************************************************************
**
**  ArxDbgDbGraphicsContainer::dwgInFields
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDbGraphicsContainer::dwgInFields(AcDbDwgFiler* filer)
{
    Acad::ErrorStatus es;
    if ((es = ArxDbgDbEntity::dwgInFields(filer)) != Acad::eOk)
        return es;

    Adesk::Int16 version;
    filer->readItem(&version);
    if (version > m_version)
        return Acad::eMakeMeProxy;

		// read in the drawing name
	char* tmpStr = NULL;
    filer->readItem(&tmpStr);
	m_dwgName = tmpStr;
	acutDelString(tmpStr);

	if (filer->filerType() == AcDb::kFileFiler)
		loadDwgFile();

	filer->readItem(&m_blockId);

    return filer->filerStatus();
}

/****************************************************************************
**
**  ArxDbgDbGraphicsContainer::dwgOutFields
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDbGraphicsContainer::dwgOutFields(AcDbDwgFiler* filer) const
{
    Acad::ErrorStatus es;
    if ((es = ArxDbgDbEntity::dwgOutFields(filer)) != Acad::eOk)
        return es;

    filer->writeItem(m_version);

    filer->writeItem(static_cast<const char*>(m_dwgName));
	filer->writeItem(m_blockId);

    return filer->filerStatus();
}

/****************************************************************************
**
**  ArxDbgDbGraphicsContainer::dxfInFields
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
ArxDbgDbGraphicsContainer::dxfInFields(AcDbDxfFiler* filer)
{
    Acad::ErrorStatus es;
    if (((es = ArxDbgDbEntity::dxfInFields(filer)) != Acad::eOk) ||
        (filer->atSubclassData(this->desc()->name()) != Adesk::kTrue))
        return filer->filerStatus();

    resbuf rb;

    while ((es == Acad::eOk) && ((es = filer->readResBuf(&rb)) == Acad::eOk)) {
        if (rb.restype == kDxfDwgName) {
			setExtDwg(rb.resval.rstring);
        }
		else if (rb.restype == kDxfBlockId) {
            AcDbObjectId id;
            id.setFromOldId(rb.resval.rlong);
            setBlockId(id);
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
**  ArxDbgDbGraphicsContainer::dxfOutFields
**
**  **jma
**
*************************************/

Acad::ErrorStatus
ArxDbgDbGraphicsContainer::dxfOutFields(AcDbDxfFiler* filer) const
{
    Acad::ErrorStatus es;
    if ((es = ArxDbgDbEntity::dxfOutFields(filer)) != Acad::eOk)
        return es;

    filer->writeItem(AcDb::kDxfSubclass, this->desc()->name());

    filer->writeItem(kDxfDwgName, m_dwgName);
    filer->writeItem(kDxfBlockId, m_blockId);

    return filer->filerStatus();
}

/****************************************************************************
**
**  ArxDbgDbGraphicsContainer::list
**
**  **jma
**
*************************************/

void
ArxDbgDbGraphicsContainer::list() const
{
	ArxDbgDbEntity::list();

	CString str;

	ArxDbgUtils::symbolIdToName(m_blockId, str);
	printForListCmd(_T("Block"), str);
	printForListCmd(_T("DWG File"), static_cast<LPCTSTR>(m_dwgName));
	printForListCmd(_T("Database Loaded"), ArxDbgUtils::booleanToStr((m_db != NULL), str));
}


