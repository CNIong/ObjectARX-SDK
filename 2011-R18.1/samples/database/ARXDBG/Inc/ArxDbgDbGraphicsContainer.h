//
// (C) Copyright 1998-2006 by Autodesk, Inc. 
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

