//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2012 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
// *****************************
// *** FOR INTERNAL USE ONLY ***
// *****************************
//
#ifndef _ADUI_THEME_MANAGER_H_
#define _ADUI_THEME_MANAGER_H_


class CAdUiThemeMgrReactor
{
public:
    CAdUiThemeMgrReactor();
    virtual void ThemeAdded(const CString & strThemeName) = 0;
    virtual void ThemeRemoved(const CString & strThemeName) = 0;
    virtual void SystemColorChanged() = 0;
    virtual ~CAdUiThemeMgrReactor();
};


class CAdUiThemeManager 
{
    friend class CAdUiThemeMgrReactor;

public:
    CAdUiThemeManager();
    ~CAdUiThemeManager();

    CAdUiTheme * GetTheme(const ACHAR *pThemeName);
    BOOL ReleaseTheme(CAdUiTheme * pTheme);

    BOOL HasTheme(const ACHAR *pThemeName) const;

    void SystemColorChanged();

private:
    int  RemoveTheme(const ACHAR *pThemeName);
    void Cleanup();
    int  GetThemeIndex(const ACHAR *pThemeName) const;
    int  GetThemeIndex(const CAdUiTheme *pTheme) const;
    BOOL RegisterThemeMgrReactor(CAdUiThemeMgrReactor * pReactor);
    BOOL UnregisterThemeMgrReactor(CAdUiThemeMgrReactor * pReactor);
    void NotifyThemeAddedReactors(const CString & strThemeName);
    void NotifySysColorReactors();
    CObArray        m_list;
    CTypedPtrArray<CPtrArray, CAdUiThemeMgrReactor*> m_arrayThemeMgrReactors;
};
#endif  // _ADUI_THEME_MANAGER_H_
