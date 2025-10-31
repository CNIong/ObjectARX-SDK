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

#ifndef ARXDBGTRANSIENTENTREACTOR_H
#define ARXDBGTRANSIENTENTREACTOR_H

/****************************************************************************
**
**	CLASS ArxDbgTransientEntReactor:
**
**	**jma
**
*************************************/

class ArxDbgTransientEntReactor : public AcDbEntityReactor {

friend class ArxDbgUiTdcTransientReactors;    // need access to objId list

public:
    ACRX_DECLARE_MEMBERS(ArxDbgTransientEntReactor);

        // constructors/destructor
                    ArxDbgTransientEntReactor() {}
    virtual			~ArxDbgTransientEntReactor();

    bool            addToObject(AcDbObject* obj);
    bool            delFromObject(AcDbObject* obj);
    void            delFromAll();

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
    virtual void    modifiedGraphics(const AcDbObject* obj);

private:
    AcDbObjectIdArray    m_objList;    // list of objects that have this reactor on it

    void    printReactorMessage(LPCTSTR, const AcDbObject* obj) const;

        // outlawed functions
    ArxDbgTransientEntReactor(const ArxDbgTransientEntReactor &copy);
    ArxDbgTransientEntReactor&	operator=(const ArxDbgTransientEntReactor &copy);        
};

#endif    // ARXDBGTRANSIENTENTREACTOR_H
