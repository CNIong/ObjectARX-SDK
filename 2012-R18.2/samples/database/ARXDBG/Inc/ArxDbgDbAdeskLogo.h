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

#ifndef ARXDBGDBADESKLOGO_H
#define ARXDBGDBADESKLOGO_H

#include "ArxDbgDbEntity.h"

class ArxDbgDbAdeskLogoStyle;

/****************************************************************************
**
**  CLASS ArxDbgDbAdeskLogo:
**		an example of handling some common operations for certain types of
**	entities.  This does not attempt to be a full-featured entity in the sense
**	that it fills out every single function that it is supposed to.  Its main
**  purpose is to illustrate how to deal with pointing to a dictionary-resident
**	"Style" object and how to handle references to other entities.
**
**  **jma
**
*************************************/

class ArxDbgDbAdeskLogo : public ArxDbgDbEntity {

public:
                ArxDbgDbAdeskLogo();
    virtual     ~ArxDbgDbAdeskLogo();

    ACRX_DECLARE_MEMBERS(ArxDbgDbAdeskLogo);

    AcDbObjectId        logoStyleId() const;
    Acad::ErrorStatus   setLogoStyleId(const AcDbObjectId& styleId);

    AcGeScale3d         scale() const;
    Acad::ErrorStatus   setScale(const AcGeScale3d& scaleFactors);

	AcDbObjectId		arbitraryReferenceId() const;
	Acad::ErrorStatus	setArbitraryReferenceId(const AcDbObjectId& refId);

        // overridden from AcDbEntity
    virtual void        subSetDatabaseDefaults(AcDbDatabase* pDb);

    virtual Acad::ErrorStatus	dwgInFields(AcDbDwgFiler *filer);
    virtual Acad::ErrorStatus	dwgOutFields(AcDbDwgFiler *filer) const;
    virtual Acad::ErrorStatus	dxfInFields(AcDbDxfFiler *filer);
    virtual Acad::ErrorStatus	dxfOutFields(AcDbDxfFiler *filer) const;
    virtual Acad::ErrorStatus	audit(AcDbAuditInfo* pAuditInfo);

	virtual Acad::ErrorStatus	verifyReferences(int& fixedErrorCount, bool fullCheck);

protected:
    // overridden from AcDbEntity
    virtual Adesk::Boolean      subWorldDraw(AcGiWorldDraw* worldDraw);
    virtual void                subViewportDraw(AcGiViewportDraw* vportDraw);
    virtual Acad::ErrorStatus   subTransformBy(const AcGeMatrix3d& xform);
    virtual void                subList() const;

    virtual void        commonDraw(AcGiCommonDraw* drawContext);
    virtual void        drawSingleCaliper(AcGiCommonDraw* drawContext, AcGePoint3d* pts, ArxDbgDbAdeskLogoStyle* lStyle);
    virtual void        drawLogo(AcGiCommonDraw* drawContext, ArxDbgDbAdeskLogoStyle* lStyle);
    virtual void        drawLabel(AcGiCommonDraw* drawContext, ArxDbgDbAdeskLogoStyle* lStyle);
    virtual void        drawBorder(AcGiCommonDraw* drawContext, ArxDbgDbAdeskLogoStyle* lStyle);
    virtual void        drawRefLine(AcGiCommonDraw* drawContext);

	virtual void		getReferenceAttachmentPoint(AcDbEntity* ent, AcGePoint3d& toPt);

protected:

	virtual void		getCloneReferences(AcDb::DeepCloneType type,
								AcDbObjectIdArray& objIds,
								AcDbIntArray& refTypes) const;

private:
        // data members
    AcDbHardPointerId   m_logoStyleId;
	AcDbHardPointerId	m_arbitraryRefEnt;
    AcGeScale3d         m_scale;
    static Adesk::Int16 m_version;
	
    // we use an in-memory Mtext object to do the dirty work of writing out
    // the text since it is extremely hard to write text with the AcGi::text()
    // signatures.
	AcDbMText* m_tmpMtext;

        // Dxf Codes
    enum {
        kDxfScale			= 15,
        kDxfLogoStyleId		= 340,
        kDxfArbitraryRefId	= 341,
    };

};


#endif    // ARXDBGDBADESKLOGO_H
