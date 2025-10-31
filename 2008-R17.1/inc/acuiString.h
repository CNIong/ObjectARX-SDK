//////////////////////////////////////////////////////////////////////////////
//
//                     (C) Copyright 1993-2006 by Autodesk, Inc.
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

#ifndef _acuiString_h
#define _acuiString_h
#pragma pack (push, 8)

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "AdAChar.h"
//////////////////////////////////////////////////////////////////////////////
// Note: This class is now obsolete and is slated for removal.

class CAcUiString : public CString
{
public:
        ADUI_PORT CAcUiString ();
        ADUI_PORT CAcUiString (const CString& stringSrc);
        ADUI_PORT CAcUiString (ACHAR ch, int nRepeat = 1);
        ADUI_PORT CAcUiString (LPCTSTR psz);
        ADUI_PORT CAcUiString (LPCTSTR pch, int nLength);
        ADUI_PORT CAcUiString (UINT nStringResourceID);

// Character Query Member Functions
public:
        ADUI_PORT BOOL    IsTab (int nIndex)          const;
        ADUI_PORT BOOL    IsWhiteSpace (int nIndex)   const;
        ADUI_PORT BOOL    IsAlphabetic (int nIndex)   const;
        ADUI_PORT BOOL    IsAlphanumeric (int nIndex) const;
        ADUI_PORT BOOL    IsBlank (int nIndex)        const;
        ADUI_PORT BOOL    IsPunctuation (int nIndex)  const;
        ADUI_PORT BOOL    IsUppercase (int nIndex)    const;
        ADUI_PORT BOOL    IsLowercase (int nIndex)    const;
        ADUI_PORT BOOL    IsNumeric (int nIndex)      const;
        ADUI_PORT BOOL    IsHexNumeric (int nIndex)   const;

// Misc Functions
public:
        ADUI_PORT void    MakeCharUpper (int nIndex);
        ADUI_PORT void    MakeCharLower (int nIndex);
        ADUI_PORT void    GetCurrentWorkingDirectory ();
        ADUI_PORT void    ReplaceCharWithChar (ACHAR chFrom, ACHAR chTo);

        // Strip the mnemonic character '&'.
        ADUI_PORT void    StripMnemonic ();
        // Strip the diesel prefix "$M="
        ADUI_PORT void    StripDiesel ();

        // Convert Menu execution string to AutoCAD input throat form
        ADUI_PORT void    ConvertMenuExecString ();
        // Go the other way for display in dialogs and such
        ADUI_PORT void    ConvertFromMenuExecString ();

        ADUI_PORT void    FixFileName ();

        ADUI_PORT void    WrapLine (CAcUiString& strRest, int nWrapAt);
        ADUI_PORT void    WrapLine (CStringList& strListWrapped, int nWrapAt);

        // Tab Expansion
        ADUI_PORT void    ExpandTabs (int nTabSize = 8);

// Stripping Functions
public:
        ADUI_PORT void    StripTrailingBlanks  ();
        ADUI_PORT void    StripPrecedingBlanks ();

        ADUI_PORT void    StripTrailingCharacters  (ACHAR cChar);
        ADUI_PORT void    StripPrecedingCharacters (ACHAR cChar);

// Name shortening functions for symbol table names.
// Useful for Layer and Linetype controls.
public:
        ADUI_PORT void    ShortenString (
                    CDC *pDC, 
                    CString OriginalString,
                    UINT width
                );
        ADUI_PORT CString CreateEllipsedString (
                    CDC *pDC,
                    CString OriginalString,
                    UINT width
                );

};

// string class that allows for macro expansion
// use this class instead of CAcUiString when you need to expand a macro
// such as %AUTOCAD% or %PRODUCT% in your string
class CAcUiStringExp : public CAcUiString
{
public:
        ADUI_PORT CAcUiStringExp ();
        ADUI_PORT CAcUiStringExp (const CString& stringSrc);
        ADUI_PORT CAcUiStringExp (ACHAR ch, int nRepeat = 1);
        ADUI_PORT CAcUiStringExp (LPCTSTR psz);
        ADUI_PORT CAcUiStringExp (LPCTSTR pch, int nLength);
        ADUI_PORT CAcUiStringExp (UINT nStringResourceID);

public:
        ADUI_PORT virtual BOOL LoadString(UINT nID);
        // Function to handle replacing product-specific string macros
        // with the appropriate text
        ADUI_PORT void    ReplaceProductMacroStrings();
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#pragma pack (pop)
#endif

//////////////////////////////////////////////////////////////////////////////
