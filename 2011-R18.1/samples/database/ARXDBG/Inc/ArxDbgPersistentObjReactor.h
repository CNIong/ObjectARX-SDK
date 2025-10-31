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
