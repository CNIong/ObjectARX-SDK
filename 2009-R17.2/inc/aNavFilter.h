/////////////////////////////////////////////////////////////////////////////
//
//         (C) Copyright 1994-2007 by Autodesk, Inc.
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
// DESCRIPTION:
//      A CNavFilter is a CStringArray corresponding to a single
//      entry in the "files of type" combobox. It is seen by the user as,
//      for example, "Image Files(*.bmp,*.jpg)". Each extension is a string in
//      the array.
/////////////////////////////////////////////////////////////////////////////

#ifndef _ANavFilter_h
#define _ANavFilter_h

#pragma once

/////////////////////////////////////////////////////////////////////////////
// File Navigation Filter - essentially an array of file extensions
#pragma warning(push)
#pragma warning(disable : 4275)
class ANAV_PORT CNavFilter : public CStringArray {
public:
// Constructor and destructor.
                CNavFilter ();
virtual         ~CNavFilter ();

// Filter management
private:

        // A full description is "Drawing files(*.dwg)". A description
        // is "Drawing files". The full description has the actual filter
        // string in it in parens, a simple description does not.
        // The following flag if TRUE means that "m_description"
        // has a full description in it. If FALSE it has only a
        // simple description and when GetFullDescription() is called
        // "m_description" is combined with the actual filter
        // strings to get the full description desired.
        BOOL    m_bFullDescription;  

protected:

        // Either a full description or a simple one depending on the
        // "m_bFullDescription" flag.
        CString m_description;
        
        // An arbitrary int associated with this filter.        
        INT_PTR m_tagIndex;         

public:
// Get/Set functions.
        LPCTSTR GetDescription ();                  // Gets the description (simple or full) for this filter.
        void    SetDescription (LPCTSTR desc);      // Sets the simple description for this filter.
        void    GetFullDescription (CString& desc); // Gets the full description for this filter.
        void    SetFullDescription (LPCTSTR desc);  // Sets the full description for this filter.
        INT_PTR GetTagIndex ();                     
        void    SetTagIndex (INT_PTR tagIndex);

        // Find a file type in this filter and return its 0 based index.
        int     Find (LPCTSTR str);

        // Returns number of strings(extensions) in this filter.
        int     GetCount ();

        // Returns TRUE if the file name supplied is allowed using this filter.
        BOOL    IsAllowed (LPCTSTR fileName);

        // Using the same input string used to initialize the files of type in the
        // Microsoft Common File Dialog, setup this filter to do the same thing.
        LPTSTR SetFrom (LPTSTR str, BOOL bUseFullDescrition = FALSE);        
};
#pragma warning(pop)
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif
