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

#ifndef ARXDBGTRANSIENTOBJREACTOR_H
#define ARXDBGTRANSIENTOBJREACTOR_H

/****************************************************************************
**
**	CLASS ArxDbgTransientObjReactor:
**
**	**jma
**
*************************************/

class ArxDbgTransientObjReactor : public AcDbObjectReactor {

friend class ArxDbgUiTdcTransientReactors;    // need access to objId list

public:
    ACRX_DECLARE_MEMBERS(ArxDbgTransientObjReactor);

        // constructors/destructor
                    ArxDbgTransientObjReactor() {};
    virtual         ~ArxDbgTransientObjReactor();

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

private:
        // data members
    AcDbObjectIdArray    m_objList;    // list of objects that have this reactor on it

    void        printReactorMessage(const TCHAR* event, const AcDbObject* obj) const;

        // outlawed functions
    ArxDbgTransientObjReactor(const ArxDbgTransientObjReactor &copy);
    ArxDbgTransientObjReactor&	operator=(const ArxDbgTransientObjReactor &copy);        
};

#endif    // ARXDBGTRANSIENTOBJREACTOR_H
