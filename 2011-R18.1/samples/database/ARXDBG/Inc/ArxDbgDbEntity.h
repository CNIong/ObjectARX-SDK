//
// (C) Copyright 1998-1999,2004 by Autodesk, Inc. 
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

#ifndef ARXDBGDBENTITY_H
#define ARXDBGDBENTITY_H

/****************************************************************************
**
**  CLASS ArxDbgDbEntity:
**		base class for entities.  Used as an example to show how to handle
**	basic blockReference-type transformations and how to handle references
**	to other entities.  See ArxDbgDbAdeskLogo.cpp
**	for examples of working derived classes.
**
**  **jma
**
*************************************/

class ArxDbgDbEntity : public AcDbEntity {

public:

	enum CloneRefType {
		kNoClone	= 0,
		kClone		= 1,	// Clone reference along with this object
		kFakeClone	= 2,	// Add to IdMap, but don't actually clone
	};

                ArxDbgDbEntity();
    virtual     ~ArxDbgDbEntity();

    ACRX_DECLARE_MEMBERS(ArxDbgDbEntity);

    AcGePoint3d         location() const;
    Acad::ErrorStatus   setLocation(const AcGePoint3d& pt);

    double              rotation() const;
    Acad::ErrorStatus   setRotation(double rot);

    AcGeVector3d        normal() const;
    Acad::ErrorStatus   setNormal(const AcGeVector3d& nvec);

        // overridden from AcDbEntity
    virtual	Acad::ErrorStatus	dwgInFields(AcDbDwgFiler *filer);
    virtual	Acad::ErrorStatus	dwgOutFields(AcDbDwgFiler *filer) const;
    virtual	Acad::ErrorStatus	dxfInFields(AcDbDxfFiler *filer);
    virtual	Acad::ErrorStatus	dxfOutFields(AcDbDxfFiler *filer) const;

    virtual void                getEcs(AcGeMatrix3d& retVal) const;

	virtual Acad::ErrorStatus	verifyReferences(int& fixedErrorCount, bool fullCheck);

protected:

	virtual void	getCloneReferences(AcDb::DeepCloneType type,
								AcDbObjectIdArray& objIds,
								AcDbIntArray& refTypes) const;

	void			printForListCmd(LPCTSTR label, LPCTSTR value) const;

    virtual Acad::ErrorStatus   subTransformBy(const AcGeMatrix3d& xform);

    virtual Acad::ErrorStatus   subGetGripPoints(AcGePoint3dArray&  gripPoints,
                                       AcDbIntArray&  osnapModes,
                                       AcDbIntArray&  geomIds) const;

    virtual  Acad::ErrorStatus  subMoveGripPointsAt(const AcDbIntArray& indices,
                                       const AcGeVector3d& offset);

    virtual void                subList() const;
    
    virtual Acad::ErrorStatus   subDeepClone(AcDbObject* pOwner,
                                        AcDbObject*& pClonedObject,
                                        AcDbIdMapping& idMap,
                                        Adesk::Boolean isPrimary) const;

    virtual Acad::ErrorStatus   subWblockClone(AcRxObject* pOwner,
                                        AcDbObject*& pClone,
                                        AcDbIdMapping& idMap,
                                        Adesk::Boolean isPrimary) const;

private:
        // data members
    AcGePoint3d         m_origin;
    AcGeVector3d        m_xDir;
    AcGeVector3d        m_zDir;

    static Adesk::Int16 m_version;

        // Dxf Codes
    enum {
        kDxfLocation	= 10,
        kDxfDirection   = 15,
        kDxfNormal      = 210,
    };
};


#endif    // ARXDBGDBENTITY_H
