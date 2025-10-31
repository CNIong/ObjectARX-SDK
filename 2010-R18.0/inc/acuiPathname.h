//
//  (C) Copyright 1995-2004 by Autodesk, Inc.
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

#pragma once

#pragma pack (push, 8)


//Forward declarations.
class AFILE;

class ACUI_PORT CAcUiPathname : public CAdUiPathname {

public:

// methods
        // constructor (initializes private data)
        CAcUiPathname(void);
        CAcUiPathname(const CAcUiPathname&);

        // destructor (frees allocated storage)
        ~CAcUiPathname(void);

        // parse a string, validate the format and fill in the data
        //  This routine actually calls ParseRelative with the
        //  current document path (if any) or the current application
        //  path as the relative path.
virtual PathErr Parse( LPCTSTR, const BOOL wildcard_ok = FALSE );

        // check status for the path
        //  the returned values are defined in astat.h
        int Status(void);

        // takes a path and tries to open it.  Return TRUE if
        //  the open succeeded, FALSE otherwise.  Note that
        //  these routines set the current directory to the
        //  appropriate place before opening, and reset it
        //  afterward.
        BOOL Open(AFILE** fdp, const TCHAR *openmode);

        // create an assignment operator that does the right thing.
        const CAcUiPathname& CAcUiPathname::operator=(const CAcUiPathname& pathSrc);
        const CAcUiPathname& CAcUiPathname::operator=(const CAcUiPathname* pathSrc);
        
protected:
        // the guts of the assignment operator
virtual void AssignCopy( const CAcUiPathname& );
    
};

inline const CAcUiPathname& CAcUiPathname::operator=(const CAcUiPathname& pathSrc)
{
    AssignCopy( pathSrc);

    return *this;
}

inline const CAcUiPathname& CAcUiPathname::operator=(const CAcUiPathname* pathSrc)
{
    AssignCopy( *pathSrc);

    return *this;
}

#pragma pack (pop)

