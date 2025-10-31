//
// (C) Copyright 1998-1999 by Autodesk, Inc. 
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


