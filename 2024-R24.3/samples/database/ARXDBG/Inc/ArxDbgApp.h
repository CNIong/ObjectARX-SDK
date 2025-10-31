//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#ifndef ARXDBGAPP_H
#define ARXDBGAPP_H

class ArxDbgEdUiContextApp;
class ArxDbgUiTdcOptions;

/****************************************************************************
**
**  CLASS ArxDbgApp:
**
**  **jma
**
*************************************/

class ArxDbgApp {

public:
						ArxDbgApp();
    virtual				~ArxDbgApp();

    AcRx::AppRetCode    entryPoint(AcRx::AppMsgCode msg, void* pPkt);

    virtual AcRx::AppRetCode    initApp();
    virtual AcRx::AppRetCode    exitApp();

    virtual AcRx::AppRetCode    initDwg();
    virtual AcRx::AppRetCode    exitDwg();
    virtual AcRx::AppRetCode    saveDwg();
    virtual AcRx::AppRetCode    endDwg();
    virtual AcRx::AppRetCode    quitDwg();
    virtual AcRx::AppRetCode    config();
    virtual AcRx::AppRetCode    invokeSubr();
    virtual AcRx::AppRetCode    initDialog(void* pTabExtMgr);
    virtual AcRx::AppRetCode    endDialog(void* pTabExtMgr);

    LPCTSTR             appName()        { return m_appName; }
    LPCTSTR             appPath()        { return m_appPath; }
    LPCTSTR             versionStr()     { return m_verStr;  }
    HINSTANCE           dllInstance() const;

    static ArxDbgApp*   getApp();   // get only instance of this app

private:
        // data members
    bool                    m_isUnlockable;
    void*                   m_acadAppPtr;
    void*                   m_appServicePtr;
    Adesk::UInt32           m_appId;
    CString                 m_appName;
	CString					m_moduleName;	// if DEBUG version, has "D" on the end
    CString                 m_appPath;
    CString                 m_verStr;
    bool                    m_didInit;
    ArxDbgEdUiContextApp*	m_uiContext;
	AcDbVoidPtrArray		m_cmdClasses;
	ArxDbgUiTdcOptions*		m_tdcOptions;

    void	registerClasses();
    void	unRegisterClasses();

    void	registerCommands();
    void	unRegisterCommands();

    void	registerAppMenu();
    void	unRegisterAppMenu();

	void	registerDialogExtensions();

	CWnd*	startSplashScreen();
	void	endSplashScreen(CWnd* splashScreen);
};


#endif    // ARXDBGAPP_H


