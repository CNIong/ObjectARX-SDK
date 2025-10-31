//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#ifndef ARXDBGDBDICTRECORD_H
#define ARXDBGDBDICTRECORD_H


/****************************************************************************
**
**	CLASS ArxDbgDbDictRecord:
**		this a base class to be used for any object that resides in a dictionary.
**	By default, there is not much support in ObjectARX for handling events 
**	like Xref name mangling, merging during INSERT, etc.  This class tries to
**	provide an example of how to implement these operations successfully.  Much
**  of the necessary code resides in ArxDbgAppEditorReactor.cpp because you must
**	rely on AcRxEventReactor or AcEdReactor functions to get the work done.
**	See ArxDbgDbAdeskLogoStyle as an example of a working derived object.
**
**	**jma
**
*************************************/

class ArxDbgDbDictRecord : public AcDbObject {

public:
                ArxDbgDbDictRecord();
    virtual     ~ArxDbgDbDictRecord();

    ACRX_DECLARE_MEMBERS(ArxDbgDbDictRecord);

        // access to data members
    virtual const TCHAR*        description() const;
    virtual void                setDescription(const TCHAR* desc);

    virtual Acad::ErrorStatus   getName(CString& name) const;

    virtual Acad::ErrorStatus   dwgInFields(AcDbDwgFiler *filer);
    virtual Acad::ErrorStatus   dwgOutFields(AcDbDwgFiler *filer) const;
    virtual Acad::ErrorStatus   dxfInFields(AcDbDxfFiler *filer);
    virtual Acad::ErrorStatus   dxfOutFields(AcDbDxfFiler *filer) const;

protected:
    virtual Acad::ErrorStatus subWblockClone(AcRxObject* pOwnerObject,
                                          AcDbObject*& pClonedObject,
                                          AcDbIdMapping& idMap,
                                          Adesk::Boolean isPrimary) const;

private:
        // data members
    CString        m_description;

		// helper functions
	bool	isDictInNOD(const AcDbObjectId& dictId, const AcDbObjectId& entryId,
                      AcDbDatabase* db, CString& dictName, CString& entryName) const;
	bool	mangleNameForXref(CString& name, AcDbDatabase* db, AcDbDictionary* pDict) const;
	bool	mangleNameForRefEdit(CString& name, AcDbDictionary* pDict) const;
	bool	unMangleNameForRefEdit(CString& csName) const;


        // DXF Codes
    enum {
        kDxfDescription   = 3,
    };
};


#endif    // ARXDBGDBDICTRECORD_H
