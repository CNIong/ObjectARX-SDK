//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2015 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
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
        ACCORE_PORT CAcUiString ();
        ACCORE_PORT CAcUiString (const CString& stringSrc);
        ACCORE_PORT CAcUiString (ACHAR ch, int nRepeat = 1);
        ACCORE_PORT CAcUiString (LPCTSTR psz);
        ACCORE_PORT CAcUiString (LPCTSTR pch, int nLength);
        ACCORE_PORT CAcUiString (UINT nStringResourceID);

// Character Query Member Functions
public:
        ACCORE_PORT BOOL    IsTab (int nIndex)          const;
        ACCORE_PORT BOOL    IsWhiteSpace (int nIndex)   const;
        ACCORE_PORT BOOL    IsAlphabetic (int nIndex)   const;
        ACCORE_PORT BOOL    IsAlphanumeric (int nIndex) const;
        ACCORE_PORT BOOL    IsBlank (int nIndex)        const;
        ACCORE_PORT BOOL    IsPunctuation (int nIndex)  const;
        ACCORE_PORT BOOL    IsUppercase (int nIndex)    const;
        ACCORE_PORT BOOL    IsLowercase (int nIndex)    const;
        ACCORE_PORT BOOL    IsNumeric (int nIndex)      const;
        ACCORE_PORT BOOL    IsHexNumeric (int nIndex)   const;

// Misc Functions
public:
        ACCORE_PORT void    MakeCharUpper (int nIndex);
        ACCORE_PORT void    MakeCharLower (int nIndex);
        ACCORE_PORT void    GetCurrentWorkingDirectory ();
        ACCORE_PORT void    ReplaceCharWithChar (ACHAR chFrom, ACHAR chTo);

        // Strip the mnemonic character '&'.
        ACCORE_PORT void    StripMnemonic ();
        // Strip the diesel prefix "$M="
        ACCORE_PORT void    StripDiesel ();

        // Convert Menu execution string to AutoCAD input throat form
        ACCORE_PORT void    ConvertMenuExecString ();
        // Go the other way for display in dialogs and such
        ACCORE_PORT void    ConvertFromMenuExecString ();

        ACCORE_PORT void    FixFileName ();

        ACCORE_PORT void    WrapLine (CAcUiString& strRest, int nWrapAt);
        ACCORE_PORT void    WrapLine (CStringList& strListWrapped, int nWrapAt);

        // Tab Expansion
        ACCORE_PORT void    ExpandTabs (int nTabSize = 8);

// Stripping Functions
public:
        ACCORE_PORT void    StripTrailingBlanks  ();
        ACCORE_PORT void    StripPrecedingBlanks ();

        ACCORE_PORT void    StripTrailingCharacters  (ACHAR cChar);
        ACCORE_PORT void    StripPrecedingCharacters (ACHAR cChar);

// Name shortening functions for symbol table names.
// Useful for Layer and Linetype controls.
public:
        ACCORE_PORT void    ShortenString (
                    CDC *pDC, 
                    CString OriginalString,
                    UINT width
                );
        ACCORE_PORT CString CreateEllipsedString (
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
        ACCORE_PORT CAcUiStringExp ();
        ACCORE_PORT virtual ~CAcUiStringExp();
        ACCORE_PORT CAcUiStringExp (const CString& stringSrc);
        ACCORE_PORT CAcUiStringExp (ACHAR ch, int nRepeat = 1);
        ACCORE_PORT CAcUiStringExp (LPCTSTR psz);
        ACCORE_PORT CAcUiStringExp (LPCTSTR pch, int nLength);
        ACCORE_PORT CAcUiStringExp (UINT nStringResourceID);

public:
        ACCORE_PORT virtual BOOL LoadString(UINT nID);
        // Function to handle replacing product-specific string macros
        // with the appropriate text
        ACCORE_PORT void    ReplaceProductMacroStrings();
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#pragma pack (pop)
#endif

//////////////////////////////////////////////////////////////////////////////
