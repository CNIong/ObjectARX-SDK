//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#include "ArxDbgDbEntity.h"

/****************************************************************************
**
**  CLASS ArxDbgDbGraphicsContainer:
**		used as an example of re-using entities to do the drawing work for
**	you by simply passing them onto AcGi.  The option to use an External
**	drawing may not be the most bullet-proof implementation... so use with
**	caution.
**
**  **jma
**
*************************************/

class ArxDbgDbGraphicsContainer: public ArxDbgDbEntity {

public:
						ArxDbgDbGraphicsContainer();
	virtual				~ArxDbgDbGraphicsContainer();

    ACDB_DECLARE_MEMBERS(ArxDbgDbGraphicsContainer);

	LPCTSTR				extDwg() const;
	Acad::ErrorStatus	setExtDwg(const TCHAR* fullPath);

	AcDbObjectId		blockId() const;
	Acad::ErrorStatus	setBlockId(const AcDbObjectId& blkRecId);

		// overridden from AcDbEntity
    virtual Acad::ErrorStatus	dwgInFields(AcDbDwgFiler *filer);
    virtual Acad::ErrorStatus	dwgOutFields(AcDbDwgFiler *filer) const;
    virtual Acad::ErrorStatus	dxfInFields(AcDbDxfFiler *filer);
    virtual Acad::ErrorStatus	dxfOutFields(AcDbDxfFiler *filer) const;

protected:
    virtual Adesk::Boolean      subWorldDraw(AcGiWorldDraw* mode);
	virtual Adesk::UInt32		subSetAttributes(AcGiDrawableTraits* traits);
    virtual void                subList() const;
    virtual Acad::ErrorStatus subGetCompoundObjectTransform(AcGeMatrix3d & xMat) const;

private:
		// data members
	AcDbObjectIdArray	m_objIds;
	AcDbDatabase*		m_db;
	CString				m_dwgName;
	AcDbHardPointerId	m_blockId;

    static Adesk::Int16 m_version;

		// helper functions
	Acad::ErrorStatus	loadDwgFile();
	void				drawMarker(AcGiWorldDraw* mode);

        // Dxf Codes
    enum {
        kDxfDwgName			= 2,
		kDxfBlockId			= 340,
    };
};

