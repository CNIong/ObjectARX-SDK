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

#ifndef ARXDBGUITDCSYSREACTORS_H
#define ARXDBGUITDCSYSREACTORS_H

#include "Res_ArxDbg.h"

#include "ArxDbgDatabaseReactor.h"
#include "ArxDbgDocumentReactor.h"
#include "ArxDbgDLinkerReactor.h"
#include "ArxDbgEditorReactor.h"
#include "ArxDbgEventReactor.h"
#include "ArxDbgGsReactor.h"
#include "ArxDbgEdInputContextReactor.h"
#include "ArxDbgLayoutManagerReactor.h"
#include "ArxDbgLongTransactionReactor.h"
#include "ArxDbgTransactionReactor.h"

/****************************************************************************
**
**  CLASS ArxDbgUiTdcSysReactors:
**
**  **jma
**
*************************************/

class ArxDbgUiTdcSysReactors : public CAcUiTabChildDialog {

friend class ArxDbgUiTdmReactors;
friend class ArxDbgAppEditorReactor;	// has to be able to attach to newly constructed databases

public:
                    ArxDbgUiTdcSysReactors();
    virtual         ~ArxDbgUiTdcSysReactors()    {}

    //{{AFX_DATA(ArxDbgUiTdcSysReactors)
    enum { IDD = ARXDBG_TDC_SYS_REACTORS };
    BOOL    m_doDatabase;
    BOOL    m_doDoc;
    BOOL    m_doLinker;
    BOOL    m_doEditor;
    BOOL    m_doEvent;
    BOOL    m_doTrans;
    BOOL    m_doLongTrans;
    BOOL    m_doGs;
    BOOL    m_doInput;
    BOOL    m_doLayout;
    BOOL    m_showLongTransDetails;
    BOOL    m_showEventDetails;
    BOOL    m_showEditorDetails;
    BOOL    m_showDocDetails;
    BOOL    m_showDbDetails;
    BOOL    m_showInputDetails;
	BOOL	m_suppressInputDetailsDuringDrag;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ArxDbgUiTdcSysReactors)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnMainDialogOK();
    //}}AFX_VIRTUAL

protected:
    // Generated message map functions
    //{{AFX_MSG(ArxDbgUiTdcSysReactors)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
        // data members

        // helper functions
    void        doDbReactor();
    void        doDLinkerReactor();
    void        doDocReactor();
    void        doEditorReactor();
    void        doEventReactor();
    void        doGsReactor();
    void        doInputReactor();
    void        doLayoutReactor();
    void        doLongTransReactor();
    void        doTransReactor();

        // static global reactor pointers
	static ArxDbgDatabaseReactor*			m_dbReactor;
	static ArxDbgDLinkerReactor*			m_dLinkerReactor;
	static ArxDbgDocumentReactor*			m_docReactor;
	static ArxDbgEditorReactor*				m_edReactor;
	static ArxDbgEventReactor*				m_eventReactor;
	static ArxDbgGsReactor*					m_gsReactor;
	static ArxDbgEdInputContextReactor*		m_inputReactor;
	static ArxDbgLayoutManagerReactor*		m_layoutReactor;
	static ArxDbgLongTransactionReactor*	m_longTransReactor;
	static ArxDbgTransactionReactor*		m_transReactor;

        // attach/detach/cleanup functions
    static void attachDbReactorToAll();
    static void removeDbReactorFromAll();

    static void attachTransactionReactorToAll();
    static void removeTransactionReactorFromAll();

    static void attachInputReactorToAll();
    static void removeInputReactorFromAll();

    static void databaseConstructed(AcDbDatabase* db);
    static void databaseDestroyed(AcDbDatabase* db);

    static void cleanUpReactors();
};


#endif // ARXDBGUITDCSYSREACTORS_H

