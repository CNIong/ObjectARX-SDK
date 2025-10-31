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
    virtual void    proxyResurrectionCompleted(const AcDbDatabase* dwg,
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
