//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////


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
