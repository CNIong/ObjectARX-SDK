//////////////////////////////////////////////////////////////////////////////
//
//                 (C) Copyright 2001-2006 by Autodesk, Inc.
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
    ~CAdUiThemeMgrReactor();
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
