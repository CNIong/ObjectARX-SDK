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
