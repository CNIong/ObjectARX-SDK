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

#ifndef ARXDBGPERSISTENTOBJREACTOR_H
#define ARXDBGPERSISTENTOBJREACTOR_H


/****************************************************************************
**
**	CLASS ArxDbgPersistentObjReactor:
**
**	**jma
**
*************************************/


class ArxDbgPersistentObjReactor : public AcDbObject {

public:
    ACRX_DECLARE_MEMBERS(ArxDbgPersistentObjReactor);

        // constructors/destructors
					ArxDbgPersistentObjReactor()	{}
    virtual			~ArxDbgPersistentObjReactor()	{}

	void				getAttachedToObjs(AcDbObjectIdArray& objIds) const;
	Acad::ErrorStatus	attachTo(const AcDbObjectId& objId);
	Acad::ErrorStatus	detachFrom(const AcDbObjectId& objId);

    virtual void    cancelled(const AcDbObject* obj);
    virtual void    copied(const AcDbObject* obj, const AcDbObject* newObj);
    virtual void    erased(const AcDbObject* obj, Adesk::Boolean pErasing = Adesk::kTrue);
    virtual void    goodbye(const AcDbObject* obj);
    virtual void    openedForModify(const AcDbObject* obj);
    virtual void    modified(const AcDbObject* obj);
    virtual void    subObjModified(const AcDbObject* obj, const AcDbObject* subObj);
    virtual void    modifyUndone(const AcDbObject* obj);
    virtual void    modifiedXData(const AcDbObject* obj);
    virtual void    unappended(const AcDbObject* obj);
    virtual void    reappended(const AcDbObject* obj);
    virtual void    objectClosed(const AcDbObjectId objId);

    virtual Acad::ErrorStatus	dwgInFields(AcDbDwgFiler *filer);
    virtual Acad::ErrorStatus	dwgOutFields(AcDbDwgFiler *filer) const;
    virtual	Acad::ErrorStatus	dxfInFields(AcDbDxfFiler *filer);
    virtual	Acad::ErrorStatus	dxfOutFields(AcDbDxfFiler *filer) const;

protected:
		// helper functions
    virtual void	printReactorMessage(LPCTSTR event, const AcDbObject* obj) const;

private:
		// data members
	AcDbObjectIdArray	m_attachedToObjs;
    static Adesk::Int16 m_version;

        // outlawed functions
    ArxDbgPersistentObjReactor(const ArxDbgPersistentObjReactor &copy);
    ArxDbgPersistentObjReactor&	operator=(const ArxDbgPersistentObjReactor &copy);        

};

#endif    // ARXDBGPERSISTENTOBJREACTOR_H
