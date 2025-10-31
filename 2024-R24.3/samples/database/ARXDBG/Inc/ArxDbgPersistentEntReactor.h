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

#ifndef ARXDBGPERSISTENTENTREACTOR_H
#define ARXDBGPERSISTENTENTREACTOR_H

#include "ArxDbgPersistentObjReactor.h"

/****************************************************************************
**
**	CLASS ArxDbgPersistEntReactor:
**
**	**jma
**
*************************************/

class ArxDbgPersistentEntReactor : public ArxDbgPersistentObjReactor {

public:
    ACRX_DECLARE_MEMBERS(ArxDbgPersistentEntReactor);

        // constructors/destructors
					ArxDbgPersistentEntReactor()	{}
    virtual			~ArxDbgPersistentEntReactor()	{}

    virtual void    modifiedGraphics(const AcDbObject* obj);

    virtual Acad::ErrorStatus	dwgInFields(AcDbDwgFiler *filer);
    virtual Acad::ErrorStatus	dwgOutFields(AcDbDwgFiler *filer) const;
    virtual	Acad::ErrorStatus	dxfInFields(AcDbDxfFiler *filer);
    virtual	Acad::ErrorStatus	dxfOutFields(AcDbDxfFiler *filer) const;

protected:
		// helper functions
    virtual void	printReactorMessage(LPCTSTR event, const AcDbObject* obj) const;

private:
		// data members
    static Adesk::Int16 m_version;

        // outlawed functions
                                ArxDbgPersistentEntReactor(const ArxDbgPersistentEntReactor &copy);
    ArxDbgPersistentEntReactor&	operator=(const ArxDbgPersistentEntReactor &copy);        

};

#endif    // ARXDBGPERSISTENTENTREACTOR_H
