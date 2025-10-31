//////////////////////////////////////////////////////////////////////////////
//
//                     (C) Copyright 1993-1999 by Autodesk, Inc.
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

//////////////////////////////////////////////////////////////////////////////
// Note: This class is now obsolete and is slated for removal.

class ACUI_PORT CAcUiString : public CString
{
public:
        CAcUiString ();
        CAcUiString (const CString& stringSrc);
        CAcUiString (char ch, int nRepeat = 1);
        CAcUiString (LPCTSTR psz);
        CAcUiString (LPCTSTR pch, int nLength);
        CAcUiString (UINT nStringResourceID);

// Character Query Member Functions
public:
        BOOL    IsTab (int nIndex)          const;
        BOOL    IsWhiteSpace (int nIndex)   const;
        BOOL    IsAlphabetic (int nIndex)   const;
        BOOL    IsAlphanumeric (int nIndex) const;
        BOOL    IsBlank (int nIndex)        const;
        BOOL    IsPunctuation (int nIndex)  const;
        BOOL    IsUppercase (int nIndex)    const;
        BOOL    IsLowercase (int nIndex)    const;
        BOOL    IsNumeric (int nIndex)      const;
        BOOL    IsHexNumeric (int nIndex)   const;

// Misc Functions
public:
        void    MakeCharUpper (int nIndex);
        void    MakeCharLower (int nIndex);
        void    GetCurrentWorkingDirectory ();
        void    ReplaceCharWithChar (char chFrom, char chTo);

        // Strip the mnemonic character '&'.
        void    StripMnemonic ();
        // Strip the diesel prefix "$M="
        void    StripDiesel ();

        // Convert Menu execution string to AutoCAD input throat form
        void    ConvertMenuExecString ();
        // Go the other way for display in dialogs and such
        void    ConvertFromMenuExecString ();

        void    FixFileName ();

        void    WrapLine (CAcUiString& strRest, int nWrapAt);
        void    WrapLine (CStringList& strListWrapped, int nWrapAt);

        // Tab Expansion
        void    ExpandTabs (int nTabSize = 8);

// Stripping Functions
public:
        void    StripTrailingBlanks  ();
        void    StripPrecedingBlanks ();

        void    StripTrailingCharacters  (char cChar);
        void    StripPrecedingCharacters (char cChar);

// Name shortening functions for symbol table names.
// Useful for Layer and Linetype controls.
public:
        void    ShortenString (
                    CDC *pDC, 
                    CString OriginalString,
                    UINT width
                );
        CString CreateEllipsedString (
                    CDC *pDC,
                    CString OriginalString,
                    UINT width
                );

};

// string class that allows for macro expansion
// use this class instead of CAcUiString when you need to expand a macro
// such as %AUTOCAD% or %PRODUCT% in your string
class ACUI_PORT CAcUiStringExp : public CAcUiString
{
public:
        CAcUiStringExp ();
        CAcUiStringExp (const CString& stringSrc);
        CAcUiStringExp (char ch, int nRepeat = 1);
        CAcUiStringExp (LPCTSTR psz);
        CAcUiStringExp (LPCTSTR pch, int nLength);
        CAcUiStringExp (UINT nStringResourceID);

public:
        virtual BOOL LoadString(UINT nID);
        // Function to handle replacing product-specific string macros
        // with the appropriate text
        void    ReplaceProductMacroStrings();
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#pragma pack (pop)
#endif

//////////////////////////////////////////////////////////////////////////////
