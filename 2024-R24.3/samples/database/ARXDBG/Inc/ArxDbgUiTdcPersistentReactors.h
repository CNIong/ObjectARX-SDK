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
//

#ifndef ARXDBGUITDCPERSISTENTREACTORS_H
#define ARXDBGUITDCPERSISTENTREACTORS_H

#include "Res_ArxDbg.h"
#include "ArxDbgUiTdcObjReactorsBase.h"
#include "ArxDbgPersistentEntReactor.h"
#include "ArxDbgPersistentObjReactor.h"

/****************************************************************************
**
**  CLASS ArxDbgUiTdcPersistentReactors:
**
**  **jma
**
*************************************/

class ArxDbgUiTdcPersistentReactors : public ArxDbgUiTdcObjReactorsBase {

friend class ArxDbgUiTdmReactors;

public:
                    ArxDbgUiTdcPersistentReactors();
    virtual         ~ArxDbgUiTdcPersistentReactors()    {}

    //{{AFX_DATA(ArxDbgUiTdcPersistentReactors)
    enum { IDD = ARXDBG_TDC_PERSISTENT_REACTORS };
    static BOOL			m_doStateModified;
    static BOOL			m_doStateCopied;
    static BOOL			m_doStateCancelled;
    static BOOL			m_doStateErased;
    static BOOL			m_doStateGoodbye;
    static BOOL			m_doStateOpenMod;
    static BOOL			m_doStateSubObjMod;
    static BOOL			m_doStateModUndone;
    static BOOL			m_doStateModXdata;
    static BOOL			m_doStateModGraphics;
    static BOOL			m_doStateUnappended;
    static BOOL			m_doStateReappended;
    static BOOL			m_doStateClosed;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxDbgUiTdcPersistentReactors)
	virtual BOOL OnInitDialog();
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxDbgUiTdcPersistentReactors)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

	virtual	void	getAttachedObjects(AcDbObjectIdArray& objIds);
	virtual void	getAttachedEntities(AcDbObjectIdArray& objIds);

	virtual void	attachObjReactors(const AcDbObjectIdArray& objIds);
	virtual void	attachEntReactors();
	virtual void	detachEntReactors();
	virtual void	detachSelectedEnts(const AcDbObjectIdArray& objIds);
	virtual void	detachSelectedObjs(const AcDbObjectIdArray& objIds);

private:
		// global pointers to single instances of reactors
	static ArxDbgPersistentObjReactor*  m_objReactor;
	static ArxDbgPersistentEntReactor*  m_entReactor;
    static LPCTSTR						m_dictName;    // dictionary for persistent entity reactors

public:
        // allow reactors to display state of notifying object
    static void doStateDboxCacelled(const AcDbObject* obj);
    static void doStateDboxCopied(const AcDbObject* obj, const AcDbObject* newObject);
    static void doStateDboxErased(const AcDbObject* obj, Adesk::Boolean isErase);
    static void doStateDboxGoodbye(const AcDbObject* obj);
    static void doStateDboxOpenedModify(const AcDbObject* obj);
    static void doStateDboxModified(const AcDbObject* obj);
    static void doStateDboxSubObjModified(const AcDbObject* obj, const AcDbObject* subObj);
    static void doStateDboxModifyUndone(const AcDbObject* obj);
    static void doStateDboxModifiedXdata(const AcDbObject* obj);
    static void doStateDboxModifiedGraphics(const AcDbObject* obj);
    static void doStateDboxUnappended(const AcDbObject* obj);
    static void doStateDboxReappended(const AcDbObject* obj);
    static void doStateDboxClosed(const AcDbObjectId& objId);

		// look up the persistent reactor in the dictionary of the
		// appropriate database
	static AcDbObjectId	getPersistentObjReactor(AcDbDatabase* db, bool createIfNotFound);
	static AcDbObjectId	getPersistentEntReactor(AcDbDatabase* db, bool createIfNotFound);

};

#endif // ARXDBGUITDCPERSISTENTREACTORS_H

