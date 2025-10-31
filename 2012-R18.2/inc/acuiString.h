//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright 1993-2011 by Autodesk, Inc.
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

#if _MSC_VER >= 1000 || defined(__GNUC__)
#pragma once
#endif // _MSC_VER >= 1000

#include "adui_port.h"
#include "AdAChar.h"

//////////////////////////////////////////////////////////////////////////////
// Note: This class is now obsolete and is slated for removal.

class CAcUiString : public CString
{
public:
        ACUI_PORT CAcUiString ();
        ACUI_PORT CAcUiString (const CString& stringSrc);
        ACUI_PORT CAcUiString (ACHAR ch, int nRepeat = 1);
        ACUI_PORT CAcUiString (LPCTSTR psz);
        ACUI_PORT CAcUiString (LPCTSTR pch, int nLength);
        ACUI_PORT CAcUiString (UINT nStringResourceID);

// Character Query Member Functions
public:
        ACUI_PORT BOOL    IsTab (int nIndex)          const;
        ACUI_PORT BOOL    IsWhiteSpace (int nIndex)   const;
        ACUI_PORT BOOL    IsAlphabetic (int nIndex)   const;
        ACUI_PORT BOOL    IsAlphanumeric (int nIndex) const;
        ACUI_PORT BOOL    IsBlank (int nIndex)        const;
        ACUI_PORT BOOL    IsPunctuation (int nIndex)  const;
        ACUI_PORT BOOL    IsUppercase (int nIndex)    const;
        ACUI_PORT BOOL    IsLowercase (int nIndex)    const;
        ACUI_PORT BOOL    IsNumeric (int nIndex)      const;
        ACUI_PORT BOOL    IsHexNumeric (int nIndex)   const;

// Misc Functions
public:
        ACUI_PORT void    MakeCharUpper (int nIndex);
        ACUI_PORT void    MakeCharLower (int nIndex);
        ACUI_PORT void    GetCurrentWorkingDirectory ();
        ACUI_PORT void    ReplaceCharWithChar (ACHAR chFrom, ACHAR chTo);

        // Strip the mnemonic character '&'.
        ACUI_PORT void    StripMnemonic ();
        // Strip the diesel prefix "$M="
        ACUI_PORT void    StripDiesel ();

        // Convert Menu execution string to AutoCAD input throat form
        ACUI_PORT void    ConvertMenuExecString ();
        // Go the other way for display in dialogs and such
        ACUI_PORT void    ConvertFromMenuExecString ();

        ACUI_PORT void    FixFileName ();

        ACUI_PORT void    WrapLine (CAcUiString& strRest, int nWrapAt);
        ACUI_PORT void    WrapLine (CStringList& strListWrapped, int nWrapAt);

        // Tab Expansion
        ACUI_PORT void    ExpandTabs (int nTabSize = 8);

// Stripping Functions
public:
        ACUI_PORT void    StripTrailingBlanks  ();
        ACUI_PORT void    StripPrecedingBlanks ();

        ACUI_PORT void    StripTrailingCharacters  (ACHAR cChar);
        ACUI_PORT void    StripPrecedingCharacters (ACHAR cChar);

// Name shortening functions for symbol table names.
// Useful for Layer and Linetype controls.
public:
        ACUI_PORT void    ShortenString (
                    CDC *pDC, 
                    CString OriginalString,
                    UINT width
                );
        ACUI_PORT CString CreateEllipsedString (
                    CDC *pDC,
                    CString OriginalString,
                    UINT width
                );

};

#pragma warning(push)
#pragma warning(disable:4265)//disable missing virtual destructor warning
// string class that allows for macro expansion
// use this class instead of CAcUiString when you need to expand a macro
// such as %AUTOCAD% or %PRODUCT% in your string
class CAcUiStringExp : public CAcUiString
{
public:
        ACUI_PORT CAcUiStringExp ();
        ACUI_PORT CAcUiStringExp (const CString& stringSrc);
        ACUI_PORT CAcUiStringExp (ACHAR ch, int nRepeat = 1);
        ACUI_PORT CAcUiStringExp (LPCTSTR psz);
        ACUI_PORT CAcUiStringExp (LPCTSTR pch, int nLength);
        ACUI_PORT CAcUiStringExp (UINT nStringResourceID);

public:
        ACUI_PORT virtual BOOL LoadString(UINT nID);
        // Function to handle replacing product-specific string macros
        // with the appropriate text
        ACUI_PORT void    ReplaceProductMacroStrings();
};
#pragma warning(pop) // C4265

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#pragma pack (pop)
#endif

//////////////////////////////////////////////////////////////////////////////
