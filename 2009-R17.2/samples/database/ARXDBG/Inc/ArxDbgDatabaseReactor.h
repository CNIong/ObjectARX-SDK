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

#ifndef ARXDBGDBREACTOR_H
#define ARXDBGDBREACTOR_H

/****************************************************************************
**
**  CLASS DbReactor:
**
**  **jma
**
*************************************/

class ArxDbgDatabaseReactor : public AcDbDatabaseReactor {

public:
	ACRX_DECLARE_MEMBERS(ArxDbgDatabaseReactor);

        // constructor/destructors
                    ArxDbgDatabaseReactor();
    virtual         ~ArxDbgDatabaseReactor();

    virtual void    objectAppended(const AcDbDatabase* dwg, const AcDbObject* obj);
    virtual void    objectUnAppended(const AcDbDatabase* dwg, const AcDbObject* obj);
    virtual void    objectReAppended(const AcDbDatabase* dwg, const AcDbObject* obj);
    virtual void    objectOpenedForModify(const AcDbDatabase* dwg, const AcDbObject* obj);
    virtual void    objectModified(const AcDbDatabase* dwg, const AcDbObject* obj);
    virtual void    objectErased(const AcDbDatabase* dwg, const AcDbObject* obj,
                                        Adesk::Boolean pErased = Adesk::kTrue);
    virtual void    headerSysVarWillChange(const AcDbDatabase* dwg, const TCHAR* name);
    virtual void    headerSysVarChanged(const AcDbDatabase* dwg, const TCHAR* name,
                                        Adesk::Boolean bSuccess);
    virtual void	proxyResurrectionCompleted(const AcDbDatabase* dwg,
										const TCHAR* appname, AcDbObjectIdArray& objects);
    virtual void	goodbye(const AcDbDatabase* dwg);

	bool			showDetails() const;
	void			setShowDetails(bool showThem);

private:
		// data members
	bool	m_showDetails;

		// helper functions
    void    printReactorMessage(const AcDbDatabase* db, LPCTSTR event, const AcDbObject* obj) const;
    void    printReactorMessage(const AcDbDatabase* db, LPCTSTR event, LPCTSTR str) const;
    void    printReactorMessage(const AcDbDatabase* db, LPCTSTR event) const;

        // outlawed functions
	ArxDbgDatabaseReactor(const ArxDbgDatabaseReactor &copy);
    ArxDbgDatabaseReactor&  operator=(const ArxDbgDatabaseReactor &copy);        
};


#endif    // ARXDBGDBREACTOR_H
