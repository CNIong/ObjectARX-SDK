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

#ifndef ARXDBGUITDCTRANSIENTREACTORS_H
#define ARXDBGUITDCTRANSIENTREACTORS_H

#include "Res_ArxDbg.h"
#include "ArxDbgUiTdcObjReactorsBase.h"
#include "ArxDbgTransientEntReactor.h"
#include "ArxDbgTransientObjReactor.h"

/****************************************************************************
**
**  CLASS ArxDbgUiTdcTransientReactors:
**
**  **jma
**
*************************************/

class ArxDbgUiTdcTransientReactors : public ArxDbgUiTdcObjReactorsBase {

friend class ArxDbgUiTdmReactors;

public:
                    ArxDbgUiTdcTransientReactors();
    virtual         ~ArxDbgUiTdcTransientReactors()    {}

    //{{AFX_DATA(ArxDbgUiTdcTransientReactors)
    enum { IDD = ARXDBG_TDC_TRANSIENT_REACTORS };
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
    //{{AFX_VIRTUAL(ArxDbgUiTdcTransientReactors)
	virtual BOOL OnInitDialog();
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxDbgUiTdcTransientReactors)
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
	static ArxDbgTransientObjReactor*     m_objReactor;
	static ArxDbgTransientEntReactor*     m_entReactor;

    static void cleanUpReactors();

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
};

#endif // ARXDBGUITDCTRANSIENTREACTORS_H

